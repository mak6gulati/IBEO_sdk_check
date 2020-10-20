//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Jan 14, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/scan/ScanImporter2205.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

#include <stdexcept> // std::out_of_range
#include <map>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::Scan;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Scan2205>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
// Specializations for RegisteredImporter
//==============================================================================

//generate link between data-type-id/importer and importer create function <dtid, ImpHash> ==> Imp::create

template<>
const Id R::registeredImporterInitial
    = Id(std::make_pair(R::getDataTypeStatic(), C::getClassIdHashStatic()), R::create);

//registering ... (create map)
//add all device that can receive any datatype that can be imported to GeneralDataTypeContainer
class IdcFile;
class IbeoEcu;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(registeredImporterInitial));

//==============================================================================

ibeo::common::logging::LoggerSPtr Importer<C, DataTypeId::DataType_Scan2205>::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_Scan2205>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return getSerializedSize(container->m_scannerInfos.size(), container->m_scanPoints.size());
}

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_Scan2205>::getSerializedSize(const std::size_t nbOfScannerInfos,
                                                                              const std::size_t nbOfScanPoints) const
{
    return std::streamsize(sizeof(NTPTime)) // scanStartTime
           + std::streamsize(sizeof(uint32_t)) // endTimeOffset
           + std::streamsize(sizeof(uint32_t)) // flags
           + std::streamsize(sizeof(uint16_t)) // scanNumber
           + std::streamsize(sizeof(uint16_t)) // nbOfScanPoints
           + std::streamsize(sizeof(uint8_t)) // nbOfScannerInfos
           + std::streamsize(sizeof(uint8_t)) // reserved
           + std::streamsize(sizeof(uint16_t)) // reserved
           + std::streamsize(nbOfScannerInfos) * ScannerInfoIn2205::getSerializedSize_static()
           + std::streamsize(nbOfScanPoints) * ScanPointIn2205::getSerializedSize_static();
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Scan2205>::deserialize(std::istream& is,
                                                             DataContainerBase& c,
                                                             const IbeoDataHeader& dh) const
{
    C* container{nullptr};
    try
    {
        container = &dynamic_cast<C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, container->m_scanStartTime);
    ibeo::common::sdk::readBE(is, container->m_endTimeOffset);

    ibeo::common::sdk::readBE(is, container->m_flags);
    ibeo::common::sdk::readBE(is, container->m_scanNumber);

    uint16_t nbScanPts = 0;
    ibeo::common::sdk::readBE(is, nbScanPts);
    container->m_scanPoints.resize(nbScanPts);

    uint8_t nbScanInfos = 0;
    ibeo::common::sdk::readBE(is, nbScanInfos);
    container->m_scannerInfos.resize(nbScanInfos);

    ibeo::common::sdk::readBE(is, container->m_reserved0);
    ibeo::common::sdk::readBE(is, container->m_reserved1);

    //read scanner infos and create a map with a transformation matrix to convert into vehicle coordinate system for each scanner
    std::map<uint8_t, TransformationMatrix3d<float>> scannerTransformationMap;
    for (ScannerInfo& scannerInfo : container->m_scannerInfos)
    {
        scannerInfo.deserialize(is);

        //As for now, by constraint, all coordinates within the general scan container are in vehicle-coordinates
        //We only do transformations when src-coordinate system is != ScanPointsCoordinateSystem::VehicleCoordinates
        if (container->isVehicleCoordinates())
        {
            // No conversion necessary -> use identity matrix.
            scannerTransformationMap[scannerInfo.getDeviceId()] = TransformationMatrix3d<float>();
        }
        else
        {
            scannerTransformationMap[scannerInfo.getDeviceId()] = scannerInfo.getCoordinateSystemTransformationMatrix();
        }
    }

    //read the scanpoints
    uint32_t destIdx = 0;
    for (uint32_t i = 0; i < nbScanPts; ++i)
    {
        container->m_scanPoints.at(i).deserialize(is);
        ScanPoint& currentScanPoint = container->m_scanPoints[i]; // bounds checking was done before

        if (container->isVehicleCoordinates() == false)
        {
            std::map<uint8_t, TransformationMatrix3d<float>>::const_iterator iter{
                scannerTransformationMap.find(currentScanPoint.getDeviceId())};
            if (iter == scannerTransformationMap.end())
            {
                LOGERROR(logger,
                         "Unknown scanner device ID " << static_cast<uint32_t>(currentScanPoint.getDeviceId())
                                                      << " found in scan point -> skipping scan point!");
                //throw std::logic_error("Invalid DeviceId provided");
                continue;
            }
            const TransformationMatrix3d<float>& transformationMatrix{iter->second};

            //Transform into vehicle coordinate system.
            Vector3<float> point{
                currentScanPoint.getPositionX(), currentScanPoint.getPositionY(), currentScanPoint.getPositionZ()};

            point = transformationMatrix * point;
            currentScanPoint.setPosX((point.getX()));
            currentScanPoint.setPosY((point.getY()));
            currentScanPoint.setPosZ((point.getZ()));
        }

        // Next point.
        ++destIdx;
    }

    if (destIdx < nbScanPts)
    {
        // Some points have been skipped -> adjust size.
        container->m_scanPoints.resize(destIdx);
    }

    container->setVehicleCoordinates();

    const std::streamsize serializedSize = getSerializedSize(container->m_scannerInfos.size(), nbScanPts);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == serializedSize)
           && serializedSize == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

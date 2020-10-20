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

#include <ibeo/common/sdk/datablocks/scan/ScanImporter2209.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/ScannerInfoIn2209.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/ScanPointIn2209.hpp>

#include <stdexcept> // std::out_of_range
#include <map>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::Scan;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Scan2209>;
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

ibeo::common::logging::LoggerSPtr Importer<C, DataTypeId::DataType_Scan2209>::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_Scan2209>::getSerializedSize(const DataContainerBase& c) const
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

std::streamsize Importer<C, DataTypeId::DataType_Scan2209>::getSerializedSize(const std::size_t nbOfScannerInfos,
                                                                              const std::size_t nbOfScanPoints) const
{
    return std::streamsize(sizeof(NTPTime)) + std::streamsize(3 * sizeof(uint32_t))
           + std::streamsize(1 * sizeof(uint16_t)) + std::streamsize(sizeof(uint8_t)) + 3
           + std::streamsize(nbOfScannerInfos) * ScannerInfoIn2209::getSerializedSize_static()
           + std::streamsize(nbOfScanPoints) * ScanPointIn2209::getSerializedSize_static(); //todo ????
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Scan2209>::deserialize(std::istream& is,
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

    uint32_t nbScanPts = 0;
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
    for (uint32_t srcIdx = 0; srcIdx < nbScanPts; ++srcIdx)
    {
        container->m_scanPoints.at(destIdx).deserialize(is);
        ScanPoint& currentScanPoint = container->m_scanPoints[destIdx]; // bounds checking was done before

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

    std::streamsize serializedSize = getSerializedSize(container->m_scannerInfos.size(), nbScanPts);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == serializedSize)
           && serializedSize == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

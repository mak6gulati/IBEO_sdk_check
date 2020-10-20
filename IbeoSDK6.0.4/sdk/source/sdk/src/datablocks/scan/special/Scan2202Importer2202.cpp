//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 15, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2202Importer2202.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::Scan2202;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Scan2202>;
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
class IbeoLux;
class IbeoTrackingBox;
class IbeoScala;
class IbeoEcu;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoLux>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoTrackingBox>::getInstance().registerImporter(
            ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
                ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(
                    registeredImporterInitial)))));

//==============================================================================

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_Scan2202>::getSerializedSize(const DataContainerBase& c) const
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

    return std::streamsize(3 * sizeof(uint16_t) + 2 * sizeof(NTPTime))
           + std::streamsize(2 * sizeof(uint16_t) + 2 * sizeof(int16_t))
           + std::streamsize(container->m_points.size()) * ScanPointIn2202::getSerializedSize_static()
           + std::streamsize(6 * sizeof(uint16_t) + sizeof(uint16_t));
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Scan2202>::deserialize(std::istream& is,
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

    container->setDataHeader(dh);

    const int64_t startPos = streamposToInt64(is.tellg());

    container->m_points.clear();

    ibeo::common::sdk::readLE(is, container->m_scanNumber);
    ibeo::common::sdk::readLE(is, container->m_scannerStatus);
    ibeo::common::sdk::readLE(is, container->m_syncPhaseOffset);
    ibeo::common::sdk::readLE(is, container->m_startNTP);
    ibeo::common::sdk::readLE(is, container->m_endNTP);
    if (!container->timeCheck())
    {
        LOGWARNING(container->logger,
                   "Read scan #" << container->getScanNumber() << ": Scan end time must be larger than scan start time."
                                 << " - discarding scan.");
        return false;
    }

    ibeo::common::sdk::readLE(is, container->m_angleTicksPerRotation);
    ibeo::common::sdk::readLE(is, container->m_startAngleTicks);
    ibeo::common::sdk::readLE(is, container->m_endAngleTicks);

    { // read the number of the scan points
        // and resize the point vector.
        uint16_t nbScanPts = 0;
        ibeo::common::sdk::readLE(is, nbScanPts);
        // adjust the list size
        container->m_points.resize(nbScanPts);
    }

    ibeo::common::sdk::readLE(is, container->m_mountingPosYawAngleTicks);
    ibeo::common::sdk::readLE(is, container->m_mountingPosPitchAngleTicks);
    ibeo::common::sdk::readLE(is, container->m_mountingPosRollAngleTicks);
    ibeo::common::sdk::readLE(is, container->m_mountingPosCmX);
    ibeo::common::sdk::readLE(is, container->m_mountingPosCmY);
    ibeo::common::sdk::readLE(is, container->m_mountingPosCmZ);
    ibeo::common::sdk::readLE(is, container->m_flags);

    std::vector<ScanPointIn2202>::iterator ptIter = container->m_points.begin();
    for (; ptIter != container->m_points.end(); ++ptIter)
    {
        ptIter->deserialize(is);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

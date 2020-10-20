//==============================================================================
//!!\file Scan2310Importer2310.cpp
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 11, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2310Importer2310.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::Scan2310;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Scan2310>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
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
class IbeoScala;
class IbeoTrackingBox;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
            ContainerBufferAndImporterProviderGlobal<IbeoTrackingBox>::getInstance().registerImporter(
                registeredImporterInitial))));

//==============================================================================

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_Scan2310>::getSerializedSize(const DataContainerBase& c) const
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

    return std::streamsize(60) + container->m_header.getSerializedSize() + container->m_info.getSerializedSize()
           + (std::streamsize(container->m_points.size()) * ScanPointIn2310::getSerializedSize_static())
           + (std::streamsize(container->m_segInfos.size()) * ScanSegInfoIn2310::getSerializedSize_static())
           + (std::streamsize(container->m_diagPulses.size()) * ScanPointDiagPulseIn2310::getSerializedSize_static())
           + (std::streamsize(container->m_refScans.size()) * ScanPointRefScanIn2310::getSerializedSize_static())
           + container->m_trailer.getSerializedSize() + std::streamsize(16);
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Scan2310>::deserialize(std::istream& is,
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
    bool ok                = true;

    container->m_points.clear();
    container->m_segInfos.clear();
    container->m_diagPulses.clear();
    container->m_refScans.clear();

    uint32_t readMagicWord{0};
    readBE(is, readMagicWord);
    if (C::magicWord != readMagicWord)
    {
        return false;
    }

    uint16_t readInternalDataTypeId{0};
    readBE(is, readInternalDataTypeId);
    if (C::internalDataTypeId != readInternalDataTypeId)
    {
        return false;
    }

    readBE(is, container->m_reserved00);
    readBE(is, container->m_payloadSize);
    readBE(is, container->m_utcSeconds);
    readBE(is, container->m_flexrayMeasTime);
    readBE(is, container->m_reserved01);
    readBE(is, container->m_reserved02);
    readBE(is, container->m_flexrayMasterClock);
    readBE(is, container->m_reserved03);
    readBE(is, container->m_versionInfo0);
    readBE(is, container->m_versionInfo1);
    readBE(is, container->m_scanStartTime);
    readBE(is, container->m_scanEndTime);
    readBE(is, container->m_scanMidTime);
    readBE(is, container->m_reserved04);

    // read header
    uint16_t readBlockId = 0;
    readLE(is, readBlockId);
    unget2(is);
    if (ScanHeaderIn2310::blockId != readBlockId)
    {
        return false;
    }

    ok = container->m_header.deserialize(is);
    if (!ok)
    {
        return false;
    }

    // read info
    readLE(is, readBlockId);
    unget2(is);
    if (ScanInfoIn2310::blockId != readBlockId)
    {
        return false;
    }

    ok = container->m_info.deserialize(is);
    if (!ok)
    {
        return false;
    }

    // read arrays until trailer
    bool complete = false;
    while ((!complete) && is.good() && ok)
    {
        readLE(is, readBlockId);
        unget2(is);
        if (ScanPointIn2310::blockId == readBlockId)
        {
            ScanPointIn2310 pt;
            ok = pt.deserialize(is);
            container->m_points.push_back(pt);
        }
        else if (ScanSegInfoIn2310::blockId == readBlockId)
        {
            ScanSegInfoIn2310 si;
            ok = si.deserialize(is);
            container->m_segInfos.push_back(si);
        }
        else if (ScanPointDiagPulseIn2310::blockId == readBlockId)
        {
            ScanPointDiagPulseIn2310 dp;
            ok = dp.deserialize(is);
            container->m_diagPulses.push_back(dp);
        }
        else if (ScanPointRefScanIn2310::blockId == readBlockId)
        {
            ScanPointRefScanIn2310 rs;
            ok = rs.deserialize(is);
            container->m_refScans.push_back(rs);
        }
        else if (ScanTrailerIn2310::blockId == readBlockId)
        {
            complete = true;
            ok       = container->m_trailer.deserialize(is);
        }
        else
        {
            return false;
        }
    } // while !complete, is.good and ok

    if ((!complete) || (ScanTrailerIn2310::blockId != readBlockId) || !ok)
    {
        return false;
    }

    readLE(is, container->m_crc32);
    readLE(is, container->m_reserved05);
    readLE(is, container->m_reserved06);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize() && ok;
}

//==============================================================================

void Scan2310Importer2310::unget2(std::istream& is)
{
    is.unget();
    is.unget();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

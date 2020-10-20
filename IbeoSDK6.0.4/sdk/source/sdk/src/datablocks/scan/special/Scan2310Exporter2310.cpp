//==============================================================================
//!\file
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

#include <ibeo/common/sdk/datablocks/scan/special/Scan2310Exporter2310.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::Scan2310;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_Scan2310>::getSerializedSize(const DataContainerBase& c) const
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

bool Exporter<C, DataTypeId::DataType_Scan2310>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, C::magicWord);
    writeBE(os, C::internalDataTypeId);
    writeBE(os, container->m_reserved00);
    writeBE(os, container->m_payloadSize);
    writeBE(os, container->m_utcSeconds);
    writeBE(os, container->m_flexrayMeasTime);
    writeBE(os, container->m_reserved01);
    writeBE(os, container->m_reserved02);
    writeBE(os, container->m_flexrayMasterClock);
    writeBE(os, container->m_reserved03);
    writeBE(os, container->m_versionInfo0);
    writeBE(os, container->m_versionInfo1);
    writeBE(os, container->m_scanStartTime);
    writeBE(os, container->m_scanEndTime);
    writeBE(os, container->m_scanMidTime);
    writeBE(os, container->m_reserved04);

    bool ok = true;
    ok      = container->m_header.serialize(os);
    if (!ok)
    {
        return false;
    }

    ok = container->m_info.serialize(os);
    if (!ok)
    {
        return false;
    }

    for (const ScanPointIn2310& pt : container->m_points)
    {
        ok = pt.serialize(os);
        if (!ok)
        {
            return false;
        }
    } // for

    for (const ScanSegInfoIn2310& si : container->m_segInfos)
    {
        ok = si.serialize(os);
        if (!ok)
        {
            return false;
        }
    } // for

    for (const ScanPointDiagPulseIn2310& dp : container->m_diagPulses)
    {
        ok = dp.serialize(os);
        if (!ok)
        {
            return false;
        }
    } // for

    for (const ScanPointRefScanIn2310& rs : container->m_refScans)
    {
        ok = rs.serialize(os);
        if (!ok)
        {
            return false;
        }
    }

    ok = container->m_trailer.serialize(os);
    if (!ok)
    {
        return false;
    }

    writeLE(os, container->m_crc32);
    writeLE(os, container->m_reserved05);
    writeLE(os, container->m_reserved06);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

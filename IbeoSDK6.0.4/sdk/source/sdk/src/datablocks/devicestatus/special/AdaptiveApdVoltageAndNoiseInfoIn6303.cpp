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
//! \date Jan 29, 2019
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/devicestatus/special/AdaptiveApdVoltageAndNoiseInfoIn6303.hpp>

#include <boost/iostreams/stream.hpp>

#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif // gcc or clang

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

uint8_t AdaptiveApdVoltageAndNoiseInfoIn6303::getSerializedSizeStatic()
{
    return static_cast<uint8_t>(sizeof(uint32_t) // procUnitAndVersion
                                + sizeof(uint16_t) // scanNumber
                                + nbOfSectors * ApdSector::getSerializedSizeStatic() // sectors
                                + sizeof(uint8_t) // flags
                                + nbOfReserved * sizeof(uint8_t) // reserved
    );
}

//==============================================================================

bool AdaptiveApdVoltageAndNoiseInfoIn6303::serialize(char*& buf) const
{
    boost::iostreams::stream<boost::iostreams::array> strm((char*)(buf), getSerializedSize());
    std::ostream& os = (std::ostream&)strm;

    writeBE(os, m_procUnitAndVersion);
    writeBE(os, m_scanNumber);
    for (const ApdSector& sector : m_sectors)
    {
        sector.serialize(os);
    }
    writeBE(os, m_flags);
    for (const uint8_t reserved : m_reserved)
    {
        writeBE(os, reserved);
    }

    buf += getSerializedSize();
    return true;
}

//==============================================================================

bool AdaptiveApdVoltageAndNoiseInfoIn6303::deserialize(const DeviceStatus6303::ContentDescr& cd)
{
    if (cd.getContentId() != DeviceStatus6303::ContentId::AdaptiveApdVoltageNoiseArray)
    {
        // Wrong content.
        return false;
    }

    if (cd.getNbOfBytes() < getSerializedSize())
    {
        // Not enough data in buffer.
        return false;
    }

    boost::iostreams::stream<boost::iostreams::array_source> is(cd.getContentBuffer(), cd.getNbOfBytes());

    readBE(is, m_procUnitAndVersion);
    readBE(is, m_scanNumber);
    for (ApdSector& sector : m_sectors)
    {
        sector.deserialize(is);
    }
    readBE(is, m_flags);
    for (uint8_t& reserved : m_reserved)
    {
        readBE(is, reserved);
    }

    return true;
}

//==============================================================================

bool operator==(const AdaptiveApdVoltageAndNoiseInfoIn6303& lhs, const AdaptiveApdVoltageAndNoiseInfoIn6303& rhs)
{
    return (lhs.getProcessingUnitAndVersion() == rhs.getProcessingUnitAndVersion())
           && (lhs.getScanNumber() == rhs.getScanNumber()) && (lhs.getSectors() == rhs.getSectors())
           && (lhs.getFlags() == rhs.getFlags()) && (lhs.getReserved() == rhs.getReserved());
}

//==============================================================================
//==============================================================================
//==============================================================================

uint8_t AdaptiveApdVoltageAndNoiseInfoIn6303::ApdSector::getSerializedSizeStatic()
{
    return sizeof(float) // adaptiveApdVoltage
           + sizeof(float) // reducedApdOffset
           + sizeof(uint16_t); // noise
}

//==============================================================================

bool AdaptiveApdVoltageAndNoiseInfoIn6303::ApdSector::serialize(std::ostream& os) const
{
    writeBE(os, m_adaptiveApdVoltage);
    writeBE(os, m_reducedApdOffset);
    writeBE(os, m_noise);

    return !os.fail();
}

//==============================================================================

bool AdaptiveApdVoltageAndNoiseInfoIn6303::ApdSector::deserialize(std::istream& is)
{
    readBE(is, m_adaptiveApdVoltage);
    readBE(is, m_reducedApdOffset);
    readBE(is, m_noise);

    return !is.fail();
}

//==============================================================================

bool operator==(const AdaptiveApdVoltageAndNoiseInfoIn6303::ApdSector& lhs,
                const AdaptiveApdVoltageAndNoiseInfoIn6303::ApdSector& rhs)
{
    return floatEqual(lhs.getAdaptiveApdVoltage(), rhs.getAdaptiveApdVoltage())
           && floatEqual(lhs.getReducedApdOffset(), rhs.getReducedApdOffset()) && (lhs.getNoise() == rhs.getNoise());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

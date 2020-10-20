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
//! \date Apr 25, 2012
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/scan/special/ScanPointIn2202.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ScanPointIn2202::ScanPointIn2202() {}

//==============================================================================

ScanPointIn2202::ScanPointIn2202(const ScanPointIn2202& src)
  : m_layer(src.m_layer),
    m_echo(src.m_echo),
    m_flags(src.m_flags),
    m_angle(src.m_angle),
    m_distance(src.m_distance),
    m_epw(src.m_epw),
    m_reserved(src.m_reserved)
{}

//==============================================================================

ScanPointIn2202& ScanPointIn2202::operator=(const ScanPointIn2202& src)
{
    if (&src != this)
    {
        m_layer    = src.m_layer;
        m_echo     = src.m_echo;
        m_flags    = src.m_flags;
        m_angle    = src.m_angle;
        m_distance = src.m_distance;
        m_epw      = src.m_epw;
        m_reserved = src.m_reserved;
    }

    return *this;
}

//==============================================================================

ScanPointIn2202::~ScanPointIn2202() {}

//==============================================================================

// static
std::streamsize ScanPointIn2202::getSerializedSize_static()
{
    return 2 * std::streamsize(sizeof(uint8_t)) + 3 * std::streamsize(sizeof(uint16_t)) + 2;
}

//==============================================================================

bool ScanPointIn2202::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    uint8_t layerAndEcho;
    ibeo::common::sdk::readLE(is, layerAndEcho);
    m_layer = layerAndEcho & 0xF;
    m_echo  = (layerAndEcho >> 4) & 0xF;
    ibeo::common::sdk::readLE(is, m_flags);
    ibeo::common::sdk::readLE(is, m_angle);
    ibeo::common::sdk::readLE(is, m_distance);

    ibeo::common::sdk::readLE(is, m_epw);
    ibeo::common::sdk::readLE(is, m_reserved);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ScanPointIn2202::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    const uint8_t layerAndEcho = uint8_t((m_echo << 4) | (m_layer & 0xF));
    ibeo::common::sdk::writeLE(os, layerAndEcho);
    ibeo::common::sdk::writeLE(os, m_flags);
    ibeo::common::sdk::writeLE(os, m_angle);
    ibeo::common::sdk::writeLE(os, m_distance);
    ibeo::common::sdk::writeLE(os, m_epw);
    ibeo::common::sdk::writeLE(os, m_reserved);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool operator==(const ScanPointIn2202& lhs, const ScanPointIn2202& rhs)
{
    return (lhs.getLayer() == rhs.getLayer()) && (lhs.getEcho() == rhs.getEcho()) && (lhs.getFlags() == rhs.getFlags())
           && (lhs.getHorizontalAngleTicks() == rhs.getHorizontalAngleTicks())
           && (lhs.getDistanceCm() == rhs.getDistanceCm()) && (lhs.getEchoPulseWidthCm() == rhs.getEchoPulseWidthCm())
           && (lhs.getReserved() == rhs.getReserved());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

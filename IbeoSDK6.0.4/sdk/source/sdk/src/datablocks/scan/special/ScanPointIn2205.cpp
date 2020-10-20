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
//! \date Apr 26, 2012
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/ScanPointIn2205.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/Math.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

ScanPointIn2205::ScanPointIn2205()
  : m_posX(0.),
    m_posY(0.),
    m_posZ(0.),
    m_epw(0.),
    m_deviceId(0),
    m_layer(0),
    m_echo(0),
    m_reserved(0),
    m_timeOffset(0),
    m_flags(0),
    m_segmentId(0)
{}

//==============================================================================

ScanPointIn2205::ScanPointIn2205(const ScanPointIn2205& other)
  : m_posX(other.m_posX),
    m_posY(other.m_posY),
    m_posZ(other.m_posZ),
    m_epw(other.m_epw),
    m_deviceId(other.m_deviceId),
    m_layer(other.m_layer),
    m_echo(other.m_echo),
    m_reserved(other.m_reserved),
    m_timeOffset(other.m_timeOffset),
    m_flags(other.m_flags),
    m_segmentId(other.m_segmentId)
{}

//==============================================================================

ScanPointIn2205& ScanPointIn2205::operator=(const ScanPointIn2205& other)
{
    m_posX       = other.m_posX;
    m_posY       = other.m_posY;
    m_posZ       = other.m_posZ;
    m_epw        = other.m_epw;
    m_deviceId   = other.m_deviceId;
    m_layer      = other.m_layer;
    m_echo       = other.m_echo;
    m_reserved   = other.m_reserved;
    m_timeOffset = other.m_timeOffset;
    m_flags      = other.m_flags;
    m_segmentId  = other.m_segmentId;

    return *this;
}

//==============================================================================

ScanPointIn2205::~ScanPointIn2205() {}

//==============================================================================

bool ScanPointIn2205::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_posX);
    ibeo::common::sdk::readBE(is, m_posY);
    ibeo::common::sdk::readBE(is, m_posZ);

    ibeo::common::sdk::readBE(is, m_epw);

    ibeo::common::sdk::readBE(is, m_deviceId);
    ibeo::common::sdk::readBE(is, m_layer);
    ibeo::common::sdk::readBE(is, m_echo);

    ibeo::common::sdk::readBE(is, m_reserved);

    ibeo::common::sdk::readBE(is, m_timeOffset);
    ibeo::common::sdk::readBE(is, m_flags);
    ibeo::common::sdk::readBE(is, m_segmentId);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

//static
std::streamsize ScanPointIn2205::getSerializedSize_static()
{
    return 4 * std::streamsize(sizeof(float)) + 3 * std::streamsize(sizeof(uint8_t)) + 1
           + std::streamsize(sizeof(uint32_t)) + std::streamsize(sizeof(uint16_t)) + 2;
}

//==============================================================================

bool ScanPointIn2205::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_posX);
    ibeo::common::sdk::writeBE(os, m_posY);
    ibeo::common::sdk::writeBE(os, m_posZ);

    ibeo::common::sdk::writeBE(os, m_epw);

    ibeo::common::sdk::writeBE(os, m_deviceId);
    ibeo::common::sdk::writeBE(os, m_layer);
    ibeo::common::sdk::writeBE(os, m_echo);

    ibeo::common::sdk::writeBE(os, m_reserved);

    ibeo::common::sdk::writeBE(os, m_timeOffset);
    ibeo::common::sdk::writeBE(os, m_flags);

    ibeo::common::sdk::writeBE(os, m_segmentId);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ScanPointIn2205::operator==(const ScanPointIn2205& other) const
{
    if (!(fuzzyFloatEqualT<7>(getPositionX(), other.getPositionX())))
        return false;

    if (!(fuzzyFloatEqualT<7>(getPositionY(), other.getPositionY())))
        return false;

    if (!(fuzzyFloatEqualT<7>(getPositionZ(), other.getPositionZ())))
        return false;

    if (!(fuzzyFloatEqualT<7>(getEchoPulseWidth(), other.getEchoPulseWidth())))
        return false;

    if (getDeviceId() != other.getDeviceId())
        return false;

    if (getLayer() != other.getLayer())
        return false;

    if (getEcho() != other.getEcho())
        return false;

    if (getReserved() != other.getReserved())
        return false;

    if (getTimeOffset() != other.getTimeOffset())
        return false;

    if (getFlags() != other.getFlags())
        return false;

    if (getSegmentId() != other.getSegmentId())
        return false;

    return true;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

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
//! \date Feb 21, 2017
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/ClockType.hpp>

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/EcefPoint.hpp>
#include <ibeo/common/sdk/DataBlockBufferProvider.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

template<>
inline void readBE<ClockType::ClockName>(std::istream& is, ClockType::ClockName& value)
{
    uint8_t tmp;
    readBE(is, tmp);
    value = ClockType::ClockName(tmp);
}

//==============================================================================

template<>
inline void writeBE<ClockType::ClockName>(std::ostream& os, const ClockType::ClockName& value)
{
    const uint8_t tmp = static_cast<uint8_t>(value);
    writeBE(os, tmp);
}

//==============================================================================

std::string ClockType::getClockNameString(const ClockName cn)
{
    switch (cn)
    {
    case ClockName::Unknown:
        return "unknown clock type";
    case ClockName::Laserscanner:
        return "Laserscanner";
    case ClockName::Ecu:
        return "ECU";
    case ClockName::CanBus:
        return "CAN Bus";
    case ClockName::Camera:
        return "Camera";
    case ClockName::GpsImu:
        return "GPS-IMU";
    case ClockName::Other:
        return "Other";
    default:
        return "undefined clock type";
    }
}

//==============================================================================

ClockType::ClockType() : m_clockId(0), m_clockName(ClockName::Unknown) {}

//==============================================================================

ClockType::ClockType(const uint8_t clockId, const ClockName clockName) : m_clockId(clockId), m_clockName(clockName) {}

//==============================================================================

ClockType::~ClockType() {}

//==============================================================================

std::streamsize ClockType::getSerializedSize() const { return 2 * sizeof(uint8_t); }

//==============================================================================

bool ClockType::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, this->m_clockId);

    uint8_t clName;
    ibeo::common::sdk::readBE(is, clName);
    this->m_clockName = ClockName(clName);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ClockType::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_clockId);
    ibeo::common::sdk::writeBE(os, static_cast<uint8_t>(m_clockName));

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================
bool ClockType::operator<(const ClockType& other) const
{
    if (m_clockId != other.m_clockId)
    {
        return m_clockId < other.m_clockId;
    }

    return m_clockName < other.m_clockName;
}

//==============================================================================

bool operator==(const ClockType& clk1, const ClockType& clk2)
{
    return (clk1.getClockId() == clk2.getClockId()) && (clk1.getClockName() == clk2.getClockName());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

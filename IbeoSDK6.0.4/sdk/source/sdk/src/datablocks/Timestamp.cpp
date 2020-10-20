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
//! \date Mar 28, 2017
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/Timestamp.hpp>

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/EcefPoint.hpp>
#include <ibeo/common/sdk/DataBlockBufferProvider.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

Timestamp::Timestamp()
  : m_measurementTimeEcu(NTPTime()),
    m_receivedTimeEcu(NTPTime()),
    m_rawDeviceTime(NTPTime()),
    m_measurementTime(NTPTime()),
    m_receivedTime(NTPTime()),
    m_clockType(ClockType(255, ClockType::ClockName::Unknown))

{}

//==============================================================================

Timestamp::Timestamp(const NTPTime measurementTimeEcu,
                     const NTPTime receivedTimeEcu,
                     const NTPTime rawDeviceTime,
                     const NTPTime measurementTime,
                     const NTPTime receivedTime,
                     const ClockType clockType)
  : m_measurementTimeEcu(measurementTimeEcu),
    m_receivedTimeEcu(receivedTimeEcu),
    m_rawDeviceTime(rawDeviceTime),
    m_measurementTime(measurementTime),
    m_receivedTime(receivedTime),
    m_clockType(clockType)
{}

//==============================================================================

Timestamp::Timestamp(const NTPTime measurementTimeEcu, const NTPTime receivedTimeEcu)
  : m_measurementTimeEcu(measurementTimeEcu), m_receivedTimeEcu(receivedTimeEcu)
{}

//==============================================================================

Timestamp::~Timestamp() {}

//==============================================================================

std::streamsize Timestamp::getSerializedSize() const
{
    std::streamsize result = 0;
    result += 8 * 5;
    result += this->m_clockType.getSerializedSize();
    return result;
}

//==============================================================================

bool Timestamp::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, this->m_measurementTimeEcu);
    ibeo::common::sdk::readBE(is, this->m_receivedTimeEcu);
    ibeo::common::sdk::readBE(is, this->m_rawDeviceTime);
    ibeo::common::sdk::readBE(is, this->m_measurementTime);
    ibeo::common::sdk::readBE(is, this->m_receivedTime);
    this->m_clockType.deserialize(is);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool Timestamp::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_measurementTimeEcu);
    ibeo::common::sdk::writeBE(os, m_receivedTimeEcu);
    ibeo::common::sdk::writeBE(os, m_rawDeviceTime);
    ibeo::common::sdk::writeBE(os, m_measurementTime);
    ibeo::common::sdk::writeBE(os, m_receivedTime);
    m_clockType.serialize(os);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool operator==(const Timestamp& ts1, const Timestamp& ts2)
{
    return (ts1.getMeasurementTimeEcu() == ts2.getMeasurementTimeEcu())
           && (ts1.getReceivedTimeEcu() == ts2.getReceivedTimeEcu())
           && (ts1.getRawDeviceTime() == ts2.getRawDeviceTime())
           && (ts1.getMeasurementTime() == ts2.getMeasurementTime()) && (ts1.getReceivedTime() == ts2.getReceivedTime())
           && (ts1.getClockType() == ts2.getClockType());
}

//==============================================================================

bool operator!=(const Timestamp& ts1, const Timestamp& ts2) { return !(ts1 == ts2); }

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

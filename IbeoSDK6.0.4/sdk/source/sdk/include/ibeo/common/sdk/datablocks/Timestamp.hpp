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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <ibeo/common/sdk/misc/deprecatedwarning.hpp>

#include <ibeo/common/sdk/datablocks/ClockType.hpp>
#include <ibeo/common/sdk/datablocks/TimestampInterface.hpp>

#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/Math.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class Timestamp : public ibeo::common::sdk::TimestampInterface
{
public:
    Timestamp();
    Timestamp(const NTPTime measurementTimeEcu,
              const NTPTime receivedTimeEcu,
              const NTPTime rawDeviceTime,
              const NTPTime measurementTime,
              const NTPTime receivedTime,
              const ClockType clockType);
    Timestamp(const NTPTime measurementTimeEcu, const NTPTime receivedTimeEcu);
    virtual ~Timestamp();

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    virtual NTPTime getReceivedTime() const override { return m_receivedTime; }
    virtual NTPTime getReceivedTimeEcu() const override { return m_receivedTimeEcu; }
    virtual ClockType getClockType() const override { return m_clockType; }
    virtual NTPTime getMeasurementTime() const override { return m_measurementTime; }
    virtual NTPTime getMeasurementTimeEcu() const override { return m_measurementTimeEcu; }
    virtual NTPTime getRawDeviceTime() const override { return m_rawDeviceTime; }
    virtual bool hasMeasurementTimeEcu() const override { return true; }
    virtual bool hasMeasurementTime() const override { return true; }

public:
    void setReceivedTime(const NTPTime& receivedTime) { this->m_receivedTime = receivedTime; }
    void setReceivedTimeECU(const NTPTime& receivedTimeEcu) { this->m_receivedTimeEcu = receivedTimeEcu; }
    void setRawDeviceTime(const NTPTime& rawDeviceTime) { this->m_rawDeviceTime = rawDeviceTime; }
    void setMeasurementTime(const NTPTime& measurementTime) { this->m_measurementTime = measurementTime; }
    void setMeasurementTimeEcu(const NTPTime& measurementTimeEcu) { this->m_measurementTimeEcu = measurementTimeEcu; }
    void setClockType(const ClockType& clockType) { this->m_clockType = clockType; }

private:
    NTPTime m_measurementTimeEcu;
    NTPTime m_receivedTimeEcu;
    NTPTime m_rawDeviceTime;
    NTPTime m_measurementTime;
    NTPTime m_receivedTime;
    ClockType m_clockType;
}; // Timestamp

//==============================================================================

bool operator==(const Timestamp& ts1, const Timestamp& ts2);
bool operator!=(const Timestamp& ts1, const Timestamp& ts2);

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

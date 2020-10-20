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

#include <ibeo/common/logging/logging.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class TimestampRecvOnly : public TimestampInterface
{
public:
    TimestampRecvOnly();
    TimestampRecvOnly(const NTPTime receivedTimeEcu, const NTPTime receivedTime, const ClockType clockType);
    virtual ~TimestampRecvOnly();

public:
    std::streamsize getSerializedSize() const;
    bool deserialize(std::istream& is);
    bool serialize(std::ostream& os) const;

public:
    NTPTime getReceivedTime() const override { return m_receivedTime; }
    NTPTime getReceivedTimeEcu() const override { return m_receivedTimeEcu; }
    ClockType getClockType() const override { return m_clockType; }

    NTPTime getMeasurementTime() const override
    {
        LOGTRACE(logger, "Measurement time not available, returning the closest estimate, ReceivedTime");
        return m_receivedTime;
    }

    NTPTime getMeasurementTimeEcu() const override
    {
        LOGTRACE(logger, "Measurement time not available, returning the closest estimate, ReceivedTimeECU");
        return m_receivedTimeEcu;
    }

    NTPTime getRawDeviceTime() const override
    {
        LOGTRACE(logger, "Not available");
        return false;
    }

    bool hasMeasurementTimeEcu() const override { return false; }
    bool hasMeasurementTime() const override { return false; }

public:
    void setReceivedTime(const NTPTime& receivedTime) { this->m_receivedTime = receivedTime; }
    void setReceivedTimeEcu(const NTPTime& receivedTimeEcu) { this->m_receivedTimeEcu = receivedTimeEcu; }
    void setClockType(const ClockType& clockType) { this->m_clockType = clockType; }

private:
    static constexpr const char* loggerId = "ibeo::common::sdk::TimestampRecvOnly";
    static ibeo::common::logging::LoggerSPtr logger;

private:
    NTPTime m_receivedTimeEcu;
    NTPTime m_receivedTime;
    ClockType m_clockType;
}; // TimestampRecvOnly

//==============================================================================

bool operator==(const TimestampRecvOnly& ts1, const TimestampRecvOnly& ts2);

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

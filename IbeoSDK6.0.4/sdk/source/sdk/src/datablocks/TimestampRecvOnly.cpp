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

#include <ibeo/common/sdk/datablocks/TimestampRecvOnly.hpp>
#include <ibeo/common/sdk/datablocks/ClockType.hpp>

#include <ibeo/common/sdk/EcefPoint.hpp>
#include <ibeo/common/sdk/DataBlockBufferProvider.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

ibeo::common::logging::LoggerSPtr TimestampRecvOnly::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

TimestampRecvOnly::TimestampRecvOnly()
  : m_receivedTimeEcu(NTPTime()), m_receivedTime(NTPTime()), m_clockType(ClockType(255, ClockType::ClockName::Unknown))
{}

//==============================================================================

TimestampRecvOnly::TimestampRecvOnly(const NTPTime receivedTimeEcu,
                                     const NTPTime receivedTime,
                                     const ClockType clockType)
  : m_receivedTimeEcu(receivedTimeEcu), m_receivedTime(receivedTime), m_clockType(clockType)
{}

//==============================================================================

TimestampRecvOnly::~TimestampRecvOnly() {}

//==============================================================================

std::streamsize TimestampRecvOnly::getSerializedSize() const
{
    int32_t result = 0;
    result += 8 * 2;
    result += int32_t(this->m_clockType.getSerializedSize());
    return result;
}

//==============================================================================

bool TimestampRecvOnly::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, this->m_receivedTimeEcu);
    ibeo::common::sdk::readBE(is, this->m_receivedTime);
    this->m_clockType.deserialize(is);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool TimestampRecvOnly::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_receivedTimeEcu);
    ibeo::common::sdk::writeBE(os, m_receivedTime);
    m_clockType.serialize(os);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool operator==(const TimestampRecvOnly& ts1, const TimestampRecvOnly& ts2)
{
    return (ts1.getReceivedTimeEcu() == ts2.getReceivedTimeEcu()) && (ts1.getReceivedTime() == ts2.getReceivedTime())
           && (ts1.getClockType() == ts2.getClockType());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

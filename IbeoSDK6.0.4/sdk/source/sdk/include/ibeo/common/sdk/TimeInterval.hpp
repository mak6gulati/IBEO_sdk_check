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
//! \date Jul 11, 2016
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <misc/WinCompatibility.hpp>

#include <Time.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class TimeInterval
{
public:
    TimeInterval(const NTPTime& startTime,
                 const NTPTime& endTime,
                 const bool startIsIncluded = true,
                 const bool endIsIncluded   = true)
      : m_startTime(startTime), m_endTime(endTime), m_startIsIncluded(startIsIncluded), m_endIsIncluded(endIsIncluded)
    {}

public:
    const NTPTime& getStartTime() const { return m_startTime; }
    const NTPTime& getEndTime() const { return m_endTime; }

    bool isStartTimeIncluded() const { return m_startIsIncluded; }
    bool isEndTimeIncluded() const { return m_endIsIncluded; }

protected:
    NTPTime m_startTime;
    NTPTime m_endTime;
    bool m_startIsIncluded;
    bool m_endIsIncluded;
}; // TimeInterval

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

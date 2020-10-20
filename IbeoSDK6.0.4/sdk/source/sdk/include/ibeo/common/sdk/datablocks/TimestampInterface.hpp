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

#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/Math.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class TimestampInterface
{
public:
    TimestampInterface(){};
    virtual ~TimestampInterface(){};

public:
    virtual NTPTime getReceivedTime() const       = 0;
    virtual NTPTime getMeasurementTime() const    = 0;
    virtual NTPTime getReceivedTimeEcu() const    = 0;
    virtual NTPTime getMeasurementTimeEcu() const = 0;
    virtual ClockType getClockType() const        = 0;
    virtual NTPTime getRawDeviceTime() const      = 0;
    virtual bool hasMeasurementTimeEcu() const    = 0;
    virtual bool hasMeasurementTime() const       = 0;
};

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

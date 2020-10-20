//==============================================================================
//!\file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Feb 24, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/timerecord/TimeRecord9000.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class TimeRecord9000TestSupport : public TestSupport
{
public:
    TimeRecord9000TestSupport();
    virtual ~TimeRecord9000TestSupport();

public:
    static ibeo::common::sdk::TimeRecord9000 createTimeRecord9000();

private:
    static void fillRandomly(ibeo::common::sdk::TimeRecord9000& tr);

protected:
    static const int32_t nbOfRepeats = 100;
}; // TimeRecord9000TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

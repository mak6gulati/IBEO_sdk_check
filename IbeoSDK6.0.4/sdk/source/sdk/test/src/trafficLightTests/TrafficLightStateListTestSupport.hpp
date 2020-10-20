//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Aug 29, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <common/TestSupport.hpp>
#include <ibeo/common/sdk/datablocks/trafficlight/TrafficLightStateList.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class TrafficLightStateListTestSupport : public TestSupport
{
public:
    TrafficLightStateListTestSupport();
    virtual ~TrafficLightStateListTestSupport() = default;

public:
    static TrafficLightStateList createTrafficLightStateList();
    static void fillRandomly(TrafficLightStateList& trafficLightStateList);

protected:
    static constexpr int32_t numRepeats = 100;

}; // TrafficLightStateListTestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

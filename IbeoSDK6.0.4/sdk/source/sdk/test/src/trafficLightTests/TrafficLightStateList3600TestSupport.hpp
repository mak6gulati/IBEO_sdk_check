//==============================================================================
//!\file
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 02, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <common/TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/trafficlight/special/TrafficLightStateList3600.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class TrafficLightStateList3600TestSupport : public TestSupport
{
public:
    TrafficLightStateList3600TestSupport();
    virtual ~TrafficLightStateList3600TestSupport() = default;

public:
    static TrafficLightStateList3600 createTrafficLightStateList3600();
    static void fillRandomly3600(TrafficLightStateList3600& trafficLightStateList);

protected:
    static constexpr int32_t numRepeats = 100;

}; // TrafficLightStateList3600TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

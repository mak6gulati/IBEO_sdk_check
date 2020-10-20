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

#include <ibeo/common/sdk/datablocks/trafficlight/special/TrafficLightStateList3600.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

TrafficLightStateList3600::TrafficLightStateList3600() : SpecializedDataContainer() {}

//==============================================================================

bool operator==(const TrafficLightStateList3600& lhs, const TrafficLightStateList3600& rhs)
{
    return (lhs.getTrafficLightStates() == rhs.getTrafficLightStates());
}

//==============================================================================

bool operator!=(const TrafficLightStateList3600& lhs, const TrafficLightStateList3600& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

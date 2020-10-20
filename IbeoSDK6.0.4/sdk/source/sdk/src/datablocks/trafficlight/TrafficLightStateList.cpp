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
//!\date 14.November 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/trafficlight/TrafficLightStateList.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

TrafficLightStateList::TrafficLightStateList() : DataContainerBase() {}

//==============================================================================

bool operator==(const TrafficLightStateList& lhs, const TrafficLightStateList& rhs)
{
    return (lhs.getTrafficLightStates() == rhs.getTrafficLightStates());
}

//==============================================================================

bool operator!=(const TrafficLightStateList& lhs, const TrafficLightStateList& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

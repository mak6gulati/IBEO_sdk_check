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
//!\date Mar 26, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/vehiclecontrol/VehicleControl9100.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

bool operator==(const VehicleControl9100& lhs, const VehicleControl9100& rhs)
{
    return (lhs.getTimestamp() == rhs.getTimestamp()) && (lhs.getSourceType() == rhs.getSourceType())
           && (lhs.getSteeringType() == rhs.getSteeringType()) && (lhs.getSteeringValue() == rhs.getSteeringValue())
           && (lhs.getIndicatorState() == rhs.getIndicatorState())
           && (lhs.getAccelerationValue() == rhs.getAccelerationValue()) && (lhs.isDoStop() == rhs.isDoStop())
           && (lhs.getStopDistance() == rhs.getStopDistance());
}

//==============================================================================

bool operator!=(const VehicleControl9100& lhs, const VehicleControl9100& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

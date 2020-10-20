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
//! \date Sep 2, 2013
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2805.hpp>

#include <ibeo/common/sdk/Math.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

VehicleState2805::VehicleState2805() : SpecializedDataContainer() {}

//==============================================================================

VehicleState2805::~VehicleState2805() {}

//==============================================================================

bool operator==(const VehicleState2805& lhs, const VehicleState2805& rhs)
{
    return (lhs.getTimestamp() == rhs.getTimestamp()) && (lhs.getScanNumber() == rhs.getScanNumber())
           && (lhs.getErrorFlags() == rhs.getErrorFlags())
           && (lhs.getLongitudinalVelocity() == rhs.getLongitudinalVelocity())
           && (lhs.getSteeringWheelAngle() == rhs.getSteeringWheelAngle())
           && (lhs.getWheelAngle() == rhs.getWheelAngle()) && (lhs.getXPosition() == rhs.getXPosition())
           && (lhs.getYPosition() == rhs.getYPosition()) && (lhs.getCourseAngle() == rhs.getCourseAngle())
           && (lhs.getTimeDiff() == rhs.getTimeDiff()) && (lhs.getXDiff() == rhs.getXDiff())
           && (lhs.getYDiff() == rhs.getYDiff()) && (lhs.getYaw() == rhs.getYaw())
           && (lhs.getCurrentYawRate() == rhs.getCurrentYawRate())
           && (lhs.getCrossAcceleration() == rhs.getCrossAcceleration())
           && (lhs.getCalculationMethod() == rhs.getCalculationMethod()) && (lhs.getReserved2() == rhs.getReserved2());
}

//==============================================================================

//==============================================================================

bool operator!=(const VehicleState2805& lhs, const VehicleState2805& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

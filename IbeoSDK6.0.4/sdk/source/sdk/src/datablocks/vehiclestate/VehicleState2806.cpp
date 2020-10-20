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
//! \date Jan 14, 2013
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2806.hpp>

#include <ibeo/common/sdk/Math.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
// Specializations for RegisteredDataBlock<VehicleState2806>
//==============================================================================

VehicleState2806::VehicleState2806() : SpecializedDataContainer() {}

//==============================================================================

VehicleState2806::~VehicleState2806() {}

//==============================================================================

bool operator==(const VehicleState2806& lhs, const VehicleState2806& rhs)
{
    return (lhs.getMicroseconds() == rhs.getMicroseconds()) && (lhs.getTimestamp() == rhs.getTimestamp())
           && (lhs.getXPosition() == rhs.getXPosition()) && (lhs.getYPosition() == rhs.getYPosition())
           && (fuzzyFloatEqualT<7>(lhs.getCourseAngle(), rhs.getCourseAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getLongitudinalVelocity(), rhs.getLongitudinalVelocity()))
           && (fuzzyFloatEqualT<7>(lhs.getYawRate(), rhs.getYawRate()))
           && (fuzzyFloatEqualT<7>(lhs.getSteeringWheelAngle(), rhs.getSteeringWheelAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getFrontWheelAngle(), rhs.getFrontWheelAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getVehicleWidth(), rhs.getVehicleWidth()))
           && (fuzzyFloatEqualT<7>(lhs.getVehicleFrontToFrontAxle(), rhs.getVehicleFrontToFrontAxle()))
           && (fuzzyFloatEqualT<7>(lhs.getFrontAxleToRearAxle(), rhs.getFrontAxleToRearAxle()))
           && (fuzzyFloatEqualT<7>(lhs.getRearAxleToVehicleRear(), rhs.getRearAxleToVehicleRear()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff0(), rhs.getSteerRatioCoeff0()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff1(), rhs.getSteerRatioCoeff1()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff2(), rhs.getSteerRatioCoeff2()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff3(), rhs.getSteerRatioCoeff3()))
           && (fuzzyFloatEqualT<7>(lhs.getCrossAcceleration(), rhs.getCrossAcceleration()))
           && (lhs.getBlindPredictionAge() == rhs.getBlindPredictionAge())
           && (fuzzyFloatEqualT<7>(lhs.getMinTurningCircle(), rhs.getMinTurningCircle()))
           && (fuzzyFloatEqualT<7>(lhs.getRearAxleToOrigin(), rhs.getRearAxleToOrigin()));
}

//==============================================================================

bool operator!=(const VehicleState2806& lhs, const VehicleState2806& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

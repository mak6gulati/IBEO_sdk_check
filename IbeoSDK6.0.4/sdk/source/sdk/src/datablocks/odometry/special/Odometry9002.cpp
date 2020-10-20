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
//!\date Mar 18, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/odometry/special/Odometry9002.hpp>
//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

Odometry9002::Odometry9002() : SpecializedDataContainer() {}

//==============================================================================

bool operator==(const Odometry9002& lhs, const Odometry9002& rhs)
{
    return doubleEqual(lhs.getSteeringAngle(), rhs.getSteeringAngle())
           && doubleEqual(lhs.getSteeringWheelAngle(), rhs.getSteeringWheelAngle())
           && doubleEqual(lhs.getSteeringWheelAngleVelocity(), rhs.getSteeringWheelAngleVelocity())
           && doubleEqual(lhs.getWheelSpeedFL(), rhs.getWheelSpeedFL())
           && doubleEqual(lhs.getWheelSpeedFR(), rhs.getWheelSpeedFR())
           && doubleEqual(lhs.getWheelSpeedRL(), rhs.getWheelSpeedRL())
           && doubleEqual(lhs.getWheelSpeedRR(), rhs.getWheelSpeedRR())
           && doubleEqual(lhs.getWheelCircumference(), rhs.getWheelCircumference())
           && doubleEqual(lhs.getVehVelocity(), rhs.getVehVelocity())
           && doubleEqual(lhs.getVehAcceleration(), rhs.getVehAcceleration())
           && doubleEqual(lhs.getVehYawRate(), rhs.getVehYawRate()) && lhs.getTimestamp() == rhs.getTimestamp()
           && floatEqual(lhs.getWheelBase(), rhs.getWheelBase()) && lhs.getReserved() == rhs.getReserved();
}

//==============================================================================

bool operator!=(const Odometry9002& lhs, const Odometry9002& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

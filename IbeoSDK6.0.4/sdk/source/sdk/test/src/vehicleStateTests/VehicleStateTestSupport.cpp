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
//!\date March 23, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "VehicleStateTestSupport.hpp"

#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================
template<>
void VehicleStateTestSupport::fillRandomly(VehicleState2805& vs)
{
    vs.setTimestamp(getRandValue<NTPTime>());
    vs.setScanNumber(getRandValue<uint16_t>());
    vs.setErrorFlags(getRandValue<uint16_t>());
    vs.setLongitudinalVelocity(getRandValue<int16_t>());
    vs.setSteeringWheelAngle(getRandValue<int16_t>());
    vs.setWheelAngle(getRandValue<int16_t>());
    vs.setXPosition(getRandValue<int32_t>());
    vs.setYPosition(getRandValue<int32_t>());
    vs.setCourseAngle(getRandValue<int16_t>());
    vs.setTimeDiff(getRandValue<uint16_t>());
    vs.setXDiff(getRandValue<int16_t>());
    vs.setYDiff(getRandValue<int16_t>());
    vs.setYaw(getRandValue<int16_t>());
    vs.setCurrentYawRate(getRandValue<int16_t>());
    vs.setCrossAcceleration(getRandValue<int16_t>());
    vs.setCalculationMethod(getRandValue<uint16_t>());
    vs.setReserved2(getRandValue<uint32_t>());
}

//==============================================================================
template<>
void VehicleStateTestSupport::fillRandomly(VehicleState2806& vs)
{
    vs.setMicroseconds(getRandValue<uint32_t>());
    vs.setTimestamp(getRandValue<NTPTime>());
    vs.setXPosition(getRandValue<int32_t>());
    vs.setYPosition(getRandValue<int32_t>());
    vs.setCourseAngle(getRandValue<float>());
    vs.setLongitudinalVelocity(getRandValue<float>());
    vs.setYawRate(getRandValue<float>());
    vs.setSteeringWheelAngle(getRandValue<float>());
    vs.setFrontWheelAngle(getRandValue<float>());
    vs.setVehicleWidth(getRandValue<float>());
    vs.setVehicleFrontToFrontAxle(getRandValue<float>());
    vs.setFrontAxleToRearAxle(getRandValue<float>());
    vs.setRearAxleToVehicleRear(getRandValue<float>());
    vs.setSteerRatioCoeff0(getRandValue<float>());
    vs.setSteerRatioCoeff1(getRandValue<float>());
    vs.setSteerRatioCoeff2(getRandValue<float>());
    vs.setSteerRatioCoeff3(getRandValue<float>());
    vs.setCrossAcceleration(getRandValue<float>());
    vs.setBlindPredictionAge(getRandValue<uint16_t>());
    vs.setMinTurningCircle(getRandValue<float>());
    vs.setRearAxleToOrigin(getRandValue<float>());
}

//==============================================================================
template<>
void VehicleStateTestSupport::fillRandomly(VehicleState2807& vs)
{
    vs.setMicroseconds(getRandValue<uint32_t>());
    vs.setTimestamp(getRandValue<NTPTime>());
    vs.setXPosition(getRandValue<int32_t>());
    vs.setYPosition(getRandValue<int32_t>());
    vs.setCourseAngle(getRandValue<float>());
    vs.setLongitudinalVelocity(getRandValue<float>());
    vs.setYawRate(getRandValue<float>());
    vs.setSteeringWheelAngle(getRandValue<float>());
    vs.setCrossAcceleration(getRandValue<float>());
    vs.setFrontWheelAngle(getRandValue<float>());
    vs.setBlindPredictionAge(getRandValue<uint16_t>());
    vs.setVehicleWidth(getRandValue<float>());
    vs.setMinTurningCircle(getRandValue<float>());
    vs.setVehicleFrontToFrontAxle(getRandValue<float>());
    vs.setFrontAxleToRearAxle(getRandValue<float>());
    vs.setRearAxleToVehicleRear(getRandValue<float>());
    vs.setRearAxleToOrigin(getRandValue<float>());
    vs.setSteerRatioCoeff0(getRandValue<float>());
    vs.setSteerRatioCoeff1(getRandValue<float>());
    vs.setSteerRatioCoeff2(getRandValue<float>());
    vs.setSteerRatioCoeff3(getRandValue<float>());
    vs.setLongitudinalAcceleration(getRandValue<float>());
}

//==============================================================================

template<>
void VehicleStateTestSupport::fillRandomly(VehicleState2808& vs)
{
    vs.setMicroseconds(getRandValue<uint32_t>());
    vs.setTimestamp(getRandValue<NTPTime>());
    vs.setSources(getRandValue<uint16_t>());
    vs.setBlindPredictionAge(getRandValue<uint16_t>());
    vs.setLatitude(getRandValue<double>());
    vs.setLatitudeSigma(getRandValue<float>());
    vs.setLongitude(getRandValue<double>());
    vs.setLongitudeSigma(getRandValue<float>());
    vs.setAltitude(getRandValue<float>());
    vs.setAltitudeSigma(getRandValue<float>());

    vs.setXPosition(getRandValue<double>());
    vs.setXPositionSigma(getRandValue<float>());
    vs.setYPosition(getRandValue<double>());
    vs.setYPositionSigma(getRandValue<float>());
    vs.setZPosition(getRandValue<float>());
    vs.setZPositionSigma(getRandValue<float>());

    vs.setXyCorrelation(getRandValue<float>());
    vs.setXzCorrelation(getRandValue<float>());
    vs.setYzCorrelation(getRandValue<float>());

    vs.setCourseAngle(getRandValue<float>());
    vs.setCourseAngleSigma(getRandValue<float>());
    vs.setHeadingAngle(getRandValue<float>());
    vs.setHeadingAngleSigma(getRandValue<float>());

    vs.setVehiclePitchAngle(getRandValue<float>());
    vs.setVehiclePitchAngleSigma(getRandValue<float>());

    vs.setVehicleRollAngle(getRandValue<float>());
    vs.setVehicleRollAngleSigma(getRandValue<float>());

    vs.setLongitudinalVelocity(getRandValue<float>());
    vs.setLongitudinalVelocitySigma(getRandValue<float>());

    vs.setYawRate(getRandValue<float>());
    vs.setYawRateSigma(getRandValue<float>());

    vs.setLongitudinalAcceleration(getRandValue<float>());
    vs.setLongitudinalAccelerationSigma(getRandValue<float>());
    vs.setCrossAcceleration(getRandValue<float>());
    vs.setCrossAccelerationSigma(getRandValue<float>());

    vs.setSteerAngle(getRandValue<float>());
    vs.setSteeringWheelAngle(getRandValue<float>());

    vs.setVehicleWidth(getRandValue<float>());
    vs.setMinTurningCircle(getRandValue<float>());

    vs.setVehicleFrontToFrontAxle(getRandValue<float>());
    vs.setFrontAxleToRearAxle(getRandValue<float>());
    vs.setRearAxleToVehicleRear(getRandValue<float>());
    vs.setRearAxleToOrigin(getRandValue<float>());
    vs.setSteerRatioCoeff0(getRandValue<float>());
    vs.setSteerRatioCoeff1(getRandValue<float>());
    vs.setSteerRatioCoeff2(getRandValue<float>());
    vs.setSteerRatioCoeff3(getRandValue<float>());
}

//==============================================================================

template<>
void VehicleStateTestSupport::fillRandomly(VehicleState& vs)
{
    vs.setMicroseconds(getRandValue<uint32_t>());
    vs.setTimestamp(getRandValue<NTPTime>());
    vs.setSources(getRandValue<uint16_t>());
    vs.setBlindPredictionAge(getRandValue<uint16_t>());
    vs.setLatitudeOfOrigin(getRandValue<double>());
    vs.setLatitudeOfOriginSigma(getRandValue<float>());
    vs.setLongitudeOfOrigin(getRandValue<double>());
    vs.setLongitudeOfOriginSigma(getRandValue<float>());
    vs.setAltitudeOfOrigin(getRandValue<float>());
    vs.setAltitudeOfOriginSigma(getRandValue<float>());

    vs.setRelativeXPosition(getRandValue<double>());
    vs.setRelativeXPositionSigma(getRandValue<float>());
    vs.setRelativeYPosition(getRandValue<double>());
    vs.setRelativeYPositionSigma(getRandValue<float>());
    vs.setRelativeZPosition(getRandValue<float>());
    vs.setRelativeZPositionSigma(getRandValue<float>());

    vs.setXyCorrelation(getRandValue<float>());
    vs.setXzCorrelation(getRandValue<float>());
    vs.setYzCorrelation(getRandValue<float>());

    vs.setCourseAngle(getRandValue<float>());
    vs.setCourseAngleSigma(getRandValue<float>());
    vs.setHeadingAngle(getRandValue<float>());
    vs.setHeadingAngleSigma(getRandValue<float>());

    vs.setVehiclePitchAngle(getRandValue<float>());
    vs.setVehiclePitchAngleSigma(getRandValue<float>());

    vs.setVehicleRollAngle(getRandValue<float>());
    vs.setVehicleRollAngleSigma(getRandValue<float>());

    vs.setLongitudinalVelocity(getRandValue<float>());
    vs.setLongitudinalVelocitySigma(getRandValue<float>());

    vs.setYawRate(getRandValue<float>());
    vs.setYawRateSigma(getRandValue<float>());

    vs.setLongitudinalAcceleration(getRandValue<float>());
    vs.setLongitudinalAccelerationSigma(getRandValue<float>());
    vs.setCrossAcceleration(getRandValue<float>());
    vs.setCrossAccelerationSigma(getRandValue<float>());

    vs.setSteerAngle(getRandValue<float>());
    vs.setSteeringWheelAngle(getRandValue<float>());

    vs.setVehicleWidth(getRandValue<float>());
    vs.setMinTurningCircle(getRandValue<float>());

    vs.setVehicleFrontToFrontAxle(getRandValue<float>());
    vs.setFrontAxleToRearAxle(getRandValue<float>());
    vs.setRearAxleToVehicleRear(getRandValue<float>());
    vs.setRearAxleToOrigin(getRandValue<float>());
    vs.setSteerRatioCoeff0(getRandValue<float>());
    vs.setSteerRatioCoeff1(getRandValue<float>());
    vs.setSteerRatioCoeff2(getRandValue<float>());
    vs.setSteerRatioCoeff3(getRandValue<float>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

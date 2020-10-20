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
//!\date 	11.08.2017
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState.hpp>
#include <ibeo/common/sdk/io.hpp>

#include <string>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

VehicleState::VehicleState(DataTypeId::DataType importerType) : DataContainerBase(importerType) {}

//==============================================================================

PositionWgs84 VehicleState::getReferencePoint() const
{
    PositionWgs84 out;

    if ((!std::isnan(m_latitudeOfOrigin)) && (!std::isnan(m_longitudeOfOrigin)))
    {
        out.setLatitudeInDeg(m_latitudeOfOrigin);
        out.setLongitudeInDeg(m_longitudeOfOrigin);
    }
    else
    {
        out.setLatitudeInDeg(0.0);
        out.setLongitudeInDeg(0.0);
    }
    out.setAltitudeInMeterMSL(static_cast<double>(m_altitudeOfOrigin));
    out.setCourseAngleInDeg(0.0);

    return out;
}

//==============================================================================

bool operator==(const VehicleState& lhs, const VehicleState& rhs)
{
    return (lhs.getMicroseconds() == rhs.getMicroseconds()) && (lhs.getTimestamp() == rhs.getTimestamp())

           && (fuzzyDoubleEqualT<7>(lhs.getRelativeXPosition(), rhs.getRelativeXPosition()))
           && (fuzzyFloatEqualT<7>(lhs.getRelativeXPositionSigma(), rhs.getRelativeXPositionSigma()))
           && (fuzzyDoubleEqualT<7>(lhs.getRelativeYPosition(), rhs.getRelativeYPosition()))
           && (fuzzyFloatEqualT<7>(lhs.getRelativeYPositionSigma(), rhs.getRelativeYPositionSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getRelativeZPosition(), rhs.getRelativeZPosition()))
           && (fuzzyFloatEqualT<7>(lhs.getRelativeZPositionSigma(), rhs.getRelativeZPositionSigma()))

           && (fuzzyFloatEqualT<7>(lhs.getCourseAngle(), rhs.getCourseAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getCourseAngleSigma(), rhs.getCourseAngleSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getHeadingAngle(), rhs.getHeadingAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getHeadingAngleSigma(), rhs.getHeadingAngleSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getSteeringWheelAngle(), rhs.getSteeringWheelAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerAngle(), rhs.getSteerAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getYawRate(), rhs.getYawRate()))
           && (fuzzyFloatEqualT<7>(lhs.getYawRateSigma(), rhs.getYawRateSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getVehiclePitchAngle(), rhs.getVehiclePitchAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getVehiclePitchAngleSigma(), rhs.getVehiclePitchAngleSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getVehicleRollAngle(), rhs.getVehicleRollAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getVehicleRollAngleSigma(), rhs.getVehicleRollAngleSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getCrossAcceleration(), rhs.getCrossAcceleration()))
           && (fuzzyFloatEqualT<7>(lhs.getCrossAccelerationSigma(), rhs.getCrossAccelerationSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getLongitudinalAcceleration(), rhs.getLongitudinalAcceleration()))
           && (fuzzyFloatEqualT<7>(lhs.getLongitudinalAccelerationSigma(), rhs.getLongitudinalAccelerationSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getLongitudinalVelocity(), rhs.getLongitudinalVelocity()))
           && (fuzzyFloatEqualT<7>(lhs.getLongitudinalVelocitySigma(), rhs.getLongitudinalVelocitySigma()))
           && (fuzzyFloatEqualT<7>(lhs.getVehicleFrontToFrontAxle(), rhs.getVehicleFrontToFrontAxle()))
           && (fuzzyFloatEqualT<7>(lhs.getFrontAxleToRearAxle(), rhs.getFrontAxleToRearAxle()))
           && (fuzzyFloatEqualT<7>(lhs.getRearAxleToVehicleRear(), rhs.getRearAxleToVehicleRear()))
           && (fuzzyFloatEqualT<7>(lhs.getRearAxleToOrigin(), rhs.getRearAxleToOrigin()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff0(), rhs.getSteerRatioCoeff0()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff1(), rhs.getSteerRatioCoeff1()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff2(), rhs.getSteerRatioCoeff2()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff3(), rhs.getSteerRatioCoeff3()))
           && (fuzzyFloatEqualT<7>(lhs.getVehicleWidth(), rhs.getVehicleWidth()))
           && (fuzzyFloatEqualT<7>(lhs.getAltitudeOfOrigin(), rhs.getAltitudeOfOrigin()))
           && (fuzzyFloatEqualT<7>(lhs.getAltitudeOfOriginSigma(), rhs.getAltitudeOfOriginSigma()))
           && (fuzzyDoubleEqualT<7>(lhs.getLatitudeOfOrigin(), rhs.getLatitudeOfOrigin()))
           && (fuzzyFloatEqualT<7>(lhs.getLatitudeOfOriginSigma(), rhs.getLatitudeOfOriginSigma()))
           && (fuzzyDoubleEqualT<7>(lhs.getLongitudeOfOrigin(), rhs.getLongitudeOfOrigin()))
           && (fuzzyFloatEqualT<7>(lhs.getLongitudeOfOriginSigma(), rhs.getLongitudeOfOriginSigma()))
           && (lhs.getBlindPredictionAge() == rhs.getBlindPredictionAge())
           && (fuzzyFloatEqualT<7>(lhs.getMinTurningCircle(), rhs.getMinTurningCircle()))
           && (lhs.getSources() == rhs.getSources())
           && (fuzzyFloatEqualT<7>(lhs.getXyCorrelation(), rhs.getXyCorrelation()))
           && (fuzzyFloatEqualT<7>(lhs.getXzCorrelation(), rhs.getXzCorrelation()))
           && (fuzzyFloatEqualT<7>(lhs.getYzCorrelation(), rhs.getYzCorrelation()));
}

//==============================================================================

bool operator!=(const VehicleState& lhs, const VehicleState& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

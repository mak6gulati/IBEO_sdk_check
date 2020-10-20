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
//!\date Jan 18, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2808.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

VehicleState2808::VehicleState2808() : SpecializedDataContainer() {}

//==============================================================================

VehicleState2808::~VehicleState2808() {}

//==============================================================================

PositionWgs84 VehicleState2808::getReferencePoint() const
{
    PositionWgs84 out;

    if ((!std::isnan(m_latitude)) && (!std::isnan(m_longitude)))
    {
        out.setLatitudeInDeg(m_latitude);
        out.setLongitudeInDeg(m_longitude);
    }
    else
    {
        out.setLatitudeInDeg(0);
        out.setLongitudeInDeg(0);
    }
    out.setAltitudeInMeterMSL(static_cast<double>(m_altitude));
    out.setCourseAngleInDeg(0);

    return out;
}

//==============================================================================

bool operator==(const VehicleState2808& lhs, const VehicleState2808& rhs)
{
    return (lhs.getMicroseconds() == rhs.getMicroseconds()) && (lhs.getTimestamp() == rhs.getTimestamp())
           && (lhs.getSources() == rhs.getSources()) && (lhs.getBlindPredictionAge() == rhs.getBlindPredictionAge())
           && (fuzzyDoubleEqualT<7>(lhs.getLatitude(), rhs.getLatitude()))
           && (fuzzyFloatEqualT<7>(lhs.getLatitudeSigma(), rhs.getLatitudeSigma()))
           && (fuzzyDoubleEqualT<7>(lhs.getLongitude(), rhs.getLongitude()))
           && (fuzzyFloatEqualT<7>(lhs.getLongitudeSigma(), rhs.getLongitudeSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getAltitude(), rhs.getAltitude()))
           && (fuzzyFloatEqualT<7>(lhs.getAltitudeSigma(), rhs.getAltitudeSigma()))
           && (fuzzyDoubleEqualT<7>(lhs.getXPosition(), rhs.getXPosition()))
           && (fuzzyFloatEqualT<7>(lhs.getXPositionSigma(), rhs.getXPositionSigma()))
           && (fuzzyDoubleEqualT<7>(lhs.getYPosition(), rhs.getYPosition()))
           && (fuzzyFloatEqualT<7>(lhs.getYPositionSigma(), rhs.getYPositionSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getZPosition(), rhs.getZPosition()))
           && (fuzzyFloatEqualT<7>(lhs.getZPositionSigma(), rhs.getZPositionSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getXyCorrelation(), rhs.getXyCorrelation()))
           && (fuzzyFloatEqualT<7>(lhs.getXzCorrelation(), rhs.getXzCorrelation()))
           && (fuzzyFloatEqualT<7>(lhs.getYzCorrelation(), rhs.getYzCorrelation()))
           && (fuzzyFloatEqualT<7>(lhs.getCourseAngle(), rhs.getCourseAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getCourseAngleSigma(), rhs.getCourseAngleSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getHeadingAngle(), rhs.getHeadingAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getHeadingAngleSigma(), rhs.getHeadingAngleSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getVehiclePitchAngle(), rhs.getVehiclePitchAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getVehiclePitchAngleSigma(), rhs.getVehiclePitchAngleSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getVehicleRollAngle(), rhs.getVehicleRollAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getVehicleRollAngleSigma(), rhs.getVehicleRollAngleSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getLongitudinalVelocity(), rhs.getLongitudinalVelocity()))
           && (fuzzyFloatEqualT<7>(lhs.getLongitudinalVelocitySigma(), rhs.getLongitudinalVelocitySigma()))
           && (fuzzyFloatEqualT<7>(lhs.getYawRate(), rhs.getYawRate()))
           && (fuzzyFloatEqualT<7>(lhs.getYawRateSigma(), rhs.getYawRateSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getLongitudinalAcceleration(), rhs.getLongitudinalAcceleration()))
           && (fuzzyFloatEqualT<7>(lhs.getLongitudinalAccelarationSigma(), rhs.getLongitudinalAccelarationSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getCrossAcceleration(), rhs.getCrossAcceleration()))
           && (fuzzyFloatEqualT<7>(lhs.getCrossAccelerationSigma(), rhs.getCrossAccelerationSigma()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerAngle(), rhs.getSteerAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getSteeringWheelAngle(), rhs.getSteeringWheelAngle()))
           && (fuzzyFloatEqualT<7>(lhs.getVehicleWidth(), rhs.getVehicleWidth()))
           && (fuzzyFloatEqualT<7>(lhs.getMinTurningCircle(), rhs.getMinTurningCircle()))
           && (fuzzyFloatEqualT<7>(lhs.getVehicleFrontToFrontAxle(), rhs.getVehicleFrontToFrontAxle()))
           && (fuzzyFloatEqualT<7>(lhs.getFrontAxleToRearAxle(), rhs.getFrontAxleToRearAxle()))
           && (fuzzyFloatEqualT<7>(lhs.getRearAxleToVehicleRear(), rhs.getRearAxleToVehicleRear()))
           && (fuzzyFloatEqualT<7>(lhs.getRearAxleToOrigin(), rhs.getRearAxleToOrigin()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff0(), rhs.getSteerRatioCoeff0()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff1(), rhs.getSteerRatioCoeff1()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff2(), rhs.getSteerRatioCoeff2()))
           && (fuzzyFloatEqualT<7>(lhs.getSteerRatioCoeff3(), rhs.getSteerRatioCoeff3()));
}

//==============================================================================

bool operator!=(const VehicleState2808& lhs, const VehicleState2808& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

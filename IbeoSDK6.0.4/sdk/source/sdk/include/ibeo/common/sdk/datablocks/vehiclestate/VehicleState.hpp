//==============================================================================
//!\file
//!\verbatim
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date 	11.08.2017
//!
//!\endverbatim
//! VehicleStateContainer
//!\brief Generalized ContainerClass for VehicleState
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/PositionWgs84.hpp>

#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/Math.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! This container holds the current state of the vehicle.
//!
//! Special data types:
//! \ref ibeo::common::sdk::VehicleState2805
//! \ref ibeo::common::sdk::VehicleState2806
//! \ref ibeo::common::sdk::VehicleState2807
//! \ref ibeo::common::sdk::VehicleState2808
class VehicleState : public DataContainerBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;

public:
    constexpr static const char* const containerType{"ibeo.sdk.generalcontainer.vehiclestate"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    VehicleState(DataTypeId::DataType importerType = DataTypeId::DataType_Unknown);
    virtual ~VehicleState() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public: // getter
    uint32_t getMicroseconds() const { return m_microseconds; }
    const NTPTime& getTimestamp() const { return m_timestamp; }
    const NTPTime& getTimestamp(bool& ok) const
    {
        ok = !m_timestamp.is_not_a_date_time();
        return m_timestamp;
    }
    uint16_t getSources() const { return m_sources; }
    uint16_t getBlindPredictionAge() const { return m_blindPredictionAge; }

    double getLongitudeOfOrigin() const { return m_longitudeOfOrigin; }
    double getLongitudeOfOrigin(bool& ok) const
    {
        ok = !std::isnan(m_longitudeOfOrigin);
        return m_longitudeOfOrigin;
    }
    double getLatitudeOfOrigin() const { return m_latitudeOfOrigin; }
    double getLatitudeOfOrigin(bool& ok) const
    {
        ok = !std::isnan(m_latitudeOfOrigin);
        return m_latitudeOfOrigin;
    }
    float getAltitudeOfOrigin() const { return m_altitudeOfOrigin; }
    float getAltitudeOfOrigin(bool& ok) const
    {
        ok = !std::isnan(m_altitudeOfOrigin);
        return m_altitudeOfOrigin;
    }
    float getLongitudeOfOriginSigma() const { return m_longitudeOfOriginSigma; }
    float getLongitudeOfOriginSigma(bool& ok) const
    {
        ok = !std::isnan(m_longitudeOfOriginSigma);
        return m_longitudeOfOriginSigma;
    }
    float getLatitudeOfOriginSigma() const { return m_latitudeOfOriginSigma; }
    float getLatitudeOfOriginSigma(bool& ok) const
    {
        ok = !std::isnan(m_latitudeOfOriginSigma);
        return m_latitudeOfOriginSigma;
    }
    float getAltitudeOfOriginSigma() const { return m_altitudeSigmaOfOrigin; }
    float getAltitudeOfOriginSigma(bool& ok) const
    {
        ok = !std::isnan(m_altitudeSigmaOfOrigin);
        return m_altitudeSigmaOfOrigin;
    }

    double getRelativeXPosition() const { return m_relativeXPosition; }
    double getRelativeXPosition(bool& ok) const
    {
        ok = !std::isnan(m_relativeXPosition);
        return m_relativeXPosition;
    }
    double getRelativeYPosition() const { return m_relativeYPosition; }
    double getRelativeYPosition(bool& ok) const
    {
        ok = !std::isnan(m_relativeYPosition);
        return m_relativeYPosition;
    }
    float getRelativeZPosition() const { return m_relativeZPosition; }
    float getRelativeZPosition(bool& ok) const
    {
        ok = !std::isnan(m_relativeZPosition);
        return m_relativeZPosition;
    }
    float getRelativeXPositionSigma() const { return m_relativeXPositionSigma; }
    float getRelativeXPositionSigma(bool& ok) const
    {
        ok = !std::isnan(m_relativeXPositionSigma);
        return m_relativeXPositionSigma;
    }
    float getRelativeYPositionSigma() const { return m_relativeYPositionSigma; }
    float getRelativeYPositionSigma(bool& ok) const
    {
        ok = !std::isnan(m_relativeYPositionSigma);
        return m_relativeYPositionSigma;
    }
    float getRelativeZPositionSigma() const { return m_relativeZPositionSigma; }
    float getRelativeZPositionSigma(bool& ok) const
    {
        ok = !std::isnan(m_relativeZPositionSigma);
        return m_relativeZPositionSigma;
    }

    float getXyCorrelation() const { return m_xyCorrelation; }
    float getXyCorrelation(bool& ok) const
    {
        ok = !std::isnan(m_xyCorrelation);
        return m_xyCorrelation;
    }
    float getXzCorrelation() const { return m_xzCorrelation; }
    float getXzCorrelation(bool& ok) const
    {
        ok = !std::isnan(m_xzCorrelation);
        return m_xzCorrelation;
    }
    float getYzCorrelation() const { return m_yzCorrelation; }
    float getYzCorrelation(bool& ok) const
    {
        ok = !std::isnan(m_yzCorrelation);
        return m_yzCorrelation;
    }

    float getCourseAngle() const { return m_courseAngle; }
    float getCourseAngle(bool& ok) const
    {
        ok = !std::isnan(m_courseAngle);
        return m_courseAngle;
    }
    float getCourseAngleSigma() const { return m_courseAngleSigma; }
    float getCourseAngleSigma(bool& ok) const
    {
        ok = !std::isnan(m_courseAngleSigma);
        return m_courseAngleSigma;
    }
    float getHeadingAngle() const { return m_headingAngle; }
    float getHeadingAngle(bool& ok) const
    {
        ok = !std::isnan(m_headingAngle);
        return m_headingAngle;
    }
    float getHeadingAngleSigma() const { return m_headingAngleSigma; }
    float getHeadingAngleSigma(bool& ok) const
    {
        ok = !std::isnan(m_headingAngleSigma);
        return m_headingAngleSigma;
    }

    float getVehiclePitchAngle() const { return m_vehiclePitchAngle; }
    float getVehiclePitchAngle(bool& ok) const
    {
        ok = !std::isnan(m_vehiclePitchAngle);
        return m_vehiclePitchAngle;
    }
    float getVehiclePitchAngleSigma() const { return m_vehiclePitchAngleSigma; }
    float getVehiclePitchAngleSigma(bool& ok) const
    {
        ok = !std::isnan(m_vehiclePitchAngleSigma);
        return m_vehiclePitchAngleSigma;
    }
    float getVehicleRollAngle() const { return m_vehicleRollAngle; }
    float getVehicleRollAngle(bool& ok) const
    {
        ok = !std::isnan(m_vehicleRollAngle);
        return m_vehicleRollAngle;
    }
    float getVehicleRollAngleSigma() const { return m_vehicleRollAngleSigma; }
    float getVehicleRollAngleSigma(bool& ok) const
    {
        ok = !std::isnan(m_vehicleRollAngleSigma);
        return m_vehicleRollAngleSigma;
    }

    float getLongitudinalVelocity() const { return m_longitudinalVelocity; }
    float getLongitudinalVelocity(bool& ok) const
    {
        ok = !std::isnan(m_longitudinalVelocity);
        return m_longitudinalVelocity;
    }
    float getLongitudinalVelocitySigma() const { return m_longitudinalVelocitySigma; }
    float getLongitudinalVelocitySigma(bool& ok) const
    {
        ok = !std::isnan(m_longitudinalVelocitySigma);
        return m_longitudinalVelocitySigma;
    }

    float getYawRate() const { return m_yawRate; }
    float getYawRate(bool& ok) const
    {
        ok = !std::isnan(m_yawRate);
        return m_yawRate;
    }
    float getYawRateSigma() const { return m_yawRateSigma; }
    float getYawRateSigma(bool& ok) const
    {
        ok = !std::isnan(m_yawRateSigma);
        return m_yawRateSigma;
    }

    float getLongitudinalAcceleration() const { return m_longitudinalAcceleration; }
    float getLongitudinalAcceleration(bool& ok) const
    {
        ok = !std::isnan(m_longitudinalAcceleration);
        return m_longitudinalAcceleration;
    }
    float getLongitudinalAccelerationSigma() const { return m_longitudinalAccelerationSigma; }
    float getLongitudinalAccelerationSigma(bool& ok) const
    {
        ok = !std::isnan(m_longitudinalAccelerationSigma);
        return m_longitudinalAccelerationSigma;
    }
    float getCrossAcceleration() const { return m_crossAcceleration; }
    float getCrossAcceleration(bool& ok) const
    {
        ok = !std::isnan(m_crossAcceleration);
        return m_crossAcceleration;
    }
    float getCrossAccelerationSigma() const { return m_crossAccelerationSigma; }
    float getCrossAccelerationSigma(bool& ok) const
    {
        ok = !std::isnan(m_crossAccelerationSigma);
        return m_crossAccelerationSigma;
    }

    float getSteerAngle() const { return m_steerAngle; }
    float getSteerAngle(bool& ok) const
    {
        ok = !std::isnan(m_steerAngle);
        return m_steerAngle;
    }
    float getSteeringWheelAngle() const { return m_steeringWheelAngle; }
    float getSteeringWheelAngle(bool& ok) const
    {
        ok = !std::isnan(m_steeringWheelAngle);
        return m_steeringWheelAngle;
    }

    float getVehicleWidth() const { return m_vehicleWidth; }
    float getVehicleWidth(bool& ok) const
    {
        ok = !std::isnan(m_vehicleWidth);
        return m_vehicleWidth;
    }
    float getMinTurningCircle() const { return m_minTurningCircle; }
    float getMinTurningCircle(bool& ok) const
    {
        ok = !std::isnan(m_minTurningCircle);
        return m_minTurningCircle;
    }

    float getVehicleFrontToFrontAxle() const { return m_vehicleFrontToFrontAxle; }
    float getVehicleFrontToFrontAxle(bool& ok) const
    {
        ok = !std::isnan(m_vehicleFrontToFrontAxle);
        return m_vehicleFrontToFrontAxle;
    }
    float getFrontAxleToRearAxle() const { return m_frontAxleToRearAxle; }
    float getFrontAxleToRearAxle(bool& ok) const
    {
        ok = !std::isnan(m_frontAxleToRearAxle);
        return m_frontAxleToRearAxle;
    }
    float getRearAxleToVehicleRear() const { return m_rearAxleToVehicleRear; }
    float getRearAxleToVehicleRear(bool& ok) const
    {
        ok = !std::isnan(m_rearAxleToVehicleRear);
        return m_rearAxleToVehicleRear;
    }
    float getRearAxleToOrigin() const { return m_rearAxleToOrigin; }
    float getRearAxleToOrigin(bool& ok) const
    {
        ok = !std::isnan(m_rearAxleToOrigin);
        return m_rearAxleToOrigin;
    }
    float getSteerRatioCoeff0() const { return m_steerRatioCoeff0; }
    float getSteerRatioCoeff0(bool& ok) const
    {
        ok = !std::isnan(m_steerRatioCoeff0);
        return m_steerRatioCoeff0;
    }
    float getSteerRatioCoeff1() const { return m_steerRatioCoeff1; }
    float getSteerRatioCoeff1(bool& ok) const
    {
        ok = !std::isnan(m_steerRatioCoeff1);
        return m_steerRatioCoeff1;
    }
    float getSteerRatioCoeff2() const { return m_steerRatioCoeff2; }
    float getSteerRatioCoeff2(bool& ok) const
    {
        ok = !std::isnan(m_steerRatioCoeff2);
        return m_steerRatioCoeff2;
    }
    float getSteerRatioCoeff3() const { return m_steerRatioCoeff3; }
    float getSteerRatioCoeff3(bool& ok) const
    {
        ok = !std::isnan(m_steerRatioCoeff3);
        return m_steerRatioCoeff3;
    }

public: // setter
    void setMicroseconds(const uint32_t microseconds) { m_microseconds = microseconds; }
    void setTimestamp(const NTPTime& timestamp) { m_timestamp = timestamp; }
    void setSources(const uint16_t sources) { m_sources = sources; }
    void setBlindPredictionAge(const uint16_t blindPredictionAge) { m_blindPredictionAge = blindPredictionAge; }

    void setLongitudeOfOrigin(const double& longitude) { m_longitudeOfOrigin = longitude; }
    void setLongitudeOfOriginSigma(const float longitudeSigma) { m_longitudeOfOriginSigma = longitudeSigma; }
    void setLatitudeOfOrigin(const double& latitude) { m_latitudeOfOrigin = latitude; }
    void setLatitudeOfOriginSigma(const float latitudeSigma) { m_latitudeOfOriginSigma = latitudeSigma; }
    void setAltitudeOfOrigin(const float altitude) { m_altitudeOfOrigin = altitude; }
    void setAltitudeOfOriginSigma(const float altitudeSigma) { m_altitudeSigmaOfOrigin = altitudeSigma; }

    void setRelativeXPosition(const double xPosition) { m_relativeXPosition = xPosition; }
    void setRelativeYPosition(const double yPosition) { m_relativeYPosition = yPosition; }
    void setRelativeZPosition(const float zPosition) { m_relativeZPosition = zPosition; }
    void setRelativeXPositionSigma(const float xPostitionSigma) { m_relativeXPositionSigma = xPostitionSigma; }
    void setRelativeYPositionSigma(const float yPostitionSigma) { m_relativeYPositionSigma = yPostitionSigma; }
    void setRelativeZPositionSigma(const float zPositionSigma) { m_relativeZPositionSigma = zPositionSigma; }

    void setXyCorrelation(const float xyCorrelation) { m_xyCorrelation = xyCorrelation; }
    void setXzCorrelation(const float xzCorrelation) { m_xzCorrelation = xzCorrelation; }
    void setYzCorrelation(const float yzCorrelation) { m_yzCorrelation = yzCorrelation; }

    void setCourseAngle(const float courseAngle) { m_courseAngle = courseAngle; }
    void setCourseAngleSigma(const float courseAngleSigma) { m_courseAngleSigma = courseAngleSigma; }
    void setHeadingAngle(const float headingAngle) { m_headingAngle = headingAngle; }
    void setHeadingAngleSigma(const float headingAngleSigma) { m_headingAngleSigma = headingAngleSigma; }

    void setVehiclePitchAngle(const float vehiclePitchAngle) { m_vehiclePitchAngle = vehiclePitchAngle; }
    void setVehiclePitchAngleSigma(const float vehiclePitchAngleSigma)
    {
        m_vehiclePitchAngleSigma = vehiclePitchAngleSigma;
    }
    void setVehicleRollAngle(const float vehicleRollingAngle) { m_vehicleRollAngle = vehicleRollingAngle; }
    void setVehicleRollAngleSigma(const float vehicleRollingAngleSigma)
    {
        m_vehicleRollAngleSigma = vehicleRollingAngleSigma;
    }

    void setLongitudinalVelocity(const float vehicleVelocity) { m_longitudinalVelocity = vehicleVelocity; }
    void setLongitudinalVelocitySigma(const float vehicleVelocitySigma)
    {
        m_longitudinalVelocitySigma = vehicleVelocitySigma;
    }

    void setYawRate(const float yawRate) { m_yawRate = yawRate; }
    void setYawRateSigma(const float yawRateSigma) { m_yawRateSigma = yawRateSigma; }

    void setLongitudinalAcceleration(const float longitudinalAcceleration)
    {
        m_longitudinalAcceleration = longitudinalAcceleration;
    }
    void setLongitudinalAccelerationSigma(const float longitudinalAccelerationSigma)
    {
        m_longitudinalAccelerationSigma = longitudinalAccelerationSigma;
    }
    void setCrossAcceleration(const float crossAcceleration) { m_crossAcceleration = crossAcceleration; }
    void setCrossAccelerationSigma(const float crossAccelerationSigma)
    {
        m_crossAccelerationSigma = crossAccelerationSigma;
    }

    void setSteeringWheelAngle(const float steeringWheelAngle) { m_steeringWheelAngle = steeringWheelAngle; }
    void setSteerAngle(const float steerAngle) { m_steerAngle = steerAngle; }

    void setVehicleWidth(const float vehicleWidth) { m_vehicleWidth = vehicleWidth; }
    void setMinTurningCircle(const float minTurningCircle) { m_minTurningCircle = minTurningCircle; }

    void setVehicleFrontToFrontAxle(const float vehicleFrontToFrontAxle)
    {
        m_vehicleFrontToFrontAxle = vehicleFrontToFrontAxle;
    }
    void setFrontAxleToRearAxle(const float frontAxleToRearAxle) { m_frontAxleToRearAxle = frontAxleToRearAxle; }
    void setRearAxleToVehicleRear(const float rearAxleToVehicleRear)
    {
        m_rearAxleToVehicleRear = rearAxleToVehicleRear;
    }
    void setRearAxleToOrigin(const float rearAxleToOrigin) { m_rearAxleToOrigin = rearAxleToOrigin; }
    void setSteerRatioCoeff0(const float steerRatioCoeff0) { m_steerRatioCoeff0 = steerRatioCoeff0; }
    void setSteerRatioCoeff1(const float steerRatioCoeff1) { m_steerRatioCoeff1 = steerRatioCoeff1; }
    void setSteerRatioCoeff2(const float steerRatioCoeff2) { m_steerRatioCoeff2 = steerRatioCoeff2; }
    void setSteerRatioCoeff3(const float steerRatioCoeff3) { m_steerRatioCoeff3 = steerRatioCoeff3; }

public:
    //========================================
    //!\brief Returns the reference point as WGS84 type. If reference point is not set, lat and lon will be 0.
    //----------------------------------------
    PositionWgs84 getReferencePoint() const;

protected: //members
    uint32_t m_microseconds{0}; //!< microseconds since startup.
    NTPTime m_timestamp{0}; //!< timestamp of this data
    uint16_t m_sources{0};
    uint16_t m_blindPredictionAge{0};

    double m_longitudeOfOrigin{NaN_double}; //!< initial global Position(origin)[deg]
    float m_longitudeOfOriginSigma{NaN}; //!< [deg]
    double m_latitudeOfOrigin{NaN_double}; //!< initial global Position(origin)[deg]
    float m_latitudeOfOriginSigma{NaN}; //!< standard deviation [deg]
    float m_altitudeOfOrigin{NaN}; //!< initial global Position(origin)[m]
    float m_altitudeSigmaOfOrigin{NaN}; //!< [m]

    double m_relativeXPosition{NaN_double}; //!< Absolute X Position from origin [m]
    float m_relativeXPositionSigma{NaN}; //!< standard deviation [m]
    double m_relativeYPosition{NaN_double}; //!< Absolute X Position from origin [m]
    float m_relativeYPositionSigma{NaN}; //!< standard deviation [m]
    float m_relativeZPosition{NaN}; //!< Absolute X Position from origin [m]
    float m_relativeZPositionSigma{NaN}; //!< standard deviation [m]

    float m_xyCorrelation{NaN}; //!< standard deviation [m]
    float m_xzCorrelation{NaN}; //!< standard deviation [m]
    float m_yzCorrelation{NaN}; //!< standard deviation [m]

    float m_courseAngle{NaN}; //!< Absolute orientation at time timeStamp | [rad]
    float m_courseAngleSigma{NaN}; //!< [rad]
    float m_headingAngle{NaN}; //!< heading angle [rad] - is different to course angle
    float m_headingAngleSigma{NaN}; //!< standard deviation [rad]

    float m_vehiclePitchAngle{NaN}; //!< current vehicle pitch angle [rad]
    float m_vehiclePitchAngleSigma{NaN}; //!< standard deviation [rad]
    float m_vehicleRollAngle{NaN}; //!< current vehicle roll angle [rad]
    float m_vehicleRollAngleSigma{NaN}; //!< standard deviation [rad]

    float m_longitudinalVelocity{NaN}; //!< Current longitudinal velocity of the vehicle | [m/s]
    float m_longitudinalVelocitySigma{NaN}; //!< standard deviation longitudinal velocity of vehicle [m/s]

    float m_yawRate{NaN}; //!< Difference in Heading during Timediff [rad/s]
    float m_yawRateSigma{NaN}; //!< [rad/s]

    float m_longitudinalAcceleration{NaN}; //!< Current longitudinal acceleration of the vehicle | [m/s^2]
    float m_longitudinalAccelerationSigma{NaN}; //!< standard deviation longitudinal acceleration of vehicle [m/s²]
    float m_crossAcceleration{NaN}; //!< current crossAcceleration of vehicle [m/s²]
    float m_crossAccelerationSigma{NaN}; //!< standard deviation crossAcceleration of vehicle [m/s²]

    float m_steerAngle{NaN}; //!< [rad]
    float m_steeringWheelAngle{NaN}; //!< steering wheel angle [rad]

    float m_vehicleWidth{NaN}; //!< Vehicle width [m]
    float m_minTurningCircle{NaN};

    float m_vehicleFrontToFrontAxle{NaN}; //!< Distance: vehicle's front axle to vehicle's front [m]
    float m_frontAxleToRearAxle{NaN}; //!< Distance: vehicle's rear axle to vehicle's front axle [m]
    float m_rearAxleToVehicleRear{NaN}; //!< Distance: vehicle's rear axle to vehicle's rear [m]
    float m_rearAxleToOrigin{NaN}; //!< Distance: vehicle's rear axle to origin [m]
    float m_steerRatioCoeff0{NaN}; //!< s_3*x^3 + s_2*x^2 + s-2*x^1 + s_0
    float m_steerRatioCoeff1{NaN}; //!< s_3*x^3 + s_2*x^2 + s-2*x^1 + s_0
    float m_steerRatioCoeff2{NaN}; //!< s_3*x^3 + s_2*x^2 + s-2*x^1 + s_0
    float m_steerRatioCoeff3{NaN}; //!< s_3*x^3 + s_2*x^2 + s-2*x^1 + s_0
}; // VehicleState

//==============================================================================

bool operator==(const VehicleState& lhs, const VehicleState& rhs);
bool operator!=(const VehicleState& lhs, const VehicleState& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

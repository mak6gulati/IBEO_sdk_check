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
//!\date Mar 23, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/Timestamp.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImuSourceIn9001.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImuInsQualityIn9001.hpp>

#include <array>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief GpsImu
//!
//! This data type contains unprocessed position and motion data provided by a connected GPS/IMU device, e.g. XSens MTi-G.
//!
//! General data type: \ref ibeo::common::sdk::GpsImu
class GpsImu9001 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    static const uint8_t nbOfReserved = 16;

public:
    using ReservedArray = std::array<uint8_t, nbOfReserved>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.gpsimu9001"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    GpsImu9001();
    ~GpsImu9001() override = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    //========================================
    //!\brief Get the latitude [rad].
    //----------------------------------------
    double getLatitudeInRad() const { return m_latitudeInRad; }

    //========================================
    //!\brief Get the latitude uncertainty [m].
    //----------------------------------------
    double getLatitudeSigmaInMeter() const { return m_latitudeSigmaInMeter; }

    //========================================
    //!\brief Get the longitude [rad].
    //----------------------------------------
    double getLongitudeInRad() const { return m_longitudeInRad; }

    //========================================
    //!\brief Get the longitude uncertainty [m].
    //----------------------------------------
    double getLongitudeSigmaInMeter() const { return m_longitudeSigmaInMeter; }

    //========================================
    //!\brief Get the altitude uncertainty [m].
    //----------------------------------------
    double getAltitudeInMeter() const { return m_altitudeInMeter; }

    //========================================
    //!\brief Get the altitude uncertainty [m].
    //----------------------------------------
    double getAltitudeSigmaInMeter() const { return m_altitudeSigmaInMeter; }

    //========================================
    //!\brief Get the course angle [rad].
    //!
    //! Relative to North. Interval: [0;2*Pi] The course angle is the angle the
    //! vehicle is traveling to. If youdrift, it is different to the yaw angle,
    //! which is the direction of the vehicle is heading/looking at.
    //! example 0.0 = North, pi/2 = West
    //----------------------------------------
    double getCourseAngleInRad() const { return m_courseAngleInRad; }

    //========================================
    //!\brief Get the course angle uncertainty [rad].
    //----------------------------------------
    double getCourseAngleSigmaInRad() const { return m_courseAngleSigmaInRad; }

    //========================================
    //!\brief
    //! Yaw Angle in [rad], Interval [0;2*Pi]. The yaw angle is the angle the vehicle
    //! is heading/looking at. If you drift, it is different to the course angle,
    //! which is the direction of travelling or the track angle.
    //! example 0.0 = North, pi/2 = West
    //----------------------------------------
    double getYawAngleInRad() const { return m_yawAngleInRad; }

    //========================================
    //!\brief Set the yaw angle uncertainty [rad].
    //----------------------------------------
    double getYawAngleSigmaInRad() const { return m_yawAngleSigmaInRad; }

    //========================================
    //!\brief Get the pitch angle uncertainty [rad].
    //----------------------------------------
    double getPitchAngleInRad() const { return m_pitchAngleInRad; }

    //========================================
    //!\brief Get the pitch angle uncertainty [rad].
    //----------------------------------------
    double getPitchAngleSigmaInRad() const { return m_pitchAngleSigmaInRad; }

    //========================================
    //!\brief Get the roll angle [rad].
    //----------------------------------------
    double getRollAngleInRad() const { return m_rollAngleInRad; }

    //========================================
    //!\brief Get the roll angle uncertainty [rad].
    //----------------------------------------
    double getRollAngleSigmaInRad() const { return m_rollAngleSigmaInRad; }

    //========================================
    //!\brief Get the cross angle [m/s^2].
    //----------------------------------------
    double getCrossAccelerationInMeterPerSecond2() const { return m_crossAccelerationInMeterPerSecond2; }

    //========================================
    //!\brief Get the cross angle uncertainty [m/s^2].
    //----------------------------------------
    double getCrossAccelerationSigmaInMeterPerSecond2() const { return m_crossAccelerationSigmaInMeterPerSecond2; }

    //========================================
    //!\brief Get the longitudinal angle  [m/s^2].
    //----------------------------------------
    double getLongitudinalAccelerationInMeterPerSecond2() const { return m_longitudinalAccelerationInMeterPerSecond2; }

    //========================================
    //!\brief Get the longitudinal angle uncertainty [m/s^2].
    //----------------------------------------
    double getLongitudinalAccelerationSigmaInMeterPerSecond2() const
    {
        return m_longitudinalAccelerationSigmaInMeterPerSecond2;
    }

    //========================================
    //!\brief Get the vertical angle [m/s^2].
    //----------------------------------------
    double getVerticalAccelerationInMeterPerSecond2() const { return m_verticalAccelerationInMeterPerSecond2; }

    //========================================
    //!\brief Get the vertical angle uncertainty [m/s^2].
    //----------------------------------------
    double getVerticalAccelerationSigmaInMeterPerSecond2() const
    {
        return m_verticalAccelerationSigmaInMeterPerSecond2;
    }

    //========================================
    //!\brief Get the velocity north [m/s].
    //----------------------------------------
    double getVelocityNorthInMeterPerSecond() const { return m_velocityNorthInMeterPerSecond; }

    //========================================
    //!\brief Get the velocity north uncertainty [m/s].
    //----------------------------------------
    double getVelocityNorthSigmaInMeterPerSecond() const { return m_velocityNorthSigmaInMeterPerSecond; }

    //========================================
    //!\brief Get the velocity west [m/s].
    //----------------------------------------
    double getVelocityWestInMeterPerSecond() const { return m_velocityWestInMeterPerSecond; }

    //========================================
    //!\brief Get the velocity west uncertainty [m/s].
    //----------------------------------------
    double getVelocityWestSigmaInMeterPerSecond() const { return m_velocityWestSigmaInMeterPerSecond; }

    //========================================
    //!\brief Get the velocity up [m/s].
    //----------------------------------------
    double getVelocityUpInMeterPerSecond() const { return m_velocityUpInMeterPerSecond; }

    //========================================
    //!\brief Get the velocity up uncertainty [m/s].
    //----------------------------------------
    double getVelocityUpSigmaInMeterPerSecond() const { return m_velocityUpSigmaInMeterPerSecond; }

    //========================================
    //!\brief Get the velocity in x direction [m/s].
    //----------------------------------------
    double getVelocityXInMeterPerSecond() const { return m_velocityXInMeterPerSecond; }

    //========================================
    //!\brief Get the velocity uncertainty in x direction [m/s].
    //----------------------------------------
    double getVelocityXSigmaInMeterPerSecond() const { return m_velocityXSigmaInMeterPerSecond; }

    //========================================
    //!\brief Get the velocity in y direction [m/s].
    //----------------------------------------
    double getVelocityYInMeterPerSecond() const { return m_velocityYInMeterPerSecond; }

    //========================================
    //!\brief Get the velocity uncertainty in y direction [m/s].
    //----------------------------------------
    double getVelocityYSigmaInMeterPerSecond() const { return m_velocityYSigmaInMeterPerSecond; }

    //========================================
    //!\brief Get the velocity in z direction [m/s].
    //----------------------------------------
    double getVelocityZInMeterPerSecond() const { return m_velocityZInMeterPerSecond; }

    //========================================
    //!\brief Get the velocity uncertainty in z direction [m/s].
    //----------------------------------------
    double getVelocityZSigmaInMeterPerSecond() const { return m_velocityZSigmaInMeterPerSecond; }

    //========================================
    //!\brief Get the roll rate [rad/s].
    //----------------------------------------
    double getYawRateInRadPerSecond() const { return m_yawRateInRadPerSecond; }

    //========================================
    //!\brief Get the roll rate uncertainty [rad/s].
    //----------------------------------------
    double getYawRateSigmaInRadPerSecond() const { return m_yawRateSigmaInRadPerSecond; }

    //========================================
    //!\brief Get the yaw rate [rad/s].
    //----------------------------------------
    double getPitchRateInRadPerSecond() const { return m_pitchRateInRadPerSecond; }

    //========================================
    //!\brief Get the yaw rate uncertainty [rad/s].
    //----------------------------------------
    double getPitchRateSigmaInRadPerSecond() const { return m_pitchRateSigmaInRadPerSecond; }

    //========================================
    //!\brief Get the pitch rate [rad/s].
    //----------------------------------------
    double getRollRateInRadPerSecond() const { return m_rollRateInRadPerSecond; }

    //========================================
    //!\brief Get the pitch rate uncertainty [rad/s].
    //----------------------------------------
    double getRollRateSigmaInRadPerSecond() const { return m_rollRateSigmaInRadPerSecond; }

    //========================================
    //!\brief Get the GPS status [none] (tbd).
    //----------------------------------------
    double getGpsStatus() const { return m_gpsStatus; }

    //========================================
    //!\brief Get the number of satellites.
    //----------------------------------------
    uint8_t getNoOfSatellites() const { return m_noOfSatellites; }

    //==================================================
    //!\brief Get the dilution of precision in x direction.
    //----------------------------------------
    double getGpsDilutionOfPrecisionX() const { return m_gpsDilutionOfPrecisionX; }

    //========================================
    //!\brief Get the dilution of precision in y direction.
    //----------------------------------------
    double getGpsDilutionOfPrecisionY() const { return m_gpsDilutionOfPrecisionY; }

    //========================================
    //!\brief Get the dilution of precision in z direction.
    //----------------------------------------
    double getGpsDilutionOfPrecisionZ() const { return m_gpsDilutionOfPrecisionZ; }

    //========================================
    //!\brief Get the dilution of precision in vertical direction.
    //----------------------------------------
    double getGpsDilutionOfPrecisionVertical() const { return m_gpsDilutionOfPrecisionVertical; }

    //========================================
    //!\brief Get the dilution of precision in position.
    //----------------------------------------
    double getGpsDilutionOfPrecisionPosition() const { return m_gpsDilutionOfPrecisionPosition; }

    //========================================
    //!\brief Get timestamp.
    //----------------------------------------
    const Timestamp& getTimestamp() const { return m_timestamp; }

    //========================================
    //!\brief Get the source of the GPS/IMU measurements.
    //----------------------------------------
    const GpsImuSourceIn9001& getSource() const { return m_source; }

    //========================================
    //!\brief Get the quality flag of the GPS/IMU measurements.
    //----------------------------------------
    const GpsImuInsQualityIn9001& getInsQuality() const { return m_insQuality; }

    uint8_t getReserved(const uint8_t idx) const { return m_reserved.at(idx); }
    const ReservedArray& getReserved() const { return m_reserved; }

public:
    //========================================
    //!\brief Set the latitude [rad].
    //----------------------------------------
    void setLatitudeInRad(const double latitude) { m_latitudeInRad = latitude; }

    //========================================
    //!\brief Set the latitude uncertainty [m].
    //----------------------------------------
    void setLatitudeSigmaInMeter(const double latitudeSigma) { m_latitudeSigmaInMeter = latitudeSigma; }

    //========================================
    //!\brief Set the longitude [rad].
    //----------------------------------------
    void setLongitudeInRad(const double longitude) { m_longitudeInRad = longitude; }

    //========================================
    //!\brief Set the longitude uncertainty [m].
    //----------------------------------------
    void setLongitudeSigmaInMeter(const double longitudeSigma) { m_longitudeSigmaInMeter = longitudeSigma; }

    //========================================
    //!\brief Set the altitude uncertainty [m].
    //----------------------------------------
    void setAltitudeInMeter(const double altitude) { m_altitudeInMeter = altitude; }

    //========================================
    //!\brief Set the altitude uncertainty [m].
    //----------------------------------------
    void setAltitudeSigmaInMeter(const double altitudeSigma) { m_altitudeSigmaInMeter = altitudeSigma; }

    //========================================
    //!\brief Set the course angle [rad].
    //!
    //! Relative to North. Interval: [0;2*Pi] The course angle is the angle the
    //! vehicle is traveling to. If you drift, it is different to the yaw angle,
    //! which is the direction of the vehicle is heading/looking at.
    //! example 0.0 = North, pi/2 = West
    //----------------------------------------
    void setCourseAngleInRad(const double courseAngle) { m_courseAngleInRad = courseAngle; }

    //========================================
    //!\brief Set the course angle uncertainty [rad].
    //----------------------------------------
    void setCourseAngleSigmaInRad(const double courseAngleSigma) { m_courseAngleSigmaInRad = courseAngleSigma; }

    //========================================
    //!\brief Set the yaw Angle in [rad].
    //!
    //! Interval [0;2*Pi]. The yaw angle is the angle the
    //! vehicle is heading/looking at. If you drift, it is different to the
    //! course angle, which is the direction of travelling or the track angle.
    //! example 0.0 = North, pi/2 = West
    //----------------------------------------
    void setYawAngleInRad(const double yawAngle) { m_yawAngleInRad = yawAngle; }

    //========================================
    //!\brief Set the yaw angle uncertainty [rad].
    //----------------------------------------
    void setYawAngleSigmaInRad(const double yawAngleSigma) { m_yawAngleSigmaInRad = yawAngleSigma; }

    //========================================
    //!\brief Set the pitch angle uncertainty [rad].
    //----------------------------------------
    void setPitchAngleInRad(const double pitchAngle) { m_pitchAngleInRad = pitchAngle; }

    //========================================
    //!\brief Set the pitch angle uncertainty [rad].
    //----------------------------------------
    void setPitchAngleSigmaInRad(const double pitchAngleSigma) { m_pitchAngleSigmaInRad = pitchAngleSigma; }

    //========================================
    //!\brief Set the roll angle [rad].
    //----------------------------------------
    void setRollAngleInRad(const double rollAngle) { m_rollAngleInRad = rollAngle; }

    //========================================
    //!\brief Set the roll angle uncertainty [rad].
    //----------------------------------------
    void setRollAngleSigmaInRad(const double rollAngleSigma) { m_rollAngleSigmaInRad = rollAngleSigma; }

    //========================================
    //!\brief Set the cross angle [m/s^2].
    //----------------------------------------
    void setCrossAccelerationInMeterPerSecond2(const double crossAcceleration)
    {
        m_crossAccelerationInMeterPerSecond2 = crossAcceleration;
    }

    //========================================
    //!\brief Set the cross angle uncertainty [m/s^2].
    //----------------------------------------
    void setCrossAccelerationSigmaInMeterPerSecond2(const double crossAccSigma)
    {
        m_crossAccelerationSigmaInMeterPerSecond2 = crossAccSigma;
    }

    //========================================
    //!\brief Set the longitudinal angle  [m/s^2].
    //----------------------------------------
    void setLongitudinalAccelerationInMeterPerSecond2(const double longAcc)
    {
        m_longitudinalAccelerationInMeterPerSecond2 = longAcc;
    }

    //========================================
    //!\brief Set the longitudinal angle uncertainty [m/s^2].
    //----------------------------------------
    void setLongitudinalAccelerationSigmaInMeterPerSecond2(const double longAccSigma)
    {
        m_longitudinalAccelerationSigmaInMeterPerSecond2 = longAccSigma;
    }

    //========================================
    //!\brief Set the vertical angle [m/s^2].
    //----------------------------------------
    void setVerticalAccelerationInMeterPerSecond2(const double vertAcc)
    {
        m_verticalAccelerationInMeterPerSecond2 = vertAcc;
    }

    //========================================
    //!\brief Set the vertical angle uncertainty [m/s^2].
    //----------------------------------------
    void setVerticalAccelerationSigmaInMeterPerSecond2(const double vertAccSigma)
    {
        m_verticalAccelerationSigmaInMeterPerSecond2 = vertAccSigma;
    }

    //========================================
    //!\brief Set the velocity north [m/s].
    //----------------------------------------
    void setVelocityNorthInMeterPerSecond(const double velocityNorth)
    {
        m_velocityNorthInMeterPerSecond = velocityNorth;
    }

    //========================================
    //!\brief Set the velocity north uncertainty [m/s].
    //----------------------------------------
    void setVelocityNorthSigmaInMeterPerSecond(const double velocityNorthSigma)
    {
        m_velocityNorthSigmaInMeterPerSecond = velocityNorthSigma;
    }

    //========================================
    //!\brief Set the velocity west [m/s].
    //----------------------------------------
    void setVelocityWestInMeterPerSecond(const double velocityWest) { m_velocityWestInMeterPerSecond = velocityWest; }

    //========================================
    //!\brief Set the velocity west uncertainty [m/s].
    //----------------------------------------
    void setVelocityWestSigmaInMeterPerSecond(const double velocityWestSigma)
    {
        m_velocityWestSigmaInMeterPerSecond = velocityWestSigma;
    }

    //========================================
    //!\brief Set the velocity up [m/s].
    //----------------------------------------
    void setVelocityUpInMeterPerSecond(const double velocityUp) { m_velocityUpInMeterPerSecond = velocityUp; }

    //========================================
    //!\brief Set the velocity up uncertainty [m/s].
    //----------------------------------------
    void setVelocityUpSigmaInMeterPerSecond(const double velocityUpSigma)
    {
        m_velocityUpSigmaInMeterPerSecond = velocityUpSigma;
    }

    //========================================
    //!\brief Set the velocity in x direction [m/s].
    //----------------------------------------
    void setVelocityXInMeterPerSecond(const double velocityX) { m_velocityXInMeterPerSecond = velocityX; }

    //========================================
    //!\brief Set the velocity uncertainty in x direction [m/s].
    //----------------------------------------
    void setVelocityXSigmaInMeterPerSecond(const double velocityXSigma)
    {
        m_velocityXSigmaInMeterPerSecond = velocityXSigma;
    }

    //========================================
    //!\brief Set the velocity in y direction [m/s].
    //----------------------------------------
    void setVelocityYInMeterPerSecond(const double velocityY) { m_velocityYInMeterPerSecond = velocityY; }

    //========================================
    //!\brief Set the velocity uncertainty in y direction [m/s].
    //----------------------------------------
    void setVelocityYSigmaInMeterPerSecond(const double velocityYSigma)
    {
        m_velocityYSigmaInMeterPerSecond = velocityYSigma;
    }

    //========================================
    //!\brief Set the velocity in z direction [m/s].
    //----------------------------------------
    void setVelocityZInMeterPerSecond(const double velocityZ) { m_velocityZInMeterPerSecond = velocityZ; }

    //========================================
    //!\brief Set the velocity uncertainty in z direction [m/s].
    //----------------------------------------
    void setVelocityZSigmaInMeterPerSecond(const double velocityZSigma)
    {
        m_velocityZSigmaInMeterPerSecond = velocityZSigma;
    }

    //========================================
    //!\brief Set the roll rate [rad/s].
    //----------------------------------------
    void setRollRateInRadPerSecond(const double rollRate) { m_rollRateInRadPerSecond = rollRate; }

    //========================================
    //!\brief Set the roll rate uncertainty [rad/s].
    //----------------------------------------
    void setRollRateSigmaInRadPerSecond(const double rollRateSigma) { m_rollRateSigmaInRadPerSecond = rollRateSigma; }

    //========================================
    //!\brief Set the yaw rate [rad/s].
    //----------------------------------------
    void setYawRateInRadPerSecond(const double yawRate) { m_yawRateInRadPerSecond = yawRate; }

    //========================================
    //!\brief Set the yaw rate uncertainty [rad/s].
    //----------------------------------------
    void setYawRateSigmaInRadPerSecond(const double yawRateSigma) { m_yawRateSigmaInRadPerSecond = yawRateSigma; }

    //========================================
    //!\brief Set the pitch rate [rad/s].
    //----------------------------------------
    void setPitchRateInRadPerSecond(const double pitchRate) { m_pitchRateInRadPerSecond = pitchRate; }

    //========================================
    //!\brief Set the pitch rate uncertainty [rad/s].
    //----------------------------------------
    void setPitchRateSigmaInRadPerSecond(const double pitchRateSigma)
    {
        m_pitchRateSigmaInRadPerSecond = pitchRateSigma;
    }

    //========================================
    //!\brief Set the GPS status [none] (tbd).
    //----------------------------------------
    void setGpsStatus(const double gpsStatus) { m_gpsStatus = gpsStatus; }

    //========================================
    //!\brief Set the number of satellites.
    //----------------------------------------
    void setNoOfSatellites(const uint8_t noOfSatellites) { m_noOfSatellites = noOfSatellites; }

    //========================================
    //!\brief Set the dilution of precision in x direction.
    //----------------------------------------
    void setGpsDilutionOfPrecisionX(const double gpsDilutionOfPrecisionX)
    {
        m_gpsDilutionOfPrecisionX = gpsDilutionOfPrecisionX;
    }

    //========================================
    //!\brief Set the dilution of precision in y direction.
    //----------------------------------------
    void setGpsDilutionOfPrecisionY(const double gpsDilutionOfPrecisionY)
    {
        m_gpsDilutionOfPrecisionY = gpsDilutionOfPrecisionY;
    }

    //========================================
    //!\brief Set the dilution of precision in z direction.
    //----------------------------------------
    void setGpsDilutionOfPrecisionZ(const double gpsDilutionOfPrecisionZ)
    {
        m_gpsDilutionOfPrecisionZ = gpsDilutionOfPrecisionZ;
    }

    //========================================
    //!\brief Set the dilution of precision in vertical direction.
    //----------------------------------------
    void setGpsDilutionOfPrecisionVertical(const double gpsDilutionOfPrecisionVertical)
    {
        m_gpsDilutionOfPrecisionVertical = gpsDilutionOfPrecisionVertical;
    }

    //========================================
    //!\brief Set the dilution of precision in position.
    //----------------------------------------
    void setGpsDilutionOfPrecisionPosition(const double gpsDilutionOfPrecisionPosition)
    {
        m_gpsDilutionOfPrecisionPosition = gpsDilutionOfPrecisionPosition;
    }

    //========================================
    //!\brief Set the timestamp.
    //----------------------------------------
    void setTimestamp(const Timestamp& timestamp) { m_timestamp = timestamp; }

    //========================================
    //!\brief Set the source of the GPS/IMU measurements.
    //----------------------------------------
    void setSource(const GpsImuSourceIn9001 source) { m_source = source; }

    //========================================
    //!\brief Get the quality flag of the GPS/IMU measurements.
    //----------------------------------------
    void setInsQuality(const GpsImuInsQualityIn9001 insQuality) { m_insQuality = insQuality; }

protected:
    double m_latitudeInRad{NaN_double}; //!< [rad]
    double m_latitudeSigmaInMeter{NaN_double}; //!< [m]
    double m_longitudeInRad{NaN_double}; //!< [rad]
    double m_longitudeSigmaInMeter{NaN_double}; //!< [m]
    double m_altitudeInMeter{NaN_double}; //!< [m]
    double m_altitudeSigmaInMeter{NaN_double}; //!< [m]
    double m_courseAngleInRad{NaN_double}; //!< [rad]
    double m_courseAngleSigmaInRad{NaN_double}; //!< [rad]
    double m_yawAngleInRad{NaN_double}; //!< [rad]
    double m_yawAngleSigmaInRad{NaN_double}; //!< [rad]
    double m_pitchAngleInRad{NaN_double}; //!< [rad]
    double m_pitchAngleSigmaInRad{NaN_double}; //!< [rad]
    double m_rollAngleInRad{NaN_double}; //!< [rad]
    double m_rollAngleSigmaInRad{NaN_double}; //!< [rad]

    double m_crossAccelerationInMeterPerSecond2{NaN_double}; //!< [m/s^2]
    double m_crossAccelerationSigmaInMeterPerSecond2{NaN_double}; //!< [m/s^2]
    double m_longitudinalAccelerationInMeterPerSecond2{NaN_double}; //!< [m/s^2]
    double m_longitudinalAccelerationSigmaInMeterPerSecond2{NaN_double}; //!< [m/s^2]
    double m_verticalAccelerationInMeterPerSecond2{NaN_double}; //!< [m/s^2]
    double m_verticalAccelerationSigmaInMeterPerSecond2{NaN_double}; //!< [m/s^2]
    double m_velocityNorthInMeterPerSecond{NaN_double}; //!< [m/s]
    double m_velocityNorthSigmaInMeterPerSecond{NaN_double}; //!< [m/s]
    double m_velocityWestInMeterPerSecond{NaN_double}; //!< [m/s]
    double m_velocityWestSigmaInMeterPerSecond{NaN_double}; //!< [m/s]
    double m_velocityUpInMeterPerSecond{NaN_double}; //!< [m/s]
    double m_velocityUpSigmaInMeterPerSecond{NaN_double}; //!< [m/s]
    double m_velocityXInMeterPerSecond{NaN_double}; //!< [m/s]
    double m_velocityXSigmaInMeterPerSecond{NaN_double}; //!< [m/s]
    double m_velocityYInMeterPerSecond{NaN_double}; //!< [m/s]
    double m_velocityYSigmaInMeterPerSecond{NaN_double}; //!< [m/s]
    double m_velocityZInMeterPerSecond{NaN_double}; //!< [m/s]
    double m_velocityZSigmaInMeterPerSecond{NaN_double}; //!< [m/s]

    double m_rollRateInRadPerSecond{NaN_double}; //!< [rad/s]
    double m_rollRateSigmaInRadPerSecond{NaN_double}; //!< [rad/s]
    double m_yawRateInRadPerSecond{NaN_double}; //!< [rad/s]
    double m_yawRateSigmaInRadPerSecond{NaN_double}; //!< [rad/s]
    double m_pitchRateInRadPerSecond{NaN_double}; //!< [rad/s]
    double m_pitchRateSigmaInRadPerSecond{NaN_double}; //!< [rad/s]

    double m_gpsStatus{NaN_double}; //!< [none] (tbd)
    uint8_t m_noOfSatellites{0}; //!< [none]

    double m_gpsDilutionOfPrecisionX{NaN_double}; //!< [none]
    double m_gpsDilutionOfPrecisionY{NaN_double}; //!< [none]
    double m_gpsDilutionOfPrecisionZ{NaN_double}; //!< [none]
    double m_gpsDilutionOfPrecisionVertical{NaN_double}; //!< [none]
    double m_gpsDilutionOfPrecisionPosition{NaN_double}; //!< [none]

    Timestamp m_timestamp{};

    GpsImuSourceIn9001 m_source{GpsImuSourceIn9001::Unknown};
    GpsImuInsQualityIn9001 m_insQuality{GpsImuInsQualityIn9001::Gps};

    ReservedArray m_reserved{{0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}};
}; // GpsImu9001

//==============================================================================

bool operator==(const GpsImu9001& lhs, const GpsImu9001& rhs);
bool operator!=(const GpsImu9001& lhs, const GpsImu9001& rhs);

//==============================================================================

template<>
void writeBE<GpsImuSourceIn9001>(std::ostream& os, const GpsImuSourceIn9001& s);

template<>
void writeBE<GpsImuInsQualityIn9001>(std::ostream& os, const GpsImuInsQualityIn9001& s);

template<>
void readBE<GpsImuSourceIn9001>(std::istream& is, GpsImuSourceIn9001& tc);

template<>
void readBE<GpsImuInsQualityIn9001>(std::istream& is, GpsImuInsQualityIn9001& tc);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

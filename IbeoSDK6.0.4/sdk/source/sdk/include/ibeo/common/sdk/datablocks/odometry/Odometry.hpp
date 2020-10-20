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
//!\date Jan 29th, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/Timestamp.hpp>

#include <ibeo/common/sdk/datablocks/odometry/special/Odometry9002.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Motion data
//!
//! This data type contains unprocessed motion data, such as the velocity and the yaw rate of the vehicle
//! that is provided to the system via CAN.
//!
//! Special data type: \ref ibeo::common::sdk::Odometry9002
class Odometry : public DataContainerBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

    friend bool operator==(const Odometry& lhs, const Odometry& rhs);

public:
    constexpr static const char* const containerType{"ibeo.sdk.generalcontainer.odometry"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    Odometry();
    ~Odometry() override = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public: // getter
    //========================================
    //!\brief Get the steering angle.
    //----------------------------------------
    double getSteeringAngle() const { return m_delegate.getSteeringAngle(); }

    //========================================
    //!\brief Get the steering wheel angle in [rad].
    //----------------------------------------
    double getSteeringWheelAngle() const { return m_delegate.getSteeringWheelAngle(); }

    //========================================
    //!\brief Get the steering wheel angle velocity.
    //----------------------------------------
    double getSteeringWheelAngleVelocity() const { return m_delegate.getSteeringWheelAngleVelocity(); }

    //========================================
    //!\brief Get the front left wheel speed in [m/s].
    //----------------------------------------
    double getWheelSpeedFL() const { return m_delegate.getWheelSpeedFL(); }

    //========================================
    //!\brief Get the front right wheel speed in [m/s].
    //----------------------------------------
    double getWheelSpeedFR() const { return m_delegate.getWheelSpeedFR(); }

    //========================================
    //!\brief Get the rear left wheel speed in [m/s].
    //----------------------------------------
    double getWheelSpeedRL() const { return m_delegate.getWheelSpeedRL(); }

    //========================================
    //!\brief Get the rear right wheel speed in [m/s].
    //----------------------------------------
    double getWheelSpeedRR() const { return m_delegate.getWheelSpeedRR(); }

    //========================================
    //!\brief Get the wheel size.
    //----------------------------------------
    double getWheelCircumference() const { return m_delegate.getWheelCircumference(); }

    //========================================
    //!\brief Get the vehicle velocity in [m/s].
    //----------------------------------------
    double getVehVelocity() const { return m_delegate.getVehVelocity(); }

    //========================================
    //!\brief Get the vehicle acceleration in [m/s^2].
    //----------------------------------------
    double getVehAcceleration() const { return m_delegate.getVehAcceleration(); }

    //========================================
    //!\brief Get the vehicle yaw rate in [rad/s].
    //----------------------------------------
    double getVehYawRate() const { return m_delegate.getVehYawRate(); }

    //========================================
    //!\brief Get the timestamp.
    //----------------------------------------
    const Timestamp& getTimestamp() const { return m_delegate.getTimestamp(); }

    //========================================
    //!\brief Get the wheel base in [m].
    //----------------------------------------
    float getWheelBase() const { return m_delegate.getWheelBase(); }

public: // setter
    //========================================
    //!\brief Set the steering angle.
    //----------------------------------------
    void setSteeringAngle(const double steeringAngle) { m_delegate.setSteeringAngle(steeringAngle); }

    //========================================
    //!\brief Set the steering wheel angle in [rad].
    //----------------------------------------
    void setSteeringWheelAngle(const double steeringWheelAngle)
    {
        m_delegate.setSteeringWheelAngle(steeringWheelAngle);
    }

    //========================================
    //!\brief Set the steering wheel angle velocity.
    //----------------------------------------
    void setSteeringWheelAngleVelocity(double steeringWheelAngleVelocity)
    {
        m_delegate.setSteeringWheelAngleVelocity(steeringWheelAngleVelocity);
    }

    //========================================
    //!\brief Set the front left wheel speed in [m/s].
    //----------------------------------------
    void setWheelSpeedFL(const double wheelSpeedFL) { m_delegate.setWheelSpeedFL(wheelSpeedFL); }

    //========================================
    //!\brief Set the front right wheel speed in [m/s].
    //----------------------------------------
    void setWheelSpeedFR(const double wheelSpeedFR) { m_delegate.setWheelSpeedFR(wheelSpeedFR); }

    //========================================
    //!\brief Set the rear left wheel speed in [m/s].
    //----------------------------------------
    void setWheelSpeedRL(const double wheelSpeedRL) { m_delegate.setWheelSpeedRL(wheelSpeedRL); }

    //========================================
    //!\brief Set the rear right wheel speed in [m/s].
    //----------------------------------------
    void setWheelSpeedRR(const double wheelSpeedRR) { m_delegate.setWheelSpeedRR(wheelSpeedRR); }

    //========================================
    //!\brief Set the wheel size.
    //----------------------------------------
    void setWheelCircumference(const double wheelCircumference)
    {
        m_delegate.setWheelCircumference(wheelCircumference);
    }

    //========================================
    //!\brief Set the vehicle velocity in [m/s].
    //----------------------------------------
    void setVehVelocity(const double vehVelocity) { m_delegate.setVehVelocity(vehVelocity); }

    //========================================
    //!\brief Set the vehicle acceleration in [m/s^2].
    //----------------------------------------
    void setVehAcceleration(const double vehAcceleration) { m_delegate.setVehAcceleration(vehAcceleration); }

    //========================================
    //!\brief Set the vehicle yaw rate in [rad/s].
    //----------------------------------------
    void setVehYawRate(const double vehYawRate) { m_delegate.setVehYawRate(vehYawRate); }

    //========================================
    //!\brief Set the timestamp.
    //----------------------------------------
    void setTimestamp(const Timestamp& timestamp) { m_delegate.setTimestamp(timestamp); }

    //========================================
    //!\brief Set the wheel base in [m].
    //----------------------------------------
    void setWheelBase(const float wheelBase) { m_delegate.setWheelBase(wheelBase); }

protected:
    Odometry9002 m_delegate; // only possible specialization currently
}; // OdometryContainer

//==============================================================================

bool operator==(const Odometry& lhs, const Odometry& rhs);
bool operator!=(const Odometry& lhs, const Odometry& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

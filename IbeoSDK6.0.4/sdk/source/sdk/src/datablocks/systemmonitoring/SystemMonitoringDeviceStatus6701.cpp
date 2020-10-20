//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 16, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringDeviceStatus6701.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

SystemMonitoringDeviceStatus6701::SystemMonitoringDeviceStatus6701() : SpecializedDataContainer() {}

//==============================================================================

SystemMonitoringDeviceStatus6701::~SystemMonitoringDeviceStatus6701() {}

//==============================================================================

std::string SystemMonitoringDeviceStatus6701::toString() const
{
    std::stringstream ss;
    ss << "Device ID: ";
    ss << static_cast<uint32_t>(m_deviceId);
    ss << ", device type: ";

    switch (m_type)
    {
    case DeviceType::Scanner:
        ss << "Scanner";
        break;
    case DeviceType::Camera:
        ss << "Camera";
        break;
    case DeviceType::Can:
        ss << "CAN";
        break;
    case DeviceType::Wgs84:
        ss << "WGS84";
        break;
    case DeviceType::Gps:
        ss << "GPS";
        break;
    case DeviceType::Imu:
        ss << "IMU";
        break;
    default:
        ss << "Unknown";
        break;
    } // switch type

    ss << ", state: ";
    switch (m_state)
    {
    case State::Init:
        ss << "Initialization";
        break;
    case State::OK:
        ss << "OK";
        break;
    case State::Warning:
        ss << "Warning";
        break;
    case State::Error:
        ss << "Error";
        break;
    default:
        ss << "Unknown";
        break;
    } // switch state

    return ss.str();
}

//==============================================================================

//==============================================================================

bool operator==(const SystemMonitoringDeviceStatus6701& lhs, const SystemMonitoringDeviceStatus6701& rhs)
{
    return lhs.getDeviceId() == rhs.getDeviceId() && lhs.getType() == rhs.getType()
           && lhs.getTypeInformation() == rhs.getTypeInformation() && lhs.getState() == rhs.getState()
           && lhs.getStateInformation() == rhs.getStateInformation()
           && lhs.getUpdateMissing() == rhs.getUpdateMissing();
}

//==============================================================================

bool operator!=(const SystemMonitoringDeviceStatus6701& lhs, const SystemMonitoringDeviceStatus6701& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

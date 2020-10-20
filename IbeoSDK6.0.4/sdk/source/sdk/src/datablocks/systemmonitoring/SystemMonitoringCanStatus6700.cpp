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

#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringCanStatus6700.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

SystemMonitoringCanStatus6700::SystemMonitoringCanStatus6700() : SpecializedDataContainer() {}

//==============================================================================

SystemMonitoringCanStatus6700::~SystemMonitoringCanStatus6700() {}

//==============================================================================

std::string SystemMonitoringCanStatus6700::toString() const
{
    std::stringstream ss;
    ss << "CAN device ID: ";
    ss << static_cast<uint32_t>(m_deviceId);
    ss << ", message ID: ";
    ss << m_messageId;
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

bool operator==(const SystemMonitoringCanStatus6700& lhs, const SystemMonitoringCanStatus6700& rhs)
{
    return (lhs.getDeviceId() == rhs.getDeviceId()) && (lhs.getMessageId() == rhs.getMessageId())
           && (lhs.getState() == rhs.getState()) && (lhs.getStateInformation() == rhs.getStateInformation())
           && (lhs.getUpdateMissing() == rhs.getUpdateMissing());
}

//==============================================================================

bool operator!=(const SystemMonitoringCanStatus6700& lhs, const SystemMonitoringCanStatus6700& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

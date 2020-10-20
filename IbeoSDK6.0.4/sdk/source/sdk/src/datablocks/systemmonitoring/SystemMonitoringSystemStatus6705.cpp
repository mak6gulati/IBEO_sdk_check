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

#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringSystemStatus6705.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

SystemMonitoringSystemStatus6705::SystemMonitoringSystemStatus6705() : SpecializedDataContainer() {}

SystemMonitoringSystemStatus6705::~SystemMonitoringSystemStatus6705() {}

//==============================================================================

std::string SystemMonitoringSystemStatus6705::toString() const
{
    std::stringstream ss;
    ss << "System state: ";

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

bool operator==(const SystemMonitoringSystemStatus6705& lhs, const SystemMonitoringSystemStatus6705& rhs)
{
    return (lhs.getLastUpdateTimestamp() == rhs.getLastUpdateTimestamp()) && (lhs.getState() == rhs.getState())
           && (lhs.getStateInformation() == rhs.getStateInformation())
           && (lhs.getCurrentCpuUsage() == rhs.getCurrentCpuUsage())
           && (lhs.getCurrentRamUsage() == rhs.getCurrentRamUsage())
           && (lhs.getCurrentHddUsage() == rhs.getCurrentHddUsage())
           && (lhs.getHddWarningLevel() == rhs.getHddWarningLevel())
           && (lhs.getHddErrorLevel() == rhs.getHddErrorLevel());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

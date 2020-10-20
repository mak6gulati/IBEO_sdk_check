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
//!\date 18.04.2017
//------------------------------------------------------------------------------

#include "SystemMonitoringTestSupport.hpp"

#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

SystemMonitoringTestSupport::SystemMonitoringTestSupport() : TestSupport() {}

//==============================================================================

SystemMonitoringTestSupport::~SystemMonitoringTestSupport() {}

//==============================================================================

ibeo::common::sdk::SystemMonitoringCanStatus6700 SystemMonitoringTestSupport::createSystemMonitoringCanStatus6700()
{
    ibeo::common::sdk::SystemMonitoringCanStatus6700 o;
    fillRandomly(o);
    return o;
}

//==============================================================================

ibeo::common::sdk::SystemMonitoringDeviceStatus6701
SystemMonitoringTestSupport::createSystemMonitoringDeviceStatus6701()
{
    ibeo::common::sdk::SystemMonitoringDeviceStatus6701 o;
    fillRandomly(o);
    return o;
}

//==============================================================================

ibeo::common::sdk::SystemMonitoringSystemStatus6705
SystemMonitoringTestSupport::createSystemMonitoringSystemStatus6705()
{
    ibeo::common::sdk::SystemMonitoringSystemStatus6705 o;
    fillRandomly(o);
    return o;
}

//==============================================================================

void SystemMonitoringTestSupport::fillRandomly(ibeo::common::sdk::SystemMonitoringCanStatus6700& input)
{
    const uint8_t deviceId = getRandValue<uint8_t>();
    input.setDeviceId(deviceId);

    const uint32_t messageId = getRandValue<uint32_t>();
    input.setMessageId(messageId);

    const uint8_t state = getRandValue<uint8_t>(3);
    input.setState(static_cast<const SystemMonitoringCanStatus6700::State>(state));

    const uint8_t stateInformation = getRandValue<uint8_t>();
    input.setStateInformation(stateInformation);

    const boost::posix_time::ptime updateMissing
        = boost::posix_time::second_clock::local_time() + boost::posix_time::seconds(getRandValue<uint32_t>());
    input.setUpdateMissing(updateMissing);
}

//==============================================================================

void SystemMonitoringTestSupport::fillRandomly(ibeo::common::sdk::SystemMonitoringDeviceStatus6701& input)
{
    const uint8_t deviceId = getRandValue<uint8_t>();
    input.setDeviceId(deviceId);

    const uint8_t type = getRandValue<uint8_t>(6);
    input.setType(static_cast<const SystemMonitoringDeviceStatus6701::DeviceType>(type));

    const uint8_t typeInformation = getRandValue<uint8_t>();
    input.setTypeInformation(typeInformation);

    const uint8_t state = getRandValue<uint8_t>(3);
    input.setState(static_cast<const SystemMonitoringDeviceStatus6701::State>(state));

    const uint8_t stateInformation = getRandValue<uint8_t>();
    input.setStateInformation(stateInformation);

    const boost::posix_time::ptime updateMissing
        = boost::posix_time::second_clock::local_time() + boost::posix_time::seconds(getRandValue<uint32_t>());
    input.setUpdateMissing(updateMissing);
}

//==============================================================================

void SystemMonitoringTestSupport::fillRandomly(ibeo::common::sdk::SystemMonitoringSystemStatus6705& input)
{
    const uint8_t cpuUsage = getRandValue<uint8_t>();
    input.setCurrentCpuUsage(cpuUsage);

    const uint8_t hddUsage = getRandValue<uint8_t>();
    input.setCurrentHddUsage(hddUsage);

    const uint8_t ramUsage = getRandValue<uint8_t>();
    input.setCurrentRamUsage(ramUsage);

    const uint8_t warningLevel = getRandValue<uint8_t>();
    input.setHddWarningLevel(warningLevel);

    const uint8_t errorLevel = getRandValue<uint8_t>();
    input.setHddErrorLevel(errorLevel);

    const uint8_t state = getRandValue<uint8_t>(3);
    input.setState(static_cast<const SystemMonitoringSystemStatus6705::State>(state));

    const uint8_t stateInformation = getRandValue<uint8_t>();
    input.setStateInformation(stateInformation);

    const boost::posix_time::ptime lastUpdate
        = boost::posix_time::second_clock::local_time() + boost::posix_time::seconds(getRandValue<uint32_t>());
    input.setLastUpdateTimestamp(lastUpdate);
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

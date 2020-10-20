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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringCanStatus6700.hpp>
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringDeviceStatus6701.hpp>
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringSystemStatus6705.hpp>

#include <ibeo/common/sdk/datablocks/ClockType.hpp>
#include <ibeo/common/sdk/datablocks/Timestamp.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class SystemMonitoringTestSupport : public TestSupport
{
public:
    SystemMonitoringTestSupport();
    virtual ~SystemMonitoringTestSupport();

public:
    static ibeo::common::sdk::SystemMonitoringCanStatus6700 createSystemMonitoringCanStatus6700();

    static ibeo::common::sdk::SystemMonitoringDeviceStatus6701 createSystemMonitoringDeviceStatus6701();

    static ibeo::common::sdk::SystemMonitoringSystemStatus6705 createSystemMonitoringSystemStatus6705();

private:
    static void fillRandomly(ibeo::common::sdk::SystemMonitoringCanStatus6700& input);

    static void fillRandomly(ibeo::common::sdk::SystemMonitoringDeviceStatus6701& input);

    static void fillRandomly(ibeo::common::sdk::SystemMonitoringSystemStatus6705& input);

protected:
    static const int32_t nbOfRepeats = 100;
}; // SystemMonitoringTestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

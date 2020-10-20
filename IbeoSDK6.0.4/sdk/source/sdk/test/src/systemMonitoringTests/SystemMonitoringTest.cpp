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

#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringCanStatus6700Importer6700.hpp>
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringCanStatus6700Exporter6700.hpp>
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringDeviceStatus6701Importer6701.hpp>
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringDeviceStatus6701Exporter6701.hpp>
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringSystemStatus6705Importer6705.hpp>
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringSystemStatus6705Exporter6705.hpp>

#define BOOST_TEST_MODULE SystemMonitoringTest
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(SystemMonitoringTestSuite)

//==============================================================================

class Fixture : public unittests::SystemMonitoringTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createSystemMonitoring, Fixture)
{
    ibeo::common::sdk::SystemMonitoringCanStatus6700 o1;
    ibeo::common::sdk::SystemMonitoringDeviceStatus6701 o2;
    ibeo::common::sdk::SystemMonitoringSystemStatus6705 o3;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoSystemMonitoringIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        SystemMonitoringCanStatus6700 canStatus(createSystemMonitoringCanStatus6700());
        const SystemMonitoringCanStatus6700Exporter6700 canStatusExporter;
        const IbeoDataHeader dhCan(
            canStatusExporter.getDataType(), 0, uint32_t(canStatusExporter.getSerializedSize(canStatus)), 0, NTPTime());

        SystemMonitoringDeviceStatus6701 deviceStatus(createSystemMonitoringDeviceStatus6701());
        const SystemMonitoringDeviceStatus6701Exporter6701 deviceStatusExporter;
        const IbeoDataHeader dhDevice(deviceStatusExporter.getDataType(),
                                      0,
                                      uint32_t(deviceStatusExporter.getSerializedSize(deviceStatus)),
                                      0,
                                      NTPTime());

        SystemMonitoringSystemStatus6705 systemStatus(createSystemMonitoringSystemStatus6705());
        const SystemMonitoringSystemStatus6705Exporter6705 systemStatusExporter;
        const IbeoDataHeader dhSystem(systemStatusExporter.getDataType(),
                                      0,
                                      uint32_t(systemStatusExporter.getSerializedSize(systemStatus)),
                                      0,
                                      NTPTime());

        std::stringstream ssCan;
        BOOST_CHECK(canStatusExporter.serialize(ssCan, canStatus));

        std::stringstream ssDevice;
        BOOST_CHECK(deviceStatusExporter.serialize(ssDevice, deviceStatus));

        std::stringstream ssSystem;
        BOOST_CHECK(systemStatusExporter.serialize(ssSystem, systemStatus));

        SystemMonitoringCanStatus6700 copyCan;
        const SystemMonitoringCanStatus6700Importer6700 canStatusImporter;
        BOOST_CHECK(canStatusImporter.deserialize(ssCan, copyCan, dhCan));

        SystemMonitoringDeviceStatus6701 copyDevice;
        const SystemMonitoringDeviceStatus6701Importer6701 deviceStatusImporter;
        BOOST_CHECK(deviceStatusImporter.deserialize(ssDevice, copyDevice, dhDevice));

        SystemMonitoringSystemStatus6705 copySystem;
        const SystemMonitoringSystemStatus6705Importer6705 systemStatusImporter;
        BOOST_CHECK(systemStatusImporter.deserialize(ssSystem, copySystem, dhSystem));

        BOOST_CHECK(copyCan == canStatus);

        BOOST_CHECK(copyDevice == deviceStatus);

        BOOST_CHECK(copySystem == systemStatus);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

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
//!\date Jan 25, 2018
//------------------------------------------------------------------------------

#include "DeviceStatusTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303Exporter6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303Importer6303.hpp>

#define BOOST_TEST_MODULE DeviceStatus6303Test
#include <boost/test/unit_test.hpp>

#include <vector>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(DeviceStatus6303TestSuite)

//==============================================================================

class Fixture : public unittests::DeviceStatusTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createDeviceStatus6303, Fixture)
{
    ibeo::common::sdk::DeviceStatus6303 oa;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoDeviceStatus6303Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const DeviceStatus6303Exporter6303 exporter;
        DeviceStatus6303 dsOrig;
        fillRandomly(dsOrig, false);

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(dsOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, dsOrig));

        DeviceStatus6303 dsCopy;
        const DeviceStatus6303Importer6303 importer;
        BOOST_CHECK(importer.deserialize(ss, dsCopy, dh));

        BOOST_CHECK(dsOrig == dsCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReorderedContentDeviceStatus6303Identity, Fixture)
{
    class DeviceStatus6303Wrapper : public DeviceStatus6303
    {
    public:
        using DeviceStatus6303::clear;
    }; // DeviceStatus6303Wrapper

    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const DeviceStatus6303Exporter6303 exporter;
        DeviceStatus6303 dsOrig;
        fillRandomly(dsOrig, true);

        //		std::cerr << "Deserialize" << std::endl;
        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(dsOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, dsOrig));

        DeviceStatus6303Wrapper dsCopy;
        const DeviceStatus6303Importer6303 importer;
        BOOST_CHECK(importer.deserialize(ss, dsCopy, dh));
        BOOST_CHECK(dsOrig == dsCopy);

        //		std::cerr << "Reordering" << std::endl;
        // Remove the contents from dsCopy and add them (from dsOrig)
        // again in random order
        dsCopy.clear();
        DeviceStatus6303::ContentDescrVector cdv = dsOrig.getContentDescrs();
        while (!cdv.empty())
        {
            const uint32_t idx                          = getRandValue<uint8_t>(uint8_t(cdv.size() - 1));
            const DeviceStatus6303::ContentDescr& descr = cdv[idx];

            dsCopy.addContent(descr);
            cdv.erase(cdv.begin() + idx);
        }
        //if (dsOrig.getContentDescrs().size() == dsCopy.getContentDescrs().size()) {
        BOOST_REQUIRE(dsOrig == dsCopy);
        //}
        //		std::cerr << "===============================================" << std::endl;
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoAdaptiveApdVoltageAndNoiseInfoIn6303Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const DeviceStatus6303Exporter6303 exporter;
        DeviceStatus6303 dsOrig;

        AdaptiveApdVoltageAndNoiseInfoIn6303 avt;
        fillRandomly(avt);
        dsOrig.addContent(avt);

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(dsOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, dsOrig));

        DeviceStatus6303 dsCopy;
        const DeviceStatus6303Importer6303 importer;
        BOOST_CHECK(importer.deserialize(ss, dsCopy, dh));

        BOOST_CHECK(dsOrig == dsCopy);

        // User defined structs are not decoded during deserialization but when fetched from the device status.
        // Only one user defined struct allowed per device status.
        AdaptiveApdVoltageAndNoiseInfoIn6303 avtOrig;
        dsOrig.getContent(DeviceStatus6303::ContentId::AdaptiveApdVoltageNoiseArray, avtOrig);

        AdaptiveApdVoltageAndNoiseInfoIn6303 avtCopy;
        dsOrig.getContent(DeviceStatus6303::ContentId::AdaptiveApdVoltageNoiseArray, avtCopy);

        BOOST_CHECK(avtOrig == avtCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

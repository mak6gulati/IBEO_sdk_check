//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Jan 30, 2019
//------------------------------------------------------------------------------

#include "DeviceStatusTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusExporter6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusImporter6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusExporter6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusImporter6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301Exporter6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301Importer6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303Exporter6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303Importer6303.hpp>

#define BOOST_TEST_MODULE DeviceStatusTest
#include <boost/test/unit_test.hpp>

#include <vector>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(DeviceStatusTestSuite)

//==============================================================================

class Fixture : public unittests::DeviceStatusTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createDeviceStatus, Fixture)
{
    ibeo::common::sdk::DeviceStatus ds;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoDeviceStatusIdentityVia6301, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const DeviceStatusExporter6301 exporter;
        DeviceStatus dsOrig;
        fillRandomly(dsOrig);

        // Clear all members that cannot be exported identically using data type 6301.
        dsOrig.setDeviceId(0);
        dsOrig.setFpgaStatusRegister(0);
        dsOrig.setSensorTemperatureApd1(0);

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(dsOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, dsOrig));

        DeviceStatus dsCopy;
        const DeviceStatusImporter6301 importer;
        BOOST_CHECK(importer.deserialize(ss, dsCopy, dh));

        BOOST_CHECK(dsOrig == dsCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoDeviceStatusIdentityVia6303, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const DeviceStatusExporter6303 exporter;
        DeviceStatus dsOrig;
        fillRandomly(dsOrig);

        // Clear all members that cannot be exported identically using data type 6301.
        dsOrig.setDspVersion(Version448());
        dsOrig.setFpgaStatusRegister(0);
        dsOrig.setSensorTemperatureApd1(0);
        dsOrig.setScanFrequency(1.0F);

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(dsOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, dsOrig));

        DeviceStatus dsCopy;
        const DeviceStatusImporter6303 importer;
        BOOST_CHECK(importer.deserialize(ss, dsCopy, dh));

        BOOST_CHECK(dsOrig == dsCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoDeviceStatus6301IdentityViaGdc, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        DeviceStatus6301 dsOrig6301;
        fillRandomly(dsOrig6301);

        std::stringstream ss;
        DeviceStatus dsCopyGdc;
        {
            const DeviceStatus6301Exporter6301 exporter6301;
            BOOST_CHECK(exporter6301.serialize(ss, dsOrig6301));

            const IbeoDataHeader dh(
                exporter6301.getDataType(), 0, uint32_t(exporter6301.getSerializedSize(dsOrig6301)), 0, NTPTime());
            const DeviceStatusImporter6301 importerGdc;
            BOOST_CHECK(importerGdc.deserialize(ss, dsCopyGdc, dh));
        }

        ss.clear();
        ss.str(std::string());

        DeviceStatus6301 dsCopy6301;
        {
            const DeviceStatusExporter6301 exporterGdc;
            BOOST_CHECK(exporterGdc.serialize(ss, dsCopyGdc));

            const IbeoDataHeader dh(
                exporterGdc.getDataType(), 0, uint32_t(exporterGdc.getSerializedSize(dsCopyGdc)), 0, NTPTime());
            const DeviceStatus6301Importer6301 importer6301;
            BOOST_CHECK(importer6301.deserialize(ss, dsCopy6301, dh));
        }

        BOOST_CHECK(dsOrig6301 == dsCopy6301);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoDeviceStatus6303IdentityViaGdc, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        DeviceStatus6303 dsOrig6303;

        // Add variable content array to be serialized into GDC.
        float apdBiasVoltage{getRandValue<float>()};
        dsOrig6303.addContent(DeviceStatus6303::ContentId::ApdVoltageTable,
                              DeviceStatus6303::ElementType::FLOAT32,
                              sizeof(float),
                              1,
                              &apdBiasVoltage);

        AdaptiveApdVoltageAndNoiseInfoIn6303 avt;
        fillRandomly(avt);

        // Clear all members that will not be exported via GDC.
        avt.setProcUnitAndVersion(0);
        avt.setScanNumber(std::numeric_limits<uint16_t>::max());
        avt.setFlags(0);
        for (AdaptiveApdVoltageAndNoiseInfoIn6303::ApdSector& sector : avt.getSectors())
        {
            sector.setReducedApdOffset(NaN);
        }

        dsOrig6303.addContent(avt);

        AdaptiveApdVoltageAndNoiseInfoIn6303 xxx;
        dsOrig6303.getContent(DeviceStatus6303::ContentId::AdaptiveApdVoltageNoiseArray, xxx);

        std::stringstream ss;
        DeviceStatus dsCopyGdc;
        {
            const DeviceStatus6303Exporter6303 exporter6303;
            BOOST_CHECK(exporter6303.serialize(ss, dsOrig6303));

            const IbeoDataHeader dh(
                exporter6303.getDataType(), 0, uint32_t(exporter6303.getSerializedSize(dsOrig6303)), 0, NTPTime());
            const DeviceStatusImporter6303 importerGdc;
            BOOST_CHECK(importerGdc.deserialize(ss, dsCopyGdc, dh));
        }

        ss.clear();
        ss.str(std::string());

        DeviceStatus6303 dsCopy6303;
        {
            const DeviceStatusExporter6303 exporterGdc;
            BOOST_CHECK(exporterGdc.serialize(ss, dsCopyGdc));

            const IbeoDataHeader dh(
                exporterGdc.getDataType(), 0, uint32_t(exporterGdc.getSerializedSize(dsCopyGdc)), 0, NTPTime());
            const DeviceStatus6303Importer6303 importer6303;
            BOOST_CHECK(importer6303.deserialize(ss, dsCopy6303, dh));
        }

        BOOST_CHECK(dsOrig6303 == dsCopy6303);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

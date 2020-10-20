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
//!\date Feb 05, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <wgs84Tests/PositionWgs84_2604TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84_2604Exporter2604.hpp>
#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84_2604Importer2604.hpp>

#define BOOST_TEST_MODULE Wgs84Test
#include <boost/test/unit_test.hpp>

#include <vector>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(Wgs84TestSuite)

//==============================================================================

class Fixture : public unittests::PositionWgs84_2604TestSupport
{
}; // Fixture

//==============================================================================
//creation test
BOOST_FIXTURE_TEST_CASE(createPositionWgs84_2604, Fixture)
{
    PositionWgs84_2604 oa;
    BOOST_CHECK(oa == oa);
}

//==============================================================================

//test operator==
BOOST_FIXTURE_TEST_CASE(isIoPositionWgs84_2604IdentityRad, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const PositionWgs84_2604Exporter2604 exporter;
        PositionWgs84_2604 wgs84orig;
        fillRandomly(wgs84orig.getPosition());

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(wgs84orig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, wgs84orig));

        PositionWgs84_2604 wgs84copy;
        const PositionWgs84_2604Importer2604 importer;
        BOOST_CHECK(importer.deserialize(ss, wgs84copy, dh));
        BOOST_CHECK(wgs84orig == wgs84copy);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoPositionWgs84_2604Equality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        PositionWgs84_2604 wgs84orig, wgs84copy;
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setUsSinceStartup(
            getDifferentRandValue<uint32_t>(wgs84orig.getPosition().getUsSinceStartup()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setUsSinceStartup(wgs84orig.getPosition().getUsSinceStartup());
        BOOST_CHECK(wgs84orig == wgs84copy);

        NTPTime tmpTime = wgs84orig.getPosition().getTimestamp();
        do
        {
            wgs84orig.getPosition().setTimestamp(getRandValue<NTPTime>());
        } while ((wgs84orig.getPosition().getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (wgs84orig.getPosition().getTimestamp() == tmpTime));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setTimestamp(wgs84orig.getPosition().getTimestamp());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setDeviceId(getDifferentRandValue<uint8_t>(wgs84orig.getPosition().getDeviceId()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setDeviceId(wgs84orig.getPosition().getDeviceId());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setLatitudeInRad(
            getDifferentRandValue<double>(wgs84orig.getPosition().getLatitudeInRad()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setLatitudeInRad(wgs84orig.getPosition().getLatitudeInRad());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setLatitudeSigmaInMeter(
            getDifferentRandValue<double>(wgs84orig.getPosition().getLatitudeSigmaInMeter()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setLatitudeSigmaInMeter(wgs84orig.getPosition().getLatitudeSigmaInMeter());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setLongitudeInRad(
            getDifferentRandValue<double>(wgs84orig.getPosition().getLongitudeInRad()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setLongitudeInRad(wgs84orig.getPosition().getLongitudeInRad());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setLongitudeSigmaInMeter(
            getDifferentRandValue<double>(wgs84orig.getPosition().getLongitudeSigmaInMeter()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setLongitudeSigmaInMeter(wgs84orig.getPosition().getLongitudeSigmaInMeter());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setAltitudeInMeterMSL(
            getDifferentRandValue<double>(wgs84orig.getPosition().getAltitudeInMeterMSL()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setAltitudeInMeterMSL(wgs84orig.getPosition().getAltitudeInMeterMSL());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setAltitudeSigmaInMeterMSL(
            getDifferentRandValue<double>(wgs84orig.getPosition().getAltitudeSigmaInMeterMSL()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setAltitudeSigmaInMeterMSL(wgs84orig.getPosition().getAltitudeSigmaInMeterMSL());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setCourseAngleInRad(
            getDifferentRandValue<double>(wgs84orig.getPosition().getCourseAngleInRad()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setCourseAngleInRad(wgs84orig.getPosition().getCourseAngleInRad());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setCourseAngleSigmaInRad(
            getDifferentRandValue<double>(wgs84orig.getPosition().getCourseAngleSigmaInRad()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setCourseAngleSigmaInRad(wgs84orig.getPosition().getCourseAngleSigmaInRad());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setYawAngleInRad(
            getDifferentRandValue<double>(wgs84orig.getPosition().getYawAngleInRad()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setYawAngleInRad(wgs84orig.getPosition().getYawAngleInRad());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setYawAngleSigmaInRad(
            getDifferentRandValue<double>(wgs84orig.getPosition().getYawAngleSigmaInRad()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setYawAngleSigmaInRad(wgs84orig.getPosition().getYawAngleSigmaInRad());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setPitchAngleInRad(
            getDifferentRandValue<double>(wgs84orig.getPosition().getPitchAngleInRad()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setPitchAngleInRad(wgs84orig.getPosition().getPitchAngleInRad());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setPitchAngleSigmaInRad(
            getDifferentRandValue<double>(wgs84orig.getPosition().getPitchAngleSigmaInRad()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setPitchAngleSigmaInRad(wgs84orig.getPosition().getPitchAngleSigmaInRad());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setRollAngleInRad(
            getDifferentRandValue<double>(wgs84orig.getPosition().getRollAngleInRad()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setRollAngleInRad(wgs84orig.getPosition().getRollAngleInRad());
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig.getPosition().setRollAngleSigmaInRad(
            getDifferentRandValue<double>(wgs84orig.getPosition().getRollAngleSigmaInRad()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy.getPosition().setRollAngleSigmaInRad(wgs84orig.getPosition().getRollAngleSigmaInRad());
        BOOST_CHECK(wgs84orig == wgs84copy);
    } // for r
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoPositionWgs84_2604Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        PositionWgs84_2604 wgs84empty, wgs84orig, wgs84copy;
        BOOST_CHECK(wgs84orig == wgs84copy);
        BOOST_CHECK(wgs84orig == wgs84empty);

        wgs84orig.getPosition().setUsSinceStartup(
            getDifferentRandValue<uint32_t>(wgs84orig.getPosition().getUsSinceStartup()));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        NTPTime tmpTime = wgs84orig.getPosition().getTimestamp();
        do
        {
            wgs84orig.getPosition().setTimestamp(getRandValue<NTPTime>());
        } while ((wgs84orig.getPosition().getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (wgs84orig.getPosition().getTimestamp() == tmpTime));
        BOOST_CHECK(wgs84orig != wgs84copy);
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);

        uint8_t tmp_uint8 = wgs84orig.getPosition().getDeviceId();
        wgs84orig.getPosition().setDeviceId(getDifferentRandValue<uint8_t>(tmp_uint8));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        double tmp_dbl = wgs84orig.getPosition().getLatitudeInRad();
        wgs84orig.getPosition().setLatitudeInRad(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);

        wgs84orig = wgs84empty;
        tmp_dbl   = wgs84orig.getPosition().getLatitudeSigmaInMeter();
        wgs84orig.getPosition().setLatitudeSigmaInMeter(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        tmp_dbl = wgs84orig.getPosition().getLongitudeInRad();
        wgs84orig.getPosition().setLongitudeInRad(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        tmp_dbl = wgs84orig.getPosition().getLongitudeSigmaInMeter();
        wgs84orig.getPosition().setLongitudeSigmaInMeter(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        tmp_dbl = wgs84orig.getPosition().getAltitudeInMeterMSL();
        wgs84orig.getPosition().setAltitudeInMeterMSL(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        tmp_dbl = wgs84orig.getPosition().getAltitudeSigmaInMeterMSL();
        wgs84orig.getPosition().setAltitudeSigmaInMeterMSL(getNonNanRandValue<double>());
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        tmp_dbl = wgs84orig.getPosition().getCourseAngleInRad();
        wgs84orig.getPosition().setCourseAngleInRad(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        tmp_dbl = wgs84orig.getPosition().getCourseAngleSigmaInRad();
        wgs84orig.getPosition().setCourseAngleSigmaInRad(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        tmp_dbl = wgs84orig.getPosition().getYawAngleInRad();
        wgs84orig.getPosition().setYawAngleInRad(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        wgs84orig = wgs84empty;
        tmp_dbl   = wgs84orig.getPosition().getYawAngleSigmaInRad();
        wgs84orig.getPosition().setYawAngleSigmaInRad(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        tmp_dbl = wgs84orig.getPosition().getPitchAngleInRad();
        wgs84orig.getPosition().setPitchAngleInRad(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        tmp_dbl = wgs84orig.getPosition().getPitchAngleSigmaInRad();
        wgs84orig.getPosition().setPitchAngleSigmaInRad(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        tmp_dbl = wgs84orig.getPosition().getRollAngleInRad();
        wgs84orig.getPosition().setRollAngleInRad(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        wgs84orig = wgs84empty;
        BOOST_CHECK(wgs84orig == wgs84empty);
        BOOST_CHECK(wgs84copy != wgs84empty);

        tmp_dbl = wgs84orig.getPosition().getRollAngleSigmaInRad();
        wgs84orig.getPosition().setRollAngleSigmaInRad(getDifferentRandValue<double>(tmp_dbl));
        wgs84copy = wgs84orig;
        BOOST_CHECK(wgs84orig == wgs84copy);
        BOOST_CHECK(wgs84copy != wgs84empty);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

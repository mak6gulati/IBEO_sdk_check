//==============================================================================
//!\file
//!
//! Tests for General Data Container GPSIMU
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 30, 2019
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001Exporter9001.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001Importer9001.hpp>

#include <ibeo/common/sdk/datablocks/gpsimu/GpsImu.hpp>
#include "GpsImuTestSupport.hpp"
#include "GpsImu9001TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/gpsimu/GpsImuImporter9001.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/GpsImuExporter9001.hpp>

#define BOOST_TEST_MODULE GpsImuTest
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(GpsImuBasicTestSuite)

//==============================================================================

class Fixture : public unittests::GpsImuTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createGpsImu, Fixture)
{
    GpsImu gpsimu;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoGpsImuIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const GpsImuExporter9001 exporter;
        GpsImu gpsimuGdc(createGpsImu<GpsImu>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, gpsimuGdc));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(gpsimuGdc)), 0, NTPTime());

        GpsImu gpsimu9001;
        BOOST_CHECK(gpsimuGdc != gpsimu9001);
        const GpsImuImporter9001 importer;
        BOOST_CHECK(importer.deserialize(ss, gpsimu9001, dh));

        BOOST_CHECK(gpsimuGdc == gpsimu9001);
    } // for r
}

//==============================================================================
//Only importer available
BOOST_FIXTURE_TEST_CASE(isIoGpsImuIdentity9001, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const GpsImu9001Exporter9001 exporter9001;
        GpsImu9001 gpsimuOrig(createGpsImu<GpsImu9001>());

        std::stringstream ss1;

        BOOST_CHECK(exporter9001.serialize(ss1, gpsimuOrig));

        const IbeoDataHeader dh(
            exporter9001.getDataType(), 0, uint32_t(exporter9001.getSerializedSize(gpsimuOrig)), 0, NTPTime());

        const GpsImuImporter9001 gpsimuImporter9001;
        GpsImu gpsimu;
        BOOST_CHECK(gpsimuImporter9001.deserialize(ss1, gpsimu, dh));
    } // for r
}

//==============================================================================

// The following test checks equality for GpsImu9001->GpsImu_GDC->GpsImu9001
BOOST_FIXTURE_TEST_CASE(isIoGpsImuIdentity9001Gdc9001, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        GpsImu9001 gpsimu9001orig(createGpsImu<GpsImu9001>());

        const GpsImu9001Exporter9001 exporter;

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, gpsimu9001orig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(gpsimu9001orig)), 0, NTPTime());

        GpsImu gpsimuGdc;
        const GpsImuImporter9001 importer;
        BOOST_CHECK(importer.deserialize(ss, gpsimuGdc, dh));

        const GpsImuExporter9001 exporter9001;
        BOOST_CHECK(exporter9001.serialize(ss, gpsimuGdc));
        const IbeoDataHeader dhGdc(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(gpsimu9001orig)), 0, NTPTime());

        GpsImu9001 gpsimu9001dup;
        BOOST_CHECK(gpsimu9001orig != gpsimu9001dup);
        const GpsImu9001Importer9001 importer9001_9001;
        BOOST_CHECK(importer9001_9001.deserialize(ss, gpsimu9001dup, dh));

        BOOST_CHECK(gpsimu9001orig == gpsimu9001dup);
    } // for r
}

//==============================================================================

bool operator==(const GpsImu& lhs, const GpsImu9001& rhs)
{
    return doubleEqual(lhs.getLatitudeInRad(), rhs.getLatitudeInRad())
           && doubleEqual(lhs.getLatitudeSigmaInMeter(), rhs.getLatitudeSigmaInMeter())
           && doubleEqual(lhs.getLongitudeInRad(), rhs.getLongitudeInRad())
           && doubleEqual(lhs.getLongitudeSigmaInMeter(), rhs.getLongitudeSigmaInMeter())
           && doubleEqual(lhs.getAltitudeInMeter(), rhs.getAltitudeInMeter())
           && doubleEqual(lhs.getAltitudeSigmaInMeter(), rhs.getAltitudeSigmaInMeter())
           && doubleEqual(lhs.getCourseAngleInRad(), rhs.getCourseAngleInRad())
           && doubleEqual(lhs.getCourseAngleSigmaInRad(), rhs.getCourseAngleSigmaInRad())
           && doubleEqual(lhs.getYawAngleInRad(), rhs.getYawAngleInRad())
           && doubleEqual(lhs.getYawAngleSigmaInRad(), rhs.getYawAngleSigmaInRad())
           && doubleEqual(lhs.getPitchAngleInRad(), rhs.getPitchAngleInRad())
           && doubleEqual(lhs.getPitchAngleSigmaInRad(), rhs.getPitchAngleSigmaInRad())
           && doubleEqual(lhs.getRollAngleInRad(), rhs.getRollAngleInRad())
           && doubleEqual(lhs.getRollAngleSigmaInRad(), rhs.getRollAngleSigmaInRad())
           && doubleEqual(lhs.getCrossAccelerationInMeterPerSecond2(), rhs.getCrossAccelerationInMeterPerSecond2())
           && doubleEqual(lhs.getCrossAccelerationSigmaInMeterPerSecond2(),
                          rhs.getCrossAccelerationSigmaInMeterPerSecond2())
           && doubleEqual(lhs.getLongitudinalAccelerationInMeterPerSecond2(),
                          rhs.getLongitudinalAccelerationInMeterPerSecond2())
           && doubleEqual(lhs.getLongitudinalAccelerationSigmaInMeterPerSecond2(),
                          rhs.getLongitudinalAccelerationSigmaInMeterPerSecond2())
           && doubleEqual(lhs.getVerticalAccelerationInMeterPerSecond2(),
                          rhs.getVerticalAccelerationInMeterPerSecond2())
           && doubleEqual(lhs.getVerticalAccelerationSigmaInMeterPerSecond2(),
                          rhs.getVerticalAccelerationSigmaInMeterPerSecond2())
           && doubleEqual(lhs.getVelocityNorthInMeterPerSecond(), rhs.getVelocityNorthInMeterPerSecond())
           && doubleEqual(lhs.getVelocityNorthSigmaInMeterPerSecond(), rhs.getVelocityNorthSigmaInMeterPerSecond())
           && doubleEqual(lhs.getVelocityWestInMeterPerSecond(), rhs.getVelocityWestInMeterPerSecond())
           && doubleEqual(lhs.getVelocityWestSigmaInMeterPerSecond(), rhs.getVelocityWestSigmaInMeterPerSecond())
           && doubleEqual(lhs.getVelocityUpInMeterPerSecond(), rhs.getVelocityUpInMeterPerSecond())
           && doubleEqual(lhs.getVelocityUpSigmaInMeterPerSecond(), rhs.getVelocityUpSigmaInMeterPerSecond())
           && doubleEqual(lhs.getVelocityXInMeterPerSecond(), rhs.getVelocityXInMeterPerSecond())
           && doubleEqual(lhs.getVelocityXSigmaInMeterPerSecond(), rhs.getVelocityXSigmaInMeterPerSecond())
           && doubleEqual(lhs.getVelocityYInMeterPerSecond(), rhs.getVelocityYInMeterPerSecond())
           && doubleEqual(lhs.getVelocityYSigmaInMeterPerSecond(), rhs.getVelocityYSigmaInMeterPerSecond())
           && doubleEqual(lhs.getVelocityZInMeterPerSecond(), rhs.getVelocityZInMeterPerSecond())
           && doubleEqual(lhs.getVelocityZSigmaInMeterPerSecond(), rhs.getVelocityZSigmaInMeterPerSecond())
           && doubleEqual(lhs.getRollRateInRadPerSecond(), rhs.getRollRateInRadPerSecond())
           && doubleEqual(lhs.getRollRateSigmaInRadPerSecond(), rhs.getRollRateSigmaInRadPerSecond())
           && doubleEqual(lhs.getYawRateInRadPerSecond(), rhs.getYawRateInRadPerSecond())
           && doubleEqual(lhs.getYawRateSigmaInRadPerSecond(), rhs.getYawRateSigmaInRadPerSecond())
           && doubleEqual(lhs.getPitchRateInRadPerSecond(), rhs.getPitchRateInRadPerSecond())
           && doubleEqual(lhs.getPitchRateSigmaInRadPerSecond(), rhs.getPitchRateSigmaInRadPerSecond())
           && doubleEqual(lhs.getGpsStatus(), rhs.getGpsStatus())
           && (lhs.getNoOfSatellites() == rhs.getNoOfSatellites())
           && doubleEqual(lhs.getGpsDilutionOfPrecisionX(), rhs.getGpsDilutionOfPrecisionX())
           && doubleEqual(lhs.getGpsDilutionOfPrecisionY(), rhs.getGpsDilutionOfPrecisionY())
           && doubleEqual(lhs.getGpsDilutionOfPrecisionZ(), rhs.getGpsDilutionOfPrecisionZ())
           && doubleEqual(lhs.getGpsDilutionOfPrecisionVertical(), rhs.getGpsDilutionOfPrecisionVertical())
           && doubleEqual(lhs.getGpsDilutionOfPrecisionPosition(), rhs.getGpsDilutionOfPrecisionPosition())
           && (lhs.getTimestamp() == rhs.getTimestamp()) && (lhs.getSource() == rhs.getSource())
           && (lhs.getInsQuality() == rhs.getInsQuality());
}

// The following test checks equality for GpsImu9001->GpsImu_GDC
BOOST_FIXTURE_TEST_CASE(isIoGpsImuIdentity9001Gdc, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const GpsImu9001Exporter9001 exporter9001;
        GpsImu9001 gpsimu9001;
        GpsImuTestSupport::fillRandomly(gpsimu9001);

        std::stringstream ss;
        BOOST_CHECK(exporter9001.serialize(ss, gpsimu9001));

        const IbeoDataHeader dh(
            exporter9001.getDataType(), 0, uint32_t(exporter9001.getSerializedSize(gpsimu9001)), 0, NTPTime());

        GpsImu gpsimuGdc;
        const GpsImuImporter9001 importer;
        BOOST_CHECK(importer.deserialize(ss, gpsimuGdc, dh));

        BOOST_CHECK(gpsimuGdc == gpsimu9001);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoGpsImuEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        GpsImu gpsimuOrig, gpsimuCopy;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        Timestamp tmpTime = gpsimuOrig.getTimestamp();
        do
        {
            gpsimuOrig.setTimestamp(Timestamp(getRandValue<NTPTime>(), getRandValue<NTPTime>()));
        } while ((gpsimuOrig.getTimestamp().getMeasurementTimeEcu().is_not_a_date_time()
                  && tmpTime.getReceivedTimeEcu().is_not_a_date_time())
                 || (gpsimuOrig.getTimestamp() == tmpTime));

        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setTimestamp(gpsimuOrig.getTimestamp());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLatitudeInRad(getDifferentRandValue<double>(gpsimuOrig.getLatitudeInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setLatitudeInRad(gpsimuOrig.getLatitudeInRad());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLatitudeSigmaInMeter(getDifferentRandValue<double>(gpsimuOrig.getLatitudeSigmaInMeter()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setLatitudeSigmaInMeter(gpsimuOrig.getLatitudeSigmaInMeter());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLongitudeInRad(getDifferentRandValue<double>(gpsimuOrig.getLongitudeInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setLongitudeInRad(gpsimuOrig.getLongitudeInRad());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLongitudeSigmaInMeter(getDifferentRandValue<double>(gpsimuOrig.getLongitudeSigmaInMeter()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setLongitudeSigmaInMeter(gpsimuOrig.getLongitudeSigmaInMeter());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setAltitudeInMeter(getDifferentRandValue<double>(gpsimuOrig.getAltitudeInMeter()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setAltitudeInMeter(gpsimuOrig.getAltitudeInMeter());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setAltitudeSigmaInMeter(getDifferentRandValue<double>(gpsimuOrig.getAltitudeSigmaInMeter()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setAltitudeSigmaInMeter(gpsimuOrig.getAltitudeSigmaInMeter());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setCourseAngleInRad(getDifferentRandValue<double>(gpsimuOrig.getCourseAngleInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setCourseAngleInRad(gpsimuOrig.getCourseAngleInRad());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setCourseAngleSigmaInRad(getDifferentRandValue<double>(gpsimuOrig.getCourseAngleSigmaInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setCourseAngleSigmaInRad(gpsimuOrig.getCourseAngleSigmaInRad());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setYawAngleInRad(getDifferentRandValue<double>(gpsimuOrig.getYawAngleInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setYawAngleInRad(gpsimuOrig.getYawAngleInRad());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setYawAngleSigmaInRad(getDifferentRandValue<double>(gpsimuOrig.getYawAngleSigmaInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setYawAngleSigmaInRad(gpsimuOrig.getYawAngleSigmaInRad());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setPitchAngleInRad(getDifferentRandValue<double>(gpsimuOrig.getPitchAngleInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setPitchAngleInRad(gpsimuOrig.getPitchAngleInRad());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setPitchAngleSigmaInRad(getDifferentRandValue<double>(gpsimuOrig.getPitchAngleSigmaInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setPitchAngleSigmaInRad(gpsimuOrig.getPitchAngleSigmaInRad());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setRollAngleInRad(getDifferentRandValue<double>(gpsimuOrig.getRollAngleInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setRollAngleInRad(gpsimuOrig.getRollAngleInRad());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setRollAngleSigmaInRad(getDifferentRandValue<double>(gpsimuOrig.getRollAngleSigmaInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setRollAngleSigmaInRad(gpsimuOrig.getRollAngleSigmaInRad());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setCrossAccelerationInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getCrossAccelerationInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setCrossAccelerationInMeterPerSecond2(gpsimuOrig.getCrossAccelerationInMeterPerSecond2());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setCrossAccelerationSigmaInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getCrossAccelerationSigmaInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setCrossAccelerationSigmaInMeterPerSecond2(gpsimuOrig.getCrossAccelerationSigmaInMeterPerSecond2());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLongitudinalAccelerationInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getLongitudinalAccelerationInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setLongitudinalAccelerationInMeterPerSecond2(
            gpsimuOrig.getLongitudinalAccelerationInMeterPerSecond2());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLongitudinalAccelerationSigmaInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getLongitudinalAccelerationSigmaInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setLongitudinalAccelerationSigmaInMeterPerSecond2(
            gpsimuOrig.getLongitudinalAccelerationSigmaInMeterPerSecond2());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVerticalAccelerationInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getVerticalAccelerationInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVerticalAccelerationInMeterPerSecond2(gpsimuOrig.getVerticalAccelerationInMeterPerSecond2());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVerticalAccelerationSigmaInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getVerticalAccelerationSigmaInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVerticalAccelerationSigmaInMeterPerSecond2(
            gpsimuOrig.getVerticalAccelerationSigmaInMeterPerSecond2());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityNorthInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityNorthInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityNorthInMeterPerSecond(gpsimuOrig.getVelocityNorthInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityNorthSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityNorthSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityNorthSigmaInMeterPerSecond(gpsimuOrig.getVelocityNorthSigmaInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityWestInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityWestInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityWestInMeterPerSecond(gpsimuOrig.getVelocityWestInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityWestSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityWestSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityWestSigmaInMeterPerSecond(gpsimuOrig.getVelocityWestSigmaInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityUpInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityUpInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityUpInMeterPerSecond(gpsimuOrig.getVelocityUpInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityUpSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityUpSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityUpSigmaInMeterPerSecond(gpsimuOrig.getVelocityUpSigmaInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityXInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityXInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityXInMeterPerSecond(gpsimuOrig.getVelocityXInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityXSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityXSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityXSigmaInMeterPerSecond(gpsimuOrig.getVelocityXSigmaInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityYInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityYInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityYInMeterPerSecond(gpsimuOrig.getVelocityYInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityYSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityYSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityYSigmaInMeterPerSecond(gpsimuOrig.getVelocityYSigmaInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityZInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityZInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityZInMeterPerSecond(gpsimuOrig.getVelocityZInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityZSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityZSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setVelocityZSigmaInMeterPerSecond(gpsimuOrig.getVelocityZSigmaInMeterPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setRollRateInRadPerSecond(getDifferentRandValue<double>(gpsimuOrig.getRollRateInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setRollRateInRadPerSecond(gpsimuOrig.getRollRateInRadPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setRollRateSigmaInRadPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getRollRateSigmaInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setRollRateSigmaInRadPerSecond(gpsimuOrig.getRollRateSigmaInRadPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setYawRateInRadPerSecond(getDifferentRandValue<double>(gpsimuOrig.getYawRateInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setYawRateInRadPerSecond(gpsimuOrig.getYawRateInRadPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setYawRateSigmaInRadPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getYawRateSigmaInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setYawRateSigmaInRadPerSecond(gpsimuOrig.getYawRateSigmaInRadPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setPitchRateInRadPerSecond(getDifferentRandValue<double>(gpsimuOrig.getPitchRateInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setPitchRateInRadPerSecond(gpsimuOrig.getPitchRateInRadPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setPitchRateSigmaInRadPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getPitchRateSigmaInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setPitchRateSigmaInRadPerSecond(gpsimuOrig.getPitchRateSigmaInRadPerSecond());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsStatus(getDifferentRandValue<double>(gpsimuOrig.getGpsStatus()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setGpsStatus(gpsimuOrig.getGpsStatus());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setNoOfSatellites(getDifferentRandValue<uint8_t>(gpsimuOrig.getNoOfSatellites()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setNoOfSatellites(gpsimuOrig.getNoOfSatellites());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsDilutionOfPrecisionX(getDifferentRandValue<double>(gpsimuOrig.getGpsDilutionOfPrecisionX()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setGpsDilutionOfPrecisionX(gpsimuOrig.getGpsDilutionOfPrecisionX());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsDilutionOfPrecisionY(getDifferentRandValue<double>(gpsimuOrig.getGpsDilutionOfPrecisionY()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setGpsDilutionOfPrecisionY(gpsimuOrig.getGpsDilutionOfPrecisionY());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsDilutionOfPrecisionZ(getDifferentRandValue<double>(gpsimuOrig.getGpsDilutionOfPrecisionZ()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setGpsDilutionOfPrecisionZ(gpsimuOrig.getGpsDilutionOfPrecisionZ());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsDilutionOfPrecisionVertical(
            getDifferentRandValue<double>(gpsimuOrig.getGpsDilutionOfPrecisionVertical()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setGpsDilutionOfPrecisionVertical(gpsimuOrig.getGpsDilutionOfPrecisionVertical());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsDilutionOfPrecisionPosition(
            getDifferentRandValue<double>(gpsimuOrig.getGpsDilutionOfPrecisionPosition()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setGpsDilutionOfPrecisionPosition(gpsimuOrig.getGpsDilutionOfPrecisionPosition());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setSource(
            static_cast<GpsImuSource>(getDifferentRandValue<uint8_t>(static_cast<uint8_t>(gpsimuOrig.getSource()))));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setSource(gpsimuOrig.getSource());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setInsQuality(static_cast<GpsImuInsQuality>(
            getDifferentRandValue<uint8_t>(static_cast<uint8_t>(gpsimuOrig.getInsQuality()))));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy.setInsQuality(gpsimuOrig.getInsQuality());
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        // TODO: Reserved?
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoGpsImuAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        GpsImu gpsimuOrig, gpsimuCopy;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        Timestamp tmpTime = gpsimuOrig.getTimestamp();
        do
        {
            gpsimuOrig.setTimestamp(Timestamp(getRandValue<NTPTime>(), getRandValue<NTPTime>()));
        } while ((gpsimuOrig.getTimestamp().getMeasurementTimeEcu().is_not_a_date_time()
                  && tmpTime.getReceivedTimeEcu().is_not_a_date_time())
                 || (gpsimuOrig.getTimestamp() == tmpTime));

        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLatitudeInRad(getDifferentRandValue<double>(gpsimuOrig.getLatitudeInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLatitudeSigmaInMeter(getDifferentRandValue<double>(gpsimuOrig.getLatitudeSigmaInMeter()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLongitudeInRad(getDifferentRandValue<double>(gpsimuOrig.getLongitudeInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLongitudeSigmaInMeter(getDifferentRandValue<double>(gpsimuOrig.getLongitudeSigmaInMeter()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setAltitudeInMeter(getDifferentRandValue<double>(gpsimuOrig.getAltitudeInMeter()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setAltitudeSigmaInMeter(getDifferentRandValue<double>(gpsimuOrig.getAltitudeSigmaInMeter()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setCourseAngleInRad(getDifferentRandValue<double>(gpsimuOrig.getCourseAngleInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setCourseAngleSigmaInRad(getDifferentRandValue<double>(gpsimuOrig.getCourseAngleSigmaInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setYawAngleInRad(getDifferentRandValue<double>(gpsimuOrig.getYawAngleInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setYawAngleSigmaInRad(getDifferentRandValue<double>(gpsimuOrig.getYawAngleSigmaInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setPitchAngleInRad(getDifferentRandValue<double>(gpsimuOrig.getPitchAngleInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setPitchAngleSigmaInRad(getDifferentRandValue<double>(gpsimuOrig.getPitchAngleSigmaInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setRollAngleInRad(getDifferentRandValue<double>(gpsimuOrig.getRollAngleInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setRollAngleSigmaInRad(getDifferentRandValue<double>(gpsimuOrig.getRollAngleSigmaInRad()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setCrossAccelerationInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getCrossAccelerationInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setCrossAccelerationSigmaInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getCrossAccelerationSigmaInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLongitudinalAccelerationInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getLongitudinalAccelerationInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setLongitudinalAccelerationSigmaInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getLongitudinalAccelerationSigmaInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVerticalAccelerationInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getVerticalAccelerationInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVerticalAccelerationSigmaInMeterPerSecond2(
            getDifferentRandValue<double>(gpsimuOrig.getVerticalAccelerationSigmaInMeterPerSecond2()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityNorthInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityNorthInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityNorthSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityNorthSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityWestInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityWestInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityWestSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityWestSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityUpInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityUpInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityUpSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityUpSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityXInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityXInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityXSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityXSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityYInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityYInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityYSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityYSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityZInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityZInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setVelocityZSigmaInMeterPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getVelocityZSigmaInMeterPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setRollRateInRadPerSecond(getDifferentRandValue<double>(gpsimuOrig.getRollRateInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setRollRateSigmaInRadPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getRollRateSigmaInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setYawRateInRadPerSecond(getDifferentRandValue<double>(gpsimuOrig.getYawRateInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setYawRateSigmaInRadPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getYawRateSigmaInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setPitchRateInRadPerSecond(getDifferentRandValue<double>(gpsimuOrig.getPitchRateInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setPitchRateSigmaInRadPerSecond(
            getDifferentRandValue<double>(gpsimuOrig.getPitchRateSigmaInRadPerSecond()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsStatus(getDifferentRandValue<double>(gpsimuOrig.getGpsStatus()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setNoOfSatellites(getDifferentRandValue<uint8_t>(gpsimuOrig.getNoOfSatellites()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsDilutionOfPrecisionX(getDifferentRandValue<double>(gpsimuOrig.getGpsDilutionOfPrecisionX()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsDilutionOfPrecisionY(getDifferentRandValue<double>(gpsimuOrig.getGpsDilutionOfPrecisionY()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsDilutionOfPrecisionZ(getDifferentRandValue<double>(gpsimuOrig.getGpsDilutionOfPrecisionZ()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsDilutionOfPrecisionVertical(
            getDifferentRandValue<double>(gpsimuOrig.getGpsDilutionOfPrecisionVertical()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setGpsDilutionOfPrecisionPosition(
            getDifferentRandValue<double>(gpsimuOrig.getGpsDilutionOfPrecisionPosition()));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setSource(
            static_cast<GpsImuSource>(getDifferentRandValue<uint8_t>(static_cast<uint8_t>(gpsimuOrig.getSource()))));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        gpsimuOrig.setInsQuality(static_cast<GpsImuInsQuality>(
            getDifferentRandValue<uint8_t>(static_cast<uint8_t>(gpsimuOrig.getInsQuality()))));
        BOOST_CHECK(gpsimuOrig != gpsimuCopy);
        gpsimuCopy = gpsimuOrig;
        BOOST_CHECK(gpsimuOrig == gpsimuCopy);

        // TODO: Reserved?
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

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
//!\date Jan 30th, 2019
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/odometry/special/Odometry9002.hpp>
#include "OdometryTestSupport.hpp"
#include <ibeo/common/sdk/datablocks/odometry/special/Odometry9002Exporter9002.hpp>
#include <ibeo/common/sdk/datablocks/odometry/special/Odometry9002Importer9002.hpp>

#include <ibeo/common/sdk/datablocks/odometry/Odometry.hpp>
#include "OdometryTestSupport.hpp"
#include "Odometry9002TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/odometry/OdometryImporter9002.hpp>
#include <ibeo/common/sdk/datablocks/odometry/OdometryExporter9002.hpp>

#define BOOST_TEST_MODULE OdometryTest
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(OdometryBasicTestSuite)

//==============================================================================

class Fixture : public unittests::OdometryTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createOdometry, Fixture)
{
    Odometry odometry;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoOdometryIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const OdometryExporter9002 exporter;
        Odometry odometryGdc(createOdometry<Odometry>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, odometryGdc));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(odometryGdc)), 0, NTPTime());

        Odometry odometry9002;
        BOOST_CHECK(odometryGdc != odometry9002);
        const OdometryImporter9002 importer;
        BOOST_CHECK(importer.deserialize(ss, odometry9002, dh));

        auto result = odometryGdc == odometry9002;
        if (result == false)
            result = odometryGdc == odometry9002;
        BOOST_CHECK(result);
    } // for r
}

//==============================================================================
//Only importer available
BOOST_FIXTURE_TEST_CASE(isIoOdometryIdentity9002, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Odometry9002Exporter9002 exporter9002;
        Odometry9002 odometryOrig(createOdometry<Odometry9002>());

        std::stringstream ss1;

        BOOST_CHECK(exporter9002.serialize(ss1, odometryOrig));

        const IbeoDataHeader dh(
            exporter9002.getDataType(), 0, uint32_t(exporter9002.getSerializedSize(odometryOrig)), 0, NTPTime());

        const OdometryImporter9002 odometryImporter9002;
        Odometry odometry;
        BOOST_CHECK(odometryImporter9002.deserialize(ss1, odometry, dh));
    } // for r
}

//==============================================================================

// The following test checks equality for Odometry9002->Odometry_GDC->Odometry9002
BOOST_FIXTURE_TEST_CASE(isIoOdometryIdentity9002Gdc9002, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Odometry9002 odometry9002orig(createOdometry<Odometry9002>());

        const Odometry9002Exporter9002 exporter;

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, odometry9002orig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(odometry9002orig)), 0, NTPTime());

        Odometry odometryGdc;
        const OdometryImporter9002 importer;
        BOOST_CHECK(importer.deserialize(ss, odometryGdc, dh));

        const OdometryExporter9002 exporter9002;
        BOOST_CHECK(exporter9002.serialize(ss, odometryGdc));
        const IbeoDataHeader dhGdc(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(odometry9002orig)), 0, NTPTime());

        Odometry9002 odometry9002dup;
        BOOST_CHECK(odometry9002orig != odometry9002dup);
        const Odometry9002Importer9002 importer9002_9002;
        BOOST_CHECK(importer9002_9002.deserialize(ss, odometry9002dup, dh));

        BOOST_CHECK(odometry9002orig == odometry9002dup);
    } // for r
}

//==============================================================================

bool operator==(const Odometry& lhs, const Odometry9002& rhs)
{
    return doubleEqual(lhs.getSteeringAngle(), rhs.getSteeringAngle())
           && doubleEqual(lhs.getSteeringWheelAngle(), rhs.getSteeringWheelAngle())
           && doubleEqual(lhs.getSteeringWheelAngleVelocity(), rhs.getSteeringWheelAngleVelocity())
           && doubleEqual(lhs.getWheelSpeedFL(), rhs.getWheelSpeedFL())
           && doubleEqual(lhs.getWheelSpeedFR(), rhs.getWheelSpeedFR())
           && doubleEqual(lhs.getWheelSpeedRL(), rhs.getWheelSpeedRL())
           && doubleEqual(lhs.getWheelSpeedRR(), rhs.getWheelSpeedRR())
           && doubleEqual(lhs.getWheelCircumference(), rhs.getWheelCircumference())
           && doubleEqual(lhs.getVehVelocity(), rhs.getVehVelocity())
           && doubleEqual(lhs.getVehAcceleration(), rhs.getVehAcceleration())
           && doubleEqual(lhs.getVehYawRate(), rhs.getVehYawRate()) && lhs.getTimestamp() == rhs.getTimestamp()
           && floatEqual(lhs.getWheelBase(), rhs.getWheelBase());
}

// The following test checks equality for Odometry9002->Odometry_GDC
BOOST_FIXTURE_TEST_CASE(isIoOdometryIdentity9002Gdc, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Odometry9002Exporter9002 exporter9002;
        Odometry9002 odometry9002;
        OdometryTestSupport::fillRandomly(odometry9002);

        std::stringstream ss;
        BOOST_CHECK(exporter9002.serialize(ss, odometry9002));

        const IbeoDataHeader dh(
            exporter9002.getDataType(), 0, uint32_t(exporter9002.getSerializedSize(odometry9002)), 0, NTPTime());

        Odometry odometryGdc;
        const OdometryImporter9002 importer;
        BOOST_CHECK(importer.deserialize(ss, odometryGdc, dh));

        BOOST_CHECK(odometryGdc == odometry9002);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoOdometryEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Odometry odometryOrig, odometryCopy;
        BOOST_CHECK(odometryOrig == odometryCopy);

        Timestamp tmpTime = odometryOrig.getTimestamp();
        do
        {
            odometryOrig.setTimestamp(Timestamp(getRandValue<NTPTime>(), getRandValue<NTPTime>()));
        } while ((odometryOrig.getTimestamp().getMeasurementTimeEcu().is_not_a_date_time()
                  && tmpTime.getReceivedTimeEcu().is_not_a_date_time())
                 || (odometryOrig.getTimestamp() == tmpTime));

        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setTimestamp(odometryOrig.getTimestamp());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setSteeringAngle(getDifferentRandValue<double>(odometryOrig.getSteeringAngle()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setSteeringAngle(odometryOrig.getSteeringAngle());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setSteeringWheelAngle(getDifferentRandValue<double>(odometryOrig.getSteeringWheelAngle()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setSteeringWheelAngle(odometryOrig.getSteeringWheelAngle());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setSteeringWheelAngleVelocity(
            getDifferentRandValue<double>(odometryOrig.getSteeringWheelAngleVelocity()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setSteeringWheelAngleVelocity(odometryOrig.getSteeringWheelAngleVelocity());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelSpeedFL(getDifferentRandValue<double>(odometryOrig.getWheelSpeedFL()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setWheelSpeedFL(odometryOrig.getWheelSpeedFL());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelSpeedFR(getDifferentRandValue<double>(odometryOrig.getWheelSpeedFR()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setWheelSpeedFR(odometryOrig.getWheelSpeedFR());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelSpeedRL(getDifferentRandValue<double>(odometryOrig.getWheelSpeedRL()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setWheelSpeedRL(odometryOrig.getWheelSpeedRL());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelSpeedRR(getDifferentRandValue<double>(odometryOrig.getWheelSpeedRR()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setWheelSpeedRR(odometryOrig.getWheelSpeedRR());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelCircumference(getDifferentRandValue<double>(odometryOrig.getWheelCircumference()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setWheelCircumference(odometryOrig.getWheelCircumference());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setVehVelocity(getDifferentRandValue<double>(odometryOrig.getVehVelocity()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setVehVelocity(odometryOrig.getVehVelocity());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setVehAcceleration(getDifferentRandValue<double>(odometryOrig.getVehAcceleration()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setVehAcceleration(odometryOrig.getVehAcceleration());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setVehYawRate(getDifferentRandValue<double>(odometryOrig.getVehYawRate()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setVehYawRate(odometryOrig.getVehYawRate());
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelBase(getDifferentRandValue<float>(odometryOrig.getWheelBase()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy.setWheelBase(odometryOrig.getWheelBase());
        BOOST_CHECK(odometryOrig == odometryCopy);

        // TODO: reserved?
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoOdometryAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Odometry odometryOrig, odometryCopy;
        BOOST_CHECK(odometryOrig == odometryCopy);

        Timestamp tmpTime = odometryOrig.getTimestamp();
        do
        {
            odometryOrig.setTimestamp(Timestamp(getRandValue<NTPTime>(), getRandValue<NTPTime>()));
        } while ((odometryOrig.getTimestamp().getMeasurementTimeEcu().is_not_a_date_time()
                  && tmpTime.getReceivedTimeEcu().is_not_a_date_time())
                 || (odometryOrig.getTimestamp() == tmpTime));

        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setSteeringAngle(getDifferentRandValue<double>(odometryOrig.getSteeringAngle()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setSteeringWheelAngle(getDifferentRandValue<double>(odometryOrig.getSteeringWheelAngle()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setSteeringWheelAngleVelocity(
            getDifferentRandValue<double>(odometryOrig.getSteeringWheelAngleVelocity()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelSpeedFL(getDifferentRandValue<double>(odometryOrig.getWheelSpeedFL()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelSpeedFR(getDifferentRandValue<double>(odometryOrig.getWheelSpeedFR()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelSpeedRL(getDifferentRandValue<double>(odometryOrig.getWheelSpeedRL()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelSpeedRR(getDifferentRandValue<double>(odometryOrig.getWheelSpeedRR()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelCircumference(getDifferentRandValue<double>(odometryOrig.getWheelCircumference()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setVehVelocity(getDifferentRandValue<double>(odometryOrig.getVehVelocity()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setVehAcceleration(getDifferentRandValue<double>(odometryOrig.getVehAcceleration()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setVehYawRate(getDifferentRandValue<double>(odometryOrig.getVehYawRate()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        odometryOrig.setWheelBase(getDifferentRandValue<float>(odometryOrig.getWheelBase()));
        BOOST_CHECK(odometryOrig != odometryCopy);
        odometryCopy = odometryOrig;
        BOOST_CHECK(odometryOrig == odometryCopy);

        // TODO: reserved?
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

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
//!\date March 23, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <vehicleStateTests/VehicleStateTestSupport.hpp>

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2805Importer2805.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2805Exporter2805.hpp>

#define BOOST_TEST_MODULE VehicleState2805Test
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(VehicleStateBasicTestSuite2805)

//==============================================================================

class Fixture : public unittests::VehicleStateTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createVehicleStateBasic2805, Fixture)
{
    VehicleState2805 vs;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoVehicleState2805Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const VehicleState2805Exporter2805 exporter;
        VehicleState2805 vsOrig(createVehicleState<VehicleState2805>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, vsOrig));

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(vsOrig)), 0, NTPTime());

        VehicleState2805 vsCopy;
        BOOST_CHECK(vsOrig != vsCopy);
        const VehicleState2805Importer2805 importer;
        BOOST_CHECK(importer.deserialize(ss, vsCopy, dh));
        BOOST_CHECK(vsOrig == vsCopy);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoVehicleState2805Equality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        VehicleState2805 vsOrig, vsCopy;
        BOOST_CHECK(vsOrig == vsCopy);

        NTPTime tmpTime = vsOrig.getTimestamp();
        do
        {
            vsOrig.setTimestamp(getRandValue<NTPTime>());
        } while ((vsOrig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (vsOrig.getTimestamp() == tmpTime));

        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setTimestamp(vsOrig.getTimestamp());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setScanNumber(getDifferentRandValue<uint16_t>(vsOrig.getScanNumber()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setScanNumber(vsOrig.getScanNumber());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setErrorFlags(getDifferentRandValue<uint16_t>(vsOrig.getErrorFlags()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setErrorFlags(vsOrig.getErrorFlags());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalVelocity(getDifferentRandValue<int16_t>(vsOrig.getLongitudinalVelocity()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalVelocity(vsOrig.getLongitudinalVelocity());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteeringWheelAngle(getDifferentRandValue<int16_t>(vsOrig.getSteeringWheelAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setSteeringWheelAngle(vsOrig.getSteeringWheelAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setWheelAngle(getDifferentRandValue<int16_t>(vsOrig.getWheelAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setWheelAngle(vsOrig.getWheelAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setXPosition(getDifferentRandValue<int32_t>(vsOrig.getXPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setXPosition(vsOrig.getXPosition());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYPosition(getDifferentRandValue<int32_t>(vsOrig.getYPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYPosition(vsOrig.getYPosition());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCourseAngle(getDifferentRandValue<int16_t>(vsOrig.getCourseAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCourseAngle(vsOrig.getCourseAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setTimeDiff(getDifferentRandValue<uint16_t>(vsOrig.getTimeDiff()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setTimeDiff(vsOrig.getTimeDiff());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setXDiff(getDifferentRandValue<int16_t>(vsOrig.getXDiff()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setXDiff(vsOrig.getXDiff());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYDiff(getDifferentRandValue<int16_t>(vsOrig.getYDiff()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYDiff(vsOrig.getYDiff());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYaw(getDifferentRandValue<int16_t>(vsOrig.getYaw()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYaw(vsOrig.getYaw());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCurrentYawRate(getDifferentRandValue<int16_t>(vsOrig.getCurrentYawRate()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCurrentYawRate(vsOrig.getCurrentYawRate());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCrossAcceleration(getDifferentRandValue<int16_t>(vsOrig.getCrossAcceleration()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCrossAcceleration(vsOrig.getCrossAcceleration());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCalculationMethod(getDifferentRandValue<uint16_t>(vsOrig.getCalculationMethod()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCalculationMethod(vsOrig.getCalculationMethod());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setReserved2(getDifferentRandValue<uint32_t>(vsOrig.getReserved2()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setReserved2(vsOrig.getReserved2());
        BOOST_CHECK(vsOrig == vsCopy);
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoVehicleState2805Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        VehicleState2805 vsEmpty, vsOrig, vsCopy;
        BOOST_CHECK(vsOrig == vsCopy);
        BOOST_CHECK(vsOrig == vsEmpty);

        NTPTime tmpTime = vsOrig.getTimestamp();
        do
        {
            vsOrig.setTimestamp(getRandValue<NTPTime>());
        } while ((vsOrig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (vsOrig.getTimestamp() == tmpTime));

        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setScanNumber(getDifferentRandValue<uint16_t>(vsOrig.getScanNumber()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setErrorFlags(getDifferentRandValue<uint16_t>(vsOrig.getErrorFlags()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalVelocity(getDifferentRandValue<int16_t>(vsOrig.getLongitudinalVelocity()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteeringWheelAngle(getDifferentRandValue<int16_t>(vsOrig.getSteeringWheelAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setWheelAngle(getDifferentRandValue<int16_t>(vsOrig.getWheelAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setXPosition(getDifferentRandValue<int32_t>(vsOrig.getXPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYPosition(getDifferentRandValue<int32_t>(vsOrig.getYPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCourseAngle(getDifferentRandValue<int16_t>(vsOrig.getCourseAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setTimeDiff(getDifferentRandValue<uint16_t>(vsOrig.getTimeDiff()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setXDiff(getDifferentRandValue<int16_t>(vsOrig.getXDiff()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYDiff(getDifferentRandValue<int16_t>(vsOrig.getYDiff()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYaw(getDifferentRandValue<int16_t>(vsOrig.getYaw()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCurrentYawRate(getDifferentRandValue<int16_t>(vsOrig.getCurrentYawRate()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCrossAcceleration(getDifferentRandValue<int16_t>(vsOrig.getCrossAcceleration()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCalculationMethod(getDifferentRandValue<uint16_t>(vsOrig.getCalculationMethod()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setReserved2(getDifferentRandValue<uint32_t>(vsOrig.getReserved2()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

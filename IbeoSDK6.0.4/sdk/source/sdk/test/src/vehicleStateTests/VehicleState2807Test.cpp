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
#include "VehicleStateTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2807Importer2807.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2807Exporter2807.hpp>

#define BOOST_TEST_MODULE VehicleState2807Test
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(VehicleStateBasicTestSuite2807)

//==============================================================================

class Fixture : public unittests::VehicleStateTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createVehicleStateBasic2807, Fixture)
{
    VehicleState2807 vs;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoVehicleState2807Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const VehicleState2807Exporter2807 exporter;
        VehicleState2807 vsOrig(createVehicleState<VehicleState2807>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, vsOrig));

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(vsOrig)), 0, NTPTime());

        VehicleState2807 vsCopy;
        BOOST_CHECK(vsOrig != vsCopy);
        const VehicleState2807Importer2807 importer;
        BOOST_CHECK(importer.deserialize(ss, vsCopy, dh));
        BOOST_CHECK(vsOrig == vsCopy);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoVehicleState2807Equality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        VehicleState2807 vsOrig, vsCopy;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setMicroseconds(getDifferentRandValue<uint32_t>(vsOrig.getMicroseconds()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setMicroseconds(vsOrig.getMicroseconds());
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

        vsOrig.setXPosition(getDifferentRandValue<int32_t>(vsOrig.getXPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setXPosition(vsOrig.getXPosition());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYPosition(getDifferentRandValue<int32_t>(vsOrig.getYPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYPosition(vsOrig.getYPosition());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCourseAngle(getDifferentRandValue<float>(vsOrig.getCourseAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCourseAngle(vsOrig.getCourseAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalVelocity(getDifferentRandValue<float>(vsOrig.getLongitudinalVelocity()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalVelocity(vsOrig.getLongitudinalVelocity());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYawRate(getDifferentRandValue<float>(vsOrig.getYawRate()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYawRate(vsOrig.getYawRate());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteeringWheelAngle(getDifferentRandValue<float>(vsOrig.getSteeringWheelAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setSteeringWheelAngle(vsOrig.getSteeringWheelAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCrossAcceleration(getDifferentRandValue<float>(vsOrig.getCrossAcceleration()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCrossAcceleration(vsOrig.getCrossAcceleration());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setFrontWheelAngle(getDifferentRandValue<float>(vsOrig.getFrontWheelAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setFrontWheelAngle(vsOrig.getFrontWheelAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setBlindPredictionAge(getDifferentRandValue<uint16_t>(vsOrig.getBlindPredictionAge()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setBlindPredictionAge(vsOrig.getBlindPredictionAge());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehicleWidth(getDifferentRandValue<float>(vsOrig.getVehicleWidth()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setVehicleWidth(vsOrig.getVehicleWidth());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setMinTurningCircle(getDifferentRandValue<float>(vsOrig.getMinTurningCircle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setMinTurningCircle(vsOrig.getMinTurningCircle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehicleFrontToFrontAxle(getDifferentRandValue<float>(vsOrig.getVehicleFrontToFrontAxle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setVehicleFrontToFrontAxle(vsOrig.getVehicleFrontToFrontAxle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setFrontAxleToRearAxle(getDifferentRandValue<float>(vsOrig.getFrontAxleToRearAxle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setFrontAxleToRearAxle(vsOrig.getFrontAxleToRearAxle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setRearAxleToVehicleRear(getDifferentRandValue<float>(vsOrig.getRearAxleToVehicleRear()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRearAxleToVehicleRear(vsOrig.getRearAxleToVehicleRear());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setRearAxleToOrigin(getDifferentRandValue<float>(vsOrig.getRearAxleToOrigin()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRearAxleToOrigin(vsOrig.getRearAxleToOrigin());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteerRatioCoeff0(getDifferentRandValue<float>(vsOrig.getSteerRatioCoeff0()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setSteerRatioCoeff0(vsOrig.getSteerRatioCoeff0());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteerRatioCoeff1(getDifferentRandValue<float>(vsOrig.getSteerRatioCoeff1()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setSteerRatioCoeff1(vsOrig.getSteerRatioCoeff1());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteerRatioCoeff2(getDifferentRandValue<float>(vsOrig.getSteerRatioCoeff2()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setSteerRatioCoeff2(vsOrig.getSteerRatioCoeff2());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteerRatioCoeff3(getDifferentRandValue<float>(vsOrig.getSteerRatioCoeff3()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setSteerRatioCoeff3(vsOrig.getSteerRatioCoeff3());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalAcceleration(getDifferentRandValue<float>(vsOrig.getLongitudinalAcceleration()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalAcceleration(vsOrig.getLongitudinalAcceleration());
        BOOST_CHECK(vsOrig == vsCopy);
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoVehicleState2807Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        VehicleState2807 vsEmpty, vsOrig, vsCopy;
        BOOST_CHECK(vsOrig == vsCopy);
        BOOST_CHECK(vsOrig == vsEmpty);

        vsOrig.setMicroseconds(getDifferentRandValue<uint32_t>(vsOrig.getMicroseconds()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        NTPTime tmpTime = vsOrig.getTimestamp();
        do
        {
            vsOrig.setTimestamp(getRandValue<NTPTime>());
        } while ((vsOrig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (vsOrig.getTimestamp() == tmpTime));

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

        vsOrig.setCourseAngle(getDifferentRandValue<float>(vsOrig.getCourseAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalVelocity(getDifferentRandValue<float>(vsOrig.getLongitudinalVelocity()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYawRate(getDifferentRandValue<float>(vsOrig.getYawRate()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteeringWheelAngle(getDifferentRandValue<float>(vsOrig.getSteeringWheelAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCrossAcceleration(getDifferentRandValue<float>(vsOrig.getCrossAcceleration()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setFrontWheelAngle(getDifferentRandValue<float>(vsOrig.getFrontWheelAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setBlindPredictionAge(getDifferentRandValue<uint16_t>(vsOrig.getBlindPredictionAge()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehicleWidth(getDifferentRandValue<float>(vsOrig.getVehicleWidth()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setMinTurningCircle(getDifferentRandValue<float>(vsOrig.getMinTurningCircle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehicleFrontToFrontAxle(getDifferentRandValue<float>(vsOrig.getVehicleFrontToFrontAxle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setFrontAxleToRearAxle(getDifferentRandValue<float>(vsOrig.getFrontAxleToRearAxle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setRearAxleToVehicleRear(getDifferentRandValue<float>(vsOrig.getRearAxleToVehicleRear()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setRearAxleToOrigin(getDifferentRandValue<float>(vsOrig.getRearAxleToOrigin()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteerRatioCoeff0(getDifferentRandValue<float>(vsOrig.getSteerRatioCoeff0()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteerRatioCoeff1(getDifferentRandValue<float>(vsOrig.getSteerRatioCoeff1()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteerRatioCoeff2(getDifferentRandValue<float>(vsOrig.getSteerRatioCoeff2()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteerRatioCoeff3(getDifferentRandValue<float>(vsOrig.getSteerRatioCoeff3()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalAcceleration(getDifferentRandValue<float>(vsOrig.getLongitudinalAcceleration()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy = vsOrig;
        BOOST_CHECK(vsOrig == vsCopy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

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

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2808Importer2808.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2808Exporter2808.hpp>

#define BOOST_TEST_MODULE VehicleState2808Test
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(VehicleStateBasicTestSuite2808)

//==============================================================================

class Fixture : public unittests::VehicleStateTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createVehicleStateBasic2808, Fixture)
{
    VehicleState2808 vs;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoVehicleState2808Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const VehicleState2808Exporter2808 exporter;
        VehicleState2808 vsOrig(createVehicleState<VehicleState2808>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, vsOrig));

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(vsOrig)), 0, NTPTime());

        VehicleState2808 vsCopy;
        BOOST_CHECK(vsOrig != vsCopy);
        const VehicleState2808Importer2808 importer;
        BOOST_CHECK(importer.deserialize(ss, vsCopy, dh));
        BOOST_CHECK(vsOrig == vsCopy);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoVehicleState2808Equality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        VehicleState2808 vsOrig, vsCopy;
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

        vsOrig.setLatitude(getDifferentRandValue<double>(vsOrig.getLatitude()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLatitude(vsOrig.getLatitude());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLatitudeSigma(getDifferentRandValue<float>(vsOrig.getLatitudeSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLatitudeSigma(vsOrig.getLatitudeSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitude(getDifferentRandValue<double>(vsOrig.getLongitude()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitude(vsOrig.getLongitude());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudeSigma(getDifferentRandValue<float>(vsOrig.getLongitudeSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudeSigma(vsOrig.getLongitudeSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setAltitude(getDifferentRandValue<float>(vsOrig.getAltitude()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setAltitude(vsOrig.getAltitude());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setAltitudeSigma(getDifferentRandValue<float>(vsOrig.getAltitudeSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setAltitudeSigma(vsOrig.getAltitudeSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setXPosition(getDifferentRandValue<double>(vsOrig.getXPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setXPosition(vsOrig.getXPosition());
        BOOST_CHECK(vsOrig == vsCopy);
        vsOrig.setXPositionSigma(getDifferentRandValue<float>(vsOrig.getXPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setXPositionSigma(vsOrig.getXPositionSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYPosition(getDifferentRandValue<double>(vsOrig.getYPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYPosition(vsOrig.getYPosition());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYPositionSigma(getDifferentRandValue<float>(vsOrig.getYPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYPositionSigma(vsOrig.getYPositionSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setZPosition(getDifferentRandValue<float>(vsOrig.getZPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setZPosition(vsOrig.getZPosition());
        BOOST_CHECK(vsOrig == vsCopy);
        vsOrig.setZPositionSigma(getDifferentRandValue<float>(vsOrig.getZPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setZPositionSigma(vsOrig.getZPositionSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setXyCorrelation(getDifferentRandValue<float>(vsOrig.getXyCorrelation()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setXyCorrelation(vsOrig.getXyCorrelation());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setXzCorrelation(getDifferentRandValue<float>(vsOrig.getXzCorrelation()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setXzCorrelation(vsOrig.getXzCorrelation());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYzCorrelation(getDifferentRandValue<float>(vsOrig.getYzCorrelation()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYzCorrelation(vsOrig.getYzCorrelation());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCourseAngle(getDifferentRandValue<float>(vsOrig.getCourseAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCourseAngle(vsOrig.getCourseAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCourseAngleSigma(getDifferentRandValue<float>(vsOrig.getCourseAngleSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCourseAngleSigma(vsOrig.getCourseAngleSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setHeadingAngle(getDifferentRandValue<float>(vsOrig.getHeadingAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setHeadingAngle(vsOrig.getHeadingAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setHeadingAngleSigma(getDifferentRandValue<float>(vsOrig.getHeadingAngleSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setHeadingAngleSigma(vsOrig.getHeadingAngleSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehiclePitchAngle(getDifferentRandValue<float>(vsOrig.getVehiclePitchAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setVehiclePitchAngle(vsOrig.getVehiclePitchAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehiclePitchAngleSigma(getDifferentRandValue<float>(vsOrig.getVehiclePitchAngleSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setVehiclePitchAngleSigma(vsOrig.getVehiclePitchAngleSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehicleRollAngle(getDifferentRandValue<float>(vsOrig.getVehicleRollAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setVehicleRollAngle(vsOrig.getVehicleRollAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehicleRollAngleSigma(getDifferentRandValue<float>(vsOrig.getVehicleRollAngleSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setVehicleRollAngleSigma(vsOrig.getVehicleRollAngleSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalVelocity(getDifferentRandValue<float>(vsOrig.getLongitudinalVelocity()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalVelocity(vsOrig.getLongitudinalVelocity());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalVelocitySigma(getDifferentRandValue<float>(vsOrig.getLongitudinalVelocitySigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalVelocitySigma(vsOrig.getLongitudinalVelocitySigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYawRate(getDifferentRandValue<float>(vsOrig.getYawRate()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYawRate(vsOrig.getYawRate());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYawRateSigma(getDifferentRandValue<float>(vsOrig.getYawRateSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYawRateSigma(vsOrig.getYawRateSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalAcceleration(getDifferentRandValue<float>(vsOrig.getLongitudinalAcceleration()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalAcceleration(vsOrig.getLongitudinalAcceleration());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalAccelerationSigma(
            getDifferentRandValue<float>(vsOrig.getLongitudinalAccelarationSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalAccelerationSigma(vsOrig.getLongitudinalAccelarationSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCrossAcceleration(getDifferentRandValue<float>(vsOrig.getCrossAcceleration()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCrossAcceleration(vsOrig.getCrossAcceleration());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCrossAccelerationSigma(getDifferentRandValue<float>(vsOrig.getCrossAccelerationSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCrossAccelerationSigma(vsOrig.getCrossAccelerationSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteerAngle(getDifferentRandValue<float>(vsOrig.getSteerAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setSteerAngle(vsOrig.getSteerAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteeringWheelAngle(getDifferentRandValue<float>(vsOrig.getSteeringWheelAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setSteeringWheelAngle(vsOrig.getSteeringWheelAngle());
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
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoVehicleState2808Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        VehicleState2808 vsEmpty, vsOrig, vsCopy;
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

        vsOrig.setLatitude(getDifferentRandValue<double>(vsOrig.getLatitude()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLatitude(vsOrig.getLatitude());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLatitudeSigma(getDifferentRandValue<float>(vsOrig.getLatitudeSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLatitudeSigma(vsOrig.getLatitudeSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitude(getDifferentRandValue<double>(vsOrig.getLongitude()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitude(vsOrig.getLongitude());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudeSigma(getDifferentRandValue<float>(vsOrig.getLongitudeSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudeSigma(vsOrig.getLongitudeSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setAltitude(getDifferentRandValue<float>(vsOrig.getAltitude()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setAltitude(vsOrig.getAltitude());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setAltitudeSigma(getDifferentRandValue<float>(vsOrig.getAltitudeSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setAltitudeSigma(vsOrig.getAltitudeSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setXPosition(getDifferentRandValue<double>(vsOrig.getXPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setXPosition(vsOrig.getXPosition());
        BOOST_CHECK(vsOrig == vsCopy);
        vsOrig.setXPositionSigma(getDifferentRandValue<float>(vsOrig.getXPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setXPositionSigma(vsOrig.getXPositionSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYPosition(getDifferentRandValue<double>(vsOrig.getYPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYPosition(vsOrig.getYPosition());
        BOOST_CHECK(vsOrig == vsCopy);
        vsOrig.setYPositionSigma(getDifferentRandValue<float>(vsOrig.getYPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYPositionSigma(vsOrig.getYPositionSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setZPosition(getDifferentRandValue<float>(vsOrig.getZPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setZPosition(vsOrig.getZPosition());
        BOOST_CHECK(vsOrig == vsCopy);
        vsOrig.setZPositionSigma(getDifferentRandValue<float>(vsOrig.getZPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setZPositionSigma(vsOrig.getZPositionSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setXyCorrelation(getDifferentRandValue<float>(vsOrig.getXyCorrelation()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setXyCorrelation(vsOrig.getXyCorrelation());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setXzCorrelation(getDifferentRandValue<float>(vsOrig.getXzCorrelation()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setXzCorrelation(vsOrig.getXzCorrelation());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYzCorrelation(getDifferentRandValue<float>(vsOrig.getYzCorrelation()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYzCorrelation(vsOrig.getYzCorrelation());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCourseAngle(getDifferentRandValue<float>(vsOrig.getCourseAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCourseAngle(vsOrig.getCourseAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCourseAngleSigma(getDifferentRandValue<float>(vsOrig.getCourseAngleSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCourseAngleSigma(vsOrig.getCourseAngleSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setHeadingAngle(getDifferentRandValue<float>(vsOrig.getHeadingAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setHeadingAngle(vsOrig.getHeadingAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setHeadingAngleSigma(getDifferentRandValue<float>(vsOrig.getHeadingAngleSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setHeadingAngleSigma(vsOrig.getHeadingAngleSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehiclePitchAngle(getDifferentRandValue<float>(vsOrig.getVehiclePitchAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setVehiclePitchAngle(vsOrig.getVehiclePitchAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehiclePitchAngleSigma(getDifferentRandValue<float>(vsOrig.getVehiclePitchAngleSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setVehiclePitchAngleSigma(vsOrig.getVehiclePitchAngleSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehicleRollAngle(getDifferentRandValue<float>(vsOrig.getVehicleRollAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setVehicleRollAngle(vsOrig.getVehicleRollAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setVehicleRollAngleSigma(getDifferentRandValue<float>(vsOrig.getVehicleRollAngleSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setVehicleRollAngleSigma(vsOrig.getVehicleRollAngleSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalVelocity(getDifferentRandValue<float>(vsOrig.getLongitudinalVelocity()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalVelocity(vsOrig.getLongitudinalVelocity());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalVelocitySigma(getDifferentRandValue<float>(vsOrig.getLongitudinalVelocitySigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalVelocitySigma(vsOrig.getLongitudinalVelocitySigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYawRate(getDifferentRandValue<float>(vsOrig.getYawRate()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYawRate(vsOrig.getYawRate());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setYawRateSigma(getDifferentRandValue<float>(vsOrig.getYawRateSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setYawRateSigma(vsOrig.getYawRateSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalAcceleration(getDifferentRandValue<float>(vsOrig.getLongitudinalAcceleration()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalAcceleration(vsOrig.getLongitudinalAcceleration());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudinalAccelerationSigma(
            getDifferentRandValue<float>(vsOrig.getLongitudinalAccelarationSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalAccelerationSigma(vsOrig.getLongitudinalAccelarationSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCrossAcceleration(getDifferentRandValue<float>(vsOrig.getCrossAcceleration()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCrossAcceleration(vsOrig.getCrossAcceleration());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setCrossAccelerationSigma(getDifferentRandValue<float>(vsOrig.getCrossAccelerationSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setCrossAccelerationSigma(vsOrig.getCrossAccelerationSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteerAngle(getDifferentRandValue<float>(vsOrig.getSteerAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setSteerAngle(vsOrig.getSteerAngle());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setSteeringWheelAngle(getDifferentRandValue<float>(vsOrig.getSteeringWheelAngle()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setSteeringWheelAngle(vsOrig.getSteeringWheelAngle());
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
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

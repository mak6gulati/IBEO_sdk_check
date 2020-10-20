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
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleStateImporter2805.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2805Importer2805.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleStateExporter2805.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2805Exporter2805.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleStateImporter2808.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleStateExporter2808.hpp>

#define BOOST_TEST_MODULE VehicleStateTest
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(VehicleStateBasicTestSuite)

//==============================================================================

class Fixture : public unittests::VehicleStateTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createVehicleState, Fixture)
{
    VehicleState vs;
    BOOST_CHECK(true);
}

//==============================================================================

//! The following test is commented out, as equality for 2805->VehicleState->2805
//! cannot be met due to type conversions int* -> double and vice versa
//! effected are :: PositionX & PositionY
//!
//! In General, Specialized Containers are used for import/export from/to same
//! data container type.
//!
/*
BOOST_FIXTURE_TEST_CASE(isIoVehicleStateIdentity2805, Fixture)
{
	for (int32_t r = 0; r < nbOfRepeats; ++r)
	{
		VehicleState2805 vsOrig(createVehicleState<VehicleState2805>());

		std::stringstream ss;
		VehicleState2805Exporter2805 exporter2805_2805;
		BOOST_CHECK(exporter2805_2805.serialize(ss, vsOrig));

		const IbeoDataHeader dh(exporter2805_2805.getDataType(),
		                        0, uint32_t(exporter2805_2805.getSerializedSize(vsOrig)),
		                        0,
		                        NTPTime());

		VehicleState vs;
		const VehicleStateImporter2805 importer;
		BOOST_CHECK(importer.deserialize(ss,vs, dh));

		const VehicleStateExporter2805 exporter;
		BOOST_CHECK(exporter.serialize(ss, vs));

		VehicleState2805 vsCopy;
		BOOST_CHECK(vsOrig != vsCopy);
		const VehicleState2805Importer2805 importer2805_2805;
		BOOST_CHECK(importer2805_2805.deserialize(ss,vsCopy, dh));
		BOOST_CHECK(vsOrig != vsCopy);

		//workaround for comparison: Set all member not being exported properly to vehicleState
		vsCopy.setScanNumber(vsOrig.getScanNumber());
		vsCopy.setErrorFlags(vsOrig.getErrorFlags());
		vsCopy.setTimeDiff(vsOrig.getTimeDiff());
		vsCopy.setXDiff(vsOrig.getXDiff());
		vsCopy.setYDiff(vsOrig.getYDiff());
		vsCopy.setYaw(vsOrig.getYaw());
		vsCopy.setReserved0(vsOrig.getReserved0());
		vsCopy.setReserved1(vsOrig.getReserved1());
		vsCopy.setReserved2(vsOrig.getReserved2());

		BOOST_CHECK(vsOrig == vsCopy);
	} // for r
}
*/

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoVehicleStateIdentity2808, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const VehicleStateExporter2808 exporter;
        VehicleState vsOrig(createVehicleState<VehicleState>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, vsOrig));

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(vsOrig)), 0, NTPTime());

        VehicleState vsCopy;
        BOOST_CHECK(vsOrig != vsCopy);
        const VehicleStateImporter2808 importer;
        BOOST_CHECK(importer.deserialize(ss, vsCopy, dh));
        BOOST_CHECK(vsOrig == vsCopy);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoVehicleStateEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        VehicleState vsOrig, vsCopy;
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

        vsOrig.setLatitudeOfOrigin(getDifferentRandValue<double>(vsOrig.getLatitudeOfOrigin()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLatitudeOfOrigin(vsOrig.getLatitudeOfOrigin());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLatitudeOfOriginSigma(getDifferentRandValue<float>(vsOrig.getLatitudeOfOriginSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLatitudeOfOriginSigma(vsOrig.getLatitudeOfOriginSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudeOfOrigin(getDifferentRandValue<double>(vsOrig.getLongitudeOfOrigin()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudeOfOrigin(vsOrig.getLongitudeOfOrigin());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudeOfOriginSigma(getDifferentRandValue<float>(vsOrig.getLongitudeOfOriginSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudeOfOriginSigma(vsOrig.getLongitudeOfOriginSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setAltitudeOfOrigin(getDifferentRandValue<float>(vsOrig.getAltitudeOfOrigin()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setAltitudeOfOrigin(vsOrig.getAltitudeOfOrigin());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setAltitudeOfOriginSigma(getDifferentRandValue<float>(vsOrig.getAltitudeOfOriginSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setAltitudeOfOriginSigma(vsOrig.getAltitudeOfOriginSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setRelativeXPosition(getDifferentRandValue<double>(vsOrig.getRelativeXPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeXPosition(vsOrig.getRelativeXPosition());
        BOOST_CHECK(vsOrig == vsCopy);
        vsOrig.setRelativeXPositionSigma(getDifferentRandValue<float>(vsOrig.getRelativeXPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeXPositionSigma(vsOrig.getRelativeXPositionSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setRelativeYPosition(getDifferentRandValue<double>(vsOrig.getRelativeYPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeYPosition(vsOrig.getRelativeYPosition());
        BOOST_CHECK(vsOrig == vsCopy);
        vsOrig.setRelativeYPositionSigma(getDifferentRandValue<float>(vsOrig.getRelativeYPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeYPositionSigma(vsOrig.getRelativeYPositionSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setRelativeZPosition(getDifferentRandValue<float>(vsOrig.getRelativeZPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeZPosition(vsOrig.getRelativeZPosition());
        BOOST_CHECK(vsOrig == vsCopy);
        vsOrig.setRelativeZPositionSigma(getDifferentRandValue<float>(vsOrig.getRelativeZPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeZPositionSigma(vsOrig.getRelativeZPositionSigma());
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
            getDifferentRandValue<float>(vsOrig.getLongitudinalAccelerationSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalAccelerationSigma(vsOrig.getLongitudinalAccelerationSigma());
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
BOOST_FIXTURE_TEST_CASE(isIoVehicleStateAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        VehicleState vsEmpty, vsOrig, vsCopy;
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

        vsOrig.setLatitudeOfOrigin(getDifferentRandValue<double>(vsOrig.getLatitudeOfOrigin()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLatitudeOfOrigin(vsOrig.getLatitudeOfOrigin());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLatitudeOfOriginSigma(getDifferentRandValue<float>(vsOrig.getLatitudeOfOriginSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLatitudeOfOriginSigma(vsOrig.getLatitudeOfOriginSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudeOfOrigin(getDifferentRandValue<double>(vsOrig.getLongitudeOfOrigin()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudeOfOrigin(vsOrig.getLongitudeOfOrigin());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setLongitudeOfOriginSigma(getDifferentRandValue<float>(vsOrig.getLongitudeOfOriginSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudeOfOriginSigma(vsOrig.getLongitudeOfOriginSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setAltitudeOfOrigin(getDifferentRandValue<float>(vsOrig.getAltitudeOfOrigin()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setAltitudeOfOrigin(vsOrig.getAltitudeOfOrigin());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setAltitudeOfOriginSigma(getDifferentRandValue<float>(vsOrig.getAltitudeOfOriginSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setAltitudeOfOriginSigma(vsOrig.getAltitudeOfOriginSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setRelativeXPosition(getDifferentRandValue<double>(vsOrig.getRelativeXPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeXPosition(vsOrig.getRelativeXPosition());
        BOOST_CHECK(vsOrig == vsCopy);
        vsOrig.setRelativeXPositionSigma(getDifferentRandValue<float>(vsOrig.getRelativeXPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeXPositionSigma(vsOrig.getRelativeXPositionSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setRelativeYPosition(getDifferentRandValue<double>(vsOrig.getRelativeYPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeYPosition(vsOrig.getRelativeYPosition());
        BOOST_CHECK(vsOrig == vsCopy);
        vsOrig.setRelativeYPositionSigma(getDifferentRandValue<float>(vsOrig.getRelativeYPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeYPositionSigma(vsOrig.getRelativeYPositionSigma());
        BOOST_CHECK(vsOrig == vsCopy);

        vsOrig.setRelativeZPosition(getDifferentRandValue<float>(vsOrig.getRelativeZPosition()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeZPosition(vsOrig.getRelativeZPosition());
        BOOST_CHECK(vsOrig == vsCopy);
        vsOrig.setRelativeZPositionSigma(getDifferentRandValue<float>(vsOrig.getRelativeZPositionSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setRelativeZPositionSigma(vsOrig.getRelativeZPositionSigma());
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
            getDifferentRandValue<float>(vsOrig.getLongitudinalAccelerationSigma()));
        BOOST_CHECK(vsOrig != vsCopy);
        vsCopy.setLongitudinalAccelerationSigma(vsOrig.getLongitudinalAccelerationSigma());
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

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
//!\date June 12, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <scanTests/Scan2202TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2202Importer2202.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2202Exporter2202.hpp>

#define BOOST_TEST_MODULE Scan2202Test
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ScanTestSuite2202)

//==============================================================================

class Fixture : public unittests::Scan2202TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createScan2202, Fixture)
{
    Scan2202 scan;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isScan2202Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Scan2202Exporter2202 exporter;
        Scan2202 scanOrig(createScan<Scan2202>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, scanOrig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(scanOrig)), 0, NTPTime());

        Scan2202 scanCopy;
        BOOST_CHECK(scanOrig != scanCopy);
        const Scan2202Importer2202 importer;
        BOOST_CHECK(importer.deserialize(ss, scanCopy, dh));
        BOOST_CHECK(scanOrig == scanCopy);
    } // for r
}

//==============================================================================

//check if StartTimestamp == EndTimestamp
BOOST_FIXTURE_TEST_CASE(isScan2202TimestampsSame, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Scan2202Exporter2202 exporter;
        Scan2202 scanOrig(createScan<Scan2202>());
        scanOrig.setEndTimestamp(scanOrig.getStartTimestamp());
        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, scanOrig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(scanOrig)), 0, NTPTime());

        Scan2202 scanCopy;
        BOOST_CHECK(scanOrig != scanCopy);
        const Scan2202Importer2202 importer;
        BOOST_CHECK(!importer.deserialize(ss, scanCopy, dh));
        BOOST_CHECK(scanOrig != scanCopy);
    } // for r
}

//==============================================================================

//check if StartTimestamp < EndTimestamp
BOOST_FIXTURE_TEST_CASE(isScan2202TimestampStartEndOrder, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Scan2202Exporter2202 exporter;
        Scan2202 scanOrig(createScan<Scan2202>());
        scanOrig.setEndTimestamp(scanOrig.getStartTimestamp() - NTPTime(1));
        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, scanOrig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(scanOrig)), 0, NTPTime());

        Scan2202 scanCopy;
        BOOST_CHECK(scanOrig != scanCopy);
        const Scan2202Importer2202 importer;
        BOOST_CHECK(!importer.deserialize(ss, scanCopy, dh));
        BOOST_CHECK(scanOrig != scanCopy);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoScan2202Equality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan2202 scanOrig, scanCopy;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanNumber(getDifferentRandValue<uint16_t>(scanOrig.getScanNumber()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScanNumber(scanOrig.getScanNumber());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScannerStatus(getDifferentRandValue<uint16_t>(scanOrig.getScannerStatus()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScannerStatus(scanOrig.getScannerStatus());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setSyncPhaseOffset(getDifferentRandValue<uint16_t>(scanOrig.getSyncPhaseOffset()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setSyncPhaseOffset(scanOrig.getSyncPhaseOffset());
        BOOST_CHECK(scanOrig == scanCopy);

        NTPTime tmpTime = scanOrig.getStartTimestamp();
        do
        {
            scanOrig.setStartTimestamp(getRandValue<NTPTime>());
        } while ((scanOrig.getStartTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (scanOrig.getStartTimestamp() == tmpTime));

        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setStartTimestamp(scanOrig.getStartTimestamp());
        BOOST_CHECK(scanOrig == scanCopy);

        tmpTime = scanOrig.getStartTimestamp();
        do
        {
            scanOrig.setEndTimestamp(getRandValue<NTPTime>());
        } while ((scanOrig.getEndTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (scanOrig.getEndTimestamp() == tmpTime));

        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setEndTimestamp(scanOrig.getEndTimestamp());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setAngleTicksPerRotation(getDifferentRandValue<uint16_t>(scanOrig.getAngleTicksPerRotation()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setAngleTicksPerRotation(scanOrig.getAngleTicksPerRotation());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setStartAngleTicks(getDifferentRandValue<int16_t>(scanOrig.getStartAngleTicks()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setStartAngleTicks(scanOrig.getStartAngleTicks());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setEndAngleTicks(getDifferentRandValue<int16_t>(scanOrig.getEndAngleTicks()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setEndAngleTicks(scanOrig.getEndAngleTicks());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionYawAngleTicks(
            getDifferentRandValue<int16_t>(scanOrig.getMountingPositionYawAngleTicks()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setMountingPositionYawAngleTicks(scanOrig.getMountingPositionYawAngleTicks());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionPitchAngleTicks(
            getDifferentRandValue<int16_t>(scanOrig.getMountingPositionPitchAngleTicks()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setMountingPositionPitchAngleTicks(scanOrig.getMountingPositionPitchAngleTicks());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionRollAngleTicks(
            getDifferentRandValue<int16_t>(scanOrig.getMountingPositionRollAngleTicks()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setMountingPositionRollAngleTicks(scanOrig.getMountingPositionRollAngleTicks());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionCmX(getDifferentRandValue<int16_t>(scanOrig.getMountingPositionCmX()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setMountingPositionCmX(scanOrig.getMountingPositionCmX());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionCmY(getDifferentRandValue<int16_t>(scanOrig.getMountingPositionCmY()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setMountingPositionCmY(scanOrig.getMountingPositionCmY());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionCmZ(getDifferentRandValue<int16_t>(scanOrig.getMountingPositionCmZ()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setMountingPositionCmZ(scanOrig.getMountingPositionCmZ());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setFlags(getDifferentRandValue<uint16_t>(scanOrig.getFlags()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setFlags(scanOrig.getFlags());
        BOOST_CHECK(scanOrig == scanCopy);

        uint16_t nbScanPoints = getRandValue<uint16_t>();
        scanOrig.setNumberOfScanPoints(nbScanPoints);
        for (uint16_t i = 0; i < scanOrig.getScanPoints().size(); ++i)
        {
            scanOrig.setScanPoint(i, getRandValue<ScanPointIn2202>());
        }
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setNumberOfScanPoints(nbScanPoints);
        for (uint16_t i = 0; i < scanCopy.getScanPoints().size(); ++i)
        {
            scanCopy.setScanPoint(i, scanOrig.getScanPoints().at(i));
        }
        BOOST_CHECK(scanOrig == scanCopy);
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoScan2202Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan2202 scanOrig, scanCopy;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanNumber(getDifferentRandValue<uint16_t>(scanOrig.getScanNumber()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScannerStatus(getDifferentRandValue<uint16_t>(scanOrig.getScannerStatus()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setSyncPhaseOffset(getDifferentRandValue<uint16_t>(scanOrig.getSyncPhaseOffset()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        NTPTime tmpTime = scanOrig.getStartTimestamp();
        do
        {
            scanOrig.setStartTimestamp(getRandValue<NTPTime>());
        } while ((scanOrig.getStartTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (scanOrig.getStartTimestamp() == tmpTime));

        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        tmpTime = scanOrig.getStartTimestamp();
        do
        {
            scanOrig.setEndTimestamp(getRandValue<NTPTime>());
        } while ((scanOrig.getEndTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (scanOrig.getEndTimestamp() == tmpTime));

        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setAngleTicksPerRotation(getDifferentRandValue<uint16_t>(scanOrig.getAngleTicksPerRotation()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setStartAngleTicks(getDifferentRandValue<int16_t>(scanOrig.getStartAngleTicks()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setEndAngleTicks(getDifferentRandValue<int16_t>(scanOrig.getEndAngleTicks()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionYawAngleTicks(
            getDifferentRandValue<int16_t>(scanOrig.getMountingPositionYawAngleTicks()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionPitchAngleTicks(
            getDifferentRandValue<int16_t>(scanOrig.getMountingPositionPitchAngleTicks()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionRollAngleTicks(
            getDifferentRandValue<int16_t>(scanOrig.getMountingPositionRollAngleTicks()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionCmX(getDifferentRandValue<int16_t>(scanOrig.getMountingPositionCmX()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionCmY(getDifferentRandValue<int16_t>(scanOrig.getMountingPositionCmY()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPositionCmZ(getDifferentRandValue<int16_t>(scanOrig.getMountingPositionCmZ()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setFlags(getDifferentRandValue<uint16_t>(scanOrig.getFlags()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        uint16_t nbScanPoints = getRandValue<uint16_t>();
        scanOrig.setNumberOfScanPoints(nbScanPoints);
        for (uint16_t i = 0; i < scanOrig.getScanPoints().size(); ++i)
        {
            scanOrig.setScanPoint(i, getRandValue<ScanPointIn2202>());
        }
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

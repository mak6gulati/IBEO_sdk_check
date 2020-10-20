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
//!\date June 14, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <scanTests/Scan2208TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2208Importer2208.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2208Exporter2208.hpp>

#include <ibeo/common/sdk/datablocks/MountingPosition.hpp>

#define BOOST_TEST_MODULE Scan2208Test
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ScanTestSuite2208)

//==============================================================================

class Fixture : public unittests::Scan2208TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createScan2208, Fixture)
{
    Scan2208 scan;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isScan2208Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Scan2208Exporter2208 exporter;
        Scan2208 scanOrig(createScan<Scan2208>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, scanOrig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(scanOrig)), 0, NTPTime());

        Scan2208 scanCopy;
        BOOST_CHECK(scanOrig != scanCopy);
        const Scan2208Importer2208 importer;
        BOOST_CHECK(importer.deserialize(ss, scanCopy, dh));
        BOOST_CHECK(scanOrig == scanCopy);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoScan2208Equality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan2208 scanOrig, scanCopy;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanNumber(getDifferentRandValue<uint16_t>(scanOrig.getScanNumber()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScanNumber(scanOrig.getScanNumber());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScannerType(
            ScannerType(getDifferentRandValue<uint8_t>(static_cast<uint8_t>(scanOrig.getScannerType()))));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScannerType(scanOrig.getScannerType());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScannerStatus(getDifferentRandValue<uint16_t>(scanOrig.getScannerStatus()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScannerStatus(scanOrig.getScannerStatus());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setAngleTicksPerRotation(getDifferentRandValue<uint16_t>(scanOrig.getAngleTicksPerRotation()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setAngleTicksPerRotation(scanOrig.getAngleTicksPerRotation());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setProcessingFlags(getDifferentRandValue<uint32_t>(scanOrig.getProcessingFlags()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setProcessingFlags(scanOrig.getProcessingFlags());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPosition(getRandMountingPosition<int16_t>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setMountingPosition(scanOrig.getMountingPosition());
        BOOST_CHECK(scanOrig == scanCopy);

        for (uint8_t i = 0; i < Scan2208::nbOfThresholds; ++i)
        {
            scanOrig.setThreshold(i, getDifferentRandValue<uint16_t>(scanOrig.getThreshold(i)));
            BOOST_CHECK(scanOrig != scanCopy);
            scanCopy.setThreshold(i, scanOrig.getThreshold(i));
            BOOST_CHECK(scanOrig == scanCopy);
        }

        for (uint8_t i = 0; i < Scan2208::nbOfReserved; ++i)
        {
            scanOrig.setReserved(i, getDifferentRandValue<uint8_t>(scanOrig.getReserved(i)));
            BOOST_CHECK(scanOrig != scanCopy);
            scanCopy.setReserved(i, scanOrig.getReserved(i));
            BOOST_CHECK(scanOrig == scanCopy);
        }

        scanOrig.setDeviceId(getDifferentRandValue<uint8_t>(scanOrig.getDeviceId()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setDeviceId(scanOrig.getDeviceId());
        BOOST_CHECK(scanOrig == scanCopy);

        do
        {
            scanOrig.getSubScans() = getRandValue<Scan2208::SubScanVector>();
        } while (scanOrig.getNbOfSubScans() == scanCopy.getNbOfSubScans());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.getSubScans() = scanOrig.getSubScans();
        BOOST_CHECK(scanOrig == scanCopy);
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoScan2208Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan2208 scanOrig, scanCopy;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanNumber(getDifferentRandValue<uint16_t>(scanOrig.getScanNumber()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScannerType(
            ScannerType(getDifferentRandValue<uint8_t>(static_cast<uint8_t>(scanOrig.getScannerType()))));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScannerStatus(getDifferentRandValue<uint16_t>(scanOrig.getScannerStatus()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setAngleTicksPerRotation(getDifferentRandValue<uint16_t>(scanOrig.getAngleTicksPerRotation()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setProcessingFlags(getDifferentRandValue<uint32_t>(scanOrig.getProcessingFlags()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setMountingPosition(getRandMountingPosition<int16_t>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        for (uint8_t i = 0; i < Scan2208::nbOfThresholds; ++i)
        {
            scanOrig.setThreshold(i, getDifferentRandValue<uint16_t>(scanOrig.getThreshold(i)));
            BOOST_CHECK(scanOrig != scanCopy);
            scanCopy = scanOrig;
            BOOST_CHECK(scanOrig == scanCopy);
        }

        for (uint8_t i = 0; i < Scan2208::nbOfReserved; ++i)
        {
            scanOrig.setReserved(i, getDifferentRandValue<uint8_t>(scanOrig.getReserved(i)));
            BOOST_CHECK(scanOrig != scanCopy);
            scanCopy = scanOrig;
            BOOST_CHECK(scanOrig == scanCopy);
        }

        scanOrig.setDeviceId(getDifferentRandValue<uint8_t>(scanOrig.getDeviceId()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        do
        {
            scanOrig.getSubScans() = getRandValue<Scan2208::SubScanVector>();
        } while (scanOrig.getNbOfSubScans() == scanCopy.getNbOfSubScans());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

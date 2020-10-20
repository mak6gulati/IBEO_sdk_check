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
#include <scanTests/Scan2209TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2209Importer2209.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2209Exporter2209.hpp>

#define BOOST_TEST_MODULE Scan2209Test
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ScanTestSuite2209)

//==============================================================================

class Fixture : public unittests::Scan2209TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createScan2209, Fixture)
{
    Scan2209 scan;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isScan2209Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Scan2209Exporter2209 exporter;
        Scan2209 scanOrig(createScan<Scan2209>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, scanOrig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(scanOrig)), 0, NTPTime());

        Scan2209 scanCopy;
        BOOST_CHECK(scanOrig != scanCopy);
        const Scan2209Importer2209 importer;
        BOOST_CHECK(importer.deserialize(ss, scanCopy, dh));
        BOOST_CHECK(scanOrig == scanCopy);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoScan2209Equality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan2209 scanOrig, scanCopy;
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

        scanOrig.setEndTimeOffset(getDifferentRandValue<uint32_t>(scanOrig.getEndTimeOffset()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setEndTimeOffset(scanOrig.getEndTimeOffset());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setFlags(getDifferentRandValue<uint32_t>(scanOrig.getFlags()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setFlags(scanOrig.getFlags());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanNumber(getDifferentRandValue<uint16_t>(scanOrig.getScanNumber()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScanNumber(scanOrig.getScanNumber());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setReserved0(getDifferentRandValue<uint8_t>(scanOrig.getReserved0()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setReserved0(scanOrig.getReserved0());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setReserved1(getDifferentRandValue<uint16_t>(scanOrig.getReserved1()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setReserved1(scanOrig.getReserved1());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScannerInfos(getRandValue<Scan2209::ScannerInfoVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScannerInfos(scanOrig.getScannerInfos());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanPoints(getRandValue<Scan2209::ScanPointVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScanPoints(scanOrig.getScanPoints());
        BOOST_CHECK(scanOrig == scanCopy);
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoScan2209Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan2209 scanOrig, scanCopy;
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

        scanOrig.setEndTimeOffset(getDifferentRandValue<uint32_t>(scanOrig.getEndTimeOffset()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setFlags(getDifferentRandValue<uint32_t>(scanOrig.getFlags()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setFlags(scanOrig.getFlags());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanNumber(getDifferentRandValue<uint16_t>(scanOrig.getScanNumber()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setReserved0(getDifferentRandValue<uint8_t>(scanOrig.getReserved0()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setReserved1(getDifferentRandValue<uint16_t>(scanOrig.getReserved1()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScannerInfos(getRandValue<Scan2209::ScannerInfoVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScannerInfos(scanOrig.getScannerInfos());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanPoints(getRandValue<Scan2209::ScanPointVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScanPoints(scanOrig.getScanPoints());
        BOOST_CHECK(scanOrig == scanCopy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

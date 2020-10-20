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
#include <scanTests/Scan2205TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2205Importer2205.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2205Exporter2205.hpp>

#define BOOST_TEST_MODULE Scan2205Test
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ScanTestSuite2205)

//==============================================================================

class Fixture : public unittests::Scan2205TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createScan2205, Fixture)
{
    Scan2205 scan;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isScan2205Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Scan2205Exporter2205 exporter;
        Scan2205 scanOrig(createScan<Scan2205>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, scanOrig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(scanOrig)), 0, NTPTime());

        Scan2205 scanCopy;
        BOOST_CHECK(scanOrig != scanCopy);
        const Scan2205Importer2205 importer;
        BOOST_CHECK(importer.deserialize(ss, scanCopy, dh));
        BOOST_CHECK(scanOrig == scanCopy);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoScan2205Equality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan2205 scanOrig, scanCopy;
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

        scanOrig.setScannerInfos(getRandValue<Scan2205::ScannerInfoVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScannerInfos(scanOrig.getScannerInfos());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanPoints(getRandValue<Scan2205::ScanPointVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScanPoints(scanOrig.getScanPoints());
        BOOST_CHECK(scanOrig == scanCopy);
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoScan2205Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan2205 scanOrig, scanCopy;
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

        scanOrig.setScannerInfos(getRandValue<Scan2205::ScannerInfoVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScannerInfos(scanOrig.getScannerInfos());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanPoints(getRandValue<Scan2205::ScanPointVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScanPoints(scanOrig.getScanPoints());
        BOOST_CHECK(scanOrig == scanCopy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

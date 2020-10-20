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
//!\date Feb 24, 2017
//------------------------------------------------------------------------------

#include "Scan2310TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/scan/special/Scan2310Exporter2310.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2310Importer2310.hpp>

#define BOOST_TEST_MODULE Scan2310
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(Scan2310TestSuite)

//==============================================================================

class Fixture : public unittests::Scan2310TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(doImpAndExpCalcSameSerSize2310, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan2310 sfrd(createScan2310());

        Scan2310Exporter2310 exporter;
        Scan2310Importer2310 importer;

        BOOST_CHECK(exporter.getSerializedSize(sfrd) == importer.getSerializedSize(sfrd));
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoScan2310Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan2310 sfrdOrig(createScan2310());

        Scan2310Exporter2310 exporter;
        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, sfrdOrig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(sfrdOrig)), 0U, NTPTime());

        Scan2310Importer2310 importer;
        Scan2310 sfrdCopy;
        BOOST_CHECK(importer.deserialize(ss, sfrdCopy, dh));
        BOOST_CHECK(sfrdCopy == sfrdOrig);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkReserved, Fixture)
{
    const Scan2310 sfrd(createScan2310());

    BOOST_CHECK(sfrd.getReserved00() == 0U);
    BOOST_CHECK(sfrd.getReserved01() == 0U);
    BOOST_CHECK(sfrd.getReserved02() == 0U);
    BOOST_CHECK(sfrd.getReserved03() == 0U);
    BOOST_CHECK(sfrd.getReserved04() == 0U);

    BOOST_CHECK(sfrd.getReserved05() == 0U);
    BOOST_CHECK(sfrd.getReserved06() == 0U);

    { // header
        const ScanHeaderIn2310& header{sfrd.getHeader()};
        BOOST_CHECK(header.getReservedHeader7() == 0U);
    } // info

    { // raw info
        const ScanInfoIn2310& rawInfo{sfrd.getInfo()};
        BOOST_CHECK(rawInfo.getReservedInfo7() == 0U);
    } // raw info

    for (auto& p : sfrd.getPoints())
    {
        BOOST_CHECK(p.getReserved() == 0U);
    }

    for (auto& si : sfrd.getSegInfos())
    {
        BOOST_CHECK(si.getReservedSegmentInfo4() == 0U);
        BOOST_CHECK(si.getReservedSegmentInfo5() == 0U);
        BOOST_CHECK(si.getReservedSegmentInfo6() == 0U);
        BOOST_CHECK(si.getReservedSegmentInfo7() == 0U);
    }

    for (auto& dp : sfrd.getDiagPulses())
    {
        BOOST_CHECK(dp.getReserved() == 0U);
    }

    for (auto& rs : sfrd.getRefScans())
    {
        BOOST_CHECK(rs.getReserved() == 0U);
    }

    { // trailer
        const ScanTrailerIn2310& trailer{sfrd.getTrailer()};
        BOOST_CHECK(trailer.getReservedTrailer7() == 0U);
    } // trailer
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

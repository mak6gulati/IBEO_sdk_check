//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Jan 31, 2019
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "OGpsImuMessageTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/ogpsimumessage/OGpsImuMessageImporter2610.hpp>
#include <ibeo/common/sdk/datablocks/ogpsimumessage/OGpsImuMessageExporter2610.hpp>

#define BOOST_TEST_MODULE OGpsImuMessageTest
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(OGpsImuMessageTestSuite)

//==============================================================================

class Fixture : public unittests::OGpsImuMessageTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createOGpsImuMessageImporter2610, Fixture)
{
    ibeo::common::sdk::OGpsImuMessageImporter2610 contSepImporter;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createOGpsImuMessageExporter2610, Fixture)
{
    ibeo::common::sdk::OGpsImuMessageExporter2610 contSepExporter;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isOGpsImuMessageIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const OGpsImuMessageExporter2610 exporter;
        OGpsImuMessage mOrig(createOGpsImuMessage());

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(mOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, mOrig));

        OGpsImuMessage mCopy;
        const OGpsImuMessageImporter2610 importer;
        BOOST_CHECK(importer.deserialize(ss, mCopy, dh));

        BOOST_CHECK(mOrig == mCopy);
    } // for r
}

//==============================================================================

//operator!= and operator==
BOOST_FIXTURE_TEST_CASE(isOGpsImuMessageEqual, Fixture)
{
    OGpsImuMessage ogpsimuOrig;
    OGpsImuMessage ogpsimuCopy;

    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ogpsimuCopy = ogpsimuOrig;
        BOOST_CHECK(ogpsimuOrig == ogpsimuCopy);

        ogpsimuOrig.setIpAddress(getRandValue<uint32_t>());
        BOOST_CHECK(ogpsimuOrig != ogpsimuCopy);
        ogpsimuCopy.setIpAddress(ogpsimuOrig.getIpAddress());
        BOOST_CHECK(ogpsimuOrig == ogpsimuCopy);

        ogpsimuOrig.getData() = getRandValue<std::vector<uint8_t>>();
        BOOST_CHECK(ogpsimuOrig != ogpsimuCopy);
        ogpsimuCopy.getData() = ogpsimuOrig.getData();
        BOOST_CHECK(ogpsimuOrig == ogpsimuCopy);

        fillRandomly(ogpsimuOrig);
    } // for r
}

//==============================================================================

//operator=
BOOST_FIXTURE_TEST_CASE(isOGpsImuMessageAssigned, Fixture)
{
    OGpsImuMessage ogpsimuOrig;
    OGpsImuMessage ogpsimuCopy;
    OGpsImuMessage ogpsimuRandom;

    BOOST_CHECK(ogpsimuOrig == ogpsimuCopy);
    BOOST_CHECK(ogpsimuCopy == ogpsimuRandom);

    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ogpsimuOrig = ogpsimuRandom;
        BOOST_CHECK(ogpsimuOrig == ogpsimuRandom);
        ogpsimuCopy = ogpsimuOrig;
        BOOST_CHECK(ogpsimuRandom == ogpsimuCopy);

        ogpsimuOrig.setIpAddress(getRandValue<uint32_t>());
        BOOST_CHECK(ogpsimuOrig != ogpsimuCopy);
        ogpsimuCopy = ogpsimuOrig;
        BOOST_CHECK(ogpsimuOrig == ogpsimuCopy);
        ogpsimuOrig = ogpsimuRandom;
        BOOST_CHECK(ogpsimuOrig == ogpsimuRandom);
        BOOST_CHECK(ogpsimuCopy != ogpsimuRandom);

        ogpsimuOrig.getData() = getRandValue<std::vector<uint8_t>>();
        BOOST_CHECK(ogpsimuOrig != ogpsimuCopy);
        ogpsimuCopy = ogpsimuOrig;
        BOOST_CHECK(ogpsimuOrig == ogpsimuCopy);

        fillRandomly(ogpsimuOrig);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

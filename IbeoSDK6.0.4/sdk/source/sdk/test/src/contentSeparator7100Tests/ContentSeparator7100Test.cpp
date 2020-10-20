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
//! \date Feb 12, 2018
//------------------------------------------------------------------------------

#include "ContentSeparator7100TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100Importer7100.hpp>
#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100Exporter7100.hpp>

// we link the boost_unit_test_framework library dynamically
#define BOOST_TEST_MODULE ContentSeparator7100Test
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(ContentSeparator7100TestSuite)

//==============================================================================

class Fixture : public unittests::ContentSeparator7100TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isCreateContentSeparator7100Importer7100, Fixture)
{
    ibeo::common::sdk::ContentSeparator7100Importer7100 contSepImporter;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isCreateContentSeparator7100Exporter7100, Fixture)
{
    ibeo::common::sdk::ContentSeparator7100Exporter7100 contSepExporter;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isContentSeparater7100Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ContentSeparator7100Exporter7100 exporter;
        ContentSeparator7100 mOrig(createContentSeparator<ContentSeparator7100>());

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(mOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, mOrig));

        ContentSeparator7100 mCopy;
        const ContentSeparator7100Importer7100 importer;
        BOOST_CHECK(importer.deserialize(ss, mCopy, dh));

        BOOST_CHECK(mOrig == mCopy);
    } // for r
}

//==============================================================================

//operator!= and operator==
BOOST_FIXTURE_TEST_CASE(isContentSeparator7100Equal, Fixture)
{
    ContentSeparator7100 csOrig, csCopy;
    BOOST_CHECK(csOrig == csCopy);

    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        csOrig.setSeparatorType(getDifferentRandValue<ContentSeparatorTypeIn7100>(csCopy.getSeparatorType()));
        BOOST_CHECK(csOrig != csCopy);
        csCopy.setSeparatorType(csOrig.getSeparatorType());
        BOOST_CHECK(csOrig == csCopy);

        csOrig.setContentSize(getDifferentRandValue<uint32_t>(csCopy.getContentSize()));
        BOOST_CHECK(csOrig != csCopy);
        csCopy.setContentSize(csOrig.getContentSize());
        BOOST_CHECK(csOrig == csCopy);
    } // for r
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isContentSeparator7100Assigned, Fixture)
{
    ContentSeparator7100 csOrig, csCopy, csRandom;
    BOOST_CHECK(csOrig == csCopy);
    BOOST_CHECK(csOrig == csRandom);

    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        csOrig = csRandom;
        BOOST_CHECK(csOrig == csRandom);
        csCopy = csOrig;
        BOOST_CHECK(csRandom == csCopy);

        csOrig.setSeparatorType(getDifferentRandValue<ContentSeparatorTypeIn7100>(csCopy.getSeparatorType()));
        BOOST_CHECK(csOrig != csCopy);
        csCopy = csOrig;
        BOOST_CHECK(csOrig == csCopy);
        csOrig = csRandom;
        BOOST_CHECK(csOrig == csRandom);
        BOOST_CHECK(csCopy != csRandom);

        csOrig.setContentSize(getDifferentRandValue<uint32_t>(csCopy.getContentSize()));
        BOOST_CHECK(csOrig != csCopy);
        csCopy = csOrig;
        BOOST_CHECK(csOrig == csCopy);
        csOrig = csRandom;
        BOOST_CHECK(csOrig == csRandom);
        BOOST_CHECK(csOrig != csCopy);

        fillRandomly(csOrig);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

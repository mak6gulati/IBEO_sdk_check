//==============================================================================
//!\file
//!
//! Tests for General Data Container CONTENTSEPARATOR
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Feb 4, 2019
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100.hpp>
#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100Exporter7100.hpp>
#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100Importer7100.hpp>

#include <ibeo/common/sdk/datablocks/contentseparator/ContentSeparator.hpp>
#include "ContentSeparatorTestSupport.hpp"
#include "ContentSeparator7100TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/contentseparator/ContentSeparatorImporter7100.hpp>
#include <ibeo/common/sdk/datablocks/contentseparator/ContentSeparatorExporter7100.hpp>

#define BOOST_TEST_MODULE GpsImuTest
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ContentSeparatorBasicTestSuite)

//==============================================================================

class Fixture : public unittests::ContentSeparatorTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createContentSeparator, Fixture)
{
    ContentSeparator contentSeparator;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoContentSeparatorIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ContentSeparatorExporter7100 exporter;
        ContentSeparator contentseparatorGdc(createContentSeparator<ContentSeparator>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, contentseparatorGdc));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(contentseparatorGdc)), 0, NTPTime());

        ContentSeparator contentSeparator7100;
        BOOST_CHECK(contentseparatorGdc != contentSeparator7100);
        const ContentSeparatorImporter7100 importer;
        BOOST_CHECK(importer.deserialize(ss, contentSeparator7100, dh));

        BOOST_CHECK(contentseparatorGdc == contentSeparator7100);
    } // for r
}

//==============================================================================
//Only importer available
BOOST_FIXTURE_TEST_CASE(isIoContentSeparatorIdentity7100, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ContentSeparator7100Exporter7100 exporter7100;
        ContentSeparator7100 contentSeparatorOrig(createContentSeparator<ContentSeparator7100>());

        std::stringstream ss1;

        BOOST_CHECK(exporter7100.serialize(ss1, contentSeparatorOrig));

        const IbeoDataHeader dh(exporter7100.getDataType(),
                                0,
                                uint32_t(exporter7100.getSerializedSize(contentSeparatorOrig)),
                                0,
                                NTPTime());

        const ContentSeparatorImporter7100 contentSeparatorImporter7100;
        ContentSeparator contentseparator;
        BOOST_CHECK(contentSeparatorImporter7100.deserialize(ss1, contentseparator, dh));
    } // for r
}

//==============================================================================

// The following test checks equality for ContentSeparator7100->ContentSeparator_GDC->ContentSeparator7100
BOOST_FIXTURE_TEST_CASE(isIoContentSeparatorIdentity7100Gdc7100, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ContentSeparator7100 contentSeparator7100orig(createContentSeparator<ContentSeparator7100>());

        const ContentSeparator7100Exporter7100 exporter;

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, contentSeparator7100orig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(contentSeparator7100orig)), 0, NTPTime());

        ContentSeparator contentSeparatorGdc;
        const ContentSeparatorImporter7100 importer;
        BOOST_CHECK(importer.deserialize(ss, contentSeparatorGdc, dh));

        const ContentSeparatorExporter7100 exporter7100;
        BOOST_CHECK(exporter7100.serialize(ss, contentSeparatorGdc));
        const IbeoDataHeader dhGdc(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(contentSeparator7100orig)), 0, NTPTime());

        ContentSeparator7100 contentSeparator7100dup;
        BOOST_CHECK(contentSeparator7100orig != contentSeparator7100dup);
        const ContentSeparator7100Importer7100 importer7100_7100;
        BOOST_CHECK(importer7100_7100.deserialize(ss, contentSeparator7100dup, dh));

        BOOST_CHECK(contentSeparator7100orig == contentSeparator7100dup);
    } // for r
}

//==============================================================================

bool operator==(const ContentSeparator& lhs, const ContentSeparator7100& rhs)
{
    return (lhs.getSeparatorType() == rhs.getSeparatorType()) && (lhs.getContentSize() == rhs.getContentSize());
}

// The following test checks equality for ContentSeparator7100->ContentSeparator_GDC
BOOST_FIXTURE_TEST_CASE(isIoContentSeparatorIdentity7100Gdc, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ContentSeparator7100Exporter7100 exporter7100;
        ContentSeparator7100 contentSeparator7100;
        ContentSeparatorTestSupport::fillRandomly(contentSeparator7100);

        std::stringstream ss;
        BOOST_CHECK(exporter7100.serialize(ss, contentSeparator7100));

        const IbeoDataHeader dh(exporter7100.getDataType(),
                                0,
                                uint32_t(exporter7100.getSerializedSize(contentSeparator7100)),
                                0,
                                NTPTime());

        ContentSeparator contentSeparatorGdc;
        const ContentSeparatorImporter7100 importer;
        BOOST_CHECK(importer.deserialize(ss, contentSeparatorGdc, dh));

        BOOST_CHECK(contentSeparatorGdc == contentSeparator7100);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoContentSeparatorEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ContentSeparator contentSeparatorOrig, contentSeparatorCopy;
        BOOST_CHECK(contentSeparatorOrig == contentSeparatorCopy);

        contentSeparatorCopy.setContentSize(getDifferentRandValue(contentSeparatorCopy.getContentSize()));
        BOOST_CHECK(contentSeparatorOrig != contentSeparatorCopy);
        contentSeparatorCopy.setContentSize(contentSeparatorOrig.getContentSize());
        BOOST_CHECK(contentSeparatorOrig == contentSeparatorCopy);

        contentSeparatorCopy.setSeparatorType(getDifferentRandValue(contentSeparatorCopy.getSeparatorType()));
        BOOST_CHECK(contentSeparatorOrig != contentSeparatorCopy);
        contentSeparatorCopy.setSeparatorType(contentSeparatorOrig.getSeparatorType());
        BOOST_CHECK(contentSeparatorOrig == contentSeparatorCopy);
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoContentSeparatorAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ContentSeparator contentSeparatorOrig, contentSeparatorCopy;
        BOOST_CHECK(contentSeparatorOrig == contentSeparatorCopy);

        contentSeparatorCopy.setContentSize(getDifferentRandValue(contentSeparatorCopy.getContentSize()));
        BOOST_CHECK(contentSeparatorOrig != contentSeparatorCopy);
        contentSeparatorCopy = contentSeparatorOrig;
        BOOST_CHECK(contentSeparatorOrig == contentSeparatorCopy);

        contentSeparatorCopy.setSeparatorType(getDifferentRandValue(contentSeparatorCopy.getSeparatorType()));
        BOOST_CHECK(contentSeparatorOrig != contentSeparatorCopy);
        contentSeparatorCopy = contentSeparatorOrig;
        BOOST_CHECK(contentSeparatorOrig == contentSeparatorCopy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

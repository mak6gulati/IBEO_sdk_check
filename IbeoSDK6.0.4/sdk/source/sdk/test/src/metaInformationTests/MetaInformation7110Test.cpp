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
//! \date Feb 02, 2018
//------------------------------------------------------------------------------

#include "MetaInformation7110TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationList7110Exporter7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationList7110Importer7110.hpp>

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationAppBaseConfigIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationEcuIdIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationKeywordsIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationUnsupportedIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationVersionNumberIn7110.hpp>

#define BOOST_TEST_MODULE MetaInformationTest
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(MetaInformationListSuite)

//==============================================================================

class Fixture : public unittests::MetaInformationTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(creationAppBaseConfig, Fixture)
{
    MetaInformationAppBaseConfigIn7110 abcOrig;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentityAppBaseConfig, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationAppBaseConfigIn7110 abcOrig;
        fillRandomly(abcOrig);

        std::stringstream ss;
        BOOST_CHECK(abcOrig.serialize(ss));

        MetaInformationAppBaseConfigIn7110 abcCopy;
        BOOST_CHECK(abcCopy.deserialize(ss));

        BOOST_CHECK(abcOrig == abcCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentityEcuId, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationEcuIdIn7110 ecuIdOrig;
        fillRandomly(ecuIdOrig);

        std::stringstream ss;
        BOOST_CHECK(ecuIdOrig.serialize(ss));

        MetaInformationEcuIdIn7110 ecuIdCopy;
        BOOST_CHECK(ecuIdCopy.deserialize(ss));

        BOOST_CHECK(ecuIdOrig == ecuIdCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentityKeywords, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationKeywordsIn7110 kwOrig;
        fillRandomly(kwOrig);

        std::stringstream ss;
        BOOST_CHECK(kwOrig.serialize(ss));

        MetaInformationKeywordsIn7110 kwCopy;
        BOOST_CHECK(kwCopy.deserialize(ss));

        BOOST_CHECK(kwOrig == kwCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentityUnsupported, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationUnsupportedIn7110 unsOrig(0, NTPTime(), 0);
        fillRandomly(unsOrig);

        std::stringstream ss;
        BOOST_CHECK(unsOrig.serialize(ss));

        MetaInformationUnsupportedIn7110 unsCopy(0, NTPTime(), 0);
        BOOST_CHECK(unsCopy.deserialize(ss));

        BOOST_CHECK(unsOrig == unsCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentityVersionNumber, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationVersionNumberIn7110 vnOrig;
        fillRandomly(vnOrig);

        std::stringstream ss;
        BOOST_CHECK(vnOrig.serialize(ss));

        MetaInformationVersionNumberIn7110 vnCopy;
        BOOST_CHECK(vnCopy.deserialize(ss));

        BOOST_CHECK(vnOrig == vnCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadWriteUnsupported, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationList7110 milOrig(
            MetaInformationTestSupport::createMIL(MetaInformationBaseIn7110::MetaInformationType::Unsupported));
        const MetaInformationList7110Exporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList7110 milCopy;
        const MetaInformationList7110Importer7110 importer;
        BOOST_CHECK(importer.deserialize(ss, milCopy, dh));

        //		std::cerr << "Orig: " << std::endl;
        //		milOrig.printStatistic(std::cerr);
        //		std::cerr << "Copy: " << std::endl;
        //		milCopy.printStatistic(std::cerr);

        BOOST_CHECK(milOrig == milCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadWriteVersionNumber, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationList7110 milOrig(
            MetaInformationTestSupport::createMIL(MetaInformationBaseIn7110::MetaInformationType::VersionNumber));
        const MetaInformationList7110Exporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList7110 milCopy;
        const MetaInformationList7110Importer7110 importer;
        BOOST_CHECK(importer.deserialize(ss, milCopy, dh));

        BOOST_CHECK(milOrig == milCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadWriteAppBaseConfig, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationList7110 milOrig(
            MetaInformationTestSupport::createMIL(MetaInformationBaseIn7110::MetaInformationType::AppBaseConfig));
        const MetaInformationList7110Exporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList7110 milCopy;
        const MetaInformationList7110Importer7110 importer;
        BOOST_CHECK(importer.deserialize(ss, milCopy, dh));

        BOOST_CHECK(milOrig == milCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadWriteEcuId, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationList7110 milOrig(
            MetaInformationTestSupport::createMIL(MetaInformationBaseIn7110::MetaInformationType::EcuId));
        const MetaInformationList7110Exporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList7110 milCopy;
        const MetaInformationList7110Importer7110 importer;
        BOOST_CHECK(importer.deserialize(ss, milCopy, dh));

        BOOST_CHECK(milOrig == milCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadWriteKeywords, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationList7110 milOrig(
            MetaInformationTestSupport::createMIL(MetaInformationBaseIn7110::MetaInformationType::Keywords));
        const MetaInformationList7110Exporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList7110 milCopy;
        const MetaInformationList7110Importer7110 importer;
        BOOST_CHECK(importer.deserialize(ss, milCopy, dh));

        BOOST_CHECK(milOrig == milCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentity, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationList7110 milOrig(MetaInformationTestSupport::createMIL());
        const MetaInformationList7110Exporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList7110 milCopy;
        const MetaInformationList7110Importer7110 importer;
        BOOST_CHECK(importer.deserialize(ss, milCopy, dh));

        BOOST_CHECK(milOrig == milCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

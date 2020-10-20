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

#include "MetaInformationTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationListExporter7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationListImporter7110.hpp>

#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationAppBaseConfig.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationEcuId.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationKeywords.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationUnsupported.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationVersionNumber.hpp>

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
    MetaInformationAppBaseConfig abcOrig;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentityAppBaseConfig, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationAppBaseConfig abcOrig;
        fillRandomly(abcOrig);

        std::stringstream ss;
        BOOST_CHECK(abcOrig.serialize(ss));

        MetaInformationAppBaseConfig abcCopy;
        BOOST_CHECK(abcCopy.deserialize(ss));

        BOOST_CHECK(abcOrig == abcCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentityEcuId, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationEcuId ecuIdOrig;
        fillRandomly(ecuIdOrig);

        std::stringstream ss;
        BOOST_CHECK(ecuIdOrig.serialize(ss));

        MetaInformationEcuId ecuIdCopy;
        BOOST_CHECK(ecuIdCopy.deserialize(ss));

        BOOST_CHECK(ecuIdOrig == ecuIdCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentityKeywords, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationKeywords kwOrig;
        fillRandomly(kwOrig);

        std::stringstream ss;
        BOOST_CHECK(kwOrig.serialize(ss));

        MetaInformationKeywords kwCopy;
        BOOST_CHECK(kwCopy.deserialize(ss));

        BOOST_CHECK(kwOrig == kwCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentityUnsupported, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationUnsupported unsOrig(0, NTPTime(), 0);
        fillRandomly(unsOrig);

        std::stringstream ss;
        BOOST_CHECK(unsOrig.serialize(ss));

        MetaInformationUnsupported unsCopy(0, NTPTime(), 0);
        BOOST_CHECK(unsCopy.deserialize(ss));

        BOOST_CHECK(unsOrig == unsCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentityVersionNumber, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationVersionNumber vnOrig;
        fillRandomly(vnOrig);

        std::stringstream ss;
        BOOST_CHECK(vnOrig.serialize(ss));

        MetaInformationVersionNumber vnCopy;
        BOOST_CHECK(vnCopy.deserialize(ss));

        BOOST_CHECK(vnOrig == vnCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadWriteUnsupported, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationList milOrig(
            MetaInformationTestSupport::createMIL(MetaInformationBase::MetaInformationType::Unsupported));
        const MetaInformationListExporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList milCopy;
        const MetaInformationListImporter7110 importer;
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
        MetaInformationList milOrig(
            MetaInformationTestSupport::createMIL(MetaInformationBase::MetaInformationType::VersionNumber));
        const MetaInformationListExporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList milCopy;
        const MetaInformationListImporter7110 importer;
        BOOST_CHECK(importer.deserialize(ss, milCopy, dh));

        BOOST_CHECK(milOrig == milCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadWriteAppBaseConfig, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationList milOrig(
            MetaInformationTestSupport::createMIL(MetaInformationBase::MetaInformationType::AppBaseConfig));
        const MetaInformationListExporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList milCopy;
        const MetaInformationListImporter7110 importer;
        BOOST_CHECK(importer.deserialize(ss, milCopy, dh));

        BOOST_CHECK(milOrig == milCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadWriteEcuId, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationList milOrig(
            MetaInformationTestSupport::createMIL(MetaInformationBase::MetaInformationType::EcuId));
        const MetaInformationListExporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList milCopy;
        const MetaInformationListImporter7110 importer;
        BOOST_CHECK(importer.deserialize(ss, milCopy, dh));

        BOOST_CHECK(milOrig == milCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadWriteKeywords, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationList milOrig(
            MetaInformationTestSupport::createMIL(MetaInformationBase::MetaInformationType::Keywords));
        const MetaInformationListExporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList milCopy;
        const MetaInformationListImporter7110 importer;
        BOOST_CHECK(importer.deserialize(ss, milCopy, dh));

        BOOST_CHECK(milOrig == milCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentity, Fixture)
{
    for (int r = 0; r < nbOfRepeats; ++r)
    {
        MetaInformationList milOrig(MetaInformationTestSupport::createMIL());
        const MetaInformationListExporter7110 exporter;

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(milOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, milOrig));

        MetaInformationList milCopy;
        const MetaInformationListImporter7110 importer;
        BOOST_CHECK(importer.deserialize(ss, milCopy, dh));

        BOOST_CHECK(milOrig == milCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

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
//! \date Apr 3, 2018
//------------------------------------------------------------------------------
#include "TimeRelationsListTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9010Importer9010.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9010Exporter9010.hpp>

#define BOOST_TEST_MODULE TimeRelationsListTest
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(TimeRelationsList9010TestSuite)

//==============================================================================

class Fixture : public unittests::TimeRelationsListTestSupport
{
}; // Fixture

//==============================================================================

// Test: create an empty timerelation list
BOOST_FIXTURE_TEST_CASE(createTimeRelationList9010, Fixture)
{
    ibeo::common::sdk::TimeRelationsList9010 trl9010;
    BOOST_CHECK(trl9010.getTimeRelations().size() == 0);
}

//==============================================================================

// Test: create an empty timerelation
BOOST_FIXTURE_TEST_CASE(createTimeRelation9010, Fixture)
{
    ibeo::common::sdk::TimeRelationIn9010 tr9010;
    BOOST_CHECK(tr9010.getEntryList().size() == 0);
}

//==============================================================================

// Test: create an empty importer
BOOST_FIXTURE_TEST_CASE(createTimeRelation9010Importer, Fixture)
{
    ibeo::common::sdk::TimeRelationsList9010Importer9010 importer;
    BOOST_CHECK(true);
}

//==============================================================================

// Test: create an empty exporter
BOOST_FIXTURE_TEST_CASE(createTimeRelation9010Exporter, Fixture)
{
    ibeo::common::sdk::TimeRelationsList9010Exporter9010 importer;
    BOOST_CHECK(true);
}

//==============================================================================

// Test: create an empty timerelation list
BOOST_FIXTURE_TEST_CASE(ioTimeRelationList9010Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ibeo::common::sdk::TimeRelationsList9010Exporter9010 exporter;
        ibeo::common::sdk::TimeRelationsList9010 trl9010Orig = createTimeRelationsList9010C(false);

        const ibeo::common::sdk::IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(trl9010Orig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, trl9010Orig));

        ibeo::common::sdk::TimeRelationsList9010 trl9010Copy;

        const ibeo::common::sdk::TimeRelationsList9010Importer9010 importer;
        BOOST_CHECK(importer.deserialize(ss, trl9010Copy, dh));

        BOOST_CHECK(trl9010Copy == trl9010Orig);
    }
}

//==============================================================================

//operator!= and operator==
BOOST_FIXTURE_TEST_CASE(isContentTimeRelationsList9010Equal, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ibeo::common::sdk::TimeRelationsList9010 trlOrig;
        ibeo::common::sdk::TimeRelationsList9010 trlCopy;
        BOOST_CHECK(trlOrig == trlCopy);

        trlOrig = createTimeRelationsList9010C(false);

        BOOST_CHECK(trlOrig != trlCopy);

        const TimeRelationsList9010::TimeRelationMap& timeRelMap = trlOrig.getTimeRelations();
        TimeRelationsList9010::TimeRelationMap copyMap;

        for (const auto& tr9010 : timeRelMap)
        {
            BOOST_CHECK(trlOrig != trlCopy);
            copyMap[tr9010.first]      = tr9010.second;
            trlCopy.getTimeRelations() = copyMap;
        }

        BOOST_CHECK(trlOrig == trlCopy);

        const uint16_t pos = getRandValue<uint16_t>(
            0, static_cast<uint16_t>(trlCopy.getTimeRelations().begin()->second.getEntryList().size() - 1));

        // deleting random entry in first relation
        trlCopy.getTimeRelations().begin()->second.getEntryList().erase(
            trlCopy.getTimeRelations().begin()->second.getEntryList().begin() + pos);

        BOOST_CHECK(trlOrig != trlCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

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
//! \date Apr 6, 2018
//------------------------------------------------------------------------------
#include "TimeRelationsListTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9011Importer9011.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9011Exporter9011.hpp>

#define BOOST_TEST_MODULE TimeRelationsListTest
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(TimeRelationsList9011TestSuite)

//==============================================================================

class Fixture : public unittests::TimeRelationsListTestSupport
{
}; // Fixture

//==============================================================================

// Test: create an empty timerelation list
BOOST_FIXTURE_TEST_CASE(createTimeRelationList9011, Fixture)
{
    ibeo::common::sdk::TimeRelationsList9011 trl9011;
    BOOST_CHECK(true);
    BOOST_CHECK(trl9011.getTimeRelations().size() == 0);
}

//==============================================================================

// Test: create an empty timerelation
BOOST_FIXTURE_TEST_CASE(createTimeRelation9011, Fixture)
{
    ibeo::common::sdk::TimeRelationIn9011 tr9011;
    BOOST_CHECK(true);
    BOOST_CHECK(tr9011.getEntryList().size() == 0);
}

//==============================================================================

// Test: create an empty importer
BOOST_FIXTURE_TEST_CASE(createTimeRelation9011Importer, Fixture)
{
    ibeo::common::sdk::TimeRelationsList9011Importer9011 importer;
    BOOST_CHECK(true);
}

//==============================================================================

// Test: create an empty exporter
BOOST_FIXTURE_TEST_CASE(createTimeRelation9011Exporter, Fixture)
{
    ibeo::common::sdk::TimeRelationsList9011Exporter9011 importer;
    BOOST_CHECK(true);
}

//==============================================================================

// Test: create an empty timerelation list
BOOST_FIXTURE_TEST_CASE(ioTimeRelationList9011Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ibeo::common::sdk::TimeRelationsList9011Exporter9011 exporter;
        ibeo::common::sdk::TimeRelationsList9011 trl9011Orig = createTimeRelationsList9011C(false, false);
        BOOST_CHECK(true);

        const ibeo::common::sdk::IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(trl9011Orig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, trl9011Orig));

        ibeo::common::sdk::TimeRelationsList9011 trl9011Copy;

        const ibeo::common::sdk::TimeRelationsList9011Importer9011 importer;
        BOOST_CHECK(importer.deserialize(ss, trl9011Copy, dh));

        BOOST_CHECK(trl9011Copy == trl9011Orig);
    }
}

//==============================================================================

//operator!= and operator==
BOOST_FIXTURE_TEST_CASE(isContentTimeRelationsList9011Equal, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ibeo::common::sdk::TimeRelationsList9011 trlOrig;
        ibeo::common::sdk::TimeRelationsList9011 trlCopy;
        BOOST_CHECK(trlOrig == trlCopy);

        trlOrig = createTimeRelationsList9011C();

        BOOST_CHECK(trlOrig != trlCopy);

        const TimeRelationsList9011::TimeRelationVector& timeRelVec = trlOrig.getTimeRelations();
        TimeRelationsList9011::TimeRelationVector copyVec;
        TimeRelationIn9011 tr9011;
        for (size_t i = 0; i < timeRelVec.size(); ++i)
        {
            tr9011.setOtherClock(timeRelVec[i].getOtherClock());
            tr9011.setEntryList(timeRelVec[i].getEntryList());
            copyVec.push_back(tr9011);
            trlCopy.getTimeRelations() = copyVec;
            BOOST_CHECK(trlOrig != trlCopy);
        }

        // not equal as reference clock is not set
        BOOST_CHECK(trlOrig != trlCopy);
        trlCopy.setRefClock(trlOrig.getRefClock());
        BOOST_CHECK(trlOrig == trlCopy);

        const uint16_t pos
            = getRandValue<uint16_t>(0, static_cast<uint16_t>(trlCopy.getTimeRelations()[0].getEntryList().size() - 1));

        // deleting random entry in first relation
        trlCopy.getTimeRelations()[0].getEntryList().erase(trlCopy.getTimeRelations()[0].getEntryList().begin() + pos);

        BOOST_CHECK(trlOrig != trlCopy);
    } // for r
}

//==============================================================================

//operator!= and operator==
BOOST_FIXTURE_TEST_CASE(isContentIdenticalTimeRelationsList9011Equal, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ibeo::common::sdk::TimeRelationsList9011 trlOrig, trlCopy;
        BOOST_CHECK(trlOrig == trlCopy);

        trlOrig = createTimeRelationsList9011C();
        if (trlOrig.getTimeRelations().size() < 2)
        {
            continue;
        }

        BOOST_CHECK(trlOrig != trlCopy);

        trlCopy.setRefClock(trlOrig.getRefClock());

        const TimeRelationsList9011::TimeRelationVector& timeRelVec = trlOrig.getTimeRelations();
        TimeRelationsList9011::TimeRelationVector copyVec;
        TimeRelationIn9011 tr9011;

        for (size_t i = 0; i < timeRelVec.size(); ++i)
        {
            tr9011.setOtherClock(timeRelVec[timeRelVec.size() - 1 - i].getOtherClock());
            tr9011.setEntryList(timeRelVec[timeRelVec.size() - 1 - i].getEntryList());
            copyVec.push_back(tr9011);
        }
        trlCopy.getTimeRelations() = copyVec;
        BOOST_CHECK(trlOrig != trlCopy);

        trlCopy = trlOrig;
        BOOST_CHECK(trlOrig == trlCopy);

    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

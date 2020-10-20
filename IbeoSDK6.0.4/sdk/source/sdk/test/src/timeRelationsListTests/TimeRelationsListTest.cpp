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
//! \date Mar 22, 2018
//------------------------------------------------------------------------------
#include "TimeRelationsListTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/timerelation/TimeRelationsListImporter9010.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/TimeRelationsListImporter9011.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9011Importer9011.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/TimeRelationsListExporter9011.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9010Exporter9010.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9011Exporter9011.hpp>

#define BOOST_TEST_MODULE TimeRelationsListTest
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(TimeRelationsListTestSuite)

//==============================================================================

class Fixture : public unittests::TimeRelationsListTestSupport
{
}; // Fixture

//==============================================================================

//******************************************************************************
//******************************************************************************
//******************                                      **********************
//****************** General snippet functions unit tests **********************
//******************                                      **********************
//******************************************************************************
//******************************************************************************

// Test: create an empty timerelation
BOOST_FIXTURE_TEST_CASE(createTimeRelationObject, Fixture)
{
    BOOST_CHECK(m_trEmpty.isEmpty());
    BOOST_CHECK(m_trEmpty.getEntryList().size() == 0);
    BOOST_CHECK(!m_trSimple.isEmpty());
    BOOST_CHECK(!m_trUnambiguousWithGap.isEmpty());
    BOOST_CHECK(!m_trClockChange.isEmpty());
    BOOST_CHECK(!m_trAmbiguousNoGap.isEmpty());
    BOOST_CHECK(!m_trAmbiguousWithGap.isEmpty());
}

//==============================================================================

// Test: calculate factor function
BOOST_FIXTURE_TEST_CASE(TimeRelationCalculateFactor, Fixture)
{
    // normal case
    double res = ibeo::common::sdk::TimeRelation::calculateFactor(r1, r2, o1, o3);
    BOOST_CHECK(ibeo::common::sdk::fuzzyCompareT<7>(res, 2.0));
    BOOST_CHECK(!ibeo::common::sdk::fuzzyCompareT<7>(res, 4.0));
    // -ve values
    res = ibeo::common::sdk::TimeRelation::calculateFactor(r2, r1, o1, o3);
    BOOST_CHECK(ibeo::common::sdk::fuzzyCompareT<7>(res, -2.0));
    res = ibeo::common::sdk::TimeRelation::calculateFactor(r2Plus500Micro, r1, o1, o3);
    BOOST_CHECK(ibeo::common::sdk::fuzzyCompareT<7>(res, -1.3333333));
}

//==============================================================================

// Test: isAmbiguous function
BOOST_FIXTURE_TEST_CASE(TimeRelationAmbiguous, Fixture)
{
    BOOST_CHECK(!m_trEmpty.isAmbiguous());
    BOOST_CHECK(!m_trSimple.isAmbiguous());
    BOOST_CHECK(!m_trClockChange.isAmbiguous());
    BOOST_CHECK(!m_trUnambiguousWithGap.isAmbiguous());

    BOOST_CHECK(m_trAmbiguousNoGap.isAmbiguous());
    BOOST_CHECK(m_trAmbiguousWithGap.isAmbiguous());
}

//==============================================================================

// Test: hasRefGap
BOOST_FIXTURE_TEST_CASE(TimeRelationHasRefGap, Fixture)
{
    BOOST_CHECK(!m_trEmpty.hasRefGap());
    BOOST_CHECK(!m_trSimple.hasRefGap());
    BOOST_CHECK(!m_trAmbiguousNoGap.hasRefGap());
    BOOST_CHECK(!m_trClockChange.hasRefGap());

    BOOST_CHECK(m_trUnambiguousWithGap.hasRefGap());
    BOOST_CHECK(m_trAmbiguousWithGap.hasRefGap());
}

//==============================================================================

// Test: Ref time ranges
BOOST_FIXTURE_TEST_CASE(TimeRelationRefTimeRanges, Fixture)
{
    RefTimeRangeVector refRanges;
    BOOST_CHECK(m_trEmpty.getRefTimeRanges() == RefTimeRangeVector());
    BOOST_CHECK(m_trSimple.getRefTimeRanges() == RefTimeRangeVector{RefTimeRange(r1, r9)});
    BOOST_CHECK(m_trClockChange.getRefTimeRanges() == RefTimeRangeVector{RefTimeRange(r1, r9)});
    // Note: this case is a little unusual: though there are no gaps,
    // there are multiple time-ranges, because there is an OtherTime reset.
    refRanges = {RefTimeRange(r1, r2), RefTimeRange(r2Plus1Micro, r6)};
    BOOST_CHECK(m_trAmbiguousNoGap.getRefTimeRanges() == refRanges);
    refRanges.clear();
    refRanges = {RefTimeRange(r1, r2), RefTimeRange(r5, r6), RefTimeRange(r8, r9)};
    BOOST_CHECK(m_trAmbiguousWithGap.getRefTimeRanges() == refRanges);
    refRanges.clear();
    refRanges = {RefTimeRange(r1, r2), RefTimeRange(r8, r9)};
    BOOST_CHECK(m_trUnambiguousWithGap.getRefTimeRanges() == refRanges);
}

//==============================================================================

// Test: min ref time
BOOST_FIXTURE_TEST_CASE(TimeRelationMinRefTime, Fixture)
{
    BOOST_CHECK(m_trEmpty.minRefTime() == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trSimple.minRefTime() == r1);
    BOOST_CHECK(m_trClockChange.minRefTime() == r1);
    BOOST_CHECK(m_trAmbiguousNoGap.minRefTime() == r1);
    BOOST_CHECK(m_trAmbiguousWithGap.minRefTime() == r1);
    BOOST_CHECK(m_trUnambiguousWithGap.minRefTime() == r1);
}

//==============================================================================

// Test: max ref time
BOOST_FIXTURE_TEST_CASE(TimeRelationMaxRefTime, Fixture)
{
    BOOST_CHECK(m_trEmpty.maxRefTime() == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trSimple.maxRefTime() == r9);
    BOOST_CHECK(m_trClockChange.maxRefTime() == r9);
    BOOST_CHECK(m_trAmbiguousNoGap.maxRefTime() == r6);
    BOOST_CHECK(m_trAmbiguousWithGap.maxRefTime() == r9);
    BOOST_CHECK(m_trUnambiguousWithGap.maxRefTime() == r9);
}

//==============================================================================

// Test: hasotherGap
BOOST_FIXTURE_TEST_CASE(TimeRelationHasOtherGap, Fixture)
{
    BOOST_CHECK(!m_trEmpty.hasOtherGap());
    BOOST_CHECK(!m_trSimple.hasOtherGap());
    BOOST_CHECK(!m_trAmbiguousNoGap.hasOtherGap());
    BOOST_CHECK(!m_trClockChange.hasOtherGap());

    BOOST_CHECK(m_trUnambiguousWithGap.hasOtherGap());
    BOOST_CHECK(m_trAmbiguousWithGap.hasOtherGap());
}

//==============================================================================

// Test: other time ranges
BOOST_FIXTURE_TEST_CASE(TimeRelationOtherTimeRanges, Fixture)
{
    OtherTimeRangeVector othRanges;
    BOOST_CHECK(m_trEmpty.getOtherTimeRanges() == othRanges);
    BOOST_CHECK(m_trSimple.getOtherTimeRanges() == OtherTimeRangeVector{OtherTimeRange(o0, o10)});
    BOOST_CHECK(m_trClockChange.getOtherTimeRanges() == OtherTimeRangeVector{OtherTimeRange(o0, o10)});
    othRanges = {OtherTimeRange(o0, o3), OtherTimeRange(o0, o3)};
    BOOST_CHECK(m_trAmbiguousNoGap.getOtherTimeRanges() == othRanges);
    // Note: this case is a little unusual: though there are no gaps,
    // there are multiple time-ranges, because there is an OtherTime reset.
    othRanges = {OtherTimeRange(o0, o3), OtherTimeRange(o0, o3), OtherTimeRange(o6, o10)};
    BOOST_CHECK(m_trAmbiguousWithGap.getOtherTimeRanges() == othRanges);
    othRanges = {OtherTimeRange(o0, o3), OtherTimeRange(o6, o10)};
    BOOST_CHECK(m_trUnambiguousWithGap.getOtherTimeRanges() == othRanges);
}

//==============================================================================

// Test: min other time
BOOST_FIXTURE_TEST_CASE(TimeRelationMinOtherTime, Fixture)
{
    BOOST_CHECK(m_trEmpty.minOtherTime() == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trSimple.minOtherTime() == o0);
    BOOST_CHECK(m_trClockChange.minOtherTime() == o0);
    BOOST_CHECK(m_trAmbiguousNoGap.minOtherTime() == o0);
    BOOST_CHECK(m_trAmbiguousWithGap.minOtherTime() == o0);
    BOOST_CHECK(m_trUnambiguousWithGap.minOtherTime() == o0);
}

//==============================================================================

// Test: max other time
BOOST_FIXTURE_TEST_CASE(TimeRelationMaxOtherTime, Fixture)
{
    BOOST_CHECK(m_trEmpty.maxOtherTime() == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trSimple.maxOtherTime() == o10);
    BOOST_CHECK(m_trClockChange.maxOtherTime() == o10);
    BOOST_CHECK(m_trAmbiguousNoGap.maxOtherTime() == o3);
    BOOST_CHECK(m_trAmbiguousWithGap.maxOtherTime() == o10);
    BOOST_CHECK(m_trUnambiguousWithGap.maxOtherTime() == o10);
}

//==============================================================================

// Test: get unambiguous ranges
BOOST_FIXTURE_TEST_CASE(TimeRelationUnambiguousTimeRange, Fixture)
{
    RefTimeRangeVector unAmbRefRanges;
    BOOST_CHECK_THROW(m_trEmpty.getUnambiguousRange(r1), std::domain_error);
    BOOST_CHECK_THROW(m_trEmpty.getUnambiguousRange(r5), std::domain_error);

    BOOST_CHECK(m_trSimple.getUnambiguousRange(r1) == RefTimeRange(r1, r9));
    BOOST_CHECK(m_trSimple.getUnambiguousRange(r9) == RefTimeRange(r1, r9));
    BOOST_CHECK(m_trSimple.getUnambiguousRange(r5) == RefTimeRange(r1, r9));
    BOOST_CHECK_THROW(m_trSimple.getUnambiguousRange(r0), std::domain_error);
    BOOST_CHECK_THROW(m_trSimple.getUnambiguousRange(r20), std::domain_error);

    BOOST_CHECK(m_trAmbiguousNoGap.getUnambiguousRange(r2) == RefTimeRange(r1, r2));
    BOOST_CHECK(m_trAmbiguousNoGap.getUnambiguousRange(r2Plus1Micro) == RefTimeRange(r2Plus1Micro, r6));
    BOOST_CHECK_THROW(m_trAmbiguousNoGap.getUnambiguousRange(r0), std::domain_error);
    BOOST_CHECK_THROW(m_trAmbiguousNoGap.getUnambiguousRange(r9), std::domain_error);

    BOOST_CHECK(m_trAmbiguousWithGap.getUnambiguousRange(r2) == RefTimeRange(r1, r2));
    BOOST_CHECK(m_trAmbiguousWithGap.getUnambiguousRange(r5) == RefTimeRange(r5, r6));
    BOOST_CHECK(m_trAmbiguousWithGap.getUnambiguousRange(r8) == RefTimeRange(r8, r9));
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.getUnambiguousRange(r0), std::domain_error);
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.getUnambiguousRange(r3), std::domain_error);
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.getUnambiguousRange(r7), std::domain_error);
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.getUnambiguousRange(r10), std::domain_error);

    BOOST_CHECK(m_trUnambiguousWithGap.getUnambiguousRange(r2) == RefTimeRange(r1, r2));
    BOOST_CHECK(m_trUnambiguousWithGap.getUnambiguousRange(r8) == RefTimeRange(r8, r9));
    BOOST_CHECK_THROW(m_trUnambiguousWithGap.getUnambiguousRange(r0), std::domain_error);
    BOOST_CHECK_THROW(m_trUnambiguousWithGap.getUnambiguousRange(r3), std::domain_error);
    BOOST_CHECK_THROW(m_trUnambiguousWithGap.getUnambiguousRange(r10), std::domain_error);
}

//==============================================================================

// Test: get unambiguous ranges "No Throw"
BOOST_FIXTURE_TEST_CASE(TimeRelationUnambiguousTimeRangeNoThrow, Fixture)
{
    RefTimeRangeVector unAmbRefRanges;
    BOOST_CHECK(m_trEmpty.getUnambiguousRangeNoThrow(r1) == ibeo::common::sdk::timerelation::invalidRefTimeRange());
    BOOST_CHECK(m_trEmpty.getUnambiguousRangeNoThrow(r5) == ibeo::common::sdk::timerelation::invalidRefTimeRange());

    BOOST_CHECK(m_trSimple.getUnambiguousRangeNoThrow(r1) == RefTimeRange(r1, r9));
    BOOST_CHECK(m_trSimple.getUnambiguousRangeNoThrow(r9) == RefTimeRange(r1, r9));
    BOOST_CHECK(m_trSimple.getUnambiguousRangeNoThrow(r5) == RefTimeRange(r1, r9));
    BOOST_CHECK(m_trSimple.getUnambiguousRangeNoThrow(r0) == ibeo::common::sdk::timerelation::invalidRefTimeRange());
    BOOST_CHECK(m_trSimple.getUnambiguousRangeNoThrow(r20) == ibeo::common::sdk::timerelation::invalidRefTimeRange());

    BOOST_CHECK(m_trAmbiguousNoGap.getUnambiguousRangeNoThrow(r2) == RefTimeRange(r1, r2));
    BOOST_CHECK(m_trAmbiguousNoGap.getUnambiguousRangeNoThrow(r2Plus1Micro) == RefTimeRange(r2Plus1Micro, r6));
    BOOST_CHECK(m_trAmbiguousNoGap.getUnambiguousRangeNoThrow(r0)
                == ibeo::common::sdk::timerelation::invalidRefTimeRange());
    BOOST_CHECK(m_trAmbiguousNoGap.getUnambiguousRangeNoThrow(r9)
                == ibeo::common::sdk::timerelation::invalidRefTimeRange());

    BOOST_CHECK(m_trAmbiguousWithGap.getUnambiguousRangeNoThrow(r2) == RefTimeRange(r1, r2));
    BOOST_CHECK(m_trAmbiguousWithGap.getUnambiguousRangeNoThrow(r5) == RefTimeRange(r5, r6));
    BOOST_CHECK(m_trAmbiguousWithGap.getUnambiguousRangeNoThrow(r8) == RefTimeRange(r8, r9));
    BOOST_CHECK(m_trAmbiguousWithGap.getUnambiguousRangeNoThrow(r0)
                == ibeo::common::sdk::timerelation::invalidRefTimeRange());
    BOOST_CHECK(m_trAmbiguousWithGap.getUnambiguousRangeNoThrow(r3)
                == ibeo::common::sdk::timerelation::invalidRefTimeRange());
    BOOST_CHECK(m_trAmbiguousWithGap.getUnambiguousRangeNoThrow(r7)
                == ibeo::common::sdk::timerelation::invalidRefTimeRange());
    BOOST_CHECK(m_trAmbiguousWithGap.getUnambiguousRangeNoThrow(r10)
                == ibeo::common::sdk::timerelation::invalidRefTimeRange());

    BOOST_CHECK(m_trUnambiguousWithGap.getUnambiguousRangeNoThrow(r2) == RefTimeRange(r1, r2));
    BOOST_CHECK(m_trUnambiguousWithGap.getUnambiguousRangeNoThrow(r8) == RefTimeRange(r8, r9));
    BOOST_CHECK(m_trUnambiguousWithGap.getUnambiguousRangeNoThrow(r0)
                == ibeo::common::sdk::timerelation::invalidRefTimeRange());
    BOOST_CHECK(m_trUnambiguousWithGap.getUnambiguousRangeNoThrow(r3)
                == ibeo::common::sdk::timerelation::invalidRefTimeRange());
    BOOST_CHECK(m_trUnambiguousWithGap.getUnambiguousRangeNoThrow(r10)
                == ibeo::common::sdk::timerelation::invalidRefTimeRange());
}

//==============================================================================

// Test: convert ref time to other time
BOOST_FIXTURE_TEST_CASE(TimeRelationConvertRetToOther, Fixture)
{
    BOOST_CHECK_THROW(m_trEmpty.convert(r1), std::domain_error);
    BOOST_CHECK_THROW(m_trEmpty.convert(r5), std::domain_error);

    BOOST_CHECK(m_trSimple.convert(r1) == o0);
    BOOST_CHECK(m_trSimple.convert(r5) == o5);
    BOOST_CHECK(m_trSimple.convert(r9) == o10);
    BOOST_CHECK_THROW(m_trSimple.convert(r0), std::domain_error);
    BOOST_CHECK_THROW(m_trSimple.convert(r10), std::domain_error);

    BOOST_CHECK(m_trClockChange.convert(r1) == o0);
    BOOST_CHECK(m_trClockChange.convert(r2) == o3);
    BOOST_CHECK(m_trClockChange.convert(r9) == o10);
    BOOST_CHECK_THROW(m_trClockChange.convert(r0), std::domain_error);
    BOOST_CHECK_THROW(m_trClockChange.convert(r10), std::domain_error);

    BOOST_CHECK(m_trAmbiguousNoGap.convert(r1) == o0);
    BOOST_CHECK(m_trAmbiguousNoGap.convert(r2) == o3);
    BOOST_CHECK(m_trAmbiguousNoGap.convert(r2Plus1Micro) == o0);
    BOOST_CHECK(m_trAmbiguousNoGap.convert(r6) == o3);
    BOOST_CHECK_THROW(m_trAmbiguousNoGap.convert(r0), std::domain_error);
    BOOST_CHECK_THROW(m_trAmbiguousNoGap.convert(r10), std::domain_error);

    BOOST_CHECK(m_trAmbiguousWithGap.convert(r1) == o0);
    BOOST_CHECK(m_trAmbiguousWithGap.convert(r2) == o3);
    BOOST_CHECK(m_trAmbiguousWithGap.convert(r5) == o0);
    BOOST_CHECK(m_trAmbiguousWithGap.convert(r6) == o3);
    BOOST_CHECK(m_trAmbiguousWithGap.convert(r8) == o6);
    BOOST_CHECK(m_trAmbiguousWithGap.convert(r9) == o10);
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.convert(r0), std::domain_error);
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.convert(r4), std::domain_error);
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.convert(r7), std::domain_error);
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.convert(r10), std::domain_error);

    BOOST_CHECK(m_trUnambiguousWithGap.convert(r1) == o0);
    BOOST_CHECK(m_trUnambiguousWithGap.convert(r2) == o3);
    BOOST_CHECK(m_trUnambiguousWithGap.convert(r8) == o6);
    BOOST_CHECK(m_trUnambiguousWithGap.convert(r9) == o10);
    BOOST_CHECK_THROW(m_trUnambiguousWithGap.convert(r0), std::domain_error);
    BOOST_CHECK_THROW(m_trUnambiguousWithGap.convert(r5), std::domain_error);
    BOOST_CHECK_THROW(m_trUnambiguousWithGap.convert(r7), std::domain_error);
    BOOST_CHECK_THROW(m_trUnambiguousWithGap.convert(r10), std::domain_error);
}

//==============================================================================

// Test: convert ref time to other time "NO Throw"
BOOST_FIXTURE_TEST_CASE(TimeRelationConvertRetToOthernoThrow, Fixture)
{
    BOOST_CHECK(m_trEmpty.convertNoThrow(r1) == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trEmpty.convertNoThrow(r5) == ibeo::common::sdk::timerelation::invalidOtherTime());

    BOOST_CHECK(m_trSimple.convertNoThrow(r1) == o0);
    BOOST_CHECK(m_trSimple.convertNoThrow(r5) == o5);
    BOOST_CHECK(m_trSimple.convertNoThrow(r9) == o10);
    BOOST_CHECK(m_trSimple.convertNoThrow(r0) == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trSimple.convertNoThrow(r10) == ibeo::common::sdk::timerelation::invalidOtherTime());

    BOOST_CHECK(m_trClockChange.convertNoThrow(r1) == o0);
    BOOST_CHECK(m_trClockChange.convertNoThrow(r2) == o3);
    BOOST_CHECK(m_trClockChange.convertNoThrow(r9) == o10);
    BOOST_CHECK(m_trClockChange.convertNoThrow(r0) == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trClockChange.convertNoThrow(r10) == ibeo::common::sdk::timerelation::invalidOtherTime());

    BOOST_CHECK(m_trAmbiguousNoGap.convertNoThrow(r1) == o0);
    BOOST_CHECK(m_trAmbiguousNoGap.convertNoThrow(r2) == o3);
    BOOST_CHECK(m_trAmbiguousNoGap.convertNoThrow(r2Plus1Micro) == o0);
    BOOST_CHECK(m_trAmbiguousNoGap.convertNoThrow(r6) == o3);
    BOOST_CHECK(m_trAmbiguousNoGap.convertNoThrow(r0) == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trAmbiguousNoGap.convertNoThrow(r10) == ibeo::common::sdk::timerelation::invalidOtherTime());

    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(r1) == o0);
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(r2) == o3);
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(r5) == o0);
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(r6) == o3);
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(r8) == o6);
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(r9) == o10);
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(r0) == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(r4) == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(r7) == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(r10) == ibeo::common::sdk::timerelation::invalidOtherTime());

    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(r1) == o0);
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(r2) == o3);
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(r8) == o6);
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(r9) == o10);
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(r0) == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(r5) == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(r7) == ibeo::common::sdk::timerelation::invalidOtherTime());
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(r10) == ibeo::common::sdk::timerelation::invalidOtherTime());
}

//==============================================================================

// Test: convert other time to ref time
BOOST_FIXTURE_TEST_CASE(TimeRelationConvertOtherToRef, Fixture)
{
    BOOST_CHECK_THROW(m_trEmpty.convert(o1), std::domain_error);
    BOOST_CHECK_THROW(m_trEmpty.convert(o5), std::domain_error);

    BOOST_CHECK(m_trSimple.convert(o0) == r1);
    BOOST_CHECK(m_trSimple.convert(o5) == r5);
    BOOST_CHECK(m_trSimple.convert(o10) == r9);
    BOOST_CHECK_THROW(m_trSimple.convert(om4), std::domain_error);
    BOOST_CHECK_THROW(m_trSimple.convert(o15), std::domain_error);

    BOOST_CHECK(m_trClockChange.convert(o0) == r1);
    BOOST_CHECK(m_trClockChange.convert(o3) == r2);
    BOOST_CHECK(m_trClockChange.convert(o3Plus1Micro) == r2Plus1Micro);
    BOOST_CHECK(m_trClockChange.convert(o10) == r9);
    BOOST_CHECK_THROW(m_trClockChange.convert(om4), std::domain_error);
    BOOST_CHECK_THROW(m_trClockChange.convert(o15), std::domain_error);

    BOOST_CHECK_THROW(m_trAmbiguousNoGap.convert(o0), std::runtime_error);
    BOOST_CHECK_THROW(m_trAmbiguousNoGap.convert(o3), std::runtime_error);
    BOOST_CHECK_THROW(m_trAmbiguousNoGap.convert(om4), std::domain_error);
    BOOST_CHECK_THROW(m_trAmbiguousNoGap.convert(o15), std::domain_error);

    BOOST_CHECK_THROW(m_trAmbiguousWithGap.convert(o0), std::runtime_error);
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.convert(o3), std::runtime_error);
    BOOST_CHECK(m_trAmbiguousWithGap.convert(o6) == r8);
    BOOST_CHECK(m_trAmbiguousWithGap.convert(o10) == r9);
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.convert(om4), std::domain_error);
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.convert(o3Plus1Micro), std::domain_error);
    BOOST_CHECK_THROW(m_trAmbiguousWithGap.convert(o15), std::domain_error);

    BOOST_CHECK(m_trUnambiguousWithGap.convert(o0) == r1);
    BOOST_CHECK(m_trUnambiguousWithGap.convert(o3) == r2);
    BOOST_CHECK(m_trUnambiguousWithGap.convert(o6) == r8);
    BOOST_CHECK(m_trUnambiguousWithGap.convert(o10) == r9);
    BOOST_CHECK_THROW(m_trUnambiguousWithGap.convert(om4), std::domain_error);
    BOOST_CHECK_THROW(m_trUnambiguousWithGap.convert(o3Plus1Micro), std::domain_error);
    BOOST_CHECK_THROW(m_trUnambiguousWithGap.convert(o15), std::domain_error);
}

//==============================================================================

// Test: convert other time to ref time "NO Throw"
BOOST_FIXTURE_TEST_CASE(TimeRelationConvertOtherToRefnoThrow, Fixture)
{
    BOOST_CHECK(m_trEmpty.convertNoThrow(o1) == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trEmpty.convertNoThrow(o5) == ibeo::common::sdk::timerelation::invalidRefTime());

    BOOST_CHECK(m_trSimple.convertNoThrow(o0) == r1);
    BOOST_CHECK(m_trSimple.convertNoThrow(o5) == r5);
    BOOST_CHECK(m_trSimple.convertNoThrow(o10) == r9);
    BOOST_CHECK(m_trSimple.convertNoThrow(om4) == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trSimple.convertNoThrow(o15) == ibeo::common::sdk::timerelation::invalidRefTime());

    BOOST_CHECK(m_trClockChange.convertNoThrow(o0) == r1);
    BOOST_CHECK(m_trClockChange.convertNoThrow(o3) == r2);
    BOOST_CHECK(m_trClockChange.convertNoThrow(o3Plus1Micro) == r2Plus1Micro);
    BOOST_CHECK(m_trClockChange.convertNoThrow(o10) == r9);
    BOOST_CHECK(m_trClockChange.convertNoThrow(om4) == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trClockChange.convertNoThrow(o15) == ibeo::common::sdk::timerelation::invalidRefTime());

    BOOST_CHECK(m_trAmbiguousNoGap.convertNoThrow(o0) == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trAmbiguousNoGap.convertNoThrow(o3) == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trAmbiguousNoGap.convertNoThrow(om4) == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trAmbiguousNoGap.convertNoThrow(o15) == ibeo::common::sdk::timerelation::invalidRefTime());

    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(o0) == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(o3) == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(o6) == r8);
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(o10) == r9);
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(om4) == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(o3Plus1Micro) == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trAmbiguousWithGap.convertNoThrow(o15) == ibeo::common::sdk::timerelation::invalidRefTime());

    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(o0) == r1);
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(o3) == r2);
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(o6) == r8);
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(o10) == r9);
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(om4) == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(o3Plus1Micro)
                == ibeo::common::sdk::timerelation::invalidRefTime());
    BOOST_CHECK(m_trUnambiguousWithGap.convertNoThrow(o15) == ibeo::common::sdk::timerelation::invalidRefTime());
}

//******************************************************************************
//******************************************************************************
//***************                                             ******************
//*************** General data container functions unit tests ******************
//***************                                             ******************
//******************************************************************************
//******************************************************************************

// Test: create an empty timerelation list
BOOST_FIXTURE_TEST_CASE(createEmptyTimeRelationList, Fixture)
{
    ibeo::common::sdk::TimeRelationsList trl;
    BOOST_CHECK(true);
    BOOST_CHECK(trl.getTimeRelations().size() == 0);
}

//==============================================================================

// Test: clean timerelation list
BOOST_FIXTURE_TEST_CASE(cleanTimeRelationList, Fixture)
{
    ibeo::common::sdk::TimeRelationsList trl;
    BOOST_CHECK(true);
    BOOST_CHECK(trl.getTimeRelations().size() == 0);
    trl = createTimeRelationsListC(false);
    BOOST_CHECK(trl.getTimeRelations().size() != 0);
    trl.clear();
    BOOST_CHECK(trl.getTimeRelations().size() == 0);
}

//==============================================================================

// Test: is Reftime GPS timerelation list
BOOST_FIXTURE_TEST_CASE(IsRefGPS_TimeRelationList, Fixture)
{
    ibeo::common::sdk::TimeRelationsList trl;
    trl = createTimeRelationsListC(false);
    BOOST_CHECK(trl.isRefTimeGps() == false);
    trl.clear();
    trl = createTimeRelationsListC(false, true);
    BOOST_CHECK(trl.isRefTimeGps());
}

//==============================================================================

// Test: hasTimeRelation timerelation list
BOOST_FIXTURE_TEST_CASE(hasTimeRelation_TimeRelationList, Fixture)
{
    ClockType clock;
    clock = ibeo::common::sdk::ClockType(getRandValue<uint8_t>(), ibeo::common::sdk::ClockType::ClockName::GpsImu);
    ibeo::common::sdk::TimeRelationsList trl;
    BOOST_CHECK(trl.hasTimeRelation(clock) == false);
    ibeo::common::sdk::TimeRelationsList::TimeRelationsMap trm;
    trm[clock] = m_trSimple;
    trl.setTimeRelationsMap(trm);
    BOOST_CHECK(trl.hasTimeRelation(clock));
}

//==============================================================================

// Test: ensureTimeRelationExists timerelation list
BOOST_FIXTURE_TEST_CASE(ensureTimeRelationExists_TimeRelationList, Fixture)
{
    ClockType clock;
    clock = ibeo::common::sdk::ClockType(getRandValue<uint8_t>(), ibeo::common::sdk::ClockType::ClockName::GpsImu);
    ibeo::common::sdk::TimeRelationsList trl;
    BOOST_CHECK(trl.hasTimeRelation(clock) == false);
    trl.ensureTimeRelationExists(clock);
    BOOST_CHECK(trl.hasTimeRelation(clock));
    BOOST_CHECK(trl.getTimeRelation(clock).getEntryList().size() == 0);
    trl.getTimeRelation(clock) = m_trSimple;
    BOOST_CHECK(trl.getTimeRelation(clock).getEntryList().size() > 0);
}

//==============================================================================

//operator!= and operator==
BOOST_FIXTURE_TEST_CASE(isContentTimeRelationsListEqual, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ibeo::common::sdk::TimeRelationsList trlOrig;
        ibeo::common::sdk::TimeRelationsList trlCopy;
        BOOST_CHECK(trlOrig == trlCopy);

        trlOrig = createTimeRelationsListC(false);

        BOOST_CHECK(trlOrig != trlCopy);

        const TimeRelationsList::TimeRelationsMap& timeRelMap = trlOrig.getTimeRelations();
        TimeRelationsList::TimeRelationsMap copyMap;

        for (const auto& tr : timeRelMap)
        {
            BOOST_CHECK(trlOrig != trlCopy);
            copyMap[tr.first] = tr.second;
            trlCopy.setTimeRelationsMap(copyMap);
        }

        // not equal as reference clock is not set
        BOOST_CHECK(trlOrig != trlCopy);
        trlCopy.setRefTimeType(trlOrig.getRefTimeType());
        BOOST_CHECK(trlOrig == trlCopy);
    } // for r
}

//==============================================================================

// TimeRelationList operator=  TimeRelationList9010
BOOST_FIXTURE_TEST_CASE(isContentTimeRelationsListEqualTimeRelationList9010, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ibeo::common::sdk::TimeRelationsList9010 trlOrig;
        ibeo::common::sdk::TimeRelationsList trlCopy;
        BOOST_CHECK(trlOrig != trlCopy);

        trlOrig = createTimeRelationsList9010C(false);

        const TimeRelationsList9010::TimeRelationMap& timeRelMap = trlOrig.getTimeRelations();
        TimeRelationsList::TimeRelationsMap copyMap;

        for (const auto& tr : timeRelMap)
        {
            copyMap[tr.first] = tr.second;
            trlCopy.setTimeRelationsMap(copyMap);
            BOOST_CHECK(trlOrig != trlCopy);
        }

        trlCopy.setRefTimeType(ClockType(static_cast<uint8_t>(0xFF), ClockType::ClockName::Unknown));

        BOOST_CHECK(trlOrig == trlCopy);
    } // for r
}

//==============================================================================

// TimeRelationList operator=  TimeRelationList9011
BOOST_FIXTURE_TEST_CASE(isContentTimeRelationsListEqualTimeRelationList9011, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ibeo::common::sdk::TimeRelationsList9011 trlOrig;
        ibeo::common::sdk::TimeRelationsList trlCopy;

        trlOrig = createTimeRelationsList9011C(false);
        BOOST_CHECK(trlOrig != trlCopy);

        const TimeRelationsList9011::TimeRelationVector& timeRelVec = trlOrig.getTimeRelations();
        TimeRelationsList::TimeRelationsMap copyMap;
        ClockType otherClock;

        for (const auto& tr : timeRelVec)
        {
            otherClock          = tr.getOtherClock();
            copyMap[otherClock] = tr;
            trlCopy.setTimeRelationsMap(copyMap);
            BOOST_CHECK(trlOrig != trlCopy);
        }

        trlCopy.setRefTimeType(trlOrig.getRefClock());

        BOOST_CHECK(trlOrig == trlCopy);
    } // for r
}

//==============================================================================

//******************************************************************************
//******************************************************************************
//****                                                                   *******
//**** Deserialization of specific data containers to General unit tests *******
//****                                                                   *******
//******************************************************************************
//******************************************************************************

// Test: Deserialization 9010 to general timerelation list
BOOST_FIXTURE_TEST_CASE(Serialization_Deserialization9010ToGeneralTimeRelationList, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ibeo::common::sdk::TimeRelationsList9010Exporter9010 exporter;

        ibeo::common::sdk::TimeRelationsList9010 trl9010Orig = createTimeRelationsList9010C(false);
        BOOST_CHECK(true);

        const ibeo::common::sdk::IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(trl9010Orig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, trl9010Orig));

        ibeo::common::sdk::TimeRelationsList trlCopy;

        const ibeo::common::sdk::TimeRelationsListImporter9010 importer;
        BOOST_CHECK(importer.deserialize(ss, trlCopy, dh));

        BOOST_CHECK(trlCopy == trl9010Orig);
    }
}

//==============================================================================

// Test: Deserialization 9010 with empty entries to general timerelation list
BOOST_FIXTURE_TEST_CASE(Serialization_Deserialization_EmptyEntries9010ToGeneralTimeRelationList, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ibeo::common::sdk::TimeRelationsList9010Exporter9010 exporter;

        ibeo::common::sdk::TimeRelationsList9010 trl9010Orig = createTimeRelationsList9010C(true);
        BOOST_CHECK(true);

        const ibeo::common::sdk::IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(trl9010Orig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, trl9010Orig));

        ibeo::common::sdk::TimeRelationsList trlCopy;

        const ibeo::common::sdk::TimeRelationsListImporter9010 importer;
        BOOST_CHECK(importer.deserialize(ss, trlCopy, dh));

        BOOST_CHECK(trlCopy == trl9010Orig);
    }
}

//==============================================================================

// Test: Deserialization 9011 to general timerelation list
BOOST_FIXTURE_TEST_CASE(Serialization_Deserialization9011ToGeneralTimeRelationList, Fixture)
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

        ibeo::common::sdk::TimeRelationsList trlCopy;

        const ibeo::common::sdk::TimeRelationsListImporter9011 importer;
        BOOST_CHECK(importer.deserialize(ss, trlCopy, dh));

        BOOST_CHECK(trlCopy == trl9011Orig);
    }
}

//==============================================================================

// Test: Deserialization 9011 with duplicated clock to general timerelation list
BOOST_FIXTURE_TEST_CASE(Serialization_Deserialization_DuplicatedClock9011ToGeneralTimeRelationList, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ibeo::common::sdk::TimeRelationsList9011Exporter9011 exporter;

        ibeo::common::sdk::TimeRelationsList9011 trl9011Orig = createTimeRelationsList9011C(false, true);
        BOOST_CHECK(true);

        const ibeo::common::sdk::IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(trl9011Orig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, trl9011Orig));

        ibeo::common::sdk::TimeRelationsList trlCopy;

        const ibeo::common::sdk::TimeRelationsListImporter9011 importer;
        BOOST_CHECK(importer.deserialize(ss, trlCopy, dh) == false);
    }
}

//==============================================================================

// Test: Deserialization 9011 with empty entries to general timerelation list
BOOST_FIXTURE_TEST_CASE(Serialization_Deserialization_EmptyEntries9011ToGeneralTimeRelationList, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ibeo::common::sdk::TimeRelationsList9011Exporter9011 exporter;

        ibeo::common::sdk::TimeRelationsList9011 trl9011Orig = createTimeRelationsList9011C(true, false);
        BOOST_CHECK(true);

        const ibeo::common::sdk::IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(trl9011Orig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, trl9011Orig));

        const ibeo::common::sdk::TimeRelationsListImporter9011 importer;
        ibeo::common::sdk::TimeRelationsList trlCopy;

        BOOST_CHECK(importer.deserialize(ss, trlCopy, dh));
    }
}

//==============================================================================

//******************************************************************************
//******************************************************************************
//*********                                                            *********
//********* Serialization of General data container to 9011 unit tests *********
//*********                                                            *********
//******************************************************************************
//******************************************************************************

//==============================================================================

// Test: Serialization of General data container to 9011 timerelation list
BOOST_FIXTURE_TEST_CASE(SerializationGeneralTimeRelationListTo9011, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ibeo::common::sdk::TimeRelationsListExporter9011 exporterGC;

        ibeo::common::sdk::TimeRelationsList trl1 = createTimeRelationsListC(false);

        ibeo::common::sdk::TimeRelationsList trlCopy;
        ibeo::common::sdk::TimeRelationsList9011 trl9011Copy;

        BOOST_CHECK(trl1 != trl9011Copy);
        BOOST_CHECK(trl1 != trlCopy);

        const ibeo::common::sdk::IbeoDataHeader dh(
            exporterGC.getDataType(), 0U, uint32_t(exporterGC.getSerializedSize(trl1)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporterGC.serialize(ss, trl1));

        // Importing using general container importer
        const ibeo::common::sdk::TimeRelationsListImporter9011 importerGC;
        BOOST_CHECK(importerGC.deserialize(ss, trlCopy, dh));
        BOOST_CHECK(trl1 == trlCopy);

        BOOST_CHECK(exporterGC.serialize(ss, trl1));

        const ibeo::common::sdk::TimeRelationsList9011Importer9011 importer9011;
        // Importing using specilized container importer
        BOOST_CHECK(importer9011.deserialize(ss, trl9011Copy, dh));
        BOOST_CHECK(trl1 == trl9011Copy);
    }
}

//==============================================================================

// Test: Serialization of General data container with empty entry list to 9011 timerelation list
BOOST_FIXTURE_TEST_CASE(SerializationGeneralTimeRelationListWithEmptyEntriesTo9011, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ibeo::common::sdk::TimeRelationsListExporter9011 exporterGC;

        ibeo::common::sdk::TimeRelationsList trl1 = createTimeRelationsListC(true);

        ibeo::common::sdk::TimeRelationsList trlCopy;
        ibeo::common::sdk::TimeRelationsList9011 trl9011Copy;

        BOOST_CHECK(trl1 != trl9011Copy);
        BOOST_CHECK(trl1 != trlCopy);

        const ibeo::common::sdk::IbeoDataHeader dh(
            exporterGC.getDataType(), 0U, uint32_t(exporterGC.getSerializedSize(trl1)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporterGC.serialize(ss, trl1));

        // Importing using general container importer
        const ibeo::common::sdk::TimeRelationsListImporter9011 importerGC;
        BOOST_CHECK(importerGC.deserialize(ss, trlCopy, dh));
        BOOST_CHECK(trl1 == trlCopy);

        BOOST_CHECK(exporterGC.serialize(ss, trl1));

        // Importing using specilized container importer
        const ibeo::common::sdk::TimeRelationsList9011Importer9011 importer9011;
        BOOST_CHECK(importer9011.deserialize(ss, trl9011Copy, dh));
        BOOST_CHECK(trl1 == trl9011Copy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

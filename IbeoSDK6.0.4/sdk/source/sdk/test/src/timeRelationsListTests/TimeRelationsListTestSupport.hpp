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
//!\date Mar 22, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "../common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/timerelation/TimeRelationsList.hpp>

#include <boost/date_time/gregorian/greg_date.hpp>
#include <vector>

using RefTime              = boost::posix_time::ptime;
using OtherTime            = boost::posix_time::time_duration;
using RefTimeRange         = std::pair<RefTime, RefTime>;
using RefTimeRangeVector   = std::vector<RefTimeRange>;
using OtherTimeRange       = std::pair<OtherTime, OtherTime>;
using OtherTimeRangeVector = std::vector<OtherTimeRange>;
using TestEntry            = std::pair<RefTime, OtherTime>;
using TestEntryList        = std::vector<TestEntry>;

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class TimeRelationsListTestSupport : public TestSupport
{
public:
    TimeRelationsListTestSupport();
    virtual ~TimeRelationsListTestSupport();

    // constant variables
public:
    static const boost::gregorian::date m_date;
    static const RefTime r0;
    static const RefTime r1;
    static const RefTime r2;
    static const RefTime r2Plus1Micro;
    static const RefTime r2Plus500Micro;
    static const RefTime r3;
    static const RefTime r4;
    static const RefTime r5;
    static const RefTime r6;
    static const RefTime r7;
    static const RefTime r8;
    static const RefTime r9;
    static const RefTime r10;
    static const RefTime r15;
    static const RefTime r20;

    static const OtherTime om4;
    static const OtherTime o0;
    static const OtherTime o1;
    static const OtherTime o2;
    static const OtherTime o3;
    static const OtherTime o3Plus1Micro;
    static const OtherTime o5;
    static const OtherTime o6;
    static const OtherTime o7;
    static const OtherTime o9;
    static const OtherTime o10;
    static const OtherTime o15;
    static const OtherTime o20;

public:
    static ibeo::common::sdk::TimeRelationsList createTimeRelationsListC(const bool emptyFlag,
                                                                         const bool refGps = false);

    // Creates a TimeRelationsList9010 filled randomly for testing serialization
    static ibeo::common::sdk::TimeRelationsList9010 createTimeRelationsList9010C(const bool emptyFlag);

    // Creates a TimeRelationsList9011 filled randomly for testing serialization
    static ibeo::common::sdk::TimeRelationsList9011 createTimeRelationsList9011C(const bool emptyFlag       = false,
                                                                                 const bool duplicatedClock = false);

    // creating time relation using input entries --> for testing general time
    // relation snippet functions
    static ibeo::common::sdk::TimeRelation createTimeRelation(const TestEntryList& entries);

private:
    // fill a TimeRelationsList randomly
    static ibeo::common::sdk::TimeRelationsList fillRandomly(const bool emptyFlag, const bool refGps);

    // fill a TimeRelationsList9010 randomly
    static ibeo::common::sdk::TimeRelationsList9010 fillRandomly9010(const bool emptyFlag);

    // fill a TimeRelationsList9011 randomly
    static ibeo::common::sdk::TimeRelationsList9011 fillRandomly9011(const bool emptyFlag, const bool duplicatedClock);

    // fill a General Time Relation snippet using defined entries
    static ibeo::common::sdk::TimeRelation fillTimeRelation(const TestEntryList& entries);

    // adding one entry in a relation
    static void addEntry(ibeo::common::sdk::TimeRelation::EntryList& relationEntryList,
                         const RefTime& r1,
                         const RefTime& r2,
                         const OtherTime& o1,
                         const OtherTime& o2);

    // construct relation using EntryList
    static ibeo::common::sdk::TimeRelation
    constructRelation(const ibeo::common::sdk::TimeRelation::EntryList& relationEntryList);

protected:
    static const int32_t nbOfRepeats = 100;

public:
    TimeRelation m_trSimple;
    TimeRelation m_trClockChange;
    TimeRelation m_trAmbiguousNoGap;
    TimeRelation m_trEmpty;
    TimeRelation m_trAmbiguousWithGap;
    TimeRelation m_trUnambiguousWithGap;
}; // TimeRelationsListTestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

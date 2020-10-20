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
//! \date Mar 23, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "TimeRelationsListTestSupport.hpp"
#include <cmath>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

const boost::gregorian::date TimeRelationsListTestSupport::m_date = boost::gregorian::date(2000, 10, 1);
const RefTime TimeRelationsListTestSupport::r0
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(0));
const RefTime TimeRelationsListTestSupport::r1
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(1));
const RefTime TimeRelationsListTestSupport::r2
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(2));
const RefTime TimeRelationsListTestSupport::r2Plus1Micro
    = TimeRelationsListTestSupport::r2 + boost::posix_time::microseconds(1);
const RefTime TimeRelationsListTestSupport::r2Plus500Micro
    = TimeRelationsListTestSupport::r2 + boost::posix_time::milliseconds(500);
const RefTime TimeRelationsListTestSupport::r3
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(3));
const RefTime TimeRelationsListTestSupport::r4
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(4));
const RefTime TimeRelationsListTestSupport::r5
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(5));
const RefTime TimeRelationsListTestSupport::r6
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(6));
const RefTime TimeRelationsListTestSupport::r7
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(7));
const RefTime TimeRelationsListTestSupport::r8
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(8));
const RefTime TimeRelationsListTestSupport::r9
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(9));
const RefTime TimeRelationsListTestSupport::r10
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(10));
const RefTime TimeRelationsListTestSupport::r15
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(15));
const RefTime TimeRelationsListTestSupport::r20
    = RefTime(TimeRelationsListTestSupport::m_date, boost::posix_time::seconds(20));

const OtherTime TimeRelationsListTestSupport::om4 = boost::posix_time::seconds(-4);
const OtherTime TimeRelationsListTestSupport::o0  = boost::posix_time::seconds(0);
const OtherTime TimeRelationsListTestSupport::o1  = boost::posix_time::seconds(1);
const OtherTime TimeRelationsListTestSupport::o2  = boost::posix_time::seconds(2);
const OtherTime TimeRelationsListTestSupport::o3  = boost::posix_time::seconds(3);
const OtherTime TimeRelationsListTestSupport::o3Plus1Micro
    = TimeRelationsListTestSupport::o3 + boost::posix_time::microseconds(1);
const OtherTime TimeRelationsListTestSupport::o5  = boost::posix_time::seconds(5);
const OtherTime TimeRelationsListTestSupport::o6  = boost::posix_time::seconds(6);
const OtherTime TimeRelationsListTestSupport::o7  = boost::posix_time::seconds(7);
const OtherTime TimeRelationsListTestSupport::o9  = boost::posix_time::seconds(9);
const OtherTime TimeRelationsListTestSupport::o10 = boost::posix_time::seconds(10);
const OtherTime TimeRelationsListTestSupport::o15 = boost::posix_time::seconds(15);
const OtherTime TimeRelationsListTestSupport::o20 = boost::posix_time::seconds(20);

//==============================================================================
TimeRelationsListTestSupport::TimeRelationsListTestSupport() : TestSupport()
{
    /* Build m_trSimple TimeRelation with the following graph:
		 *
		 * OtherTime
		 *10|          /
		 *  |         /
		 * 6|        /
		 *  |       /
		 * 3|      /
		 *  |     /
		 * 0|____/_________
		 *       1     9   RefTime
	*/
    TestEntryList ls{{r1, o0}, {r9, o10}};
    m_trSimple = createTimeRelation(ls);

    /* Build m_trClockChange TimeRelation with the following graph:
		 *
		 * OtherTime
		 *10|                  ../
		 *  |               ../
		 *  |            ../
		 *  |         ../
		 * 3|      ../
		 *  |     /
		 * 0|____/_______________
		 *       1 2             9   RefTime
	*/
    TestEntryList ls1{{r1, o0}, {r2, o3}, {r9, o10}};
    m_trClockChange = createTimeRelation(ls1);

    /* Build m_trAmbiguousNoGaps TimeRelation with the following graph:
		 *
		 * OtherTime
		 * 3|      /  /
		 *  |     /  /
		 * 0|____/__/_____
		 *       1 2  6   RefTime
	*/
    TestEntryList ls2{{r1, o0}, {r2, o3}, {r2Plus1Micro, o0}, {r6, o3}};
    m_trAmbiguousNoGap = createTimeRelation(ls2);

    /* Build m_trAmbiguousWithGaps TimeRelation with the following graph:
		 *
		 * OtherTime
		 *10|                   /
		 *  |                  /
		 * 6|                 /
		 *  |
		 * 3|      /      /
		 *  |     /      /
		 * 0|____/______/___________
		 *       1 2    5 6   8 9   RefTime
	*/
    TestEntryList ls3{{r1, o0}, {r2, o3}, {r5, o0}, {r6, o3}, {r8, o6}, {r9, o10}};
    m_trAmbiguousWithGap = createTimeRelation(ls3);

    /* Build m_trAmbiguousWithGaps TimeRelation with the following graph:
		 *
		 * OtherTime
		 *10|            /
		 *  |           /
		 * 6|          /
		 *  |
		 * 3|      /
		 *  |     /
		 * 0|____/_______________
		 *       1 2   8 9   RefTime
	*/
    TestEntryList ls4{{r1, o0}, {r2, o3}, {r8, o6}, {r9, o10}};
    m_trUnambiguousWithGap = createTimeRelation(ls4);
}

//==============================================================================
TimeRelationsListTestSupport::~TimeRelationsListTestSupport() {}

//==============================================================================

TimeRelation TimeRelationsListTestSupport::createTimeRelation(const TestEntryList& entries)
{
    return fillTimeRelation(entries);
}

//==============================================================================

TimeRelationsList TimeRelationsListTestSupport::createTimeRelationsListC(const bool emptyFlag, const bool refGps)
{
    return fillRandomly(emptyFlag, refGps);
}

//==============================================================================

TimeRelationsList9010 TimeRelationsListTestSupport::createTimeRelationsList9010C(const bool emptyFlag)
{
    return fillRandomly9010(emptyFlag);
}

//==============================================================================

TimeRelationsList9011 TimeRelationsListTestSupport::createTimeRelationsList9011C(const bool emptyFlag,
                                                                                 const bool duplicatedClock)
{
    return fillRandomly9011(emptyFlag, duplicatedClock);
}

//==============================================================================

TimeRelationsList TimeRelationsListTestSupport::fillRandomly(const bool emptyFlag, const bool refGps)
{
    std::vector<uint8_t> clockNames;
    clockNames.resize(static_cast<std::size_t>(getRandValue<uint8_t>(5) + 2));
    for (uint8_t clockIdx = 0; clockIdx < clockNames.size() - 1; ++clockIdx)
    {
        if (refGps && (clockIdx == static_cast<uint8_t>(ibeo::common::sdk::ClockType::ClockName::GpsImu)))
        {
            continue;
        }
        clockNames[clockIdx] = clockIdx;
    }
    std::random_shuffle(clockNames.begin(), clockNames.end());

    TimeRelationsList trl;
    if (refGps)
    {
        trl.setRefTimeType(
            ibeo::common::sdk::ClockType(getRandValue<uint8_t>(), ibeo::common::sdk::ClockType::ClockName::GpsImu));
    }
    else
    {
        trl.setRefTimeType(ibeo::common::sdk::ClockType(getRandValue<uint8_t>(),
                                                        ibeo::common::sdk::ClockType::ClockName(clockNames[0])));
    }

    ibeo::common::sdk::TimeRelationsList::TimeRelationsMap trm;
    for (uint8_t i = 0; i < clockNames.size() - 1; ++i)
    {
        ibeo::common::sdk::TimeRelation::EntryList entryList;
        for (uint16_t l = 0; l < getRandValue<uint8_t>(); ++l)
        {
            if (!emptyFlag)
            {
                ibeo::common::sdk::TimeRelation::Entry entry;
                entry.m_refTime   = RefTime(boost::gregorian::date(2000, 10, 1), boost::posix_time::seconds(l));
                entry.m_otherTime = boost::posix_time::seconds(l);
                entry.m_factor    = getNonNanRandValue<double>();
                if (l % 2)
                {
                    entry.m_optionalData.reset(new ibeo::common::sdk::TimeRelation::SmoothingOptionalData());
                    entry.m_optionalData->m_standardError          = boost::posix_time::seconds(l + 1);
                    entry.m_optionalData->m_maxDeviation           = boost::posix_time::seconds(l + 3);
                    entry.m_optionalData->m_correlationCoefficient = getNonNanRandValue<double>();
                }
                entryList.push_back(entry);
            }
        }
        ibeo::common::sdk::TimeRelation tr;
        tr.setEntryList(entryList);
        trm[ibeo::common::sdk::ClockType(
            getRandValue<uint8_t>(), ibeo::common::sdk::ClockType::ClockName(clockNames[static_cast<uint8_t>(i + 1)]))]
            = tr;
    }
    trl.setTimeRelationsMap(trm);

    return trl;
}

//==============================================================================

TimeRelationsList9010 TimeRelationsListTestSupport::fillRandomly9010(const bool emptyFlag)
{
    TimeRelationsList9010 trl;
    std::vector<uint8_t> clockNames;
    clockNames.resize(static_cast<std::size_t>(getRandValue<uint8_t>(5) + 2));
    for (uint8_t i = 0; i < clockNames.size(); ++i)
    {
        clockNames[i] = i;
    }
    std::random_shuffle(clockNames.begin(), clockNames.end());

    ibeo::common::sdk::TimeRelationsList9010::TimeRelationMap trm;
    for (uint8_t i = 0; i < clockNames.size(); ++i)
    {
        ibeo::common::sdk::TimeRelationIn9010::EntryList entryList;
        for (uint16_t l = 0; l < getRandValue<uint16_t>(); ++l)
        {
            if (!emptyFlag)
            {
                ibeo::common::sdk::TimeRelationIn9010::Entry entry;
                entry.m_refTime = NTPTime(static_cast<uint64_t>(l + 1000));
                entry.m_data.reset(new ibeo::common::sdk::TimeRelationIn9010::EntryOptionalData());
                entry.m_data->m_otherTime = static_cast<int64_t>(l);
                entry.m_data->m_factor    = getNonNanRandValue<double>();
                entry.m_data->m_factorInv = 1 / entry.m_data->m_factor;
                entryList.push_back(entry);
            }
        }
        ibeo::common::sdk::TimeRelationIn9010 tr;
        tr.setEntryList(entryList);
        trm[ibeo::common::sdk::ClockType(getRandValue<uint8_t>(),
                                         ibeo::common::sdk::ClockType::ClockName(clockNames[i]))]
            = tr;
    }
    trl.setTimeRelations(trm);

    return trl;
}

//==============================================================================

TimeRelationsList9011 TimeRelationsListTestSupport::fillRandomly9011(const bool emptyFlag, const bool duplicatedClock)
{
    TimeRelationsList9011 trl;
    std::vector<uint8_t> clockNames;
    clockNames.resize(static_cast<std::size_t>(getRandValue<uint8_t>(5) + 2));
    for (uint8_t i = 0; i < clockNames.size(); ++i)
    {
        clockNames[i] = i;
    }
    std::random_shuffle(clockNames.begin(), clockNames.end());
    trl.setRefClock(
        ibeo::common::sdk::ClockType(getRandValue<uint8_t>(), ibeo::common::sdk::ClockType::ClockName(clockNames[0])));

    ibeo::common::sdk::TimeRelationsList9011::TimeRelationVector trv;

    for (uint8_t i = 1; i < clockNames.size(); ++i)
    {
        ibeo::common::sdk::TimeRelationIn9011::EntryList entryList;
        for (uint16_t l = 0; l < getRandValue<uint16_t>(); ++l)
        {
            if (!emptyFlag)
            {
                ibeo::common::sdk::TimeRelationIn9011::Entry entry;
                entry.m_refTime                = NTPTime(static_cast<uint64_t>(l + 1000));
                entry.m_otherTime              = NTPTime(static_cast<uint64_t>(l));
                entry.m_slope                  = double(rand());
                entry.m_standardError          = NTPTime(static_cast<uint64_t>(l * 2));
                entry.m_maxDeviation           = NTPTime(static_cast<uint64_t>(l * 4));
                entry.m_correlationCoefficient = getNonNanRandValue<double>();
                entryList.push_back(entry);
            }
        }
        ibeo::common::sdk::TimeRelationIn9011 tr;
        tr.setOtherClock(ibeo::common::sdk::ClockType(getRandValue<uint8_t>(),
                                                      ibeo::common::sdk::ClockType::ClockName(clockNames[i])));
        tr.setEntryList(entryList);
        trv.push_back(tr);
        if (duplicatedClock)
        {
            trv.push_back(tr);
        }
    }

    trl.setTimeRelations(trv);

    return trl;
}

//==============================================================================

TimeRelation TimeRelationsListTestSupport::fillTimeRelation(const TestEntryList& entries)
{
    uint32_t itrCount = (static_cast<uint32_t>(entries.size()) % 2 == 0) ? static_cast<uint32_t>(entries.size())
                                                                         : static_cast<uint32_t>(entries.size() - 1);
    TimeRelation::EntryList relationEntryList;
    for (uint32_t i = 0; i < itrCount; i += 2)
    {
        addEntry(relationEntryList, entries[i].first, entries[i + 1].first, entries[i].second, entries[i + 1].second);
    }
    if (entries.size() - itrCount == 1)
    {
        relationEntryList.push_back(TimeRelation::Entry());
        TimeRelation::Entry& entry1 = *(relationEntryList.end() - 3);
        TimeRelation::Entry& entry2 = *(relationEntryList.end() - 2);
        TimeRelation::Entry& entry3 = relationEntryList.back();

        entry2.m_otherTime = entry1.interpolate(entry2.m_refTime);
        entry2.m_factor    = TimeRelation::calculateFactor(
            entry2.m_refTime, entries[itrCount].first, entry2.m_otherTime, entries[itrCount].second);

        entry3.m_refTime = entries[itrCount].first;
    }
    return constructRelation(relationEntryList);
}

//==============================================================================

void TimeRelationsListTestSupport::addEntry(TimeRelation::EntryList& relationEntryList,
                                            const RefTime& rt1,
                                            const RefTime& rt2,
                                            const OtherTime& ot1,
                                            const OtherTime& ot2)
{
    relationEntryList.push_back(TimeRelation::Entry());
    relationEntryList.push_back(TimeRelation::Entry());

    TimeRelation::Entry& entry1 = *(relationEntryList.end() - 2);
    TimeRelation::Entry& entry2 = relationEntryList.back();

    entry1.m_refTime   = rt1;
    entry1.m_otherTime = ot1;
    entry1.m_factor    = TimeRelation::calculateFactor(rt1, rt2, ot1, ot2);
    entry2.m_refTime   = rt2;

    const ibeo::common::sdk::timerelation::TimeDuration calculationError = ibeo::common::sdk::timerelation::abs(
        ot2 - (ot1 + ((rt2 - rt1) * static_cast<int32_t>(std::lround(entry1.m_factor)))));
    if (calculationError >= boost::posix_time::microseconds(1))
    {
        const RefTime rh   = rt1 + (rt2 - rt1) / 2.0;
        const OtherTime oh = ot1 + (ot2 - ot1) / 2.0;

        entry1.m_factor    = TimeRelation::calculateFactor(rt1, rh, ot1, oh);
        entry2.m_refTime   = rh;
        entry2.m_otherTime = oh;
        entry2.m_factor    = TimeRelation::calculateFactor(rh, rt2, oh, ot2);

        relationEntryList.push_back(TimeRelation::Entry());
        TimeRelation::Entry& entry3 = relationEntryList.back();
        entry3.m_refTime            = rt2;
    }
}

//==============================================================================
TimeRelation TimeRelationsListTestSupport::constructRelation(const TimeRelation::EntryList& relationEntryList)
{
    TimeRelation result;
    result.setMetadataInaccurate();
    TimeRelation::EntryList resultsEntryList;
    TimeRelation::EntryList::const_iterator prevItr;
    for (TimeRelation::EntryList::const_iterator currItr = relationEntryList.begin();
         currItr != relationEntryList.end();
         prevItr = currItr++)
    {
        if (currItr->m_otherTime != boost::posix_time::not_a_date_time
            && currItr->m_factor == ibeo::common::sdk::NaN_double)
        {
        }
        else
        {
            resultsEntryList.push_back(*currItr);
        }
    }
    result.setEntryList(resultsEntryList);
    result.updateMetadata();
    return result;
}

//==============================================================================

} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date March 13, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/timerelation/TimeRelation.hpp>

#include <ibeo/common/sdk/Time.hpp>

#include <utility>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
//using namespace ibeo::common::sdk::timerelation;
using ibeo::common::sdk::timerelation::RefTime;
using ibeo::common::sdk::timerelation::OtherTime;
using ibeo::common::sdk::timerelation::invalidRefTime;
using ibeo::common::sdk::timerelation::invalidOtherTime;
using ibeo::common::sdk::timerelation::RefTimeRange;
using ibeo::common::sdk::timerelation::OtherTimeRange;
using ibeo::common::sdk::timerelation::invalidRefTimeRange;
using ibeo::common::sdk::timerelation::invalidOtherTimeRange;
using ibeo::common::sdk::timerelation::RefTimeVector;
using ibeo::common::sdk::timerelation::RefTimeRangeVector;
using ibeo::common::sdk::timerelation::OtherTimeRangeVector;
using ibeo::common::sdk::timerelation::CompFirst;
using ibeo::common::sdk::timerelation::CompSecond;
using ibeo::common::sdk::timerelation::OutOfRangeException;
using ibeo::common::sdk::timerelation::AmbiguousException;
using ibeo::common::sdk::timerelation::operator*;
using ibeo::common::sdk::timerelation::operator/;
using ibeo::common::sdk::timerelation::epochRefTime;

//==============================================================================
// TimeRelation
//==============================================================================

bool TimeRelation::isEmpty() const
{
    // Metadata not used
    return m_entryList.empty();
}

//==============================================================================

bool TimeRelation::isAmbiguous() const
{
    updateMetadata();
    return m_metadata.m_ambiguous;
}

//==============================================================================

bool TimeRelation::hasRefGap() const
{
    updateMetadata();
    return m_metadata.m_hasRefGap;
}

//==============================================================================

RefTime TimeRelation::minRefTime() const
{
    updateMetadata();
    return m_metadata.m_refTimeRange.first;
}

//==============================================================================

RefTime TimeRelation::maxRefTime() const
{
    updateMetadata();
    return m_metadata.m_refTimeRange.second;
}

//==============================================================================

bool TimeRelation::hasOtherGap() const
{
    updateMetadata();
    return m_metadata.m_hasOtherGap;
}

//==============================================================================

OtherTime TimeRelation::minOtherTime() const
{
    updateMetadata();
    return m_metadata.m_otherTimeRange.first;
}

//==============================================================================

OtherTime TimeRelation::maxOtherTime() const
{
    updateMetadata();
    return m_metadata.m_otherTimeRange.second;
}
//==============================================================================

const std::vector<RefTimeRange>& TimeRelation::getRefTimeRanges() const
{
    updateMetadata();
    return m_metadata.m_refRanges;
}

//==============================================================================

const std::vector<OtherTimeRange>& TimeRelation::getOtherTimeRanges() const
{
    updateMetadata();
    return m_metadata.m_otherRanges;
}

//==============================================================================

const RefTimeRange& TimeRelation::getUnambiguousRange(const RefTime& t) const
{
    updateMetadata();
    const std::size_t index = m_metadata.findRangeContaining(t);
    return m_metadata.m_refRanges[index];
}

//==============================================================================

const RefTimeRange& TimeRelation::getUnambiguousRangeNoThrow(const RefTime& t) const
{
    try
    {
        return getUnambiguousRange(t);
    }
    catch (...)
    {
        return invalidRefTimeRange();
    }
}

//==============================================================================

OtherTime TimeRelation::convert(const RefTime& t) const
{
    // Metadata not used

    const EntryList::const_iterator itr = findInterpolationEntry(t);

    if (itr == m_entryList.end())
    {
        throw OutOfRangeException();
    }

    return itr->interpolate(t);
}

//==============================================================================

OtherTime TimeRelation::convertNoThrow(const RefTime& t) const
{
    try
    {
        return convert(t);
    }
    catch (...)
    {
        return invalidOtherTime();
    }
}

//==============================================================================

RefTime TimeRelation::convert(const OtherTime& t) const
{
    updateMetadata();
    // Find the otherRange containing this OtherTime
    OtherTimeRangeVector::const_iterator itr = m_metadata.m_otherRanges.begin();
    for (; itr != m_metadata.m_otherRanges.end(); ++itr)
    {
        if (itr->first <= t && t <= itr->second)
        {
            // Check for ambiguity
            if (m_metadata.m_ambiguous)
            {
                OtherTimeRangeVector::const_iterator secondItr = itr;
                ++secondItr;
                for (; secondItr != m_metadata.m_otherRanges.end(); ++secondItr)
                {
                    if (secondItr->first <= t && t <= secondItr->second)
                    {
                        throw AmbiguousException();
                    }
                }
            }

            const std::size_t index           = static_cast<std::size_t>(itr - m_metadata.m_otherRanges.begin());
            EntryList::const_iterator currItr = m_metadata.m_rangeToEntries[index];
            //EntryList::const_iterator prevItr = currItr++;

            EntryList::const_iterator prevItr = currItr;
            ++currItr;
            for (; currItr != m_entryList.end(); ++prevItr, ++currItr)
            {
                assert(prevItr->m_otherTime != invalidOtherTime());
                if (currItr->m_otherTime == invalidOtherTime() || currItr->m_otherTime > t)
                {
                    const Entry& entry = *prevItr;
                    return entry.interpolate(t);
                }
            }

            // This point should never be reached: it indicates that the
            // metadata does not match the entry data
            assert(false);
        }
    }

    // Either out of range or in a gap
    throw OutOfRangeException();
}

//==============================================================================

RefTime TimeRelation::convertNoThrow(const OtherTime& t) const
{
    try
    {
        return convert(t);
    }
    catch (...)
    {
        return invalidRefTime();
    }
}

//==============================================================================

RefTimeVector TimeRelation::convertAmbiguous(const OtherTime& t) const
{
    updateMetadata();
    RefTimeVector result;

    // Find the otherRange containing this OtherTime
    OtherTimeRangeVector::const_iterator itr = m_metadata.m_otherRanges.begin();
    for (; itr != m_metadata.m_otherRanges.end(); ++itr)
    {
        if (itr->first <= t && t <= itr->second)
        {
            const std::size_t index           = static_cast<std::size_t>(itr - m_metadata.m_otherRanges.begin());
            EntryList::const_iterator currItr = m_metadata.m_rangeToEntries[index];
            EntryList::const_iterator prevItr = currItr;
            ++currItr;
            for (; currItr != m_entryList.end(); ++prevItr, ++currItr)
            {
                assert(prevItr->m_otherTime != invalidOtherTime());
                if (currItr->m_otherTime == invalidOtherTime() || currItr->m_otherTime > t)
                {
                    const Entry& entry = *prevItr;
                    result.push_back(entry.interpolate(t));
                    break;
                }
            }
        }
    }

    return result;
}

//==============================================================================

void TimeRelation::clear()
{
    setMetadataInaccurate();
    m_entryList.clear();

    // Post-condition
    assert(isEmpty());
}

//==============================================================================

void TimeRelation::setMetadataInaccurate() const { m_metadata.m_accurate = false; }

//==============================================================================

void TimeRelation::updateMetadata() const
{
    if (m_metadata.m_accurate)
    {
        return;
    }

    assert(m_entryList.size() != 1);

    if (m_entryList.empty())
    {
        m_metadata.m_ambiguous      = false;
        m_metadata.m_hasRefGap      = false;
        m_metadata.m_refTimeRange   = invalidRefTimeRange();
        m_metadata.m_hasOtherGap    = false;
        m_metadata.m_otherTimeRange = invalidOtherTimeRange();
        m_metadata.m_refRanges.clear();
        m_metadata.m_otherRanges.clear();
    }
    else
    {
        // Update refRanges, otherRanges and rangeToEntries
        m_metadata.m_refRanges.clear();
        m_metadata.m_otherRanges.clear();
        m_metadata.m_rangeToEntries.clear();

        // Iterate entry data, keeping previous iterator
        EntryList::const_iterator prevItr;
        for (EntryList::const_iterator currItr = m_entryList.begin(); currItr != m_entryList.end(); ++currItr)
        {
#ifndef NDEBUG
            assert(!currItr->m_refTime.is_not_a_date_time());
            if (currItr->m_otherTime != invalidOtherTime())
            {
                assert(!std::isnan(currItr->m_factor));
            }
#endif

            // Check if we should start a new range
            if (m_metadata.m_refRanges.empty() || !m_metadata.m_refRanges.back().second.is_not_a_date_time())
            {
                assert(currItr->m_otherTime != invalidOtherTime());

                RefTimeRange refTimeRange     = std::make_pair(currItr->m_refTime, invalidRefTime());
                OtherTimeRange otherTimeRange = std::make_pair(currItr->m_otherTime, invalidOtherTime());

                m_metadata.m_refRanges.push_back(refTimeRange);
                m_metadata.m_otherRanges.push_back(otherTimeRange);
                m_metadata.m_rangeToEntries.push_back(currItr);
            }
            else if (currItr->m_otherTime == invalidOtherTime() && currItr != m_entryList.begin())
            {
                // This is a jump/reset

                // End the last metadata-range
                assert(m_metadata.m_refRanges.back().second.is_not_a_date_time());

                m_metadata.m_refRanges.back().second   = currItr->m_refTime;
                m_metadata.m_otherRanges.back().second = prevItr->interpolate(currItr->m_refTime);
            }
            else
            {
                // This is a continuation with a new clock-drift

                // Do nothing
            }
            prevItr = currItr;
        }

        // Note: ranges are sorted by RefTime, so the min and max are easy
        m_metadata.m_refTimeRange
            = RefTimeRange(m_metadata.m_refRanges.front().first, m_metadata.m_refRanges.back().second);

        // Check hasRefGap
        m_metadata.m_hasRefGap = false;
        for (unsigned i = 1; i < m_metadata.m_refRanges.size(); ++i)
        {
            const RefTimeRange& prev = m_metadata.m_refRanges[i - 1];
            const RefTimeRange& curr = m_metadata.m_refRanges[i];

            if (curr.first > prev.second + boost::posix_time::microseconds(1))
            {
                m_metadata.m_hasRefGap = true;
                break;
            }
        }

        // Create a vector of OtherTime ranges sorted by start-time
        OtherTimeRangeVector sortedOtherRanges = m_metadata.m_otherRanges;
        std::sort(sortedOtherRanges.begin(), sortedOtherRanges.end(), CompFirst<OtherTime>());

        m_metadata.m_otherTimeRange.first = sortedOtherRanges.front().first;

        m_metadata.m_ambiguous   = false;
        m_metadata.m_hasOtherGap = false;
        // Temporarily set the max other time
        m_metadata.m_otherTimeRange.second = sortedOtherRanges.front().second;

        for (OtherTimeRangeVector::const_iterator itr = ++sortedOtherRanges.begin(); itr != sortedOtherRanges.end();
             ++itr)
        {
            // Check ambiguity
            if (itr->first <= m_metadata.m_otherTimeRange.second)
            {
                m_metadata.m_ambiguous = true;
            }

            if (itr->first > m_metadata.m_otherTimeRange.second + boost::posix_time::microseconds(1))
            {
                m_metadata.m_hasOtherGap = true;
            }

            m_metadata.m_otherTimeRange.second = std::max(m_metadata.m_otherTimeRange.second, itr->second);
        }
    }

    m_metadata.m_accurate = true;
}

//==============================================================================

RefTime TimeRelation::Entry::interpolate(const OtherTime& o) const
{
    assert(m_otherTime != invalidOtherTime());
    assert(!std::isnan(1 / m_factor));
    // FactorInv = delta(Ref time) / delta(Other time)
    return m_refTime + (o - m_otherTime) * (1.0 / m_factor);
}

//==============================================================================

OtherTime TimeRelation::Entry::interpolate(const RefTime& r) const
{
    assert(m_otherTime != invalidOtherTime());
    assert(!std::isnan(m_factor));
    // Factor = delta(Other time) / delta(Ref time)
    return m_otherTime + (r - m_refTime) * m_factor;
}

//==============================================================================

TimeRelation::EntryList::const_iterator TimeRelation::findInterpolationEntry(const RefTime& r) const
{
    // Metadata not used

    if (m_entryList.size() < 2 || (r < m_entryList.front().m_refTime) || (r > m_entryList.back().m_refTime))
    {
        return m_entryList.end();
    }
    else
    {
        TimeRelation::EntryList::const_iterator itr
            = std::lower_bound(m_entryList.begin(), m_entryList.end(), r, CompRef());

        assert(itr != m_entryList.end());

        // Check if lower_bound found an exact match
        if ((itr->m_otherTime != invalidOtherTime()) && (itr->m_refTime == r))
        {
            return itr;
        }
        else
        {
            assert(itr != m_entryList.begin());

            // Go to the earlier item
            --itr;

            // If the earlier item is the beginning of a gap, the query was in the gap
            if (itr->m_otherTime == invalidOtherTime())
            {
                return m_entryList.end();
            }
            else
            {
                return itr;
            }
        }
    }
}

//==============================================================================

TimeRelation::TimeRelation() { clear(); }

//==============================================================================

TimeRelation::TimeRelation(const TimeRelation& other) { *this = other; }

//==============================================================================

TimeRelation::TimeRelation(const TimeRelationIn9010& other)
{
    TimeRelationIn9010::EntryList other_entrylist = other.getEntryList();
    m_entryList.resize(other_entrylist.size());
    Entry this_entry;
    TimeRelationIn9010::Entry other_entry;
    for (uint32_t ind = 0; ind < m_entryList.size(); ++ind)
    {
        other_entry          = other_entrylist[ind];
        this_entry.m_refTime = other_entry.m_refTime.toPtime();
        // if entry has other time
        if (other_entry.m_data)
        {
            this_entry.m_otherTime = boost::posix_time::microseconds(other_entry.m_data->m_otherTime);
            this_entry.m_factor    = other_entry.m_data->m_factor;
        }
        else
        {
            this_entry.m_otherTime = invalidOtherTime();
            this_entry.m_factor    = NaN_double;
        }
        m_entryList[ind] = this_entry;
    }
}

//==============================================================================

TimeRelation::TimeRelation(const TimeRelationIn9011& other)
{
    TimeRelationIn9011::EntryList other_entrylist = other.getEntryList();
    m_entryList.resize(other_entrylist.size());
    Entry this_entry;
    TimeRelationIn9011::Entry other_entry;
    for (uint32_t ind = 0; ind < m_entryList.size(); ++ind)
    {
        other_entry            = other_entrylist[ind];
        this_entry.m_refTime   = other_entry.m_refTime.toPtime();
        this_entry.m_otherTime = other_entry.m_otherTime.toTimeDurationSinceEpoch();
        this_entry.m_factor    = other_entry.m_slope;
        if (!other_entry.m_maxDeviation.is_not_a_date_time())
        {
            this_entry.m_optionalData.reset(new SmoothingOptionalData());
            this_entry.m_optionalData->m_maxDeviation  = other_entry.m_maxDeviation.toTimeDurationSinceEpoch();
            this_entry.m_optionalData->m_standardError = other_entry.m_standardError.toTimeDurationSinceEpoch();
            this_entry.m_optionalData->m_correlationCoefficient = other_entry.m_correlationCoefficient;
        }
        m_entryList[ind] = this_entry;
    }
}

//==============================================================================

std::size_t TimeRelation::Metadata::findRangeContaining(const RefTime& t) const
{
    if ((m_refTimeRange.second < t) || (t < m_refTimeRange.first))
    {
        throw OutOfRangeException();
    }

    // Find the first item with an end-time at-or-after specified time
    RefTimeRangeVector::const_iterator itr
        = std::lower_bound(m_refRanges.begin(), m_refRanges.end(), t, CompSecond<RefTime>());

    if (itr == m_refRanges.end())
    {
        throw OutOfRangeException();
    }
    else if (t < itr->first)
    {
        throw OutOfRangeException(); // TODO Actually in a gap
    }
    else
    {
        return static_cast<uint32_t>(itr - m_refRanges.begin());
    }
}

//==============================================================================

std::string TimeRelation::debugToString() const
{
    std::stringstream sstr;

    sstr << "Entry list: (" << m_entryList.size() << ")" << std::endl;
    for (std::size_t i = 0; i < m_entryList.size(); ++i)
    {
        sstr << "\t" << i << ": ";

        sstr << m_entryList[i].m_refTime << " ";
        sstr << m_entryList[i].m_otherTime << " ";
        sstr << m_entryList[i].m_factor << " ";
        sstr << 1 / m_entryList[i].m_factor;

        sstr << std::endl;
    }

    sstr << "Metadata:" << std::endl;

    sstr << ((m_metadata.m_ambiguous) ? "Ambiguous" : "Unambiguous") << ", ";
    sstr << ((m_metadata.m_hasRefGap) ? "Ref-gap" : "Ref-continuous") << ", ";
    sstr << ((m_metadata.m_hasOtherGap) ? "Other-gap" : "Other-continuous") << std::endl;
    sstr << "Ref range: " << m_metadata.m_refTimeRange.first << " -- " << m_metadata.m_refTimeRange.second << std::endl;
    sstr << "Other range: " << m_metadata.m_otherTimeRange.first << " -- " << m_metadata.m_otherTimeRange.second
         << std::endl;

    sstr << "Ranges: (" << m_metadata.m_refRanges.size() << ")" << std::endl;
    assert(m_metadata.m_refRanges.size() == m_metadata.m_otherRanges.size());
    for (std::size_t i = 0; i < m_metadata.m_refRanges.size(); ++i)
    {
        sstr << "\t" << i << ": ";

        sstr << m_metadata.m_refRanges[i].first << " == " << m_metadata.m_otherRanges[i].first;

        sstr << "\t"
             << " : ";
        sstr << m_metadata.m_refRanges[i].second << " == " << m_metadata.m_otherRanges[i].second;

        sstr << std::endl;
    }

    for (auto& rangeToEntry : m_metadata.m_rangeToEntries)
    {
        sstr << "range to entries: " << std::endl;
        sstr << "reftime: " << rangeToEntry->m_refTime << std::endl;
        sstr << "otherTime: " << rangeToEntry->m_otherTime << std::endl;
        sstr << "factor: " << rangeToEntry->m_factor << std::endl;
        sstr << std::endl;
    }

    return sstr.str();
}

//==============================================================================

TimeRelation::Entry::Entry()
  : m_refTime(invalidRefTime()),
    m_otherTime(invalidOtherTime()),
    m_factor(ibeo::common::sdk::NaN_double),
    m_optionalData()
{
    // Intentionally empty
}

//==============================================================================

TimeRelation::Entry::Entry(const TimeRelation::Entry& other)
  : m_refTime(other.m_refTime), m_otherTime(other.m_otherTime), m_factor(other.m_factor), m_optionalData()
{
    if (other.m_optionalData)
    {
        m_optionalData.reset(new SmoothingOptionalData());
        *m_optionalData = *(other.m_optionalData);
    }
}

//==============================================================================

TimeRelation::Entry& TimeRelation::Entry::operator=(const TimeRelation::Entry& other)
{
    if (&other != this)
    {
        m_refTime   = other.m_refTime;
        m_otherTime = other.m_otherTime;
        m_factor    = other.m_factor;
        if (other.m_optionalData)
        {
            if (!m_optionalData)
            {
                m_optionalData.reset(new SmoothingOptionalData());
            }
            *m_optionalData = *(other.m_optionalData);
        }
        else
        {
            m_optionalData.reset();
        }
    }
    return *this;
}

//==============================================================================

double TimeRelation::calculateFactor(const RefTime& r1, const RefTime& r2, const OtherTime& o1, const OtherTime& o2)
{
    return (o2 - o1) / (r2 - r1);
}

//==============================================================================

TimeRelation& TimeRelation::operator=(const TimeRelation& other)
{
    m_entryList = other.m_entryList;
    m_metadata.assign(other.m_metadata, other, *this);
    return *this;
}

//==============================================================================

TimeRelation& TimeRelation::operator=(const TimeRelationIn9010& other)
{
    TimeRelationIn9010::EntryList other_entrylist = other.getEntryList();
    m_entryList.resize(other_entrylist.size());

    for (uint32_t ind = 0; ind < m_entryList.size(); ++ind)
    {
        TimeRelationIn9010::Entry other_entry;
        other_entry = other_entrylist[ind];
        Entry this_entry;
        this_entry.m_refTime = other_entry.m_refTime.toPtime();
        // if entry has other time
        if (other_entry.m_data)
        {
            this_entry.m_otherTime = boost::posix_time::microseconds(other_entry.m_data->m_otherTime);
            this_entry.m_factor    = other_entry.m_data->m_factor;
        }
        else
        {
            this_entry.m_otherTime = invalidOtherTime();
            this_entry.m_factor    = NaN_double;
        }
        m_entryList[ind] = this_entry;
    }
    return *this;
}

//==============================================================================

TimeRelation& TimeRelation::operator=(const TimeRelationIn9011& other)
{
    TimeRelationIn9011::EntryList other_entrylist = other.getEntryList();
    m_entryList.resize(other_entrylist.size());

    for (uint32_t ind = 0; ind < m_entryList.size(); ++ind)
    {
        TimeRelationIn9011::Entry other_entry;
        other_entry = other_entrylist[ind];
        Entry this_entry;
        this_entry.m_refTime   = other_entry.m_refTime.toPtime();
        this_entry.m_otherTime = other_entry.m_otherTime.toTimeDurationSinceEpoch();
        this_entry.m_factor    = other_entry.m_slope;
        if (!other_entry.m_maxDeviation.is_not_a_date_time())
        {
            this_entry.m_optionalData.reset(new SmoothingOptionalData());
            this_entry.m_optionalData->m_maxDeviation  = other_entry.m_maxDeviation.toTimeDurationSinceEpoch();
            this_entry.m_optionalData->m_standardError = other_entry.m_standardError.toTimeDurationSinceEpoch();
            this_entry.m_optionalData->m_correlationCoefficient = other_entry.m_correlationCoefficient;
        }
        m_entryList[ind] = this_entry;
    }
    return *this;
}

//==============================================================================
TimeRelation::Metadata&
TimeRelation::Metadata::assign(const Metadata& other, const TimeRelation& otherParent, const TimeRelation& parent)
{
    m_accurate       = other.m_accurate;
    m_ambiguous      = other.m_ambiguous;
    m_hasRefGap      = other.m_hasRefGap;
    m_refTimeRange   = other.m_refTimeRange;
    m_hasOtherGap    = other.m_hasOtherGap;
    m_otherTimeRange = other.m_otherTimeRange;
    m_refRanges      = other.m_refRanges;
    m_otherRanges    = other.m_otherRanges;

    m_rangeToEntries.resize(other.m_rangeToEntries.size());
    for (uint32_t i = 0; i < other.m_rangeToEntries.size(); ++i)
    {
        m_rangeToEntries[i]
            = parent.m_entryList.begin() + (other.m_rangeToEntries[i] - otherParent.m_entryList.begin());
    }

    return *this;
}

//==============================================================================

bool operator==(const TimeRelation::Entry& lhs, const TimeRelation::Entry& rhs)
{
    if ((lhs.m_refTime != rhs.m_refTime) || (lhs.m_otherTime != rhs.m_otherTime)
        || !ibeo::common::sdk::fuzzyCompareT<7>(lhs.m_factor, rhs.m_factor)
        || (lhs.m_optionalData == nullptr && rhs.m_optionalData != nullptr)
        || (lhs.m_optionalData != nullptr && rhs.m_optionalData == nullptr))
    {
        return false;
    }
    if (lhs.m_optionalData != nullptr)
    {
        if ((lhs.m_optionalData->m_standardError != rhs.m_optionalData->m_standardError)
            || (lhs.m_optionalData->m_maxDeviation != rhs.m_optionalData->m_maxDeviation)
            || !ibeo::common::sdk::fuzzyCompareT<7>(lhs.m_optionalData->m_correlationCoefficient,
                                                    rhs.m_optionalData->m_correlationCoefficient))
        {
            return false;
        }
    }
    return true;
}

//==============================================================================

bool operator==(const TimeRelation& lhs, const TimeRelation& rhs) { return (lhs.getEntryList() == rhs.getEntryList()); }

//==============================================================================

bool operator!=(const TimeRelation& lhs, const TimeRelation& rhs) { return !(lhs == rhs); }

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

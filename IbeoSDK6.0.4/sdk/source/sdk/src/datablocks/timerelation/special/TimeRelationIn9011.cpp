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
//!\date March 14, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationIn9011.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/Math.hpp>

#include <utility>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

TimeRelationIn9011::TimeRelationIn9011() : m_otherClock(), m_entryList() {}

//==============================================================================

TimeRelationIn9011::~TimeRelationIn9011() {}

//==============================================================================

std::streamsize TimeRelationIn9011::getSerializedSize() const
{
    std::streamsize result = std::streamsize(sizeof(uint32_t));
    result += m_otherClock.getSerializedSize();
    result += static_cast<std::streamsize>(
        m_entryList.size() * ((4 * std::streamsize(sizeof(NTPTime))) + (2 * std::streamsize(sizeof(double)))));
    return result;
}

//==============================================================================

bool TimeRelationIn9011::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    m_otherClock.serialize(os);

    ibeo::common::sdk::writeBE(os, uint32_t(m_entryList.size()));
    for (const auto& itr : m_entryList)
    {
        ibeo::common::sdk::writeBE(os, itr.m_refTime);
        ibeo::common::sdk::writeBE(os, itr.m_otherTime);
        ibeo::common::sdk::writeBE(os, itr.m_standardError);
        ibeo::common::sdk::writeBE(os, itr.m_maxDeviation);
        ibeo::common::sdk::writeBE(os, itr.m_slope);
        ibeo::common::sdk::writeBE(os, itr.m_correlationCoefficient);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool TimeRelationIn9011::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    m_otherClock.deserialize(is);

    uint32_t lineCount;
    ibeo::common::sdk::readBE(is, lineCount);
    m_entryList.resize(lineCount);

    NTPTime refTime;
    NTPTime otherTime;
    NTPTime standardError;
    NTPTime maxDeviation;
    double slope;
    double correlationCoefficient;
    for (auto& line : m_entryList)
    {
        ibeo::common::sdk::readBE(is, refTime);
        if (refTime.is_not_a_date_time())
        {
            return false;
            // 			throw std::runtime_error("reference time is not a date time");
        }
        line.m_refTime = refTime;
        ibeo::common::sdk::readBE(is, otherTime);
        line.m_otherTime = otherTime;

        ibeo::common::sdk::readBE(is, standardError);
        line.m_standardError = standardError;

        ibeo::common::sdk::readBE(is, maxDeviation);
        line.m_maxDeviation = maxDeviation;

        ibeo::common::sdk::readBE(is, slope);
        line.m_slope = slope;

        ibeo::common::sdk::readBE(is, correlationCoefficient);
        line.m_correlationCoefficient = correlationCoefficient;
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

TimeRelationIn9011::Entry::Entry()
  : m_refTime(NTPTime::getInvalidTime()),
    m_otherTime(NTPTime::getInvalidTime()),
    m_standardError(NTPTime::getInvalidTime()),
    m_maxDeviation(NTPTime::getInvalidTime()),
    m_slope(ibeo::common::sdk::NaN_double),
    m_correlationCoefficient(ibeo::common::sdk::NaN_double)
{}

//==============================================================================

TimeRelationIn9011::Entry::Entry(const TimeRelationIn9011::Entry& other)
  : m_refTime(other.m_refTime),
    m_otherTime(other.m_otherTime),
    m_standardError(other.m_standardError),
    m_maxDeviation(other.m_maxDeviation),
    m_slope(other.m_slope),
    m_correlationCoefficient(other.m_correlationCoefficient)
{}

//==============================================================================

TimeRelationIn9011::Entry& TimeRelationIn9011::Entry::operator=(const TimeRelationIn9011::Entry& other)
{
    if (&other != this)
    {
        m_refTime                = other.m_refTime;
        m_otherTime              = other.m_otherTime;
        m_standardError          = other.m_standardError;
        m_maxDeviation           = other.m_maxDeviation;
        m_slope                  = other.m_slope;
        m_correlationCoefficient = other.m_correlationCoefficient;
    }

    return *this;
}

//==============================================================================

bool operator==(const TimeRelationIn9011& lhs, const TimeRelationIn9011& rhs)
{
    const TimeRelationIn9011::EntryList lhsEntryList = lhs.getEntryList();
    const TimeRelationIn9011::EntryList rhsEntryList = rhs.getEntryList();
    if (lhsEntryList.size() != rhsEntryList.size())
    {
        return false;
    }
    if (!(lhs.getOtherClock() == rhs.getOtherClock()))
    {
        return false;
    }

    for (uint32_t ind = 0; ind < lhsEntryList.size(); ++ind)
    {
        if ((lhsEntryList[ind].m_refTime != rhsEntryList[ind].m_refTime)
            || (lhsEntryList[ind].m_otherTime != rhsEntryList[ind].m_otherTime)
            || (lhsEntryList[ind].m_standardError != rhsEntryList[ind].m_standardError)
            || (lhsEntryList[ind].m_maxDeviation != rhsEntryList[ind].m_maxDeviation)
            || !ibeo::common::sdk::fuzzyCompareT<7>(lhsEntryList[ind].m_slope, rhsEntryList[ind].m_slope)
            || !ibeo::common::sdk::fuzzyCompareT<7>(lhsEntryList[ind].m_correlationCoefficient,
                                                    rhsEntryList[ind].m_correlationCoefficient))
        {
            return false;
        }
    }
    return true;
}

//==============================================================================

bool operator!=(const TimeRelationIn9011& lhs, const TimeRelationIn9011& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date March 19, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationIn9010.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/Math.hpp>

#include <utility>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

TimeRelationIn9010::TimeRelationIn9010() : m_entryList() {}

//==============================================================================

TimeRelationIn9010::~TimeRelationIn9010() {}

//==============================================================================

std::streamsize TimeRelationIn9010::getSerializedSize() const
{
    std::streamsize result = std::streamsize(sizeof(uint32_t));
    for (const auto& itr : m_entryList)
    {
        result += std::streamsize(sizeof(NTPTime)) + std::streamsize(sizeof(uint8_t));
        if (itr.m_data)
        {
            result += std::streamsize(sizeof(uint64_t)) + std::streamsize(sizeof(double));
        }
    }
    return result;
}

//==============================================================================

bool TimeRelationIn9010::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());
    // size
    ibeo::common::sdk::writeBE(os, static_cast<uint32_t>(m_entryList.size()));

    for (const auto& itr : m_entryList)
    {
        ibeo::common::sdk::writeBE(os, itr.m_refTime);

        const bool hasData = (itr.m_data != nullptr);
        ibeo::common::sdk::writeBE(os, static_cast<uint8_t>(hasData));

        if (hasData)
        {
            ibeo::common::sdk::writeBE(os, itr.m_data->m_otherTime);
            ibeo::common::sdk::writeBE(os, itr.m_data->m_factor);
        }
    }
    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool TimeRelationIn9010::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    uint32_t size;
    ibeo::common::sdk::readBE(is, size);

    m_entryList.resize(size);

    for (auto& line : m_entryList)
    {
        NTPTime refTime;
        ibeo::common::sdk::readBE(is, refTime);
        line.m_refTime = refTime;

        uint8_t hasData;
        ibeo::common::sdk::readBE(is, hasData);

        if (hasData > 0)
        {
            line.m_data.reset(new EntryOptionalData());
            uint64_t microsecond;
            ibeo::common::sdk::readBE(is, microsecond);
            line.m_data->m_otherTime = static_cast<int64_t>(microsecond);
            ibeo::common::sdk::readBE(is, line.m_data->m_factor);

            if (std::isnan(line.m_data->m_factor))
            {
                return false;
                //throw std::runtime_error("NaN value detected.");
            }
            line.m_data->m_factorInv = 1.0 / line.m_data->m_factor;
        }
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

TimeRelationIn9010::Entry::Entry() : m_refTime(NTPTime::getInvalidTime()), m_data() {}

//==============================================================================

TimeRelationIn9010::Entry::Entry(const TimeRelationIn9010::Entry& other) : m_refTime(other.m_refTime), m_data()
{
    if (other.m_data)
    {
        m_data.reset(new EntryOptionalData());
        *m_data = *(other.m_data);
    }
}

//==============================================================================

TimeRelationIn9010::Entry& TimeRelationIn9010::Entry::operator=(const TimeRelationIn9010::Entry& other)
{
    if (&other != this)
    {
        m_refTime = other.m_refTime;

        if (other.m_data)
        {
            if (!m_data)
            {
                m_data.reset(new EntryOptionalData());
            }
            *m_data = *(other.m_data);
        }
        else
        {
            m_data.reset();
        }
    }
    return *this;
}

//==============================================================================

bool operator==(const TimeRelationIn9010::Entry& lhs, const TimeRelationIn9010::Entry& rhs)
{
    if ((lhs.m_refTime != rhs.m_refTime) // if ref time is not equal
        || (!lhs.m_data && rhs.m_data) // if lhs has no data but rhs has data
        || (lhs.m_data && !rhs.m_data)) // if lhs has data but rhs has no data
    {
        return false;
    }
    if ((lhs.m_data->m_otherTime != rhs.m_data->m_otherTime)
        || (!ibeo::common::sdk::fuzzyCompareT<7>(lhs.m_data->m_factor, rhs.m_data->m_factor)))
    {
        return false;
    }
    return true;
}

//==============================================================================

bool operator==(const TimeRelationIn9010& lhs, const TimeRelationIn9010& rhs)
{
    return (lhs.getEntryList() == rhs.getEntryList());
}

//==============================================================================

bool operator!=(const TimeRelationIn9010& lhs, const TimeRelationIn9010& rhs) { return !(lhs == rhs); }
//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

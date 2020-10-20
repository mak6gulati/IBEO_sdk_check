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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/datablocks/ClockType.hpp>
#include <ibeo/common/sdk/Time.hpp>
#include <deque>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class TimeRelationIn9011
{
public:
    //Data stored alongside each Ref time in the EntryDataList
    struct Entry
    {
        Entry();
        Entry(Entry const&);
        Entry& operator=(Entry const&);

    public:
        NTPTime m_refTime;
        NTPTime m_otherTime;
        NTPTime m_standardError;
        NTPTime m_maxDeviation;
        double m_slope;
        double m_correlationCoefficient;
    }; // Entry

    using EntryList = std::deque<Entry>;

public:
    TimeRelationIn9011();
    virtual ~TimeRelationIn9011();

public:
    std::streamsize getSerializedSize() const;
    bool deserialize(std::istream& is);
    bool serialize(std::ostream& os) const;

public: // setter
    void setOtherClock(const ClockType otherClock) { m_otherClock = otherClock; }

    void setEntryList(const EntryList& entryList) { m_entryList = entryList; }

public: // getter
    const ClockType getOtherClock() const { return m_otherClock; }

    const EntryList& getEntryList() const { return m_entryList; }

    EntryList& getEntryList() { return m_entryList; }

protected:
    ClockType m_otherClock;

    // uint32_t; serialization size of the m_entryList
    EntryList m_entryList;
}; // TimeRelationIn9011

//==============================================================================

bool operator==(const TimeRelationIn9011& lhs, const TimeRelationIn9011& rhs);
bool operator!=(const TimeRelationIn9011& lhs, const TimeRelationIn9011& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

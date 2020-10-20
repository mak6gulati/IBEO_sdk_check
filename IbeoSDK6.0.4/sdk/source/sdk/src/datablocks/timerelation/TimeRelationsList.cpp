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

//==============================================================================
#include <ibeo/common/sdk/datablocks/timerelation/TimeRelationsList.hpp>

#include <utility>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {

using ibeo::common::sdk::timerelation::operator*;
using ibeo::common::sdk::timerelation::operator/;

//==============================================================================

TimeRelationsList::TimeRelationsList() : DataContainerBase() { clear(); }

//==============================================================================

TimeRelationsList::TimeRelationsList(const TimeRelationsList9010& other)
{
    setRefTimeType(ClockType(ClockType::unknownId, ClockType::ClockName::Unknown));

    ClockType otherClock;
    for (const auto& relation : other.getTimeRelations())
    {
        otherClock                     = relation.first;
        m_timeRelationsMap[otherClock] = relation.second;
    }
}

//==============================================================================

TimeRelationsList::TimeRelationsList(const TimeRelationsList9011& other)
{
    setRefTimeType(other.getRefClock());

    // 	TimeRelation9011 tr9011;
    ClockType otherClock;
    for (const auto& relation : other.getTimeRelations())
    {
        otherClock                     = relation.getOtherClock();
        m_timeRelationsMap[otherClock] = relation;
    }
}

//==============================================================================

TimeRelationsList& TimeRelationsList::operator=(const TimeRelationsList9010& other)
{
    setRefTimeType(ClockType(ClockType::unknownId, ClockType::ClockName::Unknown));

    ClockType otherClock;
    for (const auto& relation : other.getTimeRelations())
    {
        m_timeRelationsMap[relation.first] = relation.second;
    }

    return *this;
}

//==============================================================================

TimeRelationsList& TimeRelationsList::operator=(const TimeRelationsList9011& other)
{
    setRefTimeType(other.getRefClock());

    ClockType otherClock;
    for (const auto& relation : other.getTimeRelations())
    {
        otherClock                     = relation.getOtherClock();
        m_timeRelationsMap[otherClock] = relation;
    }

    return *this;
}

//==============================================================================

bool TimeRelationsList::isRefTimeGps() const
{
    return (m_refTimeType.getClockName() == ibeo::common::sdk::ClockType::ClockName::GpsImu);
}

//==============================================================================

void TimeRelationsList::clear() { m_timeRelationsMap.clear(); }

//==============================================================================

bool TimeRelationsList::hasTimeRelation(const ClockType type) const { return m_timeRelationsMap.count(type) > 0; }

//==============================================================================

TimeRelation& TimeRelationsList::getTimeRelation(const ClockType type) { return m_timeRelationsMap.at(type); }

//==============================================================================

const TimeRelationsList::TimeRelationsMap& TimeRelationsList::getTimeRelations() const { return m_timeRelationsMap; }

//==============================================================================

void TimeRelationsList::ensureTimeRelationExists(const ClockType type)
{
    if (m_timeRelationsMap.count(type) == 0)
    {
        m_timeRelationsMap[type] = TimeRelation();
    }
}

//==============================================================================

std::string TimeRelationsList::debugToString() const
{
    std::stringstream sstr;

    sstr << "TimeRelationsList containing " << m_timeRelationsMap.size() << " TimeRelations" << std::endl;

    for (const auto& timeRelation : m_timeRelationsMap)
    {
        sstr << timeRelation.first.getClockId() << ": " << timeRelation.second.debugToString();
    }

    return sstr.str();
}

//==============================================================================

bool operator==(const TimeRelationsList& lhs, const TimeRelationsList& rhs)
{
    if ((lhs.getRefTimeType() == rhs.getRefTimeType())
        && (lhs.getTimeRelations().size() == rhs.getTimeRelations().size()))
    {
        return (lhs.getTimeRelations() == rhs.getTimeRelations());
    }
    return false;
}

//==============================================================================

bool operator!=(const TimeRelationsList& lhs, const TimeRelationsList& rhs) { return !(lhs == rhs); }
//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/ClockType.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationIn9011.hpp>
#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief List of relations for the reference timebase to an
//! 'Other' timebase
//!
//! General data type: \ref ibeo::common::sdk::TimeRelationsList
class TimeRelationsList9011 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    using TimeRelationVector = std::vector<TimeRelationIn9011>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.timerelationslist9011"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    TimeRelationsList9011();
    ~TimeRelationsList9011() override;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public: // setter
    void setRefClock(const ClockType refClock) { m_referenceClock = refClock; }

    void setTimeRelations(const TimeRelationVector& timerRelations) { m_timeRelations = timerRelations; }

public: // getter
    const ClockType getRefClock() const { return m_referenceClock; }

    const TimeRelationVector& getTimeRelations() const { return m_timeRelations; }

    // Wrapper for getTimeRelationsMap
    TimeRelationVector& getTimeRelations() { return m_timeRelations; }

protected:
    ClockType m_referenceClock;
    TimeRelationVector m_timeRelations;
}; // TimeRelationsList9011

//==============================================================================

bool operator==(const TimeRelationsList9011& lhs, const TimeRelationsList9011& rhs);

//==============================================================================

bool operator!=(const TimeRelationsList9011& lhs, const TimeRelationsList9011& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

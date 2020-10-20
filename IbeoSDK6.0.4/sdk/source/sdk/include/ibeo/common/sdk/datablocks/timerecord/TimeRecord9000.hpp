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
//!\date Mar 21, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/ClockType.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

#include <array>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief TimeRecord
//!
//! This data type contains the local system time as well as a time signal that is provided by an external device,
//! e.g. a GPS receiver connected to the Ibeo ECU. This data can be used for offline transformation of the time base
//! of the recorded data stream.
class TimeRecord9000 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    static const uint8_t nbOfReserved = 4;

public:
    enum class FixMode : uint8_t
    {
        NotSeen = 0,
        None    = 1,
        Fix2D   = 2,
        Fix3D   = 3
    };

    using NTPTimeVector = std::vector<NTPTime>;
    using FixModeVector = std::vector<FixMode>;
    using ReservedArray = std::array<uint32_t, nbOfReserved>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.timerecord9000"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    TimeRecord9000();
    virtual ~TimeRecord9000();

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    ClockType getInternalClockType() const { return m_internalClockType; }
    ClockType getExternalClockType() const { return m_externalClockType; }
    const NTPTimeVector& getInternalClockTimes() const { return m_internalClockTimes; }
    const NTPTimeVector& getExternalClockTimes() const { return m_externalClockTimes; }
    const FixModeVector& getFixModes() const { return m_fixModes; }

    uint32_t getReserved(const uint8_t idx) const { return m_reserved.at(idx); }
    const ReservedArray& getReserved() const { return m_reserved; }

public:
    void setInternalClockType(const ClockType& clockType) { this->m_internalClockType = clockType; }
    void setExternalClockType(const ClockType& clockType) { this->m_externalClockType = clockType; }
    bool setTimesAndFixeModes(const NTPTimeVector& externalTimes,
                              const NTPTimeVector& internalTimes,
                              const FixModeVector& fixModes);

protected:
    ClockType m_externalClockType{};
    ClockType m_internalClockType{};
    NTPTimeVector m_externalClockTimes{};
    NTPTimeVector m_internalClockTimes{};
    FixModeVector m_fixModes;

    ReservedArray m_reserved{{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU}};
}; // TimeRecord9000

//==============================================================================

bool operator==(const TimeRecord9000& lhs, const TimeRecord9000& rhs);
bool operator!=(const TimeRecord9000& lhs, const TimeRecord9000& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

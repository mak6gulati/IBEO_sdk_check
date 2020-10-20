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
//!\date 02.November 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! current mission status
class MissionHandlingStatus3530 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    //! \enum State
    //! State of mission handling module
    //! This type is serialized as UINT8, 255 is the maximum value
    // ----------------------------------------
    enum class State : uint8_t
    {
        Idle              = 0,
        MissionInProgress = 1,
        NotReady          = 255
    };

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.missionhandlingstatus3530"};

    // in C++14 this could be a constexpr
    static uint64_t getClassIdHashStatic() { return hash(containerType); }

    static constexpr uint8_t nbOfReserved = 4;

public:
    using ArrayOfReserved = std::array<uint32_t, nbOfReserved>;

public:
    MissionHandlingStatus3530();
    virtual ~MissionHandlingStatus3530() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public: // setters and getters
    void setTimestamp(const NTPTime& timestamp) { this->m_timestamp = timestamp; }
    void setState(const State state) { this->m_state = state; }
    void setMissionId(const uint32_t missionId) { this->m_missionId = missionId; }

    const NTPTime& getTimestamp() const { return m_timestamp; }
    State getState() const { return m_state; }
    uint32_t getMissionId() const { return m_missionId; }
    ArrayOfReserved getReserved() const& { return m_reserved; }

protected:
    NTPTime m_timestamp{}; //!< Timestamp of status message
    State m_state{State::NotReady}; //!< Indicates current state of mission handling module
    uint32_t m_missionId{0}; //!< Id of current mission

private:
    ArrayOfReserved m_reserved{{}};

}; //MissionHandlingStatus3530

//==============================================================================

bool operator==(const MissionHandlingStatus3530& lhs, const MissionHandlingStatus3530& rhs);
bool operator!=(const MissionHandlingStatus3530& lhs, const MissionHandlingStatus3530& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

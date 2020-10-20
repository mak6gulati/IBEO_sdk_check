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
//!\date 09.November 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/trafficlight/TrafficLightState.hpp>
#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief A container for all traffic lights and their state.
//!
//! Sepcial data type: \ref ibeo::common::sdk::TrafficLightStateList3600
class TrafficLightStateList : public DataContainerBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    constexpr static const char* const containerType{"ibeo.sdk.generalcontainer.trafficlightstatelist"};
    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    TrafficLightStateList();
    ~TrafficLightStateList() override = default;

public:
    const std::vector<TrafficLightState>& getTrafficLightStates() const { return m_trafficLightStates; }

public:
    void setTrafficLightStates(const std::vector<TrafficLightState>& trafficLightStates)
    {
        m_trafficLightStates = trafficLightStates;
    }
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

private:
    std::vector<TrafficLightState> m_trafficLightStates{};

}; // TrafficLightStateList

//==============================================================================

bool operator==(const TrafficLightStateList& lhs, const TrafficLightStateList& rhs);
bool operator!=(const TrafficLightStateList& lhs, const TrafficLightStateList& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

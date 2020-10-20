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
//!\date Aug 29, 2018
//------------------------------------------------------------------------------

#include "TrafficLightStateListTestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

TrafficLightStateListTestSupport::TrafficLightStateListTestSupport() : TestSupport() {}

//==============================================================================

TrafficLightStateList TrafficLightStateListTestSupport::createTrafficLightStateList()
{
    TrafficLightStateList trafficLightStateList;
    fillRandomly(trafficLightStateList);
    return trafficLightStateList;
}

//==============================================================================

void TrafficLightStateListTestSupport::fillRandomly(TrafficLightStateList& randTrafficLightStateList)
{
    std::vector<TrafficLightState> randTrafficLightStates;
    const uint8_t nbOfTrafficLightStates = getDifferentRandValue<uint8_t>(0);
    randTrafficLightStates.resize(nbOfTrafficLightStates);

    for (uint8_t i = 0; i < nbOfTrafficLightStates; ++i)
    {
        TrafficLightState trafficLightState;
        trafficLightState.setId(getDifferentRandValue<uint32_t>(trafficLightState.getId()));
        trafficLightState.setPhase(static_cast<TrafficLightState::Phase>(
            getDifferentRandValue<uint8_t>(0, 4, static_cast<uint8_t>(trafficLightState.getPhase()))));
        trafficLightState.setTimestampFromTrafficLight(getRandValue<NTPTime>());
        trafficLightState.setTimeIntervalAbsoluteBegin(getRandValue<NTPTime>());
        trafficLightState.setTimeIntervalAbsoluteEnd(getRandValue<NTPTime>());
        trafficLightState.setTimeIntervalRelativeBegin(getRandValue<NTPTime>());
        trafficLightState.setTimeIntervalRelativeEnd(getRandValue<NTPTime>());
        randTrafficLightStates[i] = trafficLightState;
    }

    randTrafficLightStateList.setTrafficLightStates(randTrafficLightStates);
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

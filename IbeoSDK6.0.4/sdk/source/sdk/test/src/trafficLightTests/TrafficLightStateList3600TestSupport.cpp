//==============================================================================
//!\file
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 02, 2019
//------------------------------------------------------------------------------

#include "TrafficLightStateList3600TestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

TrafficLightStateList3600TestSupport::TrafficLightStateList3600TestSupport() : TestSupport() {}

//==============================================================================

TrafficLightStateList3600 TrafficLightStateList3600TestSupport::createTrafficLightStateList3600()
{
    TrafficLightStateList3600 trafficLightStateList;
    fillRandomly3600(trafficLightStateList);
    return trafficLightStateList;
}

//==============================================================================

void TrafficLightStateList3600TestSupport::fillRandomly3600(TrafficLightStateList3600& randTrafficLightStateList)
{
    std::vector<TrafficLightStateIn3600> randTrafficLightStates;
    const uint8_t nbOfTrafficLightStates = getDifferentRandValue<uint8_t>(0);
    randTrafficLightStates.resize(nbOfTrafficLightStates);

    for (uint8_t i = 0; i < nbOfTrafficLightStates; ++i)
    {
        TrafficLightStateIn3600 trafficLightState;
        trafficLightState.setId(getDifferentRandValue<uint32_t>(trafficLightState.getId()));
        trafficLightState.setPhase(static_cast<TrafficLightStateIn3600::Phase>(
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

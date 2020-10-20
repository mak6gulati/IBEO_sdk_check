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
//!\date Feb 24, 2017
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/ClockType.hpp>
#include "TimeRecord9000TestSupport.hpp"

#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

TimeRecord9000TestSupport::TimeRecord9000TestSupport() : TestSupport() {}

//==============================================================================

TimeRecord9000TestSupport::~TimeRecord9000TestSupport() {}

//==============================================================================

ibeo::common::sdk::TimeRecord9000 TimeRecord9000TestSupport::createTimeRecord9000()
{
    ibeo::common::sdk::TimeRecord9000 t;
    fillRandomly(t);
    return t;
}

//==============================================================================

void TimeRecord9000TestSupport::fillRandomly(ibeo::common::sdk::TimeRecord9000& tr)
{
    using C                        = TimeRecord9000;
    const uint8_t nbOfMeasurements = getRandValue<uint8_t>();
    std::vector<NTPTime> internalTime;
    std::vector<NTPTime> externalTime;
    std::vector<C::FixMode> fixModeVector;

    for (int i = 0; i < nbOfMeasurements; ++i)
    {
        const NTPTime genIntTime = getRandValue<NTPTime>();
        internalTime.push_back(genIntTime);
    }

    for (int i = 0; i < nbOfMeasurements; ++i)
    {
        const NTPTime genExtTime = getRandValue<NTPTime>();
        externalTime.push_back(genExtTime);
    }

    for (int i = 0; i < nbOfMeasurements; ++i)
    {
        const C::FixMode fixMode = C::FixMode(getRandValue<uint8_t>() % 4);
        fixModeVector.push_back(fixMode);
    }

    tr.setTimesAndFixeModes(externalTime, internalTime, fixModeVector);

    ibeo::common::sdk::ClockType clockInternal(getRandValue<uint8_t>(),
                                               ibeo::common::sdk::ClockType::ClockName(getRandValue<uint8_t>() % 7));
    ibeo::common::sdk::ClockType clockExternal(getRandValue<uint8_t>(),
                                               ibeo::common::sdk::ClockType::ClockName(getRandValue<uint8_t>() % 7));
    tr.setInternalClockType(clockInternal);
    tr.setExternalClockType(clockExternal);
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

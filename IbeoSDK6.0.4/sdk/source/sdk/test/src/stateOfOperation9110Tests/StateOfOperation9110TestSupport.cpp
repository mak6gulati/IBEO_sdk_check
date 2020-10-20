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
//!\date October 11, 2017
//------------------------------------------------------------------------------

#include "StateOfOperation9110TestSupport.hpp"

#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

StateOfOperation9110TestSupport::StateOfOperation9110TestSupport() : TestSupport() {}

//==============================================================================

StateOfOperation9110TestSupport::~StateOfOperation9110TestSupport() {}

//==============================================================================

StateOfOperation9110 StateOfOperation9110TestSupport::createStateOfOperation9110C()
{
    StateOfOperation9110 o;
    fillRandomly(o);
    return o;
}

//==============================================================================

void StateOfOperation9110TestSupport::fillRandomly(StateOfOperation9110& od)
{
    const StateOfOperation9110::Operation operation
        = static_cast<StateOfOperation9110::Operation>(getRandValue<uint8_t>(3) + 1);
    od.setOperation(operation);

    const StateOfOperation9110::DriverInterrupt interrupt
        = static_cast<StateOfOperation9110::DriverInterrupt>(getRandValue<uint8_t>(3) + 1);
    od.setDriverInterrupt(interrupt);

    const bool takeOver = getRandValue<bool>();
    od.setTakeOverRequest(takeOver);

    const NTPTime measEcu(getRandValue<NTPTime>());
    const NTPTime recEcu(getRandValue<NTPTime>());
    const NTPTime meas(getRandValue<NTPTime>());
    const NTPTime rec(getRandValue<NTPTime>());
    const NTPTime raw(getRandValue<NTPTime>());
    const ibeo::common::sdk::ClockType clock(getRandValue<uint8_t>(),
                                             ibeo::common::sdk::ClockType::ClockName(getRandValue<uint8_t>() % 7));
    const ibeo::common::sdk::Timestamp timestamp(measEcu, recEcu, raw, meas, rec, clock);
    od.setTimestamp(timestamp);
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

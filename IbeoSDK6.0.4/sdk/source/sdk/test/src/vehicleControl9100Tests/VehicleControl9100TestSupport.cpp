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
//!\date August 23, 2017
//------------------------------------------------------------------------------

//==============================================================================

#include "VehicleControl9100TestSupport.hpp"

#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

VehicleControl9100 VehicleControl9100TestSupport::createVehicleControl9100()
{
    VehicleControl9100 vc;
    fillRandomly(vc);
    return vc;
}

//==============================================================================

void VehicleControl9100TestSupport::fillRandomly(VehicleControl9100& vc)
{
    vc.setAccelerationValue(getNonNanRandValue<float>());
    vc.setDoStop(getRandValue<bool>());
    vc.setIndicatorState(static_cast<VehicleControl9100::IndicatorState>(getRandValue<uint8_t>()));
    vc.setSourceType(static_cast<VehicleControl9100::SourceType>(getRandValue<uint8_t>()));
    vc.setSteeringType(static_cast<VehicleControl9100::SteeringType>(getRandValue<uint8_t>()));

    const float steeringValue = getNonNanRandValue<float>();
    vc.setSteeringValue(steeringValue);

    const float distance = getNonNanRandValue<float>();
    vc.setStopDistance(distance);

    const ibeo::common::sdk::ClockType clock(getRandValue<uint8_t>(),
                                             ibeo::common::sdk::ClockType::ClockName(getRandValue<uint8_t>() % 7));

    const NTPTime measEcu(getRandValue<NTPTime>());
    const NTPTime recEcu(getRandValue<NTPTime>());
    const NTPTime meas(getRandValue<NTPTime>());
    const NTPTime rec(getRandValue<NTPTime>());
    const NTPTime raw(getRandValue<NTPTime>());
    const ibeo::common::sdk::Timestamp timestamp(measEcu, recEcu, raw, meas, rec, clock);
    vc.setTimestamp(timestamp);
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

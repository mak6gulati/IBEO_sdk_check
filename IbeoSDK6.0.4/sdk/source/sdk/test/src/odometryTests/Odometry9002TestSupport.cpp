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
//!\date Mar 28, 2017
//------------------------------------------------------------------------------

//==============================================================================

#include "Odometry9002TestSupport.hpp"

#include <cmath>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

template<>
void OdometryTestSupport::fillRandomly(Odometry9002& od)
{
    od.setSteeringAngle(getRandValue<double>());
    od.setSteeringWheelAngle(getRandValue<double>());
    od.setSteeringWheelAngleVelocity(getRandValue<double>());
    od.setWheelSpeedFL(getRandValue<double>());
    od.setWheelSpeedFR(getRandValue<double>());
    od.setWheelSpeedRL(getRandValue<double>());
    od.setWheelSpeedRR(getRandValue<double>());
    od.setWheelCircumference(getRandValue<double>());
    od.setVehVelocity(getRandValue<double>());
    od.setVehAcceleration(getRandValue<double>());
    od.setVehYawRate(getRandValue<double>());

    const ibeo::common::sdk::ClockType clock(getRandValue<uint8_t>(),
                                             ibeo::common::sdk::ClockType::ClockName(getRandValue<uint8_t>() % 7));

    const NTPTime measEcu(getRandValue<NTPTime>());
    const NTPTime recEcu(getRandValue<NTPTime>());
    const NTPTime meas(getRandValue<NTPTime>());
    const NTPTime rec(getRandValue<NTPTime>());
    const NTPTime raw(getRandValue<NTPTime>());
    const ibeo::common::sdk::Timestamp timestamp(measEcu, recEcu, raw, meas, rec, clock);
    od.setTimestamp(timestamp);

    od.setWheelBase(getRandValue<float>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

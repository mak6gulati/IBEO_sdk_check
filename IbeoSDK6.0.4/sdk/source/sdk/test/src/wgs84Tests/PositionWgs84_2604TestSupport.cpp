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
//!\date Feb 05, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "PositionWgs84_2604TestSupport.hpp"

#include <inttypes.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

void PositionWgs84_2604TestSupport::fillRandomly(PositionWgs84& wgs)
{
    wgs.setUsSinceStartup(getRandValue<uint32_t>());
    wgs.setTimestamp(getRandValue<NTPTime>());
    wgs.setDeviceId(getRandValue<uint8_t>());
    wgs.setLatitudeInRad(getRandValue<uint8_t>());
    wgs.setLatitudeSigmaInMeter(getRandValue<double_t>());
    wgs.setLongitudeInRad(getRandValue<uint8_t>());
    wgs.setLongitudeSigmaInMeter(getRandValue<double_t>());
    wgs.setAltitudeInMeterMSL(getRandValue<double_t>());
    wgs.setAltitudeSigmaInMeterMSL(getRandValue<double_t>());

    wgs.setCourseAngleInRad(getRandValue<double_t>());
    wgs.setCourseAngleSigmaInRad(getRandValue<double_t>());

    wgs.setYawAngleInRad(getRandValue<double_t>());
    wgs.setYawAngleSigmaInRad(getRandValue<double_t>());
    wgs.setPitchAngleInRad(getRandValue<double_t>());
    wgs.setPitchAngleSigmaInRad(getRandValue<double_t>());
    wgs.setRollAngleInRad(getRandValue<double_t>());
    wgs.setRollAngleSigmaInRad(getRandValue<double_t>());

    wgs.setSource(randomSourceType());
}

//==============================================================================

PositionWgs84::SourceType PositionWgs84_2604TestSupport::randomSourceType()
{
    return static_cast<PositionWgs84::SourceType>(getRandValue<uint8_t>(11));
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

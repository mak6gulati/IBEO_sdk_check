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
//!\date Apr 07, 2017
//------------------------------------------------------------------------------

#include "GpsImu9001TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/ClockType.hpp>
#include <ibeo/common/sdk/datablocks/Timestamp.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

template<>
void GpsImuTestSupport::fillRandomly(GpsImu9001& gpsImu)
{
    gpsImu.setLatitudeInRad(getRandValue<double>());
    gpsImu.setLatitudeSigmaInMeter(getRandValue<double>());
    gpsImu.setLongitudeInRad(getRandValue<double>());
    gpsImu.setLongitudeSigmaInMeter(getRandValue<double>());
    gpsImu.setAltitudeInMeter(getRandValue<double>());
    gpsImu.setAltitudeSigmaInMeter(getRandValue<double>());
    gpsImu.setCourseAngleInRad(getRandValue<double>());
    gpsImu.setCourseAngleSigmaInRad(getRandValue<double>());
    gpsImu.setYawAngleInRad(getRandValue<double>());
    gpsImu.setYawAngleSigmaInRad(getRandValue<double>());
    gpsImu.setPitchAngleInRad(getRandValue<double>());
    gpsImu.setPitchAngleSigmaInRad(getRandValue<double>());
    gpsImu.setRollAngleInRad(getRandValue<double>());
    gpsImu.setRollAngleSigmaInRad(getRandValue<double>());
    gpsImu.setCrossAccelerationInMeterPerSecond2(getRandValue<double>());
    gpsImu.setCrossAccelerationSigmaInMeterPerSecond2(getRandValue<double>());
    gpsImu.setLongitudinalAccelerationInMeterPerSecond2(getRandValue<double>());
    gpsImu.setLongitudinalAccelerationSigmaInMeterPerSecond2(getRandValue<double>());
    gpsImu.setVerticalAccelerationInMeterPerSecond2(getRandValue<double>());
    gpsImu.setVerticalAccelerationSigmaInMeterPerSecond2(getRandValue<double>());
    gpsImu.setVelocityNorthInMeterPerSecond(getRandValue<double>());
    gpsImu.setVelocityNorthSigmaInMeterPerSecond(getRandValue<double>());
    gpsImu.setVelocityWestInMeterPerSecond(getRandValue<double>());
    gpsImu.setVelocityWestSigmaInMeterPerSecond(getRandValue<double>());
    gpsImu.setVelocityUpInMeterPerSecond(getRandValue<double>());
    gpsImu.setVelocityUpSigmaInMeterPerSecond(getRandValue<double>());
    gpsImu.setVelocityXInMeterPerSecond(getRandValue<double>());
    gpsImu.setVelocityXSigmaInMeterPerSecond(getRandValue<double>());
    gpsImu.setVelocityYInMeterPerSecond(getRandValue<double>());
    gpsImu.setVelocityYSigmaInMeterPerSecond(getRandValue<double>());
    gpsImu.setVelocityZInMeterPerSecond(getRandValue<double>());
    gpsImu.setVelocityZSigmaInMeterPerSecond(getRandValue<double>());
    gpsImu.setRollRateInRadPerSecond(getRandValue<double>());
    gpsImu.setRollRateSigmaInRadPerSecond(getRandValue<double>());
    gpsImu.setYawRateInRadPerSecond(getRandValue<double>());
    gpsImu.setYawRateSigmaInRadPerSecond(getRandValue<double>());
    gpsImu.setPitchRateInRadPerSecond(getRandValue<double>());
    gpsImu.setPitchRateSigmaInRadPerSecond(getRandValue<double>());
    gpsImu.setGpsStatus(getRandValue<double>());
    gpsImu.setNoOfSatellites(getRandValue<uint8_t>());
    gpsImu.setGpsDilutionOfPrecisionX(getRandValue<double>());
    gpsImu.setGpsDilutionOfPrecisionY(getRandValue<double>());
    gpsImu.setGpsDilutionOfPrecisionZ(getRandValue<double>());
    gpsImu.setGpsDilutionOfPrecisionVertical(getRandValue<double>());
    gpsImu.setGpsDilutionOfPrecisionPosition(getRandValue<double>());

    gpsImu.setTimestamp(Timestamp(getRandValue<NTPTime>(),
                                  getRandValue<NTPTime>(),
                                  getRandValue<NTPTime>(),
                                  getRandValue<NTPTime>(),
                                  getRandValue<NTPTime>(),
                                  ClockType(getRandValue<uint8_t>(), ClockType::ClockName(getRandValue<uint8_t>()))));

    gpsImu.setSource(static_cast<GpsImuSourceIn9001>(getRandValue<uint8_t>()));
    gpsImu.setInsQuality(static_cast<GpsImuInsQualityIn9001>(getRandValue<uint8_t>()));
}
//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

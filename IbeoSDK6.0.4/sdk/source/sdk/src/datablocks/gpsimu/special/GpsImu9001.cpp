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
//!\date Mar 23, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

GpsImu9001::GpsImu9001() : SpecializedDataContainer{} {}

//==============================================================================
//==============================================================================
//==============================================================================

bool operator==(const GpsImu9001& lhs, const GpsImu9001& rhs)
{
    return doubleEqual(lhs.getLatitudeInRad(), rhs.getLatitudeInRad())
           && doubleEqual(lhs.getLatitudeSigmaInMeter(), rhs.getLatitudeSigmaInMeter())
           && doubleEqual(lhs.getLongitudeInRad(), rhs.getLongitudeInRad())
           && doubleEqual(lhs.getLongitudeSigmaInMeter(), rhs.getLongitudeSigmaInMeter())
           && doubleEqual(lhs.getAltitudeInMeter(), rhs.getAltitudeInMeter())
           && doubleEqual(lhs.getAltitudeSigmaInMeter(), rhs.getAltitudeSigmaInMeter())
           && doubleEqual(lhs.getCourseAngleInRad(), rhs.getCourseAngleInRad())
           && doubleEqual(lhs.getCourseAngleSigmaInRad(), rhs.getCourseAngleSigmaInRad())
           && doubleEqual(lhs.getYawAngleInRad(), rhs.getYawAngleInRad())
           && doubleEqual(lhs.getYawAngleSigmaInRad(), rhs.getYawAngleSigmaInRad())
           && doubleEqual(lhs.getPitchAngleInRad(), rhs.getPitchAngleInRad())
           && doubleEqual(lhs.getPitchAngleSigmaInRad(), rhs.getPitchAngleSigmaInRad())
           && doubleEqual(lhs.getRollAngleInRad(), rhs.getRollAngleInRad())
           && doubleEqual(lhs.getRollAngleSigmaInRad(), rhs.getRollAngleSigmaInRad())
           && doubleEqual(lhs.getCrossAccelerationInMeterPerSecond2(), rhs.getCrossAccelerationInMeterPerSecond2())
           && doubleEqual(lhs.getCrossAccelerationSigmaInMeterPerSecond2(),
                          rhs.getCrossAccelerationSigmaInMeterPerSecond2())
           && doubleEqual(lhs.getLongitudinalAccelerationInMeterPerSecond2(),
                          rhs.getLongitudinalAccelerationInMeterPerSecond2())
           && doubleEqual(lhs.getLongitudinalAccelerationSigmaInMeterPerSecond2(),
                          rhs.getLongitudinalAccelerationSigmaInMeterPerSecond2())
           && doubleEqual(lhs.getVerticalAccelerationInMeterPerSecond2(),
                          rhs.getVerticalAccelerationInMeterPerSecond2())
           && doubleEqual(lhs.getVerticalAccelerationSigmaInMeterPerSecond2(),
                          rhs.getVerticalAccelerationSigmaInMeterPerSecond2())
           && doubleEqual(lhs.getVelocityNorthInMeterPerSecond(), rhs.getVelocityNorthInMeterPerSecond())
           && doubleEqual(lhs.getVelocityNorthSigmaInMeterPerSecond(), rhs.getVelocityNorthSigmaInMeterPerSecond())
           && doubleEqual(lhs.getVelocityWestInMeterPerSecond(), rhs.getVelocityWestInMeterPerSecond())
           && doubleEqual(lhs.getVelocityWestSigmaInMeterPerSecond(), rhs.getVelocityWestSigmaInMeterPerSecond())
           && doubleEqual(lhs.getVelocityUpInMeterPerSecond(), rhs.getVelocityUpInMeterPerSecond())
           && doubleEqual(lhs.getVelocityUpSigmaInMeterPerSecond(), rhs.getVelocityUpSigmaInMeterPerSecond())
           && doubleEqual(lhs.getVelocityXInMeterPerSecond(), rhs.getVelocityXInMeterPerSecond())
           && doubleEqual(lhs.getVelocityXSigmaInMeterPerSecond(), rhs.getVelocityXSigmaInMeterPerSecond())
           && doubleEqual(lhs.getVelocityYInMeterPerSecond(), rhs.getVelocityYInMeterPerSecond())
           && doubleEqual(lhs.getVelocityYSigmaInMeterPerSecond(), rhs.getVelocityYSigmaInMeterPerSecond())
           && doubleEqual(lhs.getVelocityZInMeterPerSecond(), rhs.getVelocityZInMeterPerSecond())
           && doubleEqual(lhs.getVelocityZSigmaInMeterPerSecond(), rhs.getVelocityZSigmaInMeterPerSecond())
           && doubleEqual(lhs.getRollRateInRadPerSecond(), rhs.getRollRateInRadPerSecond())
           && doubleEqual(lhs.getRollRateSigmaInRadPerSecond(), rhs.getRollRateSigmaInRadPerSecond())
           && doubleEqual(lhs.getYawRateInRadPerSecond(), rhs.getYawRateInRadPerSecond())
           && doubleEqual(lhs.getYawRateSigmaInRadPerSecond(), rhs.getYawRateSigmaInRadPerSecond())
           && doubleEqual(lhs.getPitchRateInRadPerSecond(), rhs.getPitchRateInRadPerSecond())
           && doubleEqual(lhs.getPitchRateSigmaInRadPerSecond(), rhs.getPitchRateSigmaInRadPerSecond())
           && doubleEqual(lhs.getGpsStatus(), rhs.getGpsStatus())
           && (lhs.getNoOfSatellites() == rhs.getNoOfSatellites())
           && doubleEqual(lhs.getGpsDilutionOfPrecisionX(), rhs.getGpsDilutionOfPrecisionX())
           && doubleEqual(lhs.getGpsDilutionOfPrecisionY(), rhs.getGpsDilutionOfPrecisionY())
           && doubleEqual(lhs.getGpsDilutionOfPrecisionZ(), rhs.getGpsDilutionOfPrecisionZ())
           && doubleEqual(lhs.getGpsDilutionOfPrecisionVertical(), rhs.getGpsDilutionOfPrecisionVertical())
           && doubleEqual(lhs.getGpsDilutionOfPrecisionPosition(), rhs.getGpsDilutionOfPrecisionPosition())
           && (lhs.getTimestamp() == rhs.getTimestamp()) && (lhs.getSource() == rhs.getSource())
           && (lhs.getInsQuality() == rhs.getInsQuality()) && (lhs.getReserved() == rhs.getReserved());
}
//==============================================================================

bool operator!=(const GpsImu9001& lhs, const GpsImu9001& rhs) { return !(lhs == rhs); }

//==============================================================================
// Helper functions for gpsimu list im-/export.
//==============================================================================

template<>
void writeBE<GpsImuSourceIn9001>(std::ostream& os, const GpsImuSourceIn9001& s)
{
    writeBE(os, uint8_t(s));
}

//==============================================================================

template<>
void writeBE<GpsImuInsQualityIn9001>(std::ostream& os, const GpsImuInsQualityIn9001& s)
{
    writeBE(os, uint8_t(s));
}

//==============================================================================

template<>
void readBE<GpsImuSourceIn9001>(std::istream& is, GpsImuSourceIn9001& tc)
{
    uint8_t rd8;
    readBE(is, rd8);
    tc = GpsImuSourceIn9001(rd8);
}

//==============================================================================

template<>
void readBE<GpsImuInsQualityIn9001>(std::istream& is, GpsImuInsQualityIn9001& tc)
{
    uint8_t rd8;
    readBE(is, rd8);
    tc = GpsImuInsQualityIn9001(rd8);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Sept 04, 2018
//------------------------------------------------------------------------------

#include "Position84WgsSequence3510TestSupport.hpp"

#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

void PositionWgs84Sequence3510TestSupport::fillRandomly(PositionWgs84Sequence3510& ps)
{
    ps.setTimestamp(getRandValue<NTPTime>());
    ps.setSourceType(static_cast<PositionWgs84Sequence3510::SourceType>(getRandValue<uint8_t>()));
    ps.setId(getDifferentRandValue<uint32_t>(ps.getId()));

    const uint8_t sequenceSize = getRandValue<uint8_t>();
    std::vector<PositionWgs84> positionSequence(sequenceSize, PositionWgs84());
    for (uint8_t i = 0; i < sequenceSize; ++i)
    {
        fillPosRandomly(positionSequence.at(i));
    }
    ps.setPositionSequence(positionSequence);
}

//==============================================================================

void PositionWgs84Sequence3510TestSupport::fillPosRandomly(PositionWgs84& p)
{
    p.setTimestamp(getRandValue<NTPTime>());
    p.setUsSinceStartup(getRandValue<uint32_t>());
    p.setDeviceId(getRandValue<uint8_t>());
    p.setSource(static_cast<PositionWgs84::SourceType>(getRandValue<uint16_t>()));
    p.setLatitudeSigmaInMeter(getRandValue<double>());
    p.setLongitudeSigmaInMeter(getRandValue<double>());
    p.setAltitudeInMeterMSL(getRandValue<double>());
    p.setAltitudeSigmaInMeterMSL(getRandValue<double>());

    const bool setValsInRad = getRandValue<bool>();
    if (setValsInRad)
    {
        p.setLatitudeInRad(getRandValue<double>());
        p.setLongitudeInRad(getRandValue<double>());
        p.setCourseAngleInRad(getRandValue<double>());
        p.setCourseAngleSigmaInRad(getRandValue<double>());
        p.setYawAngleInRad(getRandValue<double>());
        p.setYawAngleSigmaInRad(getRandValue<double>());
        p.setPitchAngleInRad(getRandValue<double>());
        p.setPitchAngleSigmaInRad(getRandValue<double>());
        p.setRollAngleInRad(getRandValue<double>());
        p.setRollAngleSigmaInRad(getRandValue<double>());
    }
    else
    {
        p.setLatitudeInDeg(getRandValue<double>());
        p.setLongitudeInDeg(getRandValue<double>());
        p.setCourseAngleInDeg(getRandValue<double>());
        p.setCourseAngleSigmaInDeg(getRandValue<double>());
        p.setYawAngleInDeg(getRandValue<double>());
        p.setYawAngleSigmaInDeg(getRandValue<double>());
        p.setPitchAngleInDeg(getRandValue<double>());
        p.setPitchAngleSigmaInDeg(getRandValue<double>());
        p.setRollAngleInDeg(getRandValue<double>());
        p.setRollAngleSigmaInDeg(getRandValue<double>());
    }
}

//==============================================================================

PositionWgs84Sequence3510 PositionWgs84Sequence3510TestSupport::createPositionWgs84Sequence3510()
{
    PositionWgs84Sequence3510 position;
    fillRandomly(position);
    return position;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

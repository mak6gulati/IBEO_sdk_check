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
//!\date 15.November 2018
//------------------------------------------------------------------------------

#include "PositionWgs84SequenceTestSupport.hpp"

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

void PositionWgs84SequenceTestSupport::fillRandomly(PositionWgs84Sequence& ps)
{
    ps.setTimestamp(getRandValue<NTPTime>());
    ps.setSourceType(static_cast<PositionWgs84Sequence::SourceType>(getRandValue<uint8_t>()));
    ps.setId(getDifferentRandValue<uint32_t>(ps.getId()));

    const uint16_t sequenceSize = getRandValue<uint16_t>(256);

    std::vector<PositionWgs84> positionSequence(sequenceSize, PositionWgs84());
    for (auto positionWgs84 : positionSequence)
    {
        fillPosRandomly(positionWgs84);
    }
    ps.setPositionSequence(positionSequence);
}

//==============================================================================

void PositionWgs84SequenceTestSupport::fillPosRandomly(PositionWgs84& p)
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

PositionWgs84Sequence PositionWgs84SequenceTestSupport::createPositionWgs84Sequence()
{
    PositionWgs84Sequence position;
    fillRandomly(position);
    return position;
}
//==============================================================================

PositionWgs84Sequence PositionWgs84SequenceTestSupport::createPositionWgs84Sequence2604()
{
    PositionWgs84Sequence positionWgs84Sequence;
    PositionWgs84 positionWgs84;
    fillPosRandomly(positionWgs84);
    positionWgs84Sequence.setPositionSequence(std::vector<PositionWgs84>{positionWgs84});
    return positionWgs84Sequence;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date June 12, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "Scan2202TestSupport.hpp"
#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

template<>
void ScanTestSupport::fillRandomly(Scan2202& scan)
{
    scan.setScanNumber(getRandValue<uint16_t>());
    scan.setScannerStatus(getRandValue<uint16_t>());
    scan.setSyncPhaseOffset(getRandValue<uint16_t>());
    scan.setStartTimestamp(getRandValue<NTPTime>());
    do
    {
        scan.setEndTimestamp(getRandValue<NTPTime>());
    } while (scan.getStartTimestamp() > scan.getEndTimestamp());

    scan.setAngleTicksPerRotation(11520); //TODO check if CONST needs to be fixed!
    scan.setStartAngleTicks(getRandValue<int16_t>());
    scan.setEndAngleTicks(getRandValue<int16_t>());
    scan.setNumberOfScanPoints(getRandValue<uint16_t>());
    scan.setMountingPositionYawAngleTicks(getRandValue<int16_t>());
    scan.setMountingPositionPitchAngleTicks(getRandValue<int16_t>());
    scan.setMountingPositionRollAngleTicks(getRandValue<int16_t>());
    scan.setMountingPositionCmX(getRandValue<int16_t>());
    scan.setMountingPositionCmY(getRandValue<int16_t>());
    scan.setMountingPositionCmZ(getRandValue<int16_t>());

    std::array<uint16_t, 15> flagArray{0x0001U,
                                       0x0002U,
                                       0x0003U,
                                       0x0004U,
                                       0x0005U,
                                       0x0006U,
                                       0x0007U,
                                       0x0400U,
                                       0x0401U,
                                       0x0402U,
                                       0x0403U,
                                       0x0404U,
                                       0x0405U,
                                       0x0406U,
                                       0x0407U};
    scan.setFlags(flagArray.at(getRandValue<uint8_t>(0, 14)));

    uint16_t nbOfScanPoints = getRandValue<uint16_t>();
    scan.setNumberOfScanPoints(nbOfScanPoints);

    for (uint16_t i = 0; i < nbOfScanPoints; ++i)
    {
        scan.setScanPoint(i, getRandValue<ScanPointIn2202>());
    }
}

//==============================================================================

template<>
ScanPointIn2202 TestSupport::getRandValue()
{
    ScanPointIn2202 pt;
    pt.setLayer(getRandValue<uint8_t>(0, 15));
    pt.setEcho(getRandValue<uint8_t>(0, 15));
    pt.setFlags(getRandValue<uint8_t>());
    pt.setHorizontalAngleTicks(getRandValue<int16_t>());
    pt.setDistanceCm(getRandValue<uint16_t>());
    pt.setEchoPulseWidthCm(getRandValue<uint16_t>());
    pt.setReserved(getRandValue<uint16_t>());

    return pt;
}

//==============================================================================

template<>
std::vector<ScanPointIn2202> TestSupport::getRandValue()
{
    Scan2202::ScanPointVector vec;
    const size_t maxVecSize    = 1000;
    const uint32_t vecElements = getRandValue<uint32_t>(maxVecSize);

    vec.reserve(vecElements);
    for (uint32_t i = 0; i < vecElements; ++i)
    {
        vec.push_back(getRandValue<ScanPointIn2202>());
    }

    return vec;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

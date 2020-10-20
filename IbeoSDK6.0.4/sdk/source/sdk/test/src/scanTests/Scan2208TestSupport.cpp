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
//!\date June 14, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "Scan2208TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/MountingPosition.hpp>

#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

template<>
void ScanTestSupport::fillRandomly(Scan2208& scan)
{
    scan.setScanNumber(getRandValue<uint16_t>());
    scan.setScannerType(ScannerType(getRandValue<uint8_t>(0, 9)));
    scan.setScannerStatus(getRandValue<uint16_t>());
    scan.setAngleTicksPerRotation(getRandValue<uint16_t>());
    scan.setProcessingFlags(getRandValue<uint32_t>());
    //scan.setMountingPosition(Scan2208TestSupport::getRa <uint16_t>());
    for (uint8_t i = 0; i < Scan2208::nbOfThresholds; ++i)
    {
        scan.setThreshold(i, getRandValue<uint16_t>());
    }
    for (uint8_t i = 0; i < Scan2208::nbOfReserved; ++i)
    {
        scan.setReserved(i, getRandValue<uint8_t>());
    }
    scan.setDeviceId(getRandValue<uint8_t>());

    scan.getSubScans() = getRandValue<Scan2208::SubScanVector>();
}

//==============================================================================

template<>
SubScanIn2208::PointVector TestSupport::getRandValue()
{
    SubScanIn2208::PointVector vec;
    const size_t maxVecSize    = SubScanIn2208::maxNbOfPoints;
    const uint32_t vecElements = getRandValue<uint32_t>(maxVecSize);
    vec.reserve(vecElements);

    for (uint32_t i = 0; i < vecElements; ++i)
    {
        ScanPointIn2208 sp;
        sp.setThresholdId(getDifferentRandValue<uint8_t>(0, 15)); //4 bit only
        sp.setEchoId(getDifferentRandValue<uint8_t>(0, 3)); //2 bit
        sp.setReserved(getDifferentRandValue<uint8_t>(0, 3)); //2 bit

        sp.setLayerId(getRandValue<uint8_t>());
        sp.setFlags(getRandValue<uint16_t>());
        sp.setHorizontalAngle(getRandValue<int16_t>());
        sp.setRadialDistance(getRandValue<uint16_t>());
        sp.setEchoPulseWidth(getRandValue<uint16_t>());
        sp.setPfValue(getRandValue<uint8_t>());
    }

    return vec;
}

//==============================================================================

template<>
SubScanIn2208 TestSupport::getRandValue()
{
    SubScanIn2208 sc;
    NTPTime tmpTime = sc.getStartScanTimestamp();
    do
    {
        sc.setStartScanTimestamp(getRandValue<NTPTime>());
    } while ((sc.getStartScanTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
             || (sc.getStartScanTimestamp() == tmpTime));
    do
    {
        sc.setEndScanTimestamp(getRandValue<NTPTime>());
    } while ((sc.getEndScanTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
             || (sc.getEndScanTimestamp() == tmpTime));
    sc.setEndScanTimestamp(getRandValue<NTPTime>());
    sc.setStartScanAngle(getRandValue<int16_t>());
    sc.setEndScanAngle(getRandValue<int16_t>());
    sc.setFlags(getRandValue<uint8_t>());
    sc.setMirrorSide(getRandValue<uint8_t>());
    sc.setMirrorTiltDeprecated(getRandValue<float_t>());
    //sc.setMirrorTilt(getRandValue<uint16_t>());
    sc.setMirrorTilt(1);
    for (uint8_t i = 0; i < SubScanIn2208::nbOfReserved; ++i)
    {
        sc.setReserved(i, getRandValue<uint8_t>());
    }
    sc.getScanPoints() = getRandValue<SubScanIn2208::PointVector>();

    return sc;
}

//==============================================================================

template<>
Scan2208::SubScanVector TestSupport::getRandValue()
{
    Scan2208::SubScanVector vec;
    const uint32_t maxVecSize  = Scan2208::maxSubScans;
    const uint32_t vecElements = getRandValue<uint32_t>(maxVecSize);
    vec.reserve(vecElements);

    for (uint32_t i = 0; i < vecElements; ++i)
    {
        vec.push_back(getRandValue<SubScanIn2208>());
    }

    return vec;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

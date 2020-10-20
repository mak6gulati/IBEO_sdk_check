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

#include "ScanTestSupport.hpp"
#include "Scan2209TestSupport.hpp"

#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

template<>
void ScanTestSupport::fillRandomly(Scan& scan)
{
    //note: Currently Scan GDC =^= Scan2209
    scan.setStartTimestamp(getRandValue<NTPTime>());
    scan.setEndTimeOffset(getRandValue<uint32_t>());
    scan.setFlags(getRandValue<uint32_t>());
    scan.setScanNumber(getRandValue<uint16_t>());
    scan.setReserved0(getRandValue<uint8_t>());
    scan.setReserved1(getRandValue<uint16_t>());

    scan.setScannerInfos(getRandValue<Scan::ScannerInfoVector>());
    scan.setScanPoints(getRandValue<Scan::ScanPointVector>());
}

//==============================================================================

template<>
void ScanTestSupport::fillRandomly(ScannerInfo& scannerInfo)
{
    scannerInfo.setDeviceId(getRandValue<uint8_t>());
    ScannerType scT = ScanTestSupport::getScannerType(getRandValue<uint8_t>(0, 9));
    scannerInfo.setScannerType(scT);
    scannerInfo.setScanNumber(getRandValue<uint16_t>());
    scannerInfo.setScannerStatus(getRandValue<uint32_t>());
    scannerInfo.setStartAngle(getRandValue<float_t>());
    scannerInfo.setEndAngle(getRandValue<float_t>());
    scannerInfo.setScanStartTime(getRandValue<NTPTime>());
    scannerInfo.setScanEndTime(getRandValue<NTPTime>());
    scannerInfo.setScanStartTimeFromDevice(getRandValue<NTPTime>());
    scannerInfo.setScanEndTimeFromDevice(getRandValue<NTPTime>());
    scannerInfo.setFrequency(getRandValue<float_t>());
    scannerInfo.setBeamTilt(getRandValue<float_t>());
    scannerInfo.setFlags(getRandValue<uint32_t>());
    scannerInfo.setYawAngle(getRandValue<float_t>());
    scannerInfo.setPitchAngle(getRandValue<float_t>());
    scannerInfo.setRollAngle(getRandValue<float_t>());
    scannerInfo.setOffsetX(getRandValue<float_t>());
    scannerInfo.setOffsetY(getRandValue<float_t>());
    scannerInfo.setOffsetZ(getRandValue<float_t>());
    scannerInfo.setResolutionInfo(getRandValue<std::vector<ResolutionInfo>>());
    scannerInfo.setRotationOrder(getRandValue<RotationOrder>());
}

//==============================================================================

template<>
std::vector<ResolutionInfo> TestSupport::getRandValue()
{
    std::vector<ResolutionInfo> vec;
    const size_t maxVecSize = ScannerInfo::nbOfResolutionInfo;
    //	const uint32_t vecElements = getRandValue<uint32_t>(maxVecSize);
    const uint32_t vecElements = maxVecSize;

    vec.reserve(vecElements);
    for (uint32_t i = 0; i < vecElements; ++i)
    {
        ResolutionInfo resInfo;
        resInfo.setResolution(getRandValue<float_t>());
        resInfo.setResolutionStartAngle(getRandValue<float_t>());
        vec.push_back(resInfo);
    }

    return vec;
}

//==============================================================================

template<>
std::vector<ScannerInfo> TestSupport::getRandValue()
{
    Scan::ScannerInfoVector vec;
    const size_t maxVecSize = 8;
    //	const uint32_t vecElements = getRandValue<uint32_t>(maxVecSize);
    const uint32_t vecElements = maxVecSize;
    vec.reserve(vecElements);
    for (uint32_t i = 0; i < vecElements; ++i)
    {
        ScannerInfo scannerInfo;
        ScanTestSupport::fillRandomly(scannerInfo);
        scannerInfo.setDeviceId(static_cast<uint8_t>(i)); // Device ID must be in range 0..maxVecSize.
        vec.push_back(scannerInfo);
    }

    return vec;
}

//==============================================================================

template<>
std::vector<ScanPoint> TestSupport::getRandValue()
{
    std::vector<ScanPoint> vec;
    const size_t maxVecSize    = 1000;
    const uint32_t vecElements = getRandValue<uint32_t>(maxVecSize);

    vec.reserve(vecElements);
    for (uint32_t i = 0; i < vecElements; ++i)
    {
        ScanPoint pt;
        pt.setPosX(getRandValue<float_t>());
        pt.setPosY(getRandValue<float_t>());
        pt.setPosZ(getRandValue<float_t>());
        pt.setEpw(getRandValue<float_t>());
        pt.setDeviceId(getRandValue<uint8_t>(0, 7));
        pt.setLayer(getRandValue<uint8_t>());
        pt.setEcho(getRandValue<uint8_t>());
        pt.setReserved(getRandValue<uint8_t>());
        pt.setTimeOffset(getRandValue<uint32_t>());
        pt.setFlags(getRandValue<uint16_t>());
        pt.setSegmentId(getRandValue<uint16_t>());

        vec.push_back(pt);
    }

    return vec;
}

//==============================================================================

template<>
RotationOrder TestSupport::getRandValue()
{
    uint8_t randVal = getRandValue<uint8_t>(6);
    return static_cast<RotationOrder>(randVal);
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

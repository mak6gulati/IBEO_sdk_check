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

#include "Scan2209TestSupport.hpp"

#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

template<>
void ScanTestSupport::fillRandomly(Scan2209& scan)
{
    scan.setStartTimestamp(getRandValue<NTPTime>());
    scan.setEndTimeOffset(getRandValue<uint32_t>());
    scan.setFlags(getRandValue<uint32_t>());
    scan.setScanNumber(getRandValue<uint16_t>());
    scan.setReserved0(getRandValue<uint8_t>());
    scan.setReserved1(getRandValue<uint16_t>());

    scan.setScannerInfos(getRandValue<Scan2209::ScannerInfoVector>());
    scan.setScanPoints(getRandValue<Scan2209::ScanPointVector>());
}

//==============================================================================

// !!!!!!!!!!!!!!!!!!!!!!!!!!
// - following 2 methods -> same as for basis class atm (see "scan.hpp")
// !!!!!!!!!!!!!!!!!!!!!!!!!!
//template<>
//Scan2209::ScannerInfoVector TestSupport::getRandValue()
//{
//	Scan2209::ScannerInfoVector vec;
//	const size_t maxVecSize = 8;
////	const uint32_t vecElements = getRandValue<uint32_t>(maxVecSize);
//	const uint32_t vecElements = maxVecSize;
//	vec.reserve(vecElements);
//	for (uint32_t i = 0; i < vecElements; ++i)
//	{
//		ScannerInfoIn2209 scannerInfo;
//		scannerInfo.setDeviceId(getRandValue<uint8_t>());
//
//		//TODO set scanner type one of hex ENUM
//		scannerInfo.setScannerType(Ecu);
//
//		scannerInfo.setScanNumber(getRandValue<uint16_t>());
//		scannerInfo.setScannerStatus(getRandValue<uint32_t>());
//		scannerInfo.setStartAngle(getRandValue<float_t>());
//		scannerInfo.setEndAngle(getRandValue<float_t>());
//		scannerInfo.setScanStartTime(getRandValue<NTPTime>());
//		scannerInfo.setScanEndTime(getRandValue<NTPTime>());
//		scannerInfo.setScanStartTimeFromDevice(getRandValue<NTPTime>());
//		scannerInfo.setScanEndTimeFromDevice(getRandValue<NTPTime>());
//		scannerInfo.setFrequency(getRandValue<float_t>());
//		scannerInfo.setBeamTilt(getRandValue<float_t>());
//		scannerInfo.setFlags(getRandValue<uint32_t>());
//		scannerInfo.setYawAngle(getRandValue<float_t>());
//		scannerInfo.setPitchAngle(getRandValue<float_t>());
//		scannerInfo.setRollAngle(getRandValue<float_t>());
//		scannerInfo.setOffsetX(getRandValue<float_t>());
//		scannerInfo.setOffsetY(getRandValue<float_t>());
//		scannerInfo.setOffsetZ(getRandValue<float_t>());
//		scannerInfo.setResolutionInfo(getRandValue<std::vector<ResolutionInfoIn2209> >());
//
//		vec.push_back(scannerInfo);
//	}
//
//	return vec;
//}
//
////==============================================================================
//
//template<>
//Scan2209::ScanPointVector TestSupport::getRandValue()
//{
//
//	Scan2209::ScanPointVector vec;
//	const size_t maxVecSize = 1000;
//	const uint32_t vecElements = getRandValue<uint32_t>(maxVecSize);
//
//	vec.reserve(vecElements);
//	for (uint32_t i = 0; i < vecElements; ++i)
//	{
//		ScanPointIn2209 pt;
//		pt.setPosX(getRandValue<float_t>());
//		pt.setPosY(getRandValue<float_t>());
//		pt.setPosZ(getRandValue<float_t>());
//		pt.setEpw(getRandValue<float_t>());
//		pt.setDeviceId(getRandValue<uint8_t>());
//		pt.setLayer(getRandValue<uint8_t>());
//		pt.setEcho(getRandValue<uint8_t>());
//		pt.setReserved(getRandValue<uint8_t>());
//		pt.setTimeOffset(getRandValue<uint32_t>());
//		pt.setFlags(getRandValue<uint16_t>());
//		pt.setSegmentId(getRandValue<uint16_t>());
//
//		vec.push_back(pt);
//	}
//
//	return vec;
//}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date March 23, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <common/TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/scan/Scan.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2202.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2205.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2208.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2209.hpp>

#include <ibeo/common/sdk/datablocks/scan/ResolutionInfo.hpp>
#include <ibeo/common/sdk/datablocks/scan/ScannerInfo.hpp>
#include <ibeo/common/sdk/RotationOrder.hpp>

#include <vector>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class ScanTestSupport : public TestSupport
{
public:
    ScanTestSupport()          = default;
    virtual ~ScanTestSupport() = default;

    template<typename T>
    T createScan();

public:
    template<typename T>
    static void fillRandomly(T& vs);

    static ScannerType getScannerType(const uint8_t typeId)
    {
        switch (typeId)
        {
        case 0:
            return ScannerType::Invalid;
        case 1:
            return ScannerType::Ecu;
        case 2:
            return ScannerType::Lux;
        case 3:
            return ScannerType::Lux4;
        case 4:
            return ScannerType::MiniLux;
        case 5:
            return ScannerType::SickLMS100;
        case 6:
            return ScannerType::SickLMS200;
        case 7:
            return ScannerType::SickLMS500;
        case 8:
            return ScannerType::ScalaB2;
        default:
            return ScannerType::Invalid;
        }
    }

protected:
    static const int32_t nbOfRepeats = 100;

}; // ScanTestSupport

//==============================================================================

template<typename T>
T ScanTestSupport::createScan()
{
    T scan;
    fillRandomly(scan);
    return scan;
}

template<>
void ScanTestSupport::fillRandomly(Scan& scan);

template<>
void ScanTestSupport::fillRandomly(ScannerInfo& scannerInfo);

template<>
std::vector<ResolutionInfo> TestSupport::getRandValue();

template<>
std::vector<ResolutionInfo> TestSupport::getRandValue();

template<>
std::vector<ScannerInfo> TestSupport::getRandValue();

template<>
std::vector<ScanPoint> TestSupport::getRandValue();

template<>
Scan2202::ScanPointVector TestSupport::getRandValue();

template<>
RotationOrder TestSupport::getRandValue();

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

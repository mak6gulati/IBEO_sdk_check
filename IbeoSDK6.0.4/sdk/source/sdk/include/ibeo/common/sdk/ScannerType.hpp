//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Dec 18, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <cstdint>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

enum class ScannerType : uint8_t
{
    Invalid = 0xFFU, //!< invalid value ( = -1)
    // 0x00 reserved
    // 0x03 reserved
    Ecu = 0x04U, //!< Ibeo Ecu
    // 0x05 reserved
    Lux = 0x06U, //!< Ibeo Lux3
    // 0x07, 0x07 reserved
    Lux4 = 0x10U, //!< Ibeo Lux4
    // 0x11, 0x18, 0x19 reserved
    // 0x20, 0x21, 0x28, 0x29 reserved
    MiniLux = 0x30U, //!< Ibeo MiniLux
    // 0x40, 0x41, 0x42 reserved
    SickLMS200 = 0x50U, //!< Sick LMS200/291
    SickLMS100 = 0x51U, //!< Sick LMS100/111
    SickLMS500 = 0x54U, //!< Sick LMS500/511
    // 0x51 - 0x55 reserved
    // 0x60reserved
    ScalaB2 = 0x62U, //!< Ibeo/Valeo ScalaB2
    NextA0  = 0x70U, //!< Ibeo Next A0 Sample with LDMIv2
    // 0x90 reserved
    ThirdPartyVLidarVV16  = 0xC8U, //!< Third party lidar sensor with 16 channels.
    ThirdPartyVLidarVV32C = 0xC9U, //!< Third party lidar sensor with 32 channels.
    ThirdPartyVLidarVH64  = 0xD2U, //!< Third party lidar sensor with 64 channels.
    ThirdPartyVLidarVH32  = 0xD3U //!< Third party lidar sensor with 32 channels.
}; // ScannerType

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

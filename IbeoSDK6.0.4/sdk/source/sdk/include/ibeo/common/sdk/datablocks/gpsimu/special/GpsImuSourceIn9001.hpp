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
//!\date Feb 4, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {

//========================================
//!\brief Sources that provide GPS/IMU measurements.
//----------------------------------------
enum class GpsImuSourceIn9001 : uint8_t
{
    Can         = 0,
    XSensImu    = 1,
    OGpsImuRt   = 2,
    GenesysAdma = 3,
    SpatialDual = 4,
    Tfc         = 5,
    VBox3i      = 6,
    Unknown     = 99
};

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//! \date Oct 25, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! Flags representing the rotation-execution order reg. the sensors mounting
//! point transformation from sensor- to vehicle coord. system
enum class RotationOrder : uint8_t
{
    RollPitchYaw = 0x00,
    RollYawPitch = 0x01,
    PitchRollYaw = 0x02,
    PitchYawRoll = 0x03,
    YawRollPitch = 0x04,
    YawPitchRoll = 0x05
}; // RotationOrder

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//! \date Mar 07, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace image {
//==============================================================================

//==============================================================================
//! \brief Enumeration of pixel formats.
//------------------------------------------------------------------------------
enum class PixelFormat : uint8_t
{
    Unknown = 0, //!< Pixel format not known.
    Mono8   = 1, //!< Red-Green-Blue, 8-bit per pixel
    Rgb8    = 2, //!< Monochrome, 8-bit per pixel
    Yuv420  = 3, //!< YUV 4:2:0, 8-bit per pixel
    Yuv422  = 4 //!< YUV 4:2:2, 8-bit per pixel
};

//==============================================================================
} // namespace image
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

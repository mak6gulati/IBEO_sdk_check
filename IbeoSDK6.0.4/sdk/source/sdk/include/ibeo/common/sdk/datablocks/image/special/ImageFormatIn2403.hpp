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
#include <stdint.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace image {
//==============================================================================

//==============================================================================
//!\brief Enumeration of image formats.
//------------------------------------------------------------------------------
enum class ImageFormatIn2403 : uint16_t
{
    Jpeg   = 0,
    Mjpeg  = 1,
    Gray8  = 2,
    Yuv420 = 3,
    Yuv422 = 4,
    Png    = 5
};

//==============================================================================
//!\brief Converts the image format to a
//!       human readable string.
//!
//!\param[in] format  Image2403 format id to be
//!                   converted into a string.
//------------------------------------------------------------------------------
std::string formatToString(const ImageFormatIn2403 format);

//==============================================================================
} // namespace image
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

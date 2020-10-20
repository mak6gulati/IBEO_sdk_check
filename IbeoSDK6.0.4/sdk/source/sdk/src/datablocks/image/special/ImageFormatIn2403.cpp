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

//==============================================================================

#include <ibeo/common/sdk/datablocks/image/special/ImageFormatIn2403.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace image {
//==============================================================================

std::string formatToString(const ImageFormatIn2403 format)
{
    std::string name;

    // Get the key name
    switch (format)
    {
    case ImageFormatIn2403::Jpeg:
        name = "JPEG";
        break;
    case ImageFormatIn2403::Mjpeg:
        name = "MotionJPEG (MJPEG)";
        break;
    case ImageFormatIn2403::Gray8:
        name = "8-bit grayscale (GRAY8)";
        break;
    case ImageFormatIn2403::Yuv420:
        name = "YUV 4:2:0 (YUV420)";
        break;
    case ImageFormatIn2403::Yuv422:
        name = "YUV 4:2:2 (YUV422)";
        break;
    case ImageFormatIn2403::Png:
        name = "PNG";
        break;
    default:
        name = "Unknown";
        break;
    } // switch

    return name;
}

//==============================================================================
} // namespace image
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

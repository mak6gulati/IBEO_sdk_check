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

#include <ibeo/common/sdk/datablocks/image/ImageFormat.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace image {
//==============================================================================

std::string ImageFormat::formatToString(const FileFormat fileFormat)
{
    std::string name;

    switch (fileFormat)
    {
    case FileFormat::Raw:
        name = "Raw";
        break;

    case FileFormat::Jpeg:
        name = "JPEG";
        break;

    case FileFormat::Mjpeg:
        name = "MotionJPEG (MJPEG)";
        break;

    case FileFormat::Png:
        name = "PNG";
        break;

    default:
        name = "<Unknown>";
        break;
    } // switch

    return name;
}

//==============================================================================

std::string ImageFormat::formatToString(const PixelFormat pixelFormat)
{
    std::string name;

    switch (pixelFormat)
    {
    case PixelFormat::Mono8:
        name = "8-bit monochrome (Mono8)";
        break;

    case PixelFormat::Rgb8:
        name = "24-bit color (RGB8)";
        break;

    case PixelFormat::Yuv420:
        name = "YUV 4:2:0 (YUV420)";
        break;

    case PixelFormat::Yuv422:
        name = "YUV 4:2:2 (YUV422)";
        break;

    default:
        name = "<Unknown>";
        break;
    } // switch

    return name;
}

//==============================================================================

std::string ImageFormat::formatToString(const ImageFormat format)
{
    return formatToString(format.m_fileFormat) + " (" + formatToString(format.m_pixelFormat) + ")";
}

//==============================================================================
} // namespace image
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

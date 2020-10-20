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
//!\date Mar 9, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/image/special/Image2403.hpp>
#include <ibeo/common/sdk/Math.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ibeo::common::logging::LoggerSPtr Image2403::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

void Image2403::setImage(const image::ImageFormatIn2403 imageFormat,
                         const DataType* const buffer,
                         const uint32_t length,
                         const uint16_t width,
                         const uint16_t height,
                         const uint32_t microseconds,
                         const ibeo::common::sdk::NTPTime timestamp)
{
    m_microseconds = microseconds;
    m_timestamp    = timestamp;
    // deviceId, mountingPosition, h/vOpeningAngle

    image::ImageFormat genericImageFormat = getGeneralImageFormat(imageFormat);

    m_imageBuffer->set(genericImageFormat, width, height, buffer, length);
}

//==============================================================================

image::ImageFormat Image2403::getGeneralImageFormat(const image::ImageFormatIn2403 imageFormat)
{
    switch (imageFormat)
    {
    case image::ImageFormatIn2403::Jpeg:
        return image::ImageFormat(image::FileFormat::Jpeg, image::PixelFormat::Unknown);

    case image::ImageFormatIn2403::Mjpeg:
        return image::ImageFormat(image::FileFormat::Mjpeg, image::PixelFormat::Unknown);

    case image::ImageFormatIn2403::Gray8:
        return image::ImageFormat(image::FileFormat::Raw, image::PixelFormat::Mono8);

    case image::ImageFormatIn2403::Yuv420:
        return image::ImageFormat(image::FileFormat::Raw, image::PixelFormat::Yuv420);

    case image::ImageFormatIn2403::Yuv422:
        return image::ImageFormat(image::FileFormat::Raw, image::PixelFormat::Yuv422);

    default:
        LOGWARNING(logger, "Unknown image format " << image::formatToString(imageFormat) << "! Using JPEG instead.");
        return image::ImageFormat(image::FileFormat::Jpeg, image::PixelFormat::Unknown);
    }
}

//==============================================================================

image::ImageFormatIn2403 Image2403::getImageFormatIn2403(const image::ImageFormat imageFormat)
{
    image::ImageFormatIn2403 imageFormatIn2403{image::ImageFormatIn2403::Jpeg};

    switch (imageFormat.getFileFormat())
    {
    case image::FileFormat::Raw:
    {
        switch (imageFormat.getPixelFormat())
        {
        case image::PixelFormat::Mono8:
            imageFormatIn2403 = image::ImageFormatIn2403::Gray8;
            break;

        case image::PixelFormat::Yuv420:
            imageFormatIn2403 = image::ImageFormatIn2403::Yuv420;
            break;

        case image::PixelFormat::Yuv422:
            imageFormatIn2403 = image::ImageFormatIn2403::Yuv422;
            break;

        default:
            LOGWARNING(logger,
                       "Unknown image format " << image::ImageFormat::formatToString(imageFormat)
                                               << "! Changed to JPEG.");
            imageFormatIn2403 = image::ImageFormatIn2403::Jpeg;
            break;
        }
    }
    break;

    case image::FileFormat::Jpeg:
        imageFormatIn2403 = image::ImageFormatIn2403::Jpeg;
        break;

    case image::FileFormat::Mjpeg:
        imageFormatIn2403 = image::ImageFormatIn2403::Mjpeg;
        break;

    case image::FileFormat::Png:
        imageFormatIn2403 = image::ImageFormatIn2403::Png;
        break;

    default:
        LOGWARNING(logger,
                   "Unknown image format " << image::ImageFormat::formatToString(imageFormat)
                                           << "! Using JPEG instead.");
        imageFormatIn2403 = image::ImageFormatIn2403::Jpeg;
        break;
    }

    return imageFormatIn2403;
}

//==============================================================================

bool operator==(const Image2403& lhs, const Image2403& rhs)
{
    return (lhs.getFormat() == rhs.getFormat()) && (lhs.getMicroseconds() == rhs.getMicroseconds())
           && (lhs.getTimestamp() == rhs.getTimestamp()) && (lhs.getDeviceId() == rhs.getDeviceId())
           && (lhs.getCamMountingPosition() == rhs.getCamMountingPosition())
           && (doubleEqual(lhs.getCamHorizontalOpeningAngle(), rhs.getCamHorizontalOpeningAngle()))
           && (doubleEqual(lhs.getCamVerticalOpeningAngle(), rhs.getCamVerticalOpeningAngle()))
           && ((*lhs.getImageBuffer()) == (*rhs.getImageBuffer()));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

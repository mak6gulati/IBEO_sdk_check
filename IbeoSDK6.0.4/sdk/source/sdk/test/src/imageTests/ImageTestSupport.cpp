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
//!\date June 19, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "ImageTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/image/special/Image2403.hpp>
#include <ibeo/common/sdk/datablocks/image/special/ImageFormatIn2403.hpp>

#include <inttypes.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

Image ImageTestSupport::createImage()
{
    Image image;
    fillRandomly(image);
    return image;
}

//==============================================================================

void ImageTestSupport::fillRandomly(Image& image)
{
    const uint16_t width{getRandValue<uint16_t>(1, 1000)};
    const uint16_t height{getRandValue<uint16_t>(1, 1000)};
    fillRandomly(image, width, height);
}

//==============================================================================

void ImageTestSupport::fillEmptyImageRandomly(Image& image) { fillRandomly(image, 0U, 0U); }

//==============================================================================

void ImageTestSupport::fillRandomly(Image& image, const uint16_t width, const uint16_t height)
{
    const uint32_t length{static_cast<uint32_t>(width * height)};

    std::vector<Image::DataType> imageData(length);
    fillVectorRandomly(imageData);

    const uint32_t microseconds{getRandValue<uint32_t>()};
    const NTPTime timestamp{getRandValue<NTPTime>()};

    image::ImageFormatIn2403 imageFormatIn2403 = static_cast<image::ImageFormatIn2403>(getRandValue<uint16_t>());

    image.setImage(Image2403::getGeneralImageFormat(imageFormatIn2403),
                   imageData.data(),
                   length,
                   width,
                   height,
                   microseconds,
                   timestamp);
    image.setDeviceId(getRandValue<uint8_t>());
    image.setCamMountingPosition(getRandValue<MountingPosition<float>>());
    image.setCamHorizontalOpeningAngle(getNonNanRandValue<double>());
    image.setCamVerticalOpeningAngle(getNonNanRandValue<double>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Feb 05, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "Image2403TestSupport.hpp"

#include <inttypes.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

Image2403 Image2403TestSupport::createImage2403()
{
    Image2403 image;
    fillRandomly(image);
    return image;
}

//==============================================================================

void Image2403TestSupport::fillRandomly(Image2403& image)
{
    const uint16_t width{getRandValue<uint16_t>(1, 1000)};
    const uint16_t height{getRandValue<uint16_t>(1, 1000)};
    fillRandomly(image, width, height);
}

//==============================================================================

void Image2403TestSupport::fillEmptyImageRandomly(Image2403& image) { fillRandomly(image, 0U, 0U); }

//==============================================================================

void Image2403TestSupport::fillRandomly(Image2403& image, const uint16_t width, const uint16_t height)
{
    const uint32_t length{static_cast<uint32_t>(width * height)};

    std::vector<Image2403::DataType> imageData(length);
    fillVectorRandomly(imageData);

    const uint32_t microseconds{getRandValue<uint32_t>()};
    const NTPTime timestamp{getRandValue<NTPTime>()};

    image.setImage(static_cast<image::ImageFormatIn2403>(getRandValue<uint16_t>()),
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

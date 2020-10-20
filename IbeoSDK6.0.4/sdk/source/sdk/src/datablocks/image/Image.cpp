//==============================================================================
//!\file
//!
//! General data container image
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date June 18, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/image/Image.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

void Image::setImage(const image::ImageFormat imageFormat,
                     const DataType* const buffer,
                     const uint32_t length,
                     const uint32_t width,
                     const uint32_t height,
                     const uint32_t microseconds,
                     const ibeo::common::sdk::NTPTime timestamp)
{
    m_microseconds = microseconds;
    m_timestamp    = timestamp;
    // deviceId, mountingPosition, h/vOpeningAngle

    m_imageBuffer->set(imageFormat, width, height, buffer, length);
}

//==============================================================================

bool operator==(const Image& lhs, const Image& rhs)
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

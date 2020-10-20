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
//!\date June 18, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/image/ImageBuffer.hpp>

#include <cstring>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace image {
//==============================================================================

std::shared_ptr<ImageBuffer> ImageBuffer::create(const ImageFormat& imageFormat,
                                                 const uint32_t width,
                                                 const uint32_t height,
                                                 const DataType* const buffer,
                                                 const std::size_t bufferLength)
{
    ImageBufferPtr imageBuffer{std::make_shared<ImageBuffer>()};
    imageBuffer->set(imageFormat, width, height, buffer, bufferLength);

    return imageBuffer;
}

//==============================================================================

void ImageBuffer::set(const ImageFormat& imageFormat,
                      const uint32_t width,
                      const uint32_t height,
                      const DataType* const buffer,
                      const std::size_t bufferLength)
{
    preset(imageFormat, width, height, bufferLength);
    memcpy(&m_buffer[0], buffer, bufferLength);
}

//==============================================================================

void ImageBuffer::preset(const ImageFormat& imageFormat,
                         const uint32_t width,
                         const uint32_t height,
                         const std::size_t imageSize)
{
    m_imageFormat = imageFormat;
    m_width       = width;
    m_height      = height;
    m_buffer.resize(imageSize);
}

//==============================================================================
//==============================================================================

bool operator==(const ImageBuffer& lhs, const ImageBuffer& rhs)
{
    return (lhs.getImageFormat() == rhs.getImageFormat()) && (lhs.getWidth() == rhs.getWidth())
           && (lhs.getHeight() == rhs.getHeight()) && (lhs.getDataBuffer() == rhs.getDataBuffer());
}

//==============================================================================
} // namespace image
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

//==============================================================================
//!\file
//!
//!\verbatim
//! General data container image
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!
//! Created by
//!\date June 18, 2018
//!\endverbatim
//------------------------------------------------------------------------------
//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/image/ImageBuffer.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/MountingPosition.hpp>
#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>
#include <ibeo/common/sdk/Math.hpp>
#include <ibeo/common/sdk/Time.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================
//! \brief General data container for images
//------------------------------------------------------------------------------
class Image : public DataContainerBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    //========================================
    //!\brief Type of data stored in the image buffer.
    //----------------------------------------
    using DataType = image::ImageBuffer::DataType;

public:
    //========================================
    //! \brief Container type as string.
    //----------------------------------------
    constexpr static const char* const containerType{"ibeo.sdk.generalcontainer.Image"};

    //========================================
    //! \brief Hash value of this container (static version).
    //----------------------------------------
    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    //========================================
    //! \brief Constructor.
    //----------------------------------------
    Image() = default;

    //========================================
    //! \brief Destructor.
    //----------------------------------------
    virtual ~Image() = default;

    //========================================
    //! \brief Assignment operator.
    //!
    //! \param other[in]  object to be assigned
    //! \return this
    //----------------------------------------
    Image& operator=(const Image& other) = default;

public:
    //========================================
    //! \brief Hash value of this container.
    //----------------------------------------
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    //========================================
    //!\brief Copies an image source to this image object
    //!
    //!This function copies an image from the source buffer
    //!to this object.
    //!
    //!\param[in] imageFormat   Format of the image resides in \a buffer.
    //!\param[in] buffer        Source buffer, where the original image
    //!                         source resides.
    //!\param[in] length        Size of image in bytes.
    //!\param[in] width         Width of the image.
    //!\param[in] height        Height of the image.
    //!\param[in] microseconds  Number of microseconds passed since
    //!                         powering up the device.
    //!\param[in] timestamp     Time, the image was taken.
    //----------------------------------------
    void setImage(const image::ImageFormat imageFormat,
                  const DataType* const buffer,
                  const uint32_t length,
                  const uint32_t width,
                  const uint32_t height,
                  const uint32_t microseconds,
                  const ibeo::common::sdk::NTPTime timestamp);

public:
    //========================================
    //!\brief Returns the format of the image in the buffer.
    //!\return Format of the image in the buffer.
    //----------------------------------------
    image::ImageFormat getFormat() const { return m_imageBuffer->getImageFormat(); }

    //========================================
    //!\brief Get the number of elapsed microseconds since the
    //!       start of the device that created this Image DataBlock.
    //!\return The number of elapsed microseconds since the
    //!        start of the device
    //----------------------------------------
    uint32_t getMicroseconds() const { return m_microseconds; }

    //========================================
    //!\brief Get the timestamp of when this Image has been
    //!       generated.
    //!\return The timestamp of when this Image has been
    //!        generated.
    //----------------------------------------
    NTPTime getTimestamp() const { return m_timestamp; }

    //========================================
    //!\brief Get the device id of the camera that generated this image.
    //!\return Device id of camera that generated this image.
    //----------------------------------------
    uint8_t getDeviceId() const { return m_deviceId; }

    //========================================
    //!\brief Get the cameras mounting position.
    //!
    //! In case one ore more attributes of the returned
    //! MountingPosition<float> are set to NaN all data are invalid.
    //!
    //!\return Cameras mounting position.
    //----------------------------------------
    MountingPosition<float> getCamMountingPosition() const { return m_mountingPosition; }

    //========================================
    //!\brief Get the horizontal opening angle of the camera.
    //!
    //!Returns the horizontal opening angle of the camera.
    //!Note that the complete position is valid ONLY if this angle is not NaN.
    //!
    //!\return Horizontal opening angle of the camera, in [rad].
    //----------------------------------------
    double getCamHorizontalOpeningAngle() const { return m_hOpeningAngle; }

    //========================================
    //!\brief Get the vertical opening angle of the camera.
    //!
    //!Returns the vertical opening angle of the camera.
    //!Note that the complete position is valid ONLY if this angle is not NaN.
    //!
    //!\return Vertical opening angle of the camera, in [rad].
    //----------------------------------------
    double getCamVerticalOpeningAngle() const { return m_vOpeningAngle; }

    //========================================
    //!\brief Return the width (number of pixels per row) of the image.
    //!\return Number of pixels per row.
    //----------------------------------------
    uint32_t getWidth() const { return m_imageBuffer->getWidth(); }

    //========================================
    //!\brief Return the height (number of rows) of the image.
    //!\return Number of rows.
    //----------------------------------------
    uint32_t getHeight() const { return m_imageBuffer->getHeight(); }

    //========================================
    //!\brief Return the size of the image in the buffer in bytes.
    //!\return Size of the image in the buffer in bytes.
    //----------------------------------------
    uint32_t getImageSize() const { return static_cast<uint32_t>(m_imageBuffer->getSize()); }

    //========================================
    //!\brief Get the buffer with image data and parameters.
    //!\return Buffer with image data and parameters.
    //----------------------------------------
    image::ImageBufferPtr getImageBuffer() const { return m_imageBuffer; }

public:
    //========================================
    //!\brief Set the number of elapsed microseconds since the
    //!       start of the device that created this Image DataBlock.
    //!\param[in] newMicroseconds  New number of elapsed microseconds.
    //----------------------------------------
    void setMicroseconds(const uint32_t newMicroseconds) { m_microseconds = newMicroseconds; }

    //========================================
    //!\brief Set the timestamp when this image has been generated.
    //!\param[in] newTimestamp  New timestamp.
    //----------------------------------------
    void setTimestamp(const NTPTime newTimestamp) { m_timestamp = newTimestamp; }

    //========================================
    //!\brief Set the device id of the camera for this image.
    //!\param[in] newDeviceId  New device id of camera for this image.
    //----------------------------------------
    void setDeviceId(const uint8_t newDeviceId) { m_deviceId = newDeviceId; }

    //========================================
    //!\brief Set the mounting position of the camera for this image.
    //!\param[in] pos  Mounting position of the camera.
    //!\note The mounting position is relative to the vehicle/reference
    //!      coordinate system.
    //----------------------------------------
    void setCamMountingPosition(const MountingPosition<float>& pos) { m_mountingPosition = pos; }

    //========================================
    //!\brief Set the horizontal opening angle of the camera took this image.
    //!\param[in] hOpeningAngle  Horizontal opening (view) angle in [rad].
    //----------------------------------------
    void setCamHorizontalOpeningAngle(const double hOpeningAngle) { m_hOpeningAngle = hOpeningAngle; }

    //========================================
    //!\brief Set the vertical opening angle of the camera took this image.
    //!\param[in] vOpeningAngle  Vertical opening (view) angle in [rad].
    //----------------------------------------
    void setCamVerticalOpeningAngle(const double vOpeningAngle) { m_vOpeningAngle = vOpeningAngle; }

    //========================================
    //!\brief Set the buffer with image data and parameters.
    //!
    //! \param[in] imageBuffer  The new buffer with image data and parameters.
    //----------------------------------------
    void setImageBuffer(const image::ImageBufferPtr& imageBuffer) { m_imageBuffer = imageBuffer; }

private:
    //========================================
    //! \brief Reserve space in the image buffer to hold the given number of bytes and set other image parameter.
    //!
    //! \param[in] imageFormat  Format of the image to store into the buffer.
    //! \param[in] imageSize    Size of the image data to store into the buffer.
    //! \param[in] width        Width of the image to store into the buffer.
    //! \param[in] height       Height of the image to store into the buffer.
    //----------------------------------------
    void presetImageBuffer(const image::ImageFormat imageFormat,
                           const uint32_t imageSize,
                           const uint16_t width,
                           const uint16_t height)
    {
        m_imageBuffer->preset(imageFormat, width, height, imageSize);
    }

private: // attributes
    //========================================
    //!\brief Passed microseconds since start.
    //----------------------------------------
    uint32_t m_microseconds{0};

    //========================================
    //!\brief Timestamp of this DataContainer.
    //-------------------------------------
    ibeo::common::sdk::NTPTime m_timestamp{};

    //========================================
    //!\brief Device id of the origin of this image.
    //----------------------------------------
    uint8_t m_deviceId{0};

    //========================================
    //!\brief Mounting position of the camera,
    //!       this image has been taken with.
    //----------------------------------------
    MountingPosition<float> m_mountingPosition{};

    //========================================
    //!\brief Horizontal opening angle of the camera,
    //!       this image has been taken with.
    //----------------------------------------
    double m_hOpeningAngle{NaN_double};

    //========================================
    //!\brief Vertical opening angle of the camera,
    //!       this image has been taken with.
    //----------------------------------------
    double m_vOpeningAngle{NaN_double};

    //========================================
    //!\brief Format of the image stored in m_imageBuffer.
    //----------------------------------------
    image::ImageBufferPtr m_imageBuffer{std::make_shared<image::ImageBuffer>()};
}; // Image

//==============================================================================

bool operator==(const Image& lhs, const Image& rhs);
inline bool operator!=(const Image& lhs, const Image& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

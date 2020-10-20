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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/image/special/ImageFormatIn2403.hpp>
#include <ibeo/common/sdk/datablocks/image/ImageBuffer.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/MountingPosition.hpp>
#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>
#include <ibeo/common/sdk/Math.hpp>
#include <ibeo/common/sdk/Time.hpp>

#include <ibeo/common/logging/logging.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================
//! \brief Specialized data container for images (0x2403)
//!
//! Ibeo FUSION SYSTEM/ECU image: Video image w/ mounting position and device ID, no detailed description
//! available (generic)
//!
//! General data type: \ref ibeo::common::sdk::Image
//------------------------------------------------------------------------------
class Image2403 : public SpecializedDataContainer
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
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.image2403"};

    //========================================
    //! \brief Hash value of this container (static version).
    //----------------------------------------
    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    //========================================
    //! \brief Constructor.
    //----------------------------------------
    Image2403() = default;

    //========================================
    //! \brief Destructor.
    //----------------------------------------
    virtual ~Image2403() = default;

    //========================================
    //! \brief Assignment operator.
    //!
    //! \param other[in]  object to be assigned
    //! \return this
    //----------------------------------------
    Image2403& operator=(const Image2403& other) = default;

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
    void setImage(const image::ImageFormatIn2403 imageFormat,
                  const DataType* const buffer,
                  const uint32_t length,
                  const uint16_t width,
                  const uint16_t height,
                  const uint32_t microseconds,
                  const ibeo::common::sdk::NTPTime timestamp);

public:
    //========================================
    //!\brief Returns the format of the image in the buffer.
    //!\return Format of the image in the buffer.
    //----------------------------------------
    image::ImageFormatIn2403 getFormat() const { return getImageFormatIn2403(m_imageBuffer->getImageFormat()); }

    //========================================
    //!\brief Get the number of elapsed microseconds since the
    //!       start of the device that created this Image2403 DataBlock.
    //!\return The number of elapsed microseconds since the
    //!        start of the device
    //----------------------------------------
    uint32_t getMicroseconds() const { return m_microseconds; }

    //========================================
    //!\brief Get the timestamp of when this Image2403 has been
    //!       generated.
    //!\return The timestamp of when this Image2403 has been
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
    uint16_t getWidth() const { return static_cast<uint16_t>(m_imageBuffer->getWidth()); }

    //========================================
    //!\brief Return the height (number of rows) of the image.
    //!\return Number of rows.
    //----------------------------------------
    uint16_t getHeight() const { return static_cast<uint16_t>(m_imageBuffer->getHeight()); }

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

    //========================================
    //! \brief Convert an image format in container 0x2403 to a general image format.
    //!
    //! \param[in] imageFormat  The image format in container 0x2403.
    //! \return The general image format.
    //----------------------------------------
    static image::ImageFormat getGeneralImageFormat(const image::ImageFormatIn2403 imageFormat);

    //========================================
    //! \brief Convert a general image format to an image format in container 0x2403.
    //!
    //! \param[in] imageFormat  The general image format.
    //! \return The image format in container 0x2403.
    //----------------------------------------
    static image::ImageFormatIn2403 getImageFormatIn2403(const image::ImageFormat imageFormat);

public:
    //========================================
    //!\brief Set the number of elapsed microseconds since the
    //!       start of the device that created this Image2403 DataBlock.
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
    void presetImageBuffer(const image::ImageFormatIn2403 imageFormat,
                           const uint32_t imageSize,
                           const uint16_t width,
                           const uint16_t height)
    {
        m_imageBuffer->preset(getGeneralImageFormat(imageFormat), width, height, imageSize);
    }

private: // attributes
    static constexpr const char* loggerId = "ibeo::common::sdk::Image2403";
    static ibeo::common::logging::LoggerSPtr logger;

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
}; // Image2403

//==============================================================================

bool operator==(const Image2403& lhs, const Image2403& rhs);
inline bool operator!=(const Image2403& lhs, const Image2403& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

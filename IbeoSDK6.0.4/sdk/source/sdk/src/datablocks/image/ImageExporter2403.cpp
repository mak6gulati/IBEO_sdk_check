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
//!\endverbatim

//==============================================================================

#include <ibeo/common/sdk/datablocks/image/special/Image2403.hpp>
#include <ibeo/common/sdk/datablocks/image/ImageExporter2403.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::Image;
} // namespace
//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_Image2403>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    std::streamsize sz
        = static_cast<std::streamsize>(sizeof(uint16_t)) + static_cast<std::streamsize>(sizeof(uint32_t))
          + static_cast<std::streamsize>(sizeof(uint64_t)) + static_cast<std::streamsize>(sizeof(uint8_t))
          + serializedSize(container->m_mountingPosition) + static_cast<std::streamsize>(2 * sizeof(double))
          + static_cast<std::streamsize>(2 * sizeof(uint16_t)) + static_cast<std::streamsize>(sizeof(uint32_t))
          + static_cast<std::streamsize>(container->getImageSize());

    return sz;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_Image2403>::serialize(std::ostream& os, const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(os.tellp());

    const uint16_t imgFmt = static_cast<uint16_t>(Image2403::getImageFormatIn2403(container->getFormat()));
    ibeo::common::sdk::writeBE(os, imgFmt); // 2
    ibeo::common::sdk::writeBE(os, container->m_microseconds); // 4
    ibeo::common::sdk::writeBE(os, container->m_timestamp); // 8
    ibeo::common::sdk::writeBE(os, container->m_deviceId); // 1
    ibeo::common::sdk::writeBE(os, container->m_mountingPosition); // 6*4 = 24
    ibeo::common::sdk::writeBE(os, container->m_hOpeningAngle); // 8
    ibeo::common::sdk::writeBE(os, container->m_vOpeningAngle); // 8
    ibeo::common::sdk::writeBE(os, static_cast<uint16_t>(container->getWidth())); // 2
    ibeo::common::sdk::writeBE(os, static_cast<uint16_t>(container->getHeight())); // 2
    ibeo::common::sdk::writeBE(os, container->getImageSize()); // 4

    const Image::DataType* imageBuffer = &container->getImageBuffer()->getDataBuffer()[0];
    os.write(imageBuffer, container->getImageSize());

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

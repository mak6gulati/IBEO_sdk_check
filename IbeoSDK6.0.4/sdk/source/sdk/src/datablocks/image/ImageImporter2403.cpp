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

#include <ibeo/common/sdk/datablocks/image/special/Image2403.hpp>
#include <ibeo/common/sdk/datablocks/image/ImageImporter2403.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::Image;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Image2403>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
// Specializations for RegisteredImporter
//==============================================================================

//generate link between data-type-id/importer and importer create function <dtid, ImpHash> ==> Imp::create

template<>
const Id R::registeredImporterInitial
    = Id(std::make_pair(R::getDataTypeStatic(), C::getClassIdHashStatic()), R::create);

//registering ... (create map)
//add all device that can receive any datatype that can be imported to GeneralDataTypeContainer
class IdcFile;
class IbeoEcu;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(registeredImporterInitial));

//==============================================================================

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_Image2403>::getSerializedSize(const DataContainerBase& c) const
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

    return static_cast<std::streamsize>(sizeof(uint16_t)) + static_cast<std::streamsize>(sizeof(uint32_t))
           + static_cast<std::streamsize>(sizeof(uint64_t)) + static_cast<std::streamsize>(sizeof(uint8_t))
           + serializedSize(container->m_mountingPosition) + static_cast<std::streamsize>(2 * sizeof(double))
           + static_cast<std::streamsize>(2 * sizeof(uint16_t)) + static_cast<std::streamsize>(sizeof(uint32_t))
           + static_cast<std::streamsize>(container->getImageSize());
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Image2403>::deserialize(std::istream& is,
                                                              DataContainerBase& c,
                                                              const IbeoDataHeader& dh) const
{
    C* container{nullptr};
    try
    {
        container = &dynamic_cast<C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(is.tellg());

    uint16_t imgFmt = 0;
    ibeo::common::sdk::readBE(is, imgFmt); // 2

    ibeo::common::sdk::readBE(is, container->m_microseconds); // 4
    ibeo::common::sdk::readBE(is, container->m_timestamp); // 8
    ibeo::common::sdk::readBE(is, container->m_deviceId); // 1
    ibeo::common::sdk::readBE(is, container->m_mountingPosition); // 6*4 = 24
    ibeo::common::sdk::readBE(is, container->m_hOpeningAngle); // 8
    ibeo::common::sdk::readBE(is, container->m_vOpeningAngle); // 8

    uint16_t width;
    uint16_t height;
    uint32_t imageSize;
    ibeo::common::sdk::readBE(is, width); // 2
    ibeo::common::sdk::readBE(is, height); // 2
    ibeo::common::sdk::readBE(is, imageSize); // 4

    image::ImageFormat imageFormat = Image2403::getGeneralImageFormat(static_cast<image::ImageFormatIn2403>(imgFmt));
    container->presetImageBuffer(imageFormat, imageSize, width, height);
    is.read(&container->getImageBuffer()->getDataBuffer()[0], imageSize);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

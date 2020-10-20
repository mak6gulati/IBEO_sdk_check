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

#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130Importer6130.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::FrameIndex6130;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_FrameIndex6130>;
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

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter
    = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(registeredImporterInitial);

//==============================================================================

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_FrameIndex6130>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c); // ignore the return value
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const std::streamsize nbOfFrameIndices = static_cast<std::streamsize>(container->m_frameIndices.size());
    const std::streamsize sizeOfIdxEntry
        = static_cast<std::streamsize>(FrameIndexEntryIn6130::getSerializedSize_static());

    return static_cast<std::streamsize>(serializedBaseSize) + (nbOfFrameIndices * sizeOfIdxEntry);
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_FrameIndex6130>::deserialize(std::istream& is,
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

    container->setDataHeader(dh);
    const int64_t startPos = streamposToInt64(is.tellg());

    uint8_t verMajor;
    ibeo::common::sdk::readBE(is, verMajor);
    if (verMajor != C::majorVersion)
    {
        return false;
    }

    uint8_t verMinor;
    ibeo::common::sdk::readBE(is, verMinor);
    if (verMinor != C::minorVersion)
    {
        return false;
    }

    std::string nameStr;
    nameStr.resize(strlen(C::nameString));
    is.read(&nameStr[0], std::streamsize(nameStr.size())); // assuming contiguous storage for std::string.

    uint64_t nbOfFrames;
    ibeo::common::sdk::readBE(is, nbOfFrames);

    ibeo::common::sdk::readBE(is, container->m_timeOffsetMs);
    container->m_framingPolicy.deserialize(is);

    // there is room for at most 30 triggers
    int32_t numPaddingBytes;
    numPaddingBytes = static_cast<int32_t>(128 - 35 - container->m_framingPolicy.getSerializedSize());

    uint8_t padding;
    while (numPaddingBytes-- > 0)
    {
        ibeo::common::sdk::readBE(is, padding);
    }
    container->m_frameIndices.resize(C::FrameVector::size_type(nbOfFrames)); // stl only supports 32 bit size.
    for (FrameIndexEntryIn6130& frameIndex : container->m_frameIndices)
    {
        frameIndex.deserialize(is);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

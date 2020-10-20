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
//!\date Mar 21, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/eventtag/EventTag7000Importer7000.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::EventTag7000;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_EventTag7000>;
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

template<>
void readBE<C::TagClass>(std::istream& is, C::TagClass& tc)
{
    uint16_t rd16;
    readBE(is, rd16);
    tc = C::TagClass(rd16);
}

//==============================================================================

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_EventTag7000>::getSerializedSize(const DataContainerBase& c) const
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

    return serializedBaseSize + std::streamsize(container->m_tagString.size())
           + PositionWgs84::getSerializedSize_static();
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_EventTag7000>::deserialize(std::istream& is,
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

    readBE(is, container->m_tagStart);
    readBE(is, container->m_tagEnd);
    readBE(is, container->m_flags);
    readBE(is, container->m_tagClass);
    readBE(is, container->m_tagId);
    {
        uint8_t strLength;
        readBE(is, strLength);
        container->m_tagString.resize(strLength);
        is.read(&container->m_tagString[0], strLength); // assuming contiguous storage for std::string.
    }
    if (!container->m_wgs84.deserialize(is))
    {
        return false;
    }

    readBE(is, container->m_roiWidth);
    readBE(is, container->m_roiLength);

    is.read(container->m_reserved.data(), C::nbOfReserved);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

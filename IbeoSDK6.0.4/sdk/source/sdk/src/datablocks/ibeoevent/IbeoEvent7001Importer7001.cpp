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
//!\date Mar 26, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/frameendseparator/FrameEndSeparator1100Importer1100.hpp>
#include <ibeo/common/sdk/datablocks/ibeoevent/IbeoEvent7001Importer7001.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::IbeoEvent7001;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_IbeoEvent7001>;
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

std::streamsize Importer<C, DataTypeId::DataType_IbeoEvent7001>::getSerializedSize(const DataContainerBase& c) const
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

    return serializedBaseSize + static_cast<std::streamsize>(container->m_body.length())
           + static_cast<std::streamsize>(container->m_author.length());
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_IbeoEvent7001>::deserialize(std::istream& is,
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

    readBE(is, container->m_type); // read type

    uint32_t length;
    // Body
    readBE(is, length); //read length of body
    container->m_body.clear();
    container->m_body.resize(length);
    std::vector<char> buf(length);
    if (!buf.empty())
    {
        is.read(&buf.front(), length); //read body
        std::copy(buf.begin(), buf.end(), container->m_body.begin());
    }

    // Author
    readBE(is, length); // read length of author
    container->m_author.clear();
    container->m_author.resize(length);
    buf.resize(length);
    if (!buf.empty())
    {
        is.read(&buf.front(), length); // read author
        std::copy(buf.begin(), buf.end(), container->m_author.begin());
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

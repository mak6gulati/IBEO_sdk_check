//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Feb 02, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationList7110Importer7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationEcuIdIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationAppBaseConfigIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationKeywordsIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationVersionNumberIn7110.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::MetaInformationList7110;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_MetaInformationList7110>;
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

Importer<C, DataTypeId::DataType_MetaInformationList7110>::Importer() : RegisteredImporter()
{
    // Register known meta information types at factory.
    m_factory.registerType<MetaInformationEcuIdIn7110>(MetaInformationBaseIn7110::MetaInformationType::EcuId);
    m_factory.registerType<MetaInformationAppBaseConfigIn7110>(
        MetaInformationBaseIn7110::MetaInformationType::AppBaseConfig);
    m_factory.registerType<MetaInformationKeywordsIn7110>(MetaInformationBaseIn7110::MetaInformationType::Keywords);
    m_factory.registerType<MetaInformationVersionNumberIn7110>(
        MetaInformationBaseIn7110::MetaInformationType::VersionNumber);
}

//==============================================================================
std::streamsize
Importer<C, DataTypeId::DataType_MetaInformationList7110>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize sz = std::streamsize(sizeof(uint32_t));

    for (const MetaInformationList7110::MetaInformationMap::value_type& vt : container->getMetaInformationMap())
    {
        for (const MetaInformationBaseIn7110SPtr& info : vt.second)
        {
            sz += info->getSerializedSize();
        } // for each vector entry
    } // for each map entry

    return sz;
}
//==============================================================================

bool Importer<C, DataTypeId::DataType_MetaInformationList7110>::deserialize(std::istream& is,
                                                                            DataContainerBase& c,
                                                                            const IbeoDataHeader& dh) const
{
    C* container{nullptr};
    try
    {
        container = &dynamic_cast<C&>(c); // ignore the return value
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    container->setDataHeader(dh);

    const int64_t startPos = streamposToInt64(is.tellg());

    uint32_t nbOfEntries;
    readBE(is, nbOfEntries);

    C::MetaInformationHeader mih;
    for (uint32_t i = 0; i < nbOfEntries && !is.fail(); ++i)
    {
        if (!mih.deserialize(is))
            break;

        //		std::cerr << "Read type " << mih.m_type << std::endl;
        // if the type is not registered or unknown from the current version, the data and the original type
        // are stored in the unsupported type. When serializing again, the original data will be restored.
        MetaInformationBaseIn7110SPtr info = m_factory.create(mih.m_type);
        if (info == nullptr)
        {
            info = std::make_shared<MetaInformationUnsupportedIn7110>(
                static_cast<uint16_t>(mih.m_type), mih.m_timeStamp, mih.m_payloadSize);
        }
        else
        {
            info->setTimestamp(mih.m_timeStamp);
        }

        if (!info->deserializePayload(is, mih.m_payloadSize))
        {
            break;
        }

        container->addMetaInformation(info);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

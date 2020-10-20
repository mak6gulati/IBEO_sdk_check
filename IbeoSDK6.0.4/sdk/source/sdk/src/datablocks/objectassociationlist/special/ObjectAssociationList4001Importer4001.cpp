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
//!\date Mar 20, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/objectassociationlist/special/ObjectAssociationList4001Importer4001.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::ObjectAssociationList4001;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_ObjectAssociationList4001>;
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
class IbeoScala;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
            registeredImporterInitial)));

//==============================================================================

//==============================================================================

ibeo::common::logging::LoggerSPtr ObjectAssociationList4001Importer4001::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

std::streamsize
Importer<C, DataTypeId::DataType_ObjectAssociationList4001>::getSerializedSize(const DataContainerBase& c) const
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

    return std::streamsize(4 * sizeof(uint8_t)) + std::streamsize(2 * sizeof(uint16_t))
           + std::streamsize(sizeof(uint32_t)) + std::streamsize(C::nbOfReserved)
           + std::streamsize(container->m_objAssocs.size()) * ObjectAssociationIn4001::getSerializedSize_static();
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_ObjectAssociationList4001>::deserialize(std::istream& is,
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

    readBE(is, container->m_refObjListId);
    readBE(is, container->m_refDevType);
    readBE(is, container->m_refDevInterfaceVersion);
    readBE(is, container->m_dutObjListId);
    readBE(is, container->m_dutDevType);
    readBE(is, container->m_dutDevInterfaceVersion);

    try
    {
        uint32_t nbOfObjAssocs;
        readBE(is, nbOfObjAssocs);
        container->m_objAssocs.resize(nbOfObjAssocs);
    }
    catch (const std::bad_alloc& ba)
    {
        LOGERROR(logger, "bad_alloc caught: " << ba.what());
        return false;
    }

    for (auto& reserved : container->m_reserved)
    {
        readBE(is, reserved);
    }

    bool vectorDeserializationIsOk{true};
    for (auto& objAssocEl : container->getObjectAssociations())
    {
        if (!objAssocEl.deserialize(is))
        {
            vectorDeserializationIsOk = false;
            break;
        }
    }

    return vectorDeserializationIsOk && !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

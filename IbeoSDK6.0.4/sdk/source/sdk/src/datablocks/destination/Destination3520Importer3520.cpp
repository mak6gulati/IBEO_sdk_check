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
//!\date Sept 05, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/destination/Destination3520Importer3520.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::Destination3520;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Destination3520>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================
// Specializations for RegisteredImporter
//==============================================================================

//generate link between data-type-id/importer and importer create function <dtid, ImpHash> ==> Imp::create

template<>
const Id R::registeredImporterInitial
    = Id(std::make_pair(R::getDataTypeStatic(), C::getClassIdHashStatic()), R::create);

class IdcFile;
class IbeoEcu;

template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(registeredImporterInitial));

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_Destination3520>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize result = 0;
    result += container->m_targetPosition.getSerializedSize() // m_targetPosition
              + std::streamsize(sizeof(int64_t)) // m_targetId
              + std::streamsize(sizeof(uint64_t)) // m_timestamp
              + std::streamsize(sizeof(uint8_t)) // m_sourceType
              + std::streamsize(sizeof(uint8_t)) // m_destinationType
              + std::streamsize(sizeof(uint8_t)) // m_purposeType
              + std::streamsize(sizeof(uint32_t)) // m_id
              + std::streamsize(sizeof(uint32_t) * container->nbOfReserved); // reserved space

    return result;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Destination3520>::deserialize(std::istream& is,
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
    container->m_targetPosition.deserialize(is);
    readBE(is, container->m_targetId);
    readBE(is, container->m_timestamp);
    readBE<Destination3520::SourceType, uint8_t>(is, container->m_sourceType);
    readBE<Destination3520::DestinationType, uint8_t>(is, container->m_destinationType);
    readBE<Destination3520::PurposeType, uint8_t>(is, container->m_purposeType);
    readBE(is, container->m_id);

    for (auto& reserved : container->m_reserved)
    {
        readBE(is, reserved);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

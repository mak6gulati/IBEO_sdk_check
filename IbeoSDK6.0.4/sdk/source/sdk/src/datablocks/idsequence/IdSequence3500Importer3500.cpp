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
//!\date Sept 03, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/idsequence/IdSequence3500Importer3500.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================

namespace {
using C  = ibeo::common::sdk::IdSequence3500;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_IdSequence3500>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} //namespace

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

class IdcFile;
class IbeoEcu;

template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(registeredImporterInitial));

//==============================================================================

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_IdSequence3500>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize result = std::streamsize(sizeof(uint64_t)) // size of m_idSequence
                             + std::streamsize(container->m_idSequence.size() * sizeof(int64_t)) // m_idSequence
                             + std::streamsize(sizeof(uint64_t)) // m_timestamp
                             + std::streamsize(sizeof(uint8_t)) // m_sourceType
                             + std::streamsize(sizeof(uint32_t)) // m_id
                             + std::streamsize(sizeof(uint32_t) * container->nbOfReserved); // reserved space

    return result;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_IdSequence3500>::deserialize(std::istream& is,
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
    uint64_t sequenceSize  = 0;

    readBE<uint64_t>(is, sequenceSize);
    container->m_idSequence.resize(sequenceSize);

    for (auto& idSeq : container->m_idSequence)
    {
        readBE<int64_t>(is, idSeq);
    }

    readBE(is, container->m_timestamp);
    readBE<IdSequence3500::SourceType, uint8_t>(is, container->m_sourceType);
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

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
//!\date 15.November 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84SequenceImporter3510.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::PositionWgs84Sequence;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_PositionWgs84Sequence3510>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
const Id R::registeredImporterInitial
    = Id(std::make_pair(R::getDataTypeStatic(), C::getClassIdHashStatic()), R::create);

class IdcFile;
class IbeoEcu;

template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(registeredImporterInitial));

//==============================================================================

std::streamsize
Importer<C, DataTypeId::DataType_PositionWgs84Sequence3510>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize result = std::streamsize(sizeof(uint64_t));

    for (auto positionWgs84 : container->m_positionSequence)
    {
        result += positionWgs84.getSerializedSize();
    }

    result += std::streamsize(sizeof(uint64_t)) // m_timestamp
              + std::streamsize(sizeof(uint8_t)) // m_sourceType
              + std::streamsize(sizeof(uint32_t)) // m_id
              + std::streamsize(sizeof(uint32_t) * container->nbOfReserved); // reserved space

    return result;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_PositionWgs84Sequence3510>::deserialize(std::istream& is,
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
    container->m_positionSequence.resize(sequenceSize);

    for (auto& positionWgs84 : container->m_positionSequence)
    {
        if (!positionWgs84.deserialize(is))
        {
            return false;
        }
    }

    readBE(is, container->m_timestamp);
    readBE<PositionWgs84Sequence::SourceType, uint8_t>(is, container->m_sourceType);
    readBE(is, container->m_id);

    for (auto& reserved : container->getReserved())
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

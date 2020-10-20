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
//!\date 08.November 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/idsequence/IdSequenceExporter3500.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::IdSequence;
}
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_IdSequence3500>::getSerializedSize(const DataContainerBase& c) const
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

bool Exporter<C, DataTypeId::DataType_IdSequence3500>::serialize(std::ostream& os, const DataContainerBase& c) const
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
    // write size of sequence so that size can be retrieved when deserializing
    writeBE<uint64_t>(os, container->m_idSequence.size());

    for (auto& idSeq : container->m_idSequence)
    {
        writeBE<int64_t>(os, idSeq);
    }

    writeBE(os, container->m_timestamp);
    writeBE<C::SourceType, uint8_t>(os, container->m_sourceType);
    writeBE(os, container->m_id);

    for (auto& reserved : container->m_reserved)
    {
        writeBE(os, reserved);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

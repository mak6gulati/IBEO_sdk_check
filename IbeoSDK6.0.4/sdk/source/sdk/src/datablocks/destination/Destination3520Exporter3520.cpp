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

#include <ibeo/common/sdk/datablocks/destination/Destination3520Exporter3520.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::Destination3520;
} //namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_Destination3520>::getSerializedSize(const DataContainerBase& c) const
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

bool Exporter<C, DataTypeId::DataType_Destination3520>::serialize(std::ostream& os, const DataContainerBase& c) const
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
    container->m_targetPosition.serialize(os);
    writeBE(os, container->m_targetId);
    writeBE(os, container->m_timestamp);
    writeBE<Destination3520::SourceType, uint8_t>(os, container->m_sourceType);
    writeBE<Destination3520::DestinationType, uint8_t>(os, container->m_destinationType);
    writeBE<Destination3520::PurposeType, uint8_t>(os, container->m_purposeType);
    writeBE(os, container->m_id);

    for (auto reserved : container->m_reserved)
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

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

#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84SequenceExporter3510.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::PositionWgs84Sequence;
} //namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
std::streamsize
Exporter<C, DataTypeId::DataType_PositionWgs84Sequence3510>::getSerializedSize(const DataContainerBase& c) const
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

    result += std::streamsize(sizeof(uint64_t));

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

bool Exporter<C, DataTypeId::DataType_PositionWgs84Sequence3510>::serialize(std::ostream& os,
                                                                            const DataContainerBase& c) const
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
    writeBE<uint64_t>(os, container->m_positionSequence.size());

    for (auto& positionWgs84 : container->m_positionSequence)
    {
        if (!positionWgs84.serialize(os))
        {
            return false;
        }
    }

    writeBE(os, container->m_timestamp);
    writeBE<PositionWgs84Sequence::SourceType, uint8_t>(os, container->m_sourceType);
    writeBE(os, container->m_id);

    for (auto& reserved : container->getReserved())
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

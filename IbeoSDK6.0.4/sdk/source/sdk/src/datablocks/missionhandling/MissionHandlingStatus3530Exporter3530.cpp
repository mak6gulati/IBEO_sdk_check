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
//!\date 07.November 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/missionhandling/MissionHandlingStatus3530Exporter3530.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::MissionHandlingStatus3530;
}
//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_MissionHandlingStatus3530>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize result = std::streamsize(sizeof(uint64_t)) // m_timestamp
                             + std::streamsize(sizeof(uint8_t)) // m_state
                             + std::streamsize(sizeof(uint32_t)) // m_missionId
                             + std::streamsize(sizeof(uint32_t) * container->nbOfReserved); // reserved space
    return result;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_MissionHandlingStatus3530>::serialize(std::ostream& os,
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

    writeBE(os, container->m_timestamp);
    writeBE<MissionHandlingStatus3530::State, uint8_t>(os, container->m_state);
    writeBE(os, container->m_missionId);

    for (auto reserved : container->getReserved())
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

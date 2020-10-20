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

#include <ibeo/common/sdk/datablocks/missionresponse/MissionResponse3540Exporter3540.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::MissionResponse3540;
}
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_MissionResponse3540>::getSerializedSize(const DataContainerBase& c) const
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
                             + std::streamsize(sizeof(uint8_t)) // m_response
                             + std::streamsize(sizeof(uint32_t)) // m_missionId
                             + std::streamsize(sizeof(uint32_t) * container->nbOfReserved); // reserved space

    return result;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_MissionResponse3540>::serialize(std::ostream& os,
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
    writeBE<MissionResponse3540::Response, uint8_t>(os, container->m_response);
    writeBE(os, container->m_missionId);

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

//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date March 19, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9010Exporter9010.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::TimeRelationsList9010;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_TimeRelationsList9010>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize result = std::streamsize(sizeof(uint8_t)) + std::streamsize(sizeof(uint32_t));

    for (const auto& relation : container->m_timeRelationsMap)
    {
        result += relation.first.getSerializedSize();
        result += relation.second.getSerializedSize();
    }
    return result;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_TimeRelationsList9010>::serialize(std::ostream& os,
                                                                        const DataContainerBase& c) const
{
    const C* const container = dynamic_cast<const C*>(&c);
    if (!container) //casting failed
    {
        return false;
    }

    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, static_cast<uint8_t>(1));
    ibeo::common::sdk::writeBE(os, uint32_t(container->m_timeRelationsMap.size()));

    for (const auto& relation : container->m_timeRelationsMap)
    {
        relation.first.serialize(os);
        relation.second.serialize(os);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date March 15, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9011Exporter9011.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::TimeRelationsList9011;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_TimeRelationsList9011>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize result = container->m_referenceClock.getSerializedSize() + std::streamsize(sizeof(uint8_t));
    for (auto& timeRelation : container->m_timeRelations)
    {
        result += timeRelation.getSerializedSize();
    }
    return result;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_TimeRelationsList9011>::serialize(std::ostream& os,
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

    container->m_referenceClock.serialize(os);

    const uint8_t relationsCount = uint8_t(container->m_timeRelations.size());
    ibeo::common::sdk::writeBE(os, relationsCount);

    for (auto& timeRelation : container->m_timeRelations)
    {
        timeRelation.serialize(os);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

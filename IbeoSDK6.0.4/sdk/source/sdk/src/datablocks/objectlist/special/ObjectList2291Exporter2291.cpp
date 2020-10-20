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
//!\date Jan 17, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2291Exporter2291.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::ObjectList2291;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_ObjectList2291>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize sz = std::streamsize(sizeof(NTPTime) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint16_t)
                                         + sizeof(uint16_t) + sizeof(uint16_t));

    for (const ObjectIn2291& obj : container->m_objects)
    {
        sz += obj.getSerializedSize();
    }

    return sz;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_ObjectList2291>::serialize(std::ostream& os, const DataContainerBase& c) const
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
    writeBE(os, container->m_objectListId);
    writeBE(os, container->m_deviceType);
    writeBE(os, container->m_deviceInterfaceVersion);
    writeBE(os, container->m_flags);
    writeBE(os, container->m_reserved1);
    writeBE(os, uint16_t(container->m_objects.size()));

    for (const ObjectIn2291& obj : container->m_objects)
    {
        obj.serialize(os);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

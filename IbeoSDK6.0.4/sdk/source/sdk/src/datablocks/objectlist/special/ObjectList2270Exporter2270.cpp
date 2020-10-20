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

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2270Exporter2270.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::ObjectList2270;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_ObjectList2270>::getSerializedSize(const DataContainerBase& c) const
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

    std::streamsize sz = 2 * std::streamsize(sizeof(uint16_t)) + std::streamsize(sizeof(NTPTime));

    for (const ObjectIn2270& object : container->m_objects)
    {
        sz += object.getSerializedSize();
    }
    return sz;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_ObjectList2270>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    ibeo::common::sdk::writeLE(os, container->m_scanStartTimestamp);
    ibeo::common::sdk::writeLE(os, container->m_scanNumber);

    ibeo::common::sdk::writeLE(os, container->getNbOfObjects());

    for (const ObjectIn2270& object : container->m_objects)
    {
        object.serialize(os);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

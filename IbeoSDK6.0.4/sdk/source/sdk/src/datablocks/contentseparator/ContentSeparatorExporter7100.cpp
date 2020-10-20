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
//!\date Feb 4, 2019
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100Exporter7100.hpp>
#include <ibeo/common/sdk/datablocks/contentseparator/ContentSeparatorExporter7100.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::ContentSeparator;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_ContentSeparator7100>::getSerializedSize(const DataContainerBase& c) const
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

    const ContentSeparator7100Exporter7100 delegate;
    return delegate.getSerializedSize(container->m_delegate);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_ContentSeparator7100>::serialize(std::ostream& os,
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

    const ContentSeparator7100Exporter7100 delegate;
    return delegate.serialize(os, container->m_delegate);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

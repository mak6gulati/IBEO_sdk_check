//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Jan 24, 2019
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/frameindex/FrameIndexExporter6130.hpp>
#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130Exporter6130.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::FrameIndex;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_FrameIndex6130>::getSerializedSize(const DataContainerBase& c) const
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

    const FrameIndex6130Exporter6130 delegate;
    return delegate.getSerializedSize(container->m_delegate);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_FrameIndex6130>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    const FrameIndex6130Exporter6130 delegate;
    return delegate.serialize(os, container->m_delegate);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

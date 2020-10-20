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
//!\date Jan 29th, 2019
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/odometry/special/Odometry9002Exporter9002.hpp>
#include <ibeo/common/sdk/datablocks/odometry/OdometryExporter9002.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::Odometry;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_Odometry9002>::getSerializedSize(const DataContainerBase& c) const
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

    const Odometry9002Exporter9002 delegate;
    return delegate.getSerializedSize(container->m_delegate);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_Odometry9002>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    const Odometry9002Exporter9002 delegate;
    return delegate.serialize(os, container->m_delegate);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

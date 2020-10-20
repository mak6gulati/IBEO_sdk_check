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
//! \date Jan 31, 2019
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/ogpsimumessage/OGpsImuMessageExporter2610.hpp>
#include <ibeo/common/sdk/datablocks/ogpsimumessage/special/OGpsImuMessage2610Exporter2610.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::OGpsImuMessage;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_OGpsImuMessage2610>::getSerializedSize(const DataContainerBase& c) const
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

    const OGpsImuMessage2610Exporter2610 delegate;
    return delegate.getSerializedSize(container->m_delegate);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_OGpsImuMessage2610>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    const OGpsImuMessage2610Exporter2610 delegate;
    return delegate.serialize(os, container->m_delegate);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

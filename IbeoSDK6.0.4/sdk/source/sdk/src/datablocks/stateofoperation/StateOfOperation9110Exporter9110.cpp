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
//!\date Mar 16, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/stateofoperation/StateOfOperation9110Exporter9110.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::StateOfOperation9110;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_StateOfOperation9110>::getSerializedSize(const DataContainerBase& c) const
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

    return serializedBaseSize + container->m_timestamp.getSerializedSize();
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_StateOfOperation9110>::serialize(std::ostream& os,
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

    container->m_timestamp.serialize(os);
    writeBE<C::Operation, uint8_t>(os, container->m_operation);
    writeBE<C::DriverInterrupt, uint8_t>(os, container->m_driverInterrupt);
    writeBE(os, container->m_takeOverRequest);

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

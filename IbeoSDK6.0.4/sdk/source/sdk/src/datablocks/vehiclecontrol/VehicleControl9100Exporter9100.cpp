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
//!\date Mar 26, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/vehiclecontrol/VehicleControl9100Exporter9100.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::VehicleControl9100;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_VehicleControl9100>::getSerializedSize(const DataContainerBase& c) const
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

bool Exporter<C, DataTypeId::DataType_VehicleControl9100>::serialize(std::ostream& os, const DataContainerBase& c) const
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
    writeBE(os, static_cast<uint8_t>(container->m_sourceType));
    writeBE(os, static_cast<uint8_t>(container->m_steeringType));
    writeBE(os, container->m_steeringValue);
    writeBE(os, static_cast<uint8_t>(container->m_indicatorState));
    writeBE(os, container->m_accelerationValue);
    writeBE(os, static_cast<uint8_t>((container->m_doStop) ? 1 : 0));
    writeBE(os, container->m_stopDistance);

    for (auto& r : container->m_reserved)
    {
        writeBE(os, r);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Mar 18, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/odometry/special/Odometry9002Exporter9002.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::Odometry9002;
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

    return serializedBaseSize + container->m_timestamp.getSerializedSize();
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

    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, container->m_steeringAngle);
    writeBE(os, container->m_steeringWheelAngle);
    writeBE(os, container->m_steeringWheelAngleVelocity);
    writeBE(os, container->m_wheelSpeedFL);
    writeBE(os, container->m_wheelSpeedFR);
    writeBE(os, container->m_wheelSpeedRL);
    writeBE(os, container->m_wheelSpeedRR);
    writeBE(os, container->m_wheelCircumference);
    writeBE(os, container->m_vehVelocity);
    writeBE(os, container->m_vehAcceleration);
    writeBE(os, container->m_vehYawRate);
    container->m_timestamp.serialize(os);

    writeBE(os, container->m_wheelBase);

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

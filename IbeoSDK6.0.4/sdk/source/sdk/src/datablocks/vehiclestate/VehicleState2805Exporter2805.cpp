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
//!\date Jan 19, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2805Exporter2805.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::VehicleState2805;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_VehicleStateBasic2805>::getSerializedSize(const DataContainerBase& c) const
{
    try
    {
        (void)dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return serializedSize;
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_VehicleStateBasic2805>::serialize(std::ostream& os,
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

    writeLE(os, container->m_timestamp);
    writeLE(os, container->m_scanNumber);
    writeLE(os, container->m_errorFlags);
    writeLE(os, container->m_longitudinalVelocity);
    writeLE(os, container->m_steeringWheelAngle);
    writeLE(os, container->m_wheelAngle);
    writeLE(os, container->m_crossAccelertation);

    writeLE(os, container->m_xPos);
    writeLE(os, container->m_yPos);
    writeLE(os, container->m_courseAngle);

    writeLE(os, container->m_timeDiff);
    writeLE(os, container->m_xDiff);
    writeLE(os, container->m_yDiff);
    writeLE(os, container->m_yaw);

    writeLE(os, container->m_calculationMethod);
    writeLE(os, container->m_currentYawRate);
    writeLE(os, container->m_reserved2);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}
//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

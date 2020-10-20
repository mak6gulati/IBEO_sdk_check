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

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2806Exporter2806.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::VehicleState2806;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_VehicleStateBasic2806>::getSerializedSize(const DataContainerBase& c) const
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

bool Exporter<C, DataTypeId::DataType_VehicleStateBasic2806>::serialize(std::ostream& os,
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

    writeBE(os, container->m_microseconds);
    writeBE(os, container->m_timestamp);
    writeBE(os, container->m_xPos);
    writeBE(os, container->m_yPos);
    writeBE(os, container->m_courseAngle);
    writeBE(os, container->m_longitudinalVelocity);
    writeBE(os, container->m_yawRate);
    writeBE(os, container->m_steeringWheelAngle);
    writeBE(os, container->m_crossAcceleration);
    writeBE(os, container->m_frontWheelAngle);
    writeBE(os, container->m_blindPredictionAge);
    writeBE(os, container->m_vehicleWidth);
    writeBE(os, container->m_minTurningCircle);
    writeBE(os, container->m_vehicleFrontToFrontAxle);
    writeBE(os, container->m_frontAxleToRearAxle);
    writeBE(os, container->m_rearAxleToVehicleRear);
    writeBE(os, container->m_rearAxleToOrigin);
    writeBE(os, container->m_steerRatioCoeff0);
    writeBE(os, container->m_steerRatioCoeff1);
    writeBE(os, container->m_steerRatioCoeff2);
    writeBE(os, container->m_steerRatioCoeff3);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}
//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

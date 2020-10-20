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
//!\date Jan 19, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2808Exporter2808.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::VehicleState2808;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_VehicleStateBasic2808>::getSerializedSize(const DataContainerBase& c) const
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

bool Exporter<C, DataTypeId::DataType_VehicleStateBasic2808>::serialize(std::ostream& os,
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
    writeBE(os, container->m_sources);
    writeBE(os, container->m_blindPredictionAge);

    writeBE(os, container->m_latitude);
    writeBE(os, container->m_latitudeSigma);
    writeBE(os, container->m_longitude);
    writeBE(os, container->m_longitudeSigma);
    writeBE(os, container->m_altitude);
    writeBE(os, container->m_altitudeSigma);

    writeBE(os, container->m_xPosition);
    writeBE(os, container->m_xPositionSigma);
    writeBE(os, container->m_yPosition);
    writeBE(os, container->m_yPositionSigma);
    writeBE(os, container->m_zPosition);
    writeBE(os, container->m_zPositionSigma);

    writeBE(os, container->m_xyCorrelation);
    writeBE(os, container->m_xzCorrelation);
    writeBE(os, container->m_yzCorrelation);

    writeBE(os, container->m_courseAngle);
    writeBE(os, container->m_courseAngleSigma);
    writeBE(os, container->m_headingAngle);
    writeBE(os, container->m_headingAngleSigma);

    writeBE(os, container->m_vehiclePitchAngle);
    writeBE(os, container->m_vehiclePitchAngleSigma);
    writeBE(os, container->m_vehicleRollAngle);
    writeBE(os, container->m_vehicleRollAngleSigma);

    writeBE(os, container->m_vehicleVelocity);
    writeBE(os, container->m_vehicleVelocitySigma);

    writeBE(os, container->m_yawRate);
    writeBE(os, container->m_yawRateSigma);

    writeBE(os, container->m_longitudinalAcceleration);
    writeBE(os, container->m_longitudinalAccelerationSigma);
    writeBE(os, container->m_crossAcceleration);
    writeBE(os, container->m_crossAccelerationSigma);

    writeBE(os, container->m_steerAngle);
    writeBE(os, container->m_steeringWheelAngle);

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

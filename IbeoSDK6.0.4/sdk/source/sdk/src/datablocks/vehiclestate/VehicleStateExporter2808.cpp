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
//!\date Sep 1, 2017
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleStateExporter2808.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::VehicleState;
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

bool Exporter<C, DataTypeId::DataType_VehicleStateBasic2808>::serialize(std::ostream& outStream,
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

    const int64_t startPos = streamposToInt64(outStream.tellp());

    writeBE(outStream, container->getMicroseconds());
    writeBE(outStream, container->getTimestamp());
    writeBE(outStream, container->getSources());
    writeBE(outStream, container->getBlindPredictionAge());

    writeBE(outStream, container->getLatitudeOfOrigin());
    writeBE(outStream, container->getLatitudeOfOriginSigma());
    writeBE(outStream, container->getLongitudeOfOrigin());
    writeBE(outStream, container->getLongitudeOfOriginSigma());
    writeBE(outStream, container->getAltitudeOfOrigin());
    writeBE(outStream, container->getAltitudeOfOriginSigma());

    writeBE(outStream, container->getRelativeXPosition());
    writeBE(outStream, container->getRelativeXPositionSigma());
    writeBE(outStream, container->getRelativeYPosition());
    writeBE(outStream, container->getRelativeYPositionSigma());
    writeBE(outStream, container->getRelativeZPosition());
    writeBE(outStream, container->getRelativeZPositionSigma());

    writeBE(outStream, container->getXyCorrelation());
    writeBE(outStream, container->getXzCorrelation());
    writeBE(outStream, container->getYzCorrelation());

    writeBE(outStream, container->getCourseAngle());
    writeBE(outStream, container->getCourseAngleSigma());
    writeBE(outStream, container->getHeadingAngle());
    writeBE(outStream, container->getHeadingAngleSigma());

    writeBE(outStream, container->getVehiclePitchAngle());
    writeBE(outStream, container->getVehiclePitchAngleSigma());
    writeBE(outStream, container->getVehicleRollAngle());
    writeBE(outStream, container->getVehicleRollAngleSigma());

    writeBE(outStream, container->getLongitudinalVelocity());
    writeBE(outStream, container->getLongitudinalVelocitySigma());

    writeBE(outStream, container->getYawRate());
    writeBE(outStream, container->getYawRateSigma());

    writeBE(outStream, container->getLongitudinalAcceleration());
    writeBE(outStream, container->getLongitudinalAccelerationSigma());
    writeBE(outStream, container->getCrossAcceleration());
    writeBE(outStream, container->getCrossAccelerationSigma());

    writeBE(outStream, container->getSteerAngle());
    writeBE(outStream, container->getSteeringWheelAngle());

    writeBE(outStream, container->getVehicleWidth());
    writeBE(outStream, container->getMinTurningCircle());

    writeBE(outStream, container->getVehicleFrontToFrontAxle());
    writeBE(outStream, container->getFrontAxleToRearAxle());
    writeBE(outStream, container->getRearAxleToVehicleRear());
    writeBE(outStream, container->getRearAxleToOrigin());
    writeBE(outStream, container->getSteerRatioCoeff0());
    writeBE(outStream, container->getSteerRatioCoeff1());
    writeBE(outStream, container->getSteerRatioCoeff2());
    writeBE(outStream, container->getSteerRatioCoeff3());

    return !outStream.fail() && ((streamposToInt64(outStream.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

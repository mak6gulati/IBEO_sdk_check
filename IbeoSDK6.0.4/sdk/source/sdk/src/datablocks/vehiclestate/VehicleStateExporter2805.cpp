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
//! \date Sep 1, 2017
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleStateExporter2805.hpp>

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

bool Exporter<C, DataTypeId::DataType_VehicleStateBasic2805>::serialize(std::ostream& outStream,
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

    writeLE(outStream, container->getTimestamp());

    writeLE(outStream, uint16_t(0)); //ScanNumber
    writeLE(outStream, uint16_t(0)); //ErrorFlags
    {
        const float longitudinalVelocity = container->getLongitudinalVelocity() * 100.0F; //convert [m/s] -> [0.01 m/s]
        writeLE(outStream, ibeo::common::sdk::round<int16_t>(longitudinalVelocity));
    }
    {
        const float steeringWheelAngle = container->getSteeringWheelAngle() * 1000.0F; //convert [rad] -> [0.001 rad]
        writeLE(outStream, ibeo::common::sdk::round<int16_t>(steeringWheelAngle));
    }
    {
        //writeLE(outStream, container->getWheelAngle());
        const float wheelAngle = container->getSteerAngle() * 10000.0F; //convert [rad] -> [0.0001 rad]
        writeLE(outStream, ibeo::common::sdk::round<int16_t>(wheelAngle));
    }
    { //crossAcceleration (was reserved0)
        const float crossAcceleration = container->getCrossAcceleration() * 1000.0F; // convert [m/s^2] -> [0.001 m/s^2]
        writeLE(outStream, ibeo::common::sdk::round<int16_t>(crossAcceleration));
    }
    {
        const int32_t posX
            = ibeo::common::sdk::round<int32_t>(container->getRelativeXPosition()) * 100; //convert [m] -> [0.01 m]
        writeLE(outStream, posX);
    }
    {
        const int32_t posY
            = ibeo::common::sdk::round<int32_t>(container->getRelativeYPosition()) * 100; //convert [m] -> [0.01 m]
        writeLE(outStream, posY);
    }
    {
        const float courseAngle = container->getCourseAngle() * 10000.0F; // convert [rad] -> [0,0001 rad]
        writeLE(outStream, ibeo::common::sdk::round<int16_t>(courseAngle));
    }
    writeLE(outStream, uint16_t(0)); //AbsOrientationAtTimedDiff
    writeLE(outStream, int16_t(0)); //Xdiff
    writeLE(outStream, int16_t(0)); //Ydiff
    writeLE(outStream, int16_t(0)); //Yaw
    writeLE(outStream, uint16_t(0)); //calculationMethod // (was reserved1)
    {
        //writeLE(outStream, container->getCurrentYawRate());
        const float yawRate = container->getYawRate() * 10000; //convert [rad/s] -> [0.0001 rad/s]
        writeLE(outStream, ibeo::common::sdk::round<int16_t>(yawRate));
    }
    writeLE(outStream, uint32_t(0)); //reserved2

    return !outStream.fail() && ((streamposToInt64(outStream.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

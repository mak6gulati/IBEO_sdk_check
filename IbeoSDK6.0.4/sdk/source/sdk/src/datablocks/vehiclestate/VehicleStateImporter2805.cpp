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
//! \date Aug 10, 2017
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleStateImporter2805.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::VehicleState;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_VehicleStateBasic2805>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
// Specializations for RegisteredImporter
//==============================================================================

//generate link between data-type-id/importer and importer create function <dtid, ImpHash> ==> Imp::create

template<>
const Id R::registeredImporterInitial
    = Id(std::make_pair(R::getDataTypeStatic(), C::getClassIdHashStatic()), R::create);

//registering ... (create map)
//add all device that can receive any datatype that can be imported to GeneralDataTypeContainer
class IdcFile;
class IbeoEcu;
class IbeoLux;
class IbeoLuxHr;
class IbeoMiniLux;
class IbeoScala;
class IbeoTrackingBox;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const ImporterBase::ImporterRegisterId R::registeredImporter
    = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoLux>::getInstance().registerImporter(
            ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(
                ContainerBufferAndImporterProviderGlobal<IbeoLuxHr>::getInstance().registerImporter(
                    ContainerBufferAndImporterProviderGlobal<IbeoMiniLux>::getInstance().registerImporter(
                        ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
                            ContainerBufferAndImporterProviderGlobal<IbeoTrackingBox>::getInstance().registerImporter(
                                registeredImporterInitial)))))));

//==============================================================================

//==============================================================================

std::streamsize
Importer<C, DataTypeId::DataType_VehicleStateBasic2805>::getSerializedSize(const DataContainerBase& c) const
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

bool Importer<C, DataTypeId::DataType_VehicleStateBasic2805>::deserialize(std::istream& is,
                                                                          DataContainerBase& c,
                                                                          const IbeoDataHeader& dh) const
{
    C* container{nullptr};
    try
    {
        container = &dynamic_cast<C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(is.tellg());
    readLE(is, container->m_timestamp);

    uint16_t uint16_tmp;
    readLE(is, uint16_tmp); //ignore scanNumber
    readLE(is, uint16_tmp); //ignore errorFlags
    {
        int16_t longitudinalVelocity;
        readLE(is, longitudinalVelocity);
        container->setLongitudinalVelocity(static_cast<float>(longitudinalVelocity)
                                           * 1e-2F); //convert [0.01 m/s] -> [m/s]
    }
    {
        int16_t steeringWheelAngle;
        readLE(is, steeringWheelAngle);
        container->setSteeringWheelAngle(static_cast<float>(steeringWheelAngle) * 1e-3F); //convert [0.001 rad] -> [rad]
    }
    {
        int16_t wheelAngle;
        readLE(is, wheelAngle);
        container->setSteerAngle(static_cast<float>(wheelAngle) * 1e-4F); //convert [0.0001 rad] -> [rad]
    }
    {
        int16_t crossAcceleration; //cross acceleration (was reserved0)
        readLE(is, crossAcceleration);
        container->setCrossAcceleration(crossAcceleration * 1e-3F); // convert [0.001 m/s^2] -> [m/s^2]
    }
    {
        int32_t posX;
        readLE(is, posX);
        container->setRelativeXPosition(static_cast<double>(posX) * 1e-2); //convert [0.01m] -> [m]
    }
    {
        int32_t posY;
        readLE(is, posY);
        container->setRelativeYPosition(static_cast<double>(posY) * 1e-2); //convert [0.01m] -> [m]
    }
    {
        int16_t courseAngle;
        readLE(is, courseAngle);
        container->setCourseAngle(static_cast<float>(courseAngle) * 1e-4F); //convert [0,0001 rad] -> [rad]
    }
    readLE(is, uint16_tmp); //ignore timeDiff
    int16_t int16_tmp;
    readLE(is, int16_tmp); //ignore xDiff
    readLE(is, int16_tmp); //ignore yDiff
    readLE(is, int16_tmp); //ignore yaw
    readLE(is, uint16_tmp); //ignore calculation method (was reserved1)
    {
        uint16_t currentYawRate;
        readLE(is, currentYawRate);
        container->setYawRate(static_cast<float>(currentYawRate) * 1e-4F); //convert [0.0001 rad/s] -> [rad/s]
    }

    uint32_t uint32_tmp;
    readLE(is, uint32_tmp); //ignore reserved2 (unused atm);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == serializedSize)
           && serializedSize == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

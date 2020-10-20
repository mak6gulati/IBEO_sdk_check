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
//!\date Jan 18, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2808Importer2808.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::VehicleState2808;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_VehicleStateBasic2808>;
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

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(registeredImporterInitial));

//==============================================================================

//==============================================================================

std::streamsize
Importer<C, DataTypeId::DataType_VehicleStateBasic2808>::getSerializedSize(const DataContainerBase& c) const
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

bool Importer<C, DataTypeId::DataType_VehicleStateBasic2808>::deserialize(std::istream& is,
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

    container->setDataHeader(dh);

    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, container->m_microseconds);
    readBE(is, container->m_timestamp);
    readBE(is, container->m_sources);
    readBE(is, container->m_blindPredictionAge);

    readBE(is, container->m_latitude);
    readBE(is, container->m_latitudeSigma);
    readBE(is, container->m_longitude);
    readBE(is, container->m_longitudeSigma);
    readBE(is, container->m_altitude);
    readBE(is, container->m_altitudeSigma);

    readBE(is, container->m_xPosition);
    readBE(is, container->m_xPositionSigma);
    readBE(is, container->m_yPosition);
    readBE(is, container->m_yPositionSigma);
    readBE(is, container->m_zPosition);
    readBE(is, container->m_zPositionSigma);

    readBE(is, container->m_xyCorrelation);
    readBE(is, container->m_xzCorrelation);
    readBE(is, container->m_yzCorrelation);

    readBE(is, container->m_courseAngle);
    readBE(is, container->m_courseAngleSigma);
    readBE(is, container->m_headingAngle);
    readBE(is, container->m_headingAngleSigma);

    readBE(is, container->m_vehiclePitchAngle);
    readBE(is, container->m_vehiclePitchAngleSigma);
    readBE(is, container->m_vehicleRollAngle);
    readBE(is, container->m_vehicleRollAngleSigma);

    readBE(is, container->m_vehicleVelocity);
    readBE(is, container->m_vehicleVelocitySigma);

    readBE(is, container->m_yawRate);
    readBE(is, container->m_yawRateSigma);

    readBE(is, container->m_longitudinalAcceleration);
    readBE(is, container->m_longitudinalAccelerationSigma);
    readBE(is, container->m_crossAcceleration);
    readBE(is, container->m_crossAccelerationSigma);

    readBE(is, container->m_steerAngle);
    readBE(is, container->m_steeringWheelAngle);

    readBE(is, container->m_vehicleWidth);
    readBE(is, container->m_minTurningCircle);

    readBE(is, container->m_vehicleFrontToFrontAxle);
    readBE(is, container->m_frontAxleToRearAxle);
    readBE(is, container->m_rearAxleToVehicleRear);
    readBE(is, container->m_rearAxleToOrigin);
    readBE(is, container->m_steerRatioCoeff0);
    readBE(is, container->m_steerRatioCoeff1);
    readBE(is, container->m_steerRatioCoeff2);
    readBE(is, container->m_steerRatioCoeff3);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

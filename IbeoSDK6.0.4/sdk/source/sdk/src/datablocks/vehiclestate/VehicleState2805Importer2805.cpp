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
//! \date Jan 19, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2805Importer2805.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::VehicleState2805;
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
class IbeoLux;
class IbeoTrackingBox;
class IbeoScala;

//register listener types
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoLux>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoTrackingBox>::getInstance().registerImporter(
            ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
                registeredImporterInitial))));

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

    container->setDataHeader(dh);

    const int64_t startPos = streamposToInt64(is.tellg());

    readLE(is, container->m_timestamp);
    readLE(is, container->m_scanNumber);
    readLE(is, container->m_errorFlags);
    readLE(is, container->m_longitudinalVelocity);
    readLE(is, container->m_steeringWheelAngle);
    readLE(is, container->m_wheelAngle);
    readLE(is, container->m_crossAccelertation);

    readLE(is, container->m_xPos);
    readLE(is, container->m_yPos);
    readLE(is, container->m_courseAngle);

    readLE(is, container->m_timeDiff);
    readLE(is, container->m_xDiff);
    readLE(is, container->m_yDiff);
    readLE(is, container->m_yaw);

    readLE(is, container->m_calculationMethod);
    readLE(is, container->m_currentYawRate);
    readLE(is, container->m_reserved2);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

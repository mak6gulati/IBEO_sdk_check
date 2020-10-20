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
//!\date Mar 23, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001Importer9001.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/GpsImu.hpp>

//==============================================================================

#include <ibeo/common/sdk/datablocks/eventtag/EventTag7000Importer7000.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::GpsImu9001;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_GpsImu9001>;
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

std::streamsize Importer<C, DataTypeId::DataType_GpsImu9001>::getSerializedSize(const DataContainerBase& c) const
{
    try
    {
        (void)dynamic_cast<const C&>(c); // ignore the return value
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return serializedSize;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_GpsImu9001>::deserialize(std::istream& is,
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

    readBE(is, container->m_latitudeInRad);
    readBE(is, container->m_latitudeSigmaInMeter);
    readBE(is, container->m_longitudeInRad);
    readBE(is, container->m_longitudeSigmaInMeter);
    readBE(is, container->m_altitudeInMeter);
    readBE(is, container->m_altitudeSigmaInMeter);
    readBE(is, container->m_courseAngleInRad);
    readBE(is, container->m_courseAngleSigmaInRad);
    readBE(is, container->m_yawAngleInRad);
    readBE(is, container->m_yawAngleSigmaInRad);
    readBE(is, container->m_pitchAngleInRad);
    readBE(is, container->m_pitchAngleSigmaInRad);
    readBE(is, container->m_rollAngleInRad);
    readBE(is, container->m_rollAngleSigmaInRad);
    readBE(is, container->m_crossAccelerationInMeterPerSecond2);
    readBE(is, container->m_crossAccelerationSigmaInMeterPerSecond2);
    readBE(is, container->m_longitudinalAccelerationInMeterPerSecond2);
    readBE(is, container->m_longitudinalAccelerationSigmaInMeterPerSecond2);
    readBE(is, container->m_verticalAccelerationInMeterPerSecond2);
    readBE(is, container->m_verticalAccelerationSigmaInMeterPerSecond2);
    readBE(is, container->m_velocityNorthInMeterPerSecond);
    readBE(is, container->m_velocityNorthSigmaInMeterPerSecond);
    readBE(is, container->m_velocityWestInMeterPerSecond);
    readBE(is, container->m_velocityWestSigmaInMeterPerSecond);
    readBE(is, container->m_velocityUpInMeterPerSecond);
    readBE(is, container->m_velocityUpSigmaInMeterPerSecond);
    readBE(is, container->m_velocityXInMeterPerSecond);
    readBE(is, container->m_velocityXSigmaInMeterPerSecond);
    readBE(is, container->m_velocityYInMeterPerSecond);
    readBE(is, container->m_velocityYSigmaInMeterPerSecond);
    readBE(is, container->m_velocityZInMeterPerSecond);
    readBE(is, container->m_velocityZSigmaInMeterPerSecond);
    readBE(is, container->m_rollRateInRadPerSecond);
    readBE(is, container->m_rollRateSigmaInRadPerSecond);
    readBE(is, container->m_yawRateInRadPerSecond);
    readBE(is, container->m_yawRateSigmaInRadPerSecond);
    readBE(is, container->m_pitchRateInRadPerSecond);
    readBE(is, container->m_pitchRateSigmaInRadPerSecond);
    readBE(is, container->m_gpsStatus);
    readBE(is, container->m_noOfSatellites);
    readBE(is, container->m_gpsDilutionOfPrecisionX);
    readBE(is, container->m_gpsDilutionOfPrecisionY);
    readBE(is, container->m_gpsDilutionOfPrecisionZ);
    readBE(is, container->m_gpsDilutionOfPrecisionVertical);
    readBE(is, container->m_gpsDilutionOfPrecisionPosition);

    container->m_timestamp.deserialize(is);
    readBE(is, container->m_source);
    readBE(is, container->m_insQuality);

    for (auto& r : container->m_reserved)
    {
        readBE(is, r);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

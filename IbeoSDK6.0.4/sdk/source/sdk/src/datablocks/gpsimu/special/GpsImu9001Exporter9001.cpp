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

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/GpsImu.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001Exporter9001.hpp>
#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/misc/SdkExceptions.hpp>
#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <cstdint>
#include <iostream>
#include <typeinfo>

//==============================================================================
namespace {
using C = ibeo::common::sdk::GpsImu9001;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_GpsImu9001>::getSerializedSize(const DataContainerBase& c) const
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

bool Exporter<C, DataTypeId::DataType_GpsImu9001>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    writeBE(os, container->m_latitudeInRad);
    writeBE(os, container->m_latitudeSigmaInMeter);
    writeBE(os, container->m_longitudeInRad);
    writeBE(os, container->m_longitudeSigmaInMeter);
    writeBE(os, container->m_altitudeInMeter);
    writeBE(os, container->m_altitudeSigmaInMeter);
    writeBE(os, container->m_courseAngleInRad);
    writeBE(os, container->m_courseAngleSigmaInRad);
    writeBE(os, container->m_yawAngleInRad);
    writeBE(os, container->m_yawAngleSigmaInRad);
    writeBE(os, container->m_pitchAngleInRad);
    writeBE(os, container->m_pitchAngleSigmaInRad);
    writeBE(os, container->m_rollAngleInRad);
    writeBE(os, container->m_rollAngleSigmaInRad);
    writeBE(os, container->m_crossAccelerationInMeterPerSecond2);
    writeBE(os, container->m_crossAccelerationSigmaInMeterPerSecond2);
    writeBE(os, container->m_longitudinalAccelerationInMeterPerSecond2);
    writeBE(os, container->m_longitudinalAccelerationSigmaInMeterPerSecond2);
    writeBE(os, container->m_verticalAccelerationInMeterPerSecond2);
    writeBE(os, container->m_verticalAccelerationSigmaInMeterPerSecond2);
    writeBE(os, container->m_velocityNorthInMeterPerSecond);
    writeBE(os, container->m_velocityNorthSigmaInMeterPerSecond);
    writeBE(os, container->m_velocityWestInMeterPerSecond);
    writeBE(os, container->m_velocityWestSigmaInMeterPerSecond);
    writeBE(os, container->m_velocityUpInMeterPerSecond);
    writeBE(os, container->m_velocityUpSigmaInMeterPerSecond);
    writeBE(os, container->m_velocityXInMeterPerSecond);
    writeBE(os, container->m_velocityXSigmaInMeterPerSecond);
    writeBE(os, container->m_velocityYInMeterPerSecond);
    writeBE(os, container->m_velocityYSigmaInMeterPerSecond);
    writeBE(os, container->m_velocityZInMeterPerSecond);
    writeBE(os, container->m_velocityZSigmaInMeterPerSecond);
    writeBE(os, container->m_rollRateInRadPerSecond);
    writeBE(os, container->m_rollRateSigmaInRadPerSecond);
    writeBE(os, container->m_yawRateInRadPerSecond);
    writeBE(os, container->m_yawRateSigmaInRadPerSecond);
    writeBE(os, container->m_pitchRateInRadPerSecond);
    writeBE(os, container->m_pitchRateSigmaInRadPerSecond);
    writeBE(os, container->m_gpsStatus);
    writeBE(os, container->m_noOfSatellites);
    writeBE(os, container->m_gpsDilutionOfPrecisionX);
    writeBE(os, container->m_gpsDilutionOfPrecisionY);
    writeBE(os, container->m_gpsDilutionOfPrecisionZ);
    writeBE(os, container->m_gpsDilutionOfPrecisionVertical);
    writeBE(os, container->m_gpsDilutionOfPrecisionPosition);

    container->m_timestamp.serialize(os);

    writeBE(os, static_cast<uint8_t>(container->m_source));
    writeBE(os, static_cast<uint8_t>(container->m_insQuality));

    for (auto& r : container->m_reserved)
    {
        writeBE(os, r);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

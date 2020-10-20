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
//! \date Jan 30, 2019
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusExporter6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusSerializedSize6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301Exporter6301.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::DeviceStatus;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_DeviceStatus6301>::getSerializedSize(const DataContainerBase& c) const
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

    return DeviceStatusSerializedSize6301::getSerializedSize(*container);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_DeviceStatus6301>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    if (!serialize(os, container->m_serialNumberOfScanner))
    {
        return false;
    }
    writeLE(os, static_cast<uint8_t>(container->m_scannerType));
    writeLE(os, static_cast<uint8_t>(0)); // reserved
    if (!serialize(os, container->m_fpgaVersion))
    {
        return false;
    }
    if (!serialize(os, container->m_dspVersion))
    {
        return false;
    }
    if (!serialize(os, container->m_hostVersion))
    {
        return false;
    }

    writeLE(os, container->m_fpgaOperationRegister);
    writeLE(os, static_cast<uint16_t>(0)); // reserved

    writeLE(os,
            container->m_sensorTemperatureApd0 - 273.0F); // TODO: use unit conversion map (Kelvin to degree Celsius).
    writeLE(os, container->m_scanFrequency);
    writeLE(os, container->m_apdTableBiasVoltage);
    for (const float apdVoltage : container->m_adaptiveApdVoltageArray)
    {
        writeLE(os, apdVoltage);
    }
    writeLE(os, container->m_minApdVoltageOffset);
    writeLE(os, container->m_maxApdVoltageOffset);

    writeLE(os, static_cast<uint16_t>(0)); // reserved
    writeLE(os, static_cast<uint16_t>(0)); // reserved

    writeLE(os, container->m_noiseMeasurementThreshold);
    writeLE(os, container->m_referenceNoise);
    for (const uint16_t actualNoise : container->m_actualNoiseArray)
    {
        writeLE(os, actualNoise);
    }

    for (unsigned int r = 0; r < DeviceStatus6301::nbOfReservedA; ++r)
    {
        writeLE(os, static_cast<uint16_t>(0));
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_DeviceStatus6301>::serialize(std::ostream& os, const SerialNumber& sn)
{
    // same as 6301
    return DeviceStatus6301Exporter6301::serialize(os, sn);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_DeviceStatus6301>::serialize(std::ostream& os, const Version448& version)
{
    // same as 6301
    return DeviceStatus6301Exporter6301::serialize(os, version);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

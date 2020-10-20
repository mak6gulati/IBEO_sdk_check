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

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusExporter6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusSerializedSize6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303Exporter6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/AdaptiveApdVoltageAndNoiseInfoIn6303.hpp>

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

//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_DeviceStatus6303>::getSerializedSize(const DataContainerBase& c) const
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

    return DeviceStatusSerializedSize6303::getSerializedSize(*container);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_DeviceStatus6303>::serialize(std::ostream& os, const DataContainerBase& c) const
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

    // Create a sepcial device status 6303 from this data container.
    DeviceStatus6303 deviceStatus6303;
    deviceStatus6303.serialNumberOfScanner = container->m_serialNumberOfScanner;
    deviceStatus6303.scannerType           = static_cast<uint8_t>(container->m_scannerType);
    deviceStatus6303.deviceId              = container->m_deviceId;
    deviceStatus6303.fpgaVersion           = container->m_fpgaVersion;
    deviceStatus6303.hostVersion           = container->m_hostVersion;

    deviceStatus6303.fpgaOperationRegister = container->m_fpgaOperationRegister;
    deviceStatus6303.fpgaStatusRegister    = container->m_fpgaStatusRegister;

    deviceStatus6303.sensorTemperatureApd0
        = container->m_sensorTemperatureApd0 - 273.0F; // TODO: use unit conversion map (Kelvin to degree Celsius).
    deviceStatus6303.sensorTemperatureApd1
        = container->m_sensorTemperatureApd1 - 273.0F; // TODO: use unit conversion map (Kelvin to degree Celsius).
    deviceStatus6303.scanPeriod          = static_cast<uint32_t>(roundf(1.0E6F / container->m_scanFrequency));
    deviceStatus6303.minApdVoltageOffset = container->m_minApdVoltageOffset;
    deviceStatus6303.maxApdVoltageOffset = container->m_maxApdVoltageOffset;
    deviceStatus6303.referenceNoise      = container->m_referenceNoise;
    deviceStatus6303.noiseMeasurementThreshold
        = static_cast<uint32_t>(roundf(container->m_noiseMeasurementThreshold * 1000.0F));

    // Store APD bias voltage as variable content.
    deviceStatus6303.addContent(DeviceStatus6303::ContentId::ApdVoltageTable,
                                DeviceStatus6303::ElementType::FLOAT32,
                                sizeof(float),
                                1,
                                &container->m_apdTableBiasVoltage);

    {
        // Store adaptive voltage array and noise array as variable content.
        AdaptiveApdVoltageAndNoiseInfoIn6303 voltageAndNoiseInfoArray;
        std::size_t count = container->m_adaptiveApdVoltageArray.size();
        if (count > voltageAndNoiseInfoArray.getSectors().size())
        {
            count = voltageAndNoiseInfoArray.getSectors().size();
        }
        for (std::size_t i = 0; i < count; ++i)
        {
            voltageAndNoiseInfoArray.getSectors().at(i).setAdaptiveApdVoltage(
                container->m_adaptiveApdVoltageArray.at(i));
            voltageAndNoiseInfoArray.getSectors().at(i).setNoise(container->m_actualNoiseArray.at(i));
        }

        deviceStatus6303.addContent(voltageAndNoiseInfoArray);
    }

    // Use special importer to write device status 6303.
    DeviceStatus6303Exporter6303 exporter6303;
    return exporter6303.serialize(os, deviceStatus6303);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_DeviceStatus6303>::serialize(std::ostream& os, const SerialNumber& sn)
{
    // same as 6303
    return DeviceStatus6303Exporter6303::serialize(os, sn);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_DeviceStatus6303>::serialize(std::ostream& os, const Version448& version)
{
    // same as 6301
    return DeviceStatus6303Exporter6303::serialize(os, version);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

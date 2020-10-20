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

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusImporter6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusSerializedSize6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303Importer6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/AdaptiveApdVoltageAndNoiseInfoIn6303.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::DeviceStatus;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_DeviceStatus6303>;
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
class IbeoScala;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
            registeredImporterInitial)));

//==============================================================================

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_DeviceStatus6303>::getSerializedSize(const DataContainerBase& c) const
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

bool Importer<C, DataTypeId::DataType_DeviceStatus6303>::deserialize(std::istream& is,
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

    // Use special importer to read device status 6303.
    DeviceStatus6303Importer6303 importer6303;
    DeviceStatus6303 deviceStatus6303;
    if (!importer6303.deserialize(is, deviceStatus6303, dh))
    {
        // Import failed.
        return false;
    }

    // Copy members to general device status.
    container->m_serialNumberOfScanner = deviceStatus6303.serialNumberOfScanner;
    container->m_scannerType           = static_cast<ScannerType>(deviceStatus6303.scannerType);
    container->m_deviceId              = deviceStatus6303.deviceId;
    container->m_fpgaVersion           = deviceStatus6303.fpgaVersion;
    container->m_hostVersion           = deviceStatus6303.hostVersion;

    container->m_fpgaOperationRegister = deviceStatus6303.fpgaOperationRegister;
    container->m_fpgaStatusRegister    = deviceStatus6303.fpgaStatusRegister;

    container->m_sensorTemperatureApd0
        = deviceStatus6303.sensorTemperatureApd0 + 273.0F; // TODO: use unit conversion map (degree Celsius to Kelvin).
    container->m_sensorTemperatureApd1
        = deviceStatus6303.sensorTemperatureApd1 + 273.0F; // TODO: use unit conversion map (degree Celsius to Kelvin).
    container->m_scanFrequency             = 1.0E6F / static_cast<float>(deviceStatus6303.scanPeriod);
    container->m_minApdVoltageOffset       = deviceStatus6303.minApdVoltageOffset;
    container->m_maxApdVoltageOffset       = deviceStatus6303.maxApdVoltageOffset;
    container->m_referenceNoise            = deviceStatus6303.referenceNoise;
    container->m_noiseMeasurementThreshold = static_cast<float>(deviceStatus6303.noiseMeasurementThreshold) / 1000.0F;

    {
        // Get APD bias voltage from variable content.
        const float* value;
        int nbOfBytes = deviceStatus6303.getContent(DeviceStatus6303::ContentId::ApdVoltageTable, value);
        if (nbOfBytes == static_cast<int>(sizeof(float)))
        {
            container->m_apdTableBiasVoltage = *value;
        }
    }

    {
        // Get adaptive voltage array and noise array from variable content.
        AdaptiveApdVoltageAndNoiseInfoIn6303 voltageAndNoiseInfoArray;
        if (deviceStatus6303.getContent(DeviceStatus6303::ContentId::AdaptiveApdVoltageNoiseArray,
                                        voltageAndNoiseInfoArray))
        {
            std::size_t count = voltageAndNoiseInfoArray.getSectors().size();
            if (count > container->m_adaptiveApdVoltageArray.size())
            {
                count = container->m_adaptiveApdVoltageArray.size();
            }

            for (std::size_t i = 0; i < count; ++i)
            {
                container->m_adaptiveApdVoltageArray.at(i)
                    = voltageAndNoiseInfoArray.getSectors().at(i).getAdaptiveApdVoltage();
                container->m_actualNoiseArray.at(i) = voltageAndNoiseInfoArray.getSectors().at(i).getNoise();
            }
        }
    }

    return true;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_DeviceStatus6303>::deserialize(std::istream& is, SerialNumber& sn)
{
    // same as 6303
    return DeviceStatus6303Importer6303::deserialize(is, sn);
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_DeviceStatus6303>::deserialize(std::istream& is, Version448& version)
{
    // same as 6303
    return DeviceStatus6303Importer6303::deserialize(is, version);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

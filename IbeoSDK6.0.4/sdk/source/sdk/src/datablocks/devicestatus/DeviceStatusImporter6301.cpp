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

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusImporter6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusSerializedSize6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301Importer6301.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/scan/ScannerInfo.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::DeviceStatus;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_DeviceStatus6301>;
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

std::streamsize Importer<C, DataTypeId::DataType_DeviceStatus6301>::getSerializedSize(const DataContainerBase& c) const
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

bool Importer<C, DataTypeId::DataType_DeviceStatus6301>::deserialize(std::istream& is,
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

    if (!deserialize(is, container->m_serialNumberOfScanner))
    {
        return false;
    }

    {
        uint8_t st;
        readLE(is, st);
        container->m_scannerType = ScannerType(st);
    }

    {
        uint8_t reserved;
        readLE(is, reserved);
    }

    if (!deserialize(is, container->m_fpgaVersion))
    {
        return false;
    }
    if (!deserialize(is, container->m_dspVersion))
    {
        return false;
    }
    if (!deserialize(is, container->m_hostVersion))
    {
        return false;
    }

    readLE(is, container->m_fpgaOperationRegister);

    {
        uint16_t reserved;
        ibeo::common::sdk::readLE(is, reserved);
    }

    {
        float temperatureInCelsius;
        readLE(is, temperatureInCelsius);
        container->m_sensorTemperatureApd0
            = temperatureInCelsius + 273.0F; // TODO: use unit conversion map (degree Celsius to Kelvin).
    }
    readLE(is, container->m_scanFrequency);
    readLE(is, container->m_apdTableBiasVoltage);
    for (float& adaptiveVoltage : container->m_adaptiveApdVoltageArray)
    {
        readLE(is, adaptiveVoltage);
    }
    readLE(is, container->m_minApdVoltageOffset);
    readLE(is, container->m_maxApdVoltageOffset);

    {
        uint16_t reserved;
        readLE(is, reserved);
        readLE(is, reserved);
    }

    readLE(is, container->m_noiseMeasurementThreshold);
    readLE(is, container->m_referenceNoise);
    for (uint16_t& actualNoise : container->m_actualNoiseArray)
    {
        readLE(is, actualNoise);
    }

    for (uint8_t r = 0; r < DeviceStatus6301::nbOfReservedA; ++r)
    {
        uint16_t reserved;
        readLE(is, reserved);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_DeviceStatus6301>::deserialize(std::istream& is, SerialNumber& sn)
{
    // same as 6301
    return DeviceStatus6301Importer6301::deserialize(is, sn);
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_DeviceStatus6301>::deserialize(std::istream& is, Version448& version)
{
    // same as 6301
    return DeviceStatus6301Importer6301::deserialize(is, version);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

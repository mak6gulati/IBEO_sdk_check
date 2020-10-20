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

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusSerializedSize6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301SerializedSize6301.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize DeviceStatusSerializedSize6301::getSerializedSize(const DeviceStatus& ds)
{
    return getSerializedSize(ds.getSerialNumberOfScanner()) // serialNumberOfScanner
           + std::streamsize(sizeof(uint8_t)) // scannerType
           + std::streamsize(sizeof(uint8_t)) // reserved0
           + getSerializedSize(ds.getFpgaVersion()) // fpgaVersion
           + getSerializedSize(ds.getDspVersion()) // dspVersion
           + getSerializedSize(ds.getHostVersion()) // hostVersion
           + std::streamsize(sizeof(uint16_t)) // fpgaModusRegister
           + std::streamsize(sizeof(uint16_t)) // reserved1
           + std::streamsize(sizeof(float)) // sensorTemperature
           + std::streamsize(sizeof(float)) // frequency
           + std::streamsize(sizeof(float)) // apdTableVoltage
           + std::streamsize(DeviceStatus::nbOfApdSectors * sizeof(float)) // adaptiveApdVoltage
           + std::streamsize(sizeof(float)) // minApdVoltageOffset
           + std::streamsize(sizeof(float)) // maxApdVoltageOffset
           + std::streamsize(sizeof(uint16_t)) // reserved2
           + std::streamsize(sizeof(uint16_t)) // reserved3
           + std::streamsize(sizeof(float)) // noiseMeasurementThreshold
           + std::streamsize(sizeof(uint16_t)) // referenceNoise
           + std::streamsize(DeviceStatus::nbOfApdSectors * sizeof(uint16_t)) // actualNoise
           + std::streamsize(DeviceStatus6301::nbOfReservedA * sizeof(uint16_t)) // reservedA
        ;
}

//==============================================================================

std::streamsize DeviceStatusSerializedSize6301::getSerializedSize(const SerialNumber& sn)
{
    // same as 6301
    return DeviceStatus6301SerializedSize6301::getSerializedSize(sn);
}

//==============================================================================

std::streamsize DeviceStatusSerializedSize6301::getSerializedSize(const Version448& version)
{
    // same as 6301
    return DeviceStatus6301SerializedSize6301::getSerializedSize(version);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

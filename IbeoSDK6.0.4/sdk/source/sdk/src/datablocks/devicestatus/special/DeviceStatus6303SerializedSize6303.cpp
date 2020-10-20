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

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303SerializedSize6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301SerializedSize6301.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize DeviceStatus6303SerializedSize6303::getSerializedSize(const DeviceStatus6303& ds)
{
    std::streamsize sz = getSerializedSize(ds.getSerialNumberOfScanner()) // serialNumberOfScanner
                         + std::streamsize(sizeof(uint8_t)) // scannerType
                         + std::streamsize(sizeof(uint8_t)) // deviceId
                         + getSerializedSize(ds.getFpgaVersion()) // fpgaVersion
                         + getSerializedSize(ds.getHostVersion()) // hostVersion
                         + std::streamsize(sizeof(uint16_t)) // fpgaStatusRegister
                         + std::streamsize(sizeof(uint16_t)) // fpgaOperationRegister
                         + std::streamsize(sizeof(uint32_t)) // scanPeriod
                         + std::streamsize(sizeof(float)) // sensorTemperatureApd0
                         + std::streamsize(sizeof(float)) // sensorTemperatureApd1
                         + std::streamsize(sizeof(float)) // minApdVoltageOffset
                         + std::streamsize(sizeof(float)) // maxApdVoltageOffset
                         + std::streamsize(sizeof(uint32_t)) // noiseMeasurementThreshold
                         + std::streamsize(sizeof(uint16_t)) // referenceNoise
                         + std::streamsize(sizeof(uint16_t)) // nbOfContentsEntries
        ;

    for (const DeviceStatus6303::ContentDescr& contDescr : ds.getContentDescrs())
    {
        sz += contDescr.getSerializedSize();
    }
    return sz;
}

//==============================================================================

std::streamsize DeviceStatus6303SerializedSize6303::getSerializedSize(const SerialNumberIn6303& sn)
{
    // same as 6301
    return DeviceStatus6301SerializedSize6301::getSerializedSize(sn);
}

//==============================================================================

std::streamsize DeviceStatus6303SerializedSize6303::getSerializedSize(const Version448In6303& version)
{
    // same as 6301
    return DeviceStatus6301SerializedSize6301::getSerializedSize(version);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

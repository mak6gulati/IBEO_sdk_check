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

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatusSerializedSize6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303SerializedSize6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/AdaptiveApdVoltageAndNoiseInfoIn6303.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize DeviceStatusSerializedSize6303::getSerializedSize(const DeviceStatus& ds)
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

    // The exporter uses two variable content fields in the data type 6303: ApdVoltageTable and
    // AdaptiveApdVoltageNoiseArray.

    // Variable content field: ApdVoltageTable (single float element)
    sz += std::streamsize(sizeof(uint16_t)) // contentId
          + std::streamsize(sizeof(uint8_t)) // elementType
          + std::streamsize(sizeof(uint8_t)) // nbOfByte
          + std::streamsize(sizeof(float)) // variable content data
        ;

    // Variable content field: AdaptiveApdVoltageNoiseArray (user defined struct)
    sz += std::streamsize(sizeof(uint16_t)) // contentId
          + std::streamsize(sizeof(uint8_t)) // elementType
          + std::streamsize(sizeof(uint8_t)) // nbOfByte
          + AdaptiveApdVoltageAndNoiseInfoIn6303::getSerializedSizeStatic() // variable content data
        ;

    return sz;
}

//==============================================================================

std::streamsize DeviceStatusSerializedSize6303::getSerializedSize(const SerialNumber& sn)
{
    // same as 6303
    return DeviceStatus6303SerializedSize6303::getSerializedSize(sn);
}

//==============================================================================

std::streamsize DeviceStatusSerializedSize6303::getSerializedSize(const Version448& version)
{
    // same as 6303
    return DeviceStatus6303SerializedSize6303::getSerializedSize(version);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

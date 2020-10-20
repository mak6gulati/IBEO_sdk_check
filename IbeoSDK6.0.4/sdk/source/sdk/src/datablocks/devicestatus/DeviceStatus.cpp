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
//! \date Jan 29, 2019
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatus.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

DeviceStatus::DeviceStatus() : DataContainerBase()
{
    m_adaptiveApdVoltageArray.fill(0.0F);
    m_actualNoiseArray.fill(0);
}

//==============================================================================

bool operator==(const DeviceStatus& lhs, const DeviceStatus& rhs)
{
    // Temperatures might have been converted between degrees Celsius and Kelvin. They are not float-equal but
    // fuzzy-float-equal up to 3 decimal digits.
    // Noise measurement threshold might have been converted between mV and V. They are not float-equal but
    // fuzzy-float-equal up to 3 decimal digits.

    return (lhs.getSerialNumberOfScanner() == rhs.getSerialNumberOfScanner())
           && (lhs.getScannerType() == rhs.getScannerType()) && (lhs.getFpgaVersion() == rhs.getFpgaVersion())
           && (lhs.getDspVersion() == rhs.getDspVersion()) && (lhs.getHostVersion() == rhs.getHostVersion())
           && (lhs.getFpgaOperationRegister() == rhs.getFpgaOperationRegister())
           && (lhs.getFpgaStatusRegister() == rhs.getFpgaStatusRegister())
           && fuzzyFloatEqualT<3>(lhs.getSensorTemperatureApd0(), rhs.getSensorTemperatureApd0())
           && fuzzyFloatEqualT<3>(lhs.getSensorTemperatureApd1(), rhs.getSensorTemperatureApd1())
           && floatEqual(lhs.getScanFrequency(), rhs.getScanFrequency())
           && floatEqual(lhs.getApdTableBiasVoltage(), rhs.getApdTableBiasVoltage())
           && std::equal(lhs.getAdaptiveApdVoltageArray().begin(),
                         lhs.getAdaptiveApdVoltageArray().end(),
                         rhs.getAdaptiveApdVoltageArray().begin(),
                         [](const float lv, const float rv) { return floatEqual(lv, rv); })
           && floatEqual(lhs.getMinApdVoltageOffset(), rhs.getMinApdVoltageOffset())
           && floatEqual(lhs.getMaxApdVoltageOffset(), rhs.getMaxApdVoltageOffset())
           && fuzzyFloatEqualT<3>(lhs.getNoiseMeasurementThreshold(), rhs.getNoiseMeasurementThreshold())
           && (lhs.getReferenceNoise() == rhs.getReferenceNoise())
           && (lhs.getActualNoiseArray() == rhs.getActualNoiseArray());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Jan 19, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

DeviceStatus6301::DeviceStatus6301()
  : SpecializedDataContainer(), m_adaptiveApdVoltage{}, m_actualNoise{}, m_reservedA{}
{
    m_adaptiveApdVoltage.fill(0.0F);
    m_actualNoise.fill(0);
    m_reservedA.fill(0);
}

//==============================================================================

bool operator==(const DeviceStatus6301& lhs, const DeviceStatus6301& rhs)
{
    return (lhs.getSerialNumber() == rhs.getSerialNumber()) && (lhs.getScannerType() == rhs.getScannerType())
           && (lhs.getReserved0() == rhs.getReserved0())

           && (lhs.getFpgaVersion() == rhs.getFpgaVersion()) && (lhs.getDspVersion() == rhs.getDspVersion())
           && (lhs.getHostVersion() == rhs.getHostVersion())

           && (lhs.getFpgaModusRegister() == rhs.getFpgaModusRegister()) && (lhs.getReserved1() == rhs.getReserved1())
           && fuzzyFloatEqualT<3>(lhs.getSensorTemperature(), rhs.getSensorTemperature())
           && floatEqual(lhs.getFrequency(), rhs.getFrequency())
           && floatEqual(lhs.getApdTableVoltage(), rhs.getApdTableVoltage())

           && std::equal(lhs.getAdaptiveApdVoltageArray().begin(),
                         lhs.getAdaptiveApdVoltageArray().end(),
                         lhs.getAdaptiveApdVoltageArray().begin(),
                         [](const float lv, const float rv) { return floatEqual(lv, rv); })

           && floatEqual(lhs.getMinApdVoltageOffset(), rhs.getMinApdVoltageOffset())
           && floatEqual(lhs.getMaxApdVoltageOffset(), rhs.getMaxApdVoltageOffset())

           && (lhs.getReserved2() == rhs.getReserved2()) && (lhs.getReserved3() == rhs.getReserved3())

           && fuzzyFloatEqualT<3>(lhs.getNoiseMeasurementThreshold(), rhs.getNoiseMeasurementThreshold())
           && (lhs.getReferenceNoise() == rhs.getReferenceNoise())
           && (lhs.getActualNoiseArray() == rhs.getActualNoiseArray())
           && (lhs.getReservedAArray() == rhs.getReservedAArray());
}

//==============================================================================

bool operator!=(const DeviceStatus6301& lhs, const DeviceStatus6301& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

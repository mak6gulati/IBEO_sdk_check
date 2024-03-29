//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 16, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringDeviceStatus6701.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::SystemMonitoringDeviceStatus6701,
               DataTypeId::DataType_SystemMonitoringDeviceStatus6701>
  : public TypedExporter<ibeo::common::sdk::SystemMonitoringDeviceStatus6701,
                         DataTypeId::DataType_SystemMonitoringDeviceStatus6701>
{
public:
    constexpr static const std::streamsize serializedSize{std::streamsize(
        sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint64_t))};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // SystemMonitoringDeviceStatus6701Exporter6701

//==============================================================================

using SystemMonitoringDeviceStatus6701Exporter6701 = Exporter<ibeo::common::sdk::SystemMonitoringDeviceStatus6701,
                                                              DataTypeId::DataType_SystemMonitoringDeviceStatus6701>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

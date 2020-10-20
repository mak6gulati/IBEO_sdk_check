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
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringSystemStatus6705.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::SystemMonitoringSystemStatus6705,
               DataTypeId::DataType_SystemMonitoringSystemStatus6705>
  : public TypedExporter<ibeo::common::sdk::SystemMonitoringSystemStatus6705,
                         DataTypeId::DataType_SystemMonitoringSystemStatus6705>
{
public:
    static constexpr const std::streamsize serializedSize{
        std::streamsize(sizeof(uint64_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint8_t)
                        + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint8_t))};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // SystemMonitoringSystemStatus6705Exporter6705

//==============================================================================

using SystemMonitoringSystemStatus6705Exporter6705 = Exporter<ibeo::common::sdk::SystemMonitoringSystemStatus6705,
                                                              DataTypeId::DataType_SystemMonitoringSystemStatus6705>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

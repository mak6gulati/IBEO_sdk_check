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
#include <ibeo/common/sdk/datablocks/systemmonitoring/SystemMonitoringCanStatus6700.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<SystemMonitoringCanStatus6700, DataTypeId::DataType_SystemMonitoringCanStatus6700>
  : public TypedExporter<SystemMonitoringCanStatus6700, DataTypeId::DataType_SystemMonitoringCanStatus6700>
{
public:
    constexpr static const std::streamsize serializedSize{static_cast<std::streamsize>(
        sizeof(uint8_t) + sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint64_t))};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase&) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& importContainer) const override;
}; // SystemMonitoringCanStatus6700Exporter6700

//==============================================================================

using SystemMonitoringCanStatus6700Exporter6700
    = Exporter<SystemMonitoringCanStatus6700, DataTypeId::DataType_SystemMonitoringCanStatus6700>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

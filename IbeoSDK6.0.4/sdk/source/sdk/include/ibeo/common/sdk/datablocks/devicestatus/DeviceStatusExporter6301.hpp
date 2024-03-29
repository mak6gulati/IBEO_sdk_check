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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatus.hpp>
#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<DeviceStatus, DataTypeId::DataType_DeviceStatus6301>
  : public TypedExporter<DeviceStatus, DataTypeId::DataType_DeviceStatus6301>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;

private:
    static bool serialize(std::ostream& os, const SerialNumber& sn);
    static bool serialize(std::ostream& os, const Version448& version);
}; // DeviceStatusExporter6301

//==============================================================================

using DeviceStatusExporter6301 = Exporter<DeviceStatus, DataTypeId::DataType_DeviceStatus6301>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

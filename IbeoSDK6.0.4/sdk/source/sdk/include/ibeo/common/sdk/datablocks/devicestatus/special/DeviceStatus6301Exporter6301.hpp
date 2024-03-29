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
//!\date Jan 22, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301.hpp>
#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<DeviceStatus6301, DataTypeId::DataType_DeviceStatus6301>
  : public TypedExporter<DeviceStatus6301, DataTypeId::DataType_DeviceStatus6301>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;

public:
    static bool serialize(std::ostream& os, const SerialNumberIn6301& sn);
    static bool serialize(std::ostream& os, const Version448In6301& version);
}; // DeviceStatus6301Exporter6301

//==============================================================================

using DeviceStatus6301Exporter6301 = Exporter<DeviceStatus6301, DataTypeId::DataType_DeviceStatus6301>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

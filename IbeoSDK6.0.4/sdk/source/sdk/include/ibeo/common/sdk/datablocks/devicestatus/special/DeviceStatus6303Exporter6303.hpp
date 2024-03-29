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

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303.hpp>
#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<DeviceStatus6303, DataTypeId::DataType_DeviceStatus6303>
  : public TypedExporter<DeviceStatus6303, DataTypeId::DataType_DeviceStatus6303>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& importContainer) const override;

public:
    static bool serialize(std::ostream& os, const SerialNumberIn6303& sn);
    static bool serialize(std::ostream& os, const Version448In6303& version);
}; // DeviceStatus6303Exporter6303

//==============================================================================

using DeviceStatus6303Exporter6303 = Exporter<DeviceStatus6303, DataTypeId::DataType_DeviceStatus6303>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Sep 1, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::VehicleState, DataTypeId::DataType_VehicleStateBasic2808>
  : public TypedExporter<ibeo::common::sdk::VehicleState, DataTypeId::DataType_VehicleStateBasic2808>
{
public:
    static constexpr const std::streamsize serializedSize{204};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& outStream, const DataContainerBase& c) const override;
}; // VehicleStateExporter2808

//==============================================================================

using VehicleStateExporter2808 = Exporter<VehicleState, DataTypeId::DataType_VehicleStateBasic2808>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

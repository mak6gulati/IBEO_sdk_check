
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
//!\date Jan 19, 2018
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2805.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<VehicleState2805, DataTypeId::DataType_VehicleStateBasic2805>
  : public TypedExporter<VehicleState2805, DataTypeId::DataType_VehicleStateBasic2805>
{
public:
    constexpr static const std::streamsize serializedSize{46};

public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // VehicleState2805Exporter2805

//==============================================================================

using VehicleState2805Exporter2805
    = Exporter<ibeo::common::sdk::VehicleState2805, DataTypeId::DataType_VehicleStateBasic2805>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Jan 15, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84_2604.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::PositionWgs84_2604, DataTypeId::DataType_PositionWgs84_2604>
  : public TypedExporter<ibeo::common::sdk::PositionWgs84_2604, DataTypeId::DataType_PositionWgs84_2604>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // PositionWgs84_2604Exporter2604

//==============================================================================

using PositionWgs84_2604Exporter2604
    = Exporter<ibeo::common::sdk::PositionWgs84_2604, DataTypeId::DataType_PositionWgs84_2604>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

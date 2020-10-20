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
//!\date March 14, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9010.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::TimeRelationsList9010, DataTypeId::DataType_TimeRelationsList9010>
  : public TypedExporter<ibeo::common::sdk::TimeRelationsList9010, DataTypeId::DataType_TimeRelationsList9010>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // TimeRelationsList9010Exporter9010

//==============================================================================

using TimeRelationsList9010Exporter9010
    = Exporter<ibeo::common::sdk::TimeRelationsList9010, DataTypeId::DataType_TimeRelationsList9010>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

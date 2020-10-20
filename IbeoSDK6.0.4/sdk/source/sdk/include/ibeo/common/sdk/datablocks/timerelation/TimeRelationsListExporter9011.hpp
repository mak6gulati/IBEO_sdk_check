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
//!\date Apr 5, 2018
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/timerelation/TimeRelationsList.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::TimeRelationsList, DataTypeId::DataType_TimeRelationsList9011>
  : public TypedExporter<ibeo::common::sdk::TimeRelationsList, DataTypeId::DataType_TimeRelationsList9011>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    bool serialize(std::ostream& outStream, const DataContainerBase& c) const override;
}; // VehicleStateExporter2805

//==============================================================================

using TimeRelationsListExporter9011 = Exporter<TimeRelationsList, DataTypeId::DataType_TimeRelationsList9011>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

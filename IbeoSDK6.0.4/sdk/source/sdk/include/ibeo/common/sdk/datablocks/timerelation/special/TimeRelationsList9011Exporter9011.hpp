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
//!\date March 15, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>

#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9011.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<TimeRelationsList9011, DataTypeId::DataType_TimeRelationsList9011>
  : public TypedExporter<TimeRelationsList9011, DataTypeId::DataType_TimeRelationsList9011>
{
public:
    std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // TimeRelationsList9011Exporter9011

//==============================================================================

using TimeRelationsList9011Exporter9011 = Exporter<TimeRelationsList9011, DataTypeId::DataType_TimeRelationsList9011>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Mar 14, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageWarning6410.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessage64x0Exporter64x0Base.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::LogMessageWarning6410, DataTypeId::DataType_LogWarning6410>
  : public TypedExporter<ibeo::common::sdk::LogMessageWarning6410, DataTypeId::DataType_LogWarning6410>,
    protected LogMessage64x0Exporter64x0Base<LogMessageWarning6410>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // LogMessageWarning6410Exporter6410

//==============================================================================

using LogMessageWarning6410Exporter6410 = Exporter<LogMessageWarning6410, DataTypeId::DataType_LogWarning6410>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

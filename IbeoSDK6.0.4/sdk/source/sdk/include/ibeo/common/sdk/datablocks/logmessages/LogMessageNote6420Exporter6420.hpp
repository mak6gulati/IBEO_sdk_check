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
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageNote6420.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessage64x0Exporter64x0Base.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::LogMessageNote6420, DataTypeId::DataType_LogNote6420>
  : public TypedExporter<ibeo::common::sdk::LogMessageNote6420, DataTypeId::DataType_LogNote6420>,
    protected LogMessage64x0Exporter64x0Base<LogMessageNote6420>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // LogMessageNote6420Exporter6420

//==============================================================================

using LogMessageNote6420Exporter6420 = Exporter<LogMessageNote6420, DataTypeId::DataType_LogNote6420>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageError6400.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessage64x0Exporter64x0Base.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<ibeo::common::sdk::LogMessageError6400, DataTypeId::DataType_LogError6400>
  : public TypedExporter<ibeo::common::sdk::LogMessageError6400, DataTypeId::DataType_LogError6400>,
    protected LogMessage64x0Exporter64x0Base<LogMessageError6400>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // LogMessageError6400Exporter6400

//==============================================================================

using LogMessageError6400Exporter6400 = Exporter<LogMessageError6400, DataTypeId::DataType_LogError6400>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

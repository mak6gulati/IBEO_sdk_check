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
#include <ibeo/common/sdk/datablocks/logmessages/LogMessageDebug6430.hpp>
#include <ibeo/common/sdk/datablocks/logmessages/LogMessage64x0Exporter64x0Base.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class Exporter<LogMessageDebug6430, DataTypeId::DataType_LogDebug6430>
  : public TypedExporter<LogMessageDebug6430, DataTypeId::DataType_LogDebug6430>,
    protected LogMessage64x0Exporter64x0Base<LogMessageDebug6430>
{
public:
    virtual std::streamsize getSerializedSize(const DataContainerBase& c) const override;

public:
    virtual bool serialize(std::ostream& os, const DataContainerBase& c) const override;
}; // LogMessageDebug6430Exporter6430

//==============================================================================

using LogMessageDebug6430Exporter6430 = Exporter<LogMessageDebug6430, DataTypeId::DataType_LogDebug6430>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

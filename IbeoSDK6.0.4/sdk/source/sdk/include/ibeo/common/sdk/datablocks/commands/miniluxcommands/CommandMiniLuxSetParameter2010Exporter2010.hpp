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
//!\date Mar 1, 2018
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/SpecialExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/CommandMiniLuxSetParameterC.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class SpecialExporter<CommandMiniLuxSetParameterC> : public SpecialExporterBase<CommandCBase>
{
public:
    static constexpr int commandSize{10};

public:
    SpecialExporter() : SpecialExporterBase<CommandCBase>() {}

public:
    //========================================
    //!\brief Get the DataType of exporter/importer.
    //!\return The DataTypeId of the data this exporter/importer
    //!        can handle.
    //----------------------------------------
    virtual CommandCBase::KeyType getSpecialType() const override { return CommandMiniLuxSetParameterC::key; }

public:
    //========================================
    //!\brief Get serializable size of data from exporter/importer.
    //!\return Number of Bytes used by data type.
    //----------------------------------------
    virtual std::streamsize getSerializedSize(const CommandCBase& c) const override;

    virtual bool serialize(std::ostream& outStream, const CommandCBase& c) const override;
}; // CommandMiniLuxSetParameter2010Exporter2010

//==============================================================================

using CommandMiniLuxSetParameter2010Exporter2010 = SpecialExporter<CommandMiniLuxSetParameterC>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Feb 28, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/SpecialExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/commands/ecucommands/CommandEcuAppBaseStatusC.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class SpecialExporter<CommandEcuAppBaseStatusC> : public SpecialExporterBase<CommandCBase>
{
public:
    static constexpr int commandSize{4};

public:
    SpecialExporter() : SpecialExporterBase<CommandCBase>() {}
    virtual ~SpecialExporter() {}

public:
    //========================================
    //!\brief Get the DataType of exporter/importer.
    //!\return The DataTypeId of the data this exporter/importer
    //!        can handle.
    //----------------------------------------
    virtual CommandCBase::KeyType getSpecialType() const override { return CommandEcuAppBaseStatusC::key; }

public:
    //========================================
    //!\brief Get serializable size of data from exporter/importer.
    //!\return Number of Bytes used by data type.
    //----------------------------------------
    virtual std::streamsize getSerializedSize(const CommandCBase& c) const override;

    virtual bool serialize(std::ostream& outStream, const CommandCBase& c) const override;
}; // CommandEcuAppBaseStatus2010Exporter2010

//==============================================================================

using CommandEcuAppBaseStatus2010Exporter2010 = SpecialExporter<CommandEcuAppBaseStatusC>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

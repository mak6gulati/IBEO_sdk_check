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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/SpecialExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/commands/ecucommands/CommandEcuSetFilterC.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class SpecialExporter<CommandEcuSetFilterC> : public SpecialExporterBase<CommandCBase>
{
public:
    static constexpr uint8_t commandBaseSize{4};

public:
    SpecialExporter() : SpecialExporterBase<CommandCBase>() {}
    virtual ~SpecialExporter() {}

public:
    //========================================
    //!\brief Get the DataType of exporter/importer.
    //!\return The DataTypeId of the data this exporter/importer
    //!        can handle.
    //----------------------------------------
    virtual CommandCBase::KeyType getSpecialType() const override { return CommandEcuSetFilterC::key; }

public:
    //========================================
    //!\brief Get serializable size of data from exporter/importer.
    //!\return Number of Bytes used by data type.
    //----------------------------------------
    virtual std::streamsize getSerializedSize(const CommandCBase& c) const override;

    virtual bool serialize(std::ostream& outStream, const CommandCBase& c) const override;
}; // CommandEcuSetFilter2010Exporter2010

//==============================================================================

using CommandEcuSetFilter2010Exporter2010 = SpecialExporter<CommandEcuSetFilterC>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

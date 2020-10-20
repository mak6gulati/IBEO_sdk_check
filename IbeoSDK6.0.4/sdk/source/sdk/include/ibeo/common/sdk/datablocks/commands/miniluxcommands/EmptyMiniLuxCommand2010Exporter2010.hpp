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

#include <ibeo/common/sdk/datablocks/commands/EmptyCommandExporter.hpp>
#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/CommandMiniLuxGetStatusC.hpp>
#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/CommandMiniLuxSaveConfigC.hpp>
#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/CommandMiniLuxResetC.hpp>
#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/CommandMiniLuxResetToDefaultParametersC.hpp>
#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/CommandMiniLuxStartMeasureC.hpp>
#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/CommandMiniLuxStopMeasureC.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class SpecialExporter<CommandMiniLuxGetStatusC> : public EmptyCommandExporter<CommandMiniLuxGetStatusC>
{
};
template<>
class SpecialExporter<CommandMiniLuxSaveConfigC> : public EmptyCommandExporter<CommandMiniLuxSaveConfigC>
{
};
template<>
class SpecialExporter<CommandMiniLuxResetC> : public EmptyCommandExporter<CommandMiniLuxResetC>
{
};
template<>
class SpecialExporter<CommandMiniLuxResetToDefaultParametersC>
  : public EmptyCommandExporter<CommandMiniLuxResetToDefaultParametersC>
{
};
template<>
class SpecialExporter<CommandMiniLuxStartMeasureC> : public EmptyCommandExporter<CommandMiniLuxStartMeasureC>
{
};
template<>
class SpecialExporter<CommandMiniLuxStopMeasureC> : public EmptyCommandExporter<CommandMiniLuxStopMeasureC>
{
};

//==============================================================================

using CommandMiniLuxGetStatus2010Exporter2010                = SpecialExporter<CommandMiniLuxGetStatusC>;
using CommandMiniLuxSaveConfig2010Exporter2010               = SpecialExporter<CommandMiniLuxSaveConfigC>;
using CommandMiniLuxReset2010Exporter2010                    = SpecialExporter<CommandMiniLuxResetC>;
using CommandMiniLuxResetToDefaultParameters2010Exporter2010 = SpecialExporter<CommandMiniLuxResetToDefaultParametersC>;
using CommandMiniLuxStartMeasure2010Exporter2010             = SpecialExporter<CommandMiniLuxStartMeasureC>;
using CommandMiniLuxStopMeasure2010Exporter2010              = SpecialExporter<CommandMiniLuxStopMeasureC>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

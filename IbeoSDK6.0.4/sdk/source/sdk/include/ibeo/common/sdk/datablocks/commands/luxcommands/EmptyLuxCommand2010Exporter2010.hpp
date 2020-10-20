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
#include <ibeo/common/sdk/datablocks/commands/luxcommands/CommandLuxGetStatusC.hpp>
#include <ibeo/common/sdk/datablocks/commands/luxcommands/CommandLuxSaveConfigC.hpp>
#include <ibeo/common/sdk/datablocks/commands/luxcommands/CommandLuxResetC.hpp>
#include <ibeo/common/sdk/datablocks/commands/luxcommands/CommandLuxResetToDefaultParametersC.hpp>
#include <ibeo/common/sdk/datablocks/commands/luxcommands/CommandLuxStartMeasureC.hpp>
#include <ibeo/common/sdk/datablocks/commands/luxcommands/CommandLuxStopMeasureC.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<>
class SpecialExporter<CommandLuxGetStatusC> : public EmptyCommandExporter<CommandLuxGetStatusC>
{
};
template<>
class SpecialExporter<CommandLuxSaveConfigC> : public EmptyCommandExporter<CommandLuxSaveConfigC>
{
};
template<>
class SpecialExporter<CommandLuxResetC> : public EmptyCommandExporter<CommandLuxResetC>
{
};
template<>
class SpecialExporter<CommandLuxResetToDefaultParametersC>
  : public EmptyCommandExporter<CommandLuxResetToDefaultParametersC>
{
};
template<>
class SpecialExporter<CommandLuxStartMeasureC> : public EmptyCommandExporter<CommandLuxStartMeasureC>
{
};
template<>
class SpecialExporter<CommandLuxStopMeasureC> : public EmptyCommandExporter<CommandLuxStopMeasureC>
{
};

//==============================================================================

using CommandLuxGetStatus2010Exporter2010                = SpecialExporter<CommandLuxGetStatusC>;
using CommandLuxSaveConfig2010Exporter2010               = SpecialExporter<CommandLuxSaveConfigC>;
using CommandLuxReset2010Exporter2010                    = SpecialExporter<CommandLuxResetC>;
using CommandLuxResetToDefaultParameters2010Exporter2010 = SpecialExporter<CommandLuxResetToDefaultParametersC>;
using CommandLuxStartMeasure2010Exporter2010             = SpecialExporter<CommandLuxStartMeasureC>;
using CommandLuxStopMeasure2010Exporter2010              = SpecialExporter<CommandLuxStopMeasureC>;

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

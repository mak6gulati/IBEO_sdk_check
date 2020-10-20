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
//!\date Feb 19, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/commands/Command2010.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================
//!\brief Base class for ECU commands
//!\date Feb 14, 2018
//------------------------------------------------------------------------------
class EcuCommandCBase : public CommandCBase
{
public:
    EcuCommandCBase(const CommandId commandId) : CommandCBase(commandId) {}
}; // EcuCommandCBase

//==============================================================================
//!\brief Template base class for ECU commands with given command id.
//!\date Feb 14, 2018
//!\tparam cId  Command id of the ECU command.
//------------------------------------------------------------------------------
template<CommandId::Id cId>
class EcuCommandC : public EcuCommandCBase
{
public:
    EcuCommandC() : EcuCommandCBase(cId) {}
}; // EcuCommandC<cId>

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

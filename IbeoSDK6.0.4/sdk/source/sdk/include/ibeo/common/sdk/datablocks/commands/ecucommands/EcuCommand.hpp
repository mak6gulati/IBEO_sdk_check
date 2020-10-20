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
//!\date Feb 14, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/commands/Command.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class EcuCommandReplyBase : public CommandReplyBase
{
public:
    EcuCommandReplyBase(const CommandId commandId) : CommandReplyBase(commandId) {}
}; // EcuCommandReplyBase

//==============================================================================

template<CommandId::Id cId>
class EcuCommandReply : public EcuCommandReplyBase
{
public:
    EcuCommandReply() : EcuCommandReplyBase(cId) {}
}; // EcuCommandReply<cId>

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

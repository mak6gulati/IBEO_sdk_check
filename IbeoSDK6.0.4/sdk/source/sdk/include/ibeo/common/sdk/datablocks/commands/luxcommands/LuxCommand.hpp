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

class LuxCommandReplyBase : public CommandReplyBase
{
public:
    LuxCommandReplyBase(const CommandId commandId) : CommandReplyBase(commandId) {}
}; // LuxCommandReplyBase

//==============================================================================

template<CommandId::Id cId>
class LuxCommandReply : public LuxCommandReplyBase
{
public:
    LuxCommandReply() : LuxCommandReplyBase(cId) {}
}; // LuxCommandReply<cId>

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

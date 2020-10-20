//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Apr 14, 2015
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace statuscodes {

//==============================================================================

enum Codes
{
    EverythingOk = 0, //!< No error
    NotConnected, //!< Device is not connected.
    MismatchingCommandAndReply, //!<
    FailedToPrepareSendingCommand, //!< Error in preparing the send buffer.
    FailedToPrepareSendingDataBlock, //!< Error in preparing the send buffer.
    SendingCommandFailed, //!< Sending the command has failed.
    SendingDataBlockFailed, //!< Sending of the data block has failed.
    ReplyMismatch, //!< Received wrong command reply. Command ids not matching.
    TimeOut, //!< The reply has not received in proper time.
    TimeOutCriticalSection, //!< Critical section was blocked too long.
    ReceiveCommandErrorReply, //!< An command error reply has been received.
    DataBlockBlockedByFilter, //!< Datablock blocked by datatype id filter

    StreamerNotRegistered,
    ListenerNotRegistered
}; // Codes

//==============================================================================

} // namespace statuscodes
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

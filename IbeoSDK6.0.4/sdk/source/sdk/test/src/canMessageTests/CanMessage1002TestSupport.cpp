//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Mar 19, 2018
//------------------------------------------------------------------------------

#include "CanMessage1002TestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

//==============================================================================

CanMessage1002 CanMessage1002TestSupport::createCanMessage(const bool extCanId, const bool validTimeStamp)
{
    CanMessage1002 canMsg;
    fillRandomly(canMsg, extCanId, validTimeStamp);
    return canMsg;
}

//==============================================================================

void CanMessage1002TestSupport::fillRandomly(CanMessage1002& canMsg, const bool extCanId, const bool validTimeStamp)
{
    canMsg.setVersion(getRandValue<uint8_t>(CanMessage1002::maxVersion));
    const uint8_t nbOfBytes = getRandValue<uint8_t>(CanMessage1002::maxMsgSize);
    canMsg.setLength(nbOfBytes);
    canMsg.setMsgType(extCanId ? CanMessage1002::MsgType::Extended : CanMessage1002::MsgType::Standard);
    canMsg.setCanId(getRandValue<uint32_t>(extCanId ? CanMessage1002::maxExtId : CanMessage1002::maxStdId));
    canMsg.setUsSinceStartup(getRandValue<uint32_t>());

    if (validTimeStamp)
    {
        canMsg.setTimestamp(getRandValue<NTPTime>());
    }
    else
    {
        NTPTime ts;
        ts.setInvalid();
        canMsg.setTimestamp(ts);
    }
    canMsg.setDeviceId(getRandValue<uint8_t>());
}

//==============================================================================

CanMessage1002::MsgType CanMessage1002TestSupport::getRandomCanMessageType(const bool extCanId)
{
    CanMessage1002::MsgType msgType = extCanId ? CanMessage1002::MsgType::Extended : CanMessage1002::MsgType::Standard;
    //	msgType |= CanMessage1002::MsgType((getRandValue<bool>()) ? CanMessage1002::RTR : 0U);
    //	msgType |= CanMessage1002::MsgType((getRandValue<bool>()) ? CanMessage1002::ErrFrame : 0U);
    //	msgType |= CanMessage1002::MsgType((getRandValue<bool>()) ? CanMessage1002::Status : 0U);

    return msgType;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

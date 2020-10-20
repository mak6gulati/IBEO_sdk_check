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

#include "CanMessageTestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

CanMessage CanMessageTestSupport::createCanMessage(const bool extCanId, const bool validTimeStamp)
{
    CanMessage canMsg;
    fillRandomly(canMsg, extCanId, validTimeStamp);
    return canMsg;
}

//==============================================================================

void CanMessageTestSupport::fillRandomly(CanMessage& canMsg, const bool extCanId, const bool validTimeStamp)
{
    canMsg.setVersion(getRandValue<uint8_t>(CanMessage::maxVersion));
    const uint8_t nbOfBytes = getRandValue<uint8_t>(CanMessage::maxMsgSize);
    canMsg.setLength(nbOfBytes);
    canMsg.setMsgType(extCanId ? CanMessage::MsgType::Extended : CanMessage::MsgType::Standard);
    canMsg.setCanId(getRandValue<uint32_t>(extCanId ? CanMessage::maxExtId : CanMessage::maxStdId));
    NTPTime tmpTime = canMsg.getTimestamp();
    if (validTimeStamp)
    {
        do
        {
            canMsg.setTimestamp(getRandValue<NTPTime>());
        } while ((canMsg.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (canMsg.getTimestamp() == tmpTime));
        canMsg.setUsSinceStartup(getRandValue<uint32_t>());
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
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

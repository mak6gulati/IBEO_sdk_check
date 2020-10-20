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
//!\date 12.October 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/datablocks/canmessage/CanMessage.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <string>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

bool operator==(const CanMessage& lhs, const CanMessage& rhs)
{
    const bool fixPartEqual = (lhs.getVersion() == rhs.getVersion()) && (lhs.getLength() == rhs.getLength())
                              && (lhs.getMsgType() == rhs.getMsgType()) && (lhs.getCanId() == rhs.getCanId())
                              && (lhs.getDeviceId() == rhs.getDeviceId());

    const bool hasTimestamp = lhs.hasTimeStamp();

    if (fixPartEqual)
    {
        bool tsEqual{true};
        if (hasTimestamp)
        {
            tsEqual
                = (lhs.getUsSinceStartup() == rhs.getUsSinceStartup()) && (lhs.getTimestamp() == rhs.getTimestamp());
        }

        if (tsEqual)
        {
            if (lhs.getLength() > 0)
            {
                for (uint_fast8_t b = 0; b < lhs.getLength(); ++b)
                {
                    if (lhs.getData(CanMessage::ByteNumber(b)) != rhs.getData(CanMessage::ByteNumber(b)))
                    {
                        return false; // found one byte that isn't equal
                    }
                } // for all valid bytes
            } // if any data is attached

            // if tsEqual and length equal 0 or otherwise all bytes are the same
            return true; // all valid bytes are equal
        }
    }
    return false; // the fix part isn't equal
}

//==============================================================================

bool operator!=(const CanMessage& lhs, const CanMessage& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

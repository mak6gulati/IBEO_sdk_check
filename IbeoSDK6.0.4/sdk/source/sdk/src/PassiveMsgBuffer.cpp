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
//! \date Jul 12, 2016
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/PassiveMsgBuffer.hpp>

#include <boost/array.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/bind.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

PassiveMsgBuffer::PassiveMsgBuffer(const int bufSize) : MsgBufferBase(bufSize) {}

//==============================================================================

PassiveMsgBuffer::~PassiveMsgBuffer() {}

//==============================================================================

bool PassiveMsgBuffer::getMessage(const IbeoDataHeader*& recvDataHeader,
                                  const char*& startOfMsgBody,
                                  const int nbOfBytesReceived)
{
    increaseInsPos(nbOfBytesReceived);
    const bool receivedDataBlock = processBuffer(recvDataHeader, startOfMsgBody, nbOfBytesReceived);
    bufferCleanup();
    return receivedDataBlock;
}

//==============================================================================

bool PassiveMsgBuffer::increaseInsPos(const int nbOfBytesReceived)
{
    this->m_insAt += nbOfBytesReceived;

    if (this->m_insAt > this->m_bufCapacity)
    {
        this->m_insAt = -1;
        return false;
    }
    return true;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

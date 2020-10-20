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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/MsgBufferBase.hpp>
#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>

#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/system/error_code.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//! \brief
//! \date Jul 12, 2016
//!
//!
//------------------------------------------------------------------------------
class PassiveMsgBuffer : public MsgBufferBase
{
public:
    //========================================
    //! \brief Constructor
    //!
    //! \param[in]       bufSize     Size of the buffer
    //!                              which will be allocated
    //!                              to hold the received
    //!                              message data. This size has to be
    //!                              significantly larger than the largest
    //!                              to be expected message.
    //-------------------------------------
    PassiveMsgBuffer(const int bufSize);

    //========================================
    //! \brief Destructor.
    //-------------------------------------
    virtual ~PassiveMsgBuffer();

public:
    bool getMessage(const IbeoDataHeader*& recvDataHeader, const char*& startOfMsgBody, const int nbOfBytesReceived);

protected:
    bool increaseInsPos(const int nbOfBytesReceived);
}; // PassiveMsgBuffer

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

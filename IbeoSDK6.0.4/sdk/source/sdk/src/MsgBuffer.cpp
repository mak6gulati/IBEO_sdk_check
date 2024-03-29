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
//! \date Jun 28, 2012
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/MsgBuffer.hpp>
#include <ibeo/common/logging/logging.hpp>

#include <boost/array.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/bind.hpp>

#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif // gcc or clang

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

MsgBuffer::MsgBuffer(boost::asio::ip::tcp::socket* recvSocket, const int bufSize)
  : MsgBufferBase(bufSize),
    m_socket(recvSocket),
    m_timer(m_socket->get_io_service()),
    m_timerResult(),
    m_readResult(),
    m_nbOfBytesRead(0),
    m_stopOnTimeOut(false)
{}

//==============================================================================

MsgBuffer::~MsgBuffer() {}

//==============================================================================

int MsgBuffer::readWithTimeout(boost::asio::ip::tcp::socket& s,
                               const boost::asio::mutable_buffers_1& buffers,
                               const boost::asio::deadline_timer::duration_type& expiryTime,
                               boost::system::error_code& readError)
{
    m_timerResult.reset();
    m_readResult.reset();

    m_timer.expires_from_now(expiryTime);
    m_timer.async_wait(boost::bind(&MsgBuffer::waitHandler, this, _1));
    s.async_read_some(buffers, boost::bind(&MsgBuffer::asynReadSomeHandler, this, _1, _2));

    s.get_io_service().reset();
    while (s.get_io_service().run_one())
    {
        if (m_readResult)
        {
            m_timer.cancel();
        }
        else if (m_timerResult)
        {
            if (m_stopOnTimeOut)
            {
                LOGDEBUG(logger, "Timeout in async read. Stop io service.");
                s.cancel();
            }
            else
            {
                LOGDEBUG(logger, "Timeout in async read. Continue io service.");
                readError = boost::system::error_code();
                return 0;
            }
        }
    }

    if (*m_readResult)
        readError = *m_readResult;
    else
    {
        readError = boost::system::error_code();
    }

    return int(m_nbOfBytesRead);
}

//==============================================================================

bool MsgBuffer::recvMsg(const IbeoDataHeader*& recvDataHeader, const char*& startOfMsgBody)
{
    m_stopOnTimeOut = false;
    return recvMsgInternal(recvDataHeader, startOfMsgBody, boost::posix_time::seconds(1));
}

//==============================================================================

bool MsgBuffer::recvMsg(const IbeoDataHeader*& recvDataHeader,
                        const char*& startOfMsgBody,
                        const boost::asio::deadline_timer::duration_type expiryTime)
{
    m_stopOnTimeOut = true;
    return recvMsgInternal(recvDataHeader, startOfMsgBody, expiryTime);
}

//==============================================================================

bool MsgBuffer::recvMsg(const IbeoDataHeader*& recvDataHeader,
                        const char*& startOfMsgBody,
                        const boost::optional<boost::asio::deadline_timer::duration_type> expiryTime)
{
    if (expiryTime)
    {
        m_stopOnTimeOut = true;
        return recvMsgInternal(recvDataHeader, startOfMsgBody, expiryTime.get());
    }
    else
    {
        m_stopOnTimeOut = false;
        return recvMsgInternal(recvDataHeader, startOfMsgBody, boost::posix_time::seconds(1));
    }
}

//==============================================================================

int MsgBuffer::getNewDataIfNeeded(const boost::asio::deadline_timer::duration_type expiryTime)
{
    int recvLen = 0;
    if (this->m_needToRecvData)
    {
        const int bytesToRead = this->m_bufCapacity - this->m_insAt;
        char* const recvBuf   = this->m_ptr + this->m_insAt;
        boost::system::error_code error;

        recvLen = readWithTimeout(*m_socket, boost::asio::buffer(recvBuf, std::size_t(bytesToRead)), expiryTime, error);

        //recvLen = int(m_socket->read_some(boost::asio::buffer(recvBuf, std::size_t(bytesToRead)), error));
        m_insAt += recvLen;

        if (error == boost::asio::error::eof)
        {
            LOGERROR(logger, "TCP/IP eof error occured  -  " << error.message());
            throw error;
        }
        else if (error)
        {
            LOGERROR(logger, "TCP/IP error occured  -  " << error.message());
            throw error;
        }
    } // if

    return recvLen;
}

//==============================================================================

bool MsgBuffer::recvMsgInternal(const IbeoDataHeader*& recvDataHeader,
                                const char*& startOfMsgBody,
                                const boost::asio::deadline_timer::duration_type expiryTime)
{
    bufferCleanup();

    const int recvLen = getNewDataIfNeeded(expiryTime);

    return processBuffer(recvDataHeader, startOfMsgBody, recvLen);
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

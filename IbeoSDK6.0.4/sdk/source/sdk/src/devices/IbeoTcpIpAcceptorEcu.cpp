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
//! \date May 17, 2016
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/devices/IbeoTcpIpAcceptorEcu.hpp>
#include <ibeo/common/sdk/CommandId.hpp>
#include <ibeo/common/sdk/datablocks/commands/ecucommands/CommandEcuSetFilterC.hpp>
#include <ibeo/common/sdk/datablocks/commands/ecucommands/CommandEcuSetFilter2010Importer2010.hpp>
#include <ibeo/common/sdk/datablocks/commands/ecucommands/ReplyEcuSetFilter.hpp>
#include <ibeo/common/sdk/MsgBuffer.hpp>

#include <boost/iostreams/stream.hpp>

#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif // gcc or clang

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

IbeoTcpIpAcceptorEcu::SessionEcu::SessionEcu(
    IbeoTcpIpAcceptorBase* const parent,
    boost::asio::io_service& io_service,
    const boost::optional<boost::asio::deadline_timer::duration_type> readExpirationTime,
    const uint8_t deviceId)
  : IbeoTcpIpAcceptorBase::SessionBase(parent, io_service, deviceId),
    m_expiryTime(readExpirationTime),
    m_timer(io_service),
    m_msgBuffer(msgBufferSize)
{}

//==============================================================================

void IbeoTcpIpAcceptorEcu::SessionEcu::startListen()
{
    LOGDEBUG(logger, "Start listening  " << (void*)(this));
    if (m_socket.is_open())
    {
        startTimer();
        startRead();
    }
}

//==============================================================================

void IbeoTcpIpAcceptorEcu::SessionEcu::startTimer()
{
    if (m_expiryTime)
        m_timer.expires_from_now(m_expiryTime.get());
    else
        m_timer.expires_from_now(boost::posix_time::seconds(1));
    m_timer.async_wait(boost::bind(&IbeoTcpIpAcceptorEcu::timeout, this, _1));
}

//==============================================================================

void IbeoTcpIpAcceptorEcu::SessionEcu::startRead()
{
    char* const recvBuf                           = m_msgBuffer.getRecvBuf();
    const int bytesToRead                         = m_msgBuffer.getBytesToRead();
    const boost::asio::mutable_buffers_1& buffers = boost::asio::buffer(recvBuf, std::size_t(bytesToRead));

    if (m_socket.is_open())
    {
        m_socket.async_read_some(buffers, boost::bind(&IbeoTcpIpAcceptorEcu::listen, this, _1, _2));
    }
}

//==============================================================================

void IbeoTcpIpAcceptorEcu::SessionEcu::listen(const boost::system::error_code& error, const size_t nbOfBytesReceived)
{
    if (!error)
    {
        LOGDEBUG(logger, "Received " << nbOfBytesReceived << " byte.");
        //m_msgBuffer.increaseInsPos(int(nbOfBytesReceived));

        const IbeoDataHeader* recvDataHeader;
        const char* startOfMsgBody;

        // process all received commands
        while (m_msgBuffer.getMessage(recvDataHeader, startOfMsgBody, int(nbOfBytesReceived)))
        {
            LOGDEBUG(logger, "Received data block " << toHex(recvDataHeader->getDataType()));

            if (recvDataHeader && (recvDataHeader->getDataType() == DataTypeId::DataType_Command2010))
            {
                onReceiveCommand(*recvDataHeader, startOfMsgBody);
                continue;
            }
        }

        if (m_socket.is_open())
        {
            startRead();
        }
    }
    else
    {
        LOGERROR(logger, error.message());
        m_timer.cancel();
    }
}

//==============================================================================

void IbeoTcpIpAcceptorEcu::SessionEcu::readTimeout(const boost::system::error_code& error)
{
    if (m_socket.is_open())
    {
        if (!error)
        {
            LOGDEBUG(logger, "Restart read timer");
            startTimer();
        }
        else
        {
            // open or error occurred
            LOGTRACE(logger, error.message());
            LOGDEBUG(logger, "Canceling read operation");
            m_socket.cancel();
        }
    }
}

//==============================================================================

IbeoTcpIpAcceptorEcu::IbeoTcpIpAcceptorEcu(const unsigned short port)
  : IbeoTcpIpAcceptorBase(port), m_readExpirationTime()
{}

//==============================================================================

IbeoTcpIpAcceptorEcu::IbeoTcpIpAcceptorEcu(
    const boost::optional<boost::asio::deadline_timer::duration_type> expirationTime,
    const unsigned short port)
  : IbeoTcpIpAcceptorBase(expirationTime, port), m_readExpirationTime(expirationTime)
{}

//==============================================================================

IbeoTcpIpAcceptorEcu::IbeoTcpIpAcceptorEcu(
    const boost::optional<boost::asio::deadline_timer::duration_type> readExpirationTime,
    const boost::asio::deadline_timer::duration_type writeExpirationTime,
    const unsigned short port)
  : IbeoTcpIpAcceptorBase(writeExpirationTime, port), m_readExpirationTime(readExpirationTime)
{}

//==============================================================================

IbeoTcpIpAcceptorBase::SessionBase::Ptr IbeoTcpIpAcceptorEcu::getNewSessionPtr(boost::asio::io_service& io_service)
{
    m_sessionPtr.reset(new SessionEcu(this, io_service, m_readExpirationTime));
    return m_sessionPtr;
}

//==============================================================================

void IbeoTcpIpAcceptorEcu::SessionEcu::onReceiveCommand(const IbeoDataHeader& dh, const char* bodyBuf)
{
    {
        const uint8_t* bb = reinterpret_cast<const uint8_t*>(bodyBuf);
        LOGDEBUG(logger,
                 "Incomming Command: " << toHex(uint16_t(*(bb + 1) + ((*(bb)) << 8)))
                                       << "  Size: " << dh.getMessageSize());
    }

    ibeo::common::sdk::CommandId cmd_id(0); // set dummy id
    {
        boost::iostreams::stream<boost::iostreams::array_source> stream(bodyBuf, dh.getMessageSize());
        std::istream& s = (std::istream&)stream;
        cmd_id.readBE(s);
    }

    if (cmd_id == ibeo::common::sdk::CommandId::Id::CmdManagerSetFilter)
    {
        // serialize CmdSetFilter because we want to apply that filter
        // dummy construct, will be filled with stream

        CommandEcuSetFilterC cmd;
        CommandEcuSetFilter2010Importer2010 imp;

        boost::iostreams::stream<boost::iostreams::array_source> cmdStream(bodyBuf, dh.getMessageSize());
        std::istream& cmdS = (std::istream&)cmdStream;

        imp.deserialize(cmdS, cmd, dh);

        setRanges(cmd.getRanges());

        ibeo::common::sdk::ReplyEcuSetFilter rplyEcuSetFilter;
        sendDatablock(rplyEcuSetFilter);
    }
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

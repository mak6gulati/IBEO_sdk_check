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
//! \date May 5, 2017
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/devices/TcpReceiveThreadEnsemble.hpp>
#include <ibeo/common/sdk/devices/IbeoDeviceBase.hpp>
#include <ibeo/common/sdk/MsgBuffer.hpp>
#include <ibeo/common/sdk/EventMonitor.hpp>

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/scoped_ptr.hpp>

#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif // gcc or clang

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

TcpReceiveThreadEnsemble::TcpReceiveThreadEnsemble(const boost::asio::ip::address& ip,
                                                   const unsigned short port,
                                                   ReceiveDataBlock receiveDataBlock)
  : m_ioService(),
    m_endPoint(ip, port),
    m_socket(),
    m_expiryTime(),
    m_receiveDataBlock(receiveDataBlock),
    m_mutex(),
    m_threadRunner(std::bind(&TcpReceiveThreadEnsemble::recvThreadMain, this)),
    m_rMutex(),
    m_replyPtr(nullptr),
    m_expectedReplyId(CommandId(CommandId::Id::CmdLuxReset)),
    m_eventMonitor(),
    m_eventReplyReceived(m_eventMonitor.newEvent()),
    m_sizeOfPrevCommand(0)
{
    m_threadRunner.setThreadName("TcpReceive");
}

//==============================================================================

TcpReceiveThreadEnsemble::~TcpReceiveThreadEnsemble()
{
    // Stop thread.
    m_threadRunner.stop();
    m_threadRunner.join();
}

//==============================================================================

TcpReceiveThreadEnsemble::ReconnectMode TcpReceiveThreadEnsemble::getReconnectMode() const
{
    Lock lock(m_mutex);
    return m_reconnectMode;
}

//==============================================================================

void TcpReceiveThreadEnsemble::setReconnectMode(TcpReceiveThreadEnsemble::ReconnectMode reconnectMode)
{
    Lock lock(m_mutex);
    m_reconnectMode = reconnectMode;
    LOGDEBUG(logger, "Reconnect mode set to " << m_reconnectMode << ".");
}

//==============================================================================

const TcpReceiveThreadEnsemble::TimeDuration& TcpReceiveThreadEnsemble::getReconnectTime() const
{
    Lock lock(m_mutex);
    return m_reconnectTime;
}

//==============================================================================

void TcpReceiveThreadEnsemble::setReconnectTime(const TimeDuration& reconnectTime)
{
    Lock lock(m_mutex);
    m_reconnectTime = reconnectTime;
    LOGDEBUG(logger, "Reconnect time set to " << m_reconnectTime << ".");
}

//==============================================================================

boost::optional<boost::asio::deadline_timer::duration_type> TcpReceiveThreadEnsemble::getExpiryTime() const
{
    Lock lock(m_mutex);
    return m_expiryTime;
}

//==============================================================================

void TcpReceiveThreadEnsemble::setExpiryTime(const boost::asio::deadline_timer::duration_type expiryTime)
{
    Lock lock(m_mutex);
    m_expiryTime.reset(expiryTime);

    if (m_expiryTime.is_initialized())
    {
        LOGDEBUG(logger, "Expiry time set to " << m_expiryTime.value() << ".");
    }
    else
    {
        LOGDEBUG(logger, "Expiry time set to <null>.");
    }
}

//==============================================================================

void TcpReceiveThreadEnsemble::resetExpiryTime()
{
    Lock lock(m_mutex);
    m_expiryTime.reset();
    LOGDEBUG(logger, "Expiry time set to <null>.");
}

//==============================================================================

void TcpReceiveThreadEnsemble::run() { m_threadRunner.start(); }

//==============================================================================

bool TcpReceiveThreadEnsemble::powerUpConnection()
{
    if (!m_receiveDataBlock)
    {
        LOGERROR(logger, "Failed to start TCP/IP receive thread! Reason: no onData method has be specified.");
        return false;
    }

    m_threadRunner.setThreadState(ThreadRunner::ThreadState::Starting);

    try
    {
        Lock lock(m_mutex);
        m_socket.reset(new boost::asio::ip::tcp::socket(m_ioService));
    }
    catch (const std::exception& e)
    {
        LOGERROR(logger, "Failed to allocate socket! Reason: " << e.what() << ".");

        m_threadRunner.setThreadState(ThreadRunner::ThreadState::StartFailed);
        return false;
    }

    return true;
}

//==============================================================================

bool TcpReceiveThreadEnsemble::connect()
{
    Lock lock(m_mutex);
    boost::system::error_code ec;
    m_socket->connect(m_endPoint, ec);

    if (ec)
    {
        LOGERROR(logger, "Failed to connect to device (" << m_endPoint << ")! Reason: " << ec.message() << ".");
        m_socket->close();
        return false;
    }

    try
    {
        boost::asio::ip::tcp::no_delay option(true);
        m_socket->set_option(option);
    }
    catch (const std::exception& e)
    {
        LOGERROR(logger, "Failed to set socket option! Reason: " << e.what() << ".");
        m_socket->close();
        return false;
    }

    LOGTRACE(logger, "Connected to device on " << m_endPoint << ".");
    return true;
}

//==============================================================================

void TcpReceiveThreadEnsemble::recvThreadMain()
{
    // Initialize socket connection.
    if (powerUpConnection() == false)
    {
        // Startup failed -> end thread.
        return;
    }

    // Thread is running now.
    m_threadRunner.setThreadState(ThreadRunner::ThreadState::Running);

    while (m_threadRunner.getThreadState() == ThreadRunner::ThreadState::Running)
    {
        if (connect() == false)
        {
            // Connection to remote device failed.
            if (getReconnectMode() == ReconnectMode::InitialConnect)
            {
                // Do not attempt to re-establish the connection, but mark as failed.
                m_threadRunner.setThreadState(ThreadRunner::ThreadState::StartFailed);
            }
            else
            {
                // Wait some time before trying to re-establish the connection.
                waitForReconnectTimeout();
                continue;
            }
        }

        // Connection established -> start handling received data.
        const char* bodyBuf;
        const IbeoDataHeader* dh;
        ibeo::common::sdk::MsgBuffer msgBuf(m_socket.get(), bufferSize);

        boost::optional<boost::asio::deadline_timer::duration_type> expiryTime;

        try
        {
            while ((m_threadRunner.getThreadState() != ThreadRunner::ThreadState::Stopping) && m_socket->is_open())
            {
                {
                    Lock lock(m_mutex);
                    expiryTime = m_expiryTime;
                }

                try
                {
                    // Read next datablock.
                    bool messageReceived;
                    {
                        Lock lock(m_mutex);
                        messageReceived = msgBuf.recvMsg(dh, bodyBuf, expiryTime);
                    }
                    if (messageReceived)
                    {
                        LOGTRACE(logger, "Received DataBlock of type " << toHex(dh->getDataType()) << std::dec);

                        if ((dh->getDataType() == DataTypeId::DataType_Reply2020))
                        {
                            onReceiveCommandReply(*dh, bodyBuf);
                            continue; // do not inform any streamer or listener
                        }

                        m_receiveDataBlock(dh, bodyBuf);
                    }
                } // try
                catch (const boost::system::error_code& errorCode)
                {
                    Lock lock(m_mutex);
                    if ((m_socket == nullptr) || (m_socket->is_open() == false)
                        || (errorCode != boost::asio::error::operation_aborted))
                    {
                        // Unrecoverable error -> stop receiving datablocks.
                        throw;
                    }
                    else
                    {
                        // Log error and continue with next datablock.
                        LOGINFO(logger, errorCode.message());
                    }
                } // catch
            } // while
        } // try
        catch (const boost::system::error_code& errorCode)
        {
            // Error while receiving datablocks.
            LOGINFO(logger, "Stop receiving: " << errorCode.message());
        } // catch

        {
            Lock lock(m_mutex);
            if ((m_socket != nullptr) && m_socket->is_open())
            {
                LOGINFO(logger, "Closing socket");
                m_socket->close();
            }
        }

        if (getReconnectMode() == ReconnectMode::AutoReconnect)
        {
            // Wait some time before trying to re-establish the connection.
            waitForReconnectTimeout();
        }
        else
        {
            // Connection lost and should not be re-established -> task done.
            m_threadRunner.setThreadState(ThreadRunner::ThreadState::Stopping);
        }
    } // while

    m_threadRunner.setThreadState(ThreadRunner::ThreadState::NotRunning);
}

//==============================================================================

bool TcpReceiveThreadEnsemble::waitForReconnectTimeout() const
{
    TimeDuration reconnectTime;
    {
        Lock lock(m_mutex);
        reconnectTime = m_reconnectTime;
    }

    try
    {
        boost::this_thread::sleep(reconnectTime);
        return true;
    }
    catch (const boost::thread_interrupted& exc)
    {
        return false;
    }
}

//==============================================================================

void TcpReceiveThreadEnsemble::disconnect()
{
    Lock lock(m_mutex);

    if (m_socket.get() != nullptr)
    {
        m_socket->close();
        m_socket.reset();
    }
}

//==============================================================================

void TcpReceiveThreadEnsemble::stop()
{
    // Interrupt and stop thread.
    m_threadRunner.stop(true);
    disconnect();
}

//==============================================================================

bool TcpReceiveThreadEnsemble::isRunning() const
{
    ThreadRunner::ThreadState state = m_threadRunner.getThreadState();

    return (state == ThreadRunner::ThreadState::Starting) || (state == ThreadRunner::ThreadState::Running);
}

//==============================================================================

bool TcpReceiveThreadEnsemble::isNotYetRunning() const
{
    ThreadRunner::ThreadState state = m_threadRunner.getThreadState();

    return (state == ThreadRunner::ThreadState::NotRunning) || (state == ThreadRunner::ThreadState::Starting);
}

//==============================================================================

bool TcpReceiveThreadEnsemble::isConnected() const
{
    Lock lock(m_mutex);

    if (m_socket == nullptr)
    {
        LOGDEBUG(logger, "Not connected: socket not created!");
        return false;
    }
    if (m_socket->is_open() == false)
    {
        LOGDEBUG(logger, "Not connected: socket not open!");
        return false;
    }

    LOGDEBUG(logger, "Connected!");
    return true;
}

//==============================================================================

statuscodes::Codes TcpReceiveThreadEnsemble ::sendCommand(const CommandCBase& cmd,
                                                          const SpecialExporterBase<CommandCBase>& exporter)
{
    if (!isConnected())
    {
        // cannot send a command if the device is not connected.
        LOGERROR(logger, " command (id " << toHex(cmd.getCommandId()) << ") failed " << statuscodes::NotConnected);
        return statuscodes::NotConnected;
    }

    // Send command
    LOGDEBUG(logger,
             "Sending "
                 << " command (id " << toHex(cmd.getCommandId()) << ") "
                 << "; expecting no reply");

    const statuscodes::Codes errorCode = sendCommandInternal(cmd, exporter);
    LOGDEBUG(logger, "Done. " << errorCode);

    return errorCode;
}

//==============================================================================

statuscodes::Codes TcpReceiveThreadEnsemble ::sendCommand(const CommandCBase& cmd,
                                                          const SpecialExporterBase<CommandCBase>& exporter,
                                                          CommandReplyBase& reply,
                                                          const boost::posix_time::time_duration timeOut)
{
    if (!isConnected())
    {
        // cannot send a command if the device is not connected.
        LOGERROR(logger,
                 " command (id " << toHex(cmd.getCommandId()) << ") failed  Reply: " << toHex(reply.getCommandId())
                                 << " " << statuscodes::NotConnected);
        return statuscodes::NotConnected;
    }

    if (CommandId::Id(cmd.getCommandId()) != CommandId::Id(reply.getCommandId()))
    {
        LOGERROR(logger,
                 " command (id " << toHex(cmd.getCommandId()) << ") failed  Reply: " << toHex(reply.getCommandId())
                                 << " " << statuscodes::MismatchingCommandAndReply);
        return statuscodes::MismatchingCommandAndReply;
    }

    {
        // Pass reply buffer to onReceiveCommandReply() which is running
        // in the reception thread
        boost::recursive_timed_mutex::scoped_lock criticalSection(m_rMutex);
        assert(!m_replyPtr); // previous reply must have been completely processed
        m_replyPtr        = &reply;
        m_expectedReplyId = cmd.getCommandId();
    }

    statuscodes::Codes errorCode = statuscodes::EverythingOk;
    try
    {
        // Send command
        LOGDEBUG(logger,
                 "Sending "
                     << " command (id " << toHex(cmd.getCommandId()) << ")");

        if (sendCommandInternal(cmd, exporter) != statuscodes::EverythingOk)
            throw statuscodes::SendingCommandFailed;

        // Wait for reply. The event m_eventReplyReceived will be signaled by
        EventMonitor::Mask event = m_eventMonitor.wait(timeOut, m_eventReplyReceived);

        if (event == EventMonitor::TimeOutEvent)
            throw statuscodes::TimeOut;
        else if ((uint16_t(cmd.getCommandId()) | CommandReplyBase::errorMask)
                 != (uint16_t(reply.getCommandId()) | CommandReplyBase::errorMask))
            throw statuscodes::ReplyMismatch;
        else if (reply.isErrorReply())
            throw statuscodes::ReceiveCommandErrorReply;
    } // try
    catch (const statuscodes::Codes& ec)
    {
        errorCode = ec;
        LOGERROR(logger,
                 " command (id " << toHex(cmd.getCommandId()) << ") failed  Reply: " << toHex(reply.getCommandId())
                                 << " " << ec);
    } // catch

    {
        // Clear reply buffer for reception thread
        boost::recursive_timed_mutex::scoped_lock criticalSection(m_rMutex);
        assert(m_replyPtr);
        m_replyPtr        = nullptr;
        m_expectedReplyId = CommandId(0x7fff);
    }

    return errorCode;
}

//==============================================================================

statuscodes::Codes TcpReceiveThreadEnsemble ::sendCommandInternal(const CommandCBase& cmd,
                                                                  const SpecialExporterBase<CommandCBase>& exporter)
{
    const boost::posix_time::ptime timeout
        = boost::posix_time::microsec_clock::universal_time() + boost::posix_time::milliseconds(50);
    boost::recursive_timed_mutex::scoped_timed_lock criticalSection(m_rMutex, timeout);

    if (criticalSection)
    {
        // if we have got thread-safe access in time
        if (isConnected())
        {
            const uint32_t cmdLength     = uint32_t(exporter.getSerializedSize(cmd));
            const uint32_t sizeOfThisMsg = cmdLength;
            const uint32_t sizeOfBuffer  = sizeOfThisMsg + IbeoDataHeader::getHeaderSize();

            boost::scoped_ptr<char> sendBuf(new char[sizeOfBuffer]);
            boost::iostreams::stream<boost::iostreams::array> strm(sendBuf.get(), sizeOfBuffer);
            std::ostream& s = (std::ostream&)strm;

            const IbeoDataHeader header(
                DataTypeId::DataType_Command2010, m_sizeOfPrevCommand, sizeOfThisMsg, 1, NTPTime());

            LOGDEBUG(logger, "Sending command with " << sizeOfThisMsg << " bytes");

            header.serialize(s);
            exporter.serialize(s, cmd);
            if (!s.good())
                return statuscodes::FailedToPrepareSendingCommand;

            const size_t nbOfBytesSend = m_socket->send(boost::asio::buffer(sendBuf.get(), sizeOfBuffer));
            if (nbOfBytesSend != size_t(sizeOfBuffer))
            {
                LOGERROR(logger, "Send " << nbOfBytesSend << " expected: " << sizeOfBuffer);

                return statuscodes::SendingCommandFailed;
            }

            m_sizeOfPrevCommand = uint32_t(sizeOfThisMsg);

            return statuscodes::EverythingOk;
        }
        return statuscodes::NotConnected;
    }

    LOGERROR(logger, "Timeout while locking critical section");
    return statuscodes::TimeOutCriticalSection;
}

//==============================================================================

void TcpReceiveThreadEnsemble::onReceiveCommandReply(const IbeoDataHeader& dh, const char* bodyBuf)
{
    {
        const uint8_t* bb = reinterpret_cast<const uint8_t*>(bodyBuf);
        LOGTRACE(logger,
                 "INCOMMING REPLY: " << toHex(uint16_t(*(bb + 1) + ((*(bb)) << 8)))
                                     << "  Size: " << dh.getMessageSize());
    }

    if (m_replyPtr != nullptr)
    {
        boost::iostreams::stream<boost::iostreams::array_source> strm(bodyBuf, dh.getMessageSize());
        std::istream& s = (std::istream&)strm;
        if (m_replyPtr->deserializeFromStream(s, dh))
        {
            LOGDEBUG(logger, "Received Reply -- good");
        }
        else
        {
            LOGDEBUG(logger, "Received Reply -- failed");
            if (m_replyPtr)
                m_replyPtr->setErrorReply();
        }

        // Wake up main thread waiting in command()
        m_eventMonitor.signal(m_eventReplyReceived);
    }
    else
    {
        LOGDEBUG(logger, "INCOMMING REPLY UNEXPECTED");
    }
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

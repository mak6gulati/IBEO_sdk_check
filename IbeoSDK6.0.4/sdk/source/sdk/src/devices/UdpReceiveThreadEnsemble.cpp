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

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>
#include <ibeo/common/sdk/devices/UdpReceiveThreadEnsemble.hpp>

#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif // gcc or clang

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

UdpReceiveThreadEnsemble::UdpReceiveThreadEnsemble(const boost::asio::ip::address& ip,
                                                   const unsigned short port,
                                                   ReceiveDataBlock receiveDataBlock,
                                                   const boost::asio::ip::address_v4 ifa,
                                                   bool enableMulticast)
  : m_ioService(),
    m_endPoint(ifa, port),
    m_ipAdr(ip),
    m_socket(),
    m_enableMulticast(enableMulticast),
    m_timerResult(),
    m_readResult(),
    m_auxTimer(m_ioService),
    m_stopOnTimeOut(true),
    m_expiryTime(),
    m_sutpInterface(boost::bind(&UdpReceiveThreadEnsemble::handleSutpMsgs,
                                this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred)),
    m_receiveDataBlock(receiveDataBlock),
    m_udpRecvMutex(),
    m_udpRecvThreadStateCondition(),
    m_udpRecvThread(NULL),
    m_sutpMutex(),
    m_sutpThread(NULL),
    m_udpRecvThreadState(ThreadState::NotRunning)
{}

//==============================================================================

UdpReceiveThreadEnsemble::~UdpReceiveThreadEnsemble()
{
    try
    {
        Lock lock(m_sutpMutex);
        if (m_sutpThreadState == ThreadState::Running)
        {
            m_sutpThreadState = ThreadState::Stopping;

            m_sutpInterface.getPacketCompleteCondition().notify_all();
        }
    }
    catch (...)
    {
        LOGERROR(logger, "failed");
    }

    try
    {
        Lock lock(m_udpRecvMutex);
        if (m_udpRecvThreadState == ThreadState::Running || m_udpRecvThreadState == ThreadState::Starting)
        {
            // Thread has not yet been stopped.
            // Ask for termination and wait till a state change
            // has been performed.
            m_udpRecvThreadState = ThreadState::Stopping;
            m_udpRecvThreadStateCondition.wait(lock);
        }
    }
    catch (...)
    {
        LOGERROR(logger, "failed 2");
    }

    if (this->m_sutpThread->joinable())
    {
        this->m_sutpThread->join();
        delete this->m_sutpThread;
        this->m_sutpThread = NULL;
    }
    if (this->m_udpRecvThread->joinable())
    {
        this->m_udpRecvThread->join();
        delete this->m_udpRecvThread;
        this->m_udpRecvThread = NULL;
    }
}

//==============================================================================

boost::optional<boost::asio::deadline_timer::duration_type> UdpReceiveThreadEnsemble::getExpiryTime() const
{
    Lock lock(m_udpRecvMutex);
    return m_expiryTime;
}

//==============================================================================

void UdpReceiveThreadEnsemble::setExpiryTime(const boost::asio::deadline_timer::duration_type expiryTime)
{
    Lock lock(m_udpRecvMutex);
    m_expiryTime.reset(expiryTime);
    LOGDEBUG(logger, "Set new ExpiryTime");
}

//==============================================================================

void UdpReceiveThreadEnsemble::resetExpiryTime()
{
    Lock lock(m_udpRecvMutex);
    m_expiryTime.reset();
}

//==============================================================================

void UdpReceiveThreadEnsemble::run()
{
    if (m_udpRecvThread)
        return;

    try
    {
        Lock lock(m_udpRecvMutex);

        m_sutpThread    = new boost::thread(&UdpReceiveThreadEnsemble::sutpHandlingThreadMain, this);
        m_udpRecvThread = new boost::thread(&UdpReceiveThreadEnsemble::recvThreadMain, this);

        while ((this->m_udpRecvThreadState == ThreadState::NotRunning
                || this->m_udpRecvThreadState == ThreadState::Starting))
        {
            m_udpRecvThreadStateCondition.wait(lock);
        }
    }
    catch (const boost::lock_error& e)
    {
        LOGERROR(logger, e.what());
    }
}

//==============================================================================

bool UdpReceiveThreadEnsemble::powerUpConnection()
{
    if (!m_receiveDataBlock)
    {
        LOGERROR(logger, "Failed to start UDP receive thread. No onData method has be specified.");
        return false;
    }

    try
    {
        Lock lock(m_udpRecvMutex);
        m_udpRecvThreadState = ThreadState::Starting;
        m_udpRecvThreadStateCondition.notify_all();
    }
    catch (const boost::lock_error& e)
    {
        LOGERROR(logger, e.what());
        return false;
    }

    try
    {
        m_socket.reset(new boost::asio::ip::udp::socket(m_ioService));
    }
    catch (const std::exception& e)
    {
        LOGERROR(logger, "Failed to allocate socket. - " << e.what());
        Lock lock(m_udpRecvMutex);
        m_udpRecvThreadState = ThreadState::StartFailed;
        m_udpRecvThreadStateCondition.notify_all();
        return false;
    }

    try
    {
        m_socket->open(boost::asio::ip::udp::v4());
        m_socket->set_option(boost::asio::ip::udp::socket::reuse_address(true));
        m_socket->set_option(boost::asio::socket_base::receive_buffer_size(bufferSize));
    }
    catch (const std::exception& e)
    {
        LOGERROR(logger, "Failed to open and configure socket. - " << e.what());
        try
        {
            Lock lock(m_udpRecvMutex);
            m_udpRecvThreadState = ThreadState::StartFailed;
            m_udpRecvThreadStateCondition.notify_all();
        }
        catch (const boost::lock_error& e1)
        {
            LOGERROR(logger, e1.what());
        }

        return false;
    }

    boost::system::error_code ec;

    m_socket->bind(m_endPoint);
    if (m_enableMulticast)
    {
        m_socket->set_option(boost::asio::ip::multicast::join_group(m_ipAdr));
    }

    if (ec)
    {
        LOGERROR(logger, "Failed to connect to device (" << m_endPoint << ") " << ec.message());
        try
        {
            Lock lock(m_udpRecvMutex);
            m_udpRecvThreadState = ThreadState::StartFailed;
            m_udpRecvThreadStateCondition.notify_all();
        }
        catch (const boost::lock_error& e)
        {
            LOGERROR(logger, e.what());
        }
        return false;
    }

    LOGDEBUG(logger, "Connected to device on " << m_endPoint);

    try
    {
        Lock lock(m_udpRecvMutex);
        m_udpRecvThreadState = ThreadState::Running;
        m_udpRecvThreadStateCondition.notify_all();
    }
    catch (const boost::lock_error& e)
    {
        LOGERROR(logger, e.what());
        return false;
    }

    return true;
}

//==============================================================================

void UdpReceiveThreadEnsemble::recvThreadMain()
{
    const bool powerUpOk = powerUpConnection();

    try
    {
        Lock lock(m_udpRecvMutex);
        m_udpRecvThreadState = powerUpOk ? ThreadState::Running : ThreadState::RunFailed;
        m_udpRecvThreadStateCondition.notify_all();
    }
    catch (const boost::lock_error& e)
    {
        LOGERROR(logger, e.what());
        return;
    }

    if (!powerUpOk)
    {
        return;
    }

    boost::optional<boost::asio::deadline_timer::duration_type> expiryTime;
    boost::system::error_code error;

    try
    {
        while (this->m_udpRecvThreadState != ThreadState::Stopping && m_socket->is_open())
        {
            try
            {
                Lock lock(m_udpRecvMutex);
                expiryTime = m_expiryTime;
            }
            catch (const boost::lock_error& e)
            {
                LOGERROR(logger, e.what());
            }

            if (receiveWithTimeout(*m_socket, m_endPoint, expiryTime.get(), error))
            {
                //				try
                //				{
                //					Lock lock(this->m_udpRecvMutex); // enforce extra lock here to give
                //					                                 // canceling a better chance.
                //					this->m_udpRecvThreadState = Running;
                //				}
                //				catch (const boost::lock_error& e)
                //				{
                //					LOGERROR(logger, e.what());
                //				}
            }
            else
            {
                try
                {
                    Lock lock(m_udpRecvMutex);
                    this->m_udpRecvThreadState = ThreadState::Stopping;
                    m_udpRecvThreadStateCondition.notify_all();
                }
                catch (const boost::lock_error& e)
                {
                    LOGERROR(logger, e.what());
                }
            }
        }
    }
    catch (const boost::system::error_code& errorCode)
    {
        LOGERROR(logger, "In receive loop: " << errorCode.message());
        m_udpRecvThreadState = ThreadState::RunFailed;
        m_udpRecvThreadStateCondition.notify_all();
        return;
    }

    if (!m_socket->is_open() && this->m_udpRecvThreadState != ThreadState::Stopping)
    {
        try
        {
            Lock lock(m_udpRecvMutex);
            m_udpRecvThreadState = ThreadState::RunFailed;
            m_udpRecvThreadStateCondition.notify_all();
        }
        catch (const boost::lock_error& e)
        {
            LOGERROR(logger, e.what());
        }

        return;
    }

    m_udpRecvThreadState = ThreadState::NotRunning;
    m_udpRecvThreadStateCondition.notify_all();
}

//==============================================================================

void UdpReceiveThreadEnsemble::disconnect()
{
    if (m_socket.get() != NULL)
    {
        m_socket.reset();
    }
}

//==============================================================================

void UdpReceiveThreadEnsemble::stop()
{
    if (isRunning())
    {
        try
        {
            Lock lock(m_udpRecvMutex);
            m_udpRecvThreadState = ThreadState::Stopping;
        }
        catch (const boost::lock_error& e)
        {
            LOGERROR(logger, e.what());
        }
    }
    disconnect();
}

//==============================================================================

bool UdpReceiveThreadEnsemble::isRunning() const
{
    ThreadState state = ThreadState::NotRunning;
    try
    {
        Lock lock(m_udpRecvMutex);
        state = m_udpRecvThreadState;
    }
    catch (const boost::lock_error& e)
    {
        LOGERROR(logger, e.what());
    }

    if (state == ThreadState::Starting || state == ThreadState::Running)
    {
        return true;
    }
    return false;
}

//==============================================================================

bool UdpReceiveThreadEnsemble::isNotYetRunning() const
{
    ThreadState state = ThreadState::NotRunning;
    try
    {
        Lock lock(m_udpRecvMutex);
        state = m_udpRecvThreadState;
    }
    catch (const boost::lock_error& e)
    {
        LOGERROR(logger, e.what());
    }

    if (state == ThreadState::NotRunning || state == ThreadState::Starting)
    {
        return true;
    }
    return false;
}

//==============================================================================

void UdpReceiveThreadEnsemble::handleReceive(const boost::system::error_code& error, std::size_t len)
{
    if (!m_timerResult)
    {
        LOGDEBUG(logger, "Received some data. Length: " << len);

        m_readResult.reset(error);

        if ((error == 0) && (len > 0))
        {
            boost::iostreams::stream<boost::iostreams::array_source> is(m_inCArrBuffer, len);
            m_sutpInterface.onReceiveRaw(is, uint32_t(len));
        }
    }
}

//==============================================================================

void UdpReceiveThreadEnsemble::sutpHandlingThreadMain()
{
    try
    {
        Lock lock(this->m_sutpMutex);
        m_sutpThreadState = ThreadState::Running;
    }
    catch (const boost::lock_error& e)
    {
        LOGERROR(logger, e.what());
    }

    boost::condition& packetComplete    = m_sutpInterface.getPacketCompleteCondition();
    boost::recursive_mutex& packetMutex = m_sutpInterface.getPacketCompleteMutex();
    while (this->m_sutpThreadState != ThreadState::Stopping)
    {
        try
        {
            boost::recursive_mutex::scoped_lock lock(packetMutex);
            packetComplete.wait(packetMutex);
        }
        catch (const boost::lock_error& e)
        {
            LOGERROR(logger, e.what());
        }

        m_sutpInterface.processCache();
    }

    try
    {
        Lock lock(this->m_sutpMutex);
        m_sutpThreadState = ThreadState::NotRunning;
    }
    catch (const boost::lock_error& e)
    {
        LOGERROR(logger, e.what());
    }

    LOGDEBUG(logger, "sutpHandlingThreadMain: I am dead!");
}

//==============================================================================

bool UdpReceiveThreadEnsemble::handleSutpMsgs(const char* bodyBuf, size_t len)
{
    Lock lock(m_sutpMutex);
    {
        boost::iostreams::array_source as(bodyBuf, len);
        boost::iostreams::stream<boost::iostreams::array_source> strm(as);
        std::istream& is = static_cast<std::istream&>(strm);

        IbeoDataHeader dh;
        if (len < IbeoDataHeader::getHeaderSize())
        {
            return false;
        }

        if (dh.deserialize(is))
        {
            if (len < dh.getMessageSize() + IbeoDataHeader::getHeaderSize())
            {
                return false;
            }
            m_receiveDataBlock(&dh, bodyBuf + IbeoDataHeader::getHeaderSize());
            return true;
        }
        return false;
    }
}

//==============================================================================

void UdpReceiveThreadEnsemble::waitHandler(const boost::system::error_code& error)
{
    if (!m_readResult)
    {
        LOGDEBUG(logger, "TimeOut Event");
    }
    m_timerResult.reset(error);
}

//==============================================================================

bool UdpReceiveThreadEnsemble::receiveWithTimeout(boost::asio::ip::udp::socket& socket,
                                                  boost::asio::ip::udp::endpoint& ep,
                                                  const boost::asio::deadline_timer::duration_type& expiryTime,
                                                  boost::system::error_code& readError)
{
    m_timerResult.reset();
    m_readResult.reset();

    std::memset(m_inCArrBuffer, 0, bufferSize);

    m_auxTimer.expires_from_now(expiryTime);
    m_auxTimer.async_wait(boost::bind(&UdpReceiveThreadEnsemble::waitHandler, this, _1));

    socket.async_receive_from(boost::asio::buffer(m_inCArrBuffer, bufferSize),
                              ep,
                              boost::bind(&UdpReceiveThreadEnsemble::handleReceive,
                                          this,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));

    socket.get_io_service().reset();
    while (socket.get_io_service().run_one())
    {
        if (m_readResult)
        {
            m_auxTimer.cancel();
        }
        else if (m_timerResult)
        {
            socket.cancel();
            if (m_stopOnTimeOut)
            {
                return false;
            }
        }
    }

    if (m_readResult && *m_readResult)
    {
        readError = *m_readResult;
    }
    else
    {
        readError = boost::system::error_code();
    }

    return true;
}

//==============================================================================

statuscodes::Codes UdpReceiveThreadEnsemble ::sendCommand(const CommandCBase&, const SpecialExporterBase<CommandCBase>&)
{
    return statuscodes::SendingCommandFailed; // UNUSED
}

//==============================================================================

statuscodes::Codes UdpReceiveThreadEnsemble ::sendCommand(const CommandCBase&,
                                                          const SpecialExporterBase<CommandCBase>&,
                                                          CommandReplyBase&,
                                                          const boost::posix_time::time_duration)
{
    return statuscodes::SendingCommandFailed; // UNUSED
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

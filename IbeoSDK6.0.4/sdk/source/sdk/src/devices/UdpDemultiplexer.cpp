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
//!\date Aug 21, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/devices/UdpDemultiplexer.hpp>

#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif // gcc or clang

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ibeo::common::logging::LoggerSPtr UdpDemultiplexer::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

boost::mutex UdpDemultiplexer::portMapMutex;
UdpDemultiplexer::PortMap UdpDemultiplexer::portMap;

//==============================================================================

UdpDemultiplexer::UdpDemultiplexerPtr UdpDemultiplexer::get(const basio::ip::udp::endpoint& localEndpoint,
                                                            const std::size_t maxBufferSize)
{
    // Port must not be zero!
    if (localEndpoint.port() == 0)
    {
        throw std::invalid_argument("Endpoint port must not be zero!");
    }

    // IP address must be IPv4!
    if (localEndpoint.address().is_v4() == false)
    {
        throw std::invalid_argument("Only IPv4 addresses are supported yet!");
    }

    boost::mutex::scoped_lock locker(portMapMutex);

    // Remove all entries from the map that are no longer alive.
    cleanPortMap();

    try
    {
        // Check if there is already an instance listening on the endpoint.
        UdpDemultiplexerPtr instance = findInstance(localEndpoint);

        if (instance == nullptr)
        {
            // Endpoint not found in map or invalid -> create a new instance.
            instance.reset(new UdpDemultiplexer(localEndpoint, maxBufferSize));
            portMap[localEndpoint] = UdpDemultiplexerWeakPtr(instance);
        }
        else
        {
            // Instance already created before -> adjust packet size to the new maximum.
            instance->adjustBufferSize(maxBufferSize);
        }

        return instance;
    }
    catch (const std::exception& exc)
    {
        LOGERROR(logger, exc.what());
        return nullptr;
    }
}

//==============================================================================

UdpDemultiplexer::UdpDemultiplexer(const basio::ip::udp::endpoint& localEndpoint, const std::size_t maxBufferSize)
  : m_udpReceiveThread(std::bind(&UdpDemultiplexer::udpReceiveThreadMain, this)),
    m_localEndpoint(localEndpoint),
    m_dataBufferSize(maxBufferSize)
{}

//==============================================================================

UdpDemultiplexer::~UdpDemultiplexer()
{
    stopThread();

    LOGTRACE(logger,
             m_nbOfRecvPackets << " packets on endpoint " << m_localEndpoint.address().to_string() << ":"
                               << m_localEndpoint.port() << " received.");
}

//==============================================================================

UdpDemultiplexer::CallbackHandle UdpDemultiplexer::registerCallback(const basio::ip::udp::endpoint remoteEndpoint,
                                                                    CallbackFunction callback)
{
    boost::mutex::scoped_lock locker(m_callbacksMutex);

    // Add callback to map.
    CallbackHandle handle = getNextCallbackHandle();

    CallbackEntry entry;
    entry.endpoint      = remoteEndpoint;
    entry.function      = callback;
    m_callbacks[handle] = entry;

    ThreadRunner::ThreadState state = m_udpReceiveThread.getThreadState();
    if (state != ThreadRunner::ThreadState::Running)
    {
        // UDP receive thread not started yet -> do it now (start blocks until thread is running).
        if (startThread() == false)
        {
            // Starting thread failed.
            m_callbacks.erase(handle);
            return nullptr;
        }
    }

    return handle;
}

//==============================================================================

bool UdpDemultiplexer::unregisterCallback(const CallbackHandle handle)
{
    boost::mutex::scoped_lock locker(m_callbacksMutex);

    Callbacks::const_iterator iter = m_callbacks.find(handle);
    if (iter == m_callbacks.end())
    {
        // Handle not found.
        return false;
    }
    else
    {
        if (m_callbacks.size() == 1)
        {
            // This is the last entry -> stop thread now.

            // The UDP thread might want to send data through the callback map before stopping -> unlock mutex
            // temporarily.
            locker.unlock();

            stopThread();

            // No thread listening on this endpoint anymore -> remove self from port map.
            {
                boost::mutex::scoped_lock portMapLocker(portMapMutex);
                for (PortMap::iterator instanceMapIter = portMap.begin(); instanceMapIter != portMap.end();
                     ++instanceMapIter)
                {
                    if (instanceMapIter->second.lock().get() == this)
                    {
                        // Entry found -> remove it.
                        portMap.erase(instanceMapIter);
                        break;
                    }
                }
            }

            // // Lock callback map again for rest of function.
            locker.lock();
        }

        // Remove entry.
        m_callbacks.erase(iter);

        return true;
    }
}

//==============================================================================

void UdpDemultiplexer::setWorkerThreadCount(const int value)
{
    if (m_udpReceiveThread.getThreadState() != ThreadRunner::ThreadState::NotRunning)
    {
        throw std::logic_error("Worker thread count cannot be set while the thread is running!");
    }

    m_workerThreadCount = value;
}

//==============================================================================

void UdpDemultiplexer::cleanPortMap()
{
    PortMap::const_iterator iter = portMap.begin();

    while (iter != portMap.end())
    {
        if (iter->second.lock() == nullptr)
        {
            // Entry is not alive anymore -> remove it.
            iter = portMap.erase(iter);
        }
        else
        {
            // Next entry.
            ++iter;
        }
    }
}

//==============================================================================

UdpDemultiplexer::UdpDemultiplexerPtr UdpDemultiplexer::findInstance(const boost::asio::ip::udp::endpoint& endpoint)
{
    for (PortMap::const_iterator iter = portMap.begin(); iter != portMap.end(); ++iter)
    {
        if (iter->first.port() != endpoint.port())
        {
            // Wrong local port -> next one.
            continue;
        }

        if ((iter->first.address() == basio::ip::address_v4::any())
            && (endpoint.address() != basio::ip::address_v4::any()))
        {
            throw std::invalid_argument("Cannot get an instance for a specific local network interface while there is "
                                        "already an instance for all local network interfaces created!");
        }

        if ((iter->first.address() != basio::ip::address_v4::any())
            && (endpoint.address() == basio::ip::address_v4::any()))
        {
            throw std::invalid_argument("Cannot get an instance for all local network interfaces while there is "
                                        "already an instance for a specific local network interface created!");
        }

        if (iter->first.address() != endpoint.address())
        {
            // Wrong local IP address -> next one.
            continue;
        }

        // Endpoint found in map.
        return iter->second.lock();
    }

    // No instance found.
    return nullptr;
}

//==============================================================================

void UdpDemultiplexer::adjustBufferSize(const std::size_t maxBufferSize)
{
    boost::mutex::scoped_lock callbacksLocker(m_callbacksMutex);
    if (m_dataBufferSize < maxBufferSize)
    {
        // Buffer too small -> can it be resized?
        if (m_callbacks.empty())
        {
            // No callbacks registered -> it is safe to resize the buffer.
            m_dataBufferSize = maxBufferSize;
        }
        else
        {
            // Callbacks already registered (i.e. UDP reception already running) -> cannot resize the buffer.
            throw std::logic_error("Cannot adjust buffer size because callbacks already registered!");
        }
    }
}

//==============================================================================

void UdpDemultiplexer::udpReceiveThreadMain()
{
    std::stringstream ss;
    ss << "UDPListen_" << m_localEndpoint.port();
    m_udpReceiveThread.setThreadName(ss.str());

    LOGTRACE(logger,
             "Thread started. Listening on endpoint " << m_localEndpoint.address().to_string() << ":"
                                                      << m_localEndpoint.port());

    if (m_udpReceiveThread.setThreadState(ThreadRunner::ThreadState::Running) == false)
    {
        // Setting thread state failed.
        return;
    }

    try
    {
        // Add enough work to the service so that each thread has two tasks pending.
        for (int ix = 0; ix < m_workerThreadCount * 2; ++ix)
        {
            addIoServiceWork();
        }

        // Start worker threads handling UDP data.
        boost::thread_group workerThreads;
        for (int ix = 0; ix < m_workerThreadCount; ++ix)
        {
            workerThreads.create_thread(boost::bind(&boost::asio::io_service::run, &m_socket->get_io_service()));
        }

        // Wait until all threads finished their work.
        workerThreads.join_all();
    }
    catch (const boost::system::error_code& errorCode)
    {
        LOGERROR(logger, "Receiving data failed! Reason: " << errorCode.message());
        m_udpReceiveThread.setThreadState(ThreadRunner::ThreadState::RunFailed);
    }

    if ((m_socket != nullptr) && (m_socket->is_open() == false)
        && (m_udpReceiveThread.getThreadState() != ThreadRunner::ThreadState::Stopping)
        && (m_udpReceiveThread.getThreadState() != ThreadRunner::ThreadState::RunFailed))
    {
        m_udpReceiveThread.setThreadState(ThreadRunner::ThreadState::Stopping);
    }

    m_udpReceiveThread.setThreadState(ThreadRunner::ThreadState::NotRunning);

    LOGTRACE(logger,
             "Thread ended. Listening on endpoint " << m_localEndpoint.address().to_string() << ":"
                                                    << m_localEndpoint.port() << " stopped.");
}

//==============================================================================

void UdpDemultiplexer::addIoServiceWork()
{
    // Create new buffer.
    DataBufferPtr dataBuffer(new std::vector<char>(m_dataBufferSize));

    // Setup IO service work for receiving UDP packets asynchronously.
    std::shared_ptr<boost::asio::ip::udp::endpoint> senderEndpoint(new boost::asio::ip::udp::endpoint());
    m_socket->async_receive_from(boost::asio::buffer(*dataBuffer),
                                 *senderEndpoint,
                                 bind(&UdpDemultiplexer::handleUdpData,
                                      this,
                                      senderEndpoint,
                                      dataBuffer,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
}

//==============================================================================

void UdpDemultiplexer::handleUdpData(const std::shared_ptr<boost::asio::ip::udp::endpoint> remoteEndpoint,
                                     const UdpDemultiplexer::DataBufferPtr& dataBuffer,
                                     const boost::system::error_code& errorCode,
                                     std::size_t recvBytes)
{
    // Add new work to receive the next packet.
    addIoServiceWork();

    if ((errorCode == 0) && (recvBytes > 0))
    {
        // Another packet received.
        ++m_nbOfRecvPackets;

        boost::mutex::scoped_lock locker(m_callbacksMutex);

        // Iterate over all callbacks.
        for (const auto& callbackMapPair : m_callbacks)
        {
            const CallbackEntry& callbackEntry = callbackMapPair.second;
            if (endpointMatches(*remoteEndpoint, callbackEntry.endpoint))
            {
                // Match found -> notify callback.
                callbackEntry.function(callbackMapPair.first, dataBuffer);
            }
        }
    }
    else
    {
        // Print warning but continue with next packet.
        LOGWARNING(logger, "Error receiving UDP packet! Reason: " << errorCode.message());
    }
}

//==============================================================================

bool UdpDemultiplexer::startThread()
{
    try
    {
        m_socket.reset(new boost::asio::ip::udp::socket(m_ioService));
    }
    catch (const std::exception& e)
    {
        LOGERROR(logger, "Failed to allocate UDP socket. reason: " << e.what());
        m_udpReceiveThread.setThreadState(ThreadRunner::ThreadState::StartFailed);
        return false;
    }

    try
    {
        m_socket->open(boost::asio::ip::udp::v4());
        m_socket->set_option(boost::asio::ip::udp::socket::reuse_address(true));
        m_socket->set_option(boost::asio::socket_base::receive_buffer_size(static_cast<int>(m_dataBufferSize)));
    }
    catch (const std::exception& e)
    {
        LOGERROR(logger, "Failed to open and configure UDP socket. Rreason: " << e.what());
        m_udpReceiveThread.setThreadState(ThreadRunner::ThreadState::StartFailed);
        return false;
    }

    try
    {
        m_socket->bind(m_localEndpoint);
    }
    catch (const std::exception& e)
    {
        LOGERROR(logger, "Failed to bind UDP socket to local endpoint. Reason: " << e.what());
        m_udpReceiveThread.setThreadState(ThreadRunner::ThreadState::StartFailed);
        return false;
    }

    m_udpReceiveThread.start();

    return true;
}

//==============================================================================

void UdpDemultiplexer::stopThread()
{
    if (m_socket != nullptr)
    {
        m_socket->get_io_service().stop();
        m_udpReceiveThread.join();

        m_socket->close();
        m_socket = nullptr;
    }
}

//==============================================================================

bool UdpDemultiplexer::endpointMatches(const basio::ip::udp::endpoint& remoteEndpoint,
                                       const basio::ip::udp::endpoint& callbackEndpoint)
{
    if ((callbackEndpoint.port() != 0) && (remoteEndpoint.port() != callbackEndpoint.port()))
    {
        // Callback is for a specific remote port, but this port was not received -> match failed.
        return false;
    }
    // else: callback is for any port, so received port does not matter.

    if ((callbackEndpoint.address().to_v4() != basio::ip::address_v4::any())
        && (remoteEndpoint.address() != callbackEndpoint.address()))
    {
        // Callback is for a specific remote address, but this address was not received -> match failed.
        return false;
    }
    // else: callback is for any IP address, so received IP address does not matter.

    return true;
}

//==============================================================================

UdpDemultiplexer::CallbackHandle UdpDemultiplexer::getNextCallbackHandle()
{
    uint32_t lastCallbackHandle = m_lastCallbackHandle;

    while (true)
    {
        ++m_lastCallbackHandle;

        if (m_lastCallbackHandle == lastCallbackHandle)
        {
            // Overflow -> all handles in use.
            throw std::logic_error("All callback handles in use!");
        }

        if (m_callbacks.find(reinterpret_cast<CallbackHandle>(m_lastCallbackHandle)) == m_callbacks.end())
        {
            // New handle not found -> it is valid.
            break;
        }
    }

    return reinterpret_cast<CallbackHandle>(m_lastCallbackHandle);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

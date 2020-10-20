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
//!\date Aug 22, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/logging/logging.hpp>
#include <deviceTests/UdpDemultiplexerTestWrapper.hpp>

#include <functional>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr
UdpDemultiplexerTestWrapper::get(const basio::ip::udp::endpoint& endpoint, const std::size_t maxBufferSize)
{
    boost::mutex::scoped_lock locker(portMapMutex);

    // Remove all entries from the map that are no longer alive.
    cleanPortMap();

    try
    {
        // Check if there is already an instance listening on the endpoint.
        UdpDeMultiplexerTestWrapperPtr instance
            = std::dynamic_pointer_cast<UdpDemultiplexerTestWrapper>(findInstance(endpoint));

        if (instance == nullptr)
        {
            // Endpoint not found in map or invalid -> create a new instance.
            instance.reset(new UdpDemultiplexerTestWrapper(endpoint, maxBufferSize));
            portMap[endpoint] = UdpDemultiplexerWeakPtr(instance);
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
        ibeo::common::logging::LogManager::getInstance().globalLogger()->error(LOGMSG << exc.what());
        return nullptr;
    }
}

//==============================================================================

UdpDemultiplexer::CallbackHandle UdpDemultiplexerTestWrapper::registerCallback(const basio::ip::udp::endpoint endpoint)
{
    return UdpDemultiplexer::registerCallback(
        endpoint,
        std::bind(&UdpDemultiplexerTestWrapper::udpDataCallback, this, std::placeholders::_1, std::placeholders::_2));
}

//==============================================================================

void UdpDemultiplexerTestWrapper::pushData(const basio::ip::udp::endpoint remoteEndpoint,
                                           const std::vector<char>& udpData,
                                           const boost::system::error_code& errorCode)
{
    DataEntryPtr dataEntry{new DataEntry()};
    dataEntry->remoteEndpoint
        = std::shared_ptr<boost::asio::ip::udp::endpoint>(new boost::asio::ip::udp::endpoint(remoteEndpoint));
    dataEntry->udpData   = DataBufferPtr(new std::vector<char>(udpData));
    dataEntry->errorCode = errorCode;

    m_dataQueue.push(dataEntry);
}

//==============================================================================

std::size_t UdpDemultiplexerTestWrapper::getNbOfReceivedUdpDataBlocks() const
{
    std::size_t count{0};
    for (const auto& keyValuePair : m_dataBufferMap)
    {
        count += keyValuePair.second.size();
    }

    return count;
}

//==============================================================================

UdpDemultiplexerTestWrapper::DataBufferVector
UdpDemultiplexerTestWrapper::getUpdDataBuffers(const CallbackHandle handle) const
{
    DataBufferMap::const_iterator iter = m_dataBufferMap.find(handle);
    if (iter == m_dataBufferMap.end())
    {
        // Not found -< empty element.
        return DataBufferVector();
    }
    else
    {
        return iter->second;
    }
}

//==============================================================================

void UdpDemultiplexerTestWrapper::udpReceiveThreadMain()
{
    ibeo::common::logging::LogManager::getInstance().globalLogger()->debug(LOGMSG << "Thread started.");

    if (m_udpReceiveThread.setThreadState(ThreadRunner::ThreadState::Running) == false)
    {
        // Setting thread state failed.
        return;
    }

    // Main loop.
    while (true)
    {
        DataEntryPtr dataEntry;
        m_dataQueue.pop(dataEntry);

        if (dataEntry == nullptr)
        {
            // Null-data received -> terminate thread.
            break;
        }

        handleUdpData(dataEntry->remoteEndpoint, dataEntry->udpData, dataEntry->errorCode, dataEntry->udpData->size());
    }

    if ((m_udpReceiveThread.getThreadState() != ThreadRunner::ThreadState::Stopping)
        && (m_udpReceiveThread.getThreadState() != ThreadRunner::ThreadState::RunFailed))
    {
        m_udpReceiveThread.setThreadState(ThreadRunner::ThreadState::Stopping);
    }

    m_udpReceiveThread.setThreadState(ThreadRunner::ThreadState::NotRunning);

    ibeo::common::logging::LogManager::getInstance().globalLogger()->debug(LOGMSG << "Thread ended.");
}

//==============================================================================

void UdpDemultiplexerTestWrapper::addIoServiceWork()
{
    // No sockets used in test class -> no need to add work to the IO service.
    return;
}

//==============================================================================

bool UdpDemultiplexerTestWrapper::startThread()
{
    m_udpReceiveThread.start();
    return true;
}

//==============================================================================

void UdpDemultiplexerTestWrapper::stopThread()
{
    m_dataQueue.push(nullptr);
    m_udpReceiveThread.join();
}

//==============================================================================

void UdpDemultiplexerTestWrapper::udpDataCallback(const CallbackHandle handle, const DataBufferPtr& udpData)
{
    DataBufferMap::iterator iter = m_dataBufferMap.find(handle);
    if (iter == m_dataBufferMap.end())
    {
        // No entry for this handle yet -> create empty element.
        m_dataBufferMap[handle] = DataBufferVector();
        iter                    = m_dataBufferMap.find(handle);
    }

    // Add data buffer to this handle.
    iter->second.push_back(*udpData);
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

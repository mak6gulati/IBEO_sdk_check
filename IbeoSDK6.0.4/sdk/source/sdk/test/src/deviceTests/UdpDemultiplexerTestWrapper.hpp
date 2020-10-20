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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/UdpDemultiplexer.hpp>
#include <ibeo/common/sdk/misc/BlockingQueue.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class UdpDemultiplexerTestWrapper : public UdpDemultiplexer
{
public:
    using UdpDeMultiplexerTestWrapperPtr = std::shared_ptr<UdpDemultiplexerTestWrapper>;
    using DataBufferVector               = std::vector<std::vector<char>>;
    using DataBufferMap                  = std::map<const CallbackHandle, DataBufferVector>;

public:
    static UdpDeMultiplexerTestWrapperPtr get(const basio::ip::udp::endpoint& endpoint,
                                              const std::size_t maxBufferSize);
    virtual ~UdpDemultiplexerTestWrapper() { stopThread(); }

    CallbackHandle registerCallback(const basio::ip::udp::endpoint endpoint);

    void pushData(const basio::ip::udp::endpoint remoteEndpoint,
                  const std::vector<char>& udpData,
                  const boost::system::error_code& errorCode = boost::system::error_code());

    std::size_t getNbOfReceivedUdpDataBlocks() const;
    DataBufferVector getUpdDataBuffers(const CallbackHandle handle) const;
    ThreadRunner::ThreadState getThreadState() const { return m_udpReceiveThread.getThreadState(); }

protected:
    UdpDemultiplexerTestWrapper(const basio::ip::udp::endpoint& localEndpoint, const std::size_t maxPacketSize)
      : UdpDemultiplexer(localEndpoint, maxPacketSize), m_dataQueue(1024)
    {}

    void udpReceiveThreadMain() override;
    void addIoServiceWork() override;
    bool startThread() override;
    void stopThread() override;

    void udpDataCallback(const CallbackHandle handle, const DataBufferPtr& udpData);

private:
    struct DataEntry
    {
        std::shared_ptr<basio::ip::udp::endpoint> remoteEndpoint;
        DataBufferPtr udpData;
        boost::system::error_code errorCode;
    };
    using DataEntryPtr = std::shared_ptr<DataEntry>;

private:
    BlockingQueue<DataEntryPtr> m_dataQueue;
    DataBufferMap m_dataBufferMap;
}; // UdpDemultiplexerTestWrapper

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

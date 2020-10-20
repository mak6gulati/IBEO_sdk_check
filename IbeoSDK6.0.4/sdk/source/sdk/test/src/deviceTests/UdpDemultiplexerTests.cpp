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
//! \date Aug 22, 2018
//------------------------------------------------------------------------------

#include <deviceTests/UdpDemultiplexerTestWrapper.hpp>
#include <common/TestSupport.hpp>

#include <ibeo/common/logging/logging.hpp>

#define BOOST_TEST_MODULE UdpDeMultiplexerTests
#include <boost/test/unit_test.hpp>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <chrono>
#include <thread>

//==============================================================================
using namespace ibeo::common::sdk;
using namespace ibeo::common::logging;
using namespace boost::interprocess;
//==============================================================================

BOOST_AUTO_TEST_SUITE(UdpDemultiplexerTestSuite)

//==============================================================================

static const uint16_t localPortNumberBase{50000};
static const uint16_t remotePortNumber1{54321};
static const uint16_t remotePortNumber2{54322};
static const char* const sharedMemoryName{"ibeo_common_sdk_unittests_UdpDemultiplexerTestSuite"};

//==============================================================================

class Fixture
{
public:
    Fixture() : m_sharedMemory{open_or_create, sharedMemoryName, read_write}
    {
        ibeo::common::logging::LogManager::getInstance().setDefaultLogLevel(ibeo::common::logging::LogLevel::Debug);

        // Initialize shared memory.
        offset_t shmSize;
        m_sharedMemory.get_size(shmSize);
        if (shmSize == 0)
        {
            // Shared memory not created yet -> do it now.
            m_sharedMemory.truncate(sizeof(uint16_t));

            // Create shared memory region.
            mapped_region region{m_sharedMemory, read_write};

            // Initialize last port number.
            uint16_t* memPtr = static_cast<uint16_t*>(region.get_address());
            *memPtr          = localPortNumberBase;

            LOGINFO(logger, "Shared memory created, local port initialized to " << localPortNumberBase << ".");
        }
        else
        {
            LOGINFO(logger, "Shared memory already exists.");
        }
    }

    virtual ~Fixture()
    {
        // Release shared memory.
        shared_memory_object::remove(sharedMemoryName);

        LOGINFO(logger, "Shared memory deleted.");
    }

protected:
    static void printTestName()
    {
        BOOST_TEST_MESSAGE("***" << boost::unit_test::framework::current_test_case().p_name << " ***");
    }

    uint16_t getNextLocalPortNumber()
    {
        // Read last port number from shared memory.
        uint16_t portNumber;
        mapped_region region{m_sharedMemory, read_write};
        uint16_t* memPtr = static_cast<uint16_t*>(region.get_address());
        portNumber       = *memPtr;

        LOGINFO(logger, "Last used port from shared memory is " << portNumber << ".");

        // Increment it.
        ++portNumber;

        // Store it back in shared memory.
        *memPtr = portNumber;

        return portNumber;
    }

    static void printLocalPorts(const uint16_t portNo1, const uint16_t portNo2 = 0)
    {
        std::stringstream stream;
        if (portNo2 == 0)
        {
            stream << "Using local port " << portNo1;
        }
        else
        {
            stream << "Using local ports " << portNo1 << " and " << portNo2;
        }

        LOGINFO(logger, stream.str().c_str());
    }

protected:
    static LoggerSPtr logger;

private:
    shared_memory_object m_sharedMemory;
}; // Fixture

//==============================================================================

LoggerSPtr Fixture::logger{
    LogManager::getInstance().createLogger("ibeo::common::sdk::unittests::UdpDemultiplexerTestSuite")};

//==============================================================================

BOOST_FIXTURE_TEST_CASE(getInstance, Fixture)
{
    printTestName();

    constexpr std::size_t maxDataSize{256};
    basio::ip::udp::endpoint localEndpoint(basio::ip::address_v4::any(), 1234);

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint, maxDataSize);
    BOOST_CHECK(demux);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux->getThreadState()),
                      static_cast<uint8_t>(ThreadRunner::ThreadState::NotRunning));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(registerCallback, Fixture)
{
    constexpr std::size_t maxDataSize{256};
    basio::ip::udp::endpoint localEndpoint(basio::ip::address_v4::any(), 1234);
    basio::ip::udp::endpoint remoteEndpoint(basio::ip::address_v4::any(), remotePortNumber1);

    printTestName();
    printLocalPorts(localEndpoint.port());

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint, maxDataSize);
    BOOST_CHECK(demux);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux->getThreadState()),
                      static_cast<uint8_t>(ThreadRunner::ThreadState::NotRunning));

    UdpDemultiplexer::CallbackHandle handle = demux->registerCallback(remoteEndpoint);
    BOOST_CHECK(handle);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux->getThreadState()),
                      static_cast<uint8_t>(ThreadRunner::ThreadState::Running));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(getMultipleInstancesAnyAddress, Fixture)
{
    constexpr std::size_t maxDataSize{256};
    const basio::ip::address_v4 anyAddress{basio::ip::address_v4::any()};

    basio::ip::udp::endpoint localEndpoint1 = basio::ip::udp::endpoint(anyAddress, getNextLocalPortNumber());
    basio::ip::udp::endpoint localEndpoint2 = basio::ip::udp::endpoint(anyAddress, getNextLocalPortNumber());

    printTestName();
    printLocalPorts(localEndpoint1.port(), localEndpoint2.port());

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux1
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint1, maxDataSize);
    BOOST_CHECK(demux1);

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux2
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint2, maxDataSize);
    BOOST_CHECK(demux2);

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux3
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint1, maxDataSize);
    BOOST_CHECK(demux2);

    // 1 <-> 2: Different endpoints -> different instances.
    BOOST_CHECK_NE(demux1.get(), demux2.get());

    // 1 <-> 3: Same endpoints -> same instances.
    BOOST_CHECK_EQUAL(demux1.get(), demux3.get());

    // 2 <-> 3: Different endpoints -> different instances.
    BOOST_CHECK_NE(demux2.get(), demux3.get());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(getMultipleInstancesSpecificAddress, Fixture)
{
    constexpr std::size_t maxDataSize{256};
    const uint16_t localPort1{getNextLocalPortNumber()};
    const uint16_t localPort2{getNextLocalPortNumber()};
    const basio::ip::address_v4 localAddress1{basio::ip::address_v4::from_string("1.2.3.4")};
    const basio::ip::address_v4 localAddress2{basio::ip::address_v4::from_string("2.3.4.5")};

    basio::ip::udp::endpoint localEndpoint11 = basio::ip::udp::endpoint(localAddress1, localPort1);
    basio::ip::udp::endpoint localEndpoint12 = basio::ip::udp::endpoint(localAddress1, localPort2);
    basio::ip::udp::endpoint localEndpoint21 = basio::ip::udp::endpoint(localAddress2, localPort1);
    basio::ip::udp::endpoint localEndpoint22 = basio::ip::udp::endpoint(localAddress2, localPort2);

    printTestName();
    printLocalPorts(localPort1, localPort2);

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux11
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint11, maxDataSize);
    BOOST_CHECK(demux11);

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux12
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint12, maxDataSize);
    BOOST_CHECK(demux12);

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux13
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint11, maxDataSize);
    BOOST_CHECK(demux13);

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux21
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint21, maxDataSize);
    BOOST_CHECK(demux21);

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux22
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint22, maxDataSize);
    BOOST_CHECK(demux22);

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux23
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint21, maxDataSize);
    BOOST_CHECK(demux23);

    BOOST_CHECK_NE(demux11.get(), demux12.get());
    BOOST_CHECK_EQUAL(demux11.get(), demux13.get());
    BOOST_CHECK_NE(demux11.get(), demux21.get());
    BOOST_CHECK_NE(demux11.get(), demux22.get());
    BOOST_CHECK_NE(demux11.get(), demux23.get());

    BOOST_CHECK_NE(demux12.get(), demux13.get());
    BOOST_CHECK_NE(demux12.get(), demux21.get());
    BOOST_CHECK_NE(demux12.get(), demux22.get());
    BOOST_CHECK_NE(demux12.get(), demux23.get());

    BOOST_CHECK_NE(demux13.get(), demux21.get());
    BOOST_CHECK_NE(demux13.get(), demux22.get());
    BOOST_CHECK_NE(demux13.get(), demux23.get());

    BOOST_CHECK_NE(demux21.get(), demux22.get());
    BOOST_CHECK_EQUAL(demux21.get(), demux23.get());

    BOOST_CHECK_NE(demux22.get(), demux23.get());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(getInvalidInstances1, Fixture)
{
    constexpr std::size_t maxDataSize{256};
    const uint16_t localPort1{getNextLocalPortNumber()};
    const uint16_t localPort2{getNextLocalPortNumber()};
    const basio::ip::address_v4 localAddress{basio::ip::address_v4::from_string("1.2.3.4")};
    const basio::ip::address_v4 anyAddress{basio::ip::address_v4::any()};

    basio::ip::udp::endpoint localEndpoint1 = basio::ip::udp::endpoint(localAddress, localPort1);
    basio::ip::udp::endpoint localEndpoint2 = basio::ip::udp::endpoint(anyAddress, localPort1);
    basio::ip::udp::endpoint localEndpoint3 = basio::ip::udp::endpoint(anyAddress, localPort2);

    printTestName();
    printLocalPorts(localPort1, localPort2);

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux1
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint1, maxDataSize);
    BOOST_CHECK(demux1);

    // Getting an instance for any address IS NOT allowed if there is already an instance registered for a specific
    // address on the same port.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux2
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint2, maxDataSize);
    BOOST_CHECK(demux2 == nullptr);

    // Getting an instance for any address IS allowed if there is already an instance registered for a specific
    // address but on a different port.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux3
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint3, maxDataSize);
    BOOST_CHECK(demux3);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(getInvalidInstances2, Fixture)
{
    constexpr std::size_t maxDataSize{256};
    const uint16_t localPort1{getNextLocalPortNumber()};
    const uint16_t localPort2{getNextLocalPortNumber()};
    const basio::ip::address_v4 localAddress{basio::ip::address_v4::from_string("1.2.3.4")};
    const basio::ip::address_v4 anyAddress{basio::ip::address_v4::any()};

    basio::ip::udp::endpoint localEndpoint1 = basio::ip::udp::endpoint(anyAddress, localPort1);
    basio::ip::udp::endpoint localEndpoint2 = basio::ip::udp::endpoint(localAddress, localPort1);
    basio::ip::udp::endpoint localEndpoint3 = basio::ip::udp::endpoint(localAddress, localPort2);

    printTestName();
    printLocalPorts(localPort1, localPort2);

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux1
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint1, maxDataSize);
    BOOST_CHECK(demux1);

    // Getting an instance for a specific address IS NOT allowed if there is already an instance registered for any
    // address on the same port.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux2
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint2, maxDataSize);
    BOOST_CHECK(demux2 == nullptr);

    // Getting an instance for a soecific address IS allowed if there is already an instance registered for any
    // address but on a different port.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux3
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint3, maxDataSize);
    BOOST_CHECK(demux3);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(useDifferentPacketSizesNoRegistrations, Fixture)
{
    constexpr std::size_t maxDataSize{256};
    const std::size_t dataSizeOffset{64}; // Shall be lower than maxDataSize!
    const basio::ip::address_v4 anyAddress{basio::ip::address_v4::any()};

    basio::ip::udp::endpoint localEndpoint = basio::ip::udp::endpoint(anyAddress, getNextLocalPortNumber());

    printTestName();
    printLocalPorts(localEndpoint.port());

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux1
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint, maxDataSize);
    BOOST_CHECK(demux1);

    // Using a smaller data size is always allowed.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux2
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint, maxDataSize - dataSizeOffset);
    BOOST_CHECK(demux2);

    // Using a bigger data size is allowed as long as there is no callback registered.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux3
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint, maxDataSize + dataSizeOffset);
    BOOST_CHECK(demux3);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(useDifferentPacketSizesWithRegistration, Fixture)
{
    printTestName();

    constexpr std::size_t maxDataSize{256};
    constexpr std::size_t dataSizeOffset{64}; // Shall be lower than maxDataSize!
    const uint16_t localPort1{getNextLocalPortNumber()};
    const uint16_t localPort2{getNextLocalPortNumber()};
    const basio::ip::address_v4 anyAddress{basio::ip::address_v4::any()};

    basio::ip::udp::endpoint localEndpoint1 = basio::ip::udp::endpoint(anyAddress, localPort1);
    basio::ip::udp::endpoint localEndpoint2 = basio::ip::udp::endpoint(anyAddress, localPort2);
    basio::ip::udp::endpoint remoteEndpoint(anyAddress, remotePortNumber1);

    printTestName();
    printLocalPorts(localEndpoint1.port(), localEndpoint2.port());

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux1
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint1, maxDataSize);
    BOOST_CHECK(demux1);

    // Register callback.
    UdpDemultiplexer::CallbackHandle handle = demux1->registerCallback(remoteEndpoint);
    BOOST_CHECK(handle);

    // Using a smaller data size is always allowed.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux2
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint1, maxDataSize - dataSizeOffset);
    BOOST_CHECK(demux2);

    // Using a bigger data size is not allowed if there is a callback registered.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux3
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint1, maxDataSize + dataSizeOffset);
    BOOST_CHECK(demux3 == nullptr);

    // But using a bigger data size is allowed even if there is a callback registered if it is for a different endpoint.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux4
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint2, maxDataSize + dataSizeOffset);
    BOOST_CHECK(demux4);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkSingleInstanceSingleCallback, Fixture)
{
    basio::ip::udp::endpoint localEndpoint(basio::ip::address_v4::any(), getNextLocalPortNumber());
    basio::ip::udp::endpoint remoteEndpoint(basio::ip::address_v4::any(), remotePortNumber1);

    printTestName();
    printLocalPorts(localEndpoint.port());

    // Get instance.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint, 1000);
    BOOST_CHECK(demux);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux->getThreadState()),
                      static_cast<uint8_t>(ThreadRunner::ThreadState::NotRunning));

    // Register callback.
    UdpDemultiplexer::CallbackHandle handle = demux->registerCallback(remoteEndpoint);
    BOOST_CHECK(handle);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux->getThreadState()),
                      static_cast<uint8_t>(ThreadRunner::ThreadState::Running));

    // Send some data.
    std::vector<char> udpData(256);
    unittests::TestSupport::fillVectorRandomly<char>(udpData);
    demux->pushData(remoteEndpoint, udpData);

    // Let other threads do their work (~10ms).
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Compare received data.
    BOOST_CHECK_EQUAL(demux->getNbOfReceivedUdpDataBlocks(), 1);

    unittests::UdpDemultiplexerTestWrapper::DataBufferVector udpDataBuffers = demux->getUpdDataBuffers(handle);
    BOOST_CHECK_EQUAL(udpDataBuffers.size(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(udpDataBuffers[0].begin(), udpDataBuffers[0].end(), udpData.begin(), udpData.end());

    // Unregister callback.
    demux->unregisterCallback(handle);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux->getThreadState()),
                      static_cast<uint8_t>(ThreadRunner::ThreadState::NotRunning));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkSingleInstanceMultipleCallbacks, Fixture)
{
    printTestName();

    constexpr std::size_t maxDataSize{256};
    const basio::ip::address_v4 remoteAddress1{basio::ip::address_v4::from_string("1.2.3.4")};
    const basio::ip::address_v4 remoteAddress2{basio::ip::address_v4::from_string("2.3.4.5")};
    const basio::ip::address_v4 anyAddress{basio::ip::address_v4::any()};

    basio::ip::udp::endpoint localEndpoint(basio::ip::address_v4::any(), getNextLocalPortNumber());

    std::map<std::string, basio::ip::udp::endpoint> remoteEndpoints;
    remoteEndpoints["AnyAddressAnyPort"]       = basio::ip::udp::endpoint(anyAddress, 0);
    remoteEndpoints["AnyAddressSinglePort1"]   = basio::ip::udp::endpoint(anyAddress, remotePortNumber1);
    remoteEndpoints["AnyAddressSinglePort2"]   = basio::ip::udp::endpoint(anyAddress, remotePortNumber2);
    remoteEndpoints["SingleAddress1AnyPort"]   = basio::ip::udp::endpoint(remoteAddress1, 0);
    remoteEndpoints["SingleAddress2AnyPort"]   = basio::ip::udp::endpoint(remoteAddress2, 0);
    remoteEndpoints["SingleAddressSinglePort"] = basio::ip::udp::endpoint(remoteAddress1, remotePortNumber1);

    printTestName();
    printLocalPorts(localEndpoint.port());

    // Get instance.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint, maxDataSize);
    BOOST_CHECK(demux);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux->getThreadState()),
                      static_cast<uint8_t>(ThreadRunner::ThreadState::NotRunning));

    // Register callbacks.
    using HandleMap = std::map<std::string, UdpDemultiplexer::CallbackHandle>;
    HandleMap handleMap;

    for (const auto& keyValuePair : remoteEndpoints)
    {
        UdpDemultiplexer::CallbackHandle handle;

        handle = demux->registerCallback(keyValuePair.second);
        BOOST_CHECK(handle);
        handleMap[keyValuePair.first] = handle;
        BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux->getThreadState()),
                          static_cast<uint8_t>(ThreadRunner::ThreadState::Running));
    }

    // Initialize expected data buffer.
    unittests::UdpDemultiplexerTestWrapper::DataBufferMap expDataBufferMap;
    for (const auto& keyValuePair : handleMap)
    {
        expDataBufferMap[keyValuePair.second] = unittests::UdpDemultiplexerTestWrapper::DataBufferVector();
    }

    // Send some data.
    std::vector<char> udpData(maxDataSize);

    unittests::TestSupport::fillVectorRandomly<char>(udpData);
    demux->pushData(basio::ip::udp::endpoint(remoteAddress1, remotePortNumber1), udpData);
    expDataBufferMap[handleMap["AnyAddressAnyPort"]].push_back(udpData);
    expDataBufferMap[handleMap["AnyAddressSinglePort1"]].push_back(udpData);
    expDataBufferMap[handleMap["SingleAddress1AnyPort"]].push_back(udpData);
    expDataBufferMap[handleMap["SingleAddressSinglePort"]].push_back(udpData);

    unittests::TestSupport::fillVectorRandomly<char>(udpData);
    demux->pushData(basio::ip::udp::endpoint(remoteAddress1, remotePortNumber2), udpData);
    expDataBufferMap[handleMap["AnyAddressAnyPort"]].push_back(udpData);
    expDataBufferMap[handleMap["AnyAddressSinglePort2"]].push_back(udpData);
    expDataBufferMap[handleMap["SingleAddress1AnyPort"]].push_back(udpData);

    unittests::TestSupport::fillVectorRandomly<char>(udpData);
    demux->pushData(basio::ip::udp::endpoint(remoteAddress2, remotePortNumber1), udpData);
    expDataBufferMap[handleMap["AnyAddressAnyPort"]].push_back(udpData);
    expDataBufferMap[handleMap["AnyAddressSinglePort1"]].push_back(udpData);
    expDataBufferMap[handleMap["SingleAddress2AnyPort"]].push_back(udpData);

    unittests::TestSupport::fillVectorRandomly<char>(udpData);
    demux->pushData(basio::ip::udp::endpoint(remoteAddress2, remotePortNumber2), udpData);
    expDataBufferMap[handleMap["AnyAddressAnyPort"]].push_back(udpData);
    expDataBufferMap[handleMap["AnyAddressSinglePort2"]].push_back(udpData);
    expDataBufferMap[handleMap["SingleAddress2AnyPort"]].push_back(udpData);

    // Let other threads do their work (~10ms).
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Compare received data.
    std::size_t expNbOfReceivedUdpDataBlocks{0};
    for (const auto& keyValuePair : expDataBufferMap)
    {
        expNbOfReceivedUdpDataBlocks += keyValuePair.second.size();
    }
    BOOST_CHECK_EQUAL(demux->getNbOfReceivedUdpDataBlocks(), expNbOfReceivedUdpDataBlocks);

    for (const auto& keyValuePair : expDataBufferMap)
    {
        unittests::UdpDemultiplexerTestWrapper::DataBufferVector recDataBuffers
            = demux->getUpdDataBuffers(keyValuePair.first);

        BOOST_CHECK_EQUAL(recDataBuffers.size(), keyValuePair.second.size());

        for (std::size_t i = 0; i < recDataBuffers.size(); ++i)
        {
            BOOST_CHECK_EQUAL_COLLECTIONS(recDataBuffers[i].begin(),
                                          recDataBuffers[i].end(),
                                          keyValuePair.second[i].begin(),
                                          keyValuePair.second[i].end());
        }
    }

    // Unregister callbacks.
    HandleMap::const_iterator iter;
    std::size_t i;
    for (iter = handleMap.begin(), i = 0; iter != handleMap.end(); ++iter, ++i)
    {
        demux->unregisterCallback(iter->second);
        if (i == handleMap.size() - 1)
        {
            BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux->getThreadState()),
                              static_cast<uint8_t>(ThreadRunner::ThreadState::NotRunning));
        }
        else
        {
            BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux->getThreadState()),
                              static_cast<uint8_t>(ThreadRunner::ThreadState::Running));
        }
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkMultipleInstancesMultipleCallbacks, Fixture)
{
    constexpr std::size_t maxDataSize{256};
    const uint16_t localPort1{getNextLocalPortNumber()};
    const uint16_t localPort2{getNextLocalPortNumber()};
    const basio::ip::address_v4 remoteAddress1{basio::ip::address_v4::from_string("1.2.3.4")};
    const basio::ip::address_v4 remoteAddress2{basio::ip::address_v4::from_string("2.3.4.5")};
    const basio::ip::address_v4 anyAddress{basio::ip::address_v4::any()};

    basio::ip::udp::endpoint localEndpoint1(basio::ip::address_v4::any(), localPort1);
    basio::ip::udp::endpoint localEndpoint2(basio::ip::address_v4::any(), localPort2);

    std::map<std::string, basio::ip::udp::endpoint> remoteEndpoints;
    remoteEndpoints["AnyAddressAnyPort"]       = basio::ip::udp::endpoint(anyAddress, 0);
    remoteEndpoints["AnyAddressSinglePort1"]   = basio::ip::udp::endpoint(anyAddress, remotePortNumber1);
    remoteEndpoints["AnyAddressSinglePort2"]   = basio::ip::udp::endpoint(anyAddress, remotePortNumber2);
    remoteEndpoints["SingleAddress1AnyPort"]   = basio::ip::udp::endpoint(remoteAddress1, 0);
    remoteEndpoints["SingleAddress2AnyPort"]   = basio::ip::udp::endpoint(remoteAddress2, 0);
    remoteEndpoints["SingleAddressSinglePort"] = basio::ip::udp::endpoint(remoteAddress1, remotePortNumber1);

    printTestName();
    printLocalPorts(localPort1, localPort2);

    // Get instances.
    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux1
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint1, maxDataSize);
    BOOST_CHECK(demux1);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux1->getThreadState()),
                      static_cast<uint8_t>(ThreadRunner::ThreadState::NotRunning));

    unittests::UdpDemultiplexerTestWrapper::UdpDeMultiplexerTestWrapperPtr demux2
        = unittests::UdpDemultiplexerTestWrapper::get(localEndpoint2, maxDataSize);
    BOOST_CHECK(demux2);
    BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux2->getThreadState()),
                      static_cast<uint8_t>(ThreadRunner::ThreadState::NotRunning));

    // Different local ports -> different instances.
    BOOST_CHECK_NE(demux1.get(), demux2.get());

    // Register callbacks.
    using HandleMap = std::map<std::string, UdpDemultiplexer::CallbackHandle>;
    HandleMap handleMap1;
    HandleMap handleMap2;

    for (const auto& keyValuePair : remoteEndpoints)
    {
        UdpDemultiplexer::CallbackHandle handle;

        handle = demux1->registerCallback(keyValuePair.second);
        BOOST_CHECK(handle);
        handleMap1[keyValuePair.first] = handle;
        BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux1->getThreadState()),
                          static_cast<uint8_t>(ThreadRunner::ThreadState::Running));

        handle = demux2->registerCallback(keyValuePair.second);
        BOOST_CHECK(handle);
        handleMap2[keyValuePair.first] = handle;
        BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux2->getThreadState()),
                          static_cast<uint8_t>(ThreadRunner::ThreadState::Running));
    }

    // Initialize expected data buffer.
    unittests::UdpDemultiplexerTestWrapper::DataBufferMap expDataBufferMap1;
    for (const auto& keyValuePair : handleMap1)
    {
        expDataBufferMap1[keyValuePair.second] = unittests::UdpDemultiplexerTestWrapper::DataBufferVector();
    }
    unittests::UdpDemultiplexerTestWrapper::DataBufferMap expDataBufferMap2;
    for (const auto& keyValuePair : handleMap2)
    {
        expDataBufferMap2[keyValuePair.second] = unittests::UdpDemultiplexerTestWrapper::DataBufferVector();
    }

    // Send some data.
    std::vector<char> udpData(maxDataSize);

    unittests::TestSupport::fillVectorRandomly<char>(udpData);
    demux1->pushData(basio::ip::udp::endpoint(remoteAddress1, remotePortNumber1), udpData);
    expDataBufferMap1[handleMap1["AnyAddressAnyPort"]].push_back(udpData);
    expDataBufferMap1[handleMap1["AnyAddressSinglePort1"]].push_back(udpData);
    expDataBufferMap1[handleMap1["SingleAddress1AnyPort"]].push_back(udpData);
    expDataBufferMap1[handleMap1["SingleAddressSinglePort"]].push_back(udpData);

    unittests::TestSupport::fillVectorRandomly<char>(udpData);
    demux1->pushData(basio::ip::udp::endpoint(remoteAddress1, remotePortNumber2), udpData);
    expDataBufferMap1[handleMap1["AnyAddressAnyPort"]].push_back(udpData);
    expDataBufferMap1[handleMap1["AnyAddressSinglePort2"]].push_back(udpData);
    expDataBufferMap1[handleMap1["SingleAddress1AnyPort"]].push_back(udpData);

    unittests::TestSupport::fillVectorRandomly<char>(udpData);
    demux2->pushData(basio::ip::udp::endpoint(remoteAddress2, remotePortNumber1), udpData);
    expDataBufferMap2[handleMap2["AnyAddressAnyPort"]].push_back(udpData);
    expDataBufferMap2[handleMap2["AnyAddressSinglePort1"]].push_back(udpData);
    expDataBufferMap2[handleMap2["SingleAddress2AnyPort"]].push_back(udpData);

    unittests::TestSupport::fillVectorRandomly<char>(udpData);
    demux2->pushData(basio::ip::udp::endpoint(remoteAddress2, remotePortNumber2), udpData);
    expDataBufferMap2[handleMap2["AnyAddressAnyPort"]].push_back(udpData);
    expDataBufferMap2[handleMap2["AnyAddressSinglePort2"]].push_back(udpData);
    expDataBufferMap2[handleMap2["SingleAddress2AnyPort"]].push_back(udpData);

    // Let other threads do their work (~10ms).
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Compare received data.
    std::size_t expNbOfReceivedUdpDataBlocks1{0};
    for (const auto& keyValuePair : expDataBufferMap1)
    {
        expNbOfReceivedUdpDataBlocks1 += keyValuePair.second.size();
    }
    BOOST_CHECK_EQUAL(demux1->getNbOfReceivedUdpDataBlocks(), expNbOfReceivedUdpDataBlocks1);

    std::size_t expNbOfReceivedUdpDataBlocks2{0};
    for (const auto& keyValuePair : expDataBufferMap2)
    {
        expNbOfReceivedUdpDataBlocks2 += keyValuePair.second.size();
    }
    BOOST_CHECK_EQUAL(demux2->getNbOfReceivedUdpDataBlocks(), expNbOfReceivedUdpDataBlocks2);

    for (const auto& keyValuePair : expDataBufferMap1)
    {
        unittests::UdpDemultiplexerTestWrapper::DataBufferVector recDataBuffers
            = demux1->getUpdDataBuffers(keyValuePair.first);

        BOOST_CHECK_EQUAL(recDataBuffers.size(), keyValuePair.second.size());

        for (std::size_t i = 0; i < recDataBuffers.size(); ++i)
        {
            BOOST_CHECK_EQUAL_COLLECTIONS(recDataBuffers[i].begin(),
                                          recDataBuffers[i].end(),
                                          keyValuePair.second[i].begin(),
                                          keyValuePair.second[i].end());
        }
    }

    for (const auto& keyValuePair : expDataBufferMap2)
    {
        unittests::UdpDemultiplexerTestWrapper::DataBufferVector recDataBuffers
            = demux2->getUpdDataBuffers(keyValuePair.first);

        BOOST_CHECK_EQUAL(recDataBuffers.size(), keyValuePair.second.size());

        for (std::size_t i = 0; i < recDataBuffers.size(); ++i)
        {
            BOOST_CHECK_EQUAL_COLLECTIONS(recDataBuffers[i].begin(),
                                          recDataBuffers[i].end(),
                                          keyValuePair.second[i].begin(),
                                          keyValuePair.second[i].end());
        }
    }

    // Unregister callbacks.
    HandleMap::const_iterator iter;
    std::size_t i;
    for (iter = handleMap1.begin(), i = 0; iter != handleMap1.end(); ++iter, ++i)
    {
        demux1->unregisterCallback(iter->second);
        if (i == handleMap1.size() - 1)
        {
            BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux1->getThreadState()),
                              static_cast<uint8_t>(ThreadRunner::ThreadState::NotRunning));
        }
        else
        {
            BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux1->getThreadState()),
                              static_cast<uint8_t>(ThreadRunner::ThreadState::Running));
        }
    }

    for (iter = handleMap2.begin(), i = 0; iter != handleMap2.end(); ++iter, ++i)
    {
        demux2->unregisterCallback(iter->second);
        if (i == handleMap2.size() - 1)
        {
            BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux2->getThreadState()),
                              static_cast<uint8_t>(ThreadRunner::ThreadState::NotRunning));
        }
        else
        {
            BOOST_CHECK_EQUAL(static_cast<uint8_t>(demux2->getThreadState()),
                              static_cast<uint8_t>(ThreadRunner::ThreadState::Running));
        }
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

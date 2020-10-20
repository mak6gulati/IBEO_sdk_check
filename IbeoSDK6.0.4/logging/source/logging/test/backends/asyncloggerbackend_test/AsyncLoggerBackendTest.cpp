//==============================================================================
//! \file
//!\brief Test for AsyncLoggerBackend class.
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Nov 06, 2018
//------------------------------------------------------------------------------

#define BOOST_TEST_MODULE AsyncLoggerBackendTest

//==============================================================================

#include <boost/test/unit_test.hpp>

#include <ibeo/common/logging/logging.hpp>
#include <TestSupport.hpp>

//==============================================================================

using namespace ibeo::common::logging;

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
namespace unittest {
//==============================================================================

class CustomLoggerBackend : public AsyncLoggerBackend
{
public:
    constexpr static const char* const backendId{"CustomLoggerBackend"};

public:
    CustomLoggerBackend(const std::string& backendId) : AsyncLoggerBackend{backendId} {}

    virtual ~CustomLoggerBackend() = default;

public:
    void setProcessingDelay(const std::chrono::milliseconds& processingDelay) { m_processingDelay = processingDelay; }

    std::size_t getNbOfReceivedMessages() const
    {
        std::unique_lock<std::mutex> guard(m_mutex);
        return m_receivedLogMessages.size();
    }

    bool getReceivedLogMessageInfo(const std::size_t index, std::string& loggerId, LogLevel& logLevel, MessageSPtr& msg)
    {
        std::unique_lock<std::mutex> guard(m_mutex);
        if (index >= m_receivedLogMessages.size())
        {
            // Wrong index.
            return false;
        }

        LogMsgInfoList::iterator msgIter = m_receivedLogMessages.begin();
        std::advance(msgIter, index);

        loggerId = msgIter->m_loggerId;
        logLevel = msgIter->m_logLevel;
        msg      = msgIter->m_msg;
        return true;
    }

    bool isAsynchronousMode() const
    {
        std::unique_lock<std::mutex> guard(m_mutex);

        // Check if all messages were received asynchronously, i.e. the sending and receiving thread must be different.
        for (const LogMsgInfo& logMsgInfo : m_receivedLogMessages)
        {
            if (logMsgInfo.m_receivingThreadId == logMsgInfo.m_msg->getThreadId())
            {
                // This message was received by the same thread that sent it -> synchronous mode.
                return false;
            }
        }

        return true;
    }

    bool isSynchronousMode() const
    {
        std::unique_lock<std::mutex> guard(m_mutex);

        // Check if all messages were received synchronously, i.e. the sending and receiving thread must be the same.
        for (const LogMsgInfo& logMsgInfo : m_receivedLogMessages)
        {
            if (logMsgInfo.m_receivingThreadId != logMsgInfo.m_msg->getThreadId())
            {
                // This message was received by the different thread than that which sent it -> asynchronous mode.
                return false;
            }
        }

        return true;
    }

public:
    void logAsync(const std::string& loggerId, const LogLevel& logLevel, const MessageSPtr msg) override
    {
        std::unique_lock<std::mutex> guard(m_mutex);

        LogMsgInfo msgInfo(loggerId, logLevel, msg, std::this_thread::get_id());
        m_receivedLogMessages.push_back(msgInfo);

        BOOST_TEST_MESSAGE(msg->getText());
        std::this_thread::sleep_for(m_processingDelay);
    }

private:
    struct LogMsgInfo
    {
        LogMsgInfo(const std::string& loggerId,
                   const LogLevel& logLevel,
                   const MessageSPtr msg,
                   const std::thread::id& receivingThreadId)
          : m_loggerId(loggerId), m_logLevel(logLevel), m_msg(msg), m_receivingThreadId(receivingThreadId)
        {}

        std::string m_loggerId;
        LogLevel m_logLevel;
        MessageSPtr m_msg;
        std::thread::id m_receivingThreadId;
    };

    using LogMsgInfoList = std::list<LogMsgInfo>;

private:
    std::chrono::milliseconds m_processingDelay{0};

    mutable std::mutex m_mutex{};
    LogMsgInfoList m_receivedLogMessages{};
};

constexpr const char* const CustomLoggerBackend::backendId;

//==============================================================================

class Fixture
{
public:
    Fixture()
    {
        m_logger  = LogManager::getInstance().createLogger("TestLogger");
        m_backend = std::make_shared<CustomLoggerBackend>(CustomLoggerBackend::backendId);

        LogManager::getInstance().registerBackend(m_backend);

        m_logger->removeAllBackends();
        m_logger->addLoggerBackend(m_backend);
    }

    virtual ~Fixture() = default;

protected:
    std::shared_ptr<CustomLoggerBackend> m_backend;
    LoggerSPtr m_logger;
}; // Fixture

//==============================================================================
BOOST_AUTO_TEST_SUITE(AsyncLoggerBackendTestSuite)
//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkDefaultConfiguration, Fixture)
{
    TestSupport::printTestName();

    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueSize(), AsyncLoggerBackend::logMessageDefaultQueueSize);
    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueTimeoutMilliseconds(), LogMessageQueue::infiniteMilliseconds);

    LOGCRITICAL(m_logger, "test message");

    // Wait until all messages have been delivered.
    m_backend->flush();

    // Check number of log messages received by the backend.
    BOOST_CHECK_EQUAL(m_backend->getNbOfReceivedMessages(), 1);

    // All log messages should have been received asynchronously.
    BOOST_CHECK(m_backend->isAsynchronousMode());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkModeBlock, Fixture)
{
    TestSupport::printTestName();

    // Create XML string.
    std::string xmlString = "<Backend>"
                            "    <Mode>Block</Mode>"
                            "    <QueueSize>1</QueueSize>"
                            "</Backend>";

    tinyxml2::XMLDocument doc;
    doc.Parse(xmlString.c_str(), xmlString.size());
    const tinyxml2::XMLElement* configNode = doc.FirstChildElement("Backend");

    BOOST_CHECK(m_backend->configure(configNode, false));

    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueSize(), 1);
    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueTimeoutMilliseconds(), LogMessageQueue::infiniteMilliseconds);

    static constexpr std::size_t nbOfLogMesages{3};
    static constexpr std::chrono::milliseconds processingDelay{std::chrono::milliseconds(200)};
    m_backend->setProcessingDelay(processingDelay);

    auto startTime = std::chrono::system_clock::now();
    for (uint32_t ix = 0; ix < nbOfLogMesages; ++ix)
    {
        LOGCRITICAL(m_logger, "test message " << (ix + 1));
    }
    auto endTime = std::chrono::system_clock::now();

    // The first message is handled immediately, the second one will fill the queue (capacity is one), and the third
    // messages will be delivered to the queue as soon as the first message is processed. Thus, sending three log
    // messages should take at least one time the processing delay.
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    BOOST_CHECK_GE(duration.count(), processingDelay.count());

    // Wait until all messages have been delivered.
    m_backend->flush(processingDelay.count() * nbOfLogMesages);

    // Check number of log messages received by the backend.
    BOOST_CHECK_EQUAL(m_backend->getNbOfReceivedMessages(), nbOfLogMesages);

    // All log messages should have been received asynchronously.
    BOOST_CHECK(m_backend->isAsynchronousMode());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkModeTimed, Fixture)
{
    TestSupport::printTestName();

    // Create XML string.
    std::string xmlString = "<Backend>"
                            "    <Mode>Timed</Mode>"
                            "    <QueueSize>1</QueueSize>"
                            "    <Timeout>200</Timeout>"
                            "</Backend>";

    tinyxml2::XMLDocument doc;
    doc.Parse(xmlString.c_str(), xmlString.size());
    const tinyxml2::XMLElement* configNode = doc.FirstChildElement("Backend");

    BOOST_CHECK(m_backend->configure(configNode, false));

    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueSize(), 1);
    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueTimeoutMilliseconds(), 200);

    static constexpr std::size_t nbOfLogMesages{3};
    static constexpr std::chrono::milliseconds processingDelay{std::chrono::milliseconds(100)};
    m_backend->setProcessingDelay(processingDelay);

    for (uint32_t ix = 0; ix < nbOfLogMesages; ++ix)
    {
        LOGCRITICAL(m_logger, "test message " << (ix + 1));
    }

    // Wait until all messages have been delivered.
    m_backend->flush(processingDelay.count() * nbOfLogMesages);

    // The first message is handled immediately, the second one will fill the queue (capacity is one), and the third
    // messages will be delivered to the queue as soon as the first message is processed. As the processing delay is
    // shorter than the wait timeout, all messages should have been delivered.

    // Check number of log messages received by the backend.
    BOOST_CHECK_EQUAL(m_backend->getNbOfReceivedMessages(), nbOfLogMesages);

    // All log messages should have been received asynchronously.
    BOOST_CHECK(m_backend->isAsynchronousMode());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkModeTimedTimeout, Fixture)
{
    TestSupport::printTestName();

    // Create XML string.
    std::string xmlString = "<Backend>"
                            "    <Mode>Timed</Mode>"
                            "    <QueueSize>1</QueueSize>"
                            "    <Timeout>100</Timeout>"
                            "</Backend>";

    tinyxml2::XMLDocument doc;
    doc.Parse(xmlString.c_str(), xmlString.size());
    const tinyxml2::XMLElement* configNode = doc.FirstChildElement("Backend");

    BOOST_CHECK(m_backend->configure(configNode, false));

    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueSize(), 1);
    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueTimeoutMilliseconds(), 100);

    static constexpr std::size_t nbOfLogMesages{3};
    static constexpr std::chrono::milliseconds processingDelay{std::chrono::milliseconds(200)};
    m_backend->setProcessingDelay(processingDelay);

    for (uint32_t ix = 0; ix < nbOfLogMesages; ++ix)
    {
        LOGCRITICAL(m_logger, "test message " << (ix + 1));
    }

    // Wait until all messages have been delivered.
    m_backend->flush(processingDelay.count() * nbOfLogMesages);

    // The first message is handled immediately, the second one will fill the queue (capacity is one), and the third
    // messages will be delivered to the queue as soon as the first message is processed. As the processing delay is
    // longer than the wait timeout, only the first two messages should have been delivered at most.

    // Check number of log messages received by the backend.
    BOOST_CHECK_LE(m_backend->getNbOfReceivedMessages(), 2);

    // All log messages should have been received asynchronously.
    BOOST_CHECK(m_backend->isAsynchronousMode());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkModeDrop, Fixture)
{
    TestSupport::printTestName();

    // Create XML string.
    std::string xmlString = "<Backend>"
                            "    <Mode>Drop</Mode>"
                            "    <QueueSize>1</QueueSize>"
                            "</Backend>";

    tinyxml2::XMLDocument doc;
    doc.Parse(xmlString.c_str(), xmlString.size());
    const tinyxml2::XMLElement* configNode = doc.FirstChildElement("Backend");

    BOOST_CHECK(m_backend->configure(configNode, false));

    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueSize(), 1);
    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueTimeoutMilliseconds(), 0);

    static constexpr std::size_t nbOfLogMesages{3};
    static constexpr std::chrono::milliseconds processingDelay{std::chrono::milliseconds(100)};
    m_backend->setProcessingDelay(processingDelay);

    for (uint32_t ix = 0; ix < nbOfLogMesages; ++ix)
    {
        LOGCRITICAL(m_logger, "test message " << (ix + 1));
    }

    // Wait until all messages have been delivered.
    m_backend->flush(processingDelay.count() * nbOfLogMesages);

    // The first message is handled immediately, the second one will fill the queue (capacity is one), and the third
    // messages should be dropped as the queue is full. Thus, only the first two messages should have been delivered at
    // most.

    // Check number of log messages received by the backend.
    BOOST_CHECK_LE(m_backend->getNbOfReceivedMessages(), 2);

    // All log messages should have been received asynchronously.
    BOOST_CHECK(m_backend->isAsynchronousMode());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkModeByPass, Fixture)
{
    TestSupport::printTestName();

    // Create XML string.
    std::string xmlString = "<Backend>"
                            "    <Mode>Bypass</Mode>"
                            "</Backend>";

    tinyxml2::XMLDocument doc;
    doc.Parse(xmlString.c_str(), xmlString.size());
    const tinyxml2::XMLElement* configNode = doc.FirstChildElement("Backend");

    BOOST_CHECK(m_backend->configure(configNode, false));

    static constexpr std::size_t nbOfLogMesages{3};
    static constexpr std::chrono::milliseconds processingDelay{std::chrono::milliseconds(100)};
    m_backend->setProcessingDelay(processingDelay);

    for (uint32_t ix = 0; ix < nbOfLogMesages; ++ix)
    {
        LOGCRITICAL(m_logger, "test message " << (ix + 1));
    }

    // Check number of log messages received by the backend.
    BOOST_CHECK_EQUAL(m_backend->getNbOfReceivedMessages(), nbOfLogMesages);

    // All log messages should have been received synchronously.
    BOOST_CHECK(m_backend->isSynchronousMode());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkInvalidMode, Fixture)
{
    TestSupport::printTestName();

    // Create XML string.
    std::string xmlString = "<Backend>"
                            "    <Mode>xxx</Mode>"
                            "</Backend>";

    tinyxml2::XMLDocument doc;
    doc.Parse(xmlString.c_str(), xmlString.size());
    const tinyxml2::XMLElement* configNode = doc.FirstChildElement("Backend");

    BOOST_CHECK(m_backend->configure(configNode, false));

    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueSize(), AsyncLoggerBackend::logMessageDefaultQueueSize);
    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueTimeoutMilliseconds(), LogMessageQueue::infiniteMilliseconds);

    static constexpr std::size_t nbOfLogMesages{3};

    for (uint32_t ix = 0; ix < nbOfLogMesages; ++ix)
    {
        LOGCRITICAL(m_logger, "test message " << (ix + 1));
    }
    // Wait until all messages have been delivered.
    m_backend->flush();

    // Check number of log messages received by the backend.
    BOOST_CHECK_EQUAL(m_backend->getNbOfReceivedMessages(), nbOfLogMesages);

    // All log messages should have been received asynchronously.
    BOOST_CHECK(m_backend->isAsynchronousMode());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkInvalidTimeout, Fixture)
{
    TestSupport::printTestName();

    // Create XML string.
    std::string xmlString = "<Backend>"
                            "    <Mode>Timed</Mode>"
                            "    <Timeout>xxx</Timeout>"
                            "</Backend>";

    tinyxml2::XMLDocument doc;
    doc.Parse(xmlString.c_str(), xmlString.size());
    const tinyxml2::XMLElement* configNode = doc.FirstChildElement("Backend");

    BOOST_CHECK(m_backend->configure(configNode, false));

    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueSize(), AsyncLoggerBackend::logMessageDefaultQueueSize);
    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueTimeoutMilliseconds(), LogMessageQueue::infiniteMilliseconds);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkInvalidQueueSize, Fixture)
{
    TestSupport::printTestName();

    // Create XML string.
    std::string xmlString = "<Backend>"
                            "    <QueueSize>xxx</QueueSize>"
                            "</Backend>";

    tinyxml2::XMLDocument doc;
    doc.Parse(xmlString.c_str(), xmlString.size());
    const tinyxml2::XMLElement* configNode = doc.FirstChildElement("Backend");

    BOOST_CHECK(m_backend->configure(configNode, false));

    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueSize(), AsyncLoggerBackend::logMessageDefaultQueueSize);
    BOOST_CHECK_EQUAL(m_backend->getLogMessageQueueTimeoutMilliseconds(), LogMessageQueue::infiniteMilliseconds);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkPointer, Fixture)
{
    TestSupport::printTestName();

    // Send a test message (re-use pointers to check asynchronous behavior).
    const char* constPtr;
    char* rawPtr;

    constPtr = "<const from literal>";
    LOGCRITICAL(m_logger, "const char* from literal: " << constPtr);

    std::string textString{"<from string>"};
    constPtr = textString.data();
    LOGCRITICAL(m_logger, "const char* from string: " << constPtr);
    textString.clear();

    rawPtr = new char[64];
    strcpy(rawPtr, "<from memory>");
    LOGCRITICAL(m_logger, "char* from memory: " << rawPtr);
    strcpy(rawPtr, "xxxxxxxxxxxxx");
    delete[] rawPtr;

    // Wait until all messages have been delivered.
    m_backend->flush();

    std::string loggerId("?");
    LogLevel logLevel;
    MessageSPtr msg;

    BOOST_CHECK(m_backend->getReceivedLogMessageInfo(0, loggerId, logLevel, msg));
    BOOST_CHECK_EQUAL(msg->getText(), "const char* from literal: <const from literal>");

    BOOST_CHECK(m_backend->getReceivedLogMessageInfo(1, loggerId, logLevel, msg));
    BOOST_CHECK_EQUAL(msg->getText(), "const char* from string: <from string>");

    BOOST_CHECK(m_backend->getReceivedLogMessageInfo(2, loggerId, logLevel, msg));
    BOOST_CHECK_EQUAL(msg->getText(), "char* from memory: <from memory>");
}

//==============================================================================
BOOST_AUTO_TEST_SUITE_END()
//==============================================================================

//==============================================================================
} // namespace unittest
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

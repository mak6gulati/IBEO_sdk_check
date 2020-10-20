//==============================================================================
//! \file
//!\brief Testing execution speed.
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Oct 04, 2018
//------------------------------------------------------------------------------

#define BOOST_TEST_MODULE SpeedTest

//==============================================================================

#include <boost/test/unit_test.hpp>

#include <ibeo/common/logging/logging.hpp>
#include <TestSupport.hpp>

#include <chrono>
#include <iomanip>

//==============================================================================

using namespace ibeo::common::logging;
using namespace std::chrono;

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
namespace unittest {
//==============================================================================

//==============================================================================
BOOST_AUTO_TEST_SUITE(SpeedTestSuite)
//==============================================================================

class CustomLoggerBackend : public LoggerBackend
{
public:
    CustomLoggerBackend(const std::string& backendId) : LoggerBackend(backendId) {}

    void log(const std::string&, const LogLevel&, const MessageSPtr msg) override
    {
        // Get formatted message to get an indication of the performance when logging is switched of according
        // to log level.
        std::stringstream stream;
        msg->print(stream);
    }
};

//==============================================================================

class Fixture
{
public:
    Fixture()
    {
        // Register custom backend.
        std::string backendId{"CustomBackend"};
        const std::shared_ptr<CustomLoggerBackend>& backend = std::make_shared<CustomLoggerBackend>(backendId);
        LogManager::getInstance().registerBackend(backend);

        // Create logger with most detailed log level to ensure that the log method is always called.
        m_logger = LogManager::getInstance().createLogger("logger");
        m_logger->setLogLevel(LogLevel::Warning); // some level from the middle

        // Ensure that our custom backend is the only backend.
        m_logger->removeAllBackends();
        m_logger->addLoggerBackend(backend);
    }

    ~Fixture() = default;

protected:
    LoggerSPtr m_logger;
}; // Fixture

//==============================================================================

#define SPEED_TEST_BEGIN(traceLoopCount, testName)                                                                     \
    BOOST_TEST_MESSAGE(#testName << ":");                                                                              \
    high_resolution_clock::time_point start##testName = high_resolution_clock::now();                                  \
    for (uint32_t traceLoopIx##testName = 0; traceLoopIx##testName < traceLoopCount; ++traceLoopIx##testName)          \
    {
//==============================================================================

#define SPEED_TEST_END(testName)                                                                                       \
    }                                                                                                                  \
    high_resolution_clock::time_point end##testName = high_resolution_clock::now();                                    \
    int64_t duration##testName = duration_cast<microseconds>(end##testName - start##testName).count();                 \
    BOOST_TEST_MESSAGE("Execution time: " << std::fixed << std::setprecision(0) << duration##testName << " us.");

//==============================================================================

static const uint32_t traceLoopCount{100000};

//==============================================================================

BOOST_FIXTURE_TEST_CASE(speedTest, Fixture)
{
    TestSupport::printTestName();

    SPEED_TEST_BEGIN(traceLoopCount, FixedText);
    m_logger->critical(std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__, "log text"));
    SPEED_TEST_END(FixedText);

    SPEED_TEST_BEGIN(traceLoopCount, CreateMessageAndStream);
    m_logger->critical(std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__) << "log text");
    SPEED_TEST_END(CreateMessageAndStream);

    SPEED_TEST_BEGIN(traceLoopCount, LogMsgMacro);
    m_logger->critical(LOGMSG << "log text");
    SPEED_TEST_END(LogMsgMacro);

    SPEED_TEST_BEGIN(traceLoopCount, FixedTextNoOutput);
    m_logger->trace(std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__, "log text"));
    SPEED_TEST_END(FixedTextNoOutput);

    SPEED_TEST_BEGIN(traceLoopCount, CreateMessageAndStreamNoOutput);
    m_logger->trace(std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__) << "log text");
    SPEED_TEST_END(CreateMessageAndStreamNoOutput);

    SPEED_TEST_BEGIN(traceLoopCount, LogMsgMacroNoOutput);
    m_logger->trace(LOGMSG << "log text");
    SPEED_TEST_END(LogMsgMacroNoOutput);

    BOOST_CHECK(true);
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

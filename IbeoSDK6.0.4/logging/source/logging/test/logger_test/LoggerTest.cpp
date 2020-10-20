//==============================================================================
//!\file
//!\brief Test for Logger class.
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jun 26, 2018
//------------------------------------------------------------------------------

#define BOOST_TEST_MODULE LoggerTest

//==============================================================================

#include <boost/test/unit_test.hpp>

#include <ibeo/common/logging/logging.hpp>
#include <TestSupport.hpp>

#include <iomanip>

//==============================================================================
#ifdef BOOST_TEST_INFO
// From 1.59 onwards Boost has this macro that can be used directly.
#    define BOOST_CHECK_EQUAL_MESSAGE(L, R, M)                                                                         \
        {                                                                                                              \
            BOOST_TEST_INFO(M);                                                                                        \
            BOOST_CHECK_EQUAL(L, R);                                                                                   \
        }
#    define BOOST_WARN_EQUAL_MESSAGE(L, R, M)                                                                          \
        {                                                                                                              \
            BOOST_TEST_INFO(M);                                                                                        \
            BOOST_WARN_EQUAL(L, R);                                                                                    \
        }
#    define BOOST_REQUIRE_EQUAL_MESSAGE(L, R, M)                                                                       \
        {                                                                                                              \
            BOOST_TEST_INFO(M);                                                                                        \
            BOOST_REQUIRE_EQUAL(L, R);                                                                                 \
        }
#else
// Up to version 1.58 the behaviour of BOOST_TEST_INFO is simulated.
#    define BOOST_TEST_REL_EQ_MESSAGE_EXTENSION(L, R, M, CMP, ICMP, CT)                                                \
        {                                                                                                              \
            auto _1(L);                                                                                                \
            auto _2(R);                                                                                                \
            std::stringstream ss;                                                                                      \
            ss << "check " << BOOST_TEST_STRINGIZE(L) << " " << BOOST_TEST_STRINGIZE(CMP) << " "                       \
               << BOOST_TEST_STRINGIZE(R) << " failed [" << _1 << " " << BOOST_TEST_STRINGIZE(ICMP) << " " << _2       \
               << "] : " << M;                                                                                         \
            BOOST_CHECK_IMPL((_1 CMP _2), ss.str(), CT, CHECK_MSG);                                                    \
        }

#    define BOOST_CHECK_EQUAL_MESSAGE(L, R, M) BOOST_TEST_REL_EQ_MESSAGE_EXTENSION(L, R, M, ==, !=, CHECK)
#    define BOOST_WARN_EQUAL_MESSAGE(L, R, M) BOOST_TEST_REL_EQ_MESSAGE_EXTENSION(L, R, M, ==, !=, WARN)
#    define BOOST_REQUIRE_EQUAL_MESSAGE(L, R, M) BOOST_TEST_REL_EQ_MESSAGE_EXTENSION(L, R, M, ==, !=, REQUIRE)
#endif
//==============================================================================

using namespace ibeo::common::logging;

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
namespace unittest {
//==============================================================================

class CustomLoggerBackend : public LoggerBackend
{
public:
    CustomLoggerBackend(const std::string& backendId) : LoggerBackend{backendId} {}

public:
    const std::string& getLastLogText() const { return m_lastLogText; }

public:
    void log(const std::string&, const LogLevel& level, const MessageSPtr msg) override
    {
        std::stringstream stream;
        stream << "[backend '" << getId() << "', LogLevel::" << std::setw(8) << std::left << logLevelToString(level)
               << "] '" << msg->getText() << "'";
        BOOST_TEST_MESSAGE(stream.str());

        m_lastLogText = msg->getText();
    }

    void clearLogText() { m_lastLogText = ""; }

private:
    std::string m_lastLogText;
};

//==============================================================================

using CustomLoggerBackendSPtr = std::shared_ptr<CustomLoggerBackend>;

//==============================================================================

class Fixture
{
public:
    static const int nbOfBackends{2};

    Fixture()
    {
        // Register some backends.
        for (int backendNo = 1; backendNo <= nbOfBackends; ++backendNo)
        {
            std::stringstream stream;
            stream << "CustomLoggerBackend" << backendNo;
            const std::string backendId{stream.str()};
            CustomLoggerBackendSPtr backend = std::make_shared<CustomLoggerBackend>(backendId);
            LogManager::getInstance().registerBackend(backend);

            m_backends.push_back(backend);
        }
    }

    ~Fixture()
    {
        // Reset (static) state of log manager.
        LogManager::getInstance().reset();
    }

public:
    static void checkLogMessages(Logger& logger,
                                 const std::vector<std::pair<CustomLoggerBackendSPtr, bool>>& testBackends)
    {
        std::vector<LogLevel> testData{LogLevel::Off,
                                       LogLevel::Critical,
                                       LogLevel::Error,
                                       LogLevel::Warning,
                                       LogLevel::Info,
                                       LogLevel::Trace,
                                       LogLevel::Debug};

        for (std::size_t i = 0; i < testData.size(); ++i)
        {
            LogLevel testLogLevel   = testData[i];
            std::string testLogText = logLevelToString(testLogLevel) + " text";

            logger.log(testLogLevel, LOGMSG << testLogText);
            for (std::pair<CustomLoggerBackendSPtr, bool> testBackend : testBackends)
            {
                CustomLoggerBackendSPtr backend = testBackend.first;
                bool enabled                    = testBackend.second;

                std::string testInfo = std::string("Logger log level ") + logLevelToString(logger.getLogLevel())
                                       + ", test log level " + logLevelToString(testLogLevel) + ", backend ID '"
                                       + backend->getId() + "'";

                if (enabled && (logger.getLogLevel() >= testLogLevel))
                {
                    // Backend is enabled and log level fits -> message should have been logged.
                    BOOST_CHECK_EQUAL_MESSAGE(backend->getLastLogText(), testLogText, testInfo);
                }
                else
                {
                    // No message should have been logged.
                    BOOST_CHECK_MESSAGE(backend->getLastLogText().empty(), testInfo);
                }

                // Reset log text for next run.
                backend->clearLogText();
            }
        }
    }

protected:
    std::vector<CustomLoggerBackendSPtr> m_backends;
}; // Fixture

//==============================================================================
BOOST_AUTO_TEST_SUITE(LoggerTestSuite)
//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkLogLevels, Fixture)
{
    TestSupport::printTestName();

    CustomLoggerBackendSPtr backend = m_backends[0];
    const std::vector<std::pair<CustomLoggerBackendSPtr, bool>>& testBackends{{backend, true}};

    Logger logger("logger");
    logger.addLoggerBackend(backend);
    BOOST_CHECK_EQUAL(logger.getId(), "logger");
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger.getLogLevel()), static_cast<uint16_t>(LogLevel::Off));
    checkLogMessages(logger, testBackends);

    logger.setLogLevel(LogLevel::Critical);
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger.getLogLevel()), static_cast<uint16_t>(LogLevel::Critical));
    checkLogMessages(logger, testBackends);

    logger.setLogLevel(LogLevel::Error);
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger.getLogLevel()), static_cast<uint16_t>(LogLevel::Error));
    checkLogMessages(logger, testBackends);

    logger.setLogLevel(LogLevel::Warning);
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger.getLogLevel()), static_cast<uint16_t>(LogLevel::Warning));
    checkLogMessages(logger, testBackends);

    logger.setLogLevel(LogLevel::Info);
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger.getLogLevel()), static_cast<uint16_t>(LogLevel::Info));
    checkLogMessages(logger, testBackends);

    logger.setLogLevel(LogLevel::Trace);
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger.getLogLevel()), static_cast<uint16_t>(LogLevel::Trace));
    checkLogMessages(logger, testBackends);

    logger.setLogLevel(LogLevel::Debug);
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger.getLogLevel()), static_cast<uint16_t>(LogLevel::Debug));
    checkLogMessages(logger, testBackends);

    logger.setLogLevel(LogLevel::Off);
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger.getLogLevel()), static_cast<uint16_t>(LogLevel::Off));
    checkLogMessages(logger, testBackends);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkBackends, Fixture)
{
    TestSupport::printTestName();

    // Create test backends that are disabled initially.
    std::vector<std::pair<CustomLoggerBackendSPtr, bool>> testBackends;
    for (std::size_t backendIx = 0; backendIx < m_backends.size(); ++backendIx)
    {
        testBackends.push_back({m_backends[backendIx], false});
    }

    // Create logger without backend.
    Logger logger("logger");
    logger.setLogLevel(LogLevel::Debug);

    // None of the backends should received a message now.
    BOOST_TEST_MESSAGE("Without backends:");
    checkLogMessages(logger, testBackends);

    // Add one backend to the logger, enable it in the test data, and check the log messages again.
    logger.addLoggerBackend(m_backends[0]);
    testBackends[0].second = true;
    BOOST_TEST_MESSAGE("With first backend only:");
    checkLogMessages(logger, testBackends);

    // Add another backend to the logger, enable it in the test data, and check the log messages again.
    logger.addLoggerBackend(m_backends[1]);
    testBackends[1].second = true;
    BOOST_TEST_MESSAGE("With first and second backend:");
    checkLogMessages(logger, testBackends);

    // Remove first backend from the logger, disable it in the test data, and check the log messages again.
    logger.removeLoggerBackend(m_backends[0]->getId());
    testBackends[0].second = false;
    BOOST_TEST_MESSAGE("With second backend only:");
    checkLogMessages(logger, testBackends);

    // Remove second backend from the logger, disable it in the test data, and check the log messages again.
    logger.removeLoggerBackend(m_backends[1]->getId());
    testBackends[1].second = false;
    BOOST_TEST_MESSAGE("Without backends again:");
    checkLogMessages(logger, testBackends);
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

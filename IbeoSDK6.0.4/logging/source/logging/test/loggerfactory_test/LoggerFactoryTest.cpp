//==============================================================================
//!\file
//!\brief Test for LoggerFactory class.
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

#define BOOST_TEST_MODULE LoggerFactoryTest

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

class Fixture
{
public:
    Fixture() = default;

    ~Fixture()
    {
        // Reset (static) state of log manager.
        LogManager::getInstance().reset();
    }
}; // Fixture

//==============================================================================
BOOST_AUTO_TEST_SUITE(LoggerFactoryTestSuite)
//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkCreateDifferentLoggers, Fixture)
{
    TestSupport::printTestName();

    std::string loggerId1{"logger1"};
    std::string loggerId2{"logger2"};

    // No loggers should have been created initially.
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 0);

    // Get first logger.
    LoggerSPtr logger1 = LogManager::getInstance().createLogger(loggerId1);
    BOOST_CHECK(logger1.get());
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 1);

    // Get second logger.
    LoggerSPtr logger2 = LogManager::getInstance().createLogger(loggerId2);
    BOOST_CHECK(logger2.get());
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 2);

    // Loggers should be different.
    BOOST_CHECK_NE(logger1.get(), logger2.get());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkCreateSameLoggerTwice, Fixture)
{
    TestSupport::printTestName();

    std::string loggerId{"logger"};

    // Get logger first time.
    LoggerSPtr logger1 = LogManager::getInstance().createLogger(loggerId);
    BOOST_CHECK(logger1.get());
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 1);

    // Get same logger second time.
    LoggerSPtr logger2 = LogManager::getInstance().createLogger(loggerId);
    BOOST_CHECK(logger2.get());
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 1);

    // Loggers should be identical.
    BOOST_CHECK_EQUAL(logger1.get(), logger2.get());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkDestroyLogger, Fixture)
{
    TestSupport::printTestName();

    std::string loggerId{"logger"};

    // Get logger.
    LoggerSPtr logger1 = LogManager::getInstance().createLogger(loggerId);
    BOOST_CHECK(logger1.get());
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 1);

    // Destroy logger.
    logger1 = nullptr;
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 0);

    // Re-create logger.
    LoggerSPtr logger2 = LogManager::getInstance().createLogger(loggerId);
    BOOST_CHECK(logger2.get());
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 1);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkDestroyMultiLogger, Fixture)
{
    TestSupport::printTestName();

    std::string loggerId{"logger"};

    // Get same logger twice.
    LoggerSPtr logger1 = LogManager::getInstance().createLogger(loggerId);
    LoggerSPtr logger2 = LogManager::getInstance().createLogger(loggerId);
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 1);

    // Destroy second logger.
    logger2 = nullptr;
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 1);

    // Re-create second logger.
    logger2 = LogManager::getInstance().createLogger(loggerId);
    BOOST_CHECK(logger2.get());
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 1);

    // Loggers should still be identical.
    BOOST_CHECK_EQUAL(logger1.get(), logger2.get());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigBeforeCreatingLoggers, Fixture)
{
    TestSupport::printTestName();

    // Set configuration.
    ConfigurationSPtr config{std::make_shared<Configuration>()};
    config->setDefaultLogLevel("Info");
    LogManager::getInstance().configure(config);

    // Create some loggers.
    LoggerSPtr logger1 = LogManager::getInstance().createLogger("Logger1");
    BOOST_CHECK(logger1.get());

    LoggerSPtr logger2 = LogManager::getInstance().createLogger("Logger2");
    BOOST_CHECK(logger2.get());

    // Check log level.
    BOOST_CHECK(logger1->isInfo());
    BOOST_CHECK(logger1->isDebug() == false);

    BOOST_CHECK(logger2->isInfo());
    BOOST_CHECK(logger2->isDebug() == false);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigAfterCreatingLoggers, Fixture)
{
    TestSupport::printTestName();

    // Create some loggers with default configuration.
    LoggerSPtr logger1 = LogManager::getInstance().createLogger("Logger1");
    BOOST_CHECK(logger1.get());

    LoggerSPtr logger2 = LogManager::getInstance().createLogger("Logger2");
    BOOST_CHECK(logger2.get());

    // Check default log level (Error).
    BOOST_CHECK(logger1->isError());
    BOOST_CHECK(logger1->isWarning() == false);

    BOOST_CHECK(logger2->isError());
    BOOST_CHECK(logger2->isWarning() == false);

    // Change configuration.
    ConfigurationSPtr newConfig{std::make_shared<Configuration>()};
    newConfig->setDefaultLogLevel("Info");
    LogManager::getInstance().configure(newConfig);

    // Check new log level.
    BOOST_CHECK(logger1->isInfo());
    BOOST_CHECK(logger1->isDebug() == false);

    BOOST_CHECK(logger2->isInfo());
    BOOST_CHECK(logger2->isDebug() == false);
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

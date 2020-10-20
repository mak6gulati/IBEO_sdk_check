//==============================================================================
//!\file
//!\brief Test for Configuration class.
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

#define BOOST_TEST_MODULE ConfigurationTest

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

//==============================================================================
BOOST_AUTO_TEST_SUITE(ConfigurationTestSuite)
//==============================================================================

BOOST_AUTO_TEST_CASE(checkDefaultLogLevel)
{
    TestSupport::printTestName();

    std::string loggerId1{"logger1"};
    std::string loggerId2{"logger2"};

    Configuration config;

    // Default log level should be Error initially.
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId1)),
                      static_cast<uint16_t>(LogLevel::Error));
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId2)),
                      static_cast<uint16_t>(LogLevel::Error));

    config.setDefaultLogLevel("Warning");
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId1)),
                      static_cast<uint16_t>(LogLevel::Warning));
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId2)),
                      static_cast<uint16_t>(LogLevel::Warning));
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkSpecificLogLevel)
{
    TestSupport::printTestName();

    std::string loggerId1{"logger1"};
    std::string loggerId2{"logger2"};

    Configuration config;

    config.setLogLevelForLogger("Debug", loggerId1);
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId1)),
                      static_cast<uint16_t>(LogLevel::Debug));
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId2)),
                      static_cast<uint16_t>(LogLevel::Error));

    config.setDefaultLogLevel("Warning");
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId1)),
                      static_cast<uint16_t>(LogLevel::Debug));
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId2)),
                      static_cast<uint16_t>(LogLevel::Warning));
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkDefaultBackends)
{
    TestSupport::printTestName();

    std::string loggerId1{"logger1"};
    std::string loggerId2{"logger2"};

    Configuration config;

    // Check default backends.
    {
        std::list<std::string> defaultBackends{ConsoleLoggerBackend::getBackendId()};

        std::list<std::string> logger1Backends = config.getBackendsForLogger(loggerId1);
        std::list<std::string> logger2Backends = config.getBackendsForLogger(loggerId2);

        BOOST_CHECK_EQUAL_COLLECTIONS(
            logger1Backends.begin(), logger1Backends.end(), defaultBackends.begin(), defaultBackends.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(
            logger2Backends.begin(), logger2Backends.end(), defaultBackends.begin(), defaultBackends.end());
    }

    // Check new default backends.
    {
        std::list<std::string> newDefaultBackends{ConsoleLoggerBackend::getBackendId(),
                                                  FileLoggerBackend::getBackendId()};
        config.setDefaultBackends(newDefaultBackends);

        std::list<std::string> logger1Backends = config.getBackendsForLogger(loggerId1);
        std::list<std::string> logger2Backends = config.getBackendsForLogger(loggerId2);

        BOOST_CHECK_EQUAL_COLLECTIONS(
            logger1Backends.begin(), logger1Backends.end(), newDefaultBackends.begin(), newDefaultBackends.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(
            logger2Backends.begin(), logger2Backends.end(), newDefaultBackends.begin(), newDefaultBackends.end());
    }
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkSpecifcBackends)
{
    TestSupport::printTestName();

    std::string loggerId1{"logger1"};
    std::string loggerId2{"logger2"};

    Configuration config;
    std::list<std::string> defaultBackends{ConsoleLoggerBackend::getBackendId()};

    // Check specific backends.
    {
        config.addBackendForLogger(FileLoggerBackend::getBackendId(), loggerId1);

        std::list<std::string> logger1Backends = config.getBackendsForLogger(loggerId1);
        std::list<std::string> logger2Backends = config.getBackendsForLogger(loggerId2);

        std::list<std::string> targetLogger1Backends{FileLoggerBackend::getBackendId()};
        std::list<std::string> targetLogger2Backends = defaultBackends;

        BOOST_CHECK_EQUAL_COLLECTIONS(
            logger1Backends.begin(), logger1Backends.end(), targetLogger1Backends.begin(), targetLogger1Backends.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(
            logger2Backends.begin(), logger2Backends.end(), targetLogger2Backends.begin(), targetLogger2Backends.end());
    }

    // Check multiple backends.
    {
        config.addBackendForLogger(ConsoleLoggerBackend::getBackendId(), loggerId1);

        std::list<std::string> logger1Backends = config.getBackendsForLogger(loggerId1);
        std::list<std::string> logger2Backends = config.getBackendsForLogger(loggerId2);

        std::list<std::string> targetLogger1Backends{FileLoggerBackend::getBackendId(),
                                                     ConsoleLoggerBackend::getBackendId()};
        std::list<std::string> targetLogger2Backends = defaultBackends;

        BOOST_CHECK_EQUAL_COLLECTIONS(
            logger1Backends.begin(), logger1Backends.end(), targetLogger1Backends.begin(), targetLogger1Backends.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(
            logger2Backends.begin(), logger2Backends.end(), targetLogger2Backends.begin(), targetLogger2Backends.end());
    }

    // Change default backends.
    {
        std::list<std::string> newDefaultBackends{ConsoleLoggerBackend::getBackendId(),
                                                  FileLoggerBackend::getBackendId()};
        config.setDefaultBackends(newDefaultBackends);

        std::list<std::string> logger1Backends = config.getBackendsForLogger(loggerId1);
        std::list<std::string> logger2Backends = config.getBackendsForLogger(loggerId2);

        std::list<std::string> targetLogger1Backends{FileLoggerBackend::getBackendId(),
                                                     ConsoleLoggerBackend::getBackendId()};
        std::list<std::string> targetLogger2Backends = newDefaultBackends;

        BOOST_CHECK_EQUAL_COLLECTIONS(
            logger1Backends.begin(), logger1Backends.end(), targetLogger1Backends.begin(), targetLogger1Backends.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(
            logger2Backends.begin(), logger2Backends.end(), targetLogger2Backends.begin(), targetLogger2Backends.end());
    }
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkDefaultBackendTwice)
{
    TestSupport::printTestName();

    std::string loggerId{"logger"};

    Configuration config;

    std::list<std::string> newDefaultBackends{FileLoggerBackend::getBackendId(), FileLoggerBackend::getBackendId()};
    config.setDefaultBackends(newDefaultBackends);

    std::list<std::string> loggerBackends = config.getBackendsForLogger(loggerId);
    std::list<std::string> targetLoggerBackends{FileLoggerBackend::getBackendId()};
    BOOST_CHECK_EQUAL_COLLECTIONS(
        loggerBackends.begin(), loggerBackends.end(), targetLoggerBackends.begin(), targetLoggerBackends.end());
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkSpecifcBackendTwice)
{
    TestSupport::printTestName();

    std::string loggerId{"logger"};

    Configuration config;

    config.addBackendForLogger(FileLoggerBackend::getBackendId(), loggerId);
    config.addBackendForLogger(FileLoggerBackend::getBackendId(), loggerId);

    std::list<std::string> loggerBackends = config.getBackendsForLogger(loggerId);
    std::list<std::string> targetLoggerBackends{FileLoggerBackend::getBackendId()};
    BOOST_CHECK_EQUAL_COLLECTIONS(
        loggerBackends.begin(), loggerBackends.end(), targetLoggerBackends.begin(), targetLoggerBackends.end());
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkWildcardMatch)
{
    TestSupport::printTestName();

    {
        std::string loggerId1{"namespace1::logger1"};
        std::string loggerId2{"namespace1::logger2"};

        Configuration config;

        config.setLogLevelForLogger("Warning", "namespace1::*");
        BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId1)),
                          static_cast<uint16_t>(LogLevel::Warning));
        BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId2)),
                          static_cast<uint16_t>(LogLevel::Warning));
    }

    {
        std::string loggerId1{"namespace1::logger1"};
        std::string loggerId2{"namespace2::logger2"};

        Configuration config;

        config.setLogLevelForLogger("Warning", "namespace1::*");
        BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId1)),
                          static_cast<uint16_t>(LogLevel::Warning));
        BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId2)),
                          static_cast<uint16_t>(LogLevel::Error));
    }

    {
        std::string loggerId1{"logger1"};
        std::string loggerId2{"logger2"};

        Configuration config;

        config.setLogLevelForLogger("Warning", "*");
        BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId1)),
                          static_cast<uint16_t>(LogLevel::Warning));
        BOOST_CHECK_EQUAL(static_cast<uint16_t>(config.getLogLevelForLogger(loggerId2)),
                          static_cast<uint16_t>(LogLevel::Warning));
    }
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

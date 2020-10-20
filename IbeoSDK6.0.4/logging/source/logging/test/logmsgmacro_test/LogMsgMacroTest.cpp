//==============================================================================
//!\file
//!\brief Test for LogMsgDefinitions macro.
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

//==============================================================================

#define BOOST_TEST_MODULE LogMsgMacroTest

//==============================================================================

#include <boost/test/unit_test.hpp>

#include <ibeo/common/logging/logging.hpp>
#include <TestSupport.hpp>

#include <iomanip>

//==============================================================================

using namespace ibeo::common::logging;

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
namespace unittest {
//==============================================================================

//==============================================================================
BOOST_AUTO_TEST_SUITE(LogMsgMacroTestSuite)
//==============================================================================

BOOST_AUTO_TEST_CASE(checkLogMsgMacro)
{
    TestSupport::printTestName();

    LogManager::globalLogger()->critical(LOGMSG << "Complex log message: " << std::setw(4) << std::setfill('_') << 42);

    BOOST_CHECK(true);
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkLogMsgTextMacro)
{
    TestSupport::printTestName();

    LogManager::globalLogger()->critical(LOGMSG_TEXT("Simple log message."));

    BOOST_CHECK(true);
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkLogLevelMacros)
{
    TestSupport::printTestName();

    LogManager::globalLogger()->setLogLevel(LogLevel::Debug);

    LOGCRITICAL(LogManager::globalLogger(),
                "Critical log level is " << std::setw(4) << std::setfill(' ')
                                         << static_cast<uint16_t>(LogLevel::Critical));
    LOGERROR(LogManager::globalLogger(),
             "Error log level is " << std::setw(4) << std::setfill(' ') << static_cast<uint16_t>(LogLevel::Error));
    LOGWARNING(LogManager::globalLogger(),
               "Warning log level is " << std::setw(4) << std::setfill(' ')
                                       << static_cast<uint16_t>(LogLevel::Warning));
    LOGINFO(LogManager::globalLogger(),
            "Info log level is " << std::setw(4) << std::setfill(' ') << static_cast<uint16_t>(LogLevel::Info));
    LOGTRACE(LogManager::globalLogger(),
             "Trace log level is " << std::setw(4) << std::setfill(' ') << static_cast<uint16_t>(LogLevel::Trace));
    LOGDEBUG(LogManager::globalLogger(),
             "Debug log level is " << std::setw(4) << std::setfill(' ') << static_cast<uint16_t>(LogLevel::Debug));

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

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
//! \date Oct 30, 2018
//------------------------------------------------------------------------------

#define BOOST_TEST_MODULE FormatTest

//==============================================================================

#include <boost/test/unit_test.hpp>

#include <ibeo/common/logging/formatters/FilePathFormatter.hpp>
#include <ibeo/common/logging/formatters/LoggerIdFormatter.hpp>
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

#define CHECK_IGNORE_MARKERS(actualText, expectedText)                                                                 \
    {                                                                                                                  \
        std::string actual            = actualText;                                                                    \
        std::string expected          = expectedText;                                                                  \
        std::string actualWithMarkers = actualText;                                                                    \
        std::size_t pos               = expected.find("*date*");                                                       \
        if (pos != std::string::npos)                                                                                  \
        {                                                                                                              \
            std::size_t len = actual.length() - pos - (expected.length() - pos - 6);                                   \
            if (len > 0)                                                                                               \
            {                                                                                                          \
                actualWithMarkers.replace(pos, len, "*date*");                                                         \
            }                                                                                                          \
        }                                                                                                              \
        BOOST_CHECK_EQUAL(actualWithMarkers, expected);                                                                \
    }

//==============================================================================

class Fixture
{
public:
    Fixture()  = default;
    ~Fixture() = default;

protected:
    std::string
    getTimestampString(const MessageSPtr& msg, const char* const formatString, const bool withMilliSeconds = true)
    {
        std::time_t timeT = std::chrono::system_clock::to_time_t(msg->getTimestamp());
        std::tm tmTime    = *std::localtime(&timeT);

        std::stringstream stream;
        stream << std::put_time(&tmTime, formatString);

        if (withMilliSeconds)
        {
            std::chrono::system_clock::duration timeSinceEpoch = msg->getTimestamp().time_since_epoch();
            int64_t totalMilliSeconds = timeSinceEpoch.count() * std::chrono::system_clock::period::num
                                        / (std::chrono::system_clock::period::den / 1000);

            stream << "," << std::setw(3) << std::setfill('0') << (totalMilliSeconds % 1000);
        }

        return stream.str();
    }

protected:
    constexpr static const char* const defaultDateFormat{"%Y-%m-%d %H-%M-%S"};
}; // Fixture

//==============================================================================
BOOST_AUTO_TEST_SUITE(FormatTestSuite)
//==============================================================================

//==============================================================================
// Format
//==============================================================================
BOOST_FIXTURE_TEST_CASE(checkFormat, Fixture)
{
    TestSupport::printTestName();

    // No format string.
    {
        FormatSPtr format = Format::parse(nullptr);
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        std::string expected = std::string("[WARNING] ") + getTimestampString(msg, defaultDateFormat)
                               + " - testFile(42) - testFunction: message text\n";
        BOOST_CHECK_EQUAL(formattedText, expected);
    }

    // Empty format string.
    {
        FormatSPtr format = Format::parse("");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        std::string expected = std::string("[WARNING] ") + getTimestampString(msg, defaultDateFormat)
                               + " - testFile(42) - testFunction: message text\n";
        BOOST_CHECK_EQUAL(formattedText, expected);
    }

    // Double percent sign.
    {
        FormatSPtr format = Format::parse("Prefix %% suffix.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "Prefix % suffix.");
    }
    {
        FormatSPtr format = Format::parse("Prefix %line%% suffix.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "Prefix 42% suffix.");
    }
    {
        FormatSPtr format = Format::parse("Prefix %%%line suffix.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "Prefix %42 suffix.");
    }
    {
        FormatSPtr format = Format::parse("Prefix %%%% suffix.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "Prefix %% suffix.");
    }
    {
        FormatSPtr format = Format::parse("Prefix %%%line%% suffix.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "Prefix %42% suffix.");
    }

    // Unknown conversion pattern.
    {
        FormatSPtr format = Format::parse("Prefix %xxx suffix.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Unknown patterns are gracefully treated as literals.
        BOOST_CHECK_EQUAL(formattedText, "Prefix %xxx suffix.");
    }

    // Format string ends with percent sign.
    {
        FormatSPtr format = Format::parse("Prefix %");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Percent sign without conversion pattern is gracefully treated as literal.
        BOOST_CHECK_EQUAL(formattedText, "Prefix %");
    }

    // Invalid conversion option.
    {
        FormatSPtr format = Format::parse("Prefix %line{xxx}{yyy} suffix.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Invalid conversion options are gracefully ignored and absorbed.
        BOOST_CHECK_EQUAL(formattedText, "Prefix 42 suffix.");
    }

    // Maformed conversion option.
    {
        FormatSPtr format = Format::parse("Prefix %line{xxx{yyy} suffix.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Everything between open and closing bracket (incl. another open bracket) is treated as option and absorbed.
        BOOST_CHECK_EQUAL(formattedText, "Prefix 42 suffix.");
    }
    {
        FormatSPtr format = Format::parse("Prefix %line{xxx}{yyy suffix.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // If a closing bracket is missing everything till the end of the string is treated as option and absorbed.
        BOOST_CHECK_EQUAL(formattedText, "Prefix 42");
    }
    {
        FormatSPtr format = Format::parse("Prefix %line{xxx}yyy} suffix.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // If an opening bracket is missing the option text is treated as literal.
        BOOST_CHECK_EQUAL(formattedText, "Prefix 42yyy} suffix.");
    }
    {
        FormatSPtr format = Format::parse("Prefix %linexxx}{yyy} suffix.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Here, the missing opening bracket on the first option results in the second option being treated as literal
        // too, because there is no conversion pattern in front of it.
        BOOST_CHECK_EQUAL(formattedText, "Prefix 42xxx}{yyy} suffix.");
    }
}

//==============================================================================
// DateFormatter
//==============================================================================
BOOST_FIXTURE_TEST_CASE(checkDate, Fixture)
{
    TestSupport::printTestName();

    // No date format.
    {
        FormatSPtr format = Format::parse("%date");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        std::string timestampString = getTimestampString(msg, "%x %X");

        BOOST_TEST_MESSAGE("Expecting: " << timestampString);
        BOOST_CHECK_EQUAL(formattedText, timestampString);
    }

    // Default date format.
    {
        FormatSPtr format = Format::parse("%date{DEFAULT}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        std::string timestampString = getTimestampString(msg, "%Y-%m-%d %H:%M:%S");

        BOOST_TEST_MESSAGE("Expecting: " << timestampString);
        BOOST_CHECK_EQUAL(formattedText, timestampString);
    }

    // Sample strftime format.
    {
        FormatSPtr format = Format::parse("%date{%S*%M*%H|%d+%m+%Y}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        std::string timestampString = getTimestampString(msg, "%S*%M*%H|%d+%m+%Y", false);

        BOOST_TEST_MESSAGE("Expecting: " << timestampString);
        BOOST_CHECK_EQUAL(formattedText, timestampString);
    }

    // UNIX timestamp.
    {
        FormatSPtr format = Format::parse("%date{UNIX}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        std::chrono::system_clock::duration timeSinceEpoch = msg->getTimestamp().time_since_epoch();
        std::stringstream stream;
        stream << timeSinceEpoch.count() * std::chrono::system_clock::period::num
                      / std::chrono::system_clock::period::den;

        std::string timestampString = stream.str();

        BOOST_TEST_MESSAGE("Expecting: " << timestampString);
        BOOST_CHECK_EQUAL(formattedText, timestampString);
    }

    // UNIX timestamp with milliseconds.
    {
        FormatSPtr format = Format::parse("%date{UNIX_MILLIS}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        std::chrono::system_clock::duration timeSinceEpoch = msg->getTimestamp().time_since_epoch();
        std::stringstream stream;
        stream << timeSinceEpoch.count() * std::chrono::system_clock::period::num
                      / (std::chrono::system_clock::period::den / 1000);

        std::string timestampString = stream.str();

        BOOST_TEST_MESSAGE("Expecting: " << timestampString);
        BOOST_CHECK_EQUAL(formattedText, timestampString);
    }

    // Invalid date format.
    {
        FormatSPtr format = Format::parse("%date{xxx}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // The invalid format is forwarded to strftime which treats it as literal!
        BOOST_CHECK_EQUAL(formattedText, "xxx");
    }
}

//==============================================================================
// FilePathFormatter
//==============================================================================
BOOST_FIXTURE_TEST_CASE(checkFilePathNonRoot, Fixture)
{
    TestSupport::printTestName();

    std::string filePath{std::string("subdir1") + FilePathFormatter::pathSeparator + "subdir2"
                         + FilePathFormatter::pathSeparator + "subdir3" + FilePathFormatter::pathSeparator
                         + "fileName"};

    // No precision.
    {
        FormatSPtr format = Format::parse("%file");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }

    // Precision = 0.
    {
        FormatSPtr format = Format::parse("%file{0}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }

    // Precision = 1.
    {
        FormatSPtr format = Format::parse("%file{1}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "fileName");
    }

    // Precision = 2.
    {
        FormatSPtr format = Format::parse("%file{2}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        std::string expected{std::string("subdir3") + FilePathFormatter::pathSeparator + "fileName"};
        BOOST_CHECK_EQUAL(formattedText, expected);
    }

    // Precision = 3.
    {
        FormatSPtr format = Format::parse("%file{3}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        std::string expected{std::string("subdir2") + FilePathFormatter::pathSeparator + "subdir3"
                             + FilePathFormatter::pathSeparator + "fileName"};
        BOOST_CHECK_EQUAL(formattedText, expected);
    }

    // Precision = 4.
    {
        FormatSPtr format = Format::parse("%file{4}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }

    // Precision = 5.
    {
        FormatSPtr format = Format::parse("%file{5}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }

    // Invalid precision -> ignore error and use default.
    {
        FormatSPtr format = Format::parse("%file{xxx}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkFilePathRoot, Fixture)
{
    TestSupport::printTestName();

    std::string filePath{std::string(1, FilePathFormatter::pathSeparator) + "subdir" + FilePathFormatter::pathSeparator
                         + "fileName"};

    // No precision.
    {
        FormatSPtr format = Format::parse("%file");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }

    // Precision = 0.
    {
        FormatSPtr format = Format::parse("%file{0}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }

    // Precision = 1.
    {
        FormatSPtr format = Format::parse("%file{1}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "fileName");
    }

    // Precision = 2.
    {
        FormatSPtr format = Format::parse("%file{2}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        std::string expected{std::string("subdir") + FilePathFormatter::pathSeparator + "fileName"};
        BOOST_CHECK_EQUAL(formattedText, expected);
    }

    // Precision = 3.
    {
        FormatSPtr format = Format::parse("%file{3}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkFilePathNameOnly, Fixture)
{
    TestSupport::printTestName();

    std::string filePath{"fileName"};

    // No precision.
    {
        FormatSPtr format = Format::parse("%file");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }

    // Precision = 0.
    {
        FormatSPtr format = Format::parse("%file{0}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }

    // Precision = 1.
    {
        FormatSPtr format = Format::parse("%file{1}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }

    // Precision = 2.
    {
        FormatSPtr format = Format::parse("%file{2}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", filePath.c_str(), "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, filePath);
    }
}

//==============================================================================
// FunctionNameFormatter
//==============================================================================
BOOST_FIXTURE_TEST_CASE(checkFunctionName, Fixture)
{
    TestSupport::printTestName();

    {
        FormatSPtr format = Format::parse("%func");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "testFunction");
    }

    {
        FormatSPtr format = Format::parse("%function");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "testFunction");
    }
}

//==============================================================================
// LineNumberFormatter
//==============================================================================
BOOST_FIXTURE_TEST_CASE(checkLineNumber, Fixture)
{
    TestSupport::printTestName();

    FormatSPtr format = Format::parse("%line");
    MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
    std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

    BOOST_CHECK_EQUAL(formattedText, "42");
}

//==============================================================================
// LoggerIdFormatter
//==============================================================================
BOOST_FIXTURE_TEST_CASE(checkLoggerIdNamespace, Fixture)
{
    TestSupport::printTestName();

    std::string loggerId{"namespace1::namespace2::classname"};

    // No precision.
    {
        FormatSPtr format = Format::parse("%logger");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText(loggerId, LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, loggerId);
    }

    // Precision = 0.
    {
        FormatSPtr format = Format::parse("%logger{0}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText(loggerId, LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, loggerId);
    }

    // Precision = 1.
    {
        FormatSPtr format = Format::parse("%logger{1}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText(loggerId, LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "classname");
    }

    // Precision = 2.
    {
        FormatSPtr format = Format::parse("%logger{2}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText(loggerId, LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "namespace2::classname");
    }

    // Precision = 3.
    {
        FormatSPtr format = Format::parse("%logger{3}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText(loggerId, LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "namespace1::namespace2::classname");
    }

    // Precision = 4.
    {
        FormatSPtr format = Format::parse("%logger{4}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText(loggerId, LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, loggerId);
    }

    // Invalid precision -> ignore error and use default.
    {
        FormatSPtr format = Format::parse("%logger{xxx}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText(loggerId, LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, loggerId);
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkLoggerIdClassnameOnly, Fixture)
{
    TestSupport::printTestName();

    std::string loggerId{"classname"};

    // No precision.
    {
        FormatSPtr format = Format::parse("%logger");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText(loggerId, LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, loggerId);
    }

    // Precision = 0.
    {
        FormatSPtr format = Format::parse("%logger{0}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText(loggerId, LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, loggerId);
    }

    // Precision = 1.
    {
        FormatSPtr format = Format::parse("%logger{1}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText(loggerId, LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, loggerId);
    }

    // Precision = 2.
    {
        FormatSPtr format = Format::parse("%logger{2}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText(loggerId, LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, loggerId);
    }
}

//==============================================================================
// LogLevelFormatter
//==============================================================================
BOOST_FIXTURE_TEST_CASE(checkLogLevel, Fixture)
{
    TestSupport::printTestName();

    FormatSPtr format = Format::parse("%level");
    MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};

    std::string formattedText;

    formattedText = format->getFormattedText("loggerId", LogLevel::Off, msg);
    BOOST_CHECK_EQUAL(formattedText, "OFF");

    formattedText = format->getFormattedText("loggerId", LogLevel::Critical, msg);
    BOOST_CHECK_EQUAL(formattedText, "CRITICAL");

    formattedText = format->getFormattedText("loggerId", LogLevel::Error, msg);
    BOOST_CHECK_EQUAL(formattedText, "ERROR");

    formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);
    BOOST_CHECK_EQUAL(formattedText, "WARNING");

    formattedText = format->getFormattedText("loggerId", LogLevel::Info, msg);
    BOOST_CHECK_EQUAL(formattedText, "INFO");

    formattedText = format->getFormattedText("loggerId", LogLevel::Trace, msg);
    BOOST_CHECK_EQUAL(formattedText, "TRACE");

    formattedText = format->getFormattedText("loggerId", LogLevel::Debug, msg);
    BOOST_CHECK_EQUAL(formattedText, "DEBUG");
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkLogLevelLength, Fixture)
{
    TestSupport::printTestName();

    static const std::string levelString{"ERROR"};
    static const LogLevel level{parseLogLevel(levelString.c_str())};

    MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};

    for (std::size_t len = 0; len <= levelString.length() + 1; ++len)
    {
        std::stringstream stream;
        stream << "%level{length=" << len << "}";
        FormatSPtr format         = Format::parse(stream.str().c_str());
        std::string formattedText = format->getFormattedText("loggerId", level, msg);

        std::string expected = levelString.substr(0, len);
        BOOST_CHECK_EQUAL(formattedText, expected);
    }

    // Check invalid length -> ignore error gracefully and use whole text.
    {
        FormatSPtr format         = Format::parse("%level{length=xxx}");
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Error, msg);

        BOOST_CHECK_EQUAL(formattedText, "ERROR");
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkLogLevelLowerCase, Fixture)
{
    TestSupport::printTestName();

    // Default -> upper case.
    {
        FormatSPtr format = Format::parse("%level");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};

        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Error, msg);
        BOOST_CHECK_EQUAL(formattedText, "ERROR");
    }

    // Lower case.
    {
        FormatSPtr format = Format::parse("%level{lowerCase=true}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};

        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Error, msg);
        BOOST_CHECK_EQUAL(formattedText, "error");
    }

    // Upper case.
    {
        FormatSPtr format = Format::parse("%level{lowerCase=false}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};

        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Error, msg);
        BOOST_CHECK_EQUAL(formattedText, "ERROR");
    }

    // Invalid value -> use default.
    {
        FormatSPtr format = Format::parse("%level{lowerCase=xxx}");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};

        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Error, msg);
        BOOST_CHECK_EQUAL(formattedText, "ERROR");
    }
}

//==============================================================================
// MessageFormatter
//==============================================================================
BOOST_FIXTURE_TEST_CASE(checkMessage, Fixture)
{
    TestSupport::printTestName();

    {
        FormatSPtr format = Format::parse("%msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }

    {
        FormatSPtr format = Format::parse("%message");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
}

//==============================================================================
// SequenceNumberFormatter
//==============================================================================
BOOST_FIXTURE_TEST_CASE(checkSequenceNumber, Fixture)
{
    TestSupport::printTestName();

    {
        FormatSPtr format = Format::parse("%seqNo");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_TEST_MESSAGE("Testing sequence number " << msg->getSequenceNumber() << "...");

        std::stringstream stream;
        stream << msg->getSequenceNumber();

        BOOST_CHECK_EQUAL(formattedText, stream.str());
    }

    {
        FormatSPtr format = Format::parse("%sequenceNumber");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_TEST_MESSAGE("Testing sequence number " << msg->getSequenceNumber() << "...");

        std::stringstream stream;
        stream << msg->getSequenceNumber();

        BOOST_CHECK_EQUAL(formattedText, stream.str());
    }
}

//==============================================================================
// ThreadIdFormatter
//==============================================================================
BOOST_FIXTURE_TEST_CASE(checkThreadId, Fixture)
{
    TestSupport::printTestName();

    FormatSPtr format = Format::parse("%thread");
    MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
    std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

    BOOST_TEST_MESSAGE("Testing thread ID " << std::this_thread::get_id() << "...");

    std::stringstream stream;
    stream << std::this_thread::get_id();

    BOOST_CHECK_EQUAL(formattedText, stream.str());
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

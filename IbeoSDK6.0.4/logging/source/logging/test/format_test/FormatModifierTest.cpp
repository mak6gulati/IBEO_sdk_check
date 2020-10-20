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

#define BOOST_TEST_MODULE FormatModifierTest

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

class Fixture
{
public:
    Fixture()  = default;
    ~Fixture() = default;
}; // Fixture

//==============================================================================
BOOST_AUTO_TEST_SUITE(FormatModifierTestSuite)
//==============================================================================

//==============================================================================
// FormatModifier
//==============================================================================

// Valid modifier pattern are (e.g. when printing the message):
//                  align       min. width       max. width
//   %20msg         right           20              none
//   %-20msg        left            20              none
//   %.30msg         n/a           none              30         truncate from left
//   %.-30msg        n/a           none              30         truncate from right
//   %20.30msg      right           20               30         truncate from left
//   %20.-30msg     right           20               30         truncate from right
//   %-20.30msg     left            20               30         truncate from left
//   %-20.-30msg    left            20               30         truncate from right

BOOST_FIXTURE_TEST_CASE(checkFormatModifier, Fixture)
{
    TestSupport::printTestName();

    // No modifier.
    {
        FormatSPtr format = Format::parse("%msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }

    // Invalid alignment char.
    {
        FormatSPtr format = Format::parse("%+msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Invalid format modifiers are treated as literal text.
        BOOST_CHECK_EQUAL(formattedText, "%+msg");
    }

    // Invalid truncation char.
    {
        FormatSPtr format = Format::parse("%.+msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Invalid format modifiers are treated as literal text.
        BOOST_CHECK_EQUAL(formattedText, "%.+msg");
    }

    // Missing min. length.
    {
        FormatSPtr format = Format::parse("%-msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Invalid format modifiers are treated as literal text.
        BOOST_CHECK_EQUAL(formattedText, "%-msg");
    }

    // Missing max. length.
    {
        FormatSPtr format = Format::parse("%.msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Invalid format modifiers are treated as literal text.
        BOOST_CHECK_EQUAL(formattedText, "%.msg");
    }

    // Alignment character at end of format string.
    {
        FormatSPtr format = Format::parse("%-");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Invalid format modifiers are treated as literal text.
        BOOST_CHECK_EQUAL(formattedText, "%-");
    }

    // Min./max. width separator character at end of format string.
    {
        FormatSPtr format = Format::parse("%.");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Invalid format modifiers are treated as literal text.
        BOOST_CHECK_EQUAL(formattedText, "%.");
    }

    // Truncation character at end of format string.
    {
        FormatSPtr format = Format::parse("%.-");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        // Invalid format modifiers are treated as literal text.
        BOOST_CHECK_EQUAL(formattedText, "%.-");
    }
}

BOOST_FIXTURE_TEST_CASE(checkFormatModifierMinLength, Fixture)
{
    TestSupport::printTestName();

    // Too short, pad left.
    {
        FormatSPtr format = Format::parse("%13msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, " message text");
    }

    // Too short, pad right.
    {
        FormatSPtr format = Format::parse("%-13msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text ");
    }

    // Exact length (no padding).
    {
        FormatSPtr format = Format::parse("%12msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
    {
        FormatSPtr format = Format::parse("%-12msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }

    // Too long (no padding).
    {
        FormatSPtr format = Format::parse("%11msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
    {
        FormatSPtr format = Format::parse("%-11msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
}

BOOST_FIXTURE_TEST_CASE(checkFormatModifierMaxLength, Fixture)
{
    TestSupport::printTestName();

    // Too long, truncate from beginning.
    {
        FormatSPtr format = Format::parse("%.11msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "essage text");
    }

    // Too long, truncate from end.
    {
        FormatSPtr format = Format::parse("%.-11msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message tex");
    }

    // Exact size.
    {
        FormatSPtr format = Format::parse("%.12msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
    {
        FormatSPtr format = Format::parse("%.-12msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }

    // Too short.
    {
        FormatSPtr format = Format::parse("%.13msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
    {
        FormatSPtr format = Format::parse("%.-13msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
}

BOOST_FIXTURE_TEST_CASE(checkFormatModifierLengthRange, Fixture)
{
    TestSupport::printTestName();

    // Too long, truncate from beginning.
    {
        FormatSPtr format = Format::parse("%10.11msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "essage text");
    }
    {
        FormatSPtr format = Format::parse("%-10.11msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "essage text");
    }

    // Too long, truncate from end.
    {
        FormatSPtr format = Format::parse("%10.-11msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message tex");
    }
    {
        FormatSPtr format = Format::parse("%-10.-11msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message tex");
    }

    // Exact size, no truncation.
    {
        FormatSPtr format = Format::parse("%11.12msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
    {
        FormatSPtr format = Format::parse("%-11.12msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
    {
        FormatSPtr format = Format::parse("%11.-12msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
    {
        FormatSPtr format = Format::parse("%-11.-12msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }

    // Exact size, no padding.
    {
        FormatSPtr format = Format::parse("%12.13msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
    {
        FormatSPtr format = Format::parse("%-12.13msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
    {
        FormatSPtr format = Format::parse("%12.-13msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }
    {
        FormatSPtr format = Format::parse("%-12.-13msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text");
    }

    // Too short, pad left.
    {
        FormatSPtr format = Format::parse("%13.14msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, " message text");
    }
    {
        FormatSPtr format = Format::parse("%13.-14msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, " message text");
    }

    // Too short, pad right.
    {
        FormatSPtr format = Format::parse("%-13.14msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text ");
    }
    {
        FormatSPtr format = Format::parse("%-13.-14msg");
        MessageSPtr msg{std::make_shared<Message>(42, "testFunction", "testFile", "message text")};
        std::string formattedText = format->getFormattedText("loggerId", LogLevel::Warning, msg);

        BOOST_CHECK_EQUAL(formattedText, "message text ");
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

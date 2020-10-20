//==============================================================================
//!\file
//!\brief Test for Message class.
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

#define BOOST_TEST_MODULE MessageTest

#include <boost/test/unit_test.hpp>

#include <ibeo/common/logging/logging.hpp>

#include <StringEx.hpp>
#include <TestSupport.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>

//==============================================================================

using namespace ibeo::common::logging;

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
namespace unittest {
//==============================================================================

//==============================================================================
BOOST_AUTO_TEST_SUITE(MessageTestSuite)
//==============================================================================

BOOST_AUTO_TEST_CASE(checkStringTypes)
{
    TestSupport::printTestName();

    MessageSPtr msg = std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__, "Test string types: ");
    msg << endl << "This is a string.";

    std::istringstream ss{msg->getText()};
    StringEx header;
    std::getline(ss, header);
    BOOST_CHECK(header.endsWith("Test string types: "));

    StringEx text;
    std::getline(ss, text);
    BOOST_CHECK_EQUAL(text.compare("This is a string."), 0);

    std::getline(ss, text);
    BOOST_CHECK(ss.eof()); // no more output

    BOOST_TEST_MESSAGE(msg->getText());
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkIntegerTypes)
{
    TestSupport::printTestName();

    MessageSPtr msg = std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__, "Test integer types: ");
    msg << endl
        << "This is an int16_t: " << static_cast<int16_t>(-4242) << endl
        << "This is an uint16_t: " << static_cast<uint16_t>(4242) << endl
        << "This is an int32_t: " << static_cast<int32_t>(-42424242) << endl
        << "This is an uint32_t: " << static_cast<uint32_t>(42424242) << endl
        << "This is an int64_t: " << static_cast<int64_t>(-424242424242) << endl
        << "This is an uint64_t: " << static_cast<uint64_t>(424242424242);
    // The types int8_t and uint8_t are treated as chars and do not produce numbers in the stream.

    std::istringstream ss{msg->getText()};
    StringEx header;
    std::getline(ss, header);
    BOOST_CHECK(header.endsWith("Test integer types: "));

    StringEx text;

    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("-4242"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("4242"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("-42424242"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("42424242"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("-424242424242"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("424242424242"));

    std::getline(ss, text);
    BOOST_CHECK(ss.eof()); // no more output

    BOOST_TEST_MESSAGE(msg->getText());
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkFloatTypes)
{
    TestSupport::printTestName();

    MessageSPtr msg = std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__, "Test float types: ");
    msg << endl << "This is a float: " << -4242.4242F << endl << "This is a double: " << -4242.4242;

    std::istringstream ss{msg->getText()};
    StringEx header;
    std::getline(ss, header);
    BOOST_CHECK(header.endsWith("Test float types: "));

    StringEx text;

    // Floating number are printed with a default precision of two.
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("-4242.42"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("-4242.42"));

    std::getline(ss, text);
    BOOST_CHECK(ss.eof()); // no more output

    BOOST_TEST_MESSAGE(msg->getText());
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkHexManipulator)
{
    TestSupport::printTestName();

    MessageSPtr msg = std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__, "Test hex manipulator: ");
    msg << endl << "This is hex: " << std::hex << 42 << endl << "This is dec: " << std::dec << 42;

    std::istringstream ss{msg->getText()};
    StringEx header;
    std::getline(ss, header);
    BOOST_CHECK(header.endsWith("Test hex manipulator: "));

    StringEx text;

    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("2a"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("42"));

    std::getline(ss, text);
    BOOST_CHECK(ss.eof()); // no more output

    BOOST_TEST_MESSAGE(msg->getText());
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkWidthManipulator)
{
    TestSupport::printTestName();

    MessageSPtr msg = std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__, "Test width manipulator: ");
    msg << endl
        << "This is width 4 (' '): " << std::setw(4) << 42 << endl
        << "This is width 4 ('0'): " << std::setw(4) << std::setfill('0') << 42 << endl
        << "This is width 8 (' '): " << std::setw(8) << std::setfill(' ') << 42 << endl
        << "This is width 8 ('0'): " << std::setw(8) << std::setfill('0') << 42;

    std::istringstream ss{msg->getText()};
    StringEx header;
    std::getline(ss, header);
    BOOST_CHECK(header.endsWith("Test width manipulator: "));

    StringEx text;

    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("  42"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("0042"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("      42"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("00000042"));

    std::getline(ss, text);
    BOOST_CHECK(ss.eof()); // no more output

    BOOST_TEST_MESSAGE(msg->getText());
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkFloatingPrecisionManipulator)
{
    TestSupport::printTestName();

    MessageSPtr msg
        = std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__, "Test floating precision manipulator: ");
    msg << endl
        << "This is floating precision 6: " << std::setprecision(6) << -4242.4242 << endl
        << "This is floating precision 8: " << std::setprecision(8) << -4242.4242;

    std::istringstream ss{msg->getText()};
    StringEx header;
    std::getline(ss, header);
    BOOST_CHECK(header.endsWith("Test floating precision manipulator: "));

    StringEx text;

    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("-4242.42"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("-4242.4242"));

    std::getline(ss, text);
    BOOST_CHECK(ss.eof()); // no more output

    BOOST_TEST_MESSAGE(msg->getText());
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkFixedPrecisionManipulator)
{
    TestSupport::printTestName();

    MessageSPtr msg = std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__);
    msg << "Test fixed precision manipulator: " << endl
        << "This is fixed precision 2: " << std::fixed << std::setprecision(2) << -4242.4242 << endl
        << "This is fixed precision 6: " << std::fixed << std::setprecision(6) << -4242.4242;

    std::istringstream ss{msg->getText()};

    StringEx header;
    std::getline(ss, header);
    BOOST_CHECK(header.endsWith("Test fixed precision manipulator: "));

    StringEx text;

    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("-4242.42"));
    std::getline(ss, text);
    BOOST_CHECK(text.endsWith("-4242.424200"));

    std::getline(ss, text);
    BOOST_CHECK(ss.eof()); // no more output

    BOOST_TEST_MESSAGE(msg->getText());
}

//==============================================================================

BOOST_AUTO_TEST_CASE(checkOverflow)
{
    static const std::size_t initialBufferSize{256};

    TestSupport::printTestName();

    MessageSPtr msg = std::make_shared<Message>(__LINE__, __FUNCTION__, __FILE__, "Test overflow: ");
    msg << endl;
    for (std::size_t i = 0; i < initialBufferSize; ++i)
    {
        msg << static_cast<char>('A' + (i % 26)) << static_cast<char>('a' + (i % 26));
    }
    std::istringstream ss{msg->getText()};
    StringEx header;
    std::getline(ss, header);
    BOOST_CHECK(header.endsWith("Test overflow: "));

    StringEx text;

    std::getline(ss, text);
    for (std::size_t i = 0; i < initialBufferSize; ++i)
    {
        BOOST_CHECK_EQUAL(text[i * 2], static_cast<char>('A' + (i % 26)));
        BOOST_CHECK_EQUAL(text[i * 2 + 1], static_cast<char>('a' + (i % 26)));
    }

    BOOST_TEST_MESSAGE(msg->getText());
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

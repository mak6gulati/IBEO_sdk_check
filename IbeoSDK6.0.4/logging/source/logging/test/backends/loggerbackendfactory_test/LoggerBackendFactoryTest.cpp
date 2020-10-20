//==============================================================================
//!\file
//!\brief Test for LoggerBackendFactory class.
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

#define BOOST_TEST_MODULE LoggerBackendFactoryTest

//==============================================================================

#include <boost/test/unit_test.hpp>

#include <ibeo/common/logging/logging.hpp>
#include <TestSupport.hpp>

#include <iostream>

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
    void log(const std::string&, const LogLevel&, const MessageSPtr) override
    {
        std::cout << "This is backend ID '" << getId() << "'." << std::endl;
    }
};

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
BOOST_AUTO_TEST_SUITE(LoggerBackendFactoryTestSuite)
//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkRegisterBackend, Fixture)
{
    TestSupport::printTestName();

    const std::string backendId{"CustomLoggerBackend"};

    {
        // Backend should not be in the list.
        LoggerBackendSPtr backend = LogManager::getInstance().getBackendById(backendId);
        BOOST_CHECK_EQUAL(backend.get(), static_cast<LoggerBackend*>(nullptr));
    }

    {
        LoggerBackendSPtr backend = std::make_shared<CustomLoggerBackend>(backendId);
        BOOST_CHECK(LogManager::getInstance().registerBackend(backend));

        // Backend should be in the list now.
        backend = LogManager::getInstance().getBackendById(backendId);
        BOOST_CHECK(backend.get());
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkRegisterTwoBackends, Fixture)
{
    TestSupport::printTestName();

    const std::string backendId1{"CustomLoggerBackend1"};
    const std::string backendId2{"CustomLoggerBackend2"};

    {
        // Backends should not be in the list.
        LoggerBackendSPtr backend1 = LogManager::getInstance().getBackendById(backendId1);
        BOOST_CHECK_EQUAL(backend1.get(), static_cast<LoggerBackend*>(nullptr));

        LoggerBackendSPtr backend2 = LogManager::getInstance().getBackendById(backendId2);
        BOOST_CHECK_EQUAL(backend2.get(), static_cast<LoggerBackend*>(nullptr));
    }

    {
        // Register backends.
        LoggerBackendSPtr backend1 = std::make_shared<CustomLoggerBackend>(backendId1);
        BOOST_CHECK(LogManager::getInstance().registerBackend(backend1));

        LoggerBackendSPtr backend2 = std::make_shared<CustomLoggerBackend>(backendId2);
        BOOST_CHECK(LogManager::getInstance().registerBackend(backend2));

        // Backend should be in the list now.
        backend1 = LogManager::getInstance().getBackendById(backendId1);
        BOOST_CHECK(backend1.get());

        backend2 = LogManager::getInstance().getBackendById(backendId2);
        BOOST_CHECK(backend2.get());

        // Backends should be different objects.
        BOOST_CHECK_NE(backend1.get(), backend2.get());
        BOOST_CHECK_EQUAL(backend1->getId(), backendId1);
        BOOST_CHECK_EQUAL(backend2->getId(), backendId2);
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkRegisterSameBackendTwice, Fixture)
{
    TestSupport::printTestName();

    const std::string backendId{"CustomLoggerBackend"};

    // Register first time.
    LoggerBackendSPtr backend1 = std::make_shared<CustomLoggerBackend>(backendId);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend1));

    backend1 = LogManager::getInstance().getBackendById(backendId);
    BOOST_CHECK(backend1.get());

    // Register second time.
    LoggerBackendSPtr backend2 = std::make_shared<CustomLoggerBackend>(backendId);
    BOOST_CHECK_NE(backend1.get(), backend2.get()); // Backends should be different objects.

    // Registration should fail as there is already a backend registered for this ID.
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend2) == false);

    backend2 = LogManager::getInstance().getBackendById(backendId);
    BOOST_CHECK(backend2.get());
    BOOST_CHECK_EQUAL(backend1.get(), backend2.get()); // Backends should be the same object now.
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkFindExistingBackend, Fixture)
{
    TestSupport::printTestName();

    const char* backendIdString = "CustomLoggerBackend";

    // Register backend.
    LoggerBackendSPtr backend = std::make_shared<CustomLoggerBackend>(backendIdString);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend));

    // Get backend -> should be successful.
    backend = LogManager::getInstance().getBackendById(backendIdString);
    BOOST_CHECK_NE(backend.get(), static_cast<LoggerBackend*>(nullptr));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkFindNonExistingBackend, Fixture)
{
    TestSupport::printTestName();

    const char* backendIdString1 = "CustomLoggerBackend1";
    const char* backendIdString2 = "CustomLoggerBackend2";

    // Register backend with ID 1.
    LoggerBackendSPtr backend1 = std::make_shared<CustomLoggerBackend>(backendIdString1);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend1));

    // Get backend with ID 2 -> should fail.
    LoggerBackendSPtr backend2 = LogManager::getInstance().getBackendById(backendIdString2);
    BOOST_CHECK_EQUAL(backend2.get(), static_cast<LoggerBackend*>(nullptr));
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

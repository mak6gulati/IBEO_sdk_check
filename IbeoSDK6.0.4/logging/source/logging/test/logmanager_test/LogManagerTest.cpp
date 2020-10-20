//==============================================================================
//!\file
//!\brief Test for Setup class.
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

#define BOOST_TEST_MODULE LogManagerTest

//==============================================================================

#include <boost/test/unit_test.hpp>

#include <ibeo/common/logging/logging.hpp>
#include <TestSupport.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>

#include <fstream>

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
    Fixture()
    {
        // Reset (static) state of logger classes.
        LogManager::getInstance().reset();
    }

    ~Fixture() = default;
}; // Fixture

//==============================================================================

class CustomLoggerBackend : public LoggerBackend
{
public:
    CustomLoggerBackend(const std::string& backendId) : LoggerBackend(backendId) {}

    void log(const std::string&, const LogLevel&, const MessageSPtr) override
    {
        // Not used.
    }

    bool configure(const tinyxml2::XMLElement* const xmlNode, const bool suppressErrors) override
    {
        if (LoggerBackend::configure(xmlNode, suppressErrors) == false)
        {
            // Configuring failed -> give up.
            return false;
        }

        const tinyxml2::XMLElement* parameterNode = xmlNode->FirstChildElement("Parameter");
        if (parameterNode != nullptr)
        {
            m_parameter = parameterNode->GetText();
            return true;
        }
        else
        {
            m_parameter.reset();
            return false;
        }
    }

    bool isParameterGiven() const { return m_parameter.is_initialized(); }
    std::string getParameter() const { return m_parameter.get(); }

private:
    boost::optional<std::string> m_parameter;
};

//==============================================================================
BOOST_AUTO_TEST_SUITE(LogManagerTestSuite)
//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkGlobalLogger, Fixture)
{
    TestSupport::printTestName();

    // No loggers should have been created initially.
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 0);

    // Create global logger.
    LoggerSPtr logger = LogManager::globalLogger();
    BOOST_CHECK_EQUAL(logger->getId(), "ibeo::common::logging::GlobalLogger");
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger->getLogLevel()), static_cast<uint16_t>(LogLevel::Error));

    // A new logger should have been created.
    BOOST_CHECK_EQUAL(LogManager::getInstance().getLoggers().size(), 1);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkLoadNonExistingConfigFile, Fixture)
{
    TestSupport::printTestName();

    std::string fileName
        = std::string("Test_") + boost::lexical_cast<std::string>((boost::uuids::random_generator())()) + ".config";

    // Load config should fail.
    BOOST_CHECK_EQUAL(LogManager::getInstance().loadConfig(fileName), false);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkLoadConfigFile, Fixture)
{
    TestSupport::printTestName();

    std::string tempPath = "";
    std::ofstream configFile;
    try
    {
        // Create a temporary file with a minimal but valid logging configuration.
        static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                             "<Configuration>"
                                             "</Configuration>";

        tempPath = boost::filesystem::unique_path().make_preferred().string();
        configFile.open(tempPath);
        configFile << configXml;
        configFile.close();

        // Load config should be successful.
        BOOST_CHECK(LogManager::getInstance().loadConfig(tempPath));

        // Remove temporary config file.
        std::remove(tempPath.c_str());
    }
    catch (...)
    {
        // Close and remove temporary config file.
        if (configFile.is_open())
        {
            configFile.close();
        }

        if (tempPath.empty() == false)
        {
            std::remove(tempPath.c_str());
        }

        throw;
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigXmlFormatViolation, Fixture)
{
    TestSupport::printTestName();

    static const std::string badConfigXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                            "<Configuration>"
                                            "</xxConfiguration>";

    // Parsing the config should fail.
    BOOST_CHECK_EQUAL(LogManager::getInstance().parseConfig(badConfigXml), false);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigMandatoryElementMissing, Fixture)
{
    TestSupport::printTestName();

    static const std::string badConfigXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                            "<xxConfiguration>"
                                            "</xxConfiguration>";

    // Parsing the config should fail.
    BOOST_CHECK_EQUAL(LogManager::getInstance().parseConfig(badConfigXml), false);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigBackend, Fixture)
{
    TestSupport::printTestName();

    // Register custom backend.
    std::string backendId                               = "CustomBackend";
    const std::shared_ptr<CustomLoggerBackend>& backend = std::make_shared<CustomLoggerBackend>(backendId);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend));

    static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                         "<Configuration>"
                                         "  <Backends>"
                                         "    <Backend id=\"CustomBackend\""
                                         "             format=\"not used\">"
                                         "      <Parameter>parameterValue</Parameter>"
                                         "    </Backend>"
                                         "  </Backends>"
                                         "</Configuration>";

    // Parsing the config should be successful.
    BOOST_CHECK(LogManager::getInstance().parseConfig(configXml));

    // Check parameter value.
    BOOST_CHECK(backend->isParameterGiven());
    BOOST_CHECK_EQUAL(backend->getParameter(), "parameterValue");
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigBackendNotFound, Fixture)
{
    TestSupport::printTestName();

    // Register custom backend.
    std::string backendId                               = "CustomBackend";
    const std::shared_ptr<CustomLoggerBackend>& backend = std::make_shared<CustomLoggerBackend>(backendId);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend));

    static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                         "<Configuration>"
                                         "  <Backends>"
                                         "    <Backend id=\"NonExistingBackend\""
                                         "             format=\"not used\">"
                                         "    </Backend>"
                                         "  </Backends>"
                                         "</Configuration>";

    // Parsing the config should be successful.
    BOOST_CHECK(LogManager::getInstance().parseConfig(configXml));

    // Check that backend was not configured.
    BOOST_CHECK_EQUAL(backend->isParameterGiven(), false);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigBackendFailed, Fixture)
{
    TestSupport::printTestName();

    // Register custom backend.
    std::string backendId                               = "CustomBackend";
    const std::shared_ptr<CustomLoggerBackend>& backend = std::make_shared<CustomLoggerBackend>(backendId);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend));

    static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                         "<Configuration>"
                                         "  <Backends>"
                                         "    <Backend id=\"CustomBackend\""
                                         "             format=\"not used\">"
                                         "    </Backend>"
                                         "  </Backends>"
                                         "</Configuration>";
    // Mandatory custom backend parameter missing.

    // Nevertheless, parsing the config should be successful.
    BOOST_CHECK(LogManager::getInstance().parseConfig(configXml));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigRootLogger, Fixture)
{
    TestSupport::printTestName();

    // Register custom backend.
    std::string backendId                               = "CustomBackend";
    const std::shared_ptr<CustomLoggerBackend>& backend = std::make_shared<CustomLoggerBackend>(backendId);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend));

    static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                         "<Configuration>"
                                         "  <Loggers>"
                                         "    <Root level=\"trace\">"
                                         "      <BackendRef id=\"CustomBackend\" />"
                                         "    </Root>"
                                         "  </Loggers>"
                                         "</Configuration>";

    // Get global logger as example for any unconfigured logger.
    LoggerSPtr globalLogger = LogManager::globalLogger();

    // Create default config (for comparison only).
    Configuration config;

    // Check default log level.
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(globalLogger->getLogLevel()),
                      static_cast<uint16_t>(config.getLogLevelForLogger(globalLogger->getId())));

    // Check default backends.
    std::list<std::string> globalLoggerBackendIds{globalLogger->getBackendIds()};
    std::list<std::string> defaultBackendIds{config.getBackendsForLogger(globalLogger->getId())};
    BOOST_CHECK_EQUAL_COLLECTIONS(globalLoggerBackendIds.begin(),
                                  globalLoggerBackendIds.end(),
                                  defaultBackendIds.begin(),
                                  defaultBackendIds.end());

    // Parsing the config should be successful.
    BOOST_CHECK(LogManager::getInstance().parseConfig(configXml));

    // Check configured log level.
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(globalLogger->getLogLevel()), static_cast<uint16_t>(LogLevel::Trace));

    // Check configured backends.
    globalLoggerBackendIds = globalLogger->getBackendIds();
    std::list<std::string> configuredBackendIds{backend->getId()};
    BOOST_CHECK_EQUAL_COLLECTIONS(globalLoggerBackendIds.begin(),
                                  globalLoggerBackendIds.end(),
                                  configuredBackendIds.begin(),
                                  configuredBackendIds.end());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigRootLoggerUnknownLogLevel, Fixture)
{
    TestSupport::printTestName();

    static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                         "<Configuration>"
                                         "  <Loggers>"
                                         "    <Root level=\"unknownLogLevel\">"
                                         "    </Root>"
                                         "  </Loggers>"
                                         "</Configuration>";

    // Get global logger as example for any unconfigured logger.
    LoggerSPtr globalLogger = LogManager::globalLogger();

    // Parsing the config should be successful.
    BOOST_CHECK(LogManager::getInstance().parseConfig(configXml));

    // Invalid values should set the log level to "Off".
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(globalLogger->getLogLevel()), static_cast<uint16_t>(LogLevel::Off));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigRootLoggerUnknownBackendRef, Fixture)
{
    TestSupport::printTestName();

    static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                         "<Configuration>"
                                         "  <Loggers>"
                                         "    <Root level=\"trace\">"
                                         "      <BackendRef id=\"UnknownBackend\" />"
                                         "    </Root>"
                                         "  </Loggers>"
                                         "</Configuration>";

    // Get global logger as example for any unconfigured logger.
    LoggerSPtr globalLogger = LogManager::globalLogger();

    // Parsing the config should be successful.
    BOOST_CHECK(LogManager::getInstance().parseConfig(configXml));

    // No backends should be connected to the logger now.
    BOOST_CHECK(globalLogger->getBackendIds().empty());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigSpecificLogger, Fixture)
{
    TestSupport::printTestName();

    // Register custom backend.
    std::string backendId                               = "CustomBackend";
    const std::shared_ptr<CustomLoggerBackend>& backend = std::make_shared<CustomLoggerBackend>(backendId);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend));

    static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                         "<Configuration>"
                                         "  <Loggers>"
                                         "    <Logger id=\"SpecificLogger\" level=\"trace\">"
                                         "      <BackendRef id=\"CustomBackend\" />"
                                         "    </Logger>"
                                         "  </Loggers>"
                                         "</Configuration>";

    // Create specific logger.
    LoggerSPtr logger = LogManager::getInstance().createLogger("SpecificLogger");

    // Create default config (for comparison only).
    Configuration config;

    // Check default log level.
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger->getLogLevel()),
                      static_cast<uint16_t>(config.getLogLevelForLogger(logger->getId())));

    // Check default backends.
    std::list<std::string> loggerBackendIds{logger->getBackendIds()};
    std::list<std::string> defaultBackendIds{config.getBackendsForLogger(logger->getId())};
    BOOST_CHECK_EQUAL_COLLECTIONS(
        loggerBackendIds.begin(), loggerBackendIds.end(), defaultBackendIds.begin(), defaultBackendIds.end());

    // Parsing the config should be successful.
    BOOST_CHECK(LogManager::getInstance().parseConfig(configXml));

    // Check configured log level.
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger->getLogLevel()), static_cast<uint16_t>(LogLevel::Trace));

    // Check configured backends.
    loggerBackendIds = logger->getBackendIds();
    std::list<std::string> configuredBackendIds{backend->getId()};
    BOOST_CHECK_EQUAL_COLLECTIONS(
        loggerBackendIds.begin(), loggerBackendIds.end(), configuredBackendIds.begin(), configuredBackendIds.end());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigSpecificLoggerUnknownLogLevel, Fixture)
{
    TestSupport::printTestName();

    static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                         "<Configuration>"
                                         "  <Loggers>"
                                         "    <Logger id=\"SpecificLogger\" level=\"unknownLogLevel\">"
                                         "    </Logger>"
                                         "  </Loggers>"
                                         "</Configuration>";

    // Create specific logger.
    LoggerSPtr logger = LogManager::getInstance().createLogger("SpecificLogger");

    // Parsing the config should be successful.
    BOOST_CHECK(LogManager::getInstance().parseConfig(configXml));

    // Invalid values should set the log level to "Off".
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger->getLogLevel()), static_cast<uint16_t>(LogLevel::Off));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigSpecificLoggerUnknownBackendRef, Fixture)
{
    TestSupport::printTestName();

    static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                         "<Configuration>"
                                         "  <Loggers>"
                                         "    <Logger id=\"SpecificLogger\" level=\"trace\">"
                                         "      <BackendRef id=\"UnknownBackend\" />"
                                         "    </Logger>"
                                         "  </Loggers>"
                                         "</Configuration>";

    // Create specific logger.
    LoggerSPtr logger = LogManager::getInstance().createLogger("SpecificLogger");

    // Parsing the config should be successful.
    BOOST_CHECK(LogManager::getInstance().parseConfig(configXml));

    // No backends should be connected to the logger now.
    BOOST_CHECK(logger->getBackendIds().empty());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigSpecificLoggerNotFound, Fixture)
{
    TestSupport::printTestName();

    // Register custom backend.
    std::string backendId                               = "CustomBackend";
    const std::shared_ptr<CustomLoggerBackend>& backend = std::make_shared<CustomLoggerBackend>(backendId);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend));

    static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                         "<Configuration>"
                                         "  <Loggers>"
                                         "  </Loggers>"
                                         "</Configuration>";

    // Create specific logger.
    LoggerSPtr logger = LogManager::getInstance().createLogger("SpecificLogger");

    // Create default config (for comparison only).
    Configuration config;

    // Check default log level.
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger->getLogLevel()),
                      static_cast<uint16_t>(config.getLogLevelForLogger(logger->getId())));

    // Check default backends.
    std::list<std::string> loggerBackendIds{logger->getBackendIds()};
    std::list<std::string> defaultBackendIds{config.getBackendsForLogger(logger->getId())};
    BOOST_CHECK_EQUAL_COLLECTIONS(
        loggerBackendIds.begin(), loggerBackendIds.end(), defaultBackendIds.begin(), defaultBackendIds.end());

    // Parsing the config should be successful.
    BOOST_CHECK(LogManager::getInstance().parseConfig(configXml));

    // Configuration should still be equal to default.
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger->getLogLevel()),
                      static_cast<uint16_t>(config.getLogLevelForLogger(logger->getId())));

    // Check configured backends.
    loggerBackendIds = logger->getBackendIds();
    BOOST_CHECK_EQUAL_COLLECTIONS(
        loggerBackendIds.begin(), loggerBackendIds.end(), defaultBackendIds.begin(), defaultBackendIds.end());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkConfigSpecificLoggerWildcard, Fixture)
{
    TestSupport::printTestName();

    // Register some custom backends.
    std::string backendId1                               = "CustomBackend1";
    const std::shared_ptr<CustomLoggerBackend>& backend1 = std::make_shared<CustomLoggerBackend>(backendId1);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend1));

    std::string backendId2                               = "CustomBackend2";
    const std::shared_ptr<CustomLoggerBackend>& backend2 = std::make_shared<CustomLoggerBackend>(backendId2);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend2));

    std::string backendId3                               = "CustomBackend3";
    const std::shared_ptr<CustomLoggerBackend>& backend3 = std::make_shared<CustomLoggerBackend>(backendId3);
    BOOST_CHECK(LogManager::getInstance().registerBackend(backend3));

    static const std::string configXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                         "<Configuration>"
                                         "  <Loggers>"
                                         "    <Logger id=\"namespace1::*\" level=\"critical\">"
                                         "      <BackendRef id=\"CustomBackend1\" />"
                                         "    </Logger>"
                                         "    <Logger id=\"namespace1::namespace2::*\" level=\"warning\">"
                                         "      <BackendRef id=\"CustomBackend2\" />"
                                         "    </Logger>"
                                         "    <Logger id=\"namespace1::namespace2::Logger3\" level=\"info\">"
                                         "      <BackendRef id=\"CustomBackend3\" />"
                                         "    </Logger>"
                                         "  </Loggers>"
                                         "</Configuration>";

    // Create some loggers.
    LoggerSPtr logger1 = LogManager::getInstance().createLogger("namespace1::namespace1::Logger1");
    LoggerSPtr logger2 = LogManager::getInstance().createLogger("namespace1::namespace2::Logger2");
    LoggerSPtr logger3 = LogManager::getInstance().createLogger("namespace1::namespace2::Logger3");
    LoggerSPtr logger4 = LogManager::getInstance().createLogger("namespace2::namespace3::Logger4");

    // Parsing the config should be successful.
    BOOST_CHECK(LogManager::getInstance().parseConfig(configXml));

    // Check configured log level.
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger1->getLogLevel()), static_cast<uint16_t>(LogLevel::Critical));
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger2->getLogLevel()), static_cast<uint16_t>(LogLevel::Warning));
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger3->getLogLevel()), static_cast<uint16_t>(LogLevel::Info));
    BOOST_CHECK_EQUAL(static_cast<uint16_t>(logger4->getLogLevel()),
                      static_cast<uint16_t>(LogLevel::Error)); // default log level

    // Check configured backends.
    std::list<std::string> loggerBackendIds;
    std::list<std::string> configuredBackendIds;

    loggerBackendIds     = logger1->getBackendIds();
    configuredBackendIds = {backend1->getId()};
    BOOST_CHECK_EQUAL_COLLECTIONS(
        loggerBackendIds.begin(), loggerBackendIds.end(), configuredBackendIds.begin(), configuredBackendIds.end());

    loggerBackendIds     = logger2->getBackendIds();
    configuredBackendIds = {backend2->getId()};
    BOOST_CHECK_EQUAL_COLLECTIONS(
        loggerBackendIds.begin(), loggerBackendIds.end(), configuredBackendIds.begin(), configuredBackendIds.end());

    loggerBackendIds     = logger3->getBackendIds();
    configuredBackendIds = {backend3->getId()};
    BOOST_CHECK_EQUAL_COLLECTIONS(
        loggerBackendIds.begin(), loggerBackendIds.end(), configuredBackendIds.begin(), configuredBackendIds.end());

    loggerBackendIds     = logger4->getBackendIds();
    configuredBackendIds = {ConsoleLoggerBackend::getBackendId()}; // default backend
    BOOST_CHECK_EQUAL_COLLECTIONS(
        loggerBackendIds.begin(), loggerBackendIds.end(), configuredBackendIds.begin(), configuredBackendIds.end());
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkLoggers, Fixture)
{
    TestSupport::printTestName();

    // Create logger.
    LoggerSPtr logger       = LogManager::getInstance().createLogger("Logger");
    LoggerSPtr globalLogger = LogManager::globalLogger();

    for (int i = 0; i < 3; ++i)
    {
        LOGCRITICAL(logger, "test message");
        LOGCRITICAL(globalLogger, "test message");
    }

    globalLogger.reset();
    logger.reset();

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

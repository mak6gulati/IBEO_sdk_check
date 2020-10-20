//==============================================================================
//!\file
//!\brief Default setup of logging with one call.
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jun 20, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/logging/LogManager.hpp>
#include <ibeo/common/logging/LoggerFactory.hpp>
#include <ibeo/common/logging/backends/ConsoleLoggerBackend.hpp>
#include <ibeo/common/logging/backends/FileLoggerBackend.hpp>

#include <tinyxml2.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

LogManager& LogManager::getInstance()
{
    static LogManager instance;
    return instance;
}

//==============================================================================

LogManager::LogManager() { reset(); }

//==============================================================================

LogManager::~LogManager()
{
    MutexGuard guard{m_globalLoggerMutex};

    m_globalLogger.reset();
    m_loggerFactory.reset();
    m_backendManager.reset();
}

//==============================================================================

void LogManager::reset()
{
    // Reset (static) state of log manager.
    m_backendManager = std::make_shared<LoggerBackendManager>();
    m_loggerFactory  = std::make_shared<LoggerFactory>(m_backendManager);
    m_globalLogger   = nullptr;

    registerDefaultBackends();

    // Try loading configuration from current working directory. If it does not exist, the default configuration is
    // used.
    loadConfig("logconfig.xml", true);
}

//==============================================================================

void LogManager::registerDefaultBackends()
{
    // Register default backends.
    LoggerBackendSPtr consoleLoggerBackend = std::make_shared<ConsoleLoggerBackend>();
    registerBackend(consoleLoggerBackend);

    LoggerBackendSPtr fileLoggerBackend = std::make_shared<FileLoggerBackend>();
    registerBackend(fileLoggerBackend);
}

//==============================================================================

LoggerSPtr LogManager::createLogger(const std::string& loggerId) { return m_loggerFactory->createLogger(loggerId); }

//==============================================================================

std::list<LoggerSPtr> LogManager::getLoggers() const { return m_loggerFactory->getLoggers(); }

//==============================================================================

bool LogManager::registerBackend(LoggerBackendSPtr backend) { return m_backendManager->registerBackend(backend); }

//==============================================================================

LoggerBackendSPtr LogManager::getBackendById(const std::string& backendId)
{
    return m_backendManager->getBackendById(backendId);
}

//==============================================================================

LoggerSPtr LogManager::globalLogger()
{
    LogManager& logManager = getInstance();

    MutexGuard guard{logManager.m_globalLoggerMutex};

    if (logManager.m_globalLogger == nullptr)
    {
        logManager.m_globalLogger = logManager.createLogger("ibeo::common::logging::GlobalLogger");
    }

    return logManager.m_globalLogger;
}

//==============================================================================

bool LogManager::loadConfig(const std::string& filePath, const bool suppressErrors)
{
    // Read file completely.
    std::ifstream file;
    file.open(filePath);
    if (file.is_open() == false)
    {
        if (suppressErrors == false)
        {
            std::cerr << "Failed to load logging config file '" << filePath << "'! Fall back to default configuration."
                      << std::endl;
        }
        return false;
    }

    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string fileContent(static_cast<std::size_t>(fileSize), '\0');
    if (file.read(&fileContent[0], fileSize))
    {
        return parseConfig(fileContent, suppressErrors);
    }
    else
    {
        return false;
    }
}

//==============================================================================

bool LogManager::parseConfig(const std::string& xml, const bool suppressErrors)
{
    // Read XML configuration similar to log4j2:
    // <Configuration>
    //     <Backends>
    //         <Backend id="ibeo::common::logging::ConsoleLoggerBackend"
    //                  format="%d{HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n" />
    //         <Backend id="ibeo::common::logging::FileLoggerBackend"
    //                  format="%d{HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n">
    //             <Path>${HOME}/ibeo/logging/ibeo.log</Path>
    //         </Backend>
    //     </Backends>
    //     <Loggers>
    //         <Root level="debug">
    //             <BackendRef id="ibeo::common::logging::ConsoleLoggerBackend" />
    //             <BackendRef id="ibeo::common::logging::FileLoggerBackend" />
    //         </Root>
    //         <Logger id="ibeo::common::logging::TestLogger" level="critical">
    //             <BackendRef id="ibeo::common::logging::ConsoleLoggerBackend" />
    //         </Logger>
    //     </Loggers>
    // </Configuration>

    // Read document.
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError eResult = doc.Parse(xml.c_str(), xml.size());
    if (eResult != tinyxml2::XML_SUCCESS)
    {
        if (suppressErrors == false)
        {
            std::cerr << "Failed to parse logging configuration! Fall back to default configuration." << std::endl;
        }
        return false;
    }

    // Get configuration node.
    const tinyxml2::XMLElement* configurationNode = doc.FirstChildElement("Configuration");
    if (configurationNode == nullptr)
    {
        if (suppressErrors == false)
        {
            std::cerr
                << "Cannot find 'Configuration' node in logging configuration! Fall back to default configuration."
                << std::endl;
        }
        return false;
    }

    ConfigurationSPtr config{std::make_shared<Configuration>()};

    // Get backends.
    const tinyxml2::XMLElement* backendsNode = configurationNode->FirstChildElement("Backends");
    if (backendsNode != nullptr)
    {
        parseBackendsConfig(backendsNode, suppressErrors);
    }

    // Get loggers.
    const tinyxml2::XMLElement* loggersNode = configurationNode->FirstChildElement("Loggers");
    if (loggersNode != nullptr)
    {
        parseLoggersConfig(config, loggersNode, suppressErrors);
    }

    // Use new configuration.
    return configure(config);
}

//==============================================================================

bool LogManager::configure(const ConfigurationSPtr& config, const bool suppressErrors)
{
    return m_loggerFactory->configure(config);
}

//==============================================================================

void LogManager::parseBackendsConfig(const tinyxml2::XMLElement* const backendsNode, const bool suppressErrors)
{
    // Format:
    // <Backends>
    //     <Backend id="ibeo::common::logging::ConsoleLoggerBackend"
    //              format="%d{HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n" />
    //     <Backend id="ibeo::common::logging::FileLoggerBackend"
    //              format="%d{HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n">
    //         <Path>${HOME}/ibeo/logging/ibeo.log</Path>
    //     </Backend>
    // </Backends>

    for (const tinyxml2::XMLElement* backendNode = backendsNode->FirstChildElement("Backend"); backendNode != nullptr;
         backendNode                             = backendNode->NextSiblingElement("Backend"))
    {
        // Get backend ID.
        std::string backendId{backendNode->Attribute("id")};
        if (backendId.empty())
        {
            if (suppressErrors == false)
            {
                std::cerr << "Backend ID missing in logging configuration! Backend configuration will be ignored."
                          << std::endl;
            }
            // Ignore error and proceed with next backend.
            continue;
        }

        try
        {
            // Configure backend.
            LoggerBackendSPtr backend = m_backendManager->getBackendById(backendId);
            if (backend == nullptr)
            {
                if (suppressErrors == false)
                {
                    std::cerr << "Backend '" << backendId << "' not registered! Backend configuration will be ignored."
                              << std::endl;
                }
                // Ignore error and proceed with next backend.
                continue;
            }

            bool backendConfigured = backend->configure(backendNode, suppressErrors);
            if (backendConfigured == false)
            {
                if (suppressErrors == false)
                {
                    std::cerr << "Configuring backend '" << backendId
                              << "' failed! Backend might not be working as expected." << std::endl;
                }
                // Ignore error and proceed with next backend.
                continue;
            }
        }
        catch (const std::invalid_argument&)
        {
            // Print error and proceed with next backend.
            if (suppressErrors == false)
            {
                std::cerr << "Invalid backend ID '" << backendId
                          << "' in logging configuration! Backend configuration will be ignored." << std::endl;
            }
        }
    }
}

//==============================================================================

void LogManager::parseLoggersConfig(ConfigurationSPtr& config,
                                    const tinyxml2::XMLElement* const loggersNode,
                                    const bool suppressErrors)
{
    // Format:
    //     <Loggers>
    //         <Root level="debug">
    //             <BackendRef id="ibeo::common::logging::ConsoleLoggerBackend" />
    //             <BackendRef id="ibeo::common::logging::FileLoggerBackend" />
    //         </Root>
    //         <Logger id="ibeo::common::logging::TestLogger" level="critical">
    //             <BackendRef id="ibeo::common::logging::ConsoleLoggerBackend" />
    //         </Logger>
    //     </Loggers>

    // Parse root logger.
    const tinyxml2::XMLElement* rootLoggerNode = loggersNode->FirstChildElement("Root");
    if (rootLoggerNode != nullptr)
    {
        config->setDefaultLogLevel(rootLoggerNode->Attribute("level"));
        std::list<std::string> backendIds = parseBackendReferences("Root", rootLoggerNode, suppressErrors);
        config->setDefaultBackends(backendIds);
    }
    // else: use default configuration for root logger.

    // Parse specific loggers.
    for (const tinyxml2::XMLElement* loggerNode = loggersNode->FirstChildElement("Logger"); loggerNode != nullptr;
         loggerNode                             = loggerNode->NextSiblingElement("Logger"))
    {
        std::string loggerId{loggerNode->Attribute("id")};
        if (loggerId.empty())
        {
            if (suppressErrors == false)
            {
                std::cerr << "Logger ID missing in logging configuration! Logger configuration will be ignored."
                          << std::endl;
            }
            continue;
        }

        try
        {
            config->setLogLevelForLogger(loggerNode->Attribute("level"), loggerId);
            std::list<std::string> backendIds = parseBackendReferences(loggerId, loggerNode, suppressErrors);
            for (const std::string& backendId : backendIds)
            {
                config->addBackendForLogger(backendId, loggerId);
            }
        }
        catch (const std::invalid_argument&)
        {
            // Print error and continue with next logger.
            if (suppressErrors == false)
            {
                std::cerr << "Invalid logger ID '" << loggerId
                          << "' in logging configuration! Logger configuration will be ignored." << std::endl;
            }
        }
    }
}

//==============================================================================

std::list<std::string> LogManager::parseBackendReferences(const std::string& loggerId,
                                                          const tinyxml2::XMLElement* loggerNode,
                                                          const bool suppressErrors)
{
    // Format:
    // <Logger id="ibeo::common::logging::TestLogger" level="critical">
    //     <BackendRef id="ibeo::common::logging::ConsoleLoggerBackend" />
    //     <BackendRef id="ibeo::common::logging::FileLoggerBackend" />
    // </Logger>

    std::list<std::string> backendIds;

    for (const tinyxml2::XMLElement* backendRefNode = loggerNode->FirstChildElement("BackendRef");
         backendRefNode != nullptr;
         backendRefNode = backendRefNode->NextSiblingElement("BackendRef"))
    {
        const char* backendIdString = backendRefNode->Attribute("id");
        if (backendIdString == nullptr)
        {
            if (suppressErrors == false)
            {
                std::cerr << "Backend reference ID missing for logger ID '" << loggerId
                          << "' in logging configuration! Backend reference will be ignored." << std::endl;
            }
            continue;
        }

        try
        {
            std::string backendId{backendIdString};
            backendIds.push_back(backendId);
        }
        catch (const std::invalid_argument&)
        {
            // Print error and continue with next backend.
            if (suppressErrors == false)
            {
                std::cerr << "Invalid backend reference ID '" << backendIdString << "' for logger ID '" << loggerId
                          << "' in logging configuration! Backend reference will be ignored." << std::endl;
            }
        }
    }

    return backendIds;
}

//==============================================================================

void LogManager::setDefaultLogLevel(const LogLevel logLevel) { return m_loggerFactory->setDefaultLogLevel(logLevel); }

//==============================================================================

LogLevel LogManager::getDefaultLogLevel() const { return m_loggerFactory->getDefaultLogLevel(); }

//==============================================================================

ConfigurationSPtr LogManager::getConfiguration() const { return m_loggerFactory->getConfiguration(); }

//==============================================================================

void LogManager::flushBackends(const uint32_t maxFlushTimeMilliseconds) const
{
    return m_backendManager->flushBackends(maxFlushTimeMilliseconds);
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

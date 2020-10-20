//==============================================================================
//!\file
//!\brief Factory produces logger frontends.
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Mar 15, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/logging/LoggerFactory.hpp>
#include <ibeo/common/logging/backends/FileLoggerBackend.hpp>

#include <algorithm>
#include <iostream>
#include <exception>
#include <ibeo/common/logging/backends/ConsoleLoggerBackend.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

LoggerFactory::~LoggerFactory()
{
    MutexGuard guard{m_mutex};

    m_loggers.clear();
    m_backendManager.reset();
    m_backendIds.clear();
    m_config.reset();
}

//==============================================================================

LoggerSPtr LoggerFactory::createLogger(const std::string& loggerId)
{
    MutexGuard guard{m_mutex};

    // Remove all loggers from the map that have been destroyed.
    cleanupLoggers();

    LoggerSPtr returnLogger{nullptr};
    LoggersByClassIdMap::iterator duplicateIter = m_loggers.find(loggerId);

    if (duplicateIter == m_loggers.end())
    {
        // Not found -> create new logger.
        returnLogger = std::make_shared<Logger>(loggerId);
        m_loggers.insert(std::make_pair(loggerId, returnLogger));

        // Configure newly created logger.
        updateLoggerConfiguration(returnLogger);
    }
    else
    {
        // Found -> use it.
        returnLogger = duplicateIter->second.lock();
        if (returnLogger == nullptr)
        {
            // Cleanup did not work correctly.
            throw std::logic_error("Destroyed logger found (cleanup did not work)!");
        }
    }

    return returnLogger;
}

//==============================================================================

bool LoggerFactory::configure(const ConfigurationSPtr& config)
{
    MutexGuard guard{m_mutex};

    m_config = config;
    updateAllLoggerConfiguration();

    return true;
}

//==============================================================================

void LoggerFactory::setDefaultLogLevel(const LogLevel logLevel)
{
    m_config->setDefaultLogLevel(logLevel);
    updateAllLoggerConfiguration();
}

//==============================================================================

LogLevel LoggerFactory::getDefaultLogLevel() const { return m_config->getDefaultLogLevel(); }

//==============================================================================

std::list<LoggerSPtr> LoggerFactory::getLoggers() const
{
    MutexGuard guard{m_mutex};

    std::list<LoggerSPtr> currentLoggers;

    for (const std::pair<std::string, LoggerWPtr>& classIdLoggerPair : m_loggers)
    {
        LoggerSPtr logger = classIdLoggerPair.second.lock();
        if (logger != nullptr)
        {
            // Corresponding logger still in alive -> copy it.
            currentLoggers.push_back(logger);
        }
    }

    return currentLoggers;
}

//==============================================================================

ConfigurationSPtr LoggerFactory::getConfiguration() const { return m_config; }

//==============================================================================

void LoggerFactory::updateAllLoggerConfiguration()
{
    // Update config in all current loggers.
    for (const std::pair<std::string, LoggerWPtr>& classIdLoggerPair : m_loggers)
    {
        LoggerSPtr logger = classIdLoggerPair.second.lock();
        if (logger != nullptr)
        {
            // Corresponding logger still in alive -> configure it.
            updateLoggerConfiguration(logger);
        }
    }
}

//==============================================================================

void LoggerFactory::updateLoggerConfiguration(const LoggerSPtr& logger)
{
    LogLevel logLevel = m_config->getLogLevelForLogger(logger->getId());
    logger->setLogLevel(logLevel);

    auto backendIds = m_config->getBackendsForLogger(logger->getId());
    logger->removeAllBackends();
    for (const auto& backendId : backendIds)
    {
        LoggerBackendSPtr backend = m_backendManager->getBackendById(backendId);
        if (backend != nullptr)
        {
            logger->addLoggerBackend(backend);
        }
    }
}

//==============================================================================

void LoggerFactory::cleanupLoggers()
{
    LoggersByClassIdMap::iterator iter = m_loggers.begin();
    while (iter != m_loggers.end())
    {
        LoggerSPtr logger = iter->second.lock();
        if (logger == nullptr)
        {
            // Corresponding shared pointer destroyed -> remove weak pointer from map.
            iter = m_loggers.erase(iter);
        }
        else
        {
            // Logger still in alive -> leave it and go to next logger.
            ++iter;
        }
    }
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

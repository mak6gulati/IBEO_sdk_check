//==============================================================================
//!\file
//!\brief Frontend used for logging.
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

#include <ibeo/common/logging/Logger.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

Logger::Logger(const std::string& loggerId) : m_loggerId{loggerId} {}

//==============================================================================

Logger::~Logger()
{
    MutexGuard guard{m_mutex};

    m_loggerId = "";
    m_logLevel = LogLevel::Off;
    m_loggerBackends.clear();
}

//==============================================================================

void Logger::addLoggerBackend(LoggerBackendSPtr loggerBackend)
{
    MutexGuard guard{m_mutex};

    std::list<LoggerBackendSPtr>::const_iterator iter = findBackend(loggerBackend->getId());
    if (iter == m_loggerBackends.end())
    {
        // Backend not yet in list -> add it now.
        m_loggerBackends.push_back(loggerBackend);
    }
}

//==============================================================================

void Logger::removeLoggerBackend(const std::string& loggerBackendId)
{
    MutexGuard guard{m_mutex};

    using ListIter = std::list<LoggerBackendSPtr>::iterator;
    auto iter      = findBackend(loggerBackendId);
    if (iter != m_loggerBackends.end())
    {
        // bugfix for older gcc versions (Ubuntu 14.04.)
        // Using [distance] and [advance] to convert [const_iterator]s to [iterator]s.
        // Source: Three Guidelines for Effective Iterator Usage - Scott Meyers
        auto listIter(m_loggerBackends.begin());
        std::advance(listIter, std::distance<std::list<LoggerBackendSPtr>::const_iterator>(listIter, iter));

        m_loggerBackends.erase(listIter);
    }
}

//==============================================================================

void Logger::removeAllBackends()
{
    MutexGuard guard{m_mutex};

    m_loggerBackends.clear();
}

//==============================================================================

std::list<std::string> Logger::getBackendIds() const
{
    MutexGuard guard{m_mutex};

    std::list<std::string> backendIds;

    for (const LoggerBackendSPtr& backend : m_loggerBackends)
    {
        backendIds.push_back(backend->getId());
    }

    return backendIds;
}

//==============================================================================

LogLevel Logger::getLogLevel() const
{
    MutexGuard guard{m_mutex};

    return m_logLevel;
}

//==============================================================================

void Logger::setLogLevel(const LogLevel level)
{
    MutexGuard guard{m_mutex};

    m_logLevel = level;
}

//==============================================================================

void Logger::log(const LogLevel level, const MessageSPtr msg)
{
    MutexGuard guard{m_mutex};

    if (isLogLevelActive(level) == false)
    {
        return;
    }

    for (LoggerBackendSPtr& backend : m_loggerBackends)
    {
        backend->log(m_loggerId, level, msg);
    }
}

//==============================================================================

bool Logger::isLogLevelActive(const LogLevel& level) const
{
    MutexGuard guard{m_mutex};

    return level <= m_logLevel;
}

//==============================================================================

std::list<LoggerBackendSPtr>::const_iterator Logger::findBackend(const std::string& backendId) const
{
    std::list<LoggerBackendSPtr>::const_iterator iter
        = std::find_if(m_loggerBackends.begin(), m_loggerBackends.end(), [backendId](const LoggerBackendSPtr& backend) {
              return backend->getId() == backendId;
          });

    return iter;
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

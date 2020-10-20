//==============================================================================
//!\file
//!\brief Configuration for backends and loggers.
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

#include <ibeo/common/logging/Configuration.hpp>

#include <algorithm>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

void Configuration::setLogLevelForLogger(const char* const logLevel, const std::string& loggerId)
{
    m_loggerIds2LogLevel.insert(std::make_pair(loggerId, parseLogLevel(logLevel)));
}

//==============================================================================

void Configuration::addBackendForLogger(const std::string& backendId, const std::string& loggerId)
{
    auto iter = m_loggerIds2BackendIds.find(loggerId);
    if (iter == m_loggerIds2BackendIds.end())
    {
        // No backend set for this logger yet -> create new list.
        iter = m_loggerIds2BackendIds.insert(std::make_pair(loggerId, std::list<std::string>())).first;
    }

    auto& backendIds   = iter->second;
    auto backendIdIter = std::find(backendIds.begin(), backendIds.end(), backendId);
    if (backendIdIter == backendIds.end())
    {
        // Backend not yet in list -> add it now.
        backendIds.push_back(backendId);
    }
}

//==============================================================================

LogLevel Configuration::getLogLevelForLogger(const std::string& loggerId)
{
    // Search for logger ID (including wildcard match).
    LogLevelMap::const_iterator iter = findLogger(m_loggerIds2LogLevel, loggerId);
    if (iter != m_loggerIds2LogLevel.end())
    {
        // Logger ID found -> use specific log level.
        return iter->second;
    }
    else
    {
        // Logger ID not found -> use default log level.
        return m_logLevel;
    }
}

//==============================================================================

Configuration::ClassIdList Configuration::getBackendsForLogger(const std::string& loggerId)
{
    // Search for logger ID (including wildcard match).
    BackendIdsMap::const_iterator iter = findLogger(m_loggerIds2BackendIds, loggerId);
    if (iter != m_loggerIds2BackendIds.end())
    {
        // Logger ID found -> use specific backend IDs.
        return iter->second;
    }
    else
    {
        // Logger ID not found -> use default backend IDs.
        return m_backendIds;
    }
}

//==============================================================================

void Configuration::setDefaultBackends(const ClassIdList& backendIds)
{
    ClassIdList newBackendIds;

    // Check for duplicates.
    for (const std::string& backendId : backendIds)
    {
        ClassIdList::const_iterator iter = std::find(newBackendIds.begin(), newBackendIds.end(), backendId);
        if (iter == newBackendIds.end())
        {
            newBackendIds.push_back(backendId);
        }
        // else: duplicate backend ID found -> ignore it.
    }

    m_backendIds.swap(newBackendIds);
}

//==============================================================================

bool Configuration::isWildcard(const std::string& loggerId)
{
    // A logger ID is a wildcard if it ends with the wildcard character.
    return ((loggerId.empty() == false) && (loggerId[loggerId.size() - 1] == wildcardChar));
}

//==============================================================================

bool Configuration::matchesWildcard(const std::string& thisLoggerId, const std::string& otherLoggerId)
{
    if ((isWildcard(thisLoggerId) == false) && (isWildcard(otherLoggerId) == false))
    {
        // No wildcards -> compare complete ID.
        return thisLoggerId == otherLoggerId;
    }
    else
    {
        std::size_t thisWildcardPosition  = thisLoggerId.find(wildcardChar);
        std::size_t otherWildcardPosition = otherLoggerId.find(wildcardChar);

        if ((thisWildcardPosition == 0) || (otherWildcardPosition == 0))
        {
            // Either this or the other logger ID (or both) consist of the wildcard char only
            // -> they match every other ID.
            return true;
        }

        std::size_t compareLength;
        if ((thisWildcardPosition != std::string::npos) && (otherWildcardPosition != std::string::npos))
        {
            // Both logger IDs are wildcard -> compare up to the shorter length.
            compareLength = std::min(thisWildcardPosition, otherWildcardPosition) - 1;
        }

        else if (thisWildcardPosition != std::string::npos)
        {
            // This logger ID is a wildcard.
            compareLength = thisWildcardPosition - 1;
        }

        else // if (otherWildcardPosition != std::string::npos)
        {
            // The other logger ID is a wildcard.
            compareLength = otherWildcardPosition - 1;
        }

        int compareResult = thisLoggerId.compare(0, compareLength, otherLoggerId, 0, compareLength);
        return compareResult == 0;
    }
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

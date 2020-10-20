//==============================================================================
//!\file
//!\brief Base class for backend factories.
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

#include <ibeo/common/logging/backends/LoggerBackendManager.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

LoggerBackendManager::~LoggerBackendManager()
{
    flushBackends();

    MutexGuard guard{m_mutex};
    m_backends.clear();
}

//==============================================================================

bool LoggerBackendManager::registerBackend(LoggerBackendSPtr backend)
{
    MutexGuard guard{m_mutex};

    bool registered{false};

    auto duplicateIter = m_backends.find(backend->getId());
    if (duplicateIter == m_backends.end())
    {
        m_backends.insert(std::make_pair(backend->getId(), backend));
        registered = true;
    }

    return registered;
}

//==============================================================================

LoggerBackendSPtr LoggerBackendManager::getBackendById(const std::string& backendId)
{
    MutexGuard guard{m_mutex};

    auto iter = m_backends.find(backendId);
    if (iter != m_backends.end())
    {
        return iter->second;
    }

    return nullptr;
}

//==============================================================================

void LoggerBackendManager::flushBackends(const uint32_t maxFlushTimeMilliseconds) const
{
    MutexGuard guard{m_mutex};

    for (const BackendMap::value_type& pair : m_backends)
    {
        pair.second->flush(maxFlushTimeMilliseconds);
    }
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

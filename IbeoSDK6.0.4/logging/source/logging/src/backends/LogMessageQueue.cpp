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
//! \date Nov 06, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/logging/backends/LogMessageQueue.hpp>
#include <iostream>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

constexpr uint32_t LogMessageQueue::infiniteMilliseconds;

//==============================================================================

bool LogMessageQueue::push(std::unique_lock<std::mutex>& lock,
                           const std::string& loggerId,
                           const LogLevel& level,
                           const MessageSPtr msg)
{
    // Wait for space in queue.
    bool result = m_popEvent.wait_for(lock, m_pushWaitTime, [&]() { return m_buffer.size() < m_capacity; });
    if (result == false)
    {
        // Timeout.
        return false;
    }

    // Add element.
    m_buffer.push(Entry(loggerId, level, msg));

    // Notify one of the threads waiting for elements in queue.
    m_pushEvent.notify_one();

    return true; // Success.
}

//==============================================================================

void LogMessageQueue::pop(std::unique_lock<std::mutex>& lock, std::string& loggerId, LogLevel& level, MessageSPtr& msg)
{
    // Wait for elements in queue.
    m_pushEvent.wait(lock, [&] { return m_buffer.empty() == false; });

    // Fetch element.
    Entry& entry = m_buffer.front();

    // Fill given variables.
    loggerId = entry.m_loggerId;
    level    = entry.m_level;
    msg      = entry.m_msg;

    // Remove element from queue.
    m_buffer.pop();

    // Notify one of the threads waiting for space in the queue.
    m_popEvent.notify_one();
}

//==============================================================================

void LogMessageQueue::clear()
{
    std::size_t count = m_buffer.size();
    if (count > 0)
    {
        std::cerr << "Warning: dropping " << count << " log message(s)!" << std::endl;
        std::queue<Entry>().swap(m_buffer);
    }
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

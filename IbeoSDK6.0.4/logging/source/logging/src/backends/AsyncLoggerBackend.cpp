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

#include <ibeo/common/logging/backends/AsyncLoggerBackend.hpp>

#include <condition_variable>
#include <queue>
#include <iostream>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

constexpr std::size_t AsyncLoggerBackend::logMessageDefaultQueueSize;

//==============================================================================

AsyncLoggerBackend::AsyncLoggerBackend(const std::string& backendId) : LoggerBackend(backendId) {}

//==============================================================================

AsyncLoggerBackend::~AsyncLoggerBackend() { reset(); }

//==============================================================================

std::size_t AsyncLoggerBackend::getLogMessageQueueSize() const
{
    MutexGuard queueGuard{m_mutex};
    if (m_queue != nullptr)
    {
        return m_queue->getCapacity();
    }
    else
    {
        // No queue -> use configured value.
        return m_messageQueueSize;
    }
}

//==============================================================================

uint32_t AsyncLoggerBackend::getLogMessageQueueTimeoutMilliseconds() const
{
    MutexGuard queueGuard{m_mutex};

    if (m_queue != nullptr)
    {
        return m_queue->getWaitTimeMilliseconds();
    }
    else
    {
        // No queue -> use configured value.
        return m_messageQueueWaitTime;
    }
}

//==============================================================================

bool AsyncLoggerBackend::configure(const tinyxml2::XMLElement* const xmlNode, const bool suppressErrors)
{
    {
        MutexGuard queueGuard{m_mutex};

        // Set base configuration.
        bool result = LoggerBackend::configure(xmlNode, suppressErrors);
        if (result == false)
        {
            // Failed -> give up.
            return result;
        }

        m_bypassQueue          = false;
        m_messageQueueWaitTime = LogMessageQueue::infiniteMilliseconds;
        m_messageQueueSize     = logMessageDefaultQueueSize;

        const tinyxml2::XMLElement* modeNode = xmlNode->FirstChildElement("Mode");
        if (modeNode != nullptr)
        {
            std::string modeString = modeNode->GetText();
            if (modeString == "Block")
            {
                // Block if queue is full -> use maximum wait time.
                m_messageQueueWaitTime = LogMessageQueue::infiniteMilliseconds;
            }

            else if (modeString == "Timed")
            {
                // Wait some time if queue is full -> use wait time from config node.

                const tinyxml2::XMLElement* timeoutNode = xmlNode->FirstChildElement("Timeout");
                if (timeoutNode != nullptr)
                {
                    std::string timeoutString = timeoutNode->GetText();

                    try
                    {
                        m_messageQueueWaitTime = static_cast<uint32_t>(std::stoul(timeoutString));
                    }
                    catch (const std::logic_error&)
                    {
                        if (suppressErrors == false)
                        {
                            std::cerr << "Invalid timeout for logger backend ID '" << getId()
                                      << "' in logging configuration! Fall back to default value." << std::endl;
                        }
                    }
                }
                // else: no timeout given -> use default.
            }

            else if (modeString == "Drop")
            {
                // Drop messages if queue is full -> use no wait time.
                m_messageQueueWaitTime = 0;
            }

            else if (modeString == "Bypass")
            {
                // Bypass queue -> log synchronously.
                m_bypassQueue = true;
            }

            else if (suppressErrors == false)
            {
                std::cerr << "Invalid mode for logger backend ID '" << getId()
                          << "' in logging configuration! Fall back to default mode." << std::endl;
            }

            else
            {
                // Ignore error silently and used default mode.
            }
        }
        // else: no mode node given -> use default mode.

        // Get queue size.
        const tinyxml2::XMLElement* queueSizeNode = xmlNode->FirstChildElement("QueueSize");
        if (queueSizeNode != nullptr)
        {
            std::string queueSizeString = queueSizeNode->GetText();

            try
            {
                m_messageQueueSize = static_cast<uint32_t>(std::stoul(queueSizeString));
            }
            catch (const std::logic_error&)
            {
                if (suppressErrors == false)
                {
                    std::cerr << "Invalid queue size for logger backend ID '" << getId()
                              << "' in logging configuration! Fall back to default size." << std::endl;
                }
            }
        }
    }

    // Thread might be running when being configured -> stop thread and destroy queue now (they will be re-created on
    // receiption of first log message).
    reset();

    return true;
}

//==============================================================================

void AsyncLoggerBackend::log(const std::string& loggerId, const LogLevel& level, const MessageSPtr msg)
{
    if (msg == nullptr)
    {
        throw std::invalid_argument("Message must not be null!");
    }

    bool bypassQueue;
    {
        MutexGuard queueGuard{m_mutex};

        bypassQueue = m_bypassQueue;
    }

    if (bypassQueue)
    {
        // No queue configured -> log synchronously.
        logAsync(loggerId, level, msg);
    }
    else
    {
        MutexGuard threadGuard{m_threadMutex};
        MutexGuard queueGuard{m_mutex};

        if (m_thread == nullptr)
        {
            // Thread and queue not created yet -> do it now.
            m_queue = std::make_shared<LogMessageQueue>(m_messageQueueSize);
            m_queue->setWaitTimeMilliseconds(m_messageQueueWaitTime);

            m_thread = std::make_shared<Thread>([&] { threadMain(); });
        }

        // Push the log message to the queue.
        m_queue->push(queueGuard, loggerId, level, msg);
    }
}

//==============================================================================

bool AsyncLoggerBackend::flush(const uint32_t maxFlushTimeMilliseconds) const
{
    LoggerBackend::flush(maxFlushTimeMilliseconds);

    {
        MutexGuard threadGuard{m_threadMutex};

        if (m_thread == nullptr)
        {
            // Thread not running -> no queue -> nothing to flush.
            return true;
        }
    }

    auto endTime       = std::chrono::system_clock::now() + std::chrono::milliseconds(maxFlushTimeMilliseconds);
    auto checkInterval = std::chrono::milliseconds(maxFlushTimeMilliseconds) / 10;

    while (true)
    {
        {
            MutexGuard queueGuard{m_mutex};
            if (m_queue->isEmpty() && (m_handlingMessage == false))
            {
                // Queue empty.
                return true;
            }
        }

        if (std::chrono::system_clock::now() >= endTime)
        {
            // Max. waiting time reached or exceeded -> timeout.
            std::cerr << "Warning: flushing backend '" << getId() << "' does not complete in time." << std::endl;
            return false;
        }

        std::this_thread::sleep_for(checkInterval);
    }
}

//==============================================================================

void AsyncLoggerBackend::reset()
{
    MutexGuard threadGuard{m_threadMutex};

    if (m_thread != nullptr)
    {
        // Thread running -> stop it.
        {
            // Drop all unprocessed messages.
            MutexGuard queueGuard{m_mutex};
            m_queue->clear();

            // Add empty entry to the queue (logger ID and level do not matter).
            m_queue->push(queueGuard, "", LogLevel::Off, nullptr);
        }

        // Wait for end of thread.
        m_thread->join();
    }

    {
        MutexGuard queueGuard{m_mutex};

        m_thread.reset();
        m_queue.reset();
    }
}

//==============================================================================

void AsyncLoggerBackend::threadMain()
{
    std::string loggerId;
    LogLevel logLevel;
    MessageSPtr msg;

    while (true)
    {
        {
            MutexGuard queueGuard{m_mutex};

            m_queue->pop(queueGuard, loggerId, logLevel, msg);
            m_handlingMessage = true;
        }

        if (msg == nullptr)
        {
            // Empty entry retrieved -> stop thread now.
            break;
        }

        try
        {
            if (typeid(*this) != typeid(AsyncLoggerBackend))
            {
                logAsync(loggerId, logLevel, msg);
            }
            else
            {
                // If the thread is stopped in this class' destructor the derived class' destructor has already run and
                // this object has been demoted to this base class. Thus, the pure virtual method logAsync cannot be
                // called anymore.
                std::cerr << "Warning: dropping log message in backend '" << getId()
                          << "'! Use flush() to avoid this message." << std::endl;
            }
        }
        catch (const std::exception& exc)
        {
            std::cerr << "Error '" << exc.what() << "' when logging through backend '" << getId() << "'!" << std::endl;
        }
        catch (...)
        {
            std::cerr << "Unknown error when logging through backend '" << getId() << "'!" << std::endl;
            throw;
        }

        {
            MutexGuard queueGuard{m_mutex};
            m_handlingMessage = false;
        }
    }
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

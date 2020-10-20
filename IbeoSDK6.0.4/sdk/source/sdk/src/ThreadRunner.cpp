//==============================================================================
//!\file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Aug 1, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/ThreadRunner.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ibeo::common::logging::LoggerSPtr ThreadRunner::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

ThreadRunner::ThreadRunner(ThreadMainFunction threadMainFunction) : m_threadMainFunction(threadMainFunction) {}

//==============================================================================

ThreadRunner::~ThreadRunner()
{
    const bool stopping = stop();

    if (stopping)
    {
        // Wait for end of thread.
        join();
    }
}

//==============================================================================

ThreadRunner::ThreadState ThreadRunner::getThreadState(const bool useMutex) const
{
    if (useMutex)
    {
        try
        {
            Lock lock(m_mutex);
            return m_threadState;
        }
        catch (const boost::lock_error& e)
        {
            LOGERROR(logger, e.what());
            return ThreadState::AccessError;
        }
    }
    else
    {
        return m_threadState;
    }
}

//==============================================================================

std::string ThreadRunner::getThreadName() const
{
    std::string threadName;

#ifdef BOOST_THREAD_PLATFORM_PTHREAD
    //========================================
    // Using pthreads.
    //========================================
    if (m_thread != nullptr)
    {
        pthread_t threadId = static_cast<pthread_t>(m_thread->native_handle());

        threadName.resize(maxThreadNameLength);
        pthread_getname_np(threadId, &threadName[0], threadName.size());
    }
#endif

    return threadName;
}

//==============================================================================

bool ThreadRunner::setThreadState(const ThreadState threadState)
{
    try
    {
        Lock lock(m_mutex);
        m_threadState = threadState;
        m_threadStateCondition.notify_all();

        LOGTRACE(logger, threadState);
        return true;
    }
    catch (const boost::lock_error& e)
    {
        LOGERROR(logger, e.what());
        return false;
    }
}

//==============================================================================

void ThreadRunner::setThreadName(const std::string& name)
{
#if defined(BOOST_THREAD_PLATFORM_PTHREAD)
    //========================================
    // OSes using pthread.
    //----------------------------------------
    if (name.size() >= maxThreadNameLength)
    {
        LOGWARNING(logger,
                   "Thread name too long, will be truncated to first " << (maxThreadNameLength - 1) << " chars!");
    }

    if (m_thread != nullptr)
    {
        pthread_t threadId = static_cast<pthread_t>(m_thread->native_handle());
        pthread_setname_np(threadId, name.substr(0, maxThreadNameLength - 1).c_str());
    }
#endif
}

//==============================================================================

bool ThreadRunner::start()
{
    if (m_thread == nullptr)
    {
        // Start thread.
        try
        {
            Lock lock(m_mutex);
            m_thread.reset(new boost::thread(m_threadMainFunction));

            while ((m_threadState == ThreadState::NotRunning) || (m_threadState == ThreadState::Starting))
            {
                m_threadStateCondition.wait(lock);
            }

            return true;
        }
        catch (const boost::lock_error& e)
        {
            LOGERROR(logger, "Starting thread failed (reason " << e.what() << ")!");
            return false;
        }
    }
    else
    {
        // Thread already started -> nothing to do.
        return true;
    }
}

//==============================================================================

bool ThreadRunner::stop(const bool shouldInterruptThread)
{
    if (m_thread == nullptr)
    {
        // Thread not started.
        return true;
    }

    // Stop thread.
    try
    {
        Lock lock(m_mutex);
        if ((m_threadState == ThreadState::Running) || (m_threadState == ThreadState::Starting))
        {
            setThreadState(ThreadState::Stopping);

            if (shouldInterruptThread)
            {
                // Interrupt thread (in case it is sleeping).
                m_thread->interrupt();
            }

            // Wait for state change.
            m_threadStateCondition.wait(lock);
        }
        return true;
    }
    catch (const boost::lock_error& e)
    {
        LOGERROR(logger, "Stopping thread failed (reason " << e.what() << ")!");
        return false;
    }
}

//==============================================================================

void ThreadRunner::join()
{
    if (m_thread != nullptr)
    {
        if (m_thread->joinable())
        {
            m_thread->join();
        }
        m_thread = nullptr;
    }
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

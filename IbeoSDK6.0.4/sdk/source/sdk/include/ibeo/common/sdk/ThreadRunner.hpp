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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/ThreadEnsemble.hpp>
#include <ibeo/common/logging/logging.hpp>

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================
//! \brief Class for running a thread while maintaining the thread state.
//------------------------------------------------------------------------------
class ThreadRunner
{
public:
    using ThreadMainFunction = std::function<void()>;
    using ThreadPtr          = std::shared_ptr<boost::thread>;
    using Condition          = boost::condition;
    using Lock               = boost::recursive_mutex::scoped_lock;
    using Mutex              = boost::recursive_mutex;

    //==============================================================================
    //! \brief State of the thread.
    //------------------------------------------------------------------------------
    enum class ThreadState : uint8_t
    {
        AccessError = 0, //!< Used if accessing the thread state failed.
        NotRunning  = 1, //!< The thread is idle (either not started or stopped).
        Starting    = 2, //!< The thread was idle and is starting.
        Running     = 3, //!< The thread is running.
        Stopping    = 4, //!< The thread has run and is currently stopping.
        StartFailed = 5, //!< Starting the thread failed.
        RunFailed   = 6 //!< An unrecoverable error occurred while the thread was running.
    };

public:
    //========================================
    //! \brief Constructor.
    //!
    //! \param[in] threadMainFunction  Function to be called after the thread has started.
    //----------------------------------------
    ThreadRunner(ThreadMainFunction threadMainFunction);

    //========================================
    //! \brief Destructor.
    //!
    //! The destructor will stop the thread and wait until it is idle.
    //----------------------------------------
    virtual ~ThreadRunner();

public: // getter
    //========================================
    //! \brief Get the state of the thread.
    //!
    //! \param[in] useMutex  Whether to use the internal mutex for getting the thread state.
    //! \return The current thread state.
    //----------------------------------------
    ThreadState getThreadState(const bool useMutex = true) const;

    //========================================
    //! \brief Get the name of the thread.
    //!
    //! \return The current thread name.
    //----------------------------------------
    std::string getThreadName() const;

public: // setter
    //========================================
    //! \brief Set the current state of the thread.
    //!
    //! \return \c true if the state could be set, \c false otherwise.
    //----------------------------------------
    bool setThreadState(const ThreadState threadState);

    //========================================
    //! \brief Set the name of the thread.
    //!
    //! \param[in] name  The name to be set.
    //!
    //! \note Setting a thread name is useful for debugging, but might not be supported on every operating system.
    //----------------------------------------
    void setThreadName(const std::string& name);

public:
    //========================================
    //! \brief Start the thread.
    //!
    //! \return \c true if the thread could be started successfully and is running, \c false otherwise.
    //----------------------------------------
    bool start();

    //========================================
    //! \brief Sends a signal to stop the thread, but does not wait for the thread to be idle.
    //!
    //! \param[in] shouldInterruptThread  If \c true, the method tries to interrupt the underlying thread.
    //!
    //! \return \c true if the signal could be set successfully, \c false otherwise.
    //----------------------------------------
    bool stop(const bool shouldInterruptThread = false);

    //========================================
    //! \brief Wait until the thread is idle.
    //----------------------------------------
    void join();

private:
#ifdef BOOST_THREAD_PLATFORM_PTHREAD
    //========================================
    // Using pthreads.
    //========================================
    // Max. thread name length is 16 chars (including terminating null byte).
    static constexpr int maxThreadNameLength{16};
#endif

private:
    static constexpr const char* loggerId = "ibeo::common::sdk::ThreadRunner";
    static ibeo::common::logging::LoggerSPtr logger;

private:
    ThreadMainFunction m_threadMainFunction;
    mutable Mutex m_mutex;
    Condition m_threadStateCondition;
    ThreadPtr m_thread{nullptr};
    ThreadState m_threadState{ThreadState::NotRunning};
}; // ThreadRunner

//==============================================================================

inline std::ostream& operator<<(std::ostream& os, const ThreadRunner::ThreadState& state)
{
    switch (state)
    {
    case ThreadRunner::ThreadState::AccessError:
        os << "AccessError";
        break;
    case ThreadRunner::ThreadState::NotRunning:
        os << "NotRunning";
        break;
    case ThreadRunner::ThreadState::Starting:
        os << "Starting";
        break;
    case ThreadRunner::ThreadState::Running:
        os << "Running";
        break;
    case ThreadRunner::ThreadState::Stopping:
        os << "Stopping";
        break;
    case ThreadRunner::ThreadState::StartFailed:
        os << "StartFailed";
        break;
    case ThreadRunner::ThreadState::RunFailed:
        os << "RunFailed";
        break;
    default:
        os << "<unknown> (" << static_cast<uint8_t>(state) << ")";
        break;
    } // switch
    return os;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

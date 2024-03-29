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
//!\date July 20, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <ibeo/common/sdk/devices/IbeoDeviceBase.hpp>
#include <ibeo/common/sdk/datablocks/SpecialExporterBase.hpp>

#include <ibeo/common/logging/logging.hpp>

#include <boost/asio.hpp>
#include <boost/optional.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class IbeoDataHeader;
class DataBlock;

//==============================================================================

class ThreadEnsemble
{
protected:
    enum class ThreadState : uint8_t
    {
        NotRunning  = 0,
        Starting    = 1,
        Running     = 2,
        Stopping    = 3,
        StartFailed = 4,
        RunFailed   = 5
    }; // ThreadState

    using Lock  = boost::recursive_mutex::scoped_lock;
    using Mutex = boost::recursive_mutex;

public:
    virtual ~ThreadEnsemble(){};

public:
    virtual void run()                   = 0;
    virtual void stop()                  = 0;
    virtual bool isRunning() const       = 0;
    virtual bool isNotYetRunning() const = 0;
    virtual bool isConnected() const     = 0;

    //========================================
    //! \brief Get the expiry time for IO operations.
    //! \return The expiry time for IO operations.
    //----------------------------------------
    virtual boost::optional<boost::asio::deadline_timer::duration_type> getExpiryTime() const = 0;

    //========================================
    //! \brief Set the expiry time for IO operations.
    //! \param[in] expiryTime  The expiry time for IO operations.
    //----------------------------------------
    virtual void setExpiryTime(const boost::asio::deadline_timer::duration_type expiryTime) = 0;

    //========================================
    //! \brief Reset the expiry time for IO operations.
    //! \param[in] expiryTime  The expiry time for IO operations.
    //----------------------------------------
    virtual void resetExpiryTime() = 0;

    //========================================
    //! \brief Send a command which expects no reply.
    //! \param[in] cmd  Command to be sent.
    //! \return The result of the operation.
    //! \sa ErrorCode
    //----------------------------------------
    virtual statuscodes::Codes sendCommand(const CommandCBase& cmd, const SpecialExporterBase<CommandCBase>& exporter)
        = 0;

    //========================================
    //! \brief Send a command and wait for a reply.
    //!
    //! The command will be sent. The calling thread
    //! will sleep until a reply has been received
    //! but not longer than the number of milliseconds
    //! given in \a timeOut.
    //!
    //! \param[in]       cmd    Command to be sent.
    //! \param[in, out]  reply  The reply container for
    //!                         the reply to be stored into.
    //! \param[in]       timeOut  Number of milliseconds to
    //!                           wait for a reply.
    //! \return The result of the operation.
    //! \sa ErrorCode
    //----------------------------------------
    virtual statuscodes::Codes sendCommand(const CommandCBase& cmd,
                                           const SpecialExporterBase<CommandCBase>& exporter,
                                           CommandReplyBase& reply,
                                           const boost::posix_time::time_duration timeOut
                                           = boost::posix_time::milliseconds(500))
        = 0;

protected:
    static constexpr const char* loggerId = "ibeo::common::sdk::ThreadEnsemble";
    static ibeo::common::logging::LoggerSPtr logger;
}; // ThreadEnsemble

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

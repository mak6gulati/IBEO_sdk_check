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
//! \date May 5, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/IbeoDeviceBase.hpp>
#include <ibeo/common/sdk/devices/ThreadEnsemble.hpp>
#include <ibeo/common/sdk/ThreadRunner.hpp>

#include <boost/asio.hpp>
#include <boost/optional.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class TcpReceiveThreadEnsemble : public ThreadEnsemble
{
public:
    using TcpSocketPtr        = std::shared_ptr<boost::asio::ip::tcp::socket>;
    using CommandReplyBasePtr = CommandReplyBase*;

    using DataBlockPtr     = const ibeo::common::sdk::DataBlock*;
    using ReceiveDataBlock = boost::function<void(const ibeo::common::sdk::IbeoDataHeader* dh, const char* bodyBuf)>;

    using Condition    = boost::condition;
    using TimeDuration = boost::posix_time::time_duration;

public:
    enum class ReconnectMode : uint8_t
    {
        InitialConnect = 0,
        //!< Immediately connect to the remote device after calling \c getConnected(). If failed or if the connection
        //!< gets lost afterwards, it will not be re-established (legacy behaviour).
        WaitForRemoteDevice = 1,
        //!< Upon calling \c getConnected(), wait until the remote device is available, stop if the connection gets
        //!< lost afterwards.
        AutoReconnect = 2
        //!< Like \c WaitForRemoteDevice, but try to reconnect every time the remote device is disconnected.
    };

public:
    static const int bufferSize = 4 * 1024 * 1024;

public:
    TcpReceiveThreadEnsemble(const boost::asio::ip::address& ip,
                             const unsigned short port,
                             ReceiveDataBlock receiveDataBlock);
    virtual ~TcpReceiveThreadEnsemble();

public:
    ReconnectMode getReconnectMode() const;
    void setReconnectMode(ReconnectMode reconnectMode);

    const TimeDuration& getReconnectTime() const;
    void setReconnectTime(const TimeDuration& reconnectTime);

    void run() override;
    void stop() override;
    bool isRunning() const override;
    bool isNotYetRunning() const override;
    bool isConnected() const override;

    //========================================
    //! \brief Get the expiry time for IO operations.
    //! \return The expiry time for IO operations.
    //----------------------------------------
    boost::optional<boost::asio::deadline_timer::duration_type> getExpiryTime() const override;

    //========================================
    //! \brief Set the expiry time for IO operations.
    //! \param[in] expiryTime  The expiry time for IO operations.
    //----------------------------------------
    void setExpiryTime(const boost::asio::deadline_timer::duration_type expiryTime) override;

    //========================================
    //! \brief Reset the expiry time for IO operations.
    //! \param[in] expiryTime  The expiry time for IO operations.
    //----------------------------------------
    void resetExpiryTime() override;

    //========================================
    //! \brief Send a command which expects no reply.
    //! \param[in] cmd  Command to be sent.
    //! \return The result of the operation.
    //! \sa ErrorCode
    //----------------------------------------
    statuscodes::Codes sendCommand(const CommandCBase& cmd, const SpecialExporterBase<CommandCBase>& exporter) override;

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
    statuscodes::Codes sendCommand(const CommandCBase& cmd,
                                   const SpecialExporterBase<CommandCBase>& exporter,
                                   CommandReplyBase& reply,
                                   const boost::posix_time::time_duration timeOut
                                   = boost::posix_time::milliseconds(500)) override;

protected:
    void recvThreadMain();
    bool powerUpConnection();
    bool connect();
    bool waitForReconnectTimeout() const;
    void disconnect();

    statuscodes::Codes sendCommandInternal(const CommandCBase& cmd, const SpecialExporterBase<CommandCBase>& exporter);
    void onReceiveCommandReply(const IbeoDataHeader& dh, const char* bodyBuf);

protected:
    boost::asio::io_service m_ioService;

    boost::asio::ip::tcp::endpoint m_endPoint;

    TcpSocketPtr m_socket;

    ReconnectMode m_reconnectMode{ReconnectMode::InitialConnect};
    TimeDuration m_reconnectTime;

    //========================================
    //! \brief The expiry time for IO operations.
    //----------------------------------------
    boost::optional<boost::asio::deadline_timer::duration_type> m_expiryTime;

    ReceiveDataBlock m_receiveDataBlock;

    mutable Mutex m_mutex;
    ThreadRunner m_threadRunner;

    boost::recursive_timed_mutex m_rMutex;
    CommandReplyBasePtr m_replyPtr;
    CommandId m_expectedReplyId;
    EventMonitor m_eventMonitor;
    EventMonitor::Mask m_eventReplyReceived;
    uint32_t m_sizeOfPrevCommand;
}; // TcpReceiveThread

//==============================================================================

inline std::ostream& operator<<(std::ostream& os, const TcpReceiveThreadEnsemble::ReconnectMode& mode)
{
    switch (mode)
    {
    case TcpReceiveThreadEnsemble::ReconnectMode::InitialConnect:
        os << "InitialConnect";
        break;
    case TcpReceiveThreadEnsemble::ReconnectMode::WaitForRemoteDevice:
        os << "WaitForRemoteDevice";
        break;
    case TcpReceiveThreadEnsemble::ReconnectMode::AutoReconnect:
        os << "AutoReconnect";
        break;
    default:
        os << "<unknown> (" << static_cast<uint8_t>(mode) << ")";
        break;
    } // switch
    return os;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

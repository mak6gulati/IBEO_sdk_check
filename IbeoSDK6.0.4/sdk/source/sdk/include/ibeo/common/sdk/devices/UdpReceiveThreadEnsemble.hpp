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

#include <ibeo/common/sdk/devices/sutp/IbeoSutpInterface.hpp>
#include <ibeo/common/sdk/devices/IbeoDeviceBase.hpp>
#include <ibeo/common/sdk/devices/ThreadEnsemble.hpp>

#include <boost/asio.hpp>
#include <boost/optional.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class UdpReceiveThreadEnsemble : public ThreadEnsemble
{
public:
    using UdpSocketPtr = std::shared_ptr<boost::asio::ip::udp::socket>;

    using DataBlockPtr     = const ibeo::common::sdk::DataBlock*;
    using ReceiveDataBlock = boost::function<void(const ibeo::common::sdk::IbeoDataHeader* dh, const char* bodyBuf)>;

    using Condition = boost::condition;

public:
    static const uint32_t bufferSize = 4 * 1024 * 1024;

public:
    UdpReceiveThreadEnsemble(const boost::asio::ip::address& ip,
                             const unsigned short port,
                             ReceiveDataBlock receiveDataBlock,
                             const boost::asio::ip::address_v4 ifa,
                             bool enableMulticast = false);
    virtual ~UdpReceiveThreadEnsemble();

public:
    void run() override;
    void stop() override;
    bool isRunning() const override;
    bool isNotYetRunning() const override;
    bool isConnected() const override
    {
        // UDP is always connected.
        return true;
    }

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
    //! \param[in]       cmd      Command to be sent.
    //! \param[in, out]  reply    The reply container for
    //!                           the reply to be stored into.
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
    void handleReceive(const boost::system::error_code& error, std::size_t len);
    bool handleSutpMsgs(const char* bodyBuf, size_t len);
    void disconnect();

    bool receiveWithTimeout(boost::asio::ip::udp::socket& socket,
                            boost::asio::ip::udp::endpoint& ep,
                            const boost::asio::deadline_timer::duration_type& expiryTime,
                            boost::system::error_code& readError);

    //========================================
    //! \brief Handler used by readWithTimeout.
    //! \param[in] error  Error code of the deadline
    //!                   timer wait operation.
    //----------------------------------------
    void waitHandler(const boost::system::error_code& error);

protected:
    void sutpHandlingThreadMain();

protected:
    boost::asio::io_service m_ioService;

    boost::asio::ip::udp::endpoint m_endPoint;

    boost::asio::ip::address m_ipAdr;

    UdpSocketPtr m_socket;

    bool m_enableMulticast;

    //========================================
    //! \brief Optional error code used by readWithTimeout for the timer result.
    //----------------------------------------
    boost::optional<boost::system::error_code> m_timerResult;

    //========================================
    //! \brief Optional error code used by readWithTimeout for the read result.
    //----------------------------------------
    boost::optional<boost::system::error_code> m_readResult;

    //! Auxiliary timer to use timeout feature
    boost::asio::deadline_timer m_auxTimer;

    /// Input buffer where received data is stored.
    char m_inCArrBuffer[bufferSize];

    //========================================
    //! \brief Flag to tell, whether a read operation shall
    //!        issue an error if there was a timeout.
    //!
    //! \c true if the user set a timeout duration.
    //! \c false if there is no external timeout duration set,
    //! then the deadline timer is used to get back from the
    //! io_service::run_one method so this thread is not blocked
    //! any longer and can be killed from outside.
    //----------------------------------------
    bool m_stopOnTimeOut;

    //========================================
    //! \brief The expiry time for IO operations.
    //----------------------------------------
    boost::optional<boost::asio::deadline_timer::duration_type> m_expiryTime;

    IbeoSutpInterface m_sutpInterface;
    ReceiveDataBlock m_receiveDataBlock;

    mutable Mutex m_udpRecvMutex;
    Condition m_udpRecvThreadStateCondition;

    boost::thread* m_udpRecvThread;

    Mutex m_sutpMutex;

    boost::thread* m_sutpThread;

    //========================================
    //! \brief State of the recieve thread.
    //! \sa m_thread
    //----------------------------------------
    ThreadState m_udpRecvThreadState;
    ThreadState m_sutpThreadState;

}; // UdpReceiveThreadEnsemble

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

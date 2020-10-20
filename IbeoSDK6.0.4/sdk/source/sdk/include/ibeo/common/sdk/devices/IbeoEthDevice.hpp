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

#include <ibeo/common/sdk/devices/IbeoEthDevice.hpp>

#include <ibeo/common/sdk/devices/ThreadEnsemble.hpp>
#include <boost/asio.hpp>
#include <boost/optional.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//!\class IbeoEthDevice
//!\brief Base class for all Ibeo devices connected via TCP/IP or UDP.
//!\date July 20, 2017
//------------------------------------------------------------------------------
class IbeoEthDevice : public IbeoDeviceBase
{
public:
    using UdpSocketPtr = std::shared_ptr<boost::asio::ip::udp::socket>;

public:
    //========================================
    //!\brief Create an IbeoEthDevice (general device class).
    //!
    //! This constructor will create an IbeoEthDevice class object
    //! for devices communicating by network.
    //-------------------------------------
    IbeoEthDevice() = default;
    virtual ~IbeoEthDevice();
    //========================================

private:
    IbeoEthDevice(const IbeoEthDevice&); // forbidden
    IbeoEthDevice& operator=(const IbeoEthDevice&); // forbidden

public:
    void receivedDataBlock(const IbeoDataHeader* dh, const char* bodyBuf);

    //========================================
    //!\brief Establish the connection to the
    //!       hardware.
    //!
    //! Starting the receiving thread.
    //!\param [in] timeoutSec  Device timeout in seconds
    //-------------------------------------
    void connect(const uint32_t timeoutSec = defaultReceiveTimeoutSeconds) override;

    //========================================
    //!\brief Disconnect the TCP/IP connection
    //!       to the hardware device.
    //-------------------------------------
    void disconnect() override;

    //========================================
    //!\brief Checks whether the TCP/IP connection to the hardware device is established and can receive data.
    //!
    //!\return \c true, if messages from the hardware can be received, \c false otherwise.
    //-------------------------------------
    bool isConnected() const override;

    //========================================
    //!\brief Checks whether the thread for handling TCP/IP connections to the hardware is running.
    //!
    //!\return \c true, if the thread is running, \c false otherwise.
    //!
    //!\note This should not be mixed up with \a isConnected(). A device is running if the corresponding thread is
    //!      running, no matter if the connection to the hardware is established or not.
    //-------------------------------------
    bool isRunning() const override;

    uint32_t getRecvTimeoutSeconds() const { return m_recvTimeoutSeconds; }

    //========================================
    //!\brief Send a command which expects no reply.
    //!\param[in] cmd  Command to be sent.
    //!\return The result of the operation.
    //!\sa ErrorCode
    //-------------------------------------
    statuscodes::Codes sendCommand(const CommandCBase& cmd, const SpecialExporterBase<CommandCBase>& exporter) final;

    //========================================
    //!\brief Send a command and wait for a reply.
    //!
    //! The command will be sent. The calling thread
    //! will sleep until a reply has been received
    //! but not longer than the number of milliseconds
    //! given in \a timeOut.
    //!
    //!\param[in]       cmd    Command to be sent.
    //!\param[in, out]  reply  The reply container for
    //!                         the reply to be stored into.
    //!\param[in]       timeOut  Number of milliseconds to
    //!                           wait for a reply.
    //!\return The result of the operation.
    //!\sa ErrorCode
    //-------------------------------------
    statuscodes::Codes sendCommand(const CommandCBase& cmd,
                                   const SpecialExporterBase<CommandCBase>& exporter,
                                   CommandReplyBase& reply,
                                   const boost::posix_time::time_duration timeOut
                                   = boost::posix_time::milliseconds(500)) final;

    //========================================
    //!\brief Set the timeout period of the receive
    //!       operation.
    //!\note: if a connection to a hardware device is already established, the
    //!       new timeout takes effect immediately.
    //!       If no device is connected, changes take effect after connecting
    //!       to a device using the method getConnected().
    //! \param[in] seconds  Number of seconds.
    //----------------------------------------
    void setRecvTimeoutSeconds(const uint32_t seconds);

protected:
    static constexpr uint32_t defaultReceiveTimeoutSeconds{10};

    Mutex m_mutex;
    ThreadState m_threadState{ThreadState::NotRunning};
    ThreadEnsemble* m_receiveThread{nullptr};
    uint32_t m_recvTimeoutSeconds{defaultReceiveTimeoutSeconds}; //hardware timeout in sec

}; // IbeoEthDevice

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

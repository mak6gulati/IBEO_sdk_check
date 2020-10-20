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
//!\date Jul 2, 2018
//!
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/IbeoDevice.hpp>
#include <ibeo/common/sdk/devices/TcpReceiveThreadEnsemble.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================
//!\brief IbeoDevice for use with TCP
//!\date Jul 2, 2018
//!
//------------------------------------------------------------------------------
template<class DeviceImpl>
class IbeoTcpDevice : public IbeoDevice<DeviceImpl>
{
public:
    using ReconnectMode = TcpReceiveThreadEnsemble::ReconnectMode;
    using TimeDuration  = boost::posix_time::time_duration;

public:
    //========================================
    //!\brief Create an IbeoTcpDevice.
    //!
    //! This constructor will create an IbeoDevice class object
    //! given by the template class DeviceImpl.
    //!
    //! \param[in] ip      IP address of the device
    //!                    to be connected with.
    //! \param[in] port    Port number for the device.
    //----------------------------------------
    IbeoTcpDevice(const std::string& ip, const unsigned short port)
      : IbeoDevice<DeviceImpl>(), m_strIP(ip), m_port(port)
    {}

    virtual ~IbeoTcpDevice() = default;

    ReconnectMode getReconnectMode() const { return m_reconnectMode; }
    void setReconnectMode(ReconnectMode reconnectMode) { m_reconnectMode = reconnectMode; }

    const TimeDuration& getReconnectTime() const { return m_reconnectTime; }
    void setReconnectTime(const TimeDuration& reconnectTime) { m_reconnectTime = reconnectTime; }

public:
    virtual void connect(const uint32_t timeoutSec = IbeoEthDevice::defaultReceiveTimeoutSeconds) override
    {
        boost::system::error_code ec;
        boost::asio::ip::address ipAdr = boost::asio::ip::address::from_string(m_strIP, ec);

        if (ec)
        {
            LOGERROR(this->m_logger, "Invalid ip address (" << m_strIP << ") " << ec.message());
            IbeoDeviceBase::Lock lock(this->m_mutex);
            this->m_threadState = IbeoDeviceBase::ThreadState::StartFailed;
            return;
        }

        if (this->m_receiveThread)
        {
            LOGWARNING(this->m_logger, "Receive thread already running.");
            return;
        }

        TcpReceiveThreadEnsemble::ReceiveDataBlock rdb = boost::bind(&IbeoEthDevice::receivedDataBlock, this, _1, _2);
        TcpReceiveThreadEnsemble* receiveThread        = new TcpReceiveThreadEnsemble(ipAdr, m_port, rdb);
        receiveThread->setReconnectMode(m_reconnectMode);
        receiveThread->setReconnectTime(m_reconnectTime);
        this->m_receiveThread = receiveThread;

        IbeoDevice<DeviceImpl>::connect(timeoutSec);
    }

protected:
    std::string m_strIP;
    unsigned short m_port{0};
    ReconnectMode m_reconnectMode{ReconnectMode::WaitForRemoteDevice};
    TimeDuration m_reconnectTime{boost::posix_time::millisec(100)};
}; // IbeoDevice

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

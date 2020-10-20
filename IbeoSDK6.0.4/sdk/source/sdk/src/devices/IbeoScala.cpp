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
//!\date Oct 04, 2013
//!
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/devices/IbeoScala.hpp>
#include <ibeo/common/sdk/devices/TcpReceiveThreadEnsemble.hpp>
#include <ibeo/common/sdk/devices/UdpReceiveThreadEnsemble.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

IbeoScala::IbeoScala(const std::string& ip, const unsigned short port, const IbeoTypeEthTcp&)
  : IbeoDevice(), m_strIP(ip), m_port(port), m_ethType(EthType::EthTcp)
{}

//==============================================================================

IbeoScala::IbeoScala(const std::string& ip,
                     const unsigned short port,
                     const IbeoTypeEthUdp&,
                     const boost::asio::ip::address_v4 ifa)
  : IbeoDevice(), m_strIP(ip), m_port(port), m_ifa(ifa), m_ethType(EthType::EthUdp)
{}

//==============================================================================

IbeoScala::IbeoScala(const std::string& ip,
                     const unsigned short port,
                     const IbeoTypeEthUdpMulticast&,
                     const boost::asio::ip::address_v4 ifa)
  : IbeoDevice(), m_strIP(ip), m_port(port), m_ifa(ifa), m_ethType(EthType::EthUdpMulticast)
{}

//==============================================================================

IbeoScala::~IbeoScala() { this->disconnect(); }

//==============================================================================

void IbeoScala::connect(const uint32_t timeoutSec)
{
    boost::system::error_code ec;
    boost::asio::ip::address ipAdr = boost::asio::ip::address::from_string(m_strIP, ec);

    if (ec)
    {
        LOGERROR(m_logger, "Invalid ip address (" << m_strIP << ") " << ec.message());
        Lock lock(this->m_mutex);
        m_threadState = ThreadState::StartFailed;
        return;
    }

    if (m_receiveThread)
    {
        LOGWARNING(m_logger, "Receive thread already running.");
        return;
    }

    if (m_ethType == EthType::EthUdp)
    {
        UdpReceiveThreadEnsemble::ReceiveDataBlock rdb = boost::bind(&IbeoEthDevice::receivedDataBlock, this, _1, _2);
        m_receiveThread                                = new UdpReceiveThreadEnsemble(ipAdr, m_port, rdb, m_ifa);
    }
    else if (m_ethType == EthType::EthUdpMulticast)
    {
        UdpReceiveThreadEnsemble::ReceiveDataBlock rdb = boost::bind(&IbeoEthDevice::receivedDataBlock, this, _1, _2);
        m_receiveThread                                = new UdpReceiveThreadEnsemble(ipAdr, m_port, rdb, m_ifa, true);
    }
    else
    {
        TcpReceiveThreadEnsemble::ReceiveDataBlock rdb = boost::bind(&IbeoEthDevice::receivedDataBlock, this, _1, _2);
        m_receiveThread                                = new TcpReceiveThreadEnsemble(ipAdr, m_port, rdb);
    }

    IbeoDevice::connect(timeoutSec);
}

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IbeoScala>& getImporterCreatorMap<IbeoScala>()
{
    return ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

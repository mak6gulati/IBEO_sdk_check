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
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/IbeoDevice.hpp>
#include <ibeo/common/sdk/devices/IbeoEthType.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
//!\class IbeoScala
//! \brief Class to connect to a Scala sensor.
//! \date Oct 1, 2013
///-----------------------------------------------------------------------------
class IbeoScala : public IbeoDevice<IbeoScala>
{
public:
    //========================================
    //!\brief Create an IbeoScala (connection class).
    //!
    //! This constructor will create an IbeoLUX class object
    //! which will try to connect to a Scala sensor,
    //! using the given IP address and port number using TCP protocol.
    //!
    //! \param[in] ip      IP address of the scanner
    //!                    to be connected with.
    //! \param[in] port    Port number for the connection
    //!                    with the scanner.
    //! \param[in] ethTcp  Protocol type for the connection
    //!                    with the scanner.
    //----------------------------------------
    IbeoScala(const std::string& ip,
              const unsigned short port    = 12004,
              const IbeoTypeEthTcp& ethTcp = IbeoTypeEthTcp());

    //========================================
    //!\brief Create an IbeoScala (connection class).
    //!
    //! This constructor will create an IbeoLUX class object
    //! which will try to connect to a Scala sensor,
    //! using the given IP address, port number and ethernet protocol.
    //!
    //! \param[in] ip      IP address of the scanner
    //!                    to be connected with.
    //! \param[in] port    Port number for the connection
    //!                    with the scanner.
    //! \param[in] ethTcp  Protocol type for the connection
    //!                    with the scanner.
    //! \param[in] ifa     Address of network interface for the connection
    //!                    with the scanner.
    //----------------------------------------
    IbeoScala(const std::string& ip,
              const unsigned short port,
              const IbeoTypeEthUdp& ethUdp,
              const boost::asio::ip::address_v4 ifa = boost::asio::ip::address_v4::any());

    //========================================
    //!\brief Create an IbeoScala (connection class).
    //!
    //! This constructor will create an IbeoLUX class object
    //! which will try to connect to a Scala sensor,
    //! using the given IP address, port number and ethernet protocol.
    //!
    //! \param[in] ip      IP address of the scanner
    //!                    to be connected with.
    //! \param[in] port    Port number for the connection
    //!                    with the scanner.
    //! \param[in] ethTcp  Protocol type for the connection
    //!                    with the scanner.
    //! \param[in] ifa     Address of network interface for the connection
    //!                    with the scanner.
    //----------------------------------------
    IbeoScala(const std::string& ip,
              const unsigned short port,
              const IbeoTypeEthUdpMulticast& ethMulticast,
              const boost::asio::ip::address_v4 ifa = boost::asio::ip::address_v4::any());

    //========================================
    //!\brief Destructor.
    //!
    //! Will disconnect before destruction.
    //----------------------------------------
    virtual ~IbeoScala();

public:
    void connect(const uint32_t timeoutSec = IbeoEthDevice::defaultReceiveTimeoutSeconds) override;

private:
    enum class EthType : uint8_t
    {
        EthTcp,
        EthUdp,
        EthUdpMulticast
    };

private: // not supported
    using IbeoDevice<IbeoScala>::sendCommand;

private:
    std::string m_strIP;
    unsigned short m_port{0};
    boost::asio::ip::address_v4 m_ifa;
    EthType m_ethType;
}; // IbeoScala

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IbeoScala>& getImporterCreatorMap<IbeoScala>();

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

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
//! \date Jun 02, 2016
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/devices/IbeoTcpIpAcceptorScala.hpp>

#include <boost/iostreams/stream.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

IbeoTcpIpAcceptorScala::SessionScala::SessionScala(IbeoTcpIpAcceptorBase* const parent,
                                                   boost::asio::io_service& io_service,
                                                   const uint8_t deviceId)
  : IbeoTcpIpAcceptorBase::SessionBase(parent, io_service, deviceId)
{}

//==============================================================================

void IbeoTcpIpAcceptorScala::SessionScala::startListen() {}

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

IbeoTcpIpAcceptorScala::IbeoTcpIpAcceptorScala(const unsigned short port) : IbeoTcpIpAcceptorBase(port) {}

//==============================================================================

IbeoTcpIpAcceptorScala::IbeoTcpIpAcceptorScala(boost::asio::deadline_timer::duration_type writeExpirationTime,
                                               const unsigned short port)
  : IbeoTcpIpAcceptorBase(writeExpirationTime, port)
{}

//==============================================================================

IbeoTcpIpAcceptorBase::SessionBase::Ptr IbeoTcpIpAcceptorScala::getNewSessionPtr(boost::asio::io_service& io_service)
{
    m_sessionPtr.reset(new SessionScala(this, io_service));
    return m_sessionPtr;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

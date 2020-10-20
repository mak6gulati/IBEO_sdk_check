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
//! \date Jun 02 2016
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/IbeoTcpIpAcceptorBase.hpp>

#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//! \class IbeoTcpIpAcceptorScala
//! \brief Class for accepting connections via TCP/IP and sending data
//!        via this connection, behaving like a Scala.
//! \date Jun 02, 2016
//------------------------------------------------------------------------------
class IbeoTcpIpAcceptorScala : public IbeoTcpIpAcceptorBase
{
public:
    //========================================
    //! \brief Convenience using std::shared_ptr<IbeoTcpIpAcceptorScala> = for std::shared_ptr. 	//---------------------------------------- 	using Ptr =;

private:
    //========================================
    //! \brief Handles connections and act like a Scala sensor.
    //! \date Jun 02, 2016
    //----------------------------------------
    class SessionScala : public IbeoTcpIpAcceptorBase::SessionBase
    {
    public:
        //========================================
        //! \brief Convenience using std::shared_ptr<SessionScala> = for std::shared_ptr. 		//---------------------------------------- 		using Ptr =;

    public:
        //========================================
        //! \brief Creates a SessionScala
        //!
        //! \param[in] io_service      Service which
        //!                            established connection.
        //! \param[in] deviceId        Id of our simulated device
        //!                            needed for ibeo data header.
        //----------------------------------------
        SessionScala(IbeoTcpIpAcceptorBase* const parent,
                     boost::asio::io_service& io_service,
                     const uint8_t deviceId = 1);

        //========================================
        //! \brief Destructs a SessionScala.
        //----------------------------------------
        virtual ~SessionScala() {}

    protected:
        //========================================
        //! \brief Worker function for m_ListenThreadPtr.
        //!
        //! Doing nothing. A Scala sensor does not
        //! listen to ethernet commands.
        //----------------------------------------
        virtual void startListen();
    }; //IbeoTcpIpAcceptorScala::SessionScala

protected:
    static const int msgBufferSize = 4 * 65536;

public:
    //========================================
    //! \brief Creates an IbeoTcpIpAcceptorScala.
    //!
    //! \param[in] port            Port number for the
    //!                            connection.
    //----------------------------------------
    IbeoTcpIpAcceptorScala(const unsigned short port = 12004);

    //========================================
    //! \brief Creates an IbeoTcpIpAcceptorScala.
    //!
    //! \param[in  writeExpirationTime  Timeout limit for async
    //!                                 write operations.
    //! \param[in] port                 Port number for the
    //!                                 connection.
    //----------------------------------------
    IbeoTcpIpAcceptorScala(const boost::asio::deadline_timer::duration_type writeExpirationTime,
                           const unsigned short port = 12004);

    //========================================
    //! \brief Destructs an IbeoTcpIpAcceptorScala.
    //----------------------------------------
    virtual ~IbeoTcpIpAcceptorScala() {}

protected:
    //========================================
    //! \brief Gets current session ptr.
    //! \return Session ptr casted to sessionBase.
    //----------------------------------------
    virtual IbeoTcpIpAcceptorBase::SessionBase::Ptr getSessionPtr() { return m_sessionPtr; }

    //========================================
    //! \brief Gets new session ptr initialized
    //!        with io_service.
    //! \param[in] io_service  Service which handles
    //!                        connections.
    //! \return Session ptr casted to sessionBase.
    //----------------------------------------
    virtual IbeoTcpIpAcceptorBase::SessionBase::Ptr getNewSessionPtr(boost::asio::io_service& io_service);

private:
    //========================================
    //! \brief Session ptr for next session which
    //!        will be established.
    //----------------------------------------
    SessionScala::Ptr m_sessionPtr;
}; // IbeoTcpIpAcceptorScala

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

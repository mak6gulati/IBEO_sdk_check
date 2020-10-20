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
//! \date May 26, 2016
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/IbeoTcpIpAcceptorBase.hpp>

#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>
#include <ibeo/common/sdk/PassiveMsgBuffer.hpp>

#include <boost/optional.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/system/error_code.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//! \class IbeoTcpIpAcceptorEcu
//! \brief Class for accepting connections via TCP/IP and sending data
//!        via this connection, behaving like an ECU
//! \date May 17, 2016
//------------------------------------------------------------------------------
class IbeoTcpIpAcceptorEcu : public IbeoTcpIpAcceptorBase
{
public:
    //========================================
    //! \brief convinience using for std::shared_ptr
    //----------------------------------------
    using Ptr = std::shared_ptr<IbeoTcpIpAcceptorEcu>;

private:
    //======================================================================
    //! \class SessionEcu
    //! \brief Handles connections and also answers to set filter commands like
    //! ECU
    //! \date May 17, 2016
    //----------------------------------------
    class SessionEcu : public IbeoTcpIpAcceptorBase::SessionBase
    {
    public:
        //========================================
        //! \brief convinience using std::shared_ptr<SessionEcu> = for std::shared_ptr 		//---------------------------------------- 		using Ptr =;

    public:
        //========================================
        //! \brief Creates a SessionEcu
        //!
        //! \param[in] io_service      service which
        //!                            established connection
        //! \param[in] readExpirationTime  optional expiration time used as timeout
        //!                                for async read operations.
        //! \param[in] deviceId            device_id of our simulated device
        //!                                needed for IbeoDataHeader
        //----------------------------------------
        SessionEcu(IbeoTcpIpAcceptorBase* parent,
                   boost::asio::io_service& io_service,
                   const boost::optional<boost::asio::deadline_timer::duration_type> readExpirationTime,
                   const uint8_t deviceId = 1);

        //========================================
        //! \brief Destructs a SessionEcu
        //----------------------------------------
        virtual ~SessionEcu() {}

    protected:
        //========================================
        //! \brief worker function for m_ListenThreadPtr
        //! listens to send commands and answers
        //! setFilterCmd with a setFilter reply (required from
        //! AppBase)
        //----------------------------------------
        virtual void startListen();

        void startTimer();
        void startRead();

    public:
        void listen(const boost::system::error_code& error, const size_t nbOfBytesReceived);
        void readTimeout(const boost::system::error_code& error);

    private:
        //========================================
        //! \brief handles new received setFilterCmd
        //! \param[in] dh  dataheader of received command
        //! \param[in] bodyBuf  body of received command
        //----------------------------------------
        void onReceiveCommand(const IbeoDataHeader& dh, const char* bodyBuf);

    private:
        //========================================
        //! \brief Expiring duration for IO operations.
        //----------------------------------------
        const boost::optional<boost::asio::deadline_timer::duration_type> m_expiryTime;

        //========================================
        //! \brief Timer to be able to check, whether
        //!        to cancel a read operation if the
        //!        connection has been closed.
        //----------------------------------------
        boost::asio::deadline_timer m_timer;

        PassiveMsgBuffer m_msgBuffer;
    }; //IbeoTcpIpAcceptorECU::SessionEcu

public:
    using SessionEcuPtr = std::shared_ptr<SessionEcu>;

protected:
    static const int msgBufferSize = 4 * 1024 * 1024;

public:
    //========================================
    //! \brief Creates an IbeoTcpIpAcceptorEcu
    //!
    //! \param[in] port            Port number for the connection.
    //----------------------------------------
    IbeoTcpIpAcceptorEcu(const unsigned short port = 12002);

    //========================================
    //! \brief Creates an IbeoTcpIpAcceptorEcu
    //!
    //! \param[in] expirationTime  Timeout time for async io operations.
    //! \param[in] port            Port number for the connection.
    //----------------------------------------
    IbeoTcpIpAcceptorEcu(const boost::optional<boost::asio::deadline_timer::duration_type> expirationTime,
                         const unsigned short port = 12002);

    //========================================
    //! \brief Creates an IbeoTcpIpAcceptorEcu
    //!
    //! \param[in] readExpirationTime   Timeout time for async read operations.
    //! \param[in] writeExpirationTime  Timeout time for async write operations.
    //! \param[in] port                 Port number for the connection.
    //----------------------------------------
    IbeoTcpIpAcceptorEcu(const boost::optional<boost::asio::deadline_timer::duration_type> readExpirationTime,
                         const boost::asio::deadline_timer::duration_type writeExpirationTime,
                         const unsigned short port = 12002);

    //========================================
    //! \brief Destructs an IbeoTcpIpAcceptorEcu
    //----------------------------------------
    virtual ~IbeoTcpIpAcceptorEcu() {}

protected:
    //========================================
    //! \brief Gets current session ptr
    //! \return session ptr casted to sessionBase
    //----------------------------------------
    virtual IbeoTcpIpAcceptorBase::SessionBase::Ptr getSessionPtr() { return m_sessionPtr; }

    //========================================
    //! \brief Gets new session ptr initialized with io_service
    //! \param[in] io_service  service which handles connections
    //! \return session ptr cases to sessionBase
    //----------------------------------------
    virtual IbeoTcpIpAcceptorBase::SessionBase::Ptr getNewSessionPtr(boost::asio::io_service& io_service);

    //========================================
    //! \brief Get the expiry time for IO operations.
    //! \return The expiry time for IO operations.
    //----------------------------------------
    boost::optional<boost::asio::deadline_timer::duration_type> getExpiryTime() const { return m_readExpirationTime; }

    //========================================
    //! \brief Set the expiry time for IO operations.
    //! \param[in] expiryTime  The expiry time for IO operations.
    //----------------------------------------
    void setExpiryTime(const boost::asio::deadline_timer::duration_type expiryTime)
    {
        m_readExpirationTime.reset(expiryTime);
    }

    //========================================
    //! \brief Reset the expiry time for IO operations.
    //! \param[in] expiryTime  The expiry time for IO operations.
    //----------------------------------------
    void resetExpiryTime() { m_readExpirationTime.reset(); }

    //========================================
    //! \brief Handler for receive operation.
    //! \param[in] session            Session that issued
    //!                               the async read call.
    //! \param[in] error              Result of the async
    //!                               read call.
    //! \param[in] nbOfBytesReceived  Number of bytes that
    //!                               have been received in
    //!                               the async read call.
    //----------------------------------------
    static void listen(SessionEcu* session, const boost::system::error_code& error, const size_t nbOfBytesReceived)
    {
        session->listen(error, nbOfBytesReceived);
    }

    //========================================
    //! \brief Handler for timeout situations.
    //! \param[in] session            Session that started
    //!                               the deadline timer.
    //! \param[in] error              Result of waiting for
    //!                               the deadline timer of
    //!                               the \a session.
    //----------------------------------------
    static void timeout(SessionEcu* session, const boost::system::error_code& error) { session->readTimeout(error); }

private:
    //========================================
    //! \brief  session ptr for next session which will be established
    //----------------------------------------
    SessionEcu::Ptr m_sessionPtr;

    //========================================
    //! \brief Expiring duration for IO operations.
    //----------------------------------------
    boost::optional<boost::asio::deadline_timer::duration_type> m_readExpirationTime;
}; // IbeoTcpIpAcceptorEcu

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

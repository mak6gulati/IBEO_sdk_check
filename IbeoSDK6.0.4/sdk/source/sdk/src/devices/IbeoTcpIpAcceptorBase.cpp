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
//! \date May 17, 2016
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <ibeo/common/sdk/devices/IbeoTcpIpAcceptorBase.hpp>

#include <ibeo/common/sdk/datablocks/DataBlock.hpp>
#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>
#include <ibeo/common/sdk/MsgBuffer.hpp>

#include <boost/asio/error.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/system/error_code.hpp>

#include <fstream>
#include <iostream>

#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif // gcc or clang

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

IbeoTcpIpAcceptorBase::SessionBase::SessionBase(IbeoTcpIpAcceptorBase* const parent,
                                                boost::asio::io_service& io_service,
                                                const uint8_t deviceId)
  : m_parent(parent),
    m_socket(io_service),
    m_deviceId(deviceId),
    m_sizePrevMsg(0),
    m_connectionALive(false),
    m_ranges{std::make_pair(DataTypeId::DataType_Unknown, DataTypeId::DataType_LastId)},
    m_sendBuffer()
{}

//==============================================================================

IbeoTcpIpAcceptorBase::SessionBase::SessionBase(IbeoTcpIpAcceptorBase* const parent,
                                                boost::asio::io_service& io_service,
                                                const CommandEcuSetFilterC::RangeVector ranges,
                                                const uint8_t deviceId)
  : m_parent(parent),
    m_socket(io_service),
    m_deviceId(deviceId),
    m_sizePrevMsg(0),
    m_connectionALive(false),
    m_ranges(ranges),
    m_sendBuffer()
{}

//==============================================================================

IbeoTcpIpAcceptorBase::SessionBase::~SessionBase() { m_socket.close(); }

//==============================================================================

statuscodes::Codes IbeoTcpIpAcceptorBase::SessionBase::sendDatablock(const DataBlock& dataBlock)
{
    // lock -> not only sending thread can write but listen thread can also write replies utilizing that function!
    boost::mutex::scoped_lock lock(m_sendMutex);

    // id must lie within filter start and end range
    bool hasPassed{false};
    for (const auto& r : m_ranges)
    {
        if ((r.first <= dataBlock.getDataType()) && (dataBlock.getDataType() <= r.second))
        {
            hasPassed = true;
            break;
        }
    }
    if (!hasPassed)
    {
        LOGDEBUG(logger, "Block DataBlock " << toHex(dataBlock.getDataType()));
        return statuscodes::DataBlockBlockedByFilter;
    }

    const uint32_t sizeOfThisMsg = uint32_t(dataBlock.getSerializedSize());
    const uint32_t sizeOfBuffer  = sizeOfThisMsg + IbeoDataHeader::getHeaderSize();

    m_sendBuffer.resize(sizeOfBuffer);
    boost::iostreams::stream<boost::iostreams::array> strm(&(m_sendBuffer[0]), sizeOfBuffer);
    std::ostream& s = (std::ostream&)strm;

    LOGDEBUG(logger,
             "Sending DataBlock " << toHex(dataBlock.getDataType()) << " with " << sizeOfThisMsg + 24 << " bytes");

    const IbeoDataHeader header(
        dataBlock.getDataType(), m_sizePrevMsg, sizeOfThisMsg, m_deviceId, dataBlock.getHeaderNtpTime());
    header.serialize(s);
    dataBlock.serialize(s);

    if (!s.good())
    {
        LOGERROR(logger, "Sending failed " << statuscodes::FailedToPrepareSendingDataBlock);
        return statuscodes::FailedToPrepareSendingDataBlock;
    }

    if (!m_socket.is_open())
    {
        LOGERROR(logger, "Socket is not connected");
        return statuscodes::NotConnected;
    }

    try
    {
        if (m_socket.is_open())
        {
            boost::asio::async_write(m_socket,
                                     boost::asio::buffer(&(m_sendBuffer[0]), sizeOfBuffer),
                                     boost::bind(&IbeoTcpIpAcceptorBase::writeDone, m_parent, this, _1, _2));
        }
    }
    catch (const boost::system::system_error& ex)
    {
        LOGERROR(logger, "Sending failed: " << ex.what());
        m_connectionALive = false;
        return statuscodes::SendingDataBlockFailed;
    }

    return statuscodes::EverythingOk;
}

//==============================================================================

statuscodes::Codes IbeoTcpIpAcceptorBase::SessionBase::sendStreamData(const IbeoDataHeader& dh,
                                                                      const char* const dataPayloadBuffer)
{
    // lock -> not only sending thread can write but listen thread can also write replies utilizing that function!
    boost::mutex::scoped_lock lock(m_sendMutex);

    // id must lie within filter start and end range
    bool hasPassed{false};
    for (const auto& r : m_ranges)
    {
        if ((r.first <= dh.getDataType()) && (dh.getDataType() <= r.second))
        {
            hasPassed = true;
            break;
        }
    }
    if (!hasPassed)
    {
        LOGDEBUG(logger, "Block DataBlock " << toHex(dh.getDataType()));
        return statuscodes::DataBlockBlockedByFilter;
    }

    const uint32_t sizeOfThisMsg = dh.getMessageSize();
    const uint32_t sizeOfBuffer  = sizeOfThisMsg + IbeoDataHeader::getHeaderSize();

    m_sendBuffer.resize(sizeOfBuffer);
    boost::iostreams::stream<boost::iostreams::array> strm(&(m_sendBuffer[0]), sizeOfBuffer);
    std::ostream& s = (std::ostream&)strm;

    LOGDEBUG(logger, "Sending DataBlock " << toHex(dh.getDataType()) << " with " << sizeOfThisMsg + 24 << " bytes");

    const IbeoDataHeader header(dh.getDataType(), m_sizePrevMsg, sizeOfThisMsg, dh.getDeviceId(), dh.getTimestamp());
    header.serialize(s);
    s.write(dataPayloadBuffer, sizeOfThisMsg);
    //dataBlock.serialize(s);

    if (!s.good())
    {
        LOGERROR(logger, "Sending failed " << statuscodes::FailedToPrepareSendingDataBlock);
        return statuscodes::FailedToPrepareSendingDataBlock;
    }

    if (!m_socket.is_open())
    {
        LOGERROR(logger, "Socket is not connected");
        return statuscodes::NotConnected;
    }

    try
    {
        if (m_socket.is_open())
        {
            boost::asio::async_write(m_socket,
                                     boost::asio::buffer(&(m_sendBuffer[0]), sizeOfBuffer),
                                     boost::bind(&IbeoTcpIpAcceptorBase::writeDone, m_parent, this, _1, _2));
        }
    }
    catch (const boost::system::system_error& ex)
    {
        LOGERROR(logger, "Sending failed: " << ex.what());
        m_connectionALive = false;
        return statuscodes::SendingDataBlockFailed;
    }

    return statuscodes::EverythingOk;
}

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

ibeo::common::logging::LoggerSPtr IbeoTcpIpAcceptorBase::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

IbeoTcpIpAcceptorBase::IbeoTcpIpAcceptorBase(const short unsigned int port)
  : m_sessionPtr(),
    m_ioService(),
    m_sessionsMutex(),
    m_sessions(),
    m_activeSending(),
    m_sendingStatus(),
    m_writeCondMutex(),
    writeCondition(),
    m_writeExpirationPeriod(boost::posix_time::seconds(10)),
    m_writeExprirationTimer(m_ioService),
    m_writeState(WS_Idle),
    m_acceptor(m_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    m_acceptIOServiceThreadPtr()
{}

//==============================================================================

IbeoTcpIpAcceptorBase::IbeoTcpIpAcceptorBase(const boost::asio::deadline_timer::duration_type writeExpirationTime,
                                             const short unsigned int port)
  : m_sessionPtr(),
    m_ioService(),
    m_sessionsMutex(),
    m_sessions(),
    m_activeSending(),
    m_sendingStatus(),
    m_writeCondMutex(),
    writeCondition(),
    m_writeExpirationPeriod(writeExpirationTime),
    m_writeExprirationTimer(m_ioService),
    m_writeState(WS_Idle),
    m_acceptor(m_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    m_acceptIOServiceThreadPtr()
{}

//==============================================================================

IbeoTcpIpAcceptorBase::IbeoTcpIpAcceptorBase(
    const boost::optional<boost::asio::deadline_timer::duration_type> writeExpirationTime,
    const short unsigned int port)
  : m_sessionPtr(),
    m_ioService(),
    m_sessionsMutex(),
    m_sessions(),
    m_activeSending(),
    m_sendingStatus(),
    m_writeCondMutex(),
    writeCondition(),
    m_writeExpirationPeriod(writeExpirationTime ? writeExpirationTime.get() : boost::posix_time::seconds(10)),
    m_writeExprirationTimer(m_ioService),
    m_writeState(WS_Idle),
    m_acceptor(m_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    m_acceptIOServiceThreadPtr()
{}

//==============================================================================

void IbeoTcpIpAcceptorBase::init()
{
    m_sessionPtr = getNewSessionPtr(m_ioService);
    m_acceptor.async_accept(m_sessionPtr->getSocket(),
                            boost::bind(&IbeoTcpIpAcceptorBase::handleAccept, this, boost::asio::placeholders::error));

    // starting thread which handles io service
    m_acceptIOServiceThreadPtr.reset(
        new boost::thread(boost::bind(&IbeoTcpIpAcceptorBase::acceptorIOServiceThread, this)));
}

//==============================================================================

IbeoTcpIpAcceptorBase::~IbeoTcpIpAcceptorBase() { closeAcceptor(); }

//==============================================================================

void IbeoTcpIpAcceptorBase::issueWriteOperations(const DataBlock& dataBlock)
{
    boost::mutex::scoped_lock lock(m_sessionsMutex);

    m_sendingStatus = statuscodes::EverythingOk;
    if (m_sessions.empty())
    {
        LOGDEBUG(logger, "No session accepted. Skipping DataBlock " << toHex(dataBlock.getDataType()));
        m_writeState = WS_Completed;
        return;
    }

    const uint32_t nbOfBytesToSend = uint32_t(dataBlock.getSerializedSize() + IbeoDataHeader::getHeaderSize());

    std::vector<SessionBase::Ptr>::iterator sessionIt = m_sessions.begin();
    while (sessionIt != m_sessions.end())
    {
        // check if connection is still valid otherwise delete it from our sessions

        if (!((*sessionIt)->isConnectionValid()))
        {
            sessionIt = m_sessions.erase(sessionIt);
            if (m_sessions.empty())
            {
                LOGDEBUG(logger, "No session accepted. Skipping DataBlock " << toHex(dataBlock.getDataType()));
                m_writeState = WS_Completed;
                return;
            }
            continue;
        }

        if ((*sessionIt)->isConnectionValid())
        {
            // just to be sure (timing)
            boost::mutex::scoped_lock sendLock(m_writeCondMutex);

            const statuscodes::Codes codeCurrent = (*sessionIt)->sendDatablock(dataBlock);
            if (codeCurrent == statuscodes::EverythingOk)
            {
                m_writeState = WS_InProgress;

                m_activeSending.insert(std::make_pair(&**sessionIt, nbOfBytesToSend));

                LOGDEBUG(logger,
                         "Adding " << (void*)(&**sessionIt) << " to set. Datatype " << toHex(dataBlock.getDataType())
                                   << " Size: " << dataBlock.getSerializedSize() + 24
                                   << " Size of set: " << m_activeSending.size());
            }

            if (codeCurrent != statuscodes::EverythingOk)
            {
                m_sendingStatus = codeCurrent;
            }
        }

        ++sessionIt;
    }

    return;
}

//==============================================================================

void IbeoTcpIpAcceptorBase::issueRawWriteOperations(const IbeoDataHeader& dh, const char* const dataPayloadBuffer)
{
    LOGDEBUG(logger, "========================================");
    boost::mutex::scoped_lock lock(m_sessionsMutex);

    m_sendingStatus = statuscodes::EverythingOk;
    if (m_sessions.empty())
    {
        LOGDEBUG(logger, "No session accepted. Skipping DataBlock " << toHex(dh.getDataType()));
        m_writeState = WS_Completed;
        return;
    }

    const uint32_t nbOfBytesToSend = uint32_t(dh.getMessageSize() + IbeoDataHeader::getHeaderSize());

    std::vector<SessionBase::Ptr>::iterator sessionIt = m_sessions.begin();
    while (sessionIt != m_sessions.end())
    {
        // check if connection is still valid otherwise delete it from our sessions

        if (!((*sessionIt)->isConnectionValid()))
        {
            sessionIt = m_sessions.erase(sessionIt);
            if (m_sessions.empty())
            {
                LOGDEBUG(logger, "No session accepted. Skipping DataBlock " << toHex(dh.getDataType()));
                m_writeState = WS_Completed;
                return;
            }
            continue;
        }

        if ((*sessionIt)->isConnectionValid())
        {
            // just to be sure (timing)
            boost::mutex::scoped_lock sendLock(m_writeCondMutex);

            const statuscodes::Codes codeCurrent = (*sessionIt)->sendStreamData(dh, dataPayloadBuffer);
            if (codeCurrent == statuscodes::EverythingOk)
            {
                m_writeState = WS_InProgress;

                m_activeSending.insert(std::make_pair(&**sessionIt, nbOfBytesToSend));

                LOGDEBUG(logger,
                         "Adding " << (void*)(&**sessionIt) << " to set. Datatype " << toHex(dh.getDataType())
                                   << " Size: " << dh.getMessageSize() + 24
                                   << " Size of set: " << m_activeSending.size());
            }

            if (codeCurrent != statuscodes::EverythingOk)
            {
                m_sendingStatus = codeCurrent;
            }
        }

        ++sessionIt;
    }

    return;
}

//==============================================================================

void IbeoTcpIpAcceptorBase::waitForWriteOperationsBeCompleted()
{
    // wait for all writes been completed
    boost::mutex::scoped_lock sendLock(m_writeCondMutex);
    if (!m_activeSending.empty())
    {
        writeCondition.wait(sendLock);
    }

    if (m_writeState != WS_TimeOut)
        m_writeExprirationTimer.cancel();
}

//==============================================================================

statuscodes::Codes IbeoTcpIpAcceptorBase::sendDataBlock(const DataBlock& dataBlock)
{
    issueWriteOperations(dataBlock);

    m_writeExprirationTimer.expires_from_now(m_writeExpirationPeriod);
    m_writeExprirationTimer.async_wait(boost::bind(&IbeoTcpIpAcceptorBase::writeTimeout, this, _1));

    waitForWriteOperationsBeCompleted();

    return m_sendingStatus;
}

//==============================================================================

statuscodes::Codes IbeoTcpIpAcceptorBase::sendRawDataBlock(const IbeoDataHeader& dh,
                                                           const char* const dataPayloadBuffer)
{
    issueRawWriteOperations(dh, dataPayloadBuffer);

    m_writeExprirationTimer.expires_from_now(m_writeExpirationPeriod);
    m_writeExprirationTimer.async_wait(boost::bind(&IbeoTcpIpAcceptorBase::writeTimeout, this, _1));

    waitForWriteOperationsBeCompleted();

    return m_sendingStatus;
}

//==============================================================================

void IbeoTcpIpAcceptorBase::handleAccept(const boost::system::error_code& error)
{
    if (!error)
    {
        {
            boost::mutex::scoped_lock lock(m_sessionsMutex);
            m_sessions.push_back(getSessionPtr());
            getSessionPtr()->startListening();
            getSessionPtr()->setConnectionALive(true);
        }

        m_sessionPtr = getNewSessionPtr(m_ioService);
        m_acceptor.async_accept(
            m_sessionPtr->getSocket(),
            boost::bind(&IbeoTcpIpAcceptorBase::handleAccept, this, boost::asio::placeholders::error));
    }
    else
    {
        LOGERROR(logger, "not able to handle accept with error " << error);
    }
}

//==============================================================================

void IbeoTcpIpAcceptorBase::closeAcceptor()
{
    m_ioService.stop();
    m_acceptIOServiceThreadPtr->join();
}

//==============================================================================

void IbeoTcpIpAcceptorBase::acceptorIOServiceThread() { m_ioService.run(); }

//==============================================================================

void IbeoTcpIpAcceptorBase::writeDone(SessionBase* const session,
                                      const boost::system::error_code& error,
                                      const std::size_t nbOfBytesTransfered)
{
    if (error)
    {
        LOGERROR(logger, (void*)(session) << " Error: " << error.message());
        m_sendingStatus = statuscodes::SendingDataBlockFailed;

        boost::mutex::scoped_lock sendLock(m_writeCondMutex);

        m_activeSending.erase(session);

        // wakeup receiver
        session->setConnectionALive(false);
        if (m_writeState != WS_TimeOut)
            m_writeState = WS_Error;

        writeCondition.notify_all();
        return;
    }

    session->setSizeOfPrevMsg(uint32_t(nbOfBytesTransfered - ibeo::common::sdk::IbeoDataHeader::getHeaderSize()));

    {
        boost::mutex::scoped_lock sendLock(m_writeCondMutex);

        std::map<SessionBase*, uint32_t>::iterator fIter = m_activeSending.find(session);
        if (fIter != m_activeSending.end())
        {
            LOGDEBUG(logger,
                     "Handling " << (void*)(session) << " Size: " << nbOfBytesTransfered
                                 << " expected: " << fIter->second);

            if (fIter->second > nbOfBytesTransfered)
            {
                fIter->second -= uint32_t(nbOfBytesTransfered);
            }
            else
            {
                m_activeSending.erase(fIter);
            }
        }

        if (m_activeSending.empty())
        {
            // wakeup receiver
            m_writeState = WS_Completed;

            writeCondition.notify_all();
            m_writeExprirationTimer.cancel();
        }
    }
}

//==============================================================================

void IbeoTcpIpAcceptorBase::writeTimeout(const boost::system::error_code&)
{
    boost::mutex::scoped_lock sendLock(m_writeCondMutex);

    if (m_writeState == WS_InProgress)
    {
        m_writeState = WS_TimeOut;
        cancelWriteOperations();
        writeCondition.notify_all();
    }
    return;
}

//==============================================================================

void IbeoTcpIpAcceptorBase::cancelWriteOperations()
{
    std::map<SessionBase*, uint32_t>::iterator sessionIter = m_activeSending.begin();
    for (; sessionIter != m_activeSending.end(); ++sessionIter)
    {
        sessionIter->first->cancelAsyncIos();
    }
}

////======================================================================
//
//void IbeoTcpIpAcceptorEcu::SessionEcu::readTimeout(const boost::system::error_code& error)
//{
//	if (m_socket.is_open()) {
//		if (!error) {
//			LOGDEBUG(logger, "Restart read timer");
//			startTimer();
//		}
//		else { // open or error occurred
//			LOGTRACE(logger, error.message());
//			LOGDEBUG(logger, "Canceling read operation");
//			m_socket.cancel();
//		}
//	}
//}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

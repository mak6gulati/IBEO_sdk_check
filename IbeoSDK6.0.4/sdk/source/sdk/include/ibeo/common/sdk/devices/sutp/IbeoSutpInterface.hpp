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
//! \date Aug 31, 2016
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/sutp/SutpHeader.hpp>
#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>
#include <ibeo/common/logging/logging.hpp>

#include <boost/unordered_map.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/function.hpp>

#include <istream>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//! \class IbeoSutpInterface
//! \brief Implementation of SUTP (receiving part).
//! \date Aug 31, 2016
//!
//! Devices that use this interface communicate data using the Ibeo data
//! layer protocol on top of SUTP.
//------------------------------------------------------------------------------
class IbeoSutpInterface
{
public:
    //========================================
    //! \brief SUTP payload as raw data
    //----------------------------------------
    using SutpPayload = std::vector<char>;

    //========================================
    //! \brief Smart pointer to SUTP payload
    //----------------------------------------
    using SutpPayloadPtr = std::shared_ptr<SutpPayload>;

    //========================================
    //! \brief Smart pointer to SutpHeader
    //----------------------------------------
    using SutpHeaderPtr = std::shared_ptr<SutpHeader>;

    //========================================
    //! \brief Single sudp fragment
    //----------------------------------------
    using SudpFragment = std::pair<SutpHeaderPtr, SutpPayloadPtr>;

    using CacheType = boost::unordered_map<uint16_t, SudpFragment>;

    using MapEntry = std::pair<uint16_t, SudpFragment>;

    //========================================
    //! \brief Signature of the handler that
    //!        processes received messages.
    //----------------------------------------
    using MessageHandler = boost::function<bool(const char* bodyBuf, size_t len)>;

public:
    static const uint64_t sutpDefaultTimeout;
    static const uint64_t sutpFragmentSize;
    static const uint32_t defaultErrorResetLimit;

public:
    //========================================
    //! \brief Private Constructor.
    //!
    //! Constructor is private because this
    //! class must only be used through the
    //! std::shared_ptr. Use create()
    //! to instantiate.
    //----------------------------------------
    IbeoSutpInterface(MessageHandler msgHandler,
                      const uint64_t timeout       = sutpDefaultTimeout,
                      const uint32_t errResetLimit = defaultErrorResetLimit);

    //========================================
    //! \brief Destructor
    //!
    //! Closes the connection if necessary.
    //----------------------------------------
    virtual ~IbeoSutpInterface();

private:
    //========================================
    //! \brief Forbidden default constructor.
    //----------------------------------------
    IbeoSutpInterface(); // forbidden

public:
    //========================================
    //! \brief Sets the callback function of
    //!        the receiver.
    //----------------------------------------
    void setMessageHandler(MessageHandler msgHandler);

    //========================================
    //! \brief Deregister the MessageHandler.
    //!
    //! This method should be called by the
    //! object owning the MessageHandler if it
    //! is being destructed, so that this
    //! IbeoTcpIpInterface does not
    //! accidentally call a handler on a
    //! deleted object.
    //----------------------------------------
    void deregisterMessageHandler();

    //========================================
    //! \brief Processes incoming data.
    //----------------------------------------
    bool onReceiveRaw(std::istream& is, const uint32_t messageSize);

    //========================================
    //! \brief check cache for available
    //!        IbeoDataLayer paket and process.
    //----------------------------------------
    void processCache();

    boost::condition& getPacketCompleteCondition() { return m_paketComplete; }
    boost::recursive_mutex& getPacketCompleteMutex() { return m_paketCacheMutex; }

private:
    //========================================
    //! \brief processes a single IbeoDataLayer
    //!        paket.
    //----------------------------------------
    void processPaket();

    bool findSegNo(CacheType::const_iterator& fIter, const uint16_t seqNo);

    //========================================
    //! \brief checks if the oldest paket is
    //!        complete.
    //----------------------------------------
    bool isPacketComplete();

    //========================================
    //! \brief removes outdated fragments from
    //!        cache.
    //----------------------------------------
    void clearOutdatedFragments();

    //========================================
    //! \brief resets the internal state to
    //!        initial values.
    //----------------------------------------
    void reset();

protected:
    static constexpr const char* loggerId = "ibeo::common::sdk::IbeoSutpInterface";
    static ibeo::common::logging::LoggerSPtr logger;

protected:
    //! timeout for SUTP packets
    const uint64_t m_sutpTimeout;

    const uint32_t m_errorResetLimit;

protected:
    //! map containing cached fragments. Key = seqNb
    boost::unordered_map<uint16_t, SudpFragment> m_fragmentCache;

    //! next SUTP sequence number to be processed.
    //! this has to always be the seqNb of the first fragment
    uint16_t m_nextSeqNbProc;

    //! indicates if #m_nextSeqNb contains invalid value.
    //! should be permanently false after receiving first fragment
    bool m_nextSeqNbProcInvalid;

    //! current SUTP time. used to detect outdated pakets
    uint64_t m_sutpTime;

    //! mutex for synchronizing receive thread and callbackThread
    boost::recursive_mutex m_paketCacheMutex;

    //! condition for signaling complete ibeoDataLayer pakets
    boost::condition m_paketComplete;

    //! error counter (reinitialization trigger)
    uint16_t m_numConsecutiveErrors;

    //! Message handler callback for complete ibeo data message
    MessageHandler m_onReceive;

    uint32_t m_nbOfReceivedPackages;
    uint32_t m_nbOfDroppedPackages;
}; // IbeoSutpInterface

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

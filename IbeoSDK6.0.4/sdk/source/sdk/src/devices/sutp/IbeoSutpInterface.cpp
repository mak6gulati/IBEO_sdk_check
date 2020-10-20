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

#include <ibeo/common/sdk/devices/sutp/IbeoSutpInterface.hpp>

#include <ibeo/common/sdk/devices/sutp/SutpHeader.hpp>
#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/iostreams/stream.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

const uint64_t IbeoSutpInterface::sutpDefaultTimeout     = 80; // [ms]
const uint64_t IbeoSutpInterface::sutpFragmentSize       = 8024; // incl Hdr
const uint32_t IbeoSutpInterface::defaultErrorResetLimit = 10;

//==============================================================================

ibeo::common::logging::LoggerSPtr IbeoSutpInterface::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

IbeoSutpInterface::IbeoSutpInterface(MessageHandler msgHandler, const uint64_t timeout, const uint32_t errResetLimit)
  : m_sutpTimeout(timeout),
    m_errorResetLimit(errResetLimit),
    m_fragmentCache(),
    m_nextSeqNbProc(0),
    m_nextSeqNbProcInvalid(true),
    m_sutpTime(0),
    m_paketCacheMutex(),
    m_paketComplete(),
    m_numConsecutiveErrors(0),
    m_onReceive(msgHandler),
    m_nbOfReceivedPackages(0),
    m_nbOfDroppedPackages(0)
{
    { //mutexed
        boost::recursive_mutex::scoped_lock lock(m_paketCacheMutex);
        m_fragmentCache.rehash(size_t(std::numeric_limits<uint16_t>::max() >> 1));
    } //mutexed
    //	m_paketComplete.notify_all();
}

//==============================================================================

void IbeoSutpInterface::reset()
{
    LOGINFO(logger, "Resetting SUTP Protocol");
    { //mutexed
        boost::recursive_mutex::scoped_lock lock(m_paketCacheMutex);
        m_fragmentCache.clear();
    } //mutexed
    //	m_paketComplete.notify_all();

    m_nextSeqNbProc        = 0;
    m_nextSeqNbProcInvalid = true;
    m_sutpTime             = 0;
    m_numConsecutiveErrors = 0;
}

//==============================================================================

IbeoSutpInterface::~IbeoSutpInterface()
{
    LOGINFO(logger, m_nbOfReceivedPackages << " received packages, " << m_nbOfDroppedPackages << " dropped packages");
}

//==============================================================================

void IbeoSutpInterface::setMessageHandler(IbeoSutpInterface::MessageHandler msgHandler) { m_onReceive = msgHandler; }

//==============================================================================

void IbeoSutpInterface::deregisterMessageHandler() { m_onReceive = NULL; }

//==============================================================================

bool IbeoSutpInterface::onReceiveRaw(std::istream& is, const uint32_t messageSize)
{
    if (!is || (!is.good()))
    {
        return false;
    }

    if (messageSize < uint32_t(SutpHeader::getSerializedSize_Static()))
    {
        return false;
    }

    ++m_nbOfReceivedPackages;

    // read sutp header
    std::shared_ptr<SutpHeader> sh = std::make_shared<SutpHeader>();
    sh->deserialize(is);
    if (!is || (!is.good()))
    {
        LOGWARNING(logger, "Error reading SUTP header. Dropping paket.");
        ++m_numConsecutiveErrors;
        if (m_numConsecutiveErrors > m_errorResetLimit)
        {
            reset();
        }
        return false;
    }

    const boost::posix_time::ptime tmpTs = boost::posix_time::microsec_clock::local_time();
    const boost::posix_time::ptime epoch
        = boost::posix_time::ptime(boost::gregorian::date(1950, boost::gregorian::Dec, 1));
    sh->setTimestamp(uint64_t((tmpTs - epoch).total_milliseconds()));
    m_sutpTime = std::max(m_sutpTime, sh->getTimestamp());

    { // mutexed
        boost::recursive_mutex::scoped_lock lock(m_paketCacheMutex);
        if (m_fragmentCache.find(sh->getSeqNo()) != m_fragmentCache.end()
            || (!m_nextSeqNbProcInvalid && (int32_t(sh->getSeqNo() - m_nextSeqNbProc) < 0)))
        {
            LOGWARNING(logger,
                       "Received sequence number twice or out of order: " << sh->getSeqNo() << ". Dropping paket.");

            ++m_numConsecutiveErrors;
            if (m_numConsecutiveErrors > m_errorResetLimit)
            {
                reset();
            }
            return false;
        }

        // read datatype payload
        const uint32_t datatypePayloadSize                 = messageSize - uint32_t(sh->getSerializedSize());
        std::shared_ptr<std::vector<char>> datatypePayload = std::make_shared<std::vector<char>>();
        ;
        datatypePayload->resize(datatypePayloadSize);
        if (datatypePayloadSize > 0)
        {
            is.read(&((*datatypePayload)[0]), datatypePayloadSize);
        }

        if (!is || (!is.good()))
        {
            LOGWARNING(logger, "Failed to get SUTP payload. dropping paket.");
            ++m_numConsecutiveErrors;
            if (m_numConsecutiveErrors > m_errorResetLimit)
            {
                reset();
            }
            return false;
        }

        // first fragment ever? --> set last used seqNo
        if (m_nextSeqNbProcInvalid)
        {
            m_nextSeqNbProc        = uint16_t(sh->getSeqNo() - (sh->getFragNo() - 1));
            m_nextSeqNbProcInvalid = false;
        }

        // cache fragment
        SudpFragment frag(sh, datatypePayload);
        m_fragmentCache[sh->getSeqNo()] = frag;
        assert(frag.first.get() != NULL);
        m_paketComplete.notify_all();
    } // mutexed

    return true;
}

//==============================================================================

void IbeoSutpInterface::processCache()
{
    if (m_nextSeqNbProcInvalid)
    {
        return;
    }

    while (isPacketComplete())
    {
        processPaket();
    }

    clearOutdatedFragments();

    while (isPacketComplete())
    {
        processPaket();
    }
}

//==============================================================================

void IbeoSutpInterface::processPaket()
{
    { // mutexed
        boost::recursive_mutex::scoped_lock lock(m_paketCacheMutex);
        const uint16_t totalNbOfFragments = m_fragmentCache[m_nextSeqNbProc].first->getFragsTotal();

        const std::shared_ptr<char> buffer(new char[totalNbOfFragments * sutpFragmentSize],
                                           std::default_delete<char[]>());
        const char* const startPointer = buffer.get();
        char* writePointer             = buffer.get();

        uint16_t segNo = 0;
        bool complete  = false;
        for (segNo = m_nextSeqNbProc; !complete; ++segNo)
        {
            const SutpPayload& sutpPayload = *m_fragmentCache[segNo].second;
            const SutpHeader& sutpHeader   = *(m_fragmentCache[segNo].first.get());

            const uint16_t chunkSize = uint16_t(sutpPayload.size());

            std::memcpy(writePointer, &sutpPayload[0], size_t(chunkSize));
            writePointer += chunkSize;

            if (sutpHeader.getFragNo() == sutpHeader.getFragsTotal())
            {
                complete = true;
            }
        }

        // use value of i
        // Drop used fragments
        for (; m_nextSeqNbProc != segNo; ++m_nextSeqNbProc)
        {
            m_fragmentCache.erase(m_nextSeqNbProc);
        }

        const uint32_t dataSize = uint32_t(writePointer - startPointer);

        try
        {
            if (m_onReceive)
            {
                m_onReceive(buffer.get(), dataSize);
            }
        }
        catch (const std::exception& e)
        {
            LOGWARNING(logger, "exception during onReceive Callback: " << e.what());
        }

        //m_paketComplete.notify_all();
    } // mutexed

    m_numConsecutiveErrors = 0;
}

//==============================================================================

bool IbeoSutpInterface::findSegNo(CacheType::const_iterator& fIter, const uint16_t seqNo)
{
    fIter = m_fragmentCache.find(seqNo);
    return fIter != m_fragmentCache.end();
}

//==============================================================================

bool IbeoSutpInterface::isPacketComplete()
{
    bool complete  = false;
    uint16_t seqNo = m_nextSeqNbProc;

    CacheType::const_iterator fIter;
    { // mutexed
        boost::recursive_mutex::scoped_lock lock(m_paketCacheMutex);
        while (findSegNo(fIter, seqNo))
        {
            const std::shared_ptr<const SutpHeader> shp = fIter->second.first;
            if (shp->getFragNo() == shp->getFragsTotal())
            {
                complete = true;
                break;
            }
            ++seqNo;
        }
    } //mutexed
    return complete;
}

//==============================================================================

void IbeoSutpInterface::clearOutdatedFragments()
{
    { //mutexed
        boost::recursive_mutex::scoped_lock lock(m_paketCacheMutex);
        boost::unordered_map<uint16_t, SudpFragment>::iterator it = m_fragmentCache.begin();
        for (; it != m_fragmentCache.end();)
        {
            if ((m_sutpTime - it->second.first->getTimestamp()) > m_sutpTimeout)
            {
                bool ibeoDataPacketLost = false;
                //wrap around handling
                if (int16_t(it->first - m_nextSeqNbProc) >= 0)
                {
                    const uint16_t paketStartSeqNo = uint16_t(it->first - (it->second.first->getFragNo() - 1U));
                    m_nextSeqNbProc                = uint16_t(paketStartSeqNo + it->second.first->getFragsTotal());
                    ibeoDataPacketLost             = true;
                }
                LOGWARNING(logger,
                           "Paket timed out (seqNo=" << it->first << "; " << toHex(it->second.first->getDatatype())
                                                     << "; frag=" << it->second.first->getFragNo() << "/"
                                                     << it->second.first->getFragsTotal() << "). Dropping paket.");
                ++m_nbOfDroppedPackages;
                boost::unordered_map<uint16_t, SudpFragment>::iterator delIt = it;
                ++it;
                m_fragmentCache.erase(delIt);
                if (ibeoDataPacketLost)
                {
                    ++m_numConsecutiveErrors;
                    if (m_numConsecutiveErrors > m_errorResetLimit)
                    {
                        reset();
                    }
                    break;
                }
            }
            else
            {
                ++it;
            }
        } // for all entries in m_fragmentCache
        //m_paketComplete.notify_all();
    } //mutexed
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

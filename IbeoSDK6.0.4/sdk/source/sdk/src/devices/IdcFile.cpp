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
//!\date April 4, 2012
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/devices/IdcFile.hpp>

#include <ibeo/common/sdk/listener/DataContainerListener.hpp>
#include <ibeo/common/sdk/listener/DataListener.hpp>

#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130Exporter6130.hpp>
#include <ibeo/common/sdk/datablocks/frameindex/special/FramingPolicyIn6130.hpp>
#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndexEntryIn6130.hpp>

#include <boost/iostreams/stream.hpp>
#include <ibeo/common/sdk/devices/IdcFileController.hpp>

#include <iostream>
#include <stdexcept>

// Allow deprecated warnings in deprecated code to avoid
// compiler errors because of deprecated dependencies.
ALLOW_WARNING_DEPRECATED

#if (defined(_MSC_VER) & _MSC_VER < 1600) | defined(__MINGW32__)
#    include <io.h> // for _filelength64()
#    include <fcntl.h> // for _O_RDONLY
#endif

#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif // gcc or clang

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ibeo::common::logging::LoggerSPtr IdcFile::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

IdcFile::IdcFile()
  : m_cbaip{ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance()},
    m_dbbp{DataBlockBufferProviderGlobal<IdcFile>::getInstance()}
{
    std::stringstream stream;
    stream << std::endl << "Create Device:";

    {
        stream << std::endl << "Registered DataContainer: ";
        std::list<ImporterBase::ImporterRegisterId::Key> dtList = getIdsOfSupportedDataContainer();
        for (const ImporterBase::ImporterRegisterId::Key& key : dtList)
        {
            stream << std::endl << std::hex << "0x" << key.first << "  " << std::dec << key.second;
        }
    }

    {
        stream << std::endl << "Registered DataTypes: ";
        std::list<DataBlock::DataBlockRegisterId::Key> dtList = getIdsOfSupportedDataBlocks();
        for (const DataBlock::DataBlockRegisterId::Key& key : dtList)
        {
            stream << std::endl << std::hex << "0x" << key << std::dec;
        }
    }

    LOGTRACE(logger, stream.str());
}

//==============================================================================

IdcFile::~IdcFile() { this->close(); }

//==============================================================================
//!Opens the given file
//------------------------------------------------------------------------------
bool IdcFile::open(const std::string& filename, const bool readFrameIndex)
{
    this->close();
    m_latestMsgSize             = 0;
    m_latestHeaderTimestamp     = NTPTime();
    m_firstDataBlockToBeWritten = false;

    m_filename.clear();
    m_posBeg = -1;

    m_openMode = std::fstream::in | std::fstream::binary;
    m_strm.open(filename.c_str(), m_openMode);
    if (this->isOpen())
    {
        m_posBeg = static_cast<int64_t>(std::streamoff(m_strm.tellg()));

        if (readFrameIndex && (!loadFrameIndex()))
        {
            m_strm.close();
            m_posBeg = -1;
            return false;
        }

        m_filename = filename;

        return true;
    }

    return false;
}

//==============================================================================
// TODO: In append mode, the FrameIndex is not correctly filled.
bool IdcFile::create(const std::string& filename, const bool append)
{
    this->close();
    m_latestMsgSize             = 0;
    m_latestHeaderTimestamp     = NTPTime();
    m_firstHeaderTimestamp      = NTPTime();
    m_firstDataBlockToBeWritten = true;

    if (append)
    {
        m_openMode = std::fstream::out | std::fstream::binary | std::fstream::app;
    }
    else
    {
        m_openMode = std::fstream::out | std::fstream::binary;
    }

    this->m_strm.open(filename.c_str(), m_openMode);

    ibeo::common::sdk::FramingPolicyIn6130::TriggerSet triggers;
    triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_Scan2205,
                                                 ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));
    //no datatype Scan2202
    //triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_Scan2202, ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));
    triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_Scan2208,
                                                 ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));
    triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_Scan2209,
                                                 ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));
    triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_Scan2310,
                                                 ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));
    triggers.insert(FramingPolicyIn6130::Trigger(ibeo::common::sdk::DataTypeId::DataType_IdcTrailer6120,
                                                 ibeo::common::sdk::FramingPolicyIn6130::deviceIdAny));

    ibeo::common::sdk::FramingPolicyIn6130 policy;
    policy.setTriggerInNewFrame(true);
    policy.setTriggers(triggers);
    m_frameIndex.setFramingPolicy(policy);
    m_frameIndex.clearFrames();

    if (this->isOpen())
    {
        m_filename = filename;
        m_posBeg   = static_cast<int64_t>(std::streamoff(m_strm.tellg()));
        return true;
    }

    m_filename.clear();
    m_posBeg = -1;
    return false;
}

//==============================================================================

std::unique_ptr<IdcFileController> IdcFile::createController()
{
    return std::unique_ptr<IdcFileController>{new IdcFileController(*this, m_strm)};
}

//==============================================================================

bool IdcFile::write(const IbeoDataHeader& dh, const char* const body)
{
    if (!isOpen())
    {
        return false;
    }

    const bool headerOk = writeHeader(dh);

    if (headerOk)
    {
        return write(body, dh.getMessageSize());
    }
    return false;
}

//==============================================================================

bool IdcFile::write(const IbeoDataHeader& dh, const DataBlock* const db)
{
    if (!isOpen())
    {
        return false;
    }

    const bool headerOk = writeHeader(dh);

    if (headerOk)
    {
        return db->serialize(this->m_strm);
    }
    return false;
}

//==============================================================================

//==============================================================================
//!\internal
//! \a dh is not const since the copy is modified
//! inside the method.
//------------------------------------------------------------------------------
bool IdcFile::write(IbeoDataHeader dh, const DataContainerBase& c, const ExporterBase& exporter)
{
    if (!isOpen())
    {
        return false;
    }

    dh.setDataType(exporter.getDataType());
    dh.setMessageSize(static_cast<uint32_t>(exporter.getSerializedSize(c)));

    const bool headerOk = writeHeader(dh);
    if (headerOk)
    {
        return exporter.serialize(m_strm, c);
    }
    return false;
}

//==============================================================================

bool IdcFile::writeHeader(IbeoDataHeader dh)
{
    if (!this->isOpen())
    {
        return false;
    }

    if (m_firstHeaderTimestamp == NTPTime())
    {
        m_firstHeaderTimestamp = dh.getTimestamp();
    }

    if (!m_firstDataBlockToBeWritten)
    {
        dh.setPreviousMessageSize(m_latestMsgSize);
    }
    else
    {
        dh.setPreviousMessageSize(0);
        m_firstDataBlockToBeWritten = false;
    }

    // update frame index if necessary
    if (m_frameIndex.getFramingPolicy().isTrigger(dh.getDataType(), dh.getDeviceId()))
    {
        // add the frame before the header is written
        const uint64_t frameOffsetMs = (dh.getTimestamp() - m_firstHeaderTimestamp).getMilliseconds();

        ibeo::common::sdk::FrameIndexEntryIn6130 entry(
            uint64_t(streamposToInt64(m_strm.tellp())), frameOffsetMs, dh.getDeviceId());
        m_frameIndex.addFrame(entry);
    }

    if (dh.serialize(this->m_strm))
    {
        m_latestHeaderTimestamp = dh.getTimestamp();
        m_latestMsgSize         = dh.getMessageSize();
        return true;
    }
    else
    {
        return false;
    }
}

//==============================================================================

bool IdcFile::write(const char* const data, const uint32_t length)
{
    if (!this->isOpen())
    {
        return false;
    }
    this->m_strm.write(data, length);

    return this->m_strm.good();
}

//==============================================================================

bool IdcFile::isOpen() { return this->m_strm.is_open(); }

//==============================================================================

bool IdcFile::isEof() { return this->m_strm.eof(); }

//==============================================================================

void IdcFile::close()
{
    if (!this->isOpen())
    {
        return;
    }

    if (m_openMode & std::fstream::out)
    {
        FrameIndex6130Exporter6130 fiExporter;
        IbeoDataHeader frameIndexHeader(DataTypeId::DataType_FrameIndex6130,
                                        m_latestMsgSize,
                                        uint32_t(fiExporter.getSerializedSize(m_frameIndex)),
                                        FramingPolicyIn6130::deviceIdAny,
                                        m_latestHeaderTimestamp);
        this->writeHeader(frameIndexHeader);

        fiExporter.serialize(this->m_strm, m_frameIndex);

        IbeoDataHeader trailerHeader(DataTypeId::DataType_IdcTrailer6120,
                                     m_latestMsgSize,
                                     0,
                                     FramingPolicyIn6130::deviceIdAny,
                                     m_latestHeaderTimestamp);
        this->writeHeader(trailerHeader);
        // trailer.serialize(this->m_strm); is of size 0
    }

    this->m_strm.close();

    m_filename.clear();
    m_frameIndex.clearFrames();
    m_latestMsgSize         = 0;
    m_latestHeaderTimestamp = NTPTime();
}

//==============================================================================

int64_t IdcFile::getPos()
{
    if (!isOpen() || !isGood())
    {
        return -1;
    }

    return static_cast<int64_t>(std::streamoff(m_strm.tellg())) - m_posBeg;
}

//==============================================================================

bool IdcFile::isGood() { return this->m_strm.good(); }

//==============================================================================

std::list<ImporterBase::ImporterRegisterId::Key> IdcFile::getIdsOfSupportedDataContainer() const
{
    std::list<ImporterBase::ImporterRegisterId::Key> keyList;

    using PM     = typename ContainerBufferAndImporterProvider<IdcFile>::ProviderMap;
    const PM& pm = m_cbaip.getMap();

    for (const PM::value_type& entry : pm)
    {
        keyList.push_back(entry.first);
    } // for iter
    keyList.sort();
    return keyList;
}

//==============================================================================

std::list<DataBlock::DataBlockRegisterId::Key> IdcFile::getIdsOfSupportedDataBlocks() const
{
    std::list<DataBlock::DataBlockRegisterId::Key> keyList;

    using PM     = typename DataBlockBufferProvider<IdcFile>::ProviderMap;
    const PM& pm = m_dbbp.getMap();

    for (const PM::value_type& entry : pm)
    {
        keyList.push_back(entry.first);
    } // for iter
    keyList.sort();
    return keyList;
}

//==============================================================================

const DataBlock* IdcFile::deserialize(std::istream& is, DataBlock& db, const IbeoDataHeader& dh)
{
    db.setDataHeader(dh);
    if (db.deserialize(is, dh))
    {
        return &db;
    }

    LOGERROR(logger, "Failed to deserialization data type 0x" << std::hex << dh.getDataType() << std::dec);
    return nullptr;
}

//==============================================================================

bool IdcFile::loadFrameIndex()
{
    std::unique_ptr<IdcFileController> ifc{createController()};

    if (!ifc->setToIdcTrailer())
    {
        LOGERROR(logger, "Could not find IDC trailer (0x6120) at end of file.");
        return false;
    }

    if (ifc->skipDataBlocksBackwards(1) && ifc->getNextHeader(m_dh)
        && (m_dh.getDataType() != DataTypeId::DataType_FrameIndex6130))
    {
        LOGERROR(logger, "Could not find FrameIndex (0x6130) before IDC trailer.");
        return false;
    }

    FrameIndexListener l;
    this->registerContainerListener(&l);

    const IdcFile::ContainerImporterPairs frameIndex = IdcFile::getNextDataContainer();

    this->unregisterContainerListener(&l);

    if (frameIndex.empty())
    {
        LOGERROR(logger, "Failed to read FrameIndex (0x6130)");
        return false;
    }
    else if (const FrameIndex6130* frIdx = dynamic_cast<const FrameIndex6130*>(frameIndex[0].first))
    {
        m_frameIndex = *frIdx;
        return ifc->setToFirstDataBlock();
    }
    else
    {
        LOGERROR(logger, "Unknown error reading the FrameIndex (0x6130).");
        return false;
    }
}

//==============================================================================

const DataBlock* IdcFile::getNextDataBlock()
{
    if (!isOpen())
    {
        return nullptr;
    }

    if (!this->m_dh.deserialize(this->m_strm))
    {
        return nullptr;
    }

    DataBlock* db1 = m_dbbp.getBuffer(m_dh.getDataType());
    if (db1)
    {
        if (const DataBlock* db = deserialize(m_strm, *db1, m_dh))
        {
            return db;
        }
        else
        {
            LOGERROR(logger, "Called from here");
            return nullptr;
        }
    }

    LOGDEBUG(logger,
             "Ignoring unknown datatype "
                 << "0x" << std::hex << m_dh.getDataType() << std::dec);

    m_strm.ignore(m_dh.getMessageSize());
    return nullptr;
}

//==============================================================================

IdcFile::ContainerImporterPairs IdcFile::getNextDataContainer()
{
    std::vector<std::pair<DataContainerBase*, ImporterBase*>> pairs;

    if (!isOpen())
    {
        return pairs;
    }

    if (!this->m_dh.deserialize(this->m_strm))
    {
        return pairs;
    }

    if (!m_registeredContainerListeners.empty())
    {
        std::vector<char> bodyBuf;

        // Collect DataContainerListeners (special or general data container with explicit type ID).
        addDataContainerImporterPairsToVector(m_dh.getDataType(), bodyBuf, pairs);

        // Collect GeneralDataContainerListeners (general data container only).
        addDataContainerImporterPairsToVector(DataTypeId::DataType_Unknown, bodyBuf, pairs);

        return pairs;
    } // are any

    LOGDEBUG(logger,
             "Ignoring unknown datatype "
                 << "0x" << std::hex << m_dh.getDataType() << std::dec);
    m_strm.ignore(m_dh.getMessageSize());

    return pairs;
}

//==============================================================================

void IdcFile::addDataContainerImporterPairsToVector(const DataTypeId dataType,
                                                    std::vector<char> bodyBuf,
                                                    ContainerImporterPairs& pairs)
{
    auto cllmIter = m_registeredContainerListeners.find(dataType);
    if (cllmIter != m_registeredContainerListeners.end())
    {
        ContainerListenerListMap& cllm = cllmIter->second;

        for (auto& containerTypeIter : cllm)
        {
            auto containerHashId = containerTypeIter.first.second;
            const ImporterBase::ImporterRegisterId::Key containerId
                = std::make_pair(m_dh.getDataType(), containerHashId);

            ImporterBase* importer;
            importer = m_cbaip.getImporter(containerId);

            if (!importer)
            {
                if (dataType != DataTypeId::DataType_Unknown)
                {
                    LOGDEBUG(logger,
                             "Ignoring unknown Importer "
                                 << "0x" << std::hex << m_dh.getDataType() << std::dec
                                 << " of size: " << m_dh.getMessageSize() << " bytes.");
                }
                // else: general container listeners register without a data type. Thus, it might happen that there is
                // no importer for the current container type and the received data ytpe ID -> do not print a warning.

                continue;
            }

            DataContainerBase* container = m_cbaip.getBuffer(containerId);
            if (container)
            {
                std::pair<DataContainerBase*, ImporterBase*> containerImporterPair
                    = std::make_pair(container, importer);
                if (find(pairs.begin(), pairs.end(), containerImporterPair) == pairs.end())
                {
                    if (bodyBuf.empty())
                    {
                        // Message not read into buffer yet -> do it now.
                        const uint32_t bodySize = m_dh.getMessageSize();
                        bodyBuf.resize(bodySize);
                        m_strm.read(&bodyBuf[0], bodySize);
                    }

                    boost::iostreams::stream<boost::iostreams::array_source> is(bodyBuf.data(), bodyBuf.size());
                    if (importer->deserialize(is, *container, m_dh))
                    {
                        pairs.push_back(containerImporterPair);
                    }
                    else
                    {
                        LOGWARNING(logger,
                                   "Failed to deserialize"
                                       << "0x" << std::hex << m_dh.getDataType() << std::dec);
                    }
                }
            }
        }
    } // no listener for this datatype
}

////==============================================================================
//
//
//IdcFile::ContainerImporterPairs IdcFile::getFirstDataContainer(const bool clearStreamFlags)
//{
//	if ((!isOpen()) || (!setToFirstDataBlock(clearStreamFlags))) {
//		return IdcFile::ContainerImporterPairs{};
//	}
//
//	return getNextDataContainer();
//}
//
////==============================================================================
//
//IdcFile::ContainerImporterPairs IdcFile::getLastDataContainer(const bool clearStreamFlags)
//{
//	if ((!isOpen()) || (!setToLastDataBlock(clearStreamFlags))) {
//		return IdcFile::ContainerImporterPairs{};
//	}
//
//	return getNextDataContainer();
//}

//==============================================================================

std::shared_ptr<char> IdcFile::getNextDataBlockRaw(IbeoDataHeader& dh)
{
    std::shared_ptr<char> buf;
    if (!isOpen())
    {
        return buf; // nullptr
    }

    if (!this->m_dh.deserialize(this->m_strm))
    {
        return buf; // nullptr
    }

    dh = m_dh;

    buf.reset(new char[dh.getMessageSize()], std::default_delete<char[]>());
    m_strm.read(buf.get(), dh.getMessageSize());
    if (m_strm.fail())
    {
        LOGERROR(logger, "Failed to read data type 0x" << std::hex << dh.getDataType() << std::dec);
        buf.reset();
    }

    return buf;
}

//==============================================================================

void IdcFile::registerListener(DataListenerBase* const listener)
{
    for (const DataTypeId& dataType : listener->getAssociatedDataTypes())
    {
        m_listeners[dataType].push_back(listener);
    }
}

//==============================================================================

void IdcFile::registerContainerListener(DataContainerListenerBase* const containerListener)
{
    for (const DataContainerListenerBase::DataTypeHashPair& dataTypeHashPair :
         containerListener->getAssociatedDataTypes())
    {
        ContainerListenerListMap& cllm = m_registeredContainerListeners[dataTypeHashPair.first];
        cllm[dataTypeHashPair].push_back(containerListener);
    }
}

//==============================================================================

statuscodes::Codes IdcFile::unregisterListener(DataListenerBase* const listener)
{
    statuscodes::Codes ret = statuscodes::EverythingOk;

    for (const DataTypeId& dataType : listener->getAssociatedDataTypes())
    {
        ListenerListMap::iterator llmIter = m_listeners.find(dataType);
        if (llmIter == m_listeners.end())
        {
            ret = statuscodes::ListenerNotRegistered;
            break;
        }

        ListenerList& list = llmIter->second;

        ListenerList::iterator listenerIter = std::find(list.begin(), list.end(), listener);
        if (listenerIter == list.end())
        {
            ret = statuscodes::ListenerNotRegistered;
            break;
        }

        list.erase(listenerIter);
    }

    return ret;
}

//==============================================================================

statuscodes::Codes IdcFile::unregisterContainerListener(DataContainerListenerBase* const containerListener)
{
    statuscodes::Codes ret = statuscodes::EverythingOk;

    // ContainerListenerer are registered in a doulbe map and vector:
    //  dataTypeId                              level 1
    //    ->  (dataTypeId, hash)                level 2
    //          -> vector<ContainerListener>)   list

    for (const DataContainerListenerBase::DataTypeHashPair& dataTypeHashPair :
         containerListener->getAssociatedDataTypes())
    {
        auto rcllmIter = m_registeredContainerListeners.find(dataTypeHashPair.first);
        if (rcllmIter == m_registeredContainerListeners.end())
        {
            ret = statuscodes::ListenerNotRegistered;
            break;
        }

        auto cllmIter = rcllmIter->second.find(dataTypeHashPair);
        if (cllmIter != rcllmIter->second.end())
        {
            ContainerListenerList& list = cllmIter->second;
            auto listenerIter           = std::find(list.begin(), list.end(), containerListener);
            if (listenerIter == list.end())
            {
                ret = statuscodes::ListenerNotRegistered;
                break;
            }

            list.erase(listenerIter);
        }

        // check whether the level 2 map is empty after erasing the containerListener
        if (cllmIter->second.begin() == cllmIter->second.end())
        {
            rcllmIter->second.erase(cllmIter);
        }
    }

    return ret;
}

//==============================================================================

void IdcFile::notifyListeners(const DataBlock* const data)
{
    if (data == nullptr)
    {
        return;
    }

    ListenerListMap::iterator list = m_listeners.find(data->getDataType());
    if (list != m_listeners.end())
    {
        ListenerList& listeners = list->second;
        for (DataListenerBase* const& listener : listeners)
        {
            data->callListener(*listener);
        } // for listener
    } // if list exists
}

//==============================================================================

void IdcFile::notifyContainerListeners(const DataContainerBase* const dataContainer, const ImporterBase* const importer)
{
    if ((!dataContainer) || (!importer))
    {
        return;
    }

    LOGDEBUG(logger, "Notify container hash " << dataContainer->getClassIdHash());

    std::vector<DataContainerListenerBase*> containerListeners;

    addDataContainerListenersToVector(importer->getDataType(), dataContainer->getClassIdHash(), containerListeners);
    addDataContainerListenersToVector(
        DataTypeId::DataType_Unknown, dataContainer->getClassIdHash(), containerListeners);

    for (DataContainerListenerBase* containerListener : containerListeners)
    {
        importer->callListener(containerListener, dataContainer);
    }
}

//==============================================================================

void IdcFile::addDataContainerListenersToVector(const DataTypeId dataType,
                                                const uint64_t containerHash,
                                                std::vector<DataContainerListenerBase*>& containerListeners) const
{
    auto l1mIter = m_registeredContainerListeners.find(dataType);
    if (l1mIter != m_registeredContainerListeners.end())
    {
        auto l2mIter = l1mIter->second.find(std::make_pair(dataType, containerHash));
        if (l2mIter != l1mIter->second.end())
        {
            const auto& listeners = l2mIter->second;
            for (DataContainerListenerBase* const& listener : listeners)
            {
                if (find(containerListeners.begin(), containerListeners.end(), listener) == containerListeners.end())
                {
                    containerListeners.push_back(listener);
                }
            } // for listenerIter
        }
    }
}

//==============================================================================

void IdcFile::notifyContainerListeners(const ContainerImporterPairs& containerImporterPairs)
{
    for (auto& p : containerImporterPairs)
    {
        notifyContainerListeners(p.first, p.second);
    }
}

//==============================================================================

void IdcFile::registerStreamer(DataStreamer* const streamer) { m_streamers.push_back(streamer); }

//==============================================================================

statuscodes::Codes IdcFile::unregisterStreamer(DataStreamer* const streamer)
{
    std::list<DataStreamer*>::iterator steamerIter = std::find(m_streamers.begin(), m_streamers.end(), streamer);
    if (steamerIter == m_streamers.end())
    {
        return statuscodes::StreamerNotRegistered;
    }

    m_streamers.erase(steamerIter);
    return statuscodes::EverythingOk;
}

//==============================================================================

void IdcFile::notifyStreamers(const IbeoDataHeader& dh, const std::shared_ptr<char> bodyBuf)
{
    if (bodyBuf.get() == nullptr)
    {
        return;
    }

    for (DataStreamer* const& streamer : m_streamers)
    {
        streamer->onData(dh, bodyBuf.get());
    }
}

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IdcFile>& getImporterCreatorMap<IdcFile>()
{
    return ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

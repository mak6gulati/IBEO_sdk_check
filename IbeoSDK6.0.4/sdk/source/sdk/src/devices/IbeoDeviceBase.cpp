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
//! \date Apr 7, 2015
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/devices/IbeoDeviceBase.hpp>

#include <ibeo/common/sdk/listener/DataStreamer.hpp>
#include <ibeo/common/sdk/listener/DataListener.hpp>
#include <ibeo/common/sdk/listener/DataContainerListener.hpp>
#include <ibeo/common/sdk/datablocks/ImporterBase.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

IbeoDeviceBase::IbeoDeviceBase() : m_listeners(), m_streamers() {}

//==============================================================================

IbeoDeviceBase::~IbeoDeviceBase() { this->disconnect(); }

//==============================================================================

void IbeoDeviceBase::disconnect() { this->unregisterAll(); }

//==============================================================================

void IbeoDeviceBase::unregisterAll()
{
    Lock lock(m_listenersStreamersMutex);

    this->m_listeners.clear();
    this->m_streamers.clear();
}

//==============================================================================

void IbeoDeviceBase::notifyStreamers(const IbeoDataHeader& dh, const char* const bodyBuf)
{
    if (bodyBuf == NULL)
        return;

    Lock lock(m_listenersStreamersMutex);

    for (DataStreamer*& streamer : m_streamers)
    {
        streamer->onData(dh, bodyBuf);
    }
}

//==============================================================================

void IbeoDeviceBase::notifyListeners(const DataBlock* const data)
{
    if (!data)
        return;

    Lock lock(m_listenersStreamersMutex);

    LOGDEBUG(m_logger, "Notify data type " << toHex(data->getDataType()));

    ListenerListMap::iterator list = m_listeners.find(data->getDataType());
    if (list != m_listeners.end())
    {
        for (DataListenerBase*& listener : list->second)
        {
            data->callListener(*listener);
        } // for listener
    } // if list exists
}

//==============================================================================

void IbeoDeviceBase::notifyContainerListeners(const DataContainerBase* const dataContainer,
                                              const ImporterBase* const importer)
{
    if ((!dataContainer) || (!importer))
        return;

    Lock lock(m_listenersStreamersMutex);

    LOGDEBUG(m_logger, "Notify container hash " << static_cast<const void*>(dataContainer));

    std::vector<DataContainerListenerBase*> containerListeners;

    addContainerListeners(importer->getDataType(), dataContainer->getClassIdHash(), containerListeners);
    addContainerListeners(DataTypeId::DataType_Unknown, dataContainer->getClassIdHash(), containerListeners);

    for (DataContainerListenerBase* containerListener : containerListeners)
    {
        importer->callListener(containerListener, dataContainer);
    }
}

//==============================================================================

void IbeoDeviceBase::addContainerListeners(const DataTypeId dataType,
                                           const DataContainerListenerBase::HashId containerHash,
                                           std::vector<DataContainerListenerBase*>& containerListeners) const
{
    auto l1mIter = m_registeredContainerListeners.find(dataType);
    if (l1mIter != m_registeredContainerListeners.end())
    {
        auto l2mIter = l1mIter->second.find(std::make_pair(dataType, containerHash));
        if (l2mIter != l1mIter->second.end())
        {
            for (DataContainerListenerBase* const& listener : l2mIter->second)
            {
                if (find(containerListeners.begin(), containerListeners.end(), listener) == containerListeners.end())
                {
                    containerListeners.push_back(listener);
                }
            } // for listener
        }
    }
}

//==============================================================================

void IbeoDeviceBase::registerListener(DataListenerBase* const listener)
{
    Lock lock(m_listenersStreamersMutex);

    for (const DataTypeId dataType : listener->getAssociatedDataTypes())
    {
        m_listeners[dataType].push_back(listener);
    }
}

//==============================================================================

void IbeoDeviceBase::registerContainerListener(DataContainerListenerBase* const containerListener)
{
    Lock lock(m_listenersStreamersMutex);

    for (const DataContainerListenerBase::DataTypeHashPair& key : containerListener->getAssociatedDataTypes())
    {
        ContainerListenerListMap& cllm = m_registeredContainerListeners[key.first];
        cllm[key].push_back(containerListener);
    }
}

//==============================================================================

statuscodes::Codes IbeoDeviceBase::unregisterListener(DataListenerBase* const listener)
{
    Lock lock(m_listenersStreamersMutex);

    statuscodes::Codes ret = statuscodes::EverythingOk;

    for (const DataTypeId dataType : listener->getAssociatedDataTypes())
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

statuscodes::Codes IbeoDeviceBase::unregisterListener(DataContainerListenerBase* const containerListener)
{
    statuscodes::Codes ret = statuscodes::EverythingOk;

    // ContainerListenerer are registered in a doulbe map and vector:
    //  dataTypeId                              level 1
    //    ->  (dataTypeId, hash)                level 2
    //          -> vector<ContainerListener>)   list

    Lock lock(m_listenersStreamersMutex);

    for (const DataContainerListenerBase::DataTypeHashPair& key : containerListener->getAssociatedDataTypes())
    {
        auto rcllmIter = m_registeredContainerListeners.find(key.first);
        if (rcllmIter == m_registeredContainerListeners.end())
        {
            ret = statuscodes::ListenerNotRegistered;
            break;
        }

        auto cllmIter = rcllmIter->second.find(key);
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

void IbeoDeviceBase::registerStreamer(DataStreamer* const streamer)
{
    Lock lock(m_listenersStreamersMutex);

    this->m_streamers.push_back(streamer);
}

//==============================================================================

statuscodes::Codes IbeoDeviceBase::unregisterStreamer(DataStreamer* const streamer)
{
    Lock lock(m_listenersStreamersMutex);

    std::list<DataStreamer*>::iterator steamerIter = std::find(m_streamers.begin(), m_streamers.end(), streamer);
    if (steamerIter == m_streamers.end())
        return statuscodes::StreamerNotRegistered;

    m_streamers.erase(steamerIter);
    return statuscodes::EverythingOk;
}

//==============================================================================

const DataBlock* IbeoDeviceBase::deserialize(std::istream& is, DataBlock& db, const IbeoDataHeader& dh)
{
    if (db.getDataType() != dh.getDataType())
    {
        LOGERROR(m_logger,
                 std::setfill('0') << "Tried to deserialize a "
                                   << "0x" << std::hex << std::setw(4) << dh.getDataType() << " DataBlock into a "
                                   << "0x" << std::hex << std::setw(4) << db.getDataType() << " object." << std::dec);
        return NULL;
    }

    db.setDataHeader(dh);
    if (db.deserialize(is, dh))
    {
        LOGDEBUG(m_logger, "Sucessfully deserializated data type " << toHex(uint16_t(dh.getDataType())));
        return &db;
    }
    LOGERROR(m_logger,
             "Failed to deserialization data type " << toHex(uint16_t(dh.getDataType()))
                                                    << "  size: " << dh.getMessageSize() << " bytes");
    return NULL;
}

//==============================================================================

std::ostream& operator<<(std::ostream& os, const statuscodes::Codes ec)
{
    switch (ec)
    {
    case statuscodes::EverythingOk:
        os << "EC: [Everything Ok]";
        break;
    case statuscodes::NotConnected:
        os << "EC: [Not Connected]";
        break;
    case statuscodes::MismatchingCommandAndReply:
        os << "EC: Provide the wrong reply container for command.";
        break;
    case statuscodes::FailedToPrepareSendingCommand:
        os << "EC: [Failed To Prepare Sending Command]";
        break;
    case statuscodes::SendingCommandFailed:
        os << "EC: [Sending Command Failed]";
        break;
    case statuscodes::ReplyMismatch:
        os << "EC: [Received the reply for another (unexpected) command]";
        break;
    case statuscodes::TimeOut:
        os << "EC: [TimeOut]";
        break;
    case statuscodes::TimeOutCriticalSection:
        os << "EC: [TimeOut Critical Section]";
        break;
    case statuscodes::ReceiveCommandErrorReply:
        os << "EC: [Received Command Error Reply]";
        break;
    case statuscodes::StreamerNotRegistered:
        os << "EC: [Streamer not registered]";
        break;
    case statuscodes::ListenerNotRegistered:
        os << "EC: [Listener not registered]";
        break;
    default:
        os << "EC: [<<Missing text for ec " << int(ec) << ">>]";
        break;
    }
    return os;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

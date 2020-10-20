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
//!\date Apr 7, 2015
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/EventMonitor.hpp>
#include <ibeo/common/sdk/datablocks/commands/Command2010.hpp>
#include <ibeo/common/sdk/datablocks/commands/Command.hpp>
#include <ibeo/common/sdk/datablocks/SpecialExporterBase.hpp>
#include <ibeo/common/sdk/listener/DataContainerListener.hpp>
#include <ibeo/common/sdk/CommandId.hpp>
#include <ibeo/common/sdk/misc/StatusCodes.hpp>
#include <ibeo/common/logging/logging.hpp>

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/unordered_map.hpp>

#include <iostream>
#include <list>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class IbeoDataHeader;
class DataBlock;
class DataContainerBase;
class DataListenerBase;
class DataStreamer;
class ImporterBase;

//==============================================================================
//!\class IbeoDeviceBase
//!\brief Base class for all Ibeo devices.
//!\date Apr 07, 2015
//------------------------------------------------------------------------------
class IbeoDeviceBase : private boost::noncopyable
{
protected:
    enum class ThreadState : uint8_t
    {
        NotRunning  = 0,
        Starting    = 1,
        Running     = 2,
        Stopping    = 3,
        StartFailed = 4,
        RunFailed   = 5
    }; // ThreadState

    //========================================
    //!\brief Type of mutex guard.
    //-------------------------------------
    using Lock = boost::mutex::scoped_lock;

    //========================================
    //!\brief Type of mutex.
    //-------------------------------------
    using Mutex = boost::mutex;

    //========================================
    //!\brief List of DataListenerBase (pointer).
    //-------------------------------------
    using ListenerList = std::list<DataListenerBase*>;

    //========================================
    //!\brief Each map entry is a pair of DataTypeId and
    //!       a list of listener.
    //-------------------------------------
    using ListenerListMap = boost::unordered_map<DataTypeId, ListenerList>;

    //========================================
    //!\brief List of DataContainerListenerBase (pointer).
    //-------------------------------------
    using ContainerListenerList = std::list<DataContainerListenerBase*>;

    //========================================
    //!\brief ContainerListenerListMap maps a pair of
    //!       DataTypeId/ContainerHash to a list of all
    //!       registered ContainerListener for this
    //!       combination.
    //----------------------------------------
    using ContainerListenerListMap = boost::unordered_map<std::pair<DataTypeId, size_t>, ContainerListenerList>;

    //========================================
    //!\brief RegisteredContainerListenerListMap maps a DataTypeId to all
    //!       registered ContainerListener for this data type.
    //----------------------------------------
    using RegisteredContainerListenerListMap = boost::unordered_map<DataTypeId, ContainerListenerListMap>;

    //========================================
    //!\brief List of DataStreamer (pointer).
    //-------------------------------------
    using StreamerList = std::list<DataStreamer*>;

public:
    IbeoDeviceBase();
    virtual ~IbeoDeviceBase();

public:
    //========================================
    //!\brief Establish the connection to the
    //!       hardware.
    //!
    //! Starting the receiving thread.
    //!\param [in] timeoutSec: Device timeout in seconds
    //-------------------------------------
    virtual void connect(const uint32_t timeoutSec) = 0;

    //========================================
    //!\brief Disconnect the connection
    //!       to the hardware device.
    //-------------------------------------
    virtual void disconnect();

    //========================================
    //!\brief Checks whether the TCP/IP connection to the hardware device is established and can receive data.
    //!
    //!\return \c true, if messages from the hardware can be received, \c false otherwise.
    //-------------------------------------
    virtual bool isConnected() const = 0;

    //========================================
    //!\brief Checks whether the thread for handling TCP/IP connections to the hardware is running.
    //!
    //!\return \c true, if the thread is running, \c false otherwise.
    //!
    //!\note This should not be mixed up with \a isConnected(). A device is running if the corresponding thread is
    //!      running, no matter if the connection to the hardware is established or not.
    //-------------------------------------
    virtual bool isRunning() const = 0;

    //========================================
    //!\brief Register a DataListener to this device.
    //!
    //! Each time a message has been received by
    //! this object, the registered listener will be
    //! called which are listening to the received message
    //! type (DataType).
    //!\param[in] listener  Listener to be registered.
    //!\note There is (currently) no way to unregister a
    //!      listener, so a registered DataListener must
    //!      not be destroyed before this IbeoDevice
    //!      has been destroyed.
    //!\warning the methodology of this method have changed
    //!         the user do not need to register DataListeners for
    //!         each DataType invidually
    //-------------------------------------
    virtual void registerListener(DataListenerBase* const listener);

    virtual void registerContainerListener(DataContainerListenerBase* const containerlistener);

    //========================================
    //!\brief Unregister a listener.
    //!\param[in] listener  Address of the listener object to
    //!                     be unregistered.
    //!\return Result of the operation.
    //-------------------------------------
    virtual statuscodes::Codes unregisterListener(DataListenerBase* const listener);

    virtual statuscodes::Codes unregisterListener(DataContainerListenerBase* const containerlistener);

    //========================================
    //!\brief Register a DataStreamer to this device.
    //!
    //! Each time a message has been received by the
    //! this object, the registered streamer will be
    //! call which are listening to the received message
    //! type (DataType).
    //!\param[in] streamer  Streamer to be registered.
    //!\note There is (currently) no way to unregister a
    //!      streamer, so a registered DataStreamer must
    //!      not be destroyed before this IbeoDevice
    //!      has been destroyed.
    //-------------------------------------
    virtual void registerStreamer(DataStreamer* const streamer);

    //========================================
    //!\brief Unregister a streamer.
    //!\param[in] streamer  Address of the streamer object to
    //!                     be unregistered.
    //!\return Result of the operation.
    //-------------------------------------
    virtual statuscodes::Codes unregisterStreamer(DataStreamer* const streamer);

protected:
    //========================================
    //!\brief Unregister all streamer and listener.
    //-------------------------------------
    void unregisterAll();

    //========================================
    //!\brief This method will be called by the receive thread
    //!       when a new DataBlock has been received completely.
    //!
    //! This class will call notifyListeners and notifyStreamers.
    //!
    //!\param[in]       dh  Header that came along with that
    //!                     DataBlock.
    //!\param[in, out]  is  Stream that contains the contents of
    //!                     the DataBlock that has been received.
    //-------------------------------------
    virtual const DataBlock* onData(const IbeoDataHeader& dh, std::istream& is) = 0;
    virtual const DataContainerBase*
    onData(const IbeoDataHeader& dh, std::istream& is, const size_t containerHash, ImporterBase*& importer)
        = 0;
    //========================================
    //!\brief Send a command which expects no reply.
    //!\param[in] cmd  Command to be sent.
    //!\return The result of the operation.
    //-------------------------------------
    virtual statuscodes::Codes sendCommand(const CommandCBase& cmd, const SpecialExporterBase<CommandCBase>& exporter)
        = 0;

    //========================================
    //!\brief Send a command and wait for a reply.
    //!
    //! The command will be sent. The calling thread
    //! will sleep until a reply has been received
    //! but not longer than the number of milliseconds
    //! given in \a timeOut.
    //!
    //!\param[in]       cmd    Command to be sent.
    //!\param[in, out]  reply  The reply container for
    //!                        the reply to be stored into.
    //!\param[in]       timeOut  Number of milliseconds to
    //!                          wait for a reply.
    //!\return The result of the operation.
    //-------------------------------------
    virtual statuscodes::Codes sendCommand(const CommandCBase& cmd,
                                           const SpecialExporterBase<CommandCBase>& exporter,
                                           CommandReplyBase& reply,
                                           const boost::posix_time::time_duration timeOut
                                           = boost::posix_time::milliseconds(500))
        = 0;

    //========================================
    //!\brief Call all registered Listener listening to the
    //!       received type of DataBlock.
    //!\param[in] data  DataBlock that has been received.
    //-------------------------------------
    virtual void notifyListeners(const DataBlock* const data);
    virtual void notifyContainerListeners(const DataContainerBase* const dataContainer,
                                          const ImporterBase* const importer);

    //========================================
    //!\brief Call all registered Streamers listening to the
    //!       received type of DataBlock.
    //!\param[in] dh       Header that came along with that
    //!                    DataBlock.
    //!\param[in] bodyBuf  Buffer that contains the
    //!                    (still serialized) body of
    //!                    the received DataBlock.
    //-------------------------------------
    virtual void notifyStreamers(const IbeoDataHeader& dh, const char* const bodyBuf);

    //========================================
    //!\brief Deserialize a received DataBlock into \a db.
    //!\param[in] is  Stream that contains the body of the
    //!               DataBlock.
    //!\param[in] db  The DataBlock object the received data
    //!               will be deserialized into.
    //!\param[in] dh  IbeoDataHeader that came along with
    //!               the DataBlock.
    //-------------------------------------
    virtual const DataBlock* deserialize(std::istream& is, DataBlock& db, const IbeoDataHeader& dh);

    //========================================
    //!\brief Add all registered container listeners to the list.
    //!
    //!\param[in] dataType     The data type to look for in the registered container listener map.
    //!\param[in] containerHash  The container hash to look for in the registered container listener map.
    //!\param[in/out] containerListeners  Vector with listener where the found entries will be added to.
    //!
    //! The dataType should either be the data type from the received data block to add all listeners registered for
    //! this specific data type or DataTypeId::DataType_Unknown for the general container listeners that have not
    //! specified a data type during registration.
    //----------------------------------------
    void addContainerListeners(const DataTypeId dataType,
                               const DataContainerListenerBase::HashId containerHash,
                               std::vector<DataContainerListenerBase*>& containerListeners) const;

protected:
    //========================================
    //!\brief ID of the logger for references in logging configurations.
    //-------------------------------------
    static constexpr const char* loggerId = "ibeo::common::sdk::IbeoDeviceBase";

protected:
    //========================================
    //!\brief Map that holds all container listener that are registered.
    //!
    //! Holds for each DataTypeId for which listener have
    //! been registered a list of those listener.
    //-------------------------------------
    RegisteredContainerListenerListMap m_registeredContainerListeners;

    //========================================
    //!\brief Map that holds all listener that are registered.
    //!
    //! Holds for each DataTypeId for which listener have
    //! been registered a list of those listener.
    //-------------------------------------
    ListenerListMap m_listeners;

    //========================================
    //!\brief The list of registered streamer.
    //-------------------------------------
    StreamerList m_streamers;

    //========================================
    //!\brief Logger.
    //!
    //! Provides logging facilities for this and all derived classes.
    //-------------------------------------
    ibeo::common::logging::LoggerSPtr m_logger{ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

    //========================================
    //!\brief Mutex protecting the listener and streamer lists.
    //-------------------------------------
    mutable Mutex m_listenersStreamersMutex;

}; // IbeoDeviceBase

//==============================================================================

std::ostream& operator<<(std::ostream& os, const statuscodes::Codes ec);

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

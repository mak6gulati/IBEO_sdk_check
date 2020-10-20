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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/DataBlockBufferProvider.hpp>
#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130.hpp>
#include <ibeo/common/sdk/devices/IdcFileController.hpp>
#include <ibeo/common/sdk/devices/IbeoDevice.hpp>
#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/listener/DataStreamer.hpp>
#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/listener/DataContainerListener.hpp>

#include <ibeo/common/sdk/misc/deprecatedwarning.hpp>
#include <ibeo/common/sdk/misc/StatusCodes.hpp>

#include <ibeo/common/logging/logging.hpp>

#include <boost/utility.hpp>

#include <fstream>
#include <list>
#include <memory>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class DataBlock;
class IdcFileController;

//==============================================================================
//!\brief Class to handle the access to an file in ibeo data container (IDC)
//!       format.
//!\date Sep 4, 2013
//!
//! This class works almost like an IbeoDevice. The main difference is, that
//! there is no external timing as given in an ethernet device like the IbeoLux
//! or IbeoEcu device. Hence receiving data is a pulling of data with
//! getNextDataContainer, getNextDataBlockRaw and getNextDataBlock (deprecated)
//! and issuing them with notifyContainerListeners, notifyStreamers or
//! notifyListeners (deprecated) manually.
//------------------------------------------------------------------------------
class IdcFile : boost::noncopyable
{
public:
    //========================================
    //!\brief A vector of DataContainer-Importer pairs.
    //----------------------------------------
    using ContainerImporterPairs = std::vector<std::pair<DataContainerBase*, ImporterBase*>>;

private:
    //========================================
    //!\brief Class needed to be able to read and deserialize
    //!       a FrameIndex6130 from an exisiting IDC file
    //!       while opening the file.
    //!
    //! A listener is needed to be registered since the filter
    //! listener registration serves as filter to avoid unnecessary
    //! work.
    //----------------------------------------
    class FrameIndexListener : public DataContainerListener<FrameIndex6130, DataTypeId::DataType_FrameIndex6130>
    {
    public:
        //========================================
        //!\brief Dummy implementation of the onData
        //!       method for FrameIndex6130.
        //----------------------------------------
        void onData(const FrameIndex6130&) override {}
    }; // FrameIndexListener

protected:
    //========================================
    //!\brief List of DataListenerBase (pointer).
    //----------------------------------------
    using ListenerList = std::list<DataListenerBase*>;

    //========================================
    //!\brief Each map entry is a pair of DataTypeId and
    //!       a list of listener.
    //----------------------------------------
    using ListenerListMap = boost::unordered_map<DataTypeId, ListenerList>;

    //========================================
    //!\brief List of DataContainerListenerBase (pointer).
    //----------------------------------------
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
    //----------------------------------------
    using StreamerList = std::list<DataStreamer*>;

public:
    //========================================
    //!\brief Default constructor.
    //----------------------------------------
    IdcFile();

    //========================================
    //!\brief Destructor.
    //!
    //! Closes the file on destruction.
    //----------------------------------------
    virtual ~IdcFile();

public:
    //========================================
    //!\brief Open a file for read access.
    //!\param[in] filename        Name of the file to be opened.
    //!\param[in] readFrameIndex  If \c true the frame index will
    //!                           be loaded from the end of the file
    //!                           if existing. open fails if no frame index
    //!                           has be found.
    //!\return \c true if the file was successfully
    //!        opened. \c false otherwise.
    //----------------------------------------
    virtual bool open(const std::string& filename, const bool readFrameIndex = true);

    //========================================
    //!\brief Create/Open a file for write access.
    //!\param[in] filename  Create a new (write-only) IDC file.
    //!\param[in] append    If \c false a new/empty IDC file will be created,
    //!                     if \c true an already existing IDC file will be
    //!                     appended.
    //!\return \c true if the file was successfully
    //!        opened/created. \c false otherwise.
    //!\todo In append mode the FrameIndex is not necessarily empty after
    //!      opening the file. The FrameIndex has to be generated.
    //!\attention The append mode is not recommended. This could lead to
    //!           multiple occurances of FrameIndex and IdcTrailer data types
    //!           in the file and the file has to be repaired before it can
    //!           be used with other tools correctly.
    //----------------------------------------
    virtual bool create(const std::string& filename, const bool append = false);

public:
    //========================================
    //!\brief Create a IdcFileController for
    //!       this file
    //!\return A unique_ptr to the create
    //!        IdcFileController.
    //----------------------------------------
    std::unique_ptr<IdcFileController> createController();

public:
    //========================================
    //!\brief Check whether the file is open.
    //!
    //!\return \c true if the file was successfully
    //!        opened/created. \c false otherwise.
    //----------------------------------------
    virtual bool isOpen();

    //========================================
    //!\brief Check whether the eofbit is set.
    //!\return \c true if the eofbit is set.
    //!        \c false otherwise.
    //----------------------------------------
    virtual bool isEof();

    //========================================
    //!\brief Check whether no error bit is set.
    //! \return \c true if the not error bit is set.
    //!         \c false otherwise.
    //----------------------------------------
    virtual bool isGood();

    //========================================
    //!\brief Closes an IdcFile.
    //!
    //! Is this IdcFile an output file, this method
    //! will write an FrameIndex6130 and a IdcTrailer6120 to
    //! the file. After that it will close the
    //! underlying stream.
    //----------------------------------------
    virtual void close();

    //========================================
    //!\brief Get the current stream read position.
    //!\return current position in stream.
    //----------------------------------------
    int64_t getPos();

    //========================================
    //!\brief Get the start stream read position.
    //!\return Start position in stream.
    //----------------------------------------
    int64_t getStartPos() { return m_posBeg; }

    //========================================
    //!\brief Write a DataBlock and its IbeoDataHeader
    //!        to this file.
    //!
    //! \param[in] dh    IbeoDataHeader for the
    //!                  serialized DataBlock in
    //!                  \a body.
    //! \param[in] body  Serialized version of
    //!                  the DataBlock to be
    //!                  written to the IdcFile.
    //!\return \c true if the write operation was successful.
    //!        \c false if no file is open or the serialization of
    //!        \a dh or writing the \a body failed.
    //----------------------------------------
    virtual bool write(const IbeoDataHeader& dh, const char* const body);

    //========================================
    //!\brief Write a DataBlock and its IbeoDataHeader
    //!       to this file.
    //!
    //!\param[in] dh  IbeoDataHeader for the
    //!               serialized DataBlock in
    //!               \a db.
    //!\param[in] db  DataBlock to be written
    //!               to the IdcFile.
    //!\return \c true if the write operation was successful.
    //!        \c false if no file is open or the serialization of
    //!        \a dh or \a db failed.
    //----------------------------------------
    virtual bool write(const IbeoDataHeader& dh, const DataBlock* const db);

    //========================================
    //!\brief Write a DataContainer with help of an exporter
    //!       to this file.
    //!
    //!\param[in] dh        IbeoDataHeader for container
    //!                     to be serialized. DataType and
    //!                     serialized size will be calculated
    //!                     here.
    //!\param[in] c         DataContainer to be written
    //!                     to the IdcFile.
    //!\param[in] exporter  Exporter to be used to
    //!                     serialize the container.
    //!\return \c true if the write operation was successful.
    //!        \c false if no file is open or the serialization of
    //!        \a dh or \a c failed.
    //----------------------------------------
    virtual bool write(IbeoDataHeader dh, const DataContainerBase& c, const ExporterBase& exporter);

    //========================================
    //!\brief Reads and returns the next DataBlock
    //!       from the file.
    //!\return Pointer to the read DataBlock.
    //!        nullptr if reading the next DataBlock has
    //!        failed.
    //----------------------------------------
    const DataBlock* getNextDataBlock();

    //========================================
    //!\brief Reads and returns the next DataContainer
    //!       from the file.
    //!
    //! There may be more than one Importer registered
    //! for a data type. Hence the data will be
    //! deserialized multiple times, depending on the
    //! number of available importer.
    //!
    //! Each Importer will fill a DataContainer.
    //! Hence the outcome is a vector of DataContainer and
    //! the Importer used to fill them.
    //!
    //!\return A vector of pairs of pointer to the
    //!        filled DataContainers and the Importer
    //!        used to fill them.
    //!        The vector is empty if no importer
    //!        has been registered for the data type,
    //!        the file is not open or reading the
    //!        IbeoDataHeader has failed.
    //----------------------------------------
    ContainerImporterPairs getNextDataContainer();

    //========================================
    //!\brief Read the next Datablock from the file.
    //!
    //! Only the header will be deserialized while the
    //! body will be read in file order.
    //!
    //! The buffer to hold the data will be allocated.
    //! A copy of the data from the file stream will be
    //! performed.
    //!\param[out] dh  IbeoDataHeader of the received
    //!                message.
    //!
    //!\return The contents of the datablock in raw
    //!        file order.
    //----------------------------------------
    std::shared_ptr<char> getNextDataBlockRaw(IbeoDataHeader& dh);

public:
    //========================================
    //!\brief Return the open mode the file has
    //!       been opened with.
    //!\return The open mode.
    //----------------------------------------
    std::ios_base::openmode getOpenMode() const { return m_openMode; }

    //========================================
    //!\brief Return the frame index.
    //!\return The frame index.
    //----------------------------------------
    const FrameIndex6130& getFrameIndex() const { return m_frameIndex; }

public: // same interface as in IbeoDeviceBase
    //========================================
    //!\brief Register the given \a listener.
    //!\param[in] listener  The DataListener to be registered.
    //----------------------------------------
    void registerListener(DataListenerBase* const listener);

    //========================================
    //!\brief Register the given \a containerListener.
    //!\param[in] containerListener  The DataContainerlistener to be registered.
    //----------------------------------------
    void registerContainerListener(DataContainerListenerBase* const containerListener);

    //========================================
    //!\brief Unregister a listener.
    //!\param[in] listener  Address of the listener object to
    //!                     be unregistered.
    //!\return Result of the operation.
    //----------------------------------------
    statuscodes::Codes unregisterListener(DataListenerBase* const listener);

    //========================================
    //!\brief Unregister a container listener.
    //!\param[in] containerListener  Address of the containerListener
    //!                              object to be unregistered.
    //!\return Result of the operation.
    //----------------------------------------
    statuscodes::Codes unregisterContainerListener(DataContainerListenerBase* const containerListener);

    //========================================
    //!\brief Register a DataStreamer to this device.
    //!
    //! Each time a message has been received by the
    //! this object, the registered streamer will be
    //! call which are registered.
    //!\param[in] streamer  Streamer to be registered.
    //!\note There is (currently) no way to unregister a
    //!      streamer, so a registered DataStreamer must
    //!      not be destroyed before this IbeoDevice
    //!      has been destroyed.
    //!\sa IbeoDeviceBase::registerStreamer
    //----------------------------------------
    void registerStreamer(DataStreamer* const streamer);

    //========================================
    //!\brief Unregister a streamer.
    //!\param[in] streamer  Address of the streamer object to
    //!                     be unregistered.
    //!\return Result of the operation.
    //----------------------------------------
    statuscodes::Codes unregisterStreamer(DataStreamer* const streamer);

public:
    //========================================
    //!\brief Call all registered Listener listening to the
    //!       received type of DataBlock.
    //!\param[in] data  DataBlock that has been received.
    //!\sa IbeoDeviceBase::notifyListeners
    //----------------------------------------
    void notifyListeners(const DataBlock* const data);

    //========================================
    //!\brief Call all registered ContainerListener listening to the
    //!       combination of DataContainer and Importer.
    //!\param[in] dataContainer  DataContainer that has been received.
    //!\param[in] importer       Importer used to deserialize the data
    //!                          and fill the DataContainer.
    //!\sa IbeoDeviceBase::notifyContainerListeners
    //----------------------------------------
    void notifyContainerListeners(const DataContainerBase* const dataContainer, const ImporterBase* const importer);

    //========================================
    //!\brief Call all registered ContainerListener listening to the
    //!       combination of DataContainer and Importer for all pairs
    //!       in the given vector.
    //!\param[in] containerImporterPairs  Vector of pairs of
    //!                                   DataContainers and Importers.
    //!\sa IbeoDeviceBase::notifyContainerListeners
    //----------------------------------------
    void notifyContainerListeners(const ContainerImporterPairs& containerImporterPairs);

    //========================================
    //!\brief Call all registered Streamers listening to the
    //!       received type of DataBlock.
    //!\param[in] dh       Header that came along with that
    //!                    DataBlock.
    //!\param[in] bodyBuf  Buffer that contains the
    //!                    (still serialized) body of
    //!                    the received DataBlock.
    //!\sa IbeoDeviceBase::notifyStreamers
    //----------------------------------------
    void notifyStreamers(const IbeoDataHeader& dh, const std::shared_ptr<char> bodyBuf);

public:
    //========================================
    //!\brief Return the list of registered DataContainer, i.e. a list of the pairs
    //!       of DataTypeId and the DataContainer's hash.
    //----------------------------------------
    std::list<ImporterBase::ImporterRegisterId::Key> getIdsOfSupportedDataContainer() const;

    //========================================
    //!\brief Return the list of registered DataBlock, i.e. a list of DataTypeId.
    //----------------------------------------
    std::list<DataBlock::DataBlockRegisterId::Key> getIdsOfSupportedDataBlocks() const;

protected:
    //========================================
    //!\brief Deserialize a received DataBlock into \a db.
    //!\param[in,out] is  Stream that contains the body of the
    //!                   DataBlock.
    //!\param[out]    db  The DataBlock object the received data
    //!                   will be deserialized into.
    //!\param[in]     dh  IbeoDataHeader that came along with
    //!                   the DataBlock.
    //!\return A pointer to the deserialized DataBlock. If an error
    //!        occurred, this pointer will be a nullptr.
    //!\sa IbeoDeviceBase::deserialize
    //----------------------------------------
    const DataBlock* deserialize(std::istream& is, DataBlock& db, const IbeoDataHeader& dh);

    //========================================
    //!\brief Unregister all streamer and listener.
    //----------------------------------------
    void unregisterAll();

    //========================================
    //!\brief Load the frame index of an existing IDC file.
    //!\return \c true if the FrameIndex6130 has
    //!        successfully been read. \c false otherwise.
    //----------------------------------------
    bool loadFrameIndex();

private:
    //========================================
    //!\brief Serialize the given IbeoDataHeder to the
    //!       internal stream.
    //!
    //! Before serializing \a dh, the frame index will
    //! be updated if necessary and the first header
    //! timestamp will be set if not yet done.
    //!
    //!\param[in] dh  IbeoDataHeader to be serialized.
    //!\return \c false if an error occurred serializing
    //!        \a dh, \c true otherwise.
    //----------------------------------------
    virtual bool writeHeader(IbeoDataHeader dh);

    //========================================
    //!\brief Write the \a length bytes starting at
    //!       \a data to the internal stream.
    //!\param[in] data    byte array to be written to
    //!                   to the stream.
    //!\param[in] length  Number of bytes to be
    //!                   written.
    //!\return \c true if writing the data was
    //!        successful, \c false otherwise.
    //----------------------------------------
    virtual bool write(const char* const data, const uint32_t length);

    //========================================
    //!\brief Add all registered container listeners to the list of container/importer pairs.
    //!
    //!\param[in] dataType     The data type to look for in the registered container listener map.
    //!\param[in/out] bodyBuf  Buffer containing the received data block without the header.
    //!\param[in/out] pairs    List with container/importer pairs where the found entries will be added to.
    //!
    //! The dataType should either be the data type from the received data block to add all listeners registered for
    //! this specific data type or DataTypeId::DataType_Unknown for the general container listeners that have not
    //! specified a data type during registration.
    //! If the bodyBuf is null, the received message is copied from the stream into this buffer, before the importer is
    //! called. Otherwise, the buffer is used directly for importing the data container. This ensures that the stream
    //! is read only once and only if a container/importer pair is found.
    //----------------------------------------
    void addDataContainerImporterPairsToVector(const DataTypeId dataType,
                                               std::vector<char> bodyBuf,
                                               ContainerImporterPairs& pairs);

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
    void addDataContainerListenersToVector(const DataTypeId dataType,
                                           const uint64_t containerHash,
                                           std::vector<DataContainerListenerBase*>& containerListeners) const;

protected:
    static constexpr const char* loggerId = "ibeo::common::sdk::IdcFile";
    static ibeo::common::logging::LoggerSPtr logger;

protected:
    //========================================
    //!\brief Map that holds all container listener that are registered.
    //!
    //!Holds for each DataTypeId for which listener have
    //!been registered a list of those listener.
    //----------------------------------------
    RegisteredContainerListenerListMap m_registeredContainerListeners{};

    //========================================
    //!\brief Map that holds all listener that are registered.
    //!
    //! Holds for each DataTypeId for which listener have
    //! been registered a list of those listener.
    //----------------------------------------
    ListenerListMap m_listeners{};

    //========================================
    //!\brief The list of registered streamer.
    //----------------------------------------
    StreamerList m_streamers;

    //========================================
    //!\brief The mode the file has been opened with.
    //!
    //! If no file has been opened yet, m_openMode is 0.
    //----------------------------------------
    std::ios_base::openmode m_openMode{std::ios_base::openmode(0)};

    //========================================
    //!\brief The FrameIndex6130 of the currently open file.
    //!
    //! If the file is read-only, this is the frame index
    //! read from the file.
    //!
    //! If the file is write-only, this is the frame index
    //! which will be filled while writing into the file.
    //!
    //!\attention m_frameIndex is only valid if a file is currently open.
    //----------------------------------------
    FrameIndex6130 m_frameIndex{};

    //========================================
    //!\brief Holds map from a pair of DataTypeId and DataContainer hash
    //!       to a triple of Importer create function and a pointer
    //!       to a created Importer and one to a created
    //!       DataContainer for the given pair of DataTypeId and DataContainer.
    //----------------------------------------
    ContainerBufferAndImporterProvider<IdcFile> m_cbaip;

    //========================================
    //!\brief Holds map from DataTypeId to a pair
    //!       of DataBlock create function and a pointer
    //!       to a created DataBlock for the given
    //!       DataTypeId.
    //----------------------------------------
    DataBlockBufferProvider<IdcFile> m_dbbp;

private:
    //========================================
    //!\brief File stream for io access to the file.
    //----------------------------------------
    int64_t m_posBeg{-1};

    //========================================
    //!\brief Internal stream, the IDC file.
    //----------------------------------------
    std::fstream m_strm{};

    //========================================
    //!\brief The name of an open file.
    //----------------------------------------
    std::string m_filename{}; //idc filename (only valid for opened file)

    //========================================
    //!\brief The size of the last messages that
    //!       has been written. (Only for writing
    //!       an IDC file).
    //----------------------------------------
    uint32_t m_latestMsgSize{0};

    //========================================
    //!\brief The time stamp of the last header
    //!       written. (Only for writing
    //!       an IDC file).
    //----------------------------------------
    NTPTime m_latestHeaderTimestamp{};

    //========================================
    //!\brief The time stamp of the first header
    //!       written. (Only for writing
    //!       an IDC file).
    //----------------------------------------
    NTPTime m_firstHeaderTimestamp{};

    //========================================
    //!\brief Variable to hold the deserialization
    //!       of a IbeoDataHeader.
    //----------------------------------------
    IbeoDataHeader m_dh{};

    //========================================
    //!\brief Tells, whether yet a DataBlock has
    //!       been written into the file.
    //!       (Only for writing an IDC file).
    //----------------------------------------
    bool m_firstDataBlockToBeWritten{false};
}; // IdcFile

//==============================================================================

template<>
ContainerBufferAndImporterProviderGlobal<IdcFile>& getImporterCreatorMap<IdcFile>();

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Jan 10, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>

#include <ibeo/common/sdk/DataTypeId.hpp>

#include <boost/unordered_map.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
//!\class DataContainerListenerBase
//!\brief Abstract base class for all listener.
//!
//! A DataContainerListener can be registered to an IbeoDevice to receive
//! all DataBlock of the associated DataType received by that
//! device.
//!
//! Derived classes will have to implement an onData method for the
//! associated DataType. This onData method will be called in the
//! context of the receive thread of that device.
//!
//! The data received by the onData method will be deserialized.
//!
//! In case one is not interested in the contents of that DataBlock
//! it may be better to implement a DataStreamer.
//!
//!\sa DataStreamer
//------------------------------------------------------------------------------
class DataContainerListenerBase
{
public:
    //========================================
    //! \brief Destrutor does nothing special.
    //-------------------------------------
    virtual ~DataContainerListenerBase() {}

public:
    using HashId           = uint64_t;
    using DataTypeHashPair = std::pair<DataTypeId, HashId>;
    using DataTypes        = std::vector<DataTypeHashPair>;

    //========================================
    //! \brief Get the DataTypes for which this
    //!        listener is listening.
    //! \return The DataTypes the listener is
    //!         listening for.
    //-------------------------------------
    const DataTypes& getAssociatedDataTypes() const { return m_registeredDataTypes; }

protected:
    void registerDataType(const DataTypeId type, const HashId hash)
    {
        const auto newEntry = std::make_pair(type, hash);

        if (std::find(m_registeredDataTypes.begin(), m_registeredDataTypes.end(), newEntry)
            == m_registeredDataTypes.end())
        {
            m_registeredDataTypes.push_back(newEntry);
        }
    }

    void registerDataType(const HashId hash)
    {
        // Register the container with the generic data type.
        registerDataType(DataTypeId::DataType_Unknown, hash);
    }

private:
    DataTypes m_registeredDataTypes;
}; // DataContainerListenerBase

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================
//!\class DataContainerListener
//!\brief Abstract base class for all DataListener listen on DataBlockImpl.
//!
//!\tparam DataContainerImpl  DataContainer implementation.
//!\tparam dataType           Data type.
//------------------------------------------------------------------------------
template<class DataContainerImpl, uint16_t dataType>
class DataContainerListener : public virtual DataContainerListenerBase
{
public:
    //========================================
    //!\brief Constructor registers at DataListenerBase class
    //----------------------------------------
    DataContainerListener() { registerDataType(DataTypeId(dataType), DataContainerImpl::getClassIdHashStatic()); }

    //========================================
    //!\brief Called on receiving a new DataContainerImpl DataBlock.
    //!
    //!Method to be called by the IbeoDevice where this listener
    //!is registered when a new DataBlock of type DataBlockImpl
    //!has been received.
    //!
    //!\param[in] dcImpl  Pointer to the DataContainerImpl that has
    //!                   been received.
    //----------------------------------------
    virtual void onData(const DataContainerImpl& dcImpl) = 0;

}; // DataContainerListener

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

//==============================================================================
//!\class GeneralDataContainerListener
//!\brief Abstract base class for all DataListener listen on DataBlockImpl.
//!
//!\tparam DataContainerImpl  DataContainer implementation.
//------------------------------------------------------------------------------
template<class DataContainerImpl>
class GeneralDataContainerListener : public virtual DataContainerListenerBase
{
public:
    //========================================
    //!\brief Constructor registers at DataListenerBase class
    //----------------------------------------
    GeneralDataContainerListener() { registerDataType(DataContainerImpl::getClassIdHashStatic()); }

    //========================================
    //!\brief Called on receiving a new DataContainerImpl DataBlock.
    //!
    //!Method to be called by the IbeoDevice where this listener
    //!is registered when a new DataBlock of type DataBlockImpl
    //!has been received.
    //!
    //!\param[in] dcImpl  Pointer to the DataContainerImpl that has
    //!                   been received.
    //----------------------------------------
    virtual void onData(const DataContainerImpl& dcImpl) = 0;

}; // GeneralDataContainerListener

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================
//!\brief Abstract template set of base classes for all special listener.
//!\tparam DataContainerImpl  The DataContainer that will be read in case the
//!                           datatype has been received which contains the
//!                           special sub datatype which can be distinguished
//!                           using the value of \a KeyType.
//!\tparam KeyTpye            Type of the key variable used to distinguish between
//!                           between different special sub datatypes.
//------------------------------------------------------------------------------
template<class DataContainerImpl, typename KeyType>
class SpecialListenerBase
{
public:
    using HashId    = uint64_t;
    using KeyVector = std::vector<std::pair<KeyType, HashId>>;
    using KeyMap    = boost::unordered_map<KeyType, KeyVector>;

    //========================================
    //!\brief Get the DataTypes for which this
    //!       listener is listening.
    //!\return The DataTypes the listener is
    //!        listening for.
    //----------------------------------------
    const KeyMap& getRegisteredSubTypes() const { return m_registeredSubTypes; }

protected:
    void registerKey(const KeyType subId, const HashId hash)
    {
        const auto newEntry = std::make_pair(subId, hash);
        std::cerr << "Register: " << subId << std::endl;

        KeyVector& kv = m_registeredSubTypes[subId];

        if (std::find(kv.begin(), kv.end(), newEntry) == kv.end())
        {
            std::cerr << "Register added: (" << newEntry.first << ", " << newEntry.second << ")" << std::endl;
            kv.push_back(newEntry);
        }

        std::cerr << "m_registeredSubTypes: ";
        for (auto r : kv)
        {
            std::cerr << "(" << r.first << ", " << r.second << ")  ";
        }
        std::cerr << std::endl;
    }

private:
    KeyMap m_registeredSubTypes;
}; // SpecialListenerBase

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================
//!\class DataContainerSpecialListener
//!\brief Abstract base class for all DataListener listen on DataBlockImpl.
//!\date Feb 10, 2014
//!
//!\tparam DataContainerImpl  DataContainer implementation.
//!\tparam dataType           Data type.
//!\tparam SpecialType        Sub-type in data container.
//------------------------------------------------------------------------------
template<class DataContainerImpl, uint16_t dataType, class SpecialType>
class DataContainerSpecialListener
  : public virtual DataContainerListenerBase,
    public virtual SpecialListenerBase<DataContainerImpl, typename SpecialType::KeyType>
{
public:
    //========================================
    //!\brief Constructor registers at DataListenerBase class
    //----------------------------------------
    DataContainerSpecialListener() : SpecialListenerBase<DataContainerImpl, typename SpecialType::KeyType>()
    {
        registerDataType(DataTypeId(dataType), DataContainerImpl::getClassIdHashStatic());
        this->registerKey(SpecialType::key, SpecialType::getClassIdHashStatic()); // gcc needs this pointer here.
    }

    //========================================
    //!\brief Called on receiving a new DataContainerImpl DataBlock.
    //!
    //!Method to be called by the IbeoDevice where this listener
    //!is registered when a new DataBlock of type DataBlockImpl
    //!has been received.
    //!
    //!\param[in] dbImpl  Pointer to the DataBlockImpl that has
    //!                   been received.
    //----------------------------------------
    virtual void onData(const SpecialType* const stImpl) = 0;
}; // DataContainerSpecialListener

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

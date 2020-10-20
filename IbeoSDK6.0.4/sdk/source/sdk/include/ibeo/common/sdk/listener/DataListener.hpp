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
//! \date Apr 30, 2012
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/DataTypeId.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//! \class DataListenerBase
//! \brief Abstract base class for all listener.
//! \date Apr 39, 2012
//!
//! A DataListener can be registered to an IbeoDevice to receive
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
//! \sa DataStreamer
//------------------------------------------------------------------------------
class DataListenerBase
{
public:
    //========================================
    //! \brief Destrutor does nothing special.
    //-------------------------------------
    virtual ~DataListenerBase() {}

public:
    using DataTypes = std::vector<DataTypeId>;
    //========================================
    //! \brief Get the DataTypes for which this
    //!        listener is listening.
    //! \return The DataTypes the listener is
    //!         listening for.
    //-------------------------------------
    const DataTypes& getAssociatedDataTypes() const { return m_registeredDataTypes; }

protected:
    void registerDataType(const DataTypeId type) { m_registeredDataTypes.push_back(type); }

private:
    DataTypes m_registeredDataTypes;
}; // DataListenerBase

//==============================================================================

//==============================================================================
//! \class DataListener
//! \brief Abstract base class for all DataListener listen on DataBlockImpl.
//! \date Feb 10, 2014
//!
//! \tparam DataBlockImpl  DataBlock implementation.
//------------------------------------------------------------------------------
template<class DataBlockImpl>
class DataListener : public virtual DataListenerBase
{
public:
    //========================================
    //! \brief Constructor registers at DataListenerBase class
    //-------------------------------------

    DataListener() { registerDataType(DataBlockImpl::getDataBlockId()); }

    //========================================
    //! \brief Called on receiving a new DataBlockImpl DataBlock.
    //!
    //! Method to be called by the IbeoDevice where this listener
    //! is registered when a new DataBlock of type DataBlockImpl
    //! has been received.
    //!
    //! \param[in] dbImpl  Pointer to the DataBlockImpl that has
    //!                    been received.
    //-------------------------------------
    virtual void onData(const DataBlockImpl* const dbImpl) = 0;
}; // DataListener

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

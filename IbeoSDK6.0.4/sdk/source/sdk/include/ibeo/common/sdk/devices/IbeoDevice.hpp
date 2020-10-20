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
//!\date Apr 24, 2012
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/devices/IbeoEthDevice.hpp>
#include <ibeo/common/sdk/DataBlockBufferProvider.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//#ifdef _WIN32
//#include <ibeo/common/sdk/DataBlockRegister.hpp>
//#endif // _WIN32

#include <iostream>
#include <vector>
#include <list>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//!\class IbeoDevice
//! \brief
//! \date Jan 30, 2014
//! \tparam DeviceImpl   Implementation of the Device.
//------------------------------------------------------------------------------
template<class DeviceImpl>
class IbeoDevice : public IbeoEthDevice
{
public:
    //========================================
    //!\brief Create an IbeoDevice (general device class).
    //!
    //! This constructor will create an IbeoDevice class object
    //! given by the template class DeviceImpl.
    //----------------------------------------
    IbeoDevice();
    virtual ~IbeoDevice();

public:
    //========================================
    //!\brief This method will be called by the receive thread
    //!        when a new DataBlock has been received completely.
    //!
    //! This class will call notifyListeners and notifyStreamers.
    //!
    //! \param[in]       dh  Header that came along with that
    //!                      DataBlock.
    //! \param[in, out]  is  Stream that contains the contents of
    //!                      the DataBlock that has been received.
    //----------------------------------------
    virtual const DataBlock* onData(const IbeoDataHeader& dh, std::istream& is) override;

    //========================================
    virtual const DataContainerBase*
    onData(const IbeoDataHeader& dh, std::istream& is, const size_t containerHash, ImporterBase*& importer) override;

public:
    std::list<DataBlock::DataBlockRegisterId::Key> getIdsOfSupportedDataBlocks() const;

    std::list<ImporterBase::ImporterRegisterId::Key> getIdsOfSupportedDataContainer() const;

private:
    void startup();

protected:
    ContainerBufferAndImporterProvider<DeviceImpl> cbaip;
    DataBlockBufferProvider<DeviceImpl> dbbp;
}; // IbeoDevice

//==============================================================================

template<class D>
ContainerBufferAndImporterProviderGlobal<D>& getImporterCreatorMap();

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

#include <ibeo/common/sdk/devices/IbeoDevice.tpp>

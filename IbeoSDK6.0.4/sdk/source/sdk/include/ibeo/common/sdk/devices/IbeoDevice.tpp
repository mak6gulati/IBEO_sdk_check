//==============================================================================
//!\file IbeoDevice.hpp
//!
//!\copydoc Copyright
//!\author Jan Christian Dittmer (jcd)
//!\date Jan 11, 2018
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template <class DeviceImpl>
IbeoDevice<DeviceImpl>::IbeoDevice()
  : IbeoEthDevice(),
    cbaip(ContainerBufferAndImporterProviderGlobal<DeviceImpl>::getInstance()),
    dbbp(DataBlockBufferProviderGlobal<DeviceImpl>::getInstance())
{
	startup();
}

//==============================================================================

template <class DeviceImpl>
IbeoDevice<DeviceImpl>::~IbeoDevice() {}

//==============================================================================

template <class DeviceImpl>
const DataBlock* IbeoDevice<DeviceImpl>::onData(const IbeoDataHeader& dh, std::istream& is)
{
	if (dh.getDataType() == DataTypeId::DataType_Unknown)
	{
		LOGERROR(m_logger, "Received data block id unknown.");
		return NULL;
	}


	// this needs to be a loop over multimap equal_range(datatype)
	DataBlock* db1 = dbbp.getBuffer(dh.getDataType());
	if (db1)
	{
		if (const DataBlock* db = deserialize(is, *db1, dh))
			return db;
		else
			return nullptr;
	}

	LOGDEBUG(m_logger, "Ignoring unknown DataBlock "
	         << "0x" << std::hex << dh.getDataType() << std::dec
	         << " of size: " << dh.getMessageSize() << " bytes.");
	return nullptr;
}

//==============================================================================

template <class DeviceImpl>
const DataContainerBase* IbeoDevice<DeviceImpl>::onData(const IbeoDataHeader& dh,
                                                        std::istream& is,
                                                        const size_t containerHash,
                                                        ImporterBase*& importer)
{
	if (dh.getDataType() == DataTypeId::DataType_Unknown)
	{
		LOGERROR(m_logger, "Received data block id unknown.");
		return nullptr;
	}

	const ImporterBase::ImporterRegisterId::Key containerId = std::make_pair(dh.getDataType(), containerHash);

	importer = cbaip.getImporter(containerId);

	if (!importer)
	{
		LOGDEBUG(m_logger, "Ignoring unknown Importer "
		         << "0x" << std::hex << dh.getDataType() << std::dec
		         << " of size: " << dh.getMessageSize() << " bytes.");
		return nullptr;
	}


	DataContainerBase* container = cbaip.getBuffer(containerId);
	if (container)
	{
		if (importer->deserialize(is, *container, dh))
		{
			return container;
		}
		else
		{
			LOGWARNING(m_logger, "Failed to deserialize"
			           << "0x" << std::hex << dh.getDataType() << std::dec);
		}
	}

	return nullptr;
}
//==============================================================================

template <class DeviceImpl>
std::list<DataBlock::DataBlockRegisterId::Key>
IbeoDevice<DeviceImpl>::getIdsOfSupportedDataBlocks() const
{
	std::list<DataBlock::DataBlockRegisterId::Key> keyList;
#ifdef _WIN32
	typedef DataBlockBufferProvider<DeviceImpl>::ProviderMap PM;
	const PM& pm = dbbp.getMap();
	PM::const_iterator iter = pm.begin();
#else // _WIN32
	typedef typename DataBlockBufferProvider<DeviceImpl>::ProviderMap PM;
	const PM& pm = dbbp.getMap();
	typename PM::const_iterator iter = pm.begin();
#endif // _WIN32
	for (; iter != dbbp.getMap().end(); ++iter)
	{
		keyList.push_back(iter->first);
	} // for iter
	keyList.sort();
	return keyList;
}

//==============================================================================

template <class DeviceImpl>
std::list<ImporterBase::ImporterRegisterId::Key>
IbeoDevice<DeviceImpl>::getIdsOfSupportedDataContainer() const
{
	std::list<ImporterBase::ImporterRegisterId::Key> keyList;
#ifdef _WIN32
	typedef ContainerBufferAndImporterProvider<DeviceImpl>::ProviderMap PM;
	const PM& pm = cbaip.getMap();
	PM::const_iterator iter = pm.begin();
#else // _WIN32
	typedef typename ContainerBufferAndImporterProvider<DeviceImpl>::ProviderMap PM;
	const PM& pm = cbaip.getMap();
	typename PM::const_iterator iter = pm.begin();
#endif // _WIN32
	for (; iter != cbaip.getMap().end(); ++iter)
	{
		keyList.push_back(iter->first);
	} // for iter
	keyList.sort();
	return keyList;
}

//==============================================================================

template <class DeviceImpl>
void IbeoDevice<DeviceImpl>::startup()
{
	std::stringstream stream;
	stream  << std::endl << "Create Device:" << std::endl;

	stream << "Registered DataContainer: " << std::endl;
	std::list<ImporterBase::ImporterRegisterId::Key> dtList = getIdsOfSupportedDataContainer();
	std::list<ImporterBase::ImporterRegisterId::Key>::const_iterator iter = dtList.begin();
	for (; iter != dtList.end(); ++iter)
	{
		stream << std::hex << "0x" << iter->first << "  " << std::dec << iter->second << std::endl;
	}

	stream << "Registered DataTypes: " << std::endl;
	std::list<DataBlock::DataBlockRegisterId::Key> dtList2 = getIdsOfSupportedDataBlocks();
	std::list<DataBlock::DataBlockRegisterId::Key>::const_iterator iter2 = dtList2.begin();
	for (; iter2 != dtList2.end(); ++iter2)
	{
		stream << std::hex << "0x" << int(*iter2) << std::dec << std::endl;
	}

	LOGINFO(m_logger, stream.str())
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

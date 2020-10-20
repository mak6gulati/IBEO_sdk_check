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
//! \date Jan 29, 2014
//------------------------------------------------------------------------------
#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataBlock.hpp>

#include <ibeo/common/sdk/DataTypeId.hpp>

#include <boost/unordered_map.hpp>
#include <boost/function.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

template<class Device>
class DataBlockBufferProviderGlobal
{
public:
    using DataBlockRegisterId = DataBlock::DataBlockRegisterId;
    using GlobalProviderMap
        = boost::unordered_map<DataBlockRegisterId::Key, DataBlockRegisterId::DataBlockCreateFunction>;

private:
    DataBlockBufferProviderGlobal() : glProviderMap() {}
    ~DataBlockBufferProviderGlobal() {}

private:
    DataBlockBufferProviderGlobal(const DataBlockBufferProviderGlobal& other) = delete;
    DataBlockBufferProviderGlobal& operator=(const DataBlockBufferProviderGlobal& other) = delete;

public:
    static DataBlockBufferProviderGlobal<Device>& getInstance()
    {
        static DataBlockBufferProviderGlobal<Device> dbbp;
        return dbbp;
    }

public:
    const DataBlockRegisterId& registerDataBlock(const DataBlockRegisterId& dbri)
    {
        glProviderMap[dbri.getKey()] = dbri.getValue();
        return dbri;
    }

    const GlobalProviderMap& getMap() const { return glProviderMap; }

protected:
    GlobalProviderMap glProviderMap;
}; // DataBlockBufferProviderGlobal

//==============================================================================

template<class Device>
class DataBlockBufferProvider
{
public:
    //========================================
    class DataBlockBuffer
    {
    public:
        DataBlockBuffer() : m_buffer(nullptr), m_create() {}

        DataBlockBuffer(DataBlock::DataBlockRegisterId::DataBlockCreateFunction create)
          : m_buffer(nullptr), m_create(create)
        {}

        ~DataBlockBuffer() { delete m_buffer; }

    public:
        DataBlock* getBuffer()
        {
            if (!m_buffer && m_create)
                m_buffer = m_create();
            return m_buffer;
        }

        const DataBlock* getBufferPtr() const { return m_buffer; }
        DataBlock::DataBlockRegisterId::DataBlockCreateFunction getCreatePtr() const { return m_create; }

    protected:
        DataBlock* m_buffer;
        DataBlock::DataBlockRegisterId::DataBlockCreateFunction m_create;
        //DataBlock::DataBlockRegisterId::DataBlockCreateFunction m_createImporter;
    }; // DataBlockBuffer

    //========================================
    using ProviderMap = boost::unordered_map<DataBlock::DataBlockRegisterId::Key, DataBlockBuffer>;

public:
    DataBlockBufferProvider(DataBlockBufferProviderGlobal<Device>& globalProvider)
    {
        using GlobalMap            = typename DataBlockBufferProviderGlobal<Device>::GlobalProviderMap;
        const GlobalMap& globalMap = globalProvider.getMap();
        typename GlobalMap::const_iterator globalIter = globalMap.begin();
        for (; globalIter != globalMap.end(); ++globalIter)
        {
            providerMap[globalIter->first] = DataBlockBuffer(globalIter->second);
        } // for globalIter
    }

    ~DataBlockBufferProvider() {}

private:
    DataBlockBufferProvider(const DataBlockBufferProvider& other) = delete;
    DataBlockBufferProvider& operator=(const DataBlockBufferProvider& other) = delete;

public:
    DataBlock* getBuffer(const DataBlock::DataBlockRegisterId::Key dataTypeId)
    {
        typename ProviderMap::iterator iter = providerMap.find(dataTypeId);
        if (iter == providerMap.end())
            return nullptr;

        return iter->second.getBuffer();
    }

    const ProviderMap& getMap() const { return providerMap; }

protected:
    ProviderMap providerMap;
}; // DataBlockBufferProvider

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

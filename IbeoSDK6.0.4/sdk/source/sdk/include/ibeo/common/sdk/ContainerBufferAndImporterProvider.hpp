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
//! \date Sep 11, 2017
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/ImporterBase.hpp>
#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>

#include <ibeo/common/sdk/DataTypeId.hpp>

#include <boost/unordered_map.hpp>

#include <memory>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

template<class Device>
class ContainerBufferAndImporterProviderGlobal
{
public:
    using ImporterRegisterId     = ImporterBase::ImporterRegisterId;
    using ImporterCreateFunction = ImporterRegisterId::ImporterCreateFunction;

    using GlobalProviderMap = boost::unordered_map<ImporterRegisterId::Key, ImporterCreateFunction>;

private:
    ContainerBufferAndImporterProviderGlobal() : glProviderMap() {}
    ~ContainerBufferAndImporterProviderGlobal() {}

private:
    ContainerBufferAndImporterProviderGlobal(const ContainerBufferAndImporterProviderGlobal& other) = delete;
    ContainerBufferAndImporterProviderGlobal& operator=(const ContainerBufferAndImporterProviderGlobal& other) = delete;

public:
    static ContainerBufferAndImporterProviderGlobal<Device>& getInstance()
    {
        static ContainerBufferAndImporterProviderGlobal<Device> dbbp;
        return dbbp;
    }

public:
    const ImporterRegisterId& registerImporter(const ImporterRegisterId& dbri)
    {
        glProviderMap[dbri.getKey()] = dbri.getValue();
        return dbri;
    }

    const GlobalProviderMap& getMap() const { return glProviderMap; }

protected:
    GlobalProviderMap glProviderMap;
}; // ContainerBufferAndImporterProviderGlobal

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

template<class Device>
class ContainerBufferAndImporterProvider
{
public:
    class ContainerBufferAndImporter;

    using ImporterRegisterId = ImporterBase::ImporterRegisterId;
    using ProviderMap        = boost::unordered_map<ImporterRegisterId::Key, ContainerBufferAndImporter>;

public:
    ContainerBufferAndImporterProvider(ContainerBufferAndImporterProviderGlobal<Device>& globalProvider)
    {
        using GlobalMap            = typename ContainerBufferAndImporterProviderGlobal<Device>::GlobalProviderMap;
        const GlobalMap& globalMap = globalProvider.getMap();
        typename GlobalMap::const_iterator globalIter = globalMap.begin();
        for (; globalIter != globalMap.end(); ++globalIter)
        {
            providerMap[globalIter->first] = ContainerBufferAndImporter(globalIter->second);
        } // for globalIter
    }

    ContainerBufferAndImporterProvider(ContainerBufferAndImporterProviderGlobal<Device>& globalProvider,
                                       const size_t containerHash)
    {
        using GlobalMap            = typename ContainerBufferAndImporterProviderGlobal<Device>::GlobalProviderMap;
        const GlobalMap& globalMap = globalProvider.getMap();
        typename GlobalMap::const_iterator globalIter = globalMap.begin();
        for (; globalIter != globalMap.end(); ++globalIter)
        {
            if (globalIter->first.second == containerHash)
            {
                providerMap[globalIter->first] = ContainerBufferAndImporter(globalIter->second);
            }
        } // for globalIter
    }

    ~ContainerBufferAndImporterProvider() {}

private:
    ContainerBufferAndImporterProvider(const ContainerBufferAndImporterProvider& other) = delete;
    ContainerBufferAndImporterProvider& operator=(const ContainerBufferAndImporterProvider& other) = delete;

public:
    DataContainerBase* getBuffer(const ImporterRegisterId::Key dataTypeId)
    {
        typename ProviderMap::iterator iter = providerMap.find(dataTypeId);
        if (iter == providerMap.end())
            return NULL;

        return iter->second.getBuffer();
    }

    //========================================
    ImporterBase* getImporter(const ImporterRegisterId::Key dataTypeId)
    {
        typename ProviderMap::iterator iter = providerMap.find(dataTypeId);
        if (iter == providerMap.end())
            return NULL;

        return iter->second.getImporter();
    }

    const ProviderMap& getMap() const { return providerMap; }

protected:
    ProviderMap providerMap;
}; // ContainerBufferAndImporterProvider

//==============================================================================

template<class Device>
class ContainerBufferAndImporterProvider<Device>::ContainerBufferAndImporter
{
public:
    using ImporterCreateFunction = ImporterBase::ImporterRegisterId::ImporterCreateFunction;

public:
    ContainerBufferAndImporter() {}

    ContainerBufferAndImporter(ImporterCreateFunction createImporter) : m_createImporter(createImporter) {}

    ~ContainerBufferAndImporter() = default;

public:
    DataContainerBase* getBuffer()
    {
        if (!m_buffer && (getImporter()))
        {
            m_buffer.reset(m_importer->createContainer());
        }
        return m_buffer.get();
    }

    //========================================
    ImporterBase* getImporter()
    {
        if (!m_importer && m_createImporter)
        {
            m_importer.reset(m_createImporter());
        }
        return m_importer.get();
    }

    //	DataContainerBase* getBufferPtr() { return m_buffer.get(); }
    //	ImporterBase* getImporterPtr() { return m_importer.get(); }
    ImporterCreateFunction getCreateImporterPtr() const { return m_createImporter; }

protected:
    std::shared_ptr<DataContainerBase> m_buffer{};
    std::shared_ptr<ImporterBase> m_importer{};
    ImporterBase::ImporterRegisterId::ImporterCreateFunction m_createImporter;
}; // ContainerBufferAndImporter

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

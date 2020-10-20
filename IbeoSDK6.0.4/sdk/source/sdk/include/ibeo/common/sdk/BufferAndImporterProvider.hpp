//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Feb 13, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/SpecialImporterBase.hpp>

#include <boost/unordered_map.hpp>

#include <memory>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<typename Identifier>
class BufferAndImporterProviderGlobal
{
public:
    using KeyType                = typename Identifier::KeyType;
    using ImporterRegisterId     = typename SpecialImporterBase<typename Identifier::CommonBase>::ImporterRegisterId;
    using ImporterCreateFunction = typename ImporterRegisterId::ImporterCreateFunction;

    using GlobalProviderMap = boost::unordered_map<typename ImporterRegisterId::Key, ImporterCreateFunction>;

private:
    BufferAndImporterProviderGlobal() : m_glProviderMap() {}
    ~BufferAndImporterProviderGlobal() {}

private:
    BufferAndImporterProviderGlobal(const BufferAndImporterProviderGlobal& other) = delete;
    BufferAndImporterProviderGlobal& operator=(const BufferAndImporterProviderGlobal& other) = delete;

public:
    static BufferAndImporterProviderGlobal<Identifier>& getInstance()
    {
        static BufferAndImporterProviderGlobal<Identifier> dbbp;
        return dbbp;
    }

public:
    const ImporterRegisterId& registerImporter(const ImporterRegisterId& dbri)
    {
        m_glProviderMap[dbri.getKey()] = dbri.getValue();
        return dbri;
    }

    const GlobalProviderMap& getMap() const { return m_glProviderMap; }

protected:
    GlobalProviderMap m_glProviderMap;
}; // BufferAndImporterProviderGlobal

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

template<typename Identifier>
class BufferAndImporterProvider
{
public:
    using KeyType = typename Identifier::KeyType;

public:
    class BufferAndImporter;

    using ImporterRegisterId = typename SpecialImporterBase<Identifier>::ImporterRegisterId;
    using ProviderMap        = boost::unordered_map<typename ImporterRegisterId::Key, BufferAndImporter>;

public:
    BufferAndImporterProvider(BufferAndImporterProviderGlobal<Identifier>& globalProvider)
    {
        using GlobalMap            = typename BufferAndImporterProviderGlobal<Identifier>::GlobalProviderMap;
        const GlobalMap& globalMap = globalProvider.getMap();
        typename GlobalMap::const_iterator globalIter = globalMap.begin();
        for (; globalIter != globalMap.end(); ++globalIter)
        {
            m_providerMap[globalIter->first] = BufferAndImporter(globalIter->second);
        } // for globalIter
    }

    ~BufferAndImporterProvider() {}

private:
    BufferAndImporterProvider(const BufferAndImporterProvider&) = delete;
    BufferAndImporterProvider& operator=(const BufferAndImporterProvider&) = delete;

public:
    Identifier* getBuffer(const typename ImporterRegisterId::Key key)
    {
        typename ProviderMap::iterator iter = m_providerMap.find(key);
        if (iter == m_providerMap.end())
        {
            return nullptr;
        }

        return iter->second.getBuffer();
    }

    //========================================
    SpecialImporterBase<Identifier>* getImporter(const typename ImporterRegisterId::Key key)
    {
        //		LOGWARNING(logger, "Size of map: " << providerMap.size());

        typename ProviderMap::iterator iter = m_providerMap.find(key);
        if (iter == m_providerMap.end())
        {
            return nullptr;
        }

        return iter->second.getImporter();
    }

    const ProviderMap& getMap() const { return m_providerMap; }

protected:
    ProviderMap m_providerMap;
}; // BufferAndImporterProvider

//==============================================================================

template<typename Identifier>
class BufferAndImporterProvider<Identifier>::BufferAndImporter
{
public:
    using ImporterCreateFunction = typename SpecialImporterBase<Identifier>::ImporterRegisterId::ImporterCreateFunction;

public:
    BufferAndImporter() {}

    BufferAndImporter(ImporterCreateFunction createImporter) : m_createImporter(createImporter) {}

    ~BufferAndImporter() = default;

public:
    Identifier* getBuffer()
    {
        if (!m_buffer && (getImporter()))
        {
            m_buffer.reset(m_importer->createContainer());
        }
        return m_buffer.get();
    }

    //========================================
    SpecialImporterBase<Identifier>* getImporter()
    {
        if (!m_importer && m_createImporter)
        {
            m_importer.reset(m_createImporter());
        }
        return m_importer.get();
    }

    //========================================
    ImporterCreateFunction getCreateImporterPtr() const { return m_createImporter; }

protected:
    std::shared_ptr<Identifier> m_buffer{};
    std::shared_ptr<SpecialImporterBase<Identifier>> m_importer{};
    typename SpecialImporterBase<Identifier>::ImporterRegisterId::ImporterCreateFunction m_createImporter;
}; // ContainerBufferAndImporter

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

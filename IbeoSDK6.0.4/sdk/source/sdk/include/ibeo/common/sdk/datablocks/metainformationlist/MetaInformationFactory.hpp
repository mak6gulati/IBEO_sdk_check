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
//! \date Apr 5, 2016
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <map>
#include <exception>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

template<typename TMetaInformation>
class MetaInformationFactory
{
public:
    using MetaInformationSPtr = std::shared_ptr<TMetaInformation>;
    using FactoryFunc         = MetaInformationSPtr (*)(void);

public:
    MetaInformationFactory() = default;

public:
    void registerType(const typename TMetaInformation::MetaInformationType& type, FactoryFunc func)
    {
        // Verify we don't overwrite anything with this name!
        if (m_factoryMap.count(type) > 0)
        {
            assert(false);
            return;
        }

        m_factoryMap.insert(typename FactoryMap::value_type(type, func));
    }

    template<class T>
    void registerType(const typename TMetaInformation::MetaInformationType& type)
    {
        registerType(type, MetaInformationFactory::factory_function<T>);
    }

    const MetaInformationSPtr create(const typename TMetaInformation::MetaInformationType& type) const
    {
        typename FactoryMap::const_iterator iter = m_factoryMap.find(type);
        if (iter != m_factoryMap.end())
        {
            return iter->second();
        }
        else
        {
            return nullptr;
        }
    }

private:
    using FactoryMap = std::map<typename TMetaInformation::MetaInformationType, FactoryFunc>;

private:
    //========================
    template<class T>
    static MetaInformationSPtr factory_function()
    {
        return std::make_shared<T>();
    }
    //========================

private:
    FactoryMap m_factoryMap;
}; // MetaInformationFactory

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

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
//! \date Jan 22, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationFactory.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationList.hpp>

#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationAppBaseConfig.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationEcuId.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationKeywords.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationUnsupported.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationVersionNumber.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationBase.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class MetaInformationTestSupport : public TestSupport
{
public:
    using RandomFill = void (*)(ibeo::common::sdk::MetaInformationBase&);

private:
    using FillMap = std::map<MetaInformationBase::MetaInformationType, RandomFill>;

public:
    static constexpr int nbOfRepeats{100};

public:
    MetaInformationTestSupport();
    virtual ~MetaInformationTestSupport();

protected:
    MetaInformationList createMIL() const;
    MetaInformationList createMIL(const MetaInformationBase::MetaInformationType miType) const;
    MetaInformationBaseSPtr createMI(const MetaInformationBase::MetaInformationType miType) const;

protected:
    MetaInformationBaseSPtr createMI() const;

    static void fillRandomly(ibeo::common::sdk::MetaInformationAppBaseConfig& mil);
    static void fillRandomly(ibeo::common::sdk::MetaInformationEcuId& mil);
    static void fillRandomly(ibeo::common::sdk::MetaInformationKeywords& mil);
    static void fillRandomly(ibeo::common::sdk::MetaInformationUnsupported& mil);
    static void fillRandomly(ibeo::common::sdk::MetaInformationVersionNumber& mil);

    static void fill64kString(std::string& s);
    static void fillNonEmpty30String(std::string& s);

private:
    void fillRandomly(ibeo::common::sdk::MetaInformationBase& mi) const;

private:
    //========================
    template<class T>
    static void randomFill(MetaInformationBase& mi)
    {
        fillRandomly(dynamic_cast<T&>(mi));
    }

    //========================
    template<class T>
    void registerType(const MetaInformationBase::MetaInformationType type)
    {
        // Verify we don't overwrite anything with this name!
        if (m_fillMap.count(type) > 0)
        {
            assert(false);
            return;
        }
        m_fillMap.insert(FillMap::value_type(type, MetaInformationTestSupport::randomFill<T>));

        // register type at factory (factory cannot produce type unsupported).
        if (type != MetaInformationBase::MetaInformationType::Unsupported)
        {
            m_factory.registerType<T>(type);
        }
        //std::cerr << "MetaInformationBase Type registered: " << type << std::endl;
    }

private:
    FillMap m_fillMap;
    MetaInformationFactory<MetaInformationBase> m_factory;
}; // MetaInformationTestSupport

//==============================================================================

template<>
MetaInformationBase::MetaInformationType TestSupport::getRandValue();
template<>
MetaInformationVersionNumber::SoftwareType TestSupport::getRandValue();

//==============================================================================

} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

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

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/metainformationlist/MetaInformationFactory.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationList7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationAppBaseConfigIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationEcuIdIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationKeywordsIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationUnsupportedIn7110.hpp>
#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationVersionNumberIn7110.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class MetaInformationTestSupport : public TestSupport
{
public:
    using RandomFill = void (*)(MetaInformationBaseIn7110&);

private:
    using FillMap = std::map<MetaInformationBaseIn7110::MetaInformationType, RandomFill>;

public:
    static constexpr int nbOfRepeats{100};

public:
    MetaInformationTestSupport();
    virtual ~MetaInformationTestSupport();

protected:
    MetaInformationList7110 createMIL() const;
    MetaInformationList7110 createMIL(const MetaInformationBaseIn7110::MetaInformationType miType) const;
    MetaInformationBaseIn7110SPtr createMI(const MetaInformationBaseIn7110::MetaInformationType miType) const;

protected:
    MetaInformationBaseIn7110SPtr createMI() const;

    static void fillRandomly(ibeo::common::sdk::MetaInformationAppBaseConfigIn7110& mil);
    static void fillRandomly(ibeo::common::sdk::MetaInformationEcuIdIn7110& mil);
    static void fillRandomly(ibeo::common::sdk::MetaInformationKeywordsIn7110& mil);
    static void fillRandomly(ibeo::common::sdk::MetaInformationUnsupportedIn7110& mil);
    static void fillRandomly(ibeo::common::sdk::MetaInformationVersionNumberIn7110& mil);

    static void fill64kString(std::string& s);
    static void fillNonEmpty30String(std::string& s);

private:
    void fillRandomly(ibeo::common::sdk::MetaInformationBaseIn7110& mi) const;

private:
    //========================
    template<class T>
    static void randomFill(MetaInformationBaseIn7110& mi)
    {
        fillRandomly(dynamic_cast<T&>(mi));
    }

    //========================
    template<class T>
    void registerType(const MetaInformationBaseIn7110::MetaInformationType type)
    {
        // Verify we don't overwrite anything with this name!
        if (m_fillMap.count(type) > 0)
        {
            assert(false);
            return;
        }
        m_fillMap.insert(FillMap::value_type(type, MetaInformationTestSupport::randomFill<T>));

        // register type at factory (factory cannot produce type unsupported).
        if (type != MetaInformationBaseIn7110::MetaInformationType::Unsupported)
        {
            m_factory.registerType<T>(type);
        }
        //std::cerr << "MetaInformationBaseIn7110 Type registered: " << type << std::endl;
    }

private:
    FillMap m_fillMap;
    MetaInformationFactory<MetaInformationBaseIn7110> m_factory;
}; // MetaInformationTestSupport

//==============================================================================

template<>
MetaInformationBaseIn7110::MetaInformationType TestSupport::getRandValue();
template<>
MetaInformationVersionNumberIn7110::SoftwareType TestSupport::getRandValue();

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

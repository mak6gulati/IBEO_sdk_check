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

//==============================================================================

#include "MetaInformation7110TestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

MetaInformationTestSupport::MetaInformationTestSupport() : TestSupport()
{
    registerType<MetaInformationEcuIdIn7110>(MetaInformationBaseIn7110::MetaInformationType::EcuId);
    registerType<MetaInformationAppBaseConfigIn7110>(MetaInformationBaseIn7110::MetaInformationType::AppBaseConfig);
    registerType<MetaInformationKeywordsIn7110>(MetaInformationBaseIn7110::MetaInformationType::Keywords);
    registerType<MetaInformationVersionNumberIn7110>(MetaInformationBaseIn7110::MetaInformationType::VersionNumber);
    registerType<MetaInformationUnsupportedIn7110>(MetaInformationBaseIn7110::MetaInformationType::Unsupported);
}

//==============================================================================

MetaInformationTestSupport::~MetaInformationTestSupport() {}

//==============================================================================

MetaInformationList7110 MetaInformationTestSupport::createMIL() const
{
    MetaInformationList7110 mil;

    const uint8_t nbOfInfos = getRandValue<uint8_t>(20);

    for (uint8_t i = 0; i < nbOfInfos; ++i)
    {
        MetaInformationBaseIn7110SPtr mi = createMI();
        if (!mi)
        {
            mi = std::make_shared<MetaInformationUnsupportedIn7110>(
                static_cast<uint16_t>(
                    getRandValue<uint8_t>(2) + 1
                    + static_cast<uint16_t>(MetaInformationBaseIn7110::MetaInformationType::Keywords)),
                getRandValue<NTPTime>(),
                getRandValue<uint16_t>());
        }
        fillRandomly(*mi);
        mil.addMetaInformation(mi);
    }

    return mil;
}

//==============================================================================

MetaInformationList7110
MetaInformationTestSupport::createMIL(const MetaInformationBaseIn7110::MetaInformationType miType) const
{
    MetaInformationList7110 mil;

    const uint8_t nbOfInfos = getRandValue<uint8_t>(20);

    MetaInformationBaseIn7110SPtr mi = createMI(miType);
    if (!mi)
    {
        const MetaInformationBaseIn7110::MetaInformationType unsupportedType
            = MetaInformationBaseIn7110::MetaInformationType(
                getRandValue<uint8_t>(2) + 1
                + static_cast<uint16_t>(MetaInformationBaseIn7110::MetaInformationType::Keywords));

        mi = std::make_shared<MetaInformationUnsupportedIn7110>(
            static_cast<uint16_t>(unsupportedType), getRandValue<NTPTime>(), getRandValue<uint16_t>());
    }

    for (uint8_t i = 0; i < nbOfInfos; ++i)
    {
        fillRandomly(*mi);
        mil.addMetaInformation(mi);
    }

    return mil;
}

//==============================================================================

MetaInformationBaseIn7110SPtr
MetaInformationTestSupport::createMI(const MetaInformationBaseIn7110::MetaInformationType miType) const
{
    return m_factory.create(miType);
}

//==============================================================================

MetaInformationBaseIn7110SPtr MetaInformationTestSupport::createMI() const
{
    const MetaInformationBaseIn7110::MetaInformationType mit
        = getRandValue<MetaInformationBaseIn7110::MetaInformationType>();
    return createMI(mit);
}

//==============================================================================

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationBaseIn7110& mi) const
{
    const FillMap::const_iterator fillIter = m_fillMap.find(mi.getType());
    if (fillIter != m_fillMap.end())
    {
        (fillIter->second)(mi);
    }
}

//==============================================================================

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationAppBaseConfigIn7110& mil)
{
    std::string s;
    fill64kString(s);
    mil.setAppBaseConfig(s);
}

//==============================================================================

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationEcuIdIn7110& mil)
{
    std::string s;
    fill64kString(s);
    mil.setEcuId(s);
}

//==============================================================================

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationKeywordsIn7110& mil)
{
    const uint16_t n = getRandValue<uint16_t>(200);

    for (int i = 0; i < n; ++i)
    {
        std::string keyword;
        fillNonEmpty30String(keyword);
        mil.addKeyword(keyword);
    }
}

//==============================================================================

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationUnsupportedIn7110& mil)
{
    MetaInformationUnsupportedIn7110::DataVector& dv = mil.getData();
    dv.resize(getRandValue<uint16_t>());
    MetaInformationUnsupportedIn7110::DataVector::iterator it = dv.begin();
    for (; it != dv.end(); ++it)
    {
        *it = getRandValue<uint8_t>();
    }
}

//==============================================================================

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationVersionNumberIn7110& mil)
{
    mil.setSoftwareType(getRandValue<MetaInformationVersionNumberIn7110::SoftwareType>());
    mil.setVersionNumber(getRandValue<uint32_t>());
    std::string s;
    fill64kString(s);
    mil.setExtraString(s);
}

//==============================================================================

void MetaInformationTestSupport::fill64kString(std::string& s)
{
    const uint16_t n = getRandValue<uint16_t>();
    s.resize(n);

    std::string::iterator it = s.begin();
    for (; it != s.end(); ++it)
    {
        *it = int8_t(65 + getRandValue<uint8_t>(25));
    }
}

//==============================================================================

void MetaInformationTestSupport::fillNonEmpty30String(std::string& s)
{
    const uint32_t n = uint32_t(getRandValue<uint8_t>(29) + 1);
    s.resize(n);

    std::string::iterator it = s.begin();
    for (; it != s.end(); ++it)
    {
        *it = int8_t(65 + getRandValue<uint8_t>(25));
    }
}

//==============================================================================
//==============================================================================
//==============================================================================

template<>
MetaInformationBaseIn7110::MetaInformationType TestSupport::getRandValue()
{
    uint16_t rawMit
        = uint16_t(getRandValue<uint16_t>(uint16_t(MetaInformationBaseIn7110::MetaInformationType::Keywords) - 1));

    // skip value MetaInfoType_AppBaseSyncMethod
    if (rawMit >= static_cast<uint16_t>(MetaInformationBaseIn7110::MetaInformationType::AppBaseSyncMethod))
    {
        ++rawMit;
    }

    return static_cast<MetaInformationBaseIn7110::MetaInformationType>(rawMit);
}

//==============================================================================

template<>
MetaInformationVersionNumberIn7110::SoftwareType TestSupport::getRandValue()
{
    return static_cast<MetaInformationVersionNumberIn7110::SoftwareType>(
        getRandValue<uint16_t>(static_cast<uint16_t>(MetaInformationVersionNumberIn7110::SoftwareType::Ilv)));
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

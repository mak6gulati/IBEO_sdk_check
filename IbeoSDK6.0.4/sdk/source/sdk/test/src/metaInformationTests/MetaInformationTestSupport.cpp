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

#include "MetaInformationTestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

MetaInformationTestSupport::MetaInformationTestSupport() : TestSupport()
{
    registerType<MetaInformationEcuId>(MetaInformationBase::MetaInformationType::EcuId);
    registerType<MetaInformationAppBaseConfig>(MetaInformationBase::MetaInformationType::AppBaseConfig);
    registerType<MetaInformationKeywords>(MetaInformationBase::MetaInformationType::Keywords);
    registerType<MetaInformationVersionNumber>(MetaInformationBase::MetaInformationType::VersionNumber);
    registerType<MetaInformationUnsupported>(MetaInformationBase::MetaInformationType::Unsupported);
}

//==============================================================================

MetaInformationTestSupport::~MetaInformationTestSupport() {}

//==============================================================================

MetaInformationList MetaInformationTestSupport::createMIL() const
{
    MetaInformationList mil;

    const uint8_t nbOfInfos = getRandValue<uint8_t>(20);

    for (uint8_t i = 0; i < nbOfInfos; ++i)
    {
        MetaInformationBaseSPtr mi = createMI();
        if (!mi)
        {
            mi = std::make_shared<MetaInformationUnsupported>(
                static_cast<uint16_t>(getRandValue<uint8_t>(2) + 1
                                      + static_cast<uint16_t>(MetaInformationBase::MetaInformationType::Keywords)),
                getRandValue<NTPTime>(),
                getRandValue<uint16_t>());
        }

        fillRandomly(*mi);
        mil.addMetaInformation(mi);
    }

    return mil;
}

//==============================================================================

MetaInformationList MetaInformationTestSupport::createMIL(const MetaInformationBase::MetaInformationType miType) const
{
    MetaInformationList mil;

    const uint8_t nbOfInfos = getRandValue<uint8_t>(20);

    MetaInformationBaseSPtr mi = createMI(miType);
    if (!mi)
    {
        const MetaInformationBase::MetaInformationType unsupportedType = MetaInformationBase::MetaInformationType(
            getRandValue<uint8_t>(2) + 1 + static_cast<uint16_t>(MetaInformationBase::MetaInformationType::Keywords));

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

MetaInformationBaseSPtr
MetaInformationTestSupport::createMI(const MetaInformationBase::MetaInformationType miType) const
{
    return m_factory.create(miType);
}

//==============================================================================

MetaInformationBaseSPtr MetaInformationTestSupport::createMI() const
{
    const MetaInformationBase::MetaInformationType mit = getRandValue<MetaInformationBase::MetaInformationType>();
    return createMI(mit);
}

//==============================================================================

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationBase& mi) const
{
    const FillMap::const_iterator fillIter = m_fillMap.find(mi.getType());
    if (fillIter != m_fillMap.end())
    {
        (fillIter->second)(mi);
    }
}

//==============================================================================

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationAppBaseConfig& mil)
{
    std::string s;
    fill64kString(s);
    mil.setAppBaseConfig(s);
}

//==============================================================================

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationEcuId& mil)
{
    std::string s;
    fill64kString(s);
    mil.setEcuId(s);
}

//==============================================================================

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationKeywords& mil)
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

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationUnsupported& mil)
{
    MetaInformationUnsupported::DataVector& dv = mil.getData();
    dv.resize(getRandValue<uint16_t>());
    MetaInformationUnsupported::DataVector::iterator it = dv.begin();
    for (; it != dv.end(); ++it)
    {
        *it = getRandValue<uint8_t>();
    }
}

//==============================================================================

void MetaInformationTestSupport::fillRandomly(ibeo::common::sdk::MetaInformationVersionNumber& mil)
{
    mil.setSoftwareType(getRandValue<MetaInformationVersionNumber::SoftwareType>());
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
MetaInformationBase::MetaInformationType TestSupport::getRandValue()
{
    uint16_t rawMit
        = uint16_t(getRandValue<uint16_t>(uint16_t(MetaInformationBase::MetaInformationType::Keywords) - 1));

    // skip value MetaInfoType_AppBaseSyncMethod
    if (rawMit >= static_cast<uint16_t>(MetaInformationBase::MetaInformationType::AppBaseSyncMethod))
    {
        ++rawMit;
    }

    return static_cast<MetaInformationBase::MetaInformationType>(rawMit);
}

//==============================================================================

template<>
MetaInformationVersionNumber::SoftwareType TestSupport::getRandValue()
{
    return static_cast<MetaInformationVersionNumber::SoftwareType>(
        getRandValue<uint16_t>(static_cast<uint16_t>(MetaInformationVersionNumber::SoftwareType::Ilv)));
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

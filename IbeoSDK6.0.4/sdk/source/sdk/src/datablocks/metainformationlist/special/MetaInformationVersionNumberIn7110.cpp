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

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationVersionNumberIn7110.hpp>

#include <ibeo/common/sdk/io.hpp>

#include <algorithm>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//==============================================================================
//==============================================================================

template<>
void writeBE<MetaInformationVersionNumberIn7110::SoftwareType>(
    std::ostream& os,
    const MetaInformationVersionNumberIn7110::SoftwareType& cst)
{
    writeBE(os, uint16_t(cst));
}

//==============================================================================

template<>
void readBE<MetaInformationVersionNumberIn7110::SoftwareType>(std::istream& is,
                                                              MetaInformationVersionNumberIn7110::SoftwareType& cst)
{
    uint16_t rd16;
    readBE(is, rd16);
    cst = MetaInformationVersionNumberIn7110::SoftwareType(rd16);
}

//==============================================================================

void MetaInformationVersionNumberIn7110::setVersionNumber(const uint16_t major,
                                                          const uint16_t minor,
                                                          const uint16_t patch,
                                                          const std::string extra)
{
    m_versionNumber = VersionNumberType(major * 1000000 + minor * 1000 + patch);
    m_extraString   = extra;
}

//==============================================================================

MetaInformationVersionNumberIn7110::VersionPartType MetaInformationVersionNumberIn7110::getMajorVersion() const
{
    return VersionPartType(m_versionNumber / 1000000);
}

//==============================================================================

MetaInformationVersionNumberIn7110::VersionPartType MetaInformationVersionNumberIn7110::getMinorVersion() const
{
    return VersionPartType((m_versionNumber % 1000000) / 1000);
}

//==============================================================================

MetaInformationVersionNumberIn7110::VersionPartType MetaInformationVersionNumberIn7110::getPatchVersion() const
{
    return VersionPartType(m_versionNumber % 1000);
}

//==============================================================================

uint32_t MetaInformationVersionNumberIn7110::getSerializedPayloadSize() const
{
    return static_cast<uint32_t>(sizeof(uint16_t) + sizeof(uint32_t) + sizeof(uint16_t) + m_extraString.size());
}

//==============================================================================

bool MetaInformationVersionNumberIn7110::deserializePayload(std::istream& is, const uint32_t payloadSize)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, m_softwareType);
    readBE(is, m_versionNumber);

    uint16_t len;
    ibeo::common::sdk::readBE(is, len);

    m_extraString.resize(len);
    if (len > 0)
    {
        is.read(&m_extraString[0], len);
    }

    return !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos) == payloadSize && payloadSize == getSerializedPayloadSize());
}

//==============================================================================

bool MetaInformationVersionNumberIn7110::serializePayload(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, m_softwareType);
    writeBE(os, m_versionNumber);

    writeBE(os, static_cast<uint16_t>(m_extraString.size()));
    os.write(&m_extraString[0], std::streamsize(m_extraString.size()));

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedPayloadSize());
}

//==============================================================================

bool MetaInformationVersionNumberIn7110::isEqual(const MetaInformationBaseIn7110& otherBase) const
{
    // Can compare same types only.
    const MetaInformationVersionNumberIn7110* other
        = dynamic_cast<const MetaInformationVersionNumberIn7110*>(&otherBase);
    assert(other != nullptr);

    return MetaInformationBaseIn7110::isEqual(otherBase) && (this->getSoftwareType() == other->getSoftwareType())
           && (this->getVersionNumber() == other->getVersionNumber())
           && (this->getExtraString() == other->getExtraString());
}

//==============================================================================
//==============================================================================
//==============================================================================

std::ostream& operator<<(std::ostream& os, const MetaInformationVersionNumberIn7110::SoftwareType st)
{
    switch (st)
    {
    case MetaInformationVersionNumberIn7110::SoftwareType::Undefined:
        os << "Undefined";
        break;
    case MetaInformationVersionNumberIn7110::SoftwareType::Custom:
        os << "Custom";
        break;
    case MetaInformationVersionNumberIn7110::SoftwareType::AppBase:
        os << "AppBase";
        break;
    case MetaInformationVersionNumberIn7110::SoftwareType::EvS:
        os << "EvS";
        break;
    case MetaInformationVersionNumberIn7110::SoftwareType::Ilv:
        os << "Ilv";
        break;
    default:
        os << "Unknown software type" << static_cast<uint32_t>(st);
    }
    return os;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

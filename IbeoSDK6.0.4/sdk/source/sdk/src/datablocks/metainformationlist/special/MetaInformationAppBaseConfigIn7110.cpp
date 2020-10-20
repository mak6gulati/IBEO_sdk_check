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

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationAppBaseConfigIn7110.hpp>

#include <ibeo/common/sdk/io.hpp>

#include <algorithm>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

uint32_t MetaInformationAppBaseConfigIn7110::getSerializedPayloadSize() const
{
    return static_cast<uint32_t>(sizeof(uint16_t) + m_appBaseConfig.size());
}

//==============================================================================

void MetaInformationAppBaseConfigIn7110::setAppBaseConfig(const std::string& newAppBaseConfig)
{
    m_appBaseConfig = newAppBaseConfig;
    if (m_appBaseConfig.size() > maxStringLength)
    {
        m_appBaseConfig.resize(maxStringLength);
    }
}

//==============================================================================

bool MetaInformationAppBaseConfigIn7110::deserializePayload(std::istream& is, const uint32_t payloadSize)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    uint16_t len;
    ibeo::common::sdk::readBE(is, len);

    m_appBaseConfig.resize(len);
    if (len > 0)
    {
        is.read(&m_appBaseConfig[0], len);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == payloadSize)
           && (payloadSize == getSerializedPayloadSize());
}

//==============================================================================

bool MetaInformationAppBaseConfigIn7110::serializePayload(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, uint16_t(m_appBaseConfig.size()));
    os.write(&m_appBaseConfig[0], std::streamsize(m_appBaseConfig.size()));

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedPayloadSize());
}

//==============================================================================

bool MetaInformationAppBaseConfigIn7110::isEqual(const MetaInformationBaseIn7110& otherBase) const
{
    // Can compare same types only.
    const MetaInformationAppBaseConfigIn7110* other
        = dynamic_cast<const MetaInformationAppBaseConfigIn7110*>(&otherBase);
    assert(other != nullptr);

    return MetaInformationBaseIn7110::isEqual(otherBase) && (this->getAppBaseConfig() == other->getAppBaseConfig());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

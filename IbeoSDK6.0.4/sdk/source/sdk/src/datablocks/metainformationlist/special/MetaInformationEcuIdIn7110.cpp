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

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationEcuIdIn7110.hpp>

#include <ibeo/common/sdk/io.hpp>

#include <algorithm>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

uint32_t MetaInformationEcuIdIn7110::getSerializedPayloadSize() const
{
    return static_cast<uint32_t>(sizeof(uint16_t) + m_ecuId.size());
}

//==============================================================================

void MetaInformationEcuIdIn7110::setEcuId(const std::string& newEcuId)
{
    m_ecuId = newEcuId;
    if (m_ecuId.size() > maxStringLength)
    {
        m_ecuId.resize(maxStringLength);
    }
}

//==============================================================================

bool MetaInformationEcuIdIn7110::deserializePayload(std::istream& is, const uint32_t payloadSize)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    uint16_t len;
    ibeo::common::sdk::readBE(is, len);

    m_ecuId.resize(len);
    if (len > 0)
    {
        is.read(&m_ecuId[0], len);
    }

    return !is.fail()
           && ((streamposToInt64(is.tellg()) - startPos) == payloadSize && payloadSize == getSerializedPayloadSize());
}

//==============================================================================

bool MetaInformationEcuIdIn7110::serializePayload(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, uint16_t(m_ecuId.size()));
    os.write(&m_ecuId[0], std::streamsize(m_ecuId.size()));

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool MetaInformationEcuIdIn7110::isEqual(const MetaInformationBaseIn7110& otherBase) const
{
    // Can compare same types only.
    const MetaInformationEcuIdIn7110* other = dynamic_cast<const MetaInformationEcuIdIn7110*>(&otherBase);
    assert(other != nullptr);

    return MetaInformationBaseIn7110::isEqual(otherBase) && (this->getEcuId() == other->getEcuId());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

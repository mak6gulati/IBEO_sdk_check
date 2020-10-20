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

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationBaseIn7110.hpp>
#include <ibeo/common/sdk/misc/ToHex.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

template<>
void writeBE<MetaInformationBaseIn7110::MetaInformationType>(std::ostream& os,
                                                             const MetaInformationBaseIn7110::MetaInformationType& mit)
{
    writeBE(os, static_cast<uint16_t>(mit));
}

//==============================================================================

template<>
void readBE<MetaInformationBaseIn7110::MetaInformationType>(std::istream& is,
                                                            MetaInformationBaseIn7110::MetaInformationType& mit)
{
    uint16_t rd16;
    readBE(is, rd16);
    mit = static_cast<MetaInformationBaseIn7110::MetaInformationType>(rd16);
}

//==============================================================================
//==============================================================================
//==============================================================================

std::streamsize MetaInformationBaseIn7110::getSerializedSize() const
{
    return std::streamsize(sizeof(uint16_t) // type
                           + sizeof(uint64_t) // timestamp
                           + sizeof(uint32_t) // payload size
                           + this->getSerializedPayloadSize());
}

//==============================================================================

bool MetaInformationBaseIn7110::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, m_type);
    readBE(is, m_timeStamp);

    uint32_t payloadSize;
    readBE(is, payloadSize);

    deserializePayload(is, payloadSize);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool MetaInformationBaseIn7110::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, m_type);
    writeBE(os, m_timeStamp);
    writeBE(os, this->getSerializedPayloadSize());

    serializePayload(os);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool MetaInformationBaseIn7110::isEqual(const MetaInformationBaseIn7110& other) const
{
    return (m_type == other.m_type) && (m_timeStamp == other.m_timeStamp);
}

//==============================================================================
//==============================================================================
//==============================================================================

std::ostream& operator<<(std::ostream& os, const MetaInformationBaseIn7110::MetaInformationType t)
{
    switch (t)
    {
    case MetaInformationBaseIn7110::MetaInformationType::Unsupported:
        os << "Unsupported";
        break;
    case MetaInformationBaseIn7110::MetaInformationType::VersionNumber:
        os << "VersionNumber";
        break;
    case MetaInformationBaseIn7110::MetaInformationType::AppBaseConfig:
        os << "AppBaseConfig";
        break;
    case MetaInformationBaseIn7110::MetaInformationType::AppBaseSyncMethod:
        os << "AppBaseSyncMethod";
        break;
    case MetaInformationBaseIn7110::MetaInformationType::EcuId:
        os << "EcuId";
        break;
    case MetaInformationBaseIn7110::MetaInformationType::Keywords:
        os << "Keywords";
        break;
    default:
        os << "Unknown type " << toHex(static_cast<uint32_t>(t));
    }
    return os;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

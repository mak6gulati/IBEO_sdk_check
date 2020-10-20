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
//! \date Sep 17, 2015
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/scan/special/ScanHeaderIn2310.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

const uint16_t ScanHeaderIn2310::blockId = 0xF000U;

//==============================================================================

ScanHeaderIn2310::ScanHeaderIn2310()
  : m_scanCounter(0),
    m_minApdOffset(0),
    m_maxApdOffset(0),
    m_frequencyInteger(0),
    m_frequencyFractional(0),
    m_deviceId(0),
    m_reservedHeader7(0)
{}

//==============================================================================

ScanHeaderIn2310::~ScanHeaderIn2310() {}

//==============================================================================

bool ScanHeaderIn2310::operator==(const ScanHeaderIn2310& other) const
{
    return this->m_scanCounter == other.m_scanCounter && this->m_minApdOffset == other.m_minApdOffset
           && this->m_maxApdOffset == other.m_maxApdOffset && this->m_frequencyInteger == other.m_frequencyInteger
           && this->m_frequencyFractional == other.m_frequencyFractional && this->m_deviceId == other.m_deviceId
           && this->m_reservedHeader7 == other.m_reservedHeader7;
}

//==============================================================================

bool ScanHeaderIn2310::operator!=(const ScanHeaderIn2310& other) const { return !((*this) == other); }

//==============================================================================

bool ScanHeaderIn2310::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    uint16_t readBlockId;
    readLE(is, readBlockId);
    if (readBlockId != ScanHeaderIn2310::blockId)
        return false;

    readLE(is, m_scanCounter);
    readLE(is, m_minApdOffset);
    readLE(is, m_maxApdOffset);
    readLE(is, m_frequencyInteger);
    readLE(is, m_frequencyFractional);
    readLE(is, m_deviceId);
    readLE(is, m_reservedHeader7);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == (this->getSerializedSize()));
}

//==============================================================================

bool ScanHeaderIn2310::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeLE(os, blockId);
    writeLE(os, m_scanCounter);
    writeLE(os, m_minApdOffset);
    writeLE(os, m_maxApdOffset);
    writeLE(os, m_frequencyInteger);
    writeLE(os, m_frequencyFractional);
    writeLE(os, m_deviceId);
    writeLE(os, m_reservedHeader7);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

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
//! \date Aug 2, 2013
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/scan/special/ScanPointIn2208.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

ScanPointIn2208::ScanPointIn2208() {}

//==============================================================================

ScanPointIn2208::~ScanPointIn2208() {}

//==============================================================================

bool ScanPointIn2208::operator==(const ScanPointIn2208& other) const
{
    return this->m_thresholdId == other.m_thresholdId && this->m_echoId == other.m_echoId
           && this->m_reserved == other.m_reserved && this->m_layerId == other.m_layerId
           && this->m_flags == other.m_flags && this->m_horizontalAngle == other.m_horizontalAngle
           && this->m_radialDistance == other.m_radialDistance && this->m_echoPulseWidth == other.m_echoPulseWidth
           && this->m_pfValue == other.m_pfValue;
}

//==============================================================================

bool ScanPointIn2208::operator!=(const ScanPointIn2208& other) const
{
    return this->m_thresholdId != other.m_thresholdId || this->m_echoId != other.m_echoId
           || this->m_reserved != other.m_reserved || this->m_layerId != other.m_layerId
           || this->m_flags != other.m_flags || this->m_horizontalAngle != other.m_horizontalAngle
           || this->m_radialDistance != other.m_radialDistance || this->m_echoPulseWidth != other.m_echoPulseWidth
           || this->m_pfValue != other.m_pfValue;
}

//==============================================================================

bool ScanPointIn2208::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    uint8_t tmp = 0;
    readBE(is, tmp);
    m_thresholdId = tmp & 0xf;
    m_echoId      = uint8_t((tmp & 0x30) >> 4);
    m_reserved    = (tmp & 0xc0) >> 6;

    readBE(is, m_layerId);
    readBE(is, m_flags);
    readBE(is, m_horizontalAngle);
    readBE(is, m_radialDistance);
    readBE(is, m_echoPulseWidth);
    readBE(is, m_pfValue);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ScanPointIn2208::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    const uint8_t tmp = uint8_t((m_thresholdId & 0xf) | ((m_echoId & 0x03) << 4) | ((m_reserved & 0x03) << 6));
    writeBE(os, tmp);

    writeBE(os, m_layerId);
    writeBE(os, m_flags);
    writeBE(os, m_horizontalAngle);
    writeBE(os, m_radialDistance);
    writeBE(os, m_echoPulseWidth);
    writeBE(os, m_pfValue);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

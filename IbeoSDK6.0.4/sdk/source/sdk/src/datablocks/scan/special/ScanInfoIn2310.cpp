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

#include <ibeo/common/sdk/datablocks/scan/special/ScanInfoIn2310.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

const uint16_t ScanInfoIn2310::blockId = 0xF010U;

//==============================================================================

ScanInfoIn2310::ScanInfoIn2310()
  : m_ApdActualValue(0),
    m_ApdTableValue(0),
    m_temperature(0),
    m_referenceNoise(0),
    m_controlNoise(0),
    m_noiseMeasurementThreshold(0),
    m_reservedInfo7(0)
{}

//==============================================================================

ScanInfoIn2310::~ScanInfoIn2310() {}

//==============================================================================

bool ScanInfoIn2310::operator==(const ScanInfoIn2310& other) const
{
    return this->m_ApdActualValue == other.m_ApdActualValue && this->m_ApdTableValue == other.m_ApdTableValue
           && this->m_temperature == other.m_temperature && this->m_referenceNoise == other.m_referenceNoise
           && this->m_controlNoise == other.m_controlNoise
           && this->m_noiseMeasurementThreshold == other.m_noiseMeasurementThreshold
           && this->m_reservedInfo7 == other.m_reservedInfo7;
}

//==============================================================================

bool ScanInfoIn2310::operator!=(const ScanInfoIn2310& other) const { return !((*this) == other); }

//==============================================================================

bool ScanInfoIn2310::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    uint16_t readBlockId;
    readLE(is, readBlockId);
    if (readBlockId != ScanInfoIn2310::blockId)
        return false;

    readLE(is, m_ApdActualValue);
    readLE(is, m_ApdTableValue);
    readLE(is, m_temperature);
    readLE(is, m_referenceNoise);
    readLE(is, m_controlNoise);
    readLE(is, m_noiseMeasurementThreshold);
    readLE(is, m_reservedInfo7);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == (this->getSerializedSize()));
}

//==============================================================================

bool ScanInfoIn2310::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeLE(os, blockId);
    writeLE(os, m_ApdActualValue);
    writeLE(os, m_ApdTableValue);
    writeLE(os, m_temperature);
    writeLE(os, m_referenceNoise);
    writeLE(os, m_controlNoise);
    writeLE(os, m_noiseMeasurementThreshold);
    writeLE(os, m_reservedInfo7);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

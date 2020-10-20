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

#include <ibeo/common/sdk/datablocks/scan/special/ScanSegInfoIn2310.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

const uint16_t ScanSegInfoIn2310::blockId = 0xF040U;

//==============================================================================

ScanSegInfoIn2310::ScanSegInfoIn2310()
  : m_segmentIndex(0),
    m_ApdVoltage(0),
    m_noise(0),
    m_reservedSegmentInfo4(0),
    m_reservedSegmentInfo5(0),
    m_reservedSegmentInfo6(0),
    m_reservedSegmentInfo7(0)
{}

//==============================================================================

ScanSegInfoIn2310::~ScanSegInfoIn2310() {}

//==============================================================================

bool ScanSegInfoIn2310::operator==(const ScanSegInfoIn2310& other) const
{
    return this->m_segmentIndex == other.m_segmentIndex && this->m_ApdVoltage == other.m_ApdVoltage
           && this->m_noise == other.m_noise && this->m_reservedSegmentInfo4 == other.m_reservedSegmentInfo4
           && this->m_reservedSegmentInfo5 == other.m_reservedSegmentInfo5
           && this->m_reservedSegmentInfo6 == other.m_reservedSegmentInfo6
           && this->m_reservedSegmentInfo7 == other.m_reservedSegmentInfo7;
}

//==============================================================================

bool ScanSegInfoIn2310::operator!=(const ScanSegInfoIn2310& other) const { return !((*this) == other); }

//==============================================================================

bool ScanSegInfoIn2310::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    uint16_t readBlockId;
    readLE(is, readBlockId);
    if (readBlockId != ScanSegInfoIn2310::blockId)
        return false;

    readLE(is, m_segmentIndex);
    readLE(is, m_ApdVoltage);
    readLE(is, m_noise);
    readLE(is, m_reservedSegmentInfo4);
    readLE(is, m_reservedSegmentInfo5);
    readLE(is, m_reservedSegmentInfo6);
    readLE(is, m_reservedSegmentInfo7);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == (this->getSerializedSize()));
}

//==============================================================================

bool ScanSegInfoIn2310::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeLE(os, blockId);
    writeLE(os, m_segmentIndex);
    writeLE(os, m_ApdVoltage);
    writeLE(os, m_noise);
    writeLE(os, m_reservedSegmentInfo4);
    writeLE(os, m_reservedSegmentInfo5);
    writeLE(os, m_reservedSegmentInfo6);
    writeLE(os, m_reservedSegmentInfo7);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

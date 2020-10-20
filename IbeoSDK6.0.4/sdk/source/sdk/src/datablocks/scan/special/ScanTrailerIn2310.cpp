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

#include <ibeo/common/sdk/datablocks/scan/special/ScanTrailerIn2310.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

const uint16_t ScanTrailerIn2310::blockId = 0xF020U;

//==============================================================================

ScanTrailerIn2310::ScanTrailerIn2310()
  : m_operatingRegister(0),
    m_warning(0),
    m_error(0),
    m_reservedTrailer4(0),
    m_scanPointCounter(0),
    m_configurationRegister(0),
    m_reservedTrailer7(0)
{}

//==============================================================================

ScanTrailerIn2310::~ScanTrailerIn2310() {}

//==============================================================================

bool ScanTrailerIn2310::operator==(const ScanTrailerIn2310& other) const
{
    return this->m_operatingRegister == other.m_operatingRegister && this->m_warning == other.m_warning
           && this->m_error == other.m_error && this->m_reservedTrailer4 == other.m_reservedTrailer4
           && this->m_scanPointCounter == other.m_scanPointCounter
           && this->m_configurationRegister == other.m_configurationRegister
           && this->m_reservedTrailer7 == other.m_reservedTrailer7;
}

//==============================================================================

bool ScanTrailerIn2310::operator!=(const ScanTrailerIn2310& other) const { return !((*this) == other); }

//==============================================================================

bool ScanTrailerIn2310::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    uint16_t readBlockId;
    readLE(is, readBlockId);
    if (readBlockId != ScanTrailerIn2310::blockId)
        return false;

    readLE(is, m_operatingRegister);
    readLE(is, m_warning);
    readLE(is, m_error);
    readLE(is, m_reservedTrailer4);
    readLE(is, m_scanPointCounter);
    readLE(is, m_configurationRegister);
    readLE(is, m_reservedTrailer7);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == (this->getSerializedSize()));
}

//==============================================================================

bool ScanTrailerIn2310::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeLE(os, blockId);
    writeLE(os, m_operatingRegister);
    writeLE(os, m_warning);
    writeLE(os, m_error);
    writeLE(os, m_reservedTrailer4);
    writeLE(os, m_scanPointCounter);
    writeLE(os, m_configurationRegister);
    writeLE(os, m_reservedTrailer7);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

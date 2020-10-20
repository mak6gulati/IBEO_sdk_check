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
//! \date Aug 31, 2016
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/devices/sutp/SutpHeader.hpp>

#include <ibeo/common/sdk/io.hpp>

#include <ostream>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

ibeo::common::logging::LoggerSPtr SutpHeader::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

SutpHeader::SutpHeader()
  : m_timestamp(0),
    m_version(0),
    m_seqNo(0),
    m_flags(0),
    m_scannerId(0),
    m_dataType(0),
    m_fwVersion(0),
    m_scanNo(0),
    m_fragsTotal(0),
    m_fragNo(0)
{}

//==============================================================================

SutpHeader::SutpHeader(const uint64_t timestamp,
                       const uint16_t version,
                       const uint16_t seqNo,
                       const uint8_t flags,
                       const uint8_t scannerId,
                       const uint16_t dataType,
                       const uint16_t fwVersion,
                       const uint16_t scanNo,
                       const uint16_t fragsTotal,
                       const uint16_t fragNo)
  : m_timestamp(timestamp),
    m_version(version),
    m_seqNo(seqNo),
    m_flags(flags),
    m_scannerId(scannerId),
    m_dataType(dataType),
    m_fwVersion(fwVersion),
    m_scanNo(scanNo),
    m_fragsTotal(fragsTotal),
    m_fragNo(fragNo)
{}

//==============================================================================

SutpHeader::~SutpHeader() {}

//==============================================================================

bool SutpHeader::operator==(const SutpHeader& other) const
{
    return m_timestamp == other.m_timestamp && m_version == other.m_version && m_seqNo == other.m_seqNo
           && m_flags == other.m_flags && m_scannerId == other.m_scannerId && m_dataType == other.m_dataType
           && m_fwVersion == other.m_fwVersion && m_scanNo == other.m_scanNo && m_fragsTotal == other.m_fragsTotal
           && m_fragNo == other.m_fragNo;
}

//==============================================================================

bool SutpHeader::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_timestamp);
    ibeo::common::sdk::readBE(is, m_version);
    if (m_version != static_cast<uint16_t>(ProtocolVersion::Version_01))
    {
        LOGERROR(logger, "SUTP header magic word mismatch.");
        is.clear(std::ios::failbit);
        return !is.fail();
    }
    ibeo::common::sdk::readBE(is, m_seqNo);
    ibeo::common::sdk::readBE(is, m_flags);
    ibeo::common::sdk::readBE(is, m_scannerId);
    ibeo::common::sdk::readBE(is, m_dataType);
    ibeo::common::sdk::readBE(is, m_fwVersion);
    ibeo::common::sdk::readBE(is, m_scanNo);
    ibeo::common::sdk::readBE(is, m_fragsTotal);
    ibeo::common::sdk::readBE(is, m_fragNo);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool SutpHeader::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    if (m_version != static_cast<uint16_t>(ProtocolVersion::Version_01))
    {
        LOGERROR(logger, "SUTP header magic word mismatch.");
        return false;
    }

    ibeo::common::sdk::writeBE(os, m_timestamp);
    ibeo::common::sdk::writeBE(os, m_version);
    ibeo::common::sdk::writeBE(os, m_seqNo);
    ibeo::common::sdk::writeBE(os, m_flags);
    ibeo::common::sdk::writeBE(os, m_scannerId);
    ibeo::common::sdk::writeBE(os, m_dataType);
    ibeo::common::sdk::writeBE(os, m_fwVersion);
    ibeo::common::sdk::writeBE(os, m_scanNo);
    ibeo::common::sdk::writeBE(os, m_fragsTotal);
    ibeo::common::sdk::writeBE(os, m_fragNo);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

std::string SutpHeader::prettyPrint() const
{
    std::stringstream os;
    os << std::hex << "[ibeo::SutpHeader:"
       << " m_timestamp=" << m_timestamp << " m_version=" << m_version << " m_seqNo=" << m_seqNo
       << " m_flags=" << uint16_t(m_flags) << " m_scannerId=" << uint16_t(m_scannerId) << " m_dataType=" << m_dataType
       << " m_fwVersion=" << m_fwVersion << " m_scanNo=" << m_scanNo << " m_fragsTotal=" << m_fragsTotal
       << " m_fragNo=" << m_fragNo << "]";
    return os.str();
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

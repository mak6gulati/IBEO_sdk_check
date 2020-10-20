//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date May 11, 2015
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndexEntryIn6130.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize FrameIndexEntryIn6130::getSerializedSize_static()
{
    return std::streamsize(2 * sizeof(uint64_t) + sizeof(uint8_t));
}

//==============================================================================

std::streamsize FrameIndexEntryIn6130::getSerializedSize() const { return getSerializedSize_static(); }

//==============================================================================

bool FrameIndexEntryIn6130::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_filePosition);
    ibeo::common::sdk::readBE(is, m_timeOffsetMs);
    ibeo::common::sdk::readBE(is, m_deviceId);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool FrameIndexEntryIn6130::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_filePosition);
    ibeo::common::sdk::writeBE(os, m_timeOffsetMs);
    ibeo::common::sdk::writeBE(os, m_deviceId);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool operator==(const FrameIndexEntryIn6130& lhs, const FrameIndexEntryIn6130& rhs)
{
    return (lhs.getFilePosition() == rhs.getFilePosition()) && (lhs.getTimeOffsetMs() == rhs.getTimeOffsetMs())
           && (lhs.getDeviceId() == rhs.getDeviceId());
}

//==============================================================================

bool operator!=(const FrameIndexEntryIn6130& lhs, const FrameIndexEntryIn6130& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

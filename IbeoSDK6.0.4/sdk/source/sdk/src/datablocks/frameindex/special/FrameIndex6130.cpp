//==============================================================================
//!\file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Mar 9, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

constexpr uint8_t FrameIndex6130::majorVersion;
constexpr uint8_t FrameIndex6130::minorVersion;

//==============================================================================

bool operator==(const FrameIndex6130& lhs, const FrameIndex6130& rhs)
{
    return (lhs.getFramingPolicy() == rhs.getFramingPolicy()) && (lhs.getFrameIndices() == rhs.getFrameIndices())
           && (lhs.getTimeOffsetMs() == rhs.getTimeOffsetMs());
}

//==============================================================================

bool operator!=(const FrameIndex6130& lhs, const FrameIndex6130& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

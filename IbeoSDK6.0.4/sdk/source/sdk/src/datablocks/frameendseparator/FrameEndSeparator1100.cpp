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
//!\date Jan 11, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/frameendseparator/FrameEndSeparator1100.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

FrameEndSeparator1100::FrameEndSeparator1100() : SpecializedDataContainer() {}

//==============================================================================

FrameEndSeparator1100::~FrameEndSeparator1100() {}

//==============================================================================

//==============================================================================

bool operator==(const FrameEndSeparator1100& lhs, const FrameEndSeparator1100& rhs)
{
    return (lhs.getFrameId() == rhs.getFrameId()) && (lhs.getSizeOfThisFrame() == rhs.getSizeOfThisFrame())
           && (lhs.getSizeOfNextFrame() == rhs.getSizeOfNextFrame()) && (lhs.getCreationTime() == rhs.getCreationTime())
           && (lhs.getReserved() == rhs.getReserved());
}

//==============================================================================

bool operator!=(const FrameEndSeparator1100& lhs, const FrameEndSeparator1100& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

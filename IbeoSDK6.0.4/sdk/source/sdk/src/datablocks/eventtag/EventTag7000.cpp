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
//!\date Mar 21, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/eventtag/EventTag7000.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

EventTag7000::EventTag7000() : SpecializedDataContainer{} {}

//==============================================================================

EventTag7000::~EventTag7000() {}

//==============================================================================

bool operator==(const EventTag7000& lhs, const EventTag7000& rhs)
{
    return (lhs.getTagStart() == rhs.getTagStart()) && (lhs.getTagEnd() == rhs.getTagEnd())
           && (lhs.getFlags() == rhs.getFlags()) && (lhs.getTagClass() == rhs.getTagClass())
           && (lhs.getTagId() == rhs.getTagId()) && (lhs.getTagString() == rhs.getTagString())
           && (lhs.getWgs84() == rhs.getWgs84()) && (lhs.getRoiWidth() == rhs.getRoiWidth())
           && (lhs.getRoiLength() == rhs.getRoiLength()) && (lhs.getReserved() == rhs.getReserved());
}

//==============================================================================

bool operator!=(const EventTag7000& lhs, const EventTag7000& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

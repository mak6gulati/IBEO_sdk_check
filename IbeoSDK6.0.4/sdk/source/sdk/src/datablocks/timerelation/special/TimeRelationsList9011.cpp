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
//!\date March 14, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9011.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

TimeRelationsList9011::TimeRelationsList9011() : SpecializedDataContainer() {}

//==============================================================================

TimeRelationsList9011::~TimeRelationsList9011() {}

//==============================================================================

bool operator==(const TimeRelationsList9011& lhs, const TimeRelationsList9011& rhs)
{
    if ((lhs.getRefClock() == rhs.getRefClock()) && (lhs.getTimeRelations().size() == rhs.getTimeRelations().size()))
    {
        return (lhs.getTimeRelations() == rhs.getTimeRelations());
    }
    return false;
}

//==============================================================================

bool operator!=(const TimeRelationsList9011& lhs, const TimeRelationsList9011& rhs) { return !(lhs == rhs); }

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

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

#include <ibeo/common/sdk/datablocks/timerelation/special/TimeRelationsList9010.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

TimeRelationsList9010::TimeRelationsList9010() : SpecializedDataContainer() {}

//==============================================================================

TimeRelationsList9010::~TimeRelationsList9010() {}

//==============================================================================

bool operator==(const TimeRelationsList9010& lhs, const TimeRelationsList9010& rhs)
{
    if (lhs.getTimeRelations().size() == rhs.getTimeRelations().size())
    {
        return (lhs.getTimeRelations() == rhs.getTimeRelations());
    }

    return false;
}

//==============================================================================

bool operator!=(const TimeRelationsList9010& lhs, const TimeRelationsList9010& rhs) { return !(lhs == rhs); }
//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

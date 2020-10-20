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
//!\date 07.November 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/missionhandling/MissionHandlingStatus3530.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

MissionHandlingStatus3530::MissionHandlingStatus3530() : SpecializedDataContainer() {}

//==============================================================================

bool operator==(const MissionHandlingStatus3530& lhs, const MissionHandlingStatus3530& rhs)
{
    if ((lhs.getTimestamp() != rhs.getTimestamp()) || (lhs.getState() != rhs.getState())
        || (lhs.getMissionId() != rhs.getMissionId()) || (lhs.getReserved() != rhs.getReserved()))
    {
        return false;
    }

    return true;
}

//==============================================================================

bool operator!=(const MissionHandlingStatus3530& lhs, const MissionHandlingStatus3530& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

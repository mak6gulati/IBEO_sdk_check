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
//!\date Sept 05, 2018

#include <ibeo/common/sdk/datablocks/missionresponse/MissionResponse3540.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

MissionResponse3540::MissionResponse3540() : SpecializedDataContainer() {}

//==============================================================================

uint32_t MissionResponse3540::getReserved(const uint_fast8_t idx) const { return m_reserved.at(idx); }

//==============================================================================

bool operator==(const MissionResponse3540& lhs, const MissionResponse3540& rhs)
{
    if ((lhs.getTimestamp() != rhs.getTimestamp()) || (lhs.getResponse() != rhs.getResponse())
        || (lhs.getMissionId() != rhs.getMissionId()))
    {
        return false;
    }

    for (uint_fast8_t i = 0; i < MissionResponse3540::nbOfReserved; ++i)
    {
        if (lhs.getReserved(i) != rhs.getReserved(i))
        {
            return false;
        }
    }

    return true;
}

//==============================================================================

bool operator!=(const MissionResponse3540& lhs, const MissionResponse3540& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

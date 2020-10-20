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

#include "MissionHandlingStatus3530TestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

MissionHandlingStatus3530TestSupport::MissionHandlingStatus3530TestSupport() : TestSupport() {}

//==============================================================================

MissionHandlingStatus3530 MissionHandlingStatus3530TestSupport::createMissionHandlingStatus3530()
{
    MissionHandlingStatus3530 mhs;
    fillRandomly(mhs);
    return mhs;
}

//==============================================================================

void MissionHandlingStatus3530TestSupport::fillRandomly(MissionHandlingStatus3530& mhs)
{
    mhs.setTimestamp(getRandValue<NTPTime>());
    mhs.setState(static_cast<MissionHandlingStatus3530::State>(getRandValue<uint8_t>()));
    mhs.setMissionId(getRandValue<uint32_t>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

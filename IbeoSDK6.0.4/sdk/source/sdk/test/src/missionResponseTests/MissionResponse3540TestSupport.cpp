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
//------------------------------------------------------------------------------
#include "MissionResponse3540TestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

MissionResponse3540TestSupport::MissionResponse3540TestSupport() : TestSupport() {}
//==============================================================================

ibeo::common::sdk::MissionResponse3540 MissionResponse3540TestSupport::createMissionResponse3540()
{
    ibeo::common::sdk::MissionResponse3540 mr;
    fillRandomly(mr);
    return mr;
}

//==============================================================================

void MissionResponse3540TestSupport::fillRandomly(MissionResponse3540& mr)
{
    mr.setTimestamp(getRandValue<NTPTime>());
    mr.setResponse(static_cast<MissionResponse3540::Response>(
        getDifferentRandValue<uint8_t>(static_cast<uint8_t>(mr.getResponse()))));
    mr.setMissionId(getDifferentRandValue<uint32_t>(mr.getMissionId()));
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

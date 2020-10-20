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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include "common/TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/missionhandling/MissionHandlingStatus3530.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class MissionHandlingStatus3530TestSupport : public TestSupport
{
public:
    MissionHandlingStatus3530TestSupport();
    virtual ~MissionHandlingStatus3530TestSupport() = default;

public:
    static MissionHandlingStatus3530 createMissionHandlingStatus3530();

private:
    static void fillRandomly(MissionHandlingStatus3530& mhs);

protected:
    static const int32_t nbOfRepeats = 100;
}; // MissionHandlingStatus3530TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

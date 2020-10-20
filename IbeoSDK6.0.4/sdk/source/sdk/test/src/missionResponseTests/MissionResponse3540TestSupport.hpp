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
#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/missionresponse/MissionResponse3540.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class MissionResponse3540TestSupport : public TestSupport
{
public:
    MissionResponse3540TestSupport();
    virtual ~MissionResponse3540TestSupport() = default;

public:
    static MissionResponse3540 createMissionResponse3540();

private:
    static void fillRandomly(MissionResponse3540& mhs);

protected:
    static const int32_t nbOfRepeats = 100;

}; // MissionResponse3540TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

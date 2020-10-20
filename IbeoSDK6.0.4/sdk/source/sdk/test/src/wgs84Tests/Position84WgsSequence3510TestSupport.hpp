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
//!\date Sept 04, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================
#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84Sequence3510.hpp>
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class PositionWgs84Sequence3510TestSupport : public TestSupport
{
public:
    PositionWgs84Sequence3510TestSupport()          = default;
    virtual ~PositionWgs84Sequence3510TestSupport() = default;

public:
    static PositionWgs84Sequence3510 createPositionWgs84Sequence3510();
    static void fillRandomly(PositionWgs84Sequence3510& ps);
    static void fillPosRandomly(PositionWgs84& p);

protected:
    static const int32_t nbOfRepeats = 100;

}; //PositionWgs84Sequence3510TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Feb 05, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84_2604.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class PositionWgs84_2604TestSupport : public TestSupport
{
public:
    PositionWgs84_2604TestSupport()          = default;
    virtual ~PositionWgs84_2604TestSupport() = default;

protected:
    static PositionWgs84::SourceType randomSourceType();

    //========================================
    //!\brief Fill a wgs84 instance with random values.
    //!\param[out] wgs              The wgs84 to be filled.
    //----------------------------------------
    static void fillRandomly(PositionWgs84& wgs);

protected:
    static const int32_t nbOfRepeats = 100000;
}; // PositionWgs84_2604TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

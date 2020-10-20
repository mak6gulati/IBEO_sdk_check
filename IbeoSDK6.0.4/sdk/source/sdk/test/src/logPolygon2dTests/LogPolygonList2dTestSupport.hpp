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
//!\date Mar 19, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/logpolygonlist2d/LogPolygonList2d.hpp>
#include <ibeo/common/sdk/datablocks/logpolygonlist2d/special/LogPolygonList2dFloat6817.hpp>

#include "common/TestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class LogPolygonList2dTestSupport : public TestSupport
{
public:
    LogPolygonList2dTestSupport()          = default;
    virtual ~LogPolygonList2dTestSupport() = default;

public:
    static void fillRandomly(LogPolygonList2d& lpl);
    static void fillRandomly(LogPolygonList2dFloat6817& lpl);

protected:
    static void fillRandomly(LogPolygon2d<float>& lp);

protected:
    static const int32_t nbOfRepeats = 100;
}; // LogPolygon2dFloat6817TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

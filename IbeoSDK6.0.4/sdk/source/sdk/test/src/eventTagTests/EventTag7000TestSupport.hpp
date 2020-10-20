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
//!\date Mar 21, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "wgs84Tests/PositionWgs84_2604TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/eventtag/EventTag7000.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class EventTag7000TestSupport : public PositionWgs84_2604TestSupport
{
public:
    EventTag7000TestSupport()          = default;
    virtual ~EventTag7000TestSupport() = default;

public:
    static EventTag7000 createIbeoEvent7000();

private:
    static void fillRandomly(EventTag7000& od);

    using PositionWgs84_2604TestSupport::fillRandomly;

protected:
    static const int32_t nbOfRepeats = 100;
}; // EventTag7000TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

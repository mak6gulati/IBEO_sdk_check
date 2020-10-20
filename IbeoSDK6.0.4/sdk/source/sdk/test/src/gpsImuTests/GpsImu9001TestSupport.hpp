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
//!\date Apr 07, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "GpsImuTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class GpsImu9001TestSupport : public GpsImuTestSupport
{
public:
    GpsImu9001TestSupport() : GpsImuTestSupport() {}
    ~GpsImu9001TestSupport() override = default;
}; // GpsImu9001TestSupport

//==============================================================================

template<>
void GpsImuTestSupport::fillRandomly(GpsImu9001& gpsImu);

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

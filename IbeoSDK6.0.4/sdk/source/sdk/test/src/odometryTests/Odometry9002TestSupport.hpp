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
//!\date Mar 28, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"
#include <odometryTests/OdometryTestSupport.hpp>
#include <ibeo/common/sdk/datablocks/odometry/special/Odometry9002.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class Odometry9002TestSupport : public OdometryTestSupport
{
public:
    Odometry9002TestSupport() : OdometryTestSupport() {}
    ~Odometry9002TestSupport() override = default;

}; // Odometry9002TestSupport

//==============================================================================

template<>
void OdometryTestSupport::fillRandomly(Odometry9002& od);

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

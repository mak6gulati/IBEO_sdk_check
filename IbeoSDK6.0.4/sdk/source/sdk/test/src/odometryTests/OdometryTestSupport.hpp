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
//!\date Jan 29th, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/odometry/Odometry.hpp>

//==============================================================================
//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class OdometryTestSupport : public TestSupport
{
public:
    OdometryTestSupport();
    ~OdometryTestSupport() override = default;

public:
    template<typename T>
    T createOdometry();

public:
    template<typename T>
    static void fillRandomly(T& vs);

protected:
    static const int32_t nbOfRepeats = 100;
}; // OdometryTestSupport

//==============================================================================

template<typename T>
T OdometryTestSupport::createOdometry()
{
    T odometry;
    fillRandomly(odometry);
    return odometry;
}

//==============================================================================

// specialization for Odometry
template<>
ibeo::common::sdk::Odometry OdometryTestSupport::createOdometry<Odometry>();

//==============================================================================

template<>
void OdometryTestSupport::fillRandomly(Odometry& od);

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

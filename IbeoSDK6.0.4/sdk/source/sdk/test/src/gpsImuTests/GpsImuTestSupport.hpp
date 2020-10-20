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
#include <ibeo/common/sdk/datablocks/gpsimu/GpsImu.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class GpsImuTestSupport : public TestSupport
{
public:
    GpsImuTestSupport();
    ~GpsImuTestSupport() override = default;

public:
    template<typename T>
    T createGpsImu();

public:
    template<typename T>
    static void fillRandomly(T& vs);

protected:
    static const int32_t nbOfRepeats = 100;
}; // GpsImuTestSupport

//==============================================================================

template<typename T>
T GpsImuTestSupport::createGpsImu()
{
    T gpsimu;
    fillRandomly(gpsimu);
    return gpsimu;
}

//==============================================================================

// specialization for GpsImu
template<>
ibeo::common::sdk::GpsImu GpsImuTestSupport::createGpsImu<GpsImu>();

//==============================================================================

template<>
void GpsImuTestSupport::fillRandomly(GpsImu& gpsImu);

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

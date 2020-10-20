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
//!\date March 23, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <common/TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2805.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2806.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2807.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2808.hpp>
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class VehicleStateTestSupport : public TestSupport
{
public:
    VehicleStateTestSupport()          = default;
    virtual ~VehicleStateTestSupport() = default;

    template<typename T>
    T createVehicleState();

public:
    template<typename T>
    static void fillRandomly(T& vs);

protected:
    static const int32_t nbOfRepeats = 100;

}; // VehicleStateTestSupport

//==============================================================================

template<typename T>
T VehicleStateTestSupport::createVehicleState()
{
    T vs;
    fillRandomly(vs);
    return vs;
}

template<>
void VehicleStateTestSupport::fillRandomly(VehicleState2805& vs);
template<>
void VehicleStateTestSupport::fillRandomly(VehicleState2806& vs);
template<>
void VehicleStateTestSupport::fillRandomly(VehicleState2807& vs);
template<>
void VehicleStateTestSupport::fillRandomly(VehicleState2808& vs);
template<>
void VehicleStateTestSupport::fillRandomly(VehicleState& vs);

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

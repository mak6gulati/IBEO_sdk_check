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
//!\date August 23, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/vehiclecontrol/VehicleControl9100.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class VehicleControl9100TestSupport : public TestSupport
{
public:
    virtual ~VehicleControl9100TestSupport() = default;

public:
    static VehicleControl9100 createVehicleControl9100();

private:
    static void fillRandomly(VehicleControl9100& vc);

protected:
    static const uint32_t nbOfRepeats = 100;
}; // VehicleControl9100TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Sept 05, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include "common/TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/destination/Destination3520.hpp>
#include <wgs84Tests/PositionWgs84_2604TestSupport.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class Destination3520TestSupport : public PositionWgs84_2604TestSupport
{
public:
    Destination3520TestSupport();
    virtual ~Destination3520TestSupport() = default;

public:
    static Destination3520 createDestination3520();

private:
    static void fillRandomly(Destination3520& d);

protected:
    static const int32_t nbOfRepeats = 100;
}; // Destination3520TestSupport

//==============================================================================

} //namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo

// ==============================================================================

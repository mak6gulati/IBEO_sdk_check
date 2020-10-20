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
//!\date Mar 16, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/stateofoperation/StateOfOperation9110.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

StateOfOperation9110::StateOfOperation9110() : SpecializedDataContainer() {}

//==============================================================================

StateOfOperation9110::~StateOfOperation9110() {}

//==============================================================================

bool operator==(const StateOfOperation9110& lhs, const StateOfOperation9110& rhs)
{
    return lhs.getTimestamp() == rhs.getTimestamp() && lhs.getOperation() == rhs.getOperation()
           && lhs.getDriverInterrupt() == rhs.getDriverInterrupt()
           && lhs.getTakeOverRequest() == rhs.getTakeOverRequest() && lhs.getReserved() == rhs.getReserved();
}

//==============================================================================

bool operator!=(const StateOfOperation9110& lhs, const StateOfOperation9110& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

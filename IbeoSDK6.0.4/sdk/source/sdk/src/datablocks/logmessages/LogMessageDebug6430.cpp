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
//!\date Mar 14, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/logmessages/LogMessageDebug6430.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

LogMessageDebug6430::LogMessageDebug6430() : LogMessage64x0Base{}, SpecializedDataContainer{} {}

//==============================================================================

bool operator==(const LogMessageDebug6430& lhs, const LogMessageDebug6430& rhs)
{
    return (lhs.getMessage() == rhs.getMessage());
}

//==============================================================================

bool operator!=(const LogMessageDebug6430& lhs, const LogMessageDebug6430& rhs)
{
    return (lhs.getMessage() != rhs.getMessage());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

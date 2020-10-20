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

#include <ibeo/common/sdk/datablocks/logmessages/LogMessageWarning6410.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

LogMessageWarning6410::LogMessageWarning6410() : LogMessage64x0Base{}, SpecializedDataContainer{} {}

//==============================================================================

bool operator==(const LogMessageWarning6410& lhs, const LogMessageWarning6410& rhs)
{
    return (lhs.getMessage() == rhs.getMessage());
}

//==============================================================================

bool operator!=(const LogMessageWarning6410& lhs, const LogMessageWarning6410& rhs)
{
    return (lhs.getMessage() != rhs.getMessage());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

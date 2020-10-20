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

#include <ibeo/common/sdk/datablocks/logmessages/LogMessageNote6420.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

LogMessageNote6420::LogMessageNote6420() : LogMessage64x0Base{}, SpecializedDataContainer{} {}

//==============================================================================

bool operator==(const LogMessageNote6420& lhs, const LogMessageNote6420& rhs)
{
    return (lhs.getMessage() == rhs.getMessage());
}

//==============================================================================

bool operator!=(const LogMessageNote6420& lhs, const LogMessageNote6420& rhs)
{
    return (lhs.getMessage() != rhs.getMessage());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

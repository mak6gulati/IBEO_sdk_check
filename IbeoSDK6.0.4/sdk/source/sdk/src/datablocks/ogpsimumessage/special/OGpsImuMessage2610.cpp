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
//!\date Jan 29, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/ogpsimumessage/special/OGpsImuMessage2610.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

OGpsImuMessage2610::OGpsImuMessage2610() : SpecializedDataContainer() {}

//==============================================================================

OGpsImuMessage2610::~OGpsImuMessage2610() {}

//==============================================================================

bool operator==(const OGpsImuMessage2610& lhs, const OGpsImuMessage2610& rhs)
{
    return (lhs.getIpAddress() == rhs.getIpAddress()) && (lhs.getData() == rhs.getData());
}

//==============================================================================

bool operator!=(const OGpsImuMessage2610& lhs, const OGpsImuMessage2610& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

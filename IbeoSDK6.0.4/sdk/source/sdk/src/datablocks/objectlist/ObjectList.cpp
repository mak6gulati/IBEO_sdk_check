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
//!\date Apr 9, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectlist/ObjectList.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

bool operator==(const ObjectList& lhs, const ObjectList& rhs)
{
    return (lhs.getTimestamp() == rhs.getTimestamp()) && (lhs.getObjectListId() == rhs.getObjectListId())
           && (lhs.getFlags() == rhs.getFlags()) && (lhs.getDeviceType() == rhs.getDeviceType())
           && (lhs.getDeviceInterfaceVersion() == rhs.getDeviceInterfaceVersion())
           && (lhs.getObjects() == rhs.getObjects());
}

//==============================================================================

bool operator!=(const ObjectList& lhs, const ObjectList& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

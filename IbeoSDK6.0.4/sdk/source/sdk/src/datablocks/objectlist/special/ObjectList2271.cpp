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
//!\date Jan 17, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2271.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ObjectList2271::ObjectList2271() : SpecializedDataContainer(), m_scanStartTimestamp{0} {}

//==============================================================================

ObjectList2271::ObjectList2271(const NTPTime scanStartTimeStamp)
  : SpecializedDataContainer(), m_scanStartTimestamp{scanStartTimeStamp}
{}

//==============================================================================

ObjectList2271::~ObjectList2271() {}

//==============================================================================

bool operator==(const ObjectList2271& lhs, const ObjectList2271& rhs)
{
    return (lhs.getScanStartTimestamp() == rhs.getScanStartTimestamp()) && (lhs.getScanNumber() == rhs.getScanNumber())
           && (lhs.getObjectListId() == rhs.getObjectListId()) && (lhs.getDeviceId() == rhs.getDeviceId())
           && (lhs.getDeviceInterfaceVersion() == rhs.getDeviceInterfaceVersion())
           && (lhs.getReserved() == rhs.getReserved()) && (lhs.getObjects() == rhs.getObjects());
}

//==============================================================================

bool operator!=(const ObjectList2271& lhs, const ObjectList2271& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

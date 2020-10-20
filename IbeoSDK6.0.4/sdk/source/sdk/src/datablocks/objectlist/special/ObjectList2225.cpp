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

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2225.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ObjectList2225::ObjectList2225() : SpecializedDataContainer() {}

//==============================================================================

ObjectList2225::~ObjectList2225() {}

//==============================================================================

//==============================================================================

bool operator==(const ObjectList2225& lhs, const ObjectList2225& rhs)
{
    return (lhs.getTimestamp() == rhs.getTimestamp()) && (lhs.getObjects() == rhs.getObjects());
}

//==============================================================================

bool operator!=(const ObjectList2225& lhs, const ObjectList2225& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

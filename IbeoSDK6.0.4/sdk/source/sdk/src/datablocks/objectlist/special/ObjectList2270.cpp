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

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2270.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ObjectList2270::ObjectList2270() : SpecializedDataContainer(), m_scanStartTimestamp{0} {}

//==============================================================================

ObjectList2270::ObjectList2270(const NTPTime scanStartTimeStamp)
  : SpecializedDataContainer(), m_scanStartTimestamp{scanStartTimeStamp}
{}

//==============================================================================

ObjectList2270::~ObjectList2270() {}

//==============================================================================

//==============================================================================

bool operator==(const ObjectList2270& lhs, const ObjectList2270& rhs)
{
    return (lhs.getScanStartTimestamp() == rhs.getScanStartTimestamp()) && (lhs.getScanNumber() == rhs.getScanNumber())
           && (lhs.getObjects() == rhs.getObjects());
}

//==============================================================================

bool operator!=(const ObjectList2270& lhs, const ObjectList2270& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

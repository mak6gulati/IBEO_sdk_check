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

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2281.hpp>
#include <ibeo/common/sdk/DataBlockBufferProvider.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ObjectList2281::ObjectList2281() : SpecializedDataContainer() {}

//==============================================================================

ObjectList2281::~ObjectList2281() {}

//==============================================================================

//==============================================================================

template<>
void readBE<ObjectList2281::DeviceType>(std::istream& is, ObjectList2281::DeviceType& dt)
{
    uint8_t rd8;
    readBE(is, rd8);
    dt = ObjectList2281::DeviceType(rd8);
}

//==============================================================================

template<>
void writeBE<ObjectList2281::DeviceType>(std::ostream& os, const ObjectList2281::DeviceType& dt)
{
    writeBE(os, uint8_t(dt));
}

//==============================================================================

//==============================================================================

bool operator==(const ObjectList2281& lhs, const ObjectList2281& rhs)
{
    return (lhs.getTimestamp() == rhs.getTimestamp()) && (lhs.getObjectListId() == rhs.getObjectListId())
           && (lhs.getDeviceType() == rhs.getDeviceType())
           && (lhs.getDeviceInterfaceVersion() == rhs.getDeviceInterfaceVersion()) && (lhs.getFlags() == rhs.getFlags())
           && (lhs.getReserved1() == rhs.getReserved1()) && (lhs.getObjects() == rhs.getObjects());
}

//==============================================================================

bool operator!=(const ObjectList2281& lhs, const ObjectList2281& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

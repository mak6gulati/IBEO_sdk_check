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

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2291.hpp>
#include <ibeo/common/sdk/DataBlockBufferProvider.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ObjectList2291::ObjectList2291() : SpecializedDataContainer() {}

//==============================================================================

ObjectList2291::~ObjectList2291() {}

//==============================================================================

//==============================================================================

template<>
void readBE<ObjectList2291::DeviceType>(std::istream& is, ObjectList2291::DeviceType& dt)
{
    uint8_t rd8;
    readBE(is, rd8);
    dt = ObjectList2291::DeviceType(rd8);
}

//==============================================================================

template<>
void writeBE<ObjectList2291::DeviceType>(std::ostream& os, const ObjectList2291::DeviceType& dt)
{
    writeBE(os, uint8_t(dt));
}

//==============================================================================

//==============================================================================

bool operator==(const ObjectList2291& lhs, const ObjectList2291& rhs)
{
    return (lhs.getTimestamp() == rhs.getTimestamp()) && (lhs.getObjectListId() == rhs.getObjectListId())
           && (lhs.getDeviceType() == rhs.getDeviceType())
           && (lhs.getDeviceInterfaceVersion() == rhs.getDeviceInterfaceVersion()) && (lhs.getFlags() == rhs.getFlags())
           && (lhs.getReserved1() == rhs.getReserved1()) && (lhs.getObjects() == rhs.getObjects());
}

//==============================================================================

bool operator!=(const ObjectList2291& lhs, const ObjectList2291& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

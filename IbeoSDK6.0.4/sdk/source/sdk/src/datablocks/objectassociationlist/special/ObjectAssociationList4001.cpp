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
//!\date Mar 20, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectassociationlist/special/ObjectAssociationList4001.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ObjectAssociationList4001::ObjectAssociationList4001() : SpecializedDataContainer{} {}

//==============================================================================

ObjectAssociationList4001::~ObjectAssociationList4001() {}

//==============================================================================

//==============================================================================

bool operator==(const ObjectAssociationList4001& lhs, const ObjectAssociationList4001& rhs)
{
    if (lhs.getRefObjListId() != rhs.getRefObjListId())
        return false;
    if (lhs.getRefDevType() != rhs.getRefDevType())
        return false;
    if (lhs.getRefDevInterfaceVersion() != rhs.getRefDevInterfaceVersion())
        return false;

    if (lhs.getDutObjListId() != rhs.getDutObjListId())
        return false;
    if (lhs.getDutDevType() != rhs.getDutDevType())
        return false;
    if (lhs.getDutDevInterfaceVersion() != rhs.getDutDevInterfaceVersion())
        return false;

    if (lhs.getReserved() != rhs.getReserved())
    {
        return false;
    }

    return lhs.getObjectAssociations() == rhs.getObjectAssociations();
}

//==============================================================================

bool operator!=(const ObjectAssociationList4001& lhs, const ObjectAssociationList4001& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

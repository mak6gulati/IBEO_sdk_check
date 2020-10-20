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
//!\date Apr 26, 2016
//------------------------------------------------------------------------------

//==============================================================================

#include "ObjectAssociationList4001TestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

ObjectAssociationList4001TestSupport::ObjectAssociationList4001TestSupport() : TestSupport() {}

//==============================================================================

ObjectAssociationList4001TestSupport::~ObjectAssociationList4001TestSupport() {}

//==============================================================================

ibeo::common::sdk::ObjectAssociationList4001 ObjectAssociationList4001TestSupport::createAssocList()
{
    ObjectAssociationList4001 oal;
    fillRandomly(oal);
    return oal;
}

//==============================================================================

ibeo::common::sdk::ObjectAssociationIn4001 ObjectAssociationList4001TestSupport::createAssoc()
{
    ObjectAssociationIn4001 oa;
    fillRandomly(oa);
    return oa;
}

//==============================================================================

void ObjectAssociationList4001TestSupport::fillRandomly(ObjectAssociationList4001& oal)
{
    using C = ObjectAssociationList4001;

    oal.setRefObjListId(getRandValue<uint8_t>());
    oal.setRefDevType(getRandValue<uint8_t>());
    oal.setRefDevInterfaceVersion(getRandValue<uint16_t>(C::devInterfaceVersionMask));

    oal.setDutObjListId(getRandValue<uint8_t>());
    oal.setDutDevType(getRandValue<uint8_t>());
    oal.setDutDevInterfaceVersion(getRandValue<uint16_t>(C::devInterfaceVersionMask));

    for (uint8_t i = 0; i < C::nbOfReserved; ++i)
    {
        oal.setReserved(i, getRandValue<char>());
    }

    const uint32_t nbOfAssocs = getRandValue<uint32_t>(0x3FF);

    C::ObjAssocVector& oav = oal.getObjectAssociations();
    oav.resize(nbOfAssocs);

    C::ObjAssocVector::iterator oaIter = oav.begin();
    for (; oaIter != oav.end(); ++oaIter)
    {
        fillRandomly(*oaIter);
    }
}

//==============================================================================

void ObjectAssociationList4001TestSupport::fillRandomly(ibeo::common::sdk::ObjectAssociationIn4001& oa)
{
    oa.setRefObjId(getRandValue<uint32_t>());
    oa.setDutObjId(getRandValue<uint32_t>());
    oa.setTimestampFirst(getRandValue<NTPTime>());
    oa.setTimestampLast(getRandValue<NTPTime>());
    oa.setCertainty(getRandValue<float>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

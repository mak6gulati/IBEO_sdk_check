//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Jan 25, 2019
//------------------------------------------------------------------------------

//==============================================================================

#include "ObjectAssociationListTestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

ObjectAssociationListTestSupport::ObjectAssociationListTestSupport() : TestSupport() {}

//==============================================================================

ObjectAssociationListTestSupport::~ObjectAssociationListTestSupport() {}

//==============================================================================

ibeo::common::sdk::ObjectAssociationList ObjectAssociationListTestSupport::createAssocList()
{
    ObjectAssociationList oal;
    fillRandomly(oal);
    return oal;
}

//==============================================================================

ibeo::common::sdk::ObjectAssociation ObjectAssociationListTestSupport::createAssoc()
{
    ObjectAssociation oa;
    fillRandomly(oa);
    return oa;
}

//==============================================================================

void ObjectAssociationListTestSupport::fillRandomly(ObjectAssociationList& oal)
{
    using C = ObjectAssociationList;

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

void ObjectAssociationListTestSupport::fillRandomly(ibeo::common::sdk::ObjectAssociation& oa)
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

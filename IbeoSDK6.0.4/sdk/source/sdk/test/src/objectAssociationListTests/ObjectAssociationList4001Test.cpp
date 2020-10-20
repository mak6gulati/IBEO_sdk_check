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

#include "ObjectAssociationList4001TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectassociationlist/special/ObjectAssociationList4001Exporter4001.hpp>
#include <ibeo/common/sdk/datablocks/objectassociationlist/special/ObjectAssociationList4001Importer4001.hpp>

#define BOOST_TEST_MODULE ObjectAssociationList4001Test
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(ObjectAssociationList4001Suite)

//==============================================================================

class Fixture : public unittests::ObjectAssociationList4001TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(creationObjectAssociation4001, Fixture)
{
    ibeo::common::sdk::ObjectAssociationIn4001 oa;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(creationObjectAssociationList4001, Fixture)
{
    ibeo::common::sdk::ObjectAssociationList4001 oal;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoObjAssoc4001Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ObjectAssociationIn4001 oaOrig(createAssoc());

        std::stringstream ss;
        BOOST_CHECK(oaOrig.serialize(ss));

        ObjectAssociationIn4001 oaCopy;
        BOOST_CHECK(oaCopy.deserialize(ss));

        BOOST_CHECK(oaOrig == oaCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoObjAssoc4001ListIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ObjectAssociationList4001Exporter4001 exporter;
        ObjectAssociationList4001 oalOrig(createAssocList());

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(oalOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, oalOrig));

        ObjectAssociationList4001 oalCopy;
        ObjectAssociationList4001Importer4001 importer;
        BOOST_CHECK(importer.deserialize(ss, oalCopy, dh));

        BOOST_CHECK(oalOrig == oalCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

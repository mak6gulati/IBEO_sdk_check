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

#include "ObjectAssociationListTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectassociationlist/ObjectAssociationListExporter4001.hpp>
#include <ibeo/common/sdk/datablocks/objectassociationlist/ObjectAssociationListImporter4001.hpp>

#define BOOST_TEST_MODULE ObjectAssociationListTest
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(ObjectAssociationListSuite)

//==============================================================================

class Fixture : public unittests::ObjectAssociationListTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(creationObjectAssociation, Fixture)
{
    ibeo::common::sdk::ObjectAssociation oa;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(creationObjectAssociationList, Fixture)
{
    ibeo::common::sdk::ObjectAssociationList oal;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoObjAssocIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ObjectAssociation oaOrig(createAssoc());

        std::stringstream ss;
        BOOST_CHECK(oaOrig.serialize(ss));

        ObjectAssociation oaCopy;
        BOOST_CHECK(oaCopy.deserialize(ss));

        BOOST_CHECK(oaOrig == oaCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoObjAssocListIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ObjectAssociationListExporter4001 exporter;
        ObjectAssociationList oalOrig(createAssocList());

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(oalOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, oalOrig));

        ObjectAssociationList oalCopy;
        ObjectAssociationListImporter4001 importer;
        BOOST_CHECK(importer.deserialize(ss, oalCopy, dh));

        BOOST_CHECK(oalOrig == oalCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

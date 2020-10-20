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

#include "ObjectLabelListTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectlabellist/ObjectLabelListExporter6503.hpp>
#include <ibeo/common/sdk/datablocks/objectlabellist/ObjectLabelListImporter6503.hpp>

#define BOOST_TEST_MODULE ObjectLabelListTest
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ObjectLabelListTestSuite)

//==============================================================================

class Fixture : public unittests::ObjectLabelListTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createObjectLabel, Fixture)
{
    ibeo::common::sdk::ObjectLabel oa;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createObjectLabelList, Fixture)
{
    ibeo::common::sdk::ObjectLabelList oal;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoObjLabelIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ObjectLabel oaOrig(createObjectLabel());

        std::stringstream ss;
        BOOST_CHECK(oaOrig.serialize(ss));

        ObjectLabel oaCopy;
        BOOST_CHECK(oaCopy.deserialize(ss));

        BOOST_CHECK(oaOrig == oaCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoObjLabelListIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ObjectLabelListExporter6503 exporter;
        ObjectLabelList oalOrig(createObjectLabelList());

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(oalOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, oalOrig));

        ObjectLabelList oalCopy;
        const ObjectLabelListImporter6503 importer;
        BOOST_CHECK(importer.deserialize(ss, oalCopy, dh));

        BOOST_CHECK(oalOrig == oalCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

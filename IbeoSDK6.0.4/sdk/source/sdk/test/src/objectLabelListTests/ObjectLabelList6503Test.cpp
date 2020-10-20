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
//!\date Apr 28, 2016
//------------------------------------------------------------------------------

#include "ObjectLabelList6503TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectlabellist/special/ObjectLabelList6503Exporter6503.hpp>
#include <ibeo/common/sdk/datablocks/objectlabellist/special/ObjectLabelList6503Importer6503.hpp>

#define BOOST_TEST_MODULE ObjectLabelList6503Test
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ObjectLabelList6503TestSuite)

//==============================================================================

class Fixture : public unittests::ObjectLabelList6503TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createObjectLabel6503, Fixture)
{
    ibeo::common::sdk::ObjectLabelIn6503 oa;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createObjectLabelList6503, Fixture)
{
    ibeo::common::sdk::ObjectLabelList6503 oal;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoObjLabel6503Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ObjectLabelIn6503 oaOrig(createObjectLabel6503());

        std::stringstream ss;
        BOOST_CHECK(oaOrig.serialize(ss));

        ObjectLabelIn6503 oaCopy;
        BOOST_CHECK(oaCopy.deserialize(ss));

        BOOST_CHECK(oaOrig == oaCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoObjLabelList6503Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ObjectLabelList6503Exporter6503 exporter;
        ObjectLabelList6503 oalOrig(createObjectLabelList6503());

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(oalOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, oalOrig));

        ObjectLabelList6503 oalCopy;
        const ObjectLabelList6503Importer6503 importer;
        BOOST_CHECK(importer.deserialize(ss, oalCopy, dh));

        BOOST_CHECK(oalOrig == oalCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

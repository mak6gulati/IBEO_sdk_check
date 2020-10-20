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
//!\date Sep 29, 2015
//------------------------------------------------------------------------------

//==============================================================================

#include "ObjectList2271TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2271Importer2271.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2271Exporter2271.hpp>

#define BOOST_TEST_MODULE ObjectListScala2271Test
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ObjectListScala2271Suite)

//==============================================================================

class Fixture : public unittests::ObjectListScala2271TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentity, Fixture)
{
    for (int i = 0; i < 100; ++i)
    {
        ObjectList2271 objListOrig = createObjList();
        const ObjectList2271Exporter2271 exporter;

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(objListOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, objListOrig));

        ObjectList2271 objListCopy;
        const ObjectList2271Importer2271 importer;
        BOOST_CHECK(importer.deserialize(ss, objListCopy, dh));
        BOOST_CHECK(objListOrig == objListCopy);
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isEqualNotNonEqual, Fixture)
{
    for (int i = 0; i < 100; ++i)
    {
        ObjectList2271 objListOrig = createObjList();

        BOOST_CHECK(objListOrig == objListOrig);
        BOOST_CHECK(!(objListOrig != objListOrig));
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

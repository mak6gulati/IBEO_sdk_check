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
//!\date Apr 25, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2280.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2280Exporter2280.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2280Importer2280.hpp>

#include <objectListTests/ObjectListTestSupport.hpp>

#define BOOST_TEST_MODULE ObjectListTest
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ObjectListBasicTestSuite)

//==============================================================================

class Fixture : public unittests::ObjectListTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createObjectList2280, Fixture)
{
    ObjectList2280 objList;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoObjectList2280Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ObjectList2280Exporter2280 exporter;
        ObjectList2280 orig(createObjectList<ObjectList2280>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, orig));

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(orig)), 0, NTPTime());

        ObjectList2280 copy;
        BOOST_CHECK(orig != copy);

        const ObjectList2280Importer2280 importer;
        BOOST_CHECK(importer.deserialize(ss, copy, dh));
        BOOST_CHECK(orig == copy);
    } // for r
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoObjectList2280Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ObjectList2280 orig(createObjectList<ObjectList2280>());
        ObjectList2280 copy;

        copy = orig;
        BOOST_CHECK(orig == copy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

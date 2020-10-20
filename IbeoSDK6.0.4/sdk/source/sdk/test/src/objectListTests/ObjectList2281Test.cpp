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

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2281.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2281Exporter2281.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2281Importer2281.hpp>

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

BOOST_FIXTURE_TEST_CASE(createObjectList2281, Fixture)
{
    ObjectList2281 objList;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoObjectList2281Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ObjectList2281Exporter2281 exporter;
        ObjectList2281 orig(createObjectList<ObjectList2281>());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, orig));

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(orig)), 0, NTPTime());

        ObjectList2281 copy;
        BOOST_CHECK(orig != copy);

        const ObjectList2281Importer2281 importer;
        BOOST_CHECK(importer.deserialize(ss, copy, dh));
        BOOST_CHECK(orig == copy);
    } // for r
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoObjectList2281Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ObjectList2281 orig(createObjectList<ObjectList2281>());
        ObjectList2281 copy;

        copy = orig;
        BOOST_CHECK(orig == copy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

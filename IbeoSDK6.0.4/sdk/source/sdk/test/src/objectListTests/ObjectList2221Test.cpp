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
//! \date Jan 10, 2019
//------------------------------------------------------------------------------

#include "ObjectListTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2221Importer2221.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2221Exporter2221.hpp>

#define BOOST_TEST_MODULE ObjectList2221Test
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ObjectList2221Suite)

//==============================================================================

class Fixture : public unittests::ObjectListTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isSerializationDeserializationIdentity, Fixture)
{
    for (int i = 0; i < ObjectListTestSupport::nbOfRepeats; ++i)
    {
        ObjectList2221 objListOrig{createObjectList<ObjectList2221>()};

        const ObjectList2221Exporter2221 exporter;
        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(objListOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, objListOrig));

        ObjectList2221 objListCopy;

        const ObjectList2221Importer2221 importer;
        BOOST_CHECK(importer.deserialize(ss, objListCopy, dh));

        BOOST_CHECK(objListOrig == objListCopy);
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isEqualNotNonEqual, Fixture)
{
    for (int i = 0; i < ObjectListTestSupport::nbOfRepeats; ++i)
    {
        ObjectList2221 objListOrig{createObjectList<ObjectList2221>()};

        BOOST_CHECK(objListOrig == objListOrig);
        BOOST_CHECK(!(objListOrig != objListOrig));
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

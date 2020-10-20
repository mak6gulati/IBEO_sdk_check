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
//!\date Jan 12, 2018
//!//---------------------------------------------------------------------------

#include "common/RectangleTestSupport.hpp"

#define BOOST_TEST_MODULE RectangleTest
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(RectangleTestSuite)

//==============================================================================

class Fixture : public unittests::RectangleTestSupport
{
}; // Fixture

//==============================================================================

using test_types_all
    = boost::mpl::list<uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t, float, double>;

using test_types_serialization = boost::mpl::list<int16_t, float>;

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(checkConstructor, T, test_types_all)
{
    Rectangle<T> v;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(checkSerialization, T, test_types_serialization)
{
    // TODO This currently does not test, that the serialization is correct
    // it just checks, that reading and writing fit together
    // it should also be tested, that the serialized content is correct
    using namespace ibeo::common::sdk::unittests;
    for (int32_t r = 0; r < 100; ++r)
    {
        auto v = RectangleTestSupport::createRectangle<T>();
        std::stringstream ssBE, ssLE;

        // Big endian
        writeBE(ssBE, v);
        Rectangle<T> vCopy;
        readBE(ssBE, vCopy);
        BOOST_CHECK(v == vCopy);
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkSerializedSize, Fixture)
{
    auto vi16 = Rectangle<int16_t>{};
    BOOST_CHECK(ibeo::common::sdk::serializedSize(vi16) == 10);

    auto vf = Rectangle<float>{};
    BOOST_CHECK(ibeo::common::sdk::serializedSize(vf) == 20);
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

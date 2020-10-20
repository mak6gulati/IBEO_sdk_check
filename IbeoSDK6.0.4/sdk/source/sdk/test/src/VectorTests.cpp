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
//------------------------------------------------------------------------------

#include "common/VectorTestSupport.hpp"

#define BOOST_TEST_MODULE VectorTests
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(VectorTestSuite)

//==============================================================================

class Fixture : public unittests::VectorTestSupport
{
}; // Fixture

//==============================================================================

using test_types_all
    = boost::mpl::list<uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t, float, double>;

using test_types_serialization_v2 = boost::mpl::list<uint16_t, int16_t, float>;
using test_types_serialization_v3 = boost::mpl::list<float, double>;

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(checkConstructors, T, test_types_all)
{
    Vector2<T> v2;
    Vector3<T> v3;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(checkSerializationV2, T, test_types_serialization_v2)
{
    // TODO This currently does not test, that the serialization is correct
    // it just checks, that reading and writing fit together
    // it should also be tested, that the serialized content is correct
    using namespace ibeo::common::sdk::unittests;
    for (int32_t r = 0; r < 100; ++r)
    {
        auto v = VectorTestSupport::createVector2<T>();
        std::stringstream ssBE, ssLE;

        // Big endian
        writeBE(ssBE, v);
        Vector2<T> vCopy;
        readBE(ssBE, vCopy);
        BOOST_CHECK(v == vCopy);

        writeLE(ssLE, v);
        readLE(ssLE, vCopy);
        BOOST_CHECK(v == vCopy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(checkSerializationV3, T, test_types_serialization_v3)
{
    // TODO This currently does not test, that the serialization is correct
    // it just checks, that reading and writing fit together
    // it should also be tested, that the serialized content is correct
    using namespace ibeo::common::sdk::unittests;
    for (int32_t r = 0; r < 100; ++r)
    {
        auto v = VectorTestSupport::createVector3<T>();
        std::stringstream ssBE, ssLE;

        // Big endian
        writeBE(ssBE, v);
        Vector3<T> vCopy;
        readBE(ssBE, vCopy);
        BOOST_CHECK(v == vCopy);
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkSerializedSizeV2, Fixture)
{
    auto vui16 = Vector2<uint16_t>{};
    BOOST_CHECK(ibeo::common::sdk::serializedSize(vui16) == 4);

    auto vi16 = Vector2<int16_t>{};
    BOOST_CHECK(ibeo::common::sdk::serializedSize(vi16) == 4);

    auto vf = Vector2<float>{};
    BOOST_CHECK(ibeo::common::sdk::serializedSize(vf) == 8);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkSerializedSizeV3, Fixture)
{
    auto vi16 = Vector3<double>{};
    BOOST_CHECK(ibeo::common::sdk::serializedSize(vi16) == 24);

    auto vf = Vector3<float>{};
    BOOST_CHECK(ibeo::common::sdk::serializedSize(vf) == 12);
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

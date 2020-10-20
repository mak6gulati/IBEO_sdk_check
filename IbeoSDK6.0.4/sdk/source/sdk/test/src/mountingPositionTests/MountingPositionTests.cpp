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
//! \date Jan 12, 2018
//------------------------------------------------------------------------------

#include "MountingPositionTestSupport.hpp"
#include <ibeo/common/sdk/datablocks/MountingPosition.hpp>

#define BOOST_TEST_MODULE MountingPositionTests
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(MountingPositionTestSuite)

//==============================================================================

class Fixture : public unittests::MountingPositionTestSupport
{
}; // Fixture

using test_types = boost::mpl::list<int16_t, float>;

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(checkConstructors, T, test_types)
{
    MountingPosition<T> mp;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_AUTO_TEST_CASE_TEMPLATE(checkSerialization, T, test_types)
{
    // TODO This currently does not test, that the serialization is correct
    // it just checks, that reading and writing fit together
    // it should also be tested, that the serialized content is correct
    using namespace ibeo::common::sdk::unittests;
    for (int32_t r = 0; r < 100; ++r)
    {
        auto v = MountingPositionTestSupport::createMountingPosition<T>();
        std::stringstream ssBE;

        // Big endian
        writeBE(ssBE, v);
        MountingPosition<T> vCopy;
        readBE(ssBE, vCopy);
        BOOST_CHECK(v == vCopy);
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkSerializedSize, Fixture)
{
    auto mpi16 = MountingPosition<int16_t>{};
    BOOST_CHECK(ibeo::common::sdk::serializedSize(mpi16) == 12);

    auto mpf = MountingPosition<float>{};
    BOOST_CHECK(ibeo::common::sdk::serializedSize(mpf) == 24);
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

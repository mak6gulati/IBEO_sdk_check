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
//!\date Feb 24, 2017
//------------------------------------------------------------------------------

#include "Odometry9002TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/odometry/special/Odometry9002Exporter9002.hpp>
#include <ibeo/common/sdk/datablocks/odometry/special/Odometry9002Importer9002.hpp>

#define BOOST_TEST_MODULE OdometryTest9002
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(OdometryTestSuite9002)

//==============================================================================

class Fixture : public unittests::Odometry9002TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoOdometryIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Odometry9002 odOrig(createOdometry<Odometry9002>());

        Odometry9002Exporter9002 exporter;
        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, odOrig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(odOrig)), 0U, NTPTime());

        Odometry9002Importer9002 importer;
        Odometry9002 odCopy;
        BOOST_CHECK(importer.deserialize(ss, odCopy, dh));
        BOOST_CHECK(odCopy == odOrig);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkReserved, Fixture)
{
    Odometry9002 odOrig(createOdometry<Odometry9002>());
    auto& res = odOrig.getReserved();

    for (uint8_t r = 0; r < Odometry9002::nbOfReserved; ++r)
    {
        BOOST_CHECK(res[r] == 0);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

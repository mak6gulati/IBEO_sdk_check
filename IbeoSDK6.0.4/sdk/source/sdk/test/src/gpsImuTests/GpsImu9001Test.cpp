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
//!\date Apr 07, 2017
//------------------------------------------------------------------------------

#include "GpsImu9001TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001Exporter9001.hpp>
#include <ibeo/common/sdk/datablocks/gpsimu/special/GpsImu9001Importer9001.hpp>

#define BOOST_TEST_MODULE GpsImuTest9001
#include <boost/test/unit_test.hpp>

//==============================================================================

BOOST_AUTO_TEST_SUITE(GpsImuTestSuite9001)

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

class Fixture : public unittests::GpsImu9001TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoGpsImuIdentityCC, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const GpsImu9001Exporter9001 exporter;
        GpsImu9001 gpsImuOrig(createGpsImu<GpsImu9001>());

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(gpsImuOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, gpsImuOrig));

        GpsImu9001 gpsImuCopy;
        const GpsImu9001Importer9001 importer;
        BOOST_CHECK(importer.deserialize(ss, gpsImuCopy, dh));

        BOOST_CHECK(gpsImuCopy == gpsImuOrig);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

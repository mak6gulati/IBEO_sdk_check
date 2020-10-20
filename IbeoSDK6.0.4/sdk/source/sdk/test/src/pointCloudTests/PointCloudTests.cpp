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
//! \date Jan 08, 2019
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/pointcloud/PointCloudExporter7510.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/PointCloudImporter7510.hpp>
#include <pointCloudTests/PointCloudTestSupport.hpp>

#define BOOST_TEST_MODULE PointCloudTests
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(PointCloudPlaneTestSuite)

//==============================================================================

class Fixture : public unittests::PointCloudTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoPointCloudIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        PointCloud pcpOrig;
        fillRandomly(pcpOrig);

        const PointCloudExporter7510 exporter;
        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(pcpOrig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, pcpOrig));

        PointCloud pcpCopy;
        const PointCloudImporter7510 importer;
        BOOST_CHECK(importer.deserialize(ss, pcpCopy, dh));

        BOOST_CHECK(pcpOrig == pcpCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

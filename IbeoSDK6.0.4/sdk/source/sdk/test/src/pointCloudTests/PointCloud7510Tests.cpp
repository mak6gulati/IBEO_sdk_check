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
//!\date Mar 19, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloud7510Exporter7510.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloud7510Importer7510.hpp>
#include <pointCloudTests/PointCloudTestSupport.hpp>

#define BOOST_TEST_MODULE PointCloud7510Tests
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(PointCloudPlane7510TestSuite)

//==============================================================================

class Fixture : public unittests::PointCloudTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoPointCloudPlane7510Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        PointCloud7510 pcpOrig;
        fillRandomly(pcpOrig);

        const PointCloud7510Exporter7510 exporter;
        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(pcpOrig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, pcpOrig));

        PointCloud7510 pcpCopy;
        const PointCloud7510Importer7510 importer;
        BOOST_CHECK(importer.deserialize(ss, pcpCopy, dh));

        BOOST_CHECK(pcpOrig == pcpCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

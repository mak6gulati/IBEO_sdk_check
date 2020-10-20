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

#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloud7500Exporter7500.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloud7500Importer7500.hpp>
#include <pointCloudTests/PointCloudTestSupport.hpp>

#define BOOST_TEST_MODULE PointCloud7500Tests
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(PointCloudGlobal7500TestSuite)

//==============================================================================

class Fixture : public unittests::PointCloudTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoPointCloudGlobal7500Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        PointCloud7500 pcpOrig;
        fillRandomly(pcpOrig);

        const PointCloud7500Exporter7500 exporter;
        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(pcpOrig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, pcpOrig));

        PointCloud7500 pcpCopy;
        const PointCloud7500Importer7500 importer;
        BOOST_CHECK(importer.deserialize(ss, pcpCopy, dh));

        BOOST_CHECK(pcpOrig == pcpCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

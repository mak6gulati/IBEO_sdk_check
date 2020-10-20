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
//! \date Jan 25, 2019
//------------------------------------------------------------------------------

#include "DeviceStatusTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301Exporter6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301Importer6301.hpp>

#define BOOST_TEST_MODULE DeviceStatus6301Test
#include <boost/test/unit_test.hpp>

#include <vector>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(DeviceStatus6301TestSuite)

//==============================================================================

class Fixture : public unittests::DeviceStatusTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createDeviceStatus6301, Fixture)
{
    ibeo::common::sdk::DeviceStatus6301 ds;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoDeviceStatus6301Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const DeviceStatus6301Exporter6301 exporter;
        DeviceStatus6301 dsOrig;
        fillRandomly(dsOrig);

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(dsOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, dsOrig));

        DeviceStatus6301 dsCopy;
        const DeviceStatus6301Importer6301 importer;
        BOOST_CHECK(importer.deserialize(ss, dsCopy, dh));

        BOOST_CHECK(dsOrig == dsCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

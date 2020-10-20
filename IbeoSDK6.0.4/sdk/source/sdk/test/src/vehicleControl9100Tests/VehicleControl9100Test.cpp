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
//!\date August 23, 2017
//------------------------------------------------------------------------------

#include "VehicleControl9100TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/vehiclecontrol/VehicleControl9100Exporter9100.hpp>
#include <ibeo/common/sdk/datablocks/vehiclecontrol/VehicleControl9100Importer9100.hpp>

#define BOOST_TEST_MODULE VehicleControl9100Tests
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(VehicleControl9100TestSuite)

//==============================================================================

class Fixture : public unittests::VehicleControl9100TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoVehicleControlIdentity, Fixture)
{
    for (uint32_t r = 0; r < nbOfRepeats; ++r)
    {
        const VehicleControl9100Exporter9100 exporter;
        VehicleControl9100 vcOrig(createVehicleControl9100());

        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(vcOrig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, vcOrig));

        VehicleControl9100 vcCopy;
        VehicleControl9100Importer9100 importer;
        BOOST_CHECK(importer.deserialize(ss, vcCopy, dh));

        BOOST_CHECK(vcOrig == vcCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

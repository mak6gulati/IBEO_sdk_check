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
//!\date Mar 21, 2018
//------------------------------------------------------------------------------

#include "EventTag7000TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/eventtag/EventTag7000Exporter7000.hpp>
#include <ibeo/common/sdk/datablocks/eventtag/EventTag7000Importer7000.hpp>

#define BOOST_TEST_MODULE EventTag7000Tests
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(IbeoEventTestSuite7001)

//==============================================================================

class Fixture : public unittests::EventTag7000TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoIbeoEventIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        EventTag7000Exporter7000 exporter;
        EventTag7000 odOrig(createIbeoEvent7000());

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(odOrig)), 0, NTPTime());
        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, odOrig));

        EventTag7000 odCopy;
        const EventTag7000Importer7000 importer;
        BOOST_CHECK(importer.deserialize(ss, odCopy, dh));

        BOOST_CHECK(odCopy == odOrig);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

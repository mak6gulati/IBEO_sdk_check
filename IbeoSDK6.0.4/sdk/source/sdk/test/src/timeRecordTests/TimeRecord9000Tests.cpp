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

#include "TimeRecord9000TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/timerecord/TimeRecord9000Exporter9000.hpp>
#include <ibeo/common/sdk/datablocks/timerecord/TimeRecord9000Importer9000.hpp>

#define BOOST_TEST_MODULE TimeRecordTest9000
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(TimeRecord9000TestSuite)

//==============================================================================

class Fixture : public unittests::TimeRecord9000TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoTimeRecordIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const TimeRecord9000Exporter9000 exporter;
        TimeRecord9000 trOrig(createTimeRecord9000());

        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(trOrig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, trOrig));

        TimeRecord9000 trCopy;
        const TimeRecord9000Importer9000 importer;
        BOOST_CHECK(importer.deserialize(ss, trCopy, dh));

        BOOST_CHECK(trOrig == trCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

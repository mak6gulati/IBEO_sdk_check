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

#include "FrameEndSeparator1100TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/frameendseparator/FrameEndSeparator1100Importer1100.hpp>
#include <ibeo/common/sdk/datablocks/frameendseparator/FrameEndSeparator1100Exporter1100.hpp>

#define BOOST_TEST_MODULE FrameEndSeparator1100Tests
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(FrameEndSeparator1100TestSuite)

//==============================================================================

class Fixture : public unittests::FrameEndSeparator1100TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoFrameEndSeparator1100Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const FrameEndSeparator1100Exporter1100 exporter;
        FrameEndSeparator1100 fiOrig(createFrameSeparator());

        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(fiOrig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, fiOrig));

        FrameEndSeparator1100 fiCopy;
        const FrameEndSeparator1100Importer1100 importer;
        BOOST_CHECK(importer.deserialize(ss, fiCopy, dh));

        BOOST_CHECK(fiOrig == fiCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

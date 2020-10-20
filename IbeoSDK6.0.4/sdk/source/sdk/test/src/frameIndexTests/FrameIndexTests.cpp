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
//! \date Jan 24, 2019
//------------------------------------------------------------------------------

#include "FrameIndexTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/frameindex/FrameIndexImporter6130.hpp>
#include <ibeo/common/sdk/datablocks/frameindex/FrameIndexExporter6130.hpp>

#define BOOST_TEST_MODULE FrameIndexTest
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(FrameIndexTestSuite)

//==============================================================================

class Fixture : public unittests::FrameIndexTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoFrameIndexIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const FrameIndexExporter6130 exporter;
        FrameIndex fiOrig;
        fillRandomly(fiOrig);

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(fiOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, fiOrig));

        FrameIndex fiCopy;
        const FrameIndexImporter6130 importer;
        BOOST_CHECK(importer.deserialize(ss, fiCopy, dh));

        BOOST_CHECK(fiOrig == fiCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

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
//! \date Feb 12, 2018
//------------------------------------------------------------------------------

#include "FrameIndex6130TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130Importer6130.hpp>
#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130Exporter6130.hpp>

#define BOOST_TEST_MODULE FrameIndex6130Test
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(FrameIndex6130TestSuite)

//==============================================================================

class Fixture : public unittests::FrameIndex6130TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoFrameIndex6130Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const FrameIndex6130Exporter6130 exporter;
        FrameIndex6130 fiOrig;
        fillRandomly(fiOrig);

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(fiOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, fiOrig));

        FrameIndex6130 fiCopy;
        const FrameIndex6130Importer6130 importer;
        BOOST_CHECK(importer.deserialize(ss, fiCopy, dh));

        BOOST_CHECK(fiOrig == fiCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

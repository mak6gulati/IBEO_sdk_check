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

#include <ibeo/common/sdk/datablocks/idctrailer/IdcTrailer6120Exporter6120.hpp>
#include <ibeo/common/sdk/datablocks/idctrailer/IdcTrailer6120Importer6120.hpp>
#include <idcTrailer6120Tests/IdcTrailer6120TestSupport.hpp>

#define BOOST_TEST_MODULE FrameIndex6130Test
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(FrameIndex6130TestSuite)

//==============================================================================

class Fixture : public unittests::IdcTrailer6120TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoIdcTrailer6120Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const IdcTrailer6120Exporter6120 exporter;
        IdcTrailer6120 trailerOrig(createIdcTrailer());

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(trailerOrig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, trailerOrig));

        IdcTrailer6120 trailerCopy;
        const IdcTrailer6120Importer6120 importer;
        BOOST_CHECK(importer.deserialize(ss, trailerCopy, dh));

        BOOST_CHECK(trailerOrig == trailerCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(allTrailerAreEqual, Fixture)
{
    IdcTrailer6120 trailer1;
    IdcTrailer6120 trailer2;

    BOOST_CHECK(trailer1 == trailer2);
    BOOST_CHECK(!(trailer1 != trailer2));
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

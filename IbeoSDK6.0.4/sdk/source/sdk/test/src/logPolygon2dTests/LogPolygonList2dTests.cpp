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
//!\date Jan 23, 2019
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/logpolygonlist2d/LogPolygonList2dExporter6817.hpp>
#include <ibeo/common/sdk/datablocks/logpolygonlist2d/LogPolygonList2dImporter6817.hpp>
#include <logPolygon2dTests/LogPolygonList2dTestSupport.hpp>

#define BOOST_TEST_MODULE LogPolygonList2dTests
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(LogPolygonList2dTestSuite)

//==============================================================================

class Fixture : public unittests::LogPolygonList2dTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoLogPolygon2dIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const LogPolygonList2dExporter6817 exporter;
        LogPolygonList2d lplOrig;
        fillRandomly(lplOrig);

        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(lplOrig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, lplOrig));

        LogPolygonList2d lplCopy;
        const LogPolygonList2dImporter6817 importer;
        BOOST_CHECK(importer.deserialize(ss, lplCopy, dh));

        BOOST_CHECK(lplOrig == lplCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

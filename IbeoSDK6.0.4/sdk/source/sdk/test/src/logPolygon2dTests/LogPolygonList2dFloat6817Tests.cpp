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

#include <ibeo/common/sdk/datablocks/logpolygonlist2d/special/LogPolygonList2dFloat6817Exporter6817.hpp>
#include <ibeo/common/sdk/datablocks/logpolygonlist2d/special/LogPolygonList2dFloat6817Importer6817.hpp>
#include <logPolygon2dTests/LogPolygonList2dTestSupport.hpp>

#define BOOST_TEST_MODULE FrameEndSeparator1100Tests
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(FrameEndSeparator1100TestSuite)

//==============================================================================

class Fixture : public unittests::LogPolygonList2dTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoLogPolygon2dFloat6817Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const LogPolygonList2dFloat6817Exporter6817 exporter;
        LogPolygonList2dFloat6817 lplOrig;
        fillRandomly(lplOrig);

        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(lplOrig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, lplOrig));

        LogPolygonList2dFloat6817 lplCopy;
        const LogPolygonList2dFloat6817Importer6817 importer;
        BOOST_CHECK(importer.deserialize(ss, lplCopy, dh));

        BOOST_CHECK(lplOrig == lplCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

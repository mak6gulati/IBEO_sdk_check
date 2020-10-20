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
//!\date 15.November 2018
//------------------------------------------------------------------------------

#include <wgs84Tests/PositionWgs84SequenceTestSupport.hpp>

#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84SequenceExporter3510.hpp>
#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84SequenceImporter3510.hpp>
#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84SequenceExporter2604.hpp>
#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84SequenceImporter2604.hpp>

#define BOOST_TEST_MODULE Wgs84Test
#include <boost/test/unit_test.hpp>

#include <vector>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(Wgs84TestSuite)

//==============================================================================

class Fixture : public unittests::PositionWgs84SequenceTestSupport
{
}; // Fixture

//==============================================================================
//creation test
BOOST_FIXTURE_TEST_CASE(createPositionWgs84, Fixture)
{
    PositionWgs84Sequence positionWgs84Sequence;
    fillRandomly(positionWgs84Sequence);
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoPositionWgs84SequenceIdentity3510, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const PositionWgs84SequenceExporter3510 exp;
        PositionWgs84Sequence posOrig(createPositionWgs84Sequence());

        std::stringstream ss;
        BOOST_CHECK(exp.serialize(ss, posOrig));

        const IbeoDataHeader dh(exp.getDataType(), 0, uint32_t(exp.getSerializedSize(posOrig)), 0, NTPTime());

        PositionWgs84Sequence posCopy;
        const PositionWgs84SequenceImporter3510 imp;

        BOOST_CHECK(imp.deserialize(ss, posCopy, dh));
        BOOST_CHECK(posOrig == posCopy);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoPositionWgs84SequenceIdentity2604, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const PositionWgs84SequenceExporter2604 exp;
        PositionWgs84Sequence posOrig(createPositionWgs84Sequence2604());

        std::stringstream ss;
        BOOST_CHECK(exp.serialize(ss, posOrig));

        const IbeoDataHeader dh(exp.getDataType(), 0, uint32_t(exp.getSerializedSize(posOrig)), 0, NTPTime());

        PositionWgs84Sequence posCopy;
        const PositionWgs84SequenceImporter2604 imp;

        BOOST_CHECK(imp.deserialize(ss, posCopy, dh));
        BOOST_CHECK(posOrig == posCopy);

    } // for r
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoPositionWgs84_2604Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

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
//!\date Sept 04, 2018
//------------------------------------------------------------------------------

#include "Position84WgsSequence3510TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84Sequence3510Importer3510.hpp>
#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84Sequence3510Exporter3510.hpp>

//==============================================================================

#define BOOST_TEST_MODULE Position84WgsSequenceTest3510

//==============================================================================
#include <boost/test/unit_test.hpp>
//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(Position84WgsSequence3510TestSuite3510)

//==============================================================================

class Fixture : public unittests::PositionWgs84Sequence3510TestSupport
{
}; //Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createPositionWgs84Sequence3510, Fixture)
{
    ibeo::common::sdk::PositionWgs84Sequence3510 pos;
    fillRandomly(pos);
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoPosSequenceIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const PositionWgs84Sequence3510Exporter3510 exp;
        PositionWgs84Sequence3510 posOrig(createPositionWgs84Sequence3510());

        std::stringstream ss;
        BOOST_CHECK(exp.serialize(ss, posOrig));

        const IbeoDataHeader dh(exp.getDataType(), 0, uint32_t(exp.getSerializedSize(posOrig)), 0, NTPTime());

        PositionWgs84Sequence3510 posCopy;
        const PositionWgs84Sequence3510Importer3510 imp;

        BOOST_CHECK(imp.deserialize(ss, posCopy, dh));
        BOOST_CHECK(posOrig == posCopy);
    } //for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoPosSequenceEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        PositionWgs84Sequence3510 posOrig, posCopy;
        BOOST_CHECK(posOrig == posCopy);
        posOrig.setId(getDifferentRandValue<uint32_t>(posOrig.getId()));
        BOOST_CHECK(posOrig != posCopy);
        posCopy.setId(posOrig.getId());
        BOOST_CHECK(posOrig == posCopy);

        NTPTime tmpTime = posOrig.getTimestamp();
        do
        {
            posOrig.setTimestamp(getRandValue<NTPTime>());
        } while ((posOrig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (posOrig.getTimestamp() == tmpTime));

        BOOST_CHECK(posOrig != posCopy);
        posCopy.setTimestamp(posOrig.getTimestamp());
        BOOST_CHECK(posOrig == posCopy);

        const uint8_t sequenceSize
            = getDifferentRandValue<uint8_t>(static_cast<uint8_t>(posOrig.getPositionSequence().size()));
        std::vector<PositionWgs84> positionSequence(sequenceSize, PositionWgs84());
        for (uint8_t i = 0; i < sequenceSize; ++i)
        {
            fillPosRandomly(positionSequence.at(i));
        }
        posOrig.setPositionSequence(positionSequence);
        BOOST_CHECK(posOrig != posCopy);
        posCopy.setPositionSequence(posOrig.getPositionSequence());
        BOOST_CHECK(posOrig == posCopy);

        posOrig.setSourceType(static_cast<PositionWgs84Sequence3510::SourceType>(
            getDifferentRandValue<uint8_t>(0, 0xFF, posOrig.getSourceType())));
        BOOST_CHECK(posOrig != posCopy);
        posCopy.setSourceType(posOrig.getSourceType());
        BOOST_CHECK(posOrig == posCopy);
    } //for r
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoPosSequenceAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        PositionWgs84Sequence3510 posOrig, posCopy, posEmpty;
        BOOST_CHECK(posOrig == posCopy);
        BOOST_CHECK(posOrig == posEmpty);

        posOrig.setId(getDifferentRandValue<uint32_t>(posOrig.getId()));
        BOOST_CHECK(posOrig != posCopy);
        posCopy = posOrig;
        BOOST_CHECK(posOrig == posCopy);

        NTPTime tmpTime = posOrig.getTimestamp();
        do
        {
            posOrig.setTimestamp(getRandValue<NTPTime>());
        } while ((posOrig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (posOrig.getTimestamp() == tmpTime));

        BOOST_CHECK(posOrig != posCopy);
        posCopy = posOrig;
        BOOST_CHECK(posOrig == posCopy);

        const uint8_t sequenceSize
            = getDifferentRandValue<uint8_t>(static_cast<uint8_t>(posOrig.getPositionSequence().size()));
        std::vector<PositionWgs84> positionSequence(sequenceSize, PositionWgs84());
        for (uint8_t i = 0; i < sequenceSize; ++i)
        {
            fillPosRandomly(positionSequence.at(i));
        }
        posOrig.setPositionSequence(positionSequence);
        BOOST_CHECK(posOrig != posCopy);
        posCopy = posOrig;
        BOOST_CHECK(posOrig == posCopy);

        posOrig.setSourceType(static_cast<PositionWgs84Sequence3510::SourceType>(
            getDifferentRandValue<uint8_t>(0, 0xFF, posOrig.getSourceType())));
        BOOST_CHECK(posOrig != posCopy);
        posCopy = posOrig;
        BOOST_CHECK(posOrig == posCopy);

        posOrig = posEmpty;
        BOOST_CHECK(posOrig != posCopy);
        posCopy = posEmpty;
        BOOST_CHECK(posOrig == posCopy);
        BOOST_CHECK(posOrig == posEmpty);
    }
}

//==============================================================================
BOOST_AUTO_TEST_SUITE_END()
//==============================================================================

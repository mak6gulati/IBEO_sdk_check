//==============================================================================
//!\file
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date 08.November 2018
//------------------------------------------------------------------------------

#include "IdSequenceTestSupport.hpp"
#include <ibeo/common/sdk/datablocks/idsequence/IdSequenceImporter3500.hpp>
#include <ibeo/common/sdk/datablocks/idsequence/IdSequenceExporter3500.hpp>

#define BOOST_TEST_MODULE IdSequenceTest

#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(IdSequenceTestSuite)

//==============================================================================

class Fixture : public unittests::IdSequenceTestSupport
{
};

//==============================================================================

// Constructor test
BOOST_FIXTURE_TEST_CASE(createIdSequence, Fixture)
{
    ibeo::common::sdk::IdSequence o;
    fillRandomly(o);
    BOOST_CHECK(true);
}

//==============================================================================

//Identity Test/Serialize Deserialize
BOOST_FIXTURE_TEST_CASE(isIoIdSequenceIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const IdSequenceExporter3500 exp;
        IdSequence isOrig(createIdSequence());

        const IbeoDataHeader dh(exp.getDataType(), 0, uint32_t(exp.getSerializedSize(isOrig)), 0, NTPTime());

        std::stringstream ss;

        BOOST_CHECK(exp.serialize(ss, isOrig));

        IdSequence isCopy;
        const IdSequenceImporter3500 imp;

        BOOST_CHECK(imp.deserialize(ss, isCopy, dh));

        BOOST_CHECK(isCopy == isOrig);

    } // for r
}

//==============================================================================
//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoIdSequenceEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        IdSequence isOrig, isCopy;
        BOOST_CHECK(isOrig == isCopy);

        isOrig.setId(getDifferentRandValue<uint32_t>(isOrig.getId()));
        BOOST_CHECK(isOrig != isCopy);
        isCopy.setId(isOrig.getId());
        BOOST_CHECK(isOrig == isCopy);

        NTPTime tmpTime = isOrig.getTimestamp();
        do
        {
            isOrig.setTimestamp(getRandValue<NTPTime>());
        } while ((isOrig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (isOrig.getTimestamp() == tmpTime));

        BOOST_CHECK(isOrig != isCopy);

        isCopy.setTimestamp(isOrig.getTimestamp());
        BOOST_CHECK(isOrig == isCopy);

        isOrig.setSourceType(static_cast<IdSequence::SourceType>(
            getDifferentRandValue<uint8_t>(0, 0xFFU, static_cast<uint8_t>(isOrig.getSourceType()))));

        BOOST_CHECK(isOrig != isCopy);

        isCopy.setSourceType(isOrig.getSourceType());
        BOOST_CHECK(isOrig == isCopy);

        const uint8_t sequenceSize
            = getDifferentRandValue<uint8_t>(0, 0xFFU, static_cast<uint8_t>(isCopy.getIdSequence().size()));

        std::vector<int64_t> idSequenceVec(sequenceSize, 0);

        for (auto& id : idSequenceVec)
        {
            id = getDifferentRandValue<int64_t>(id);
        }

        isOrig.setIdSequence(idSequenceVec);

        BOOST_CHECK(isOrig != isCopy);

        isCopy.setIdSequence(isOrig.getIdSequence());
        BOOST_CHECK(isOrig == isCopy);
    }
}

//==============================================================================

// test operator=
BOOST_FIXTURE_TEST_CASE(isIoIdSequenceAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        IdSequence isEmpty, isOrig, isCopy;
        BOOST_CHECK(isOrig == isCopy);
        BOOST_CHECK(isOrig == isEmpty);

        //Id
        isOrig.setId(getDifferentRandValue<uint32_t>(isOrig.getId()));
        BOOST_CHECK(isOrig != isCopy);
        isCopy = isOrig;
        BOOST_CHECK(isOrig == isCopy);

        //Time
        NTPTime tmpTime = isOrig.getTimestamp();

        do
        {
            isOrig.setTimestamp(getRandValue<NTPTime>());
        } while ((isOrig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (isOrig.getTimestamp() == tmpTime));

        BOOST_CHECK(isOrig != isCopy);
        isCopy = isOrig;
        BOOST_CHECK(isOrig == isCopy);

        //SourceType
        isOrig.setSourceType(static_cast<IdSequence::SourceType>(
            getDifferentRandValue<uint8_t>(0, 0xFFU, static_cast<uint8_t>(isOrig.getSourceType()))));

        BOOST_CHECK(isOrig != isCopy);

        isCopy = isOrig;
        BOOST_CHECK(isOrig == isCopy);

        //Vector
        const uint8_t sequenceSize
            = getDifferentRandValue<uint8_t>(0, 0xFFU, static_cast<uint8_t>(isCopy.getIdSequence().size()));

        std::vector<int64_t> idSequenceVec(sequenceSize, 0);

        for (auto& id : idSequenceVec)
        {
            id = getDifferentRandValue<int64_t>(id);
        }

        isOrig.setIdSequence(idSequenceVec);
        BOOST_CHECK(isOrig != isCopy);
        isCopy = isOrig;
        BOOST_CHECK(isOrig == isCopy);

        //Empty them
        isOrig = isEmpty;
        BOOST_CHECK(isOrig != isCopy);
        isCopy = isEmpty;
        BOOST_CHECK(isOrig == isCopy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

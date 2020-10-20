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
//!\date December 05, 2018
//------------------------------------------------------------------------------

#include "IdSequence3500TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/idsequence/IdSequence3500Importer3500.hpp>
#include <ibeo/common/sdk/datablocks/idsequence/IdSequence3500Exporter3500.hpp>

#define BOOST_TEST_MODULE IdSequenceTest

#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(IdSequenceTestSuite)

//==============================================================================

class Fixture : public unittests::IdSequence3500TestSupport
{
};

//==============================================================================

// Constructor test
BOOST_FIXTURE_TEST_CASE(createIdSequence3500, Fixture)
{
    IdSequence3500 o;
    fillRandomly3500(o);
    BOOST_CHECK(true);
}

//==============================================================================
//Identity Test/Serialize Deserialize
BOOST_FIXTURE_TEST_CASE(isIoIdSequence3500Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const IdSequence3500Exporter3500 exp;
        IdSequence3500 isOrig(createIdSequence3500());

        const IbeoDataHeader dh(exp.getDataType(), 0, uint32_t(exp.getSerializedSize(isOrig)), 0, NTPTime());
        std::stringstream ss;

        BOOST_CHECK(exp.serialize(ss, isOrig));

        IdSequence3500 isCopy;
        const IdSequence3500Importer3500 imp;

        BOOST_CHECK(imp.deserialize(ss, isCopy, dh));

        BOOST_CHECK(isCopy == isOrig);
    } // for r
}

//==============================================================================
//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoIdSequence3500Equality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        IdSequence3500 isOrig, isCopy;
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

        isOrig.setSourceType(static_cast<IdSequence3500::SourceType>(
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
BOOST_FIXTURE_TEST_CASE(isIoIdSequence3500Assignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        IdSequence3500 isEmpty, isOrig, isCopy;
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
        isOrig.setSourceType(static_cast<IdSequence3500::SourceType>(
            getDifferentRandValue<uint8_t>(0, 0xFFU, static_cast<uint8_t>(isOrig.getSourceType()))));

        BOOST_CHECK(isOrig != isCopy);

        isCopy = isOrig;
        BOOST_CHECK(isOrig == isCopy);

        //Vector
        const uint8_t sequenceSize
            = getDifferentRandValue<uint8_t>(0, 0xFFU, static_cast<uint8_t>(isCopy.getIdSequence().size()));

        std::vector<int64_t> idSequence(sequenceSize, 0);
        for (uint8_t i = 0; i < sequenceSize; ++i)
        {
            idSequence.at(i) = getDifferentRandValue<int64_t>(idSequence.at(i));
        }
        isOrig.setIdSequence(idSequence);
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

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
//!\date Sept 05, 2018
//------------------------------------------------------------------------------

#include "Destination3520TestSupport.hpp"
#include <wgs84Tests/PositionWgs84_2604TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/destination/Destination3520Importer3520.hpp>
#include <ibeo/common/sdk/datablocks/destination/Destination3520Exporter3520.hpp>

//==============================================================================
#define BOOST_TEST_MODULE DestinationTest3500

#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(Destination3520TestSuite3520)

//==============================================================================

class Fixture : public unittests::Destination3520TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createDestination3520, Fixture)
{
    Destination3520 d;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoDestinationIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Destination3520Exporter3520 exp;
        Destination3520 dOrig(createDestination3520());

        const IbeoDataHeader dh(exp.getDataType(), 0, uint32_t(exp.getSerializedSize(dOrig)), 0, NTPTime());
        std::stringstream ss;
        BOOST_CHECK(exp.serialize(ss, dOrig));

        Destination3520 dCopy;
        Destination3520Importer3520 imp;
        BOOST_CHECK(imp.deserialize(ss, dCopy, dh));
        BOOST_CHECK(dCopy == dOrig);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isDestinationEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Destination3520 dCopy, dOrig;
        BOOST_CHECK(dCopy == dOrig);
        dOrig.setTargetId(getDifferentRandValue<int64_t>(dOrig.getTargetId()));
        BOOST_CHECK(dCopy != dOrig);
        dCopy.setTargetId(dOrig.getTargetId());
        BOOST_CHECK(dCopy == dOrig);

        NTPTime tmpTime = dOrig.getTimestamp();
        do
        {
            dOrig.setTimestamp(getRandValue<NTPTime>());
        } while ((dOrig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (dOrig.getTimestamp() == tmpTime));
        BOOST_CHECK(dOrig != dCopy);
        dCopy.setTimestamp(dOrig.getTimestamp());
        BOOST_CHECK(dOrig == dCopy);

        dOrig.setId(getDifferentRandValue<uint32_t>(dOrig.getId()));
        BOOST_CHECK(dOrig != dCopy);
        dCopy.setId(dOrig.getId());
        BOOST_CHECK(dOrig == dCopy);

        dOrig.setSourceType(static_cast<Destination3520 ::SourceType>(
            getDifferentRandValue<uint8_t>(0, 0xFF, static_cast<uint8_t>(dOrig.getSourceType()))));
        BOOST_CHECK(dOrig != dCopy);
        dCopy.setSourceType(dOrig.getSourceType());
        BOOST_CHECK(dOrig == dCopy);

        dOrig.setPurposeType(static_cast<Destination3520::PurposeType>(
            getDifferentRandValue<uint8_t>(0, 0xFF, static_cast<uint8_t>(dOrig.getPurposeType()))));
        BOOST_CHECK(dOrig != dCopy);
        dCopy.setPurposeType(dOrig.getPurposeType());
        BOOST_CHECK(dOrig == dCopy);

        dOrig.setDestinationType(static_cast<Destination3520::DestinationType>(
            getDifferentRandValue<uint8_t>(0, 0xFF, static_cast<uint8_t>(dOrig.getDestinationType()))));
        BOOST_CHECK(dOrig != dCopy);
        dCopy.setDestinationType(dOrig.getDestinationType());
        BOOST_CHECK(dOrig == dCopy);

        PositionWgs84 randPos;
        unittests::PositionWgs84_2604TestSupport::fillRandomly(randPos);
        dOrig.setTargetPosition(randPos);
        BOOST_CHECK(dOrig != dCopy);
        dCopy.setTargetPosition(dOrig.getTargetPosition());
        BOOST_CHECK(dOrig == dCopy);
    } //for r
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isDestinationAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Destination3520 dCopy, dOrig, dEmpty;
        BOOST_CHECK(dCopy == dOrig);
        BOOST_CHECK(dEmpty == dOrig);

        dOrig.setTargetId(getDifferentRandValue<int64_t>(dOrig.getTargetId()));
        BOOST_CHECK(dCopy != dOrig);
        dCopy = dOrig;
        BOOST_CHECK(dCopy == dOrig);

        NTPTime tmpTime = dOrig.getTimestamp();
        do
        {
            dOrig.setTimestamp(getRandValue<NTPTime>());
        } while ((dOrig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (dOrig.getTimestamp() == tmpTime));
        BOOST_CHECK(dOrig != dCopy);
        dCopy = dOrig;
        BOOST_CHECK(dOrig == dCopy);

        dOrig.setId(getDifferentRandValue<uint32_t>(dOrig.getId()));
        BOOST_CHECK(dOrig != dCopy);
        dCopy = dOrig;
        BOOST_CHECK(dOrig == dCopy);

        dOrig.setSourceType(static_cast<Destination3520::SourceType>(
            getDifferentRandValue<uint8_t>(0, 0xFF, static_cast<uint8_t>(dOrig.getSourceType()))));
        BOOST_CHECK(dOrig != dCopy);
        dCopy = dOrig;
        BOOST_CHECK(dOrig == dCopy);

        dOrig.setPurposeType(static_cast<Destination3520::PurposeType>(
            getDifferentRandValue<uint8_t>(0, 0xFF, static_cast<uint8_t>(dOrig.getPurposeType()))));
        BOOST_CHECK(dOrig != dCopy);
        dCopy = dOrig;
        BOOST_CHECK(dOrig == dCopy);

        dOrig.setDestinationType(static_cast<Destination3520::DestinationType>(
            getDifferentRandValue<uint8_t>(0, 0xFF, static_cast<uint8_t>(dOrig.getDestinationType()))));
        BOOST_CHECK(dOrig != dCopy);
        dCopy = dOrig;
        BOOST_CHECK(dOrig == dCopy);

        PositionWgs84 randPos;
        unittests::PositionWgs84_2604TestSupport::fillRandomly(randPos);
        dOrig.setTargetPosition(randPos);
        BOOST_CHECK(dOrig != dCopy);
        dCopy = dOrig;
        BOOST_CHECK(dOrig == dCopy);

        dOrig = dEmpty;
        BOOST_CHECK(dOrig == dEmpty);
        BOOST_CHECK(dOrig != dCopy);

        dCopy = dEmpty;
        BOOST_CHECK(dCopy == dEmpty);
        BOOST_CHECK(dCopy == dOrig);
    } //for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

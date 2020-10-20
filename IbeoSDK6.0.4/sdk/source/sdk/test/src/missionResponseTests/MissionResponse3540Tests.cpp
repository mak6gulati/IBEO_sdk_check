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

#include "MissionResponse3540TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/missionresponse/MissionResponse3540Importer3540.hpp>
#include <ibeo/common/sdk/datablocks/missionresponse/MissionResponse3540Exporter3540.hpp>

//==============================================================================

#define BOOST_TEST_MODULE MissionResponse3540

#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(MissionResponse3540TestSuite)

//==============================================================================

class Fixture : public unittests::MissionResponse3540TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createMissionResponse3540, Fixture)
{
    MissionResponse3540 mr;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoMissionResponseIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MissionResponse3540Exporter3540 exp;
        MissionResponse3540 orig(createMissionResponse3540());

        const IbeoDataHeader dh(exp.getDataType(), 0, uint32_t(exp.getSerializedSize(orig)), 0, NTPTime());
        std::stringstream ss;
        BOOST_CHECK(exp.serialize(ss, orig));

        MissionResponse3540 copy;
        MissionResponse3540Importer3540 imp;
        BOOST_CHECK(imp.deserialize(ss, copy, dh));
        BOOST_CHECK(copy == orig);
    } // for r
}

//==============================================================================

//test operator== and operator!=
BOOST_FIXTURE_TEST_CASE(isDestinationEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MissionResponse3540 orig, copy;
        BOOST_CHECK(orig == copy);
        orig.setMissionId(getDifferentRandValue<uint32_t>(orig.getMissionId()));
        BOOST_CHECK(orig != copy);
        copy.setMissionId(orig.getMissionId());
        BOOST_CHECK(orig == copy);

        orig.setResponse(static_cast<MissionResponse3540::Response>(
            getDifferentRandValue<uint8_t>(static_cast<uint8_t>(orig.getResponse()))));
        BOOST_CHECK(orig != copy);
        copy.setResponse(orig.getResponse());
        BOOST_CHECK(orig == copy);

        NTPTime tmpTime = orig.getTimestamp();
        do
        {
            orig.setTimestamp(getRandValue<NTPTime>());
        } while ((orig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (orig.getTimestamp() == tmpTime));
        BOOST_CHECK(orig != copy);
        copy.setTimestamp(orig.getTimestamp());
        BOOST_CHECK(orig == copy);
    } // for r
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isDestinationAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MissionResponse3540 orig, copy, empty;
        BOOST_CHECK(orig == copy);
        orig.setMissionId(getDifferentRandValue<uint32_t>(orig.getMissionId()));
        BOOST_CHECK(orig != copy);
        copy = orig;
        BOOST_CHECK(orig == copy);

        orig.setResponse(static_cast<MissionResponse3540::Response>(
            getDifferentRandValue<uint8_t>(static_cast<uint8_t>(orig.getResponse()))));
        BOOST_CHECK(orig != copy);
        copy = orig;
        BOOST_CHECK(orig == copy);

        NTPTime tmpTime = orig.getTimestamp();
        do
        {
            orig.setTimestamp(getRandValue<NTPTime>());
        } while ((orig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (orig.getTimestamp() == tmpTime));
        BOOST_CHECK(orig != copy);
        copy = orig;
        BOOST_CHECK(orig == copy);

        orig = empty;
        BOOST_CHECK(orig == empty);
        BOOST_CHECK(orig != copy);

        copy = empty;
        BOOST_CHECK(copy == empty);
        BOOST_CHECK(copy == orig);
    } // for r
}

//==============================================================================
BOOST_AUTO_TEST_SUITE_END()
//==============================================================================

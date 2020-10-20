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
//!\date 07.November 2018
//------------------------------------------------------------------------------

#include "MissionHandlingStatus3530TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/missionhandling/MissionHandlingStatus3530Importer3530.hpp>
#include <ibeo/common/sdk/datablocks/missionhandling/MissionHandlingStatus3530Exporter3530.hpp>

//==============================================================================

#define BOOST_TEST_MODULE MissionHandlingStatus3530

#include <boost/test/unit_test.hpp>
//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(MissionHandlingStatus3530TestSuite)

//==============================================================================

class Fixture : public unittests::MissionHandlingStatus3530TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createMissionHandlingStatus3530, Fixture)
{
    MissionHandlingStatus3530 mhs;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoMissionHandlingStatusIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MissionHandlingStatus3530Exporter3530 exp;
        MissionHandlingStatus3530 orig(createMissionHandlingStatus3530());

        const IbeoDataHeader dh(exp.getDataType(), 0, uint32_t(exp.getSerializedSize(orig)), 0, NTPTime());
        std::stringstream ss;
        BOOST_CHECK(exp.serialize(ss, orig));

        MissionHandlingStatus3530Importer3530 imp;
        MissionHandlingStatus3530 copy;
        BOOST_CHECK(imp.deserialize(ss, copy, dh));
        BOOST_CHECK(copy == orig);
    } // for r
}

//==============================================================================

//test operator== and operator!=
BOOST_FIXTURE_TEST_CASE(isMissionHandlingStatusEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MissionHandlingStatus3530 orig, copy;
        BOOST_CHECK(orig == copy);
        orig.setMissionId(getDifferentRandValue<uint32_t>(orig.getMissionId()));
        BOOST_CHECK(orig != copy);
        copy.setMissionId(orig.getMissionId());
        BOOST_CHECK(orig == copy);
        orig.setState(static_cast<MissionHandlingStatus3530::State>(
            getDifferentRandValue<uint8_t>(static_cast<uint8_t>(orig.getState()))));
        BOOST_CHECK(orig != copy);
        copy.setState(orig.getState());
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
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isMissionHandlingStatusAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        MissionHandlingStatus3530 orig, copy, empty;

        BOOST_CHECK(orig == copy);
        orig.setMissionId(getDifferentRandValue<uint32_t>(orig.getMissionId()));
        BOOST_CHECK(orig != copy);
        copy = orig;
        BOOST_CHECK(orig == copy);
        orig.setState(static_cast<MissionHandlingStatus3530::State>(
            getDifferentRandValue<uint8_t>(static_cast<uint8_t>(orig.getState()))));
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

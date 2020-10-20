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
//!\date 14.November 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "TrafficLightStateListTestSupport.hpp"
#include <ibeo/common/sdk/datablocks/trafficlight/TrafficLightStateListExporter3600.hpp>
#include <ibeo/common/sdk/datablocks/trafficlight/TrafficLightStateListImporter3600.hpp>

#define BOOST_TEST_MODULE TrafficLightStateListTest

#include <boost/test/unit_test.hpp>
//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(TrafficLightStateListTestSuite)

//==============================================================================

class Fixture : public unittests::TrafficLightStateListTestSupport
{
};

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createTrafficLightStateList, Fixture)
{
    TrafficLightStateList d;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isTrafficLightStateListIdentity, Fixture)
{
    for (int32_t r = 0; r < numRepeats; ++r)
    {
        TrafficLightStateList dOrig(createTrafficLightStateList());
        TrafficLightStateListExporter3600 exp;
        const IbeoDataHeader dh(exp.getDataType(), 0, uint32_t(exp.getSerializedSize(dOrig)), 0, NTPTime());
        std::stringstream ss;
        BOOST_CHECK(exp.serialize(ss, dOrig));

        TrafficLightStateList dCopy;
        BOOST_CHECK(dCopy != dOrig);
        TrafficLightStateListImporter3600 imp;
        BOOST_CHECK(imp.deserialize(ss, dCopy, dh));
        BOOST_CHECK(dCopy == dOrig);
    } // for r
}

//==============================================================================

//test operator!= and operator==
BOOST_FIXTURE_TEST_CASE(isTrafficLightStateListEqual, Fixture)
{
    for (int32_t r = 0; r < numRepeats; ++r)
    {
        TrafficLightStateList dCopy, dOrig;
        BOOST_CHECK(dCopy == dOrig);
        fillRandomly(dOrig);
        BOOST_CHECK(dCopy != dOrig);
        dCopy.setTrafficLightStates(dOrig.getTrafficLightStates());
        BOOST_CHECK(dCopy == dOrig);

        BOOST_CHECK(dOrig.getTrafficLightStates().size() == dCopy.getTrafficLightStates().size());
        for (std::size_t a = 0; a < dOrig.getTrafficLightStates().size(); ++a)
        {
            TrafficLightState t1 = dOrig.getTrafficLightStates().at(a);
            TrafficLightState t2 = dCopy.getTrafficLightStates().at(a);
            BOOST_CHECK(t1.getTimeIntervalAbsoluteBegin() == t2.getTimeIntervalAbsoluteBegin());
            BOOST_CHECK(t1.getTimeIntervalRelativeBegin() == t2.getTimeIntervalRelativeBegin());
            BOOST_CHECK(t1.getTimeIntervalAbsoluteEnd() == t2.getTimeIntervalAbsoluteEnd());
            BOOST_CHECK(t1.getTimeIntervalRelativeEnd() == t2.getTimeIntervalRelativeEnd());
            BOOST_CHECK(t1.getTimestampFromTrafficLight() == t2.getTimestampFromTrafficLight());
        }
    } // for r
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isTrafficLightStateListAssignment, Fixture)
{
    for (int32_t r = 0; r < numRepeats; ++r)
    {
        TrafficLightStateList dCopy, dOrig, dEmpty;
        BOOST_CHECK(dCopy == dOrig);
        BOOST_CHECK(dEmpty == dOrig);

        fillRandomly(dOrig);
        BOOST_CHECK(dCopy != dOrig);
        dCopy = dOrig;
        BOOST_CHECK(dCopy == dOrig);

        dOrig = dEmpty;
        BOOST_CHECK(dEmpty == dOrig);
        BOOST_CHECK(dCopy != dOrig);
        dCopy = dOrig;
        BOOST_CHECK(dCopy == dOrig);
    } // for r
}

//==============================================================================
BOOST_AUTO_TEST_SUITE_END()
//==============================================================================

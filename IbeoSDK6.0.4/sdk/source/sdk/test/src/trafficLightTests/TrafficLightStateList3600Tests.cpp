//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Aug 29, 2018
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "TrafficLightStateList3600TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/trafficlight/special/TrafficLightStateList3600Exporter3600.hpp>
#include <ibeo/common/sdk/datablocks/trafficlight/special/TrafficLightStateList3600Importer3600.hpp>

#define BOOST_TEST_MODULE TrafficLightStateList3600Test

#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(TrafficLightStateListTestSuite)

//==============================================================================

class Fixture : public unittests::TrafficLightStateList3600TestSupport
{
};

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createTrafficLightStateList3600, Fixture)
{
    TrafficLightStateList3600 d;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isTrafficLightStateList3600Identity, Fixture)
{
    for (int32_t r = 0; r < numRepeats; ++r)
    {
        TrafficLightStateList3600 dOrig(createTrafficLightStateList3600());
        TrafficLightStateList3600Exporter3600 exp;
        const IbeoDataHeader dh(exp.getDataType(), 0, uint32_t(exp.getSerializedSize(dOrig)), 0, NTPTime());
        std::stringstream ss;
        BOOST_CHECK(exp.serialize(ss, dOrig));

        TrafficLightStateList3600 dCopy;
        BOOST_CHECK(dCopy != dOrig);
        TrafficLightStateList3600Importer3600 imp;
        BOOST_CHECK(imp.deserialize(ss, dCopy, dh));
        BOOST_CHECK(dCopy == dOrig);
    } // for r
}

//==============================================================================

//test operator!= and operator==
BOOST_FIXTURE_TEST_CASE(isTrafficLightStateList3600Equal, Fixture)
{
    for (int32_t r = 0; r < numRepeats; ++r)
    {
        TrafficLightStateList3600 dCopy, dOrig;
        BOOST_CHECK(dCopy == dOrig);
        fillRandomly3600(dOrig);
        BOOST_CHECK(dCopy != dOrig);
        dCopy.setTrafficLightStates(dOrig.getTrafficLightStates());
        BOOST_CHECK(dCopy == dOrig);

        BOOST_CHECK(dOrig.getTrafficLightStates().size() == dCopy.getTrafficLightStates().size());
        for (std::size_t a = 0; a < dOrig.getTrafficLightStates().size(); ++a)
        {
            TrafficLightStateIn3600 t1 = dOrig.getTrafficLightStates().at(a);
            TrafficLightStateIn3600 t2 = dCopy.getTrafficLightStates().at(a);
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
BOOST_FIXTURE_TEST_CASE(isTrafficLightStateList3600Assignment, Fixture)
{
    for (int32_t r = 0; r < numRepeats; ++r)
    {
        TrafficLightStateList3600 dCopy, dOrig, dEmpty;
        BOOST_CHECK(dCopy == dOrig);
        BOOST_CHECK(dEmpty == dOrig);

        fillRandomly3600(dOrig);
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

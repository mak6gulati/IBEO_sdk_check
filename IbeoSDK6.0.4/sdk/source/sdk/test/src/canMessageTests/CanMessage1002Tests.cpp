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

#include "CanMessage1002TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/canmessage/CanMessage1002Importer1002.hpp>
#include <ibeo/common/sdk/datablocks/canmessage/CanMessage1002Exporter1002.hpp>

#define BOOST_TEST_MODULE CanMessage1002Tests
#include <boost/test/unit_test.hpp>

//==============================================================================

using namespace ibeo::common::sdk;

//==============================================================================

BOOST_AUTO_TEST_SUITE(CanMessage1002TestSuite)

//==============================================================================

class Fixture : public unittests::CanMessage1002TestSupport
{
}; // Fixture

//==============================================================================

template<bool extId, bool ts>
class TestSetup
{
public:
    static const bool hasExtId{extId};
    static const bool hasTs{ts};
}; // TestSetup

//==============================================================================

using TestSetupColelction
    = boost::mpl::list<TestSetup<false, false>, TestSetup<false, true>, TestSetup<true, false>, TestSetup<true, true>>;

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(isIoCanMessage1002Identity, TS, TestSetupColelction, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const CanMessage1002Exporter1002 exporter;
        CanMessage1002 fiOrig(createCanMessage(TS::hasExtId, TS::hasTs));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(fiOrig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, fiOrig));

        CanMessage1002 fiCopy;
        const CanMessage1002Importer1002 importer;
        BOOST_CHECK(importer.deserialize(ss, fiCopy, dh));

        BOOST_CHECK(fiOrig == fiCopy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

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
//!\date October 11, 2017
//------------------------------------------------------------------------------

#include "StateOfOperation9110TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/stateofoperation/StateOfOperation9110Exporter9110.hpp>
#include <ibeo/common/sdk/datablocks/stateofoperation/StateOfOperation9110Importer9110.hpp>

#define BOOST_TEST_MODULE StateOfOperationTest9110
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(StateOfOperationTestSuite9110)

//==============================================================================

class Fixture : public unittests::StateOfOperation9110TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoStateOfOperationIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        StateOfOperation9110 odOrig(createStateOfOperation9110C());

        StateOfOperation9110Exporter9110 exporter;
        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, odOrig));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(odOrig)), 0U, NTPTime());

        StateOfOperation9110Importer9110 importer;
        StateOfOperation9110 odCopy;
        BOOST_CHECK(importer.deserialize(ss, odCopy, dh));
        BOOST_CHECK(odCopy == odOrig);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(checkReserved, Fixture)
{
    StateOfOperation9110 odOrig(createStateOfOperation9110C());
    auto& res = odOrig.getReserved();

    for (uint8_t r = 0; r < StateOfOperation9110::nbOfReserved; ++r)
    {
        BOOST_CHECK(res[r] == 0);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

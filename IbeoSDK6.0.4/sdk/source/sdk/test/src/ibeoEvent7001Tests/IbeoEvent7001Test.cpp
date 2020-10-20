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
//!\date September 25, 2017
//------------------------------------------------------------------------------

#include "IbeoEvent7001TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/ibeoevent/IbeoEvent7001Exporter7001.hpp>
#include <ibeo/common/sdk/datablocks/ibeoevent/IbeoEvent7001Importer7001.hpp>

#define BOOST_TEST_MODULE IbeoEventTest7001
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================
BOOST_AUTO_TEST_SUITE(IbeoEventTestSuite7001)

//==============================================================================

class Fixture : public unittests::IbeoEvent7001TestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoIbeoEventIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const IbeoEvent7001Exporter7001 exporter;
        IbeoEvent7001 ieOrig(createIbeoEvent7001());

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(ieOrig)), 0, NTPTime());
        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, ieOrig));

        IbeoEvent7001 ieCopy;
        const IbeoEvent7001Importer7001 importer;
        BOOST_CHECK(importer.deserialize(ss, ieCopy, dh));

        BOOST_CHECK(ieCopy == ieOrig);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

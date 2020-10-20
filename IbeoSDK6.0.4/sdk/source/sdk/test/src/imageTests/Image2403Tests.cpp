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
//!\date Feb 05, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "Image2403TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/image/special/Image2403Exporter2403.hpp>
#include <ibeo/common/sdk/datablocks/image/special/Image2403Importer2403.hpp>

#define BOOST_TEST_MODULE Image2403Test
#include <boost/test/unit_test.hpp>

#include <vector>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(Image2403TestSuite)

//==============================================================================

class Fixture : public unittests::Image2403TestSupport
{
}; // Fixture

//==============================================================================
//creation test
BOOST_FIXTURE_TEST_CASE(createPositionImage2403, Fixture)
{
    ibeo::common::sdk::Image2403 image;
    //BOOST_CHECK(image == image);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoImage2403Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Image2403Exporter2403 exporter;
        Image2403 origImage{createImage2403()};

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(origImage)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, origImage));

        Image2403 copyOfImage;
        const Image2403Importer2403 importer;
        BOOST_CHECK(importer.deserialize(ss, copyOfImage, dh));

        BOOST_CHECK(origImage == copyOfImage);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoEmptyImage2403Identity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Image2403Exporter2403 exporter;
        Image2403 origImage;
        fillEmptyImageRandomly(origImage);

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(origImage)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, origImage));

        Image2403 copyOfImage;
        const Image2403Importer2403 importer;
        BOOST_CHECK(importer.deserialize(ss, copyOfImage, dh));

        BOOST_CHECK(origImage == copyOfImage);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

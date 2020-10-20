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
#include <ibeo/common/sdk/datablocks/image/special/Image2403.hpp>
#include <ibeo/common/sdk/datablocks/image/special/Image2403Importer2403.hpp>
#include <ibeo/common/sdk/datablocks/image/special/Image2403Exporter2403.hpp>

#include "ImageTestSupport.hpp"
#include <ibeo/common/sdk/datablocks/image/Image.hpp>
#include <ibeo/common/sdk/datablocks/image/ImageImporter2403.hpp>
#include <ibeo/common/sdk/datablocks/image/ImageExporter2403.hpp>

#define BOOST_TEST_MODULE ImageTest
#include <boost/test/unit_test.hpp>

#include <vector>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ImageTestSuite)

//==============================================================================

class Fixture : public unittests::ImageTestSupport // Fixture1
{
protected:
    static const int32_t nbOfRepeats = 100;
};

class Fixture2 : public unittests::ImageTestSupport, public unittests::Image2403TestSupport // Fixture2
{
protected:
    static const int32_t nbOfRepeats = 100;
};

//==============================================================================
//creation test
BOOST_FIXTURE_TEST_CASE(createPositionImage, Fixture)
{
    Image image;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoImageIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ImageExporter2403 exporter;
        Image origImage{createImage()};

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(origImage)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, origImage));

        Image copyOfImage;
        const ImageImporter2403 importer;
        BOOST_CHECK(importer.deserialize(ss, copyOfImage, dh));

        BOOST_CHECK(origImage == copyOfImage);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoEmptyImageIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ImageExporter2403 exporter;
        Image origImage;
        fillEmptyImageRandomly(origImage);

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(origImage)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, origImage));

        Image copyOfImage;
        const ImageImporter2403 importer;
        BOOST_CHECK(importer.deserialize(ss, copyOfImage, dh));

        BOOST_CHECK(origImage == copyOfImage);
    } // for r
}

// The following test checks equality for Image2403->Image_GDC->Image2403
BOOST_FIXTURE_TEST_CASE(isIoEmptyImageIdentity2403Gdc2403, Fixture2)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Image2403 image2403orig{unittests::Image2403TestSupport::createImage2403()};

        const Image2403Exporter2403 exporter;

        const IbeoDataHeader dh(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(image2403orig)), 0, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, image2403orig));

        Image imageGdc;
        const ImageImporter2403 importer;
        BOOST_CHECK(importer.deserialize(ss, imageGdc, dh));

        const ImageExporter2403 exporter2403;
        BOOST_CHECK(exporter2403.serialize(ss, imageGdc));
        const IbeoDataHeader dhGdc(
            exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(image2403orig)), 0, NTPTime());

        Image2403 image2403dup;
        BOOST_CHECK(image2403orig != image2403dup);
        const Image2403Importer2403 importer2403_2403;
        BOOST_CHECK(importer2403_2403.deserialize(ss, image2403dup, dh));
        BOOST_CHECK(image2403orig == image2403dup);
    } // for r
}

//==============================================================================

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

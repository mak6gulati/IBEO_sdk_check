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
//!\date June 19, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/image/Image.hpp>
#include <ibeo/common/sdk/datablocks/image/ImageBuffer.hpp>
#include <ibeo/common/sdk/datablocks/image/ImageFormat.hpp>

#include "common/TestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class ImageTestSupport : public TestSupport
{
public:
    ImageTestSupport()          = default;
    virtual ~ImageTestSupport() = default;

protected:
    static Image createImage();

    //========================================
    //!\brief Fill a Image instance with random values.
    //!\param[out] image  The Image to be filled.
    //----------------------------------------
    static void fillRandomly(Image& image);
    static void fillEmptyImageRandomly(Image& image);
    static void fillRandomly(Image& image, const uint16_t width, const uint16_t height);
}; // ImageTestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

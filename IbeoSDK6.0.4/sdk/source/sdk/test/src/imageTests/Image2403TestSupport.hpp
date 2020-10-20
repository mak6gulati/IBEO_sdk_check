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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/image/special/Image2403.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class Image2403TestSupport : public TestSupport
{
public:
    Image2403TestSupport()          = default;
    virtual ~Image2403TestSupport() = default;

protected:
    static Image2403 createImage2403();

    //========================================
    //!\brief Fill a Image2403 instance with random values.
    //!\param[out] image  The Image2403 to be filled.
    //----------------------------------------
    static void fillRandomly(Image2403& image);
    static void fillEmptyImageRandomly(Image2403& image);
    static void fillRandomly(Image2403& image, const uint16_t width, const uint16_t height);

protected:
    static const int32_t nbOfRepeats = 100;
}; // Image2403TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

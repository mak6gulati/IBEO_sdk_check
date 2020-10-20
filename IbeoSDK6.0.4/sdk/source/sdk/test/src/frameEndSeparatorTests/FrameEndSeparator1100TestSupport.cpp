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
//!\date Mar 19, 2018
//------------------------------------------------------------------------------

#include "FrameEndSeparator1100TestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

//==============================================================================

FrameEndSeparator1100 FrameEndSeparator1100TestSupport::createFrameSeparator()
{
    FrameEndSeparator1100 fes;
    fillRandomly(fes);
    return fes;
}

//==============================================================================

void FrameEndSeparator1100TestSupport::fillRandomly(FrameEndSeparator1100& fes)
{
    fes.setFrameId(getRandValue<uint32_t>());
    fes.setSizeOfThisFrame(getRandValue<uint32_t>());
    fes.setSizeOfNextFrame(getRandValue<uint32_t>());
    fes.setCreationTime(getRandValue<NTPTime>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

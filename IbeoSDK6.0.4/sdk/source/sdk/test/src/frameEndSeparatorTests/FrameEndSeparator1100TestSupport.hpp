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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/frameendseparator/FrameEndSeparator1100.hpp>

#include "common/TestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class FrameEndSeparator1100TestSupport : public TestSupport
{
public:
    FrameEndSeparator1100TestSupport()          = default;
    virtual ~FrameEndSeparator1100TestSupport() = default;

public:
    static FrameEndSeparator1100 createFrameSeparator();

protected:
    static void fillRandomly(FrameEndSeparator1100& fes);

protected:
    static const int32_t nbOfRepeats = 100;
}; // FrameIndex6130TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

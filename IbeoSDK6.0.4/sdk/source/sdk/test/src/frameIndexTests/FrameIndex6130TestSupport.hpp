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
//!\date Feb 12, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130.hpp>

#include "common/TestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class FrameIndex6130TestSupport : public TestSupport
{
public:
    FrameIndex6130TestSupport()          = default;
    virtual ~FrameIndex6130TestSupport() = default;

public:
    static FrameIndex6130 createFrameIndex();

protected:
    static void fillRandomly(FrameIndex6130& fi);

    static void fillRandomly(FramingPolicyIn6130& fp);

    static void fillRandomly(FrameIndexEntryIn6130& fie);

protected:
    static const int32_t nbOfRepeats = 100;
}; // FrameIndex6130TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

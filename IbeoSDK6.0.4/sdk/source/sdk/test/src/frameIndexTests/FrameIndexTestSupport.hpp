//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Jan 25, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/frameindex/FrameIndex.hpp>

#include "common/TestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class FrameIndexTestSupport : public TestSupport
{
public:
    FrameIndexTestSupport()          = default;
    virtual ~FrameIndexTestSupport() = default;

public:
    static FrameIndex createFrameIndex();

protected:
    static void fillRandomly(FrameIndex& fi);

    static void fillRandomly(FramingPolicy& fp);

    static void fillRandomly(FrameIndexEntry& fie);

protected:
    static const int32_t nbOfRepeats = 100;
}; // FrameIndexTestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

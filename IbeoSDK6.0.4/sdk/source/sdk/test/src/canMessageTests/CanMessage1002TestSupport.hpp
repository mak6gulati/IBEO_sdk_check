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

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/canmessage/CanMessage1002.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class CanMessage1002TestSupport : public ibeo::common::sdk::unittests::TestSupport
{
public:
    CanMessage1002TestSupport()           = default;
    ~CanMessage1002TestSupport() override = default;

public:
    static CanMessage1002 createCanMessage(const bool extCanId, const bool validTimeStamp);

protected:
    static void fillRandomly(CanMessage1002& canMsg, const bool extCanId, const bool validTimeStamp);

    static CanMessage1002::MsgType getRandomCanMessageType(const bool extCanId);

protected:
    static const int32_t nbOfRepeats = 100;
}; // FrameIndex6130TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

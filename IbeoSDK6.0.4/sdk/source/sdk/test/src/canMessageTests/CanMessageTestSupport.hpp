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
#include <ibeo/common/sdk/datablocks/canmessage/CanMessage.hpp>
#include <ibeo/common/sdk/datablocks/canmessage/CanMessage1002.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class CanMessageTestSupport : public ibeo::common::sdk::unittests::TestSupport
{
public:
    CanMessageTestSupport()           = default;
    ~CanMessageTestSupport() override = default;

public:
    static CanMessage createCanMessage(const bool extCanId, const bool validTimeStamp);

protected:
    static void fillRandomly(CanMessage& canMsg, const bool extCanId, const bool validTimeStamp);

protected:
    static const int32_t nbOfRepeats = 100;
}; //CanMessageTestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

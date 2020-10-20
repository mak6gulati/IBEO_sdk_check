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
//!\date Feb 12, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/ogpsimumessage/OGpsImuMessage.hpp>
#include <ibeo/common/sdk/datablocks/ogpsimumessage/special/OGpsImuMessage2610.hpp>

#include <vector>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class OGpsImuMessageTestSupport : public TestSupport
{
public:
    OGpsImuMessageTestSupport()          = default;
    virtual ~OGpsImuMessageTestSupport() = default;

    static ibeo::common::sdk::OGpsImuMessage createOGpsImuMessage();
    static ibeo::common::sdk::OGpsImuMessage2610 createOGpsImuMessage2610();

protected:
    static void fillRandomly(ibeo::common::sdk::OGpsImuMessage& oxMsg);
    static void fillRandomly(ibeo::common::sdk::OGpsImuMessage2610& oxMsg);

protected:
    static constexpr int32_t nbOfRepeats{1000};
}; // OGpsImuMessageTestSupport

//==============================================================================

template<>
std::vector<uint8_t> TestSupport::getRandValue();

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//! \date Feb 13, 2019
//------------------------------------------------------------------------------

#include "Destination3520TestSupport.hpp"
#include <math.h>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

Destination3520TestSupport::Destination3520TestSupport() : PositionWgs84_2604TestSupport() {}

//==============================================================================

ibeo::common::sdk::Destination3520 Destination3520TestSupport::createDestination3520()
{
    ibeo::common::sdk::Destination3520 d;
    fillRandomly(d);
    return d;
}

//==============================================================================

void Destination3520TestSupport::fillRandomly(ibeo::common::sdk::Destination3520& d)
{
    PositionWgs84 randPos;
    //PositionWgs84Sequence3510TestSupport::fillPosRandomly(randPos);
    // d.setTargetPosition(randPos);
    d.setTargetId(getRandValue<int64_t>());
    d.setTimestamp(getRandValue<NTPTime>());
    d.setSourceType(static_cast<Destination3520::SourceType>(getRandValue<uint8_t>()));
    d.setDestinationType(static_cast<Destination3520::DestinationType>(getRandValue<uint8_t>()));
    d.setPurposeType(static_cast<Destination3520::PurposeType>(getRandValue<uint8_t>()));
    d.setId(getRandValue<uint32_t>());
}

//==============================================================================

} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

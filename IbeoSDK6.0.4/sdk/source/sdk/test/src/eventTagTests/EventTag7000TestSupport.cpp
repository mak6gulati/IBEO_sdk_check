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
//!\date Mar 21, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "EventTag7000TestSupport.hpp"

#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

EventTag7000 EventTag7000TestSupport::createIbeoEvent7000()
{
    EventTag7000 et;
    fillRandomly(et);
    return et;
}

//==============================================================================

void EventTag7000TestSupport::fillRandomly(EventTag7000& et)
{
    et.setTagStart(getRandValue<NTPTime>());
    et.setTagEnd(getRandValue<NTPTime>());
    et.setFlags(getRandValue<uint8_t>());
    et.setTagClass(static_cast<EventTag7000::TagClass>(getRandValue<uint16_t>()));
    et.setTagId(getRandValue<uint32_t>());
    et.setTagString(getRandString(getRandValue<uint8_t>()));
    fillRandomly(et.getWgs84());
    et.setRoiWidth(getRandValue<uint64_t>());
    et.setRoiLength(getRandValue<uint64_t>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

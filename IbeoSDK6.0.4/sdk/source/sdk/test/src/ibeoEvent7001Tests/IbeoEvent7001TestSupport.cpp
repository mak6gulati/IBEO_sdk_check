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
//!\date Semptember 25, 2017
//------------------------------------------------------------------------------

#include "IbeoEvent7001TestSupport.hpp"

#include <math.h>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

IbeoEvent7001 IbeoEvent7001TestSupport::createIbeoEvent7001()
{
    IbeoEvent7001 o;
    fillRandomly(o);
    return o;
}

//==============================================================================

void IbeoEvent7001TestSupport::fillRandomly(IbeoEvent7001& od)
{
    od.setType(getRandValue<uint16_t>());
    od.setBody(getRandString(getRandValue<uint32_t>(500)));
    od.setAuthor(getRandString(getRandValue<uint32_t>(500)));
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

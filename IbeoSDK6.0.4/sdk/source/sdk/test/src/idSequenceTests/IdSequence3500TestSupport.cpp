//==============================================================================
//!\file
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date January 02, 2019
//------------------------------------------------------------------------------

#include "IdSequence3500TestSupport.hpp"
#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

IdSequence3500TestSupport::IdSequence3500TestSupport() : TestSupport() {}

//==============================================================================

void IdSequence3500TestSupport::fillRandomly3500(IdSequence3500& is)
{
    const uint8_t sequenceSize = getRandValue<uint8_t>(200);
    std::vector<int64_t> idSequence(sequenceSize, 0);

    for (uint8_t i = 0; i < sequenceSize; ++i)
    {
        idSequence.at(i) = getRandValue<int64_t>();
    }

    is.setIdSequence(idSequence);
    is.setSourceType(static_cast<IdSequence3500::SourceType>(getRandValue<uint8_t>()));
    is.setId(getRandValue<uint32_t>());
    is.setTimestamp(getRandValue<NTPTime>());
}

//==============================================================================

IdSequence3500 IdSequence3500TestSupport::createIdSequence3500()
{
    ibeo::common::sdk::IdSequence3500 o;
    fillRandomly3500(o);
    return o;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

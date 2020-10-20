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
//!\date Sept 05, 2018
//------------------------------------------------------------------------------

#include "IdSequenceTestSupport.hpp"
#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

IdSequenceTestSupport::IdSequenceTestSupport() : TestSupport() {}

//==============================================================================

void IdSequenceTestSupport::fillRandomly(IdSequence& is)
{
    const uint8_t sequenceSize = getRandValue<uint8_t>(200);
    std::vector<int64_t> idSequence(sequenceSize, 0);

    for (uint8_t i = 0; i < sequenceSize; ++i)
    {
        idSequence.at(i) = getRandValue<int64_t>();
    }

    is.setIdSequence(idSequence);
    is.setSourceType(static_cast<IdSequence::SourceType>(getRandValue<uint8_t>()));
    is.setId(getRandValue<uint32_t>());
    is.setTimestamp(getRandValue<NTPTime>());
}

//==============================================================================

ibeo::common::sdk::IdSequence IdSequenceTestSupport::createIdSequence()
{
    ibeo::common::sdk::IdSequence o;
    fillRandomly(o);
    return o;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

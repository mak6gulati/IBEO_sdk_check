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

#include "FrameIndex6130TestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

//==============================================================================

FrameIndex6130 FrameIndex6130TestSupport::createFrameIndex()
{
    ibeo::common::sdk::FrameIndex6130 fi;
    fillRandomly(fi);
    return fi;
}

//==============================================================================

void FrameIndex6130TestSupport::fillRandomly(FrameIndex6130& fi)
{
    FramingPolicyIn6130 fp;
    fillRandomly(fp);
    fi.setFramingPolicy(fp);

    const uint16_t nbOfFrames{getRandValue<uint16_t>()};

    FrameIndexEntryIn6130 fie;
    for (uint32_t n = 0; n < nbOfFrames; ++n)
    {
        fillRandomly(fie);
        fi.addFrame(fie);
    }
}

//==============================================================================

void FrameIndex6130TestSupport::fillRandomly(FramingPolicyIn6130& fp)
{
    fp.setTriggerInNewFrame(getRandValue<bool>());

    FramingPolicyIn6130::TriggerSet& ts = fp.getTriggers();

    // not more than 30 triggers are supported by 0x6130.
    const uint8_t nbOfTriggers{getRandValue<uint8_t>(30)};
    for (uint32_t n = 0; n < nbOfTriggers; ++n)
    {
        const DataTypeId dtId{DataTypeId(getRandValue<uint16_t>())};
        const uint8_t deviceId{getRandValue<uint8_t>()};
        ts[dtId] = deviceId; // insert or replace
    }
}

//==============================================================================

void FrameIndex6130TestSupport::fillRandomly(FrameIndexEntryIn6130& fie)
{
    fie.setFilePosition(getRandValue<uint64_t>());
    fie.setTimeOffsetMs(getRandValue<uint64_t>());
    fie.setDeviceId(getRandValue<uint8_t>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

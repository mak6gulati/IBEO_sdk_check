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

#include "FrameIndexTestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

//==============================================================================

FrameIndex FrameIndexTestSupport::createFrameIndex()
{
    ibeo::common::sdk::FrameIndex fi;
    fillRandomly(fi);
    return fi;
}

//==============================================================================

void FrameIndexTestSupport::fillRandomly(FrameIndex& fi)
{
    FramingPolicy fp;
    fillRandomly(fp);
    fi.setFramingPolicy(fp);

    const uint16_t nbOfFrames{getRandValue<uint16_t>()};

    FrameIndexEntry fie;
    for (uint32_t n = 0; n < nbOfFrames; ++n)
    {
        fillRandomly(fie);
        fi.addFrame(fie);
    }
}

//==============================================================================

void FrameIndexTestSupport::fillRandomly(FramingPolicy& fp)
{
    fp.setTriggerInNewFrame(getRandValue<bool>());

    FramingPolicy::TriggerSet& ts = fp.getTriggers();

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

void FrameIndexTestSupport::fillRandomly(FrameIndexEntry& fie)
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

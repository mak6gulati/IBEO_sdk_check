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

#include "OGpsImuMessageTestSupport.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

ibeo::common::sdk::OGpsImuMessage OGpsImuMessageTestSupport::createOGpsImuMessage()
{
    ibeo::common::sdk::OGpsImuMessage oxMsg;
    fillRandomly(oxMsg);
    return oxMsg;
}

//==============================================================================

ibeo::common::sdk::OGpsImuMessage2610 OGpsImuMessageTestSupport::createOGpsImuMessage2610()
{
    ibeo::common::sdk::OGpsImuMessage2610 oxMsg;
    fillRandomly(oxMsg);
    return oxMsg;
}

//==============================================================================

void OGpsImuMessageTestSupport::fillRandomly(ibeo::common::sdk::OGpsImuMessage& oxMsg)
{
    oxMsg.setIpAddress(getRandValue<uint32_t>());
    oxMsg.getData() = getRandValue<std::vector<uint8_t>>();
}

//==============================================================================

void OGpsImuMessageTestSupport::fillRandomly(ibeo::common::sdk::OGpsImuMessage2610& oxMsg)
{
    oxMsg.setIpAddress(getRandValue<uint32_t>());
    oxMsg.getData() = getRandValue<std::vector<uint8_t>>();
}

//==============================================================================

template<>
std::vector<uint8_t> TestSupport::getRandValue()
{
    std::vector<uint8_t> vec;
    const size_t maxVecSize    = 10000;
    const uint32_t vecElements = getRandValue<uint32_t>(maxVecSize);

    vec.reserve(vecElements);
    for (uint32_t i = 0; i < vecElements; ++i)
    {
        vec.push_back(getRandValue<uint8_t>());
    }

    return vec;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

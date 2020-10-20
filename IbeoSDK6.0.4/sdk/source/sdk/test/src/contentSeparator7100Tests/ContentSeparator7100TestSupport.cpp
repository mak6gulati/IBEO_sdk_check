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
//! \date Feb 12, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "ContentSeparator7100TestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

//==============================================================================

template<>
void ContentSeparatorTestSupport::fillRandomly(ibeo::common::sdk::ContentSeparator7100& cs)
{
    cs.setSeparatorType(getRandValue<ContentSeparatorTypeIn7100>());
    cs.setContentSize(getRandValue<uint32_t>());
}

//==============================================================================

template<>
ContentSeparatorTypeIn7100 TestSupport::getRandValue()
{
    const int maxVal = static_cast<uint8_t>(ContentSeparatorTypeIn7100::StaticEnd);

    return static_cast<ContentSeparatorTypeIn7100>(getRandValue<uint8_t>(maxVal));
}

//==============================================================================

template<>
ContentSeparatorTypeIn7100 TestSupport ::getDifferentRandValue(const ContentSeparatorTypeIn7100& oldValue)
{
    const int maxVal  = static_cast<uint8_t>(ContentSeparatorTypeIn7100::StaticEnd);
    const auto newVal = getDifferentRandValue<uint8_t>(maxVal, static_cast<uint8_t>(static_cast<uint8_t>(oldValue)));
    return static_cast<ContentSeparatorTypeIn7100>(newVal);
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

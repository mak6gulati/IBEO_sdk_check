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
//!\date Feb 4th, 2019
//------------------------------------------------------------------------------

//==============================================================================

#include "ContentSeparatorTestSupport.hpp"

#include <cmath>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

ContentSeparatorTestSupport::ContentSeparatorTestSupport() : TestSupport() {}

//==============================================================================

template<>
ibeo::common::sdk::ContentSeparator ContentSeparatorTestSupport::createContentSeparator<ContentSeparator>()
{
    ibeo::common::sdk::ContentSeparator cs;
    fillRandomly(cs);
    return cs;
}

//==============================================================================

template<>
void ContentSeparatorTestSupport::fillRandomly(ibeo::common::sdk::ContentSeparator& contentSeparator)
{
    contentSeparator.setSeparatorType(getRandValue<ContentSeparatorTypeIn7100>());
    contentSeparator.setContentSize(getRandValue<uint32_t>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

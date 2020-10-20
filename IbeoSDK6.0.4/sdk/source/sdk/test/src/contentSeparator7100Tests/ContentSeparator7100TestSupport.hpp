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

#pragma once

//==============================================================================
#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "ContentSeparatorTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class ContentSeparator7100TestSupport : public ContentSeparatorTestSupport
{
public:
    ContentSeparator7100TestSupport()          = default;
    virtual ~ContentSeparator7100TestSupport() = default;
}; // ContentSeparator7100TestSupport

//==============================================================================

template<>
ContentSeparatorTypeIn7100 TestSupport::getRandValue();

template<>
ContentSeparatorTypeIn7100 TestSupport::getDifferentRandValue(const ContentSeparatorTypeIn7100& oldValue);

template<>
void ContentSeparatorTestSupport::fillRandomly(ContentSeparator7100& cs);

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

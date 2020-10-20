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
//!\date Jan 16, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

bool operator==(const ContentSeparator7100& lhs, const ContentSeparator7100& rhs)
{
    return (lhs.getSeparatorType() == rhs.getSeparatorType()) && (lhs.getContentSize() == rhs.getContentSize());
}

//==============================================================================

bool operator!=(const ContentSeparator7100& lhs, const ContentSeparator7100& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

//==============================================================================
//!\file
//!\verbatim
//! ------------------------------------------
//! (C) 2019 Ibeo Automotive Systems GmbH, Hamburg, Germany
//! ------------------------------------------
//!
//! Created on: Feb 4, 2019
//!         by: Michael Haar
//!\endverbatim
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/datablocks/contentseparator/ContentSeparator.hpp>
#include <ibeo/common/sdk/Math.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ContentSeparator::ContentSeparator() : DataContainerBase() {}

//==============================================================================
//==============================================================================

bool operator==(const ContentSeparator& lhs, const ContentSeparator& rhs) { return lhs.m_delegate == rhs.m_delegate; }

//==============================================================================

bool operator!=(const ContentSeparator& lhs, const ContentSeparator& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

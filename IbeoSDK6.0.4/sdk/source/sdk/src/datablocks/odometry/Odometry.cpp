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
//! \date Jan 29, 2019
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/odometry/Odometry.hpp>
#include <ibeo/common/sdk/Math.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

Odometry::Odometry() : DataContainerBase() {}

//==============================================================================
//==============================================================================

bool operator==(const Odometry& lhs, const Odometry& rhs) { return lhs.m_delegate == rhs.m_delegate; }

//==============================================================================

bool operator!=(const Odometry& lhs, const Odometry& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Aug 16, 2018
//!\brief Lane which has a list of LaneSegments
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/carriageway/special/LaneTemplate.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace lanes {
//==============================================================================

// Forward declaration of template class.
class LaneSegmentIn6972;

//==============================================================================
//!\brief A LaneIn6972 represents a lane of a specific type within a \ref CarriageWaySegmentIn6972
//!
//! Each LaneIn6972 has a unique id within the parent \ref CarriageWaySegmentIn6972
//!
//! A LaneIn6972 holds a list of LaneSegmentIn6972 segments as well as pointers to preceding,
//! following and neighboring Lanes.
//!
//! The segmentation of a whole road is as following:
//!
//!\ref CarriageWayIn6972 \htmlonly&#8594;\endhtmlonly
//!\ref CarriageWaySegmentIn6972 \htmlonly&#8594;\endhtmlonly
//!\ref LaneIn6972 \htmlonly&#8594;\endhtmlonly
//!\ref LaneSegmentIn6972
//!
//! The connection is handled using smart pointers. Therefore it is not possible
//! to create an instance of this class, but calling \ref create will return
//! a shared pointer to a new LaneIn6972.
//!
//!\sa CarriageWayIn6972 \sa CarriageWaySegmentIn6972 \sa LaneSegmentIn6972
//!
//!\note The implementation of this class is done via templates (\sa LaneTemplate).
//------------------------------------------------------------------------------
using LaneIn6972 = LaneTemplate<LaneSegmentIn6972>;

//==============================================================================
} // namespace lanes
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

// Define classes previously declared as forward.
#include <ibeo/common/sdk/datablocks/carriageway/special/LaneSegmentIn6972.hpp>

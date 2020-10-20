//==============================================================================
//!\file
//!\brief CarriageWaySegment6970 which has a constant number of lanes of type LaneIn6970
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Oct 9, 2014
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWaySegmentTemplate.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/special/LaneIn6970.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace lanes {
//==============================================================================

//==============================================================================
//!\brief A CarriageWaySegment6970 represents a single segment of a \ref CarriageWayIn6970.
//!
//! Each CarriageWaySegment6970 has a unique id within the parent \ref CarriageWayIn6970.
//!
//! A \ref CarriageWayIn6970 holds a constant number of lanes of type LaneIn6970. The segmentation of a whole
//! \ref CarriageWayIn6970 is as following:
//!
//!\ref CarriageWayIn6970 \htmlonly&#8594;\endhtmlonly
//!\ref CarriageWaySegmentIn6970 \htmlonly&#8594;\endhtmlonly
//!\ref LaneIn6970 \htmlonly&#8594;\endhtmlonly
//!\ref LaneSegmentIn6970
//!
//! The connection is handled using smart pointers. Therefore it is not possible
//! to create an instance of this class, but calling \ref create() will return
//! a shared pointer to a new CarriageWaySegmentIn6970.
//!
//!\sa CarriageWayIn6970 \sa LaneIn6970 \sa LaneSegmentIn6970
//!
//!\note The implementation of this class is done via templates (\sa CarriageWaySegmentTemplate).
//------------------------------------------------------------------------------
using CarriageWaySegmentIn6970 = CarriageWaySegmentTemplate<LaneSegmentIn6970>;

//==============================================================================
} // namespace lanes
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

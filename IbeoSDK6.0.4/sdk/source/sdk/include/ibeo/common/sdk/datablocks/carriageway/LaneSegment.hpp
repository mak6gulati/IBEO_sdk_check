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
//! \date Dec 19, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/carriageway/special/LaneSegmentIn6972.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/LaneSupportPoint.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace lanes {
//==============================================================================

//==============================================================================
//! A LaneSegment represents a \ref Lane segment within a parent Lane.
//! Each LaneSegment has a unique id within the parent \ref Lane
//!
//! A Lane Segment ends if the approximation error through straight bounding lines
//! reaches a certain value, or if a \ref CarriageWaySegment ends.
//!
//! The segmentation of a whole \ref CarriageWay is as following:
//!
//!\ref CarriageWay \htmlonly&#8594;\endhtmlonly
//!\ref CarriageWaySegment \htmlonly&#8594;\endhtmlonly
//!\ref Lane \htmlonly&#8594;\endhtmlonly
//!\ref LaneSegment
//!
//! The connection is handled using smart pointers. Therefore it is not possible
//! to create an instance of this class, but calling \ref create will return
//! a shared pointer to a new LaneSegment.
//!
//!\sa CarriageWay \sa CarriageWaySegment \sa Lane
//------------------------------------------------------------------------------
using LaneSegment = LaneSegmentIn6972;

//==============================================================================
} // namespace lanes
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

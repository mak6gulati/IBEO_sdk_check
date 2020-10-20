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

#include <ibeo/common/sdk/datablocks/carriageway/special/LaneIn6972.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/LaneSegment.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace lanes {
//==============================================================================

//==============================================================================
//!\brief A Lane represents a lane of a specific type within a \ref CarriageWaySegment
//!
//! Each Lane has a unique id within the parent \ref CarriageWaySegment
//!
//! A Lane holds a list of LaneSegment segments as well as pointers to preceding,
//! following and neighboring Lanes.
//!
//! The segmentation of a whole road is as following:
//!
//!\ref CarriageWay \htmlonly&#8594;\endhtmlonly
//!\ref CarriageWaySegment \htmlonly&#8594;\endhtmlonly
//!\ref Lane \htmlonly&#8594;\endhtmlonly
//!\ref LaneSegment
//!
//! The connection is handled using smart pointers. Therefore it is not possible
//! to create an instance of this class, but calling \ref create will return
//! a shared pointer to a new Lane.
//!
//!\sa CarriageWay \sa CarriageWaySegment \sa LaneSegment
//!
//!\note The implementation of this class is done via templates (\sa LaneTemplate).
//------------------------------------------------------------------------------
using Lane = LaneIn6972;

//==============================================================================
} // namespace lanes
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//! \date Dec 13, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6970.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class CarriageWayList6970SerializedSize6970
{
public:
    static std::streamsize getSerializedSize(const CarriageWayList6970& c);
    static std::streamsize getSerializedSize(const lanes::CarriageWayIn6970& cw);
    static std::streamsize getSerializedSize(const lanes::CarriageWaySegmentIn6970& segment);
    static std::streamsize getSerializedSize(const lanes::LaneIn6970& lane);
    static std::streamsize getSerializedSize(const lanes::LaneSegmentIn6970& laneSegment);
    static std::streamsize getSerializedSize(const lanes::LaneSupportPointIn6970& laneSupportPoint);
}; //CarriageWayList6970SerializedSize6970

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

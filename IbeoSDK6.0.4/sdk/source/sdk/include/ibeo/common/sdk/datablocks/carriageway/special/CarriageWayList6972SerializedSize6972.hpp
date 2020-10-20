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

#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6972.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class CarriageWayList6972SerializedSize6972
{
public:
    static std::streamsize getSerializedSize(const CarriageWayList6972& c);
    static std::streamsize getSerializedSize(const lanes::CarriageWayIn6972& cw);
    static std::streamsize getSerializedSize(const lanes::CarriageWaySegmentIn6972& segment);
    static std::streamsize getSerializedSize(const lanes::LaneIn6972& lane);
    static std::streamsize getSerializedSize(const lanes::LaneSegmentIn6972& laneSegment);
    static std::streamsize getSerializedSize(const lanes::LaneSupportPointIn6972& laneSupportPoint);
}; //CarriageWayList6972SerializedSize6972

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

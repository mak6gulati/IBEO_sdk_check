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

#include <ibeo/common/sdk/datablocks/carriageway/CarriageWayList.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class CarriageWayListSerializedSize6970
{
public:
    static std::streamsize getSerializedSize(const CarriageWayList& c);
    static std::streamsize getSerializedSize(const lanes::CarriageWay& cw);
    static std::streamsize getSerializedSize(const lanes::CarriageWaySegment& segment);
    static std::streamsize getSerializedSize(const lanes::Lane& lane);
    static std::streamsize getSerializedSize(const lanes::LaneSegment& laneSegment);
    static std::streamsize getSerializedSize(const lanes::LaneSupportPoint& laneSupportPoint);
}; //CarriageWayListSerializedSize6970

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

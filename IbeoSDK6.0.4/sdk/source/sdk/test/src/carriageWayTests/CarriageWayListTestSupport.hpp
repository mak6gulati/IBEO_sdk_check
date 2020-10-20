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
//!\date Mar 19, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6970.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6972.hpp>

#include <common/TestSupport.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class CarriageListWayTestSupport : public TestSupport
{
public:
    CarriageListWayTestSupport()          = default;
    virtual ~CarriageListWayTestSupport() = default;

public:
    //	static CarriageWayList6970 createCwListDb();
    //	static CarriageWayList6970Container createCwList();
    //	static lanes::CarriageWayIn6970Ptr createCw();
    //	static lanes::CarriageWayIn6970SegmentPtr createCwSegment();

    //static lanes::LaneIn6970Ptr createEmptyLane();
    template<typename T>
    static T createEmptyLane();

    //static lanes::LaneIn6970Ptr createLane();
    template<typename T>
    static T createLane();

    //	static lanes::LaneSegmentIn6970Ptr createEmptyLaneSegment();
    template<typename T>
    static T createEmptyLaneSegment();

    //static lanes::LaneSegmentIn6970Ptr createLaneSegment();
    template<typename T>
    static T createLaneSegment();

    //static void connectSegments(lanes::LaneIn6970Ptr lane);
    template<typename T>
    static void connectSegments(T lane);

protected:
    template<typename T>
    static T getLaneSupportPoint();

    //	static void fillRandomly(CarriageWayList6970& cwl);
    //	static void fillRandomly(lanes::CarriageWayIn6970& cw);
    //	static void fillRandomly(lanes::CarriageWaySegmentIn6970& cws);
    //	static void fillRandomly(lanes::LaneIn6970& lane);
    //	static void fillRandomly(lanes::LaneSegmentIn6970& ls);

    // 	static void fillRandomly(CarriageWayList6972& cwl);
    //	static void fillRandomly(lanes::CarriageWayIn6972& cw);
    //	static void fillRandomly(lanes::CarriageWaySegmentIn6972& cws);
    //	static void fillRandomly(lanes::LaneIn6972& lane);
    //	static void fillRandomly(lanes::LaneSegmentIn6972& ls);

protected:
    static const int32_t nbOfRepeats = 100;
}; // CarriageListWay6970TestSupport

template<>
lanes::LaneIn6970::Ptr CarriageListWayTestSupport::createEmptyLane();
template<>
lanes::LaneIn6972::Ptr CarriageListWayTestSupport::createEmptyLane();

template<>
lanes::LaneIn6970::Ptr CarriageListWayTestSupport::createLane();
template<>
lanes::LaneIn6972::Ptr CarriageListWayTestSupport::createLane();

template<>
lanes::LaneSegmentIn6970::Ptr CarriageListWayTestSupport::createEmptyLaneSegment();
template<>
lanes::LaneSegmentIn6972::Ptr CarriageListWayTestSupport::createEmptyLaneSegment();

template<>
lanes::LaneSegmentIn6970::Ptr CarriageListWayTestSupport::createLaneSegment();
template<>
lanes::LaneSegmentIn6972::Ptr CarriageListWayTestSupport::createLaneSegment();

template<>
void CarriageListWayTestSupport::connectSegments(lanes::LaneIn6970::Ptr lane);
template<>
void CarriageListWayTestSupport::connectSegments(lanes::LaneIn6972::Ptr lane);

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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

//==============================================================================

#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6972SerializedSize6972.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize CarriageWayList6972SerializedSize6972::getSerializedSize(const CarriageWayList6972& c)
{
    std::streamsize size = std::streamsize(sizeof(uint64_t)); // nb. of elements

    for (const lanes::CarriageWayIn6972::Ptr& cw : c.getCarriageWays())
    {
        size += getSerializedSize(*cw);
    }

    return size;
}

//==============================================================================

std::streamsize CarriageWayList6972SerializedSize6972::getSerializedSize(const lanes::CarriageWayIn6972& cw)
{
    std::streamsize size = std::streamsize(sizeof(uint64_t)) // id
                           + std::streamsize(sizeof(uint16_t)) // nationalId
                           + std::streamsize(sizeof(uint8_t)) // type
                           + std::streamsize(sizeof(uint64_t)); // nb. of segments

    for (const auto& keyValuePair : cw.getCwSegmentsMap())
    {
        if (keyValuePair.second == nullptr)
        {
            throw std::logic_error("Null-segment found in map!");
        }

        size += getSerializedSize(*keyValuePair.second);
    }

    return size;
}

//==============================================================================

std::streamsize CarriageWayList6972SerializedSize6972::getSerializedSize(const lanes::CarriageWaySegmentIn6972& segment)
{
    std::streamsize size = std::streamsize(sizeof(uint64_t)) // id
                           + std::streamsize(sizeof(uint8_t)) // nb. of lanes
                           + std::streamsize(sizeof(uint64_t)) // nextId
                           + std::streamsize(sizeof(uint64_t)); // prevId

    for (const auto& keyValuePair : segment.getLanesMap())
    {
        if (keyValuePair.second == nullptr)
        {
            throw std::logic_error("Null-lane found in map!");
        }

        size += getSerializedSize(*keyValuePair.second);
    }

    return size;
}

//==============================================================================

std::streamsize CarriageWayList6972SerializedSize6972::getSerializedSize(const lanes::LaneIn6972& lane)
{
    std::streamsize size = std::streamsize(sizeof(uint8_t)) // id
                           + std::streamsize(sizeof(uint64_t)) // laneId
                           + std::streamsize(sizeof(uint8_t)) // type
                           + std::streamsize(sizeof(uint8_t)) // nextLaneId
                           + std::streamsize(sizeof(uint8_t)) // prevLaneId
                           + std::streamsize(sizeof(uint8_t)) // leftLaneId
                           + std::streamsize(sizeof(uint8_t)) // rightLaneId
                           + std::streamsize(sizeof(uint64_t)); // nb. of segments

    for (const auto& keyValuePair : lane.getLaneSegmentsMap())
    {
        if (keyValuePair.second == nullptr)
        {
            throw std::logic_error("Null-lane-segment found in map!");
        }

        size += getSerializedSize(*keyValuePair.second);
    }

    return size;
}

//==============================================================================

std::streamsize CarriageWayList6972SerializedSize6972::getSerializedSize(const lanes::LaneSegmentIn6972& laneSegment)
{
    std::streamsize size = std::streamsize(sizeof(uint64_t)) // id
                           + std::streamsize(sizeof(uint64_t)) // nextId
                           + std::streamsize(sizeof(uint64_t)) // prevId
                           + std::streamsize(sizeof(uint64_t)) // leftId
                           + std::streamsize(sizeof(uint64_t)) // rightId
                           + std::streamsize(sizeof(uint64_t)) // markingLeft
                           + std::streamsize(sizeof(uint64_t)) // markingRight
                           + std::streamsize(sizeof(uint8_t)) // leftBoundaryType
                           + std::streamsize(sizeof(uint8_t)) // rightBoundaryType
                           + std::streamsize(sizeof(uint8_t)) // nextInNewSeg
                           + std::streamsize(sizeof(uint8_t)) // prevInNewSeg
                           + std::streamsize(sizeof(float)) // markingWidthLeft
                           + std::streamsize(sizeof(float)) // markingWidthRight
                           + std::streamsize(sizeof(float)) // medianDashLengthLeft
                           + std::streamsize(sizeof(float)) // medianDashLengthRight
                           + std::streamsize(sizeof(float)) // medianGapLengthLeft
                           + std::streamsize(sizeof(float)) // medianGapLengthRight
                           + getSerializedSize(laneSegment.getStartPoint()); // startPoint

    return size;
}

//==============================================================================

std::streamsize
CarriageWayList6972SerializedSize6972::getSerializedSize(const lanes::LaneSupportPointIn6972& laneSupportPoint)
{
    std::streamsize size = std::streamsize(sizeof(double_t)) // latitudeInDeg
                           + std::streamsize(sizeof(double_t)) // longitudeInDeg
                           + std::streamsize(sizeof(double_t)) // courseAngelInDeg
                           + serializedSize(laneSupportPoint.getLeftOffset()) // lineOffsetLeft
                           + serializedSize(laneSupportPoint.getRightOffset()); // lineOffsetRight

    return size;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

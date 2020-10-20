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
//!\date Jul 31, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6972Exporter6972.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6972SerializedSize6972.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::CarriageWayList6972;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_CarriageWayList6972>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return CarriageWayList6972SerializedSize6972::getSerializedSize(*container);
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_CarriageWayList6972>::serialize(std::ostream& os,
                                                                      const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, static_cast<uint64_t>(container->getCarriageWays().size()));

    for (const lanes::CarriageWayIn6972::Ptr& cw : container->getCarriageWays())
    {
        if (!serialize(os, *cw))
        {
            return false;
        }
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_CarriageWayList6972>::serialize(std::ostream& os,
                                                                      const lanes::CarriageWayIn6972& cw)
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, cw.m_id);
    ibeo::common::sdk::writeBE(os, cw.m_nationalId);
    ibeo::common::sdk::writeBE(os, static_cast<uint8_t>(cw.m_type));
    ibeo::common::sdk::writeBE(os, static_cast<uint64_t>(cw.m_cwSegmentsMap.size()));

    for (const auto& cwsme : cw.m_cwSegmentsMap)
    {
        if (cwsme.second == nullptr)
        {
            throw std::logic_error("Null-carriage-way-segment found in map!");
        }

        if (!serialize(os, *cwsme.second))
        {
            return false;
        }
    }

    return !os.fail()
           && ((streamposToInt64(os.tellp()) - startPos)
               == CarriageWayList6972SerializedSize6972::getSerializedSize(cw));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_CarriageWayList6972>::serialize(std::ostream& os,
                                                                      const lanes::CarriageWaySegmentIn6972& cws)
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, cws.m_id);
    ibeo::common::sdk::writeBE(os, static_cast<uint8_t>(cws.m_lanesMap.size()));
    ibeo::common::sdk::writeBE(os, cws.m_nextId);
    ibeo::common::sdk::writeBE(os, cws.m_prevId);

    for (const auto& lme : cws.m_lanesMap)
    {
        if (lme.second == nullptr)
        {
            throw std::logic_error("Null-lane found in map!");
        }

        if (!serialize(os, *lme.second))
        {
            return false;
        }
    } // for

    return !os.fail()
           && ((streamposToInt64(os.tellp()) - startPos)
               == CarriageWayList6972SerializedSize6972::getSerializedSize(cws));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_CarriageWayList6972>::serialize(std::ostream& os, const lanes::LaneIn6972& lane)
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, lane.m_id);
    ibeo::common::sdk::writeBE(os, lane.m_laneId);
    ibeo::common::sdk::writeBE(os, static_cast<uint8_t>(lane.m_type));
    ibeo::common::sdk::writeBE(os, lane.m_nextLaneId);
    ibeo::common::sdk::writeBE(os, lane.m_prevLaneId);
    ibeo::common::sdk::writeBE(os, lane.m_leftLaneId);
    ibeo::common::sdk::writeBE(os, lane.m_rightLaneId);
    ibeo::common::sdk::writeBE(os, static_cast<uint64_t>(lane.m_laneSegmentsMap.size()));

    // write all segments
    for (const auto& lsme : lane.m_laneSegmentsMap)
    {
        if (lsme.second == nullptr)
        {
            throw std::logic_error("Null-lane-segment found in map!");
        }

        //		std::cerr << "Lser: LS-Id: " << lsme.second->getId() << std::endl;
        if (!serialize(os, *lsme.second))
        {
            return false;
        }
    } // for

    return !os.fail()
           && ((streamposToInt64(os.tellp()) - startPos)
               == CarriageWayList6972SerializedSize6972::getSerializedSize(lane));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_CarriageWayList6972>::serialize(std::ostream& os,
                                                                      const lanes::LaneSegmentIn6972& laneSeg)
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, laneSeg.m_id);
    ibeo::common::sdk::writeBE(os, laneSeg.m_nextId);
    ibeo::common::sdk::writeBE(os, laneSeg.m_prevId);
    ibeo::common::sdk::writeBE(os, laneSeg.m_leftId);
    ibeo::common::sdk::writeBE(os, laneSeg.m_rightId);
    ibeo::common::sdk::writeBE(
        os, static_cast<uint64_t>(laneSeg.m_markingLeft)); // Type is uint8_t but is serialized as uint64_t!
    ibeo::common::sdk::writeBE(
        os, static_cast<uint64_t>(laneSeg.m_markingRight)); // Type is uint8_t but is serialized as uint64_t!
    ibeo::common::sdk::writeBE(os, static_cast<uint8_t>(laneSeg.m_boundaryLeft));
    ibeo::common::sdk::writeBE(os, static_cast<uint8_t>(laneSeg.m_boundaryRight));

    ibeo::common::sdk::writeBE(os, laneSeg.m_nextInNewSeg);
    ibeo::common::sdk::writeBE(os, laneSeg.m_prevInNewSeg);

    ibeo::common::sdk::writeBE(os, laneSeg.m_markingWidthLeft);
    ibeo::common::sdk::writeBE(os, laneSeg.m_markingWidthRight);

    ibeo::common::sdk::writeBE(os, laneSeg.m_medianDashLengthLeft);
    ibeo::common::sdk::writeBE(os, laneSeg.m_medianDashLengthRight);

    ibeo::common::sdk::writeBE(os, laneSeg.m_medianGapLengthLeft);
    ibeo::common::sdk::writeBE(os, laneSeg.m_medianGapLengthRight);

    // write LaneSupportPoint
    if (!serialize(os, laneSeg.m_start))
    {
        return false;
    }

    return !os.fail()
           && ((streamposToInt64(os.tellp()) - startPos)
               == CarriageWayList6972SerializedSize6972::getSerializedSize(laneSeg));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_CarriageWayList6972>::serialize(std::ostream& os,
                                                                      const lanes::LaneSupportPointIn6972& point)
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, point.m_longitudeInDeg);
    ibeo::common::sdk::writeBE(os, point.m_latitudeInDeg);
    ibeo::common::sdk::writeBE(os, point.m_courseAngelInDeg);
    ibeo::common::sdk::writeBE(os, point.m_lineOffsetLeft);
    ibeo::common::sdk::writeBE(os, point.m_lineOffsetRight);

    return !os.fail()
           && ((streamposToInt64(os.tellp()) - startPos)
               == CarriageWayList6972SerializedSize6972::getSerializedSize(point));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

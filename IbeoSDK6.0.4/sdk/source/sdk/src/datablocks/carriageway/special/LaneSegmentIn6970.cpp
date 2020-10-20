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
//!\date Oct 9, 2014
//!\brief Segment of a lane for data type 0x6970
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/carriageway/special/LaneSegmentIn6970.hpp>
#include <ibeo/common/sdk/Line2d.hpp>
#include <ibeo/common/sdk/TransformationMatrix2d.hpp>

#include <ibeo/common/sdk/io.hpp>

#include <vector>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace lanes {
//==============================================================================

LaneSegmentIn6970::Ptr LaneSegmentIn6970::create() { return Ptr(new LaneSegmentIn6970()); }

//==============================================================================

LaneSegmentIn6970::Ptr LaneSegmentIn6970::create(LaneIn6970::Ptr parent) { return Ptr(new LaneSegmentIn6970(parent)); }

//==============================================================================

LaneSegmentIn6970::Ptr LaneSegmentIn6970::create(const LaneSupportPointIn6970& laneStart)
{
    return Ptr(new LaneSegmentIn6970(laneStart));
}

//==============================================================================

LaneSegmentIn6970::Ptr LaneSegmentIn6970::create(const uint64_t& id,
                                                 const LaneMarkingType& markingLeft,
                                                 const LaneMarkingType& markingRight,
                                                 const LaneBoundaryType& boundaryLeft,
                                                 const LaneBoundaryType& boundaryRight,
                                                 const LaneSupportPointIn6970& laneStart,
                                                 const uint64_t& nextId,
                                                 const uint64_t& prevId,
                                                 const uint64_t& leftId,
                                                 const uint64_t& rightId,
                                                 const bool& nextInNewSeg,
                                                 const bool& prevInNewSeg,
                                                 LaneIn6970::Ptr parent)
{
    return Ptr(new LaneSegmentIn6970(id,
                                     markingLeft,
                                     markingRight,
                                     boundaryLeft,
                                     boundaryRight,
                                     laneStart,
                                     nextId,
                                     prevId,
                                     leftId,
                                     rightId,
                                     nextInNewSeg,
                                     prevInNewSeg,
                                     parent));
}

//==============================================================================

LaneSegmentIn6970::Ptr LaneSegmentIn6970::copy(const LaneSegmentIn6970::Ptr& other)
{
    Ptr out(new LaneSegmentIn6970());

    out->setId(other->getId());
    out->setLeftMarkingType(other->getLeftMarkingType());
    out->setRightMarkingType(other->getRightMarkingType());
    out->setLeftBorderType(other->getLeftBoundaryType());
    out->setRightBorderType(other->getRightBoundaryType());
    out->setStartPoint(other->getStartPoint());
    out->setNextId(other->getNextId());
    out->setPrevId(other->getPrevId());
    out->setLeftId(other->getLeftId());
    out->setRightId(other->getRightId());
    out->setNextInNewSeg(other->isNextInNewSeg());
    out->setPrevInNewSeg(other->isPrevInNewSeg());

    return out;
}

//==============================================================================

LaneSegmentIn6970::LaneSegmentIn6970(const uint64_t& id,
                                     const LaneMarkingType& markingLeft,
                                     const LaneMarkingType& markingRight,
                                     const LaneBoundaryType& boundaryLeft,
                                     const LaneBoundaryType& boundaryRight,
                                     const LaneSupportPointIn6970& laneStart,
                                     const uint64_t& nextId,
                                     const uint64_t& prevId,
                                     const uint64_t& leftId,
                                     const uint64_t& rightId,
                                     const bool& nextInNewSeg,
                                     const bool& prevInNewSeg,
                                     LaneIn6970::Ptr parent)
  : m_id{id},
    m_markingLeft{markingLeft},
    m_markingRight{markingRight},
    m_boundaryLeft{boundaryLeft},
    m_boundaryRight{boundaryRight},
    m_start{laneStart},
    m_nextId{nextId},
    m_prevId{prevId},
    m_leftId{leftId},
    m_rightId{rightId},
    m_nextInNewSeg{nextInNewSeg},
    m_prevInNewSeg{prevInNewSeg},
    m_parent{parent}
{}

//==============================================================================

LaneSegmentIn6970::LaneSegmentIn6970(const LaneIn6970::Ptr& parent) : m_parent{parent} {}

//==============================================================================

LaneSegmentIn6970::LaneSegmentIn6970(const LaneSupportPointIn6970& laneStart) : m_start{laneStart} {}

//==============================================================================

void LaneSegmentIn6970::setNext(const LaneSegmentIn6970::Ptr& next)
{
    m_nextSegment = next;
    m_nextId      = next ? next->getId() : 0;
    // check carriageWaySegment
    if (getParent() && next && next->getParent())
    {
        m_nextInNewSeg = getParent() != next->getParent();
    }
}

//==============================================================================

void LaneSegmentIn6970::setPrevious(const LaneSegmentIn6970::Ptr& previous)
{
    m_prevSegment = previous;
    m_prevId      = previous ? previous->getId() : 0;
    // check carriageWaySegment
    if (getParent() && previous && previous->getParent())
    {
        m_prevInNewSeg = getParent() != previous->getParent();
    }
}

//==============================================================================

void LaneSegmentIn6970::setLeft(const LaneSegmentIn6970::Ptr& left)
{
    m_leftSegment = left;
    m_leftId      = left ? left->getId() : 0;
}

//==============================================================================

void LaneSegmentIn6970::setRight(const LaneSegmentIn6970::Ptr& right)
{
    m_rightSegment = right;
    m_rightId      = right ? right->getId() : 0;
}

//==============================================================================

void LaneSegmentIn6970::updateConnectionIds(const LaneSegmentIn6970::Ptr& reference, const bool override)
{
    if (reference)
    {
        if (m_nextId == 0 || override)
        {
            m_nextId = reference->getNextId();
        }
        if (m_prevId == 0 || override)
        {
            m_prevId = reference->getPrevId();
        }
        if (m_leftId == 0 || override)
        {
            m_leftId = reference->getLeftId();
        }
        if (m_rightId == 0 || override)
        {
            m_rightId = reference->getRightId();
        }
        if (!m_nextInNewSeg || override)
        {
            m_nextInNewSeg = reference->isNextInNewSeg();
        }
        if (!m_prevInNewSeg || override)
        {
            m_prevInNewSeg = reference->isPrevInNewSeg();
        }
    }
}

//==============================================================================

void LaneSegmentIn6970::calculateLength()
{
    if (hasNext())
    {
        double x, y;
        m_nextSegment.lock()->getStartPoint().getWgsPoint().transformToTangentialPlane2d(m_start.getWgsPoint(), x, y);
        m_length = float(sqrt(x * x + y * y));
    }
}

//==============================================================================

void LaneSegmentIn6970::calculateWidth()
{
    if (hasNext())
    {
        Line2d<float> left(m_start.getLeftOffset(), getEndOffsetLeft());
        Line2d<float> right(m_start.getRightOffset(), getEndOffsetRight());

        Line2d<float> startCutLine(Vector2<float>(0, 100), Vector2<float>(0, -100));
        Line2d<float> endCutLine(Vector2<float>(getLength(), 100), Vector2<float>(getLength(), -100));

        Vector2<float> cls, crs, cle, cre;
        startCutLine.isIntersecting(left, &cls);
        startCutLine.isIntersecting(right, &crs);
        endCutLine.isIntersecting(left, &cle);
        endCutLine.isIntersecting(right, &cre);

        m_startWidth = (cls - crs).getLength();
        m_endWidth   = (cle - cre).getLength();
    }
    else if (hasPrevious())
    {
        m_prevSegment.lock()->updateProperties();
        m_startWidth = m_prevSegment.lock()->m_endWidth;
        m_endWidth   = m_startWidth;
    }
}

//==============================================================================

float LaneSegmentIn6970::getWidth(const float position) const
{
    if (position == 0.0F)
    {
        return m_startWidth;
    }

    if (position <= getLength())
    {
        if (getLength() > 0.0F)
        {
            return (m_endWidth - m_startWidth) / getLength() * position + m_startWidth;
        }
        else
        {
            return 0.0F;
        }
    }
    else if (hasNext())
    {
        return m_nextSegment.lock()->getWidth(position - getLength());
    }
    else
    {
        return 0.0F;
    }
}

//==============================================================================

void LaneSegmentIn6970::calculateBoundingBox()
{
    if (hasNext())
    {
        // create bounding box
        PositionWgs84 dummy;
        const PositionWgs84 startWgs{m_start.getWgsPoint()};
        std::vector<PositionWgs84> points;
        dummy.transformFromTangentialPlaneWithHeading2d(static_cast<double>(m_start.getLeftOffset().getX()),
                                                        static_cast<double>(m_start.getLeftOffset().getY()),
                                                        startWgs);
        points.push_back(dummy);
        dummy.transformFromTangentialPlaneWithHeading2d(static_cast<double>(m_start.getRightOffset().getX()),
                                                        static_cast<double>(m_start.getRightOffset().getY()),
                                                        startWgs);
        points.push_back(dummy);
        dummy.transformFromTangentialPlaneWithHeading2d(
            static_cast<double>(getEndOffsetLeft().getX()), static_cast<double>(getEndOffsetLeft().getY()), startWgs);
        points.push_back(dummy);
        dummy.transformFromTangentialPlaneWithHeading2d(
            static_cast<double>(getEndOffsetRight().getX()), static_cast<double>(getEndOffsetRight().getY()), startWgs);
        points.push_back(dummy);

        bool initialized = false;
        for (auto& p : points)
        {
            if ((!initialized) || (p.getLatitudeInDeg() < m_boundingBox.minLatitude))
            {
                m_boundingBox.minLatitude = p.getLatitudeInDeg();
            }

            if ((!initialized) || (p.getLatitudeInDeg() > m_boundingBox.maxLatitude))
            {
                m_boundingBox.maxLatitude = p.getLatitudeInDeg();
            }

            if ((!initialized) || (p.getLongitudeInDeg() < m_boundingBox.minLongitude))
            {
                m_boundingBox.minLongitude = p.getLongitudeInDeg();
            }

            if ((!initialized) || (p.getLongitudeInDeg() > m_boundingBox.maxLongitude))
            {
                m_boundingBox.maxLongitude = p.getLongitudeInDeg();
            }

            initialized = true;
        }
    }
}

//==============================================================================

void LaneSegmentIn6970::calculateOffsets()
{
    if (hasNext())
    {
        LaneSupportPointIn6970 endSupport = m_nextSegment.lock()->getStartPoint();

        const PositionWgs84 startWgs{m_start.getWgsPoint()};
        double x, y;
        endSupport.getWgsPoint().transformToTangentialPlaneWithHeading2d(startWgs, x, y);
        Vector2<float> endOffset(static_cast<float>(x), static_cast<float>(y));

        const float angleDeviation = endOffset.getAngle();

        if (!ibeo::common::sdk::fuzzyCompareT<6>(angleDeviation, 0.0F))
        {
            // correct start offsets
            const TransformationMatrix2d<float> current2Head(-angleDeviation);
            const Vector2<float> sol = current2Head * getStartOffsetLeft();
            const Vector2<float> sor = current2Head * getStartOffsetRight();
            endOffset                = current2Head * endOffset;

            // correct start heading
            PositionWgs84 newStart = startWgs;
            newStart.setCourseAngleInRad(newStart.getCourseAngleInRad() + static_cast<double>(angleDeviation));

            m_start = LaneSupportPointIn6970(newStart, sol, sor);
        }

        m_endOffset = endOffset;

        const TransformationMatrix2d<float> start2World((float)m_start.getWgsPoint().getCourseAngleInRad());
        const TransformationMatrix2d<float> end2World((float)endSupport.getWgsPoint().getCourseAngleInRad());
        const TransformationMatrix2d<float> end2start((start2World.getInverse() * end2World).getRotationMatrix(),
                                                      m_endOffset);

        m_endOffsetLeft  = end2start * endSupport.getLeftOffset();
        m_endOffsetRight = end2start * endSupport.getRightOffset();
    }
    else
    {
        m_endOffsetLeft  = m_start.getLeftOffset();
        m_endOffsetRight = m_start.getRightOffset();
    }
}

//==============================================================================

void LaneSegmentIn6970::cleanIds()
{
    m_nextId  = hasNext() ? getNext()->getId() : 0;
    m_prevId  = hasPrevious() ? getPrevious()->getId() : 0;
    m_leftId  = hasLeft() ? getLeft()->getId() : 0;
    m_rightId = hasRight() ? getRight()->getId() : 0;

    if (getParent() && getNext() && getNext()->getParent())
    {
        m_nextInNewSeg = getParent() != getNext()->getParent();
    }

    if (getParent() && getPrevious() && getPrevious()->getParent())
    {
        m_prevInNewSeg = getParent() != getPrevious()->getParent();
    }
}

//==============================================================================

PositionWgs84 LaneSegmentIn6970::getEndGps()
{
    PositionWgs84 out;
    out.transformFromTangentialPlaneWithHeading2d(static_cast<double>(getLength()), .0, m_start.getWgsPoint());
    return out;
}

//==============================================================================

void LaneSegmentIn6970::updateProperties()
{
    calculateBoundingBox();
    calculateLength();
    calculateOffsets();
    calculateWidth();
}

//==============================================================================

bool LaneSegmentIn6970::arePtrsEqualNonRecursive(const LaneSegmentIn6970::Ptr& lhs, const LaneSegmentIn6970::Ptr& rhs)
{
    if ((!lhs) && (!rhs))
    {
        return true;
    }

    if ((!lhs) || (!rhs))
    {
        return false;
    }

    return areEqualNonRecursive(*lhs, *rhs);
}

//==============================================================================

bool LaneSegmentIn6970::areEqualRecursive(const LaneSegmentIn6970& lhs, const LaneSegmentIn6970& rhs)
{
    return (lhs.getLeftMarkingType() == rhs.getLeftMarkingType())
           && (lhs.getRightMarkingType() == rhs.getRightMarkingType())
           && (lhs.getLeftBoundaryType() == rhs.getLeftBoundaryType())
           && (lhs.getRightBoundaryType() == rhs.getRightBoundaryType()) && (lhs.getStartPoint() == rhs.getStartPoint())

           && (lhs.isNextInNewSeg() == rhs.isNextInNewSeg()) && (lhs.isPrevInNewSeg() == rhs.isPrevInNewSeg())

           && arePtrsEqualNonRecursive(lhs.getNext(), rhs.getNext())
           && arePtrsEqualNonRecursive(lhs.getPrevious(), rhs.getPrevious())
           && arePtrsEqualNonRecursive(lhs.getLeft(), rhs.getLeft())
           && arePtrsEqualNonRecursive(lhs.getRight(), rhs.getRight());
}

//==============================================================================

bool LaneSegmentIn6970::areEqualNonRecursive(const LaneSegmentIn6970& lhs, const LaneSegmentIn6970& rhs)
{
    return (lhs.getLeftMarkingType() == rhs.getLeftMarkingType())
           && (lhs.getRightMarkingType() == rhs.getRightMarkingType())
           && (lhs.getLeftBoundaryType() == rhs.getLeftBoundaryType())
           && (lhs.getRightBoundaryType() == rhs.getRightBoundaryType()) && (lhs.getStartPoint() == rhs.getStartPoint())

           && (lhs.isNextInNewSeg() == rhs.isNextInNewSeg()) && (lhs.isPrevInNewSeg() == rhs.isPrevInNewSeg());
}

//==============================================================================
} // namespace lanes
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

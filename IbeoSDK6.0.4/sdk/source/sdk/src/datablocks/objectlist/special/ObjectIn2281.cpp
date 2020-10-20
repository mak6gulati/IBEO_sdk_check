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
//! \date Mar 14, 2014
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2281.hpp>
#include <ibeo/common/sdk/Math.hpp>
#include <ibeo/common/sdk/ObjectBasic.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

Vector2<float> ObjectIn2281::getObjectBoxPosition(RefPointBoxLocation curRefPtLoc,
                                                  const Vector2<float> refPt,
                                                  const float courseAngle,
                                                  const Vector2<float> objBoxSize,
                                                  RefPointBoxLocation targetRefPtLoc)
{
    static const int vect[10][2]
        = {{0, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}, {1, 0}, {0, -1}, {-1, 0}, {0, 1}, {0, 0}};

    const float sizeXh = 0.5f * objBoxSize.getX();
    const float sizeYh = 0.5f * objBoxSize.getY();
    const float cca    = std::cos(courseAngle);
    const float sca    = std::sin(courseAngle);
    const Vector2<float> halfLength(cca * sizeXh, sca * sizeXh);
    const Vector2<float> halfWidth(-sca * sizeYh, cca * sizeYh);

    // targetRefPtLoc und curRefPtLoc muessen im Intervall RPL_COG..RPL_OBJECT_CENTER liegen
    targetRefPtLoc
        = (targetRefPtLoc <= RefPointBoxLocation::ObjectCenter)
              ? ((targetRefPtLoc < RefPointBoxLocation::CenterOfGravity) ? RefPointBoxLocation::CenterOfGravity
                                                                         : targetRefPtLoc)
              : RefPointBoxLocation::ObjectCenter;
    curRefPtLoc = (curRefPtLoc <= RefPointBoxLocation::ObjectCenter)
                      ? ((curRefPtLoc < RefPointBoxLocation::CenterOfGravity) ? RefPointBoxLocation::CenterOfGravity
                                                                              : curRefPtLoc)
                      : RefPointBoxLocation::ObjectCenter;

    const float dl = float(vect[static_cast<uint8_t>(targetRefPtLoc)][0] - vect[static_cast<uint8_t>(curRefPtLoc)][0]);
    const float db = float(vect[static_cast<uint8_t>(targetRefPtLoc)][1] - vect[static_cast<uint8_t>(curRefPtLoc)][1]);

    return (refPt + halfLength * dl + halfWidth * db);
}

//==============================================================================

const MeasurementKey ObjectIn2281::mkey_OGpsImuTargetNumber = MeasurementKey(0x0190U);
const MeasurementKey ObjectIn2281::mkey_VisibilityLaser     = MeasurementKey(0x0191U);
const MeasurementKey ObjectIn2281::mkey_OcclusionLaser      = MeasurementKey(0x0192U);
const MeasurementKey ObjectIn2281::mkey_VisibilityDut       = MeasurementKey(0x0193U);
const MeasurementKey ObjectIn2281::mkey_OcclusionDut        = MeasurementKey(0x0194U);
const MeasurementKey ObjectIn2281::mkey_OGpsImuTargetType   = MeasurementKey(0x0195U);

const MeasurementKey ObjectIn2281::mkey_AccelerationCorrCoeff = MeasurementKey(0x0196U);
const MeasurementKey ObjectIn2281::mkey_VelocityCorrCoeff     = MeasurementKey(0x0197U);

//==============================================================================

ObjectIn2281::ObjectIn2281()
  : m_objectId(0),
    m_flags(0),
    m_objectAge(0),
    m_timestamp(0),
    m_hiddenStatusAge(0),
    m_classification(),
    m_classificationQuality(0),
    m_classificationAge(0),
    m_objectBoxSize(),
    m_objBoxSizeSigma(),
    m_courseAngle(0),
    m_courseAngleSigma(0),
    m_relativeVelocity(),
    m_relativeVelocitySigma(),
    m_absoluteVelocity(),
    m_absoluteVelocitySigma(),
    m_objectHeight(0),
    m_objectHeightSigma(0),
    m_motionReferencePoint(),
    m_motionReferencePointSigma(),
    m_longitudianlAcceleration(0),
    m_longitudianlAccelerationSigma(0),
    m_yawRate(0),
    m_yawRateSigma(0),
    m_closestContourPointIndex(0),
    m_referencePointLocation(ibeo::common::sdk::RefPointBoxLocation::Unknown),
    m_referencePointCoord(),
    m_referencePointCoordSigma(),
    m_referencePointPositionCorrCoeff(0),
    m_centerOfGravity(),
    m_objectPriority(0),
    m_objectExistenceMeas(0),
    m_objectBoxHeightOffset(0),
    m_objectBoxHeightOffsetSigma(0),
    m_reserved3(0),
    m_reserved4(0),
    m_contourPoints(),
    m_measurementList()
{}

//==============================================================================

std::streamsize ObjectIn2281::getSerializedSize() const
{
    const std::streamsize result
        = std::streamsize(sizeof(m_objectId)) + std::streamsize(sizeof(m_flags)) + std::streamsize(sizeof(m_objectAge))
          + std::streamsize(sizeof(uint32_t) + sizeof(uint32_t)) // timestamp
          + std::streamsize(sizeof(uint16_t)) + std::streamsize(sizeof(uint8_t)) + std::streamsize(sizeof(uint8_t))
          + std::streamsize(sizeof(uint32_t)) + serializedSize(m_objectBoxSize) + serializedSize(m_objBoxSizeSigma)
          + std::streamsize(sizeof(float)) + std::streamsize(sizeof(float)) + serializedSize(m_relativeVelocity)
          + serializedSize(m_relativeVelocitySigma) + serializedSize(m_absoluteVelocity)
          + serializedSize(m_absoluteVelocitySigma) + std::streamsize(sizeof(float)) + std::streamsize(sizeof(float))
          + serializedSize(m_motionReferencePoint) + serializedSize(m_motionReferencePointSigma)
          + std::streamsize(sizeof(float)) + std::streamsize(sizeof(float)) + std::streamsize(sizeof(float))
          + std::streamsize(sizeof(float)) + std::streamsize(sizeof(uint8_t)) + std::streamsize(sizeof(uint8_t))
          + std::streamsize(sizeof(uint16_t)) + serializedSize(m_referencePointCoord)
          + serializedSize(m_referencePointCoordSigma) + std::streamsize(sizeof(float))
          + serializedSize(m_centerOfGravity) + std::streamsize(sizeof(uint16_t)) + std::streamsize(sizeof(float))
          + std::streamsize(sizeof(int8_t)) + std::streamsize(sizeof(uint8_t)) + std::streamsize(sizeof(uint8_t))
          + std::streamsize(sizeof(uint8_t))
          + std::streamsize(m_contourPoints.size()) * serializedSize(Vector2<float>())
          + m_measurementList.getSerializedSize();

    return result;
}
//==============================================================================

bool ObjectIn2281::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, m_objectId);
    readBE(is, m_flags);
    readBE(is, m_objectAge);
    readBE(is, m_timestamp);
    readBE(is, m_hiddenStatusAge);

    readBE(is, m_classification);
    readBE(is, m_classificationQuality);
    readBE(is, m_classificationAge);

    readBE(is, m_objectBoxSize);
    readBE(is, m_objBoxSizeSigma);
    readBE(is, m_courseAngle);
    readBE(is, m_courseAngleSigma);

    readBE(is, m_relativeVelocity);
    readBE(is, m_relativeVelocitySigma);
    readBE(is, m_absoluteVelocity);
    readBE(is, m_absoluteVelocitySigma);

    readBE(is, m_objectHeight);
    readBE(is, m_objectHeightSigma);

    readBE(is, m_motionReferencePoint);
    readBE(is, m_motionReferencePointSigma);

    readBE(is, m_longitudianlAcceleration);
    readBE(is, m_longitudianlAccelerationSigma);

    readBE(is, m_yawRate);
    readBE(is, m_yawRateSigma);

    {
        uint8_t rd8;
        readBE(is, rd8);
        m_contourPoints.resize(rd8);
    }

    readBE(is, m_closestContourPointIndex);

    readBE<16>(is, m_referencePointLocation);
    readBE(is, m_referencePointCoord);
    readBE(is, m_referencePointCoordSigma);
    readBE(is, m_referencePointPositionCorrCoeff);

    readBE(is, m_centerOfGravity);
    readBE(is, m_objectPriority);
    readBE(is, m_objectExistenceMeas);

    readBE(is, m_objectBoxHeightOffset);
    readBE(is, m_objectBoxHeightOffsetSigma);
    readBE(is, m_reserved3);
    readBE(is, m_reserved4);

    // container has already been resized to the right size
    std::vector<Vector2<float>>::iterator cpIter = m_contourPoints.begin();
    for (; cpIter != m_contourPoints.end(); ++cpIter)
    {
        readBE(is, *cpIter);
    }

    m_measurementList.deserialize(is);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ObjectIn2281::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, m_objectId);
    writeBE(os, m_flags);
    writeBE(os, m_objectAge);
    writeBE(os, m_timestamp);
    writeBE(os, m_hiddenStatusAge);

    writeBE(os, m_classification);
    writeBE(os, m_classificationQuality);
    writeBE(os, m_classificationAge);

    writeBE(os, m_objectBoxSize);
    writeBE(os, m_objBoxSizeSigma);
    writeBE(os, m_courseAngle);
    writeBE(os, m_courseAngleSigma);

    writeBE(os, m_relativeVelocity);
    writeBE(os, m_relativeVelocitySigma);
    writeBE(os, m_absoluteVelocity);
    writeBE(os, m_absoluteVelocitySigma);

    writeBE(os, m_objectHeight);
    writeBE(os, m_objectHeightSigma);

    writeBE(os, m_motionReferencePoint);
    writeBE(os, m_motionReferencePointSigma);

    writeBE(os, m_longitudianlAcceleration);
    writeBE(os, m_longitudianlAccelerationSigma);

    writeBE(os, m_yawRate);
    writeBE(os, m_yawRateSigma);

    writeBE(os, uint8_t(m_contourPoints.size()));
    writeBE(os, m_closestContourPointIndex);

    writeBE<16>(os, m_referencePointLocation);
    writeBE(os, m_referencePointCoord);
    writeBE(os, m_referencePointCoordSigma);
    writeBE(os, m_referencePointPositionCorrCoeff);

    writeBE(os, m_centerOfGravity);
    writeBE(os, m_objectPriority);
    writeBE(os, m_objectExistenceMeas);

    writeBE(os, m_objectBoxHeightOffset);
    writeBE(os, m_objectBoxHeightOffsetSigma);
    writeBE(os, m_reserved3);
    writeBE(os, m_reserved4);

    std::vector<Vector2<float>>::const_iterator cpIter = m_contourPoints.begin();
    for (; cpIter != m_contourPoints.end(); ++cpIter)
    {
        writeBE(os, *cpIter);
    }

    m_measurementList.serialize(os);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

Vector2<float> ObjectIn2281::getObjectBoxPosition(const RefPointBoxLocation targetRefPtLoc) const
{
    return getObjectBoxPosition(this->getReferencePointLocation(),
                                this->getReferencePointCoord(),
                                this->getCourseAngle(),
                                this->getObjectBoxSize(),
                                targetRefPtLoc);
}

//==============================================================================

Vector2<float> ObjectIn2281::getObjectBoxCenter() const
{
    return getObjectBoxPosition(RefPointBoxLocation::ObjectCenter);
}

//==============================================================================

void ObjectIn2281::setAccelerationCorrCoeff(const float referenceAccelerationCorrCoeff)
{
    MeasurementList::MeasurementVector::iterator iter;
    iter = m_measurementList.getMeasurement(mkey_AccelerationCorrCoeff);
    if (iter != m_measurementList.getMeasurements().end())
    {
        iter->setData<float>(referenceAccelerationCorrCoeff);
    }
    else
    {
        Measurement ms;
        ms.setValue(mkey_AccelerationCorrCoeff, referenceAccelerationCorrCoeff);
        m_measurementList.addMeasurement(ms);
    }
}

//==============================================================================

void ObjectIn2281::setVelocityCorrCoeff(const float referenceVelocityCorrCoeff)
{
    MeasurementList::MeasurementVector::iterator iter;
    iter = m_measurementList.getMeasurement(mkey_VelocityCorrCoeff);
    if (iter != m_measurementList.getMeasurements().end())
    {
        iter->setData<float>(referenceVelocityCorrCoeff);
    }
    else
    {
        Measurement ms;
        ms.setValue(mkey_VelocityCorrCoeff, referenceVelocityCorrCoeff);
        m_measurementList.addMeasurement(ms);
    }
}

//==============================================================================

bool ObjectIn2281::operator==(const ObjectIn2281& other) const
{
    if (m_objectId != other.getObjectId())
        return false;

    if (m_flags != other.getFlags())
        return false;

    if (m_objectAge != other.getObjectAge())
        return false;

    if (m_timestamp != other.getTimestamp())
        return false;

    if (m_hiddenStatusAge != other.getHiddenStatusAge())
        return false;

    if (m_classification != other.getClassification())
        return false;

    if (m_classificationQuality != other.getClassificationQuality())
        return false;

    if (m_classificationAge != other.getClassificationAge())
        return false;

    if (m_objectBoxSize != other.getObjectBoxSize())
        return false;

    if (m_objBoxSizeSigma != other.getObjectBoxSizeSigma())
        return false;

    if (!fuzzyFloatEqualT<7>(m_courseAngle, other.getCourseAngle()))
        return false;

    if (!fuzzyFloatEqualT<7>(m_courseAngleSigma, other.getCourseAngleSigma()))
        return false;

    if (m_relativeVelocity != other.getRelativeVelocity())
        return false;

    if (m_relativeVelocitySigma != other.getRelativeVelocitySigma())
        return false;

    if (m_absoluteVelocity != other.getAbsoluteVelocity())
        return false;

    if (m_absoluteVelocitySigma != other.getAbsoluteVelocitySigma())
        return false;

    if (!fuzzyFloatEqualT<7>(m_objectHeight, other.getObjectHeight()))
        return false;

    if (!fuzzyFloatEqualT<7>(m_objectHeightSigma, other.getObjectHeightSigma()))
        return false;

    if (m_motionReferencePoint != other.getMotionReferencePoint())
        return false;

    if (m_motionReferencePointSigma != other.getMotionReferencePointSigma())
        return false;

    if (!fuzzyFloatEqualT<7>(m_longitudianlAcceleration, other.getLongitudinalAcceleration()))
        return false;

    if (!fuzzyFloatEqualT<7>(m_longitudianlAccelerationSigma, other.getLongitudinalAccelerationSigma()))
        return false;

    if (!fuzzyFloatEqualT<7>(m_yawRate, other.getYawRate()))
        return false;

    if (m_closestContourPointIndex != other.getClosestContourPointIndex())
        return false;

    if (m_referencePointLocation != other.getReferencePointLocation())
        return false;

    if (m_referencePointCoord != other.getReferencePointCoord())
        return false;

    if (m_referencePointCoordSigma != other.getReferencePointCoordSigma())
        return false;

    if (!fuzzyFloatEqualT<7>(m_referencePointPositionCorrCoeff, other.getReferencePointPositionCorrCoeff()))
        return false;

    if (getObjectBoxCenter() != other.getObjectBoxCenter())
        return false;

    if (m_centerOfGravity != other.getCenterOfGravity())
        return false;

    if (m_objectPriority != other.getObjectPriority())
        return false;

    if (!fuzzyFloatEqualT<7>(m_objectExistenceMeas, other.getObjectExistenceMeas()))
        return false;

    if (m_objectBoxHeightOffset != other.getObjectBoxHeightOffset())
        return false;

    if (m_objectBoxHeightOffsetSigma != other.getObjectBoxHeightOffsetSigma())
        return false;

    if (m_reserved3 != other.getReserved3())
        return false;

    if (m_reserved4 != other.getReserved4())
        return false;

    for (size_t idx = 0; idx < m_contourPoints.size(); ++idx)
    {
        if (m_contourPoints[idx] != other.getContourPoints()[idx])
            return false;
    }

    if (m_measurementList != other.getMeasurementList())
        return false;

    return true;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

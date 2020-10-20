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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Vector2.hpp>
#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/ObjectBasic.hpp>
#include <ibeo/common/sdk/datablocks/MeasurementList.hpp>
#include <ibeo/common/sdk/datablocks/Measurement.hpp>

#include <ibeo/common/sdk/misc/deprecatedwarning.hpp>

#include <vector>
#include <iostream>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \brief Object with extended tracking information an dynamic Type (generic)
class ObjectIn2281
{
public:
    enum class Flags : uint16_t
    {
        TrackedByStationaryModel = 0x0040U, ///< is object tracked using stationary model
        Mobile
        = 0x0080U, ///< Has been detected/validated as mobile. (the current tracking model is irrelevant; this flag just means it has been moving at some time)
        Validated
        = 0x0100U ///< Object (stationary or dynamic) has been validated, i.e. valid enough to send out to the interface
    }; // Flags

public:
    static Vector2<float> getObjectBoxPosition(RefPointBoxLocation curRefPtLoc,
                                               const Vector2<float> refPt,
                                               const float courseAngle,
                                               const Vector2<float> objBoxSize,
                                               RefPointBoxLocation targetRefPtLoc);

public:
    ObjectIn2281();
    virtual ~ObjectIn2281() = default;

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    void addMeasurement(const Measurement& meas) { m_measurementList.addMeasurement(meas); }
    void addContourPoint(const Vector2<float>& contourPoint) { m_contourPoints.push_back(contourPoint); }

public: // getter
    uint32_t getObjectId() const { return m_objectId; }
    uint16_t getFlags() const { return m_flags; }
    bool trackedByStationaryModel() const
    {
        return (m_flags & static_cast<uint16_t>(Flags::TrackedByStationaryModel))
               == static_cast<uint16_t>(Flags::TrackedByStationaryModel);
    }
    bool mobile() const
    {
        return (m_flags & static_cast<uint16_t>(Flags::Mobile)) == static_cast<uint16_t>(Flags::Mobile);
    }
    bool motionModelValidated() const
    {
        return (m_flags & static_cast<uint16_t>(Flags::Validated)) == static_cast<uint16_t>(Flags::Validated);
    }
    uint32_t getObjectAge() const { return m_objectAge; }
    NTPTime getTimestamp() const { return m_timestamp; }
    uint16_t getHiddenStatusAge() const { return m_hiddenStatusAge; }
    uint16_t getObjectPredictionAge() const { return getHiddenStatusAge(); }

    ObjectClass getClassification() const { return m_classification; }
    uint8_t getClassificationQuality() const { return m_classificationQuality; }
    uint32_t getClassificationAge() const { return m_classificationAge; }
    Vector2<float> getObjectBoxSize() const { return m_objectBoxSize; }
    Vector2<float> getObjectBoxSizeSigma() const { return m_objBoxSizeSigma; }
    float getCourseAngle() const { return m_courseAngle; }
    float getCourseAngleSigma() const { return m_courseAngleSigma; }
    Vector2<float> getRelativeVelocity() const { return m_relativeVelocity; }
    Vector2<float> getRelativeVelocitySigma() const { return m_relativeVelocitySigma; }
    Vector2<float> getAbsoluteVelocity() const { return m_absoluteVelocity; }
    Vector2<float> getAbsoluteVelocitySigma() const { return m_absoluteVelocitySigma; }
    float getObjectHeight() const { return m_objectHeight; }
    float getObjectHeightSigma() const { return m_objectHeightSigma; }
    Vector2<float> getMotionReferencePoint() const { return m_motionReferencePoint; }
    Vector2<float> getMotionReferencePointSigma() const { return m_motionReferencePointSigma; }
    float getLongitudinalAcceleration() const { return m_longitudianlAcceleration; }
    float getLongitudinalAccelerationSigma() const { return m_longitudianlAccelerationSigma; }
    float getYawRate() const { return m_yawRate; }
    float getYawRateSigma() const { return m_yawRateSigma; }
    uint8_t getNumContourPoints() const { return uint8_t(m_contourPoints.size()); }
    uint8_t getClosestContourPointIndex() const { return m_closestContourPointIndex; }
    RefPointBoxLocation getReferencePointLocation() const { return m_referencePointLocation; }
    Vector2<float> getReferencePointCoord() const { return m_referencePointCoord; }
    Vector2<float> getReferencePointCoordSigma() const { return m_referencePointCoordSigma; }
    float getReferencePointPositionCorrCoeff() const { return m_referencePointPositionCorrCoeff; }
    float getAccelerationCorrCoeff() const
    {
        return (m_measurementList.contains(mkey_AccelerationCorrCoeff))
                   ? m_measurementList.getMeasurement(mkey_AccelerationCorrCoeff)->getAs<float>()
                   : 0.0F;
    }
    float getVelocityCorrCoeff() const
    {
        return (m_measurementList.contains(mkey_VelocityCorrCoeff))
                   ? m_measurementList.getMeasurement(mkey_VelocityCorrCoeff)->getAs<float>()
                   : 0.0F;
    }

    Vector2<float> getObjectBoxPosition(const RefPointBoxLocation targetRefPtLoc) const;
    Vector2<float> getObjectBoxCenter() const;

    Vector2<float> getCenterOfGravity() const { return m_centerOfGravity; }
    uint16_t getObjectPriority() const { return m_objectPriority; }
    float getObjectExistenceMeas() const { return m_objectExistenceMeas; }

    int8_t getObjectBoxHeightOffset() const { return m_objectBoxHeightOffset; }
    float getObjectBoxHeightOffsetCm() const { return m_objectBoxHeightOffset * 4.f; }
    uint8_t getObjectBoxHeightOffsetSigma() const { return m_objectBoxHeightOffsetSigma; }

    uint8_t getReserved3() const { return m_reserved3; }
    uint8_t getReserved4() const { return m_reserved4; }

    const std::vector<Vector2<float>>& getContourPoints() const { return m_contourPoints; }

    const MeasurementList& getMeasurementList() const { return m_measurementList; }
    const MeasurementList& dynamicObjectProperties() const { return getMeasurementList(); }

public: // setter
    void setObjectId(const uint32_t id) { m_objectId = id; }
    void setFlags(const uint16_t flags) { m_flags = flags; }
    void setObjectAge(const uint32_t objectAge) { m_objectAge = objectAge; }
    void setTimestamp(const NTPTime timestamp) { m_timestamp = timestamp; }
    void setHiddenStatusAge(const uint16_t hiddenStatusAge) { m_hiddenStatusAge = hiddenStatusAge; }

    void setClassification(const ObjectClass classification) { m_classification = classification; }
    void setClassificationQuality(const uint8_t classificationQuality)
    {
        m_classificationQuality = classificationQuality;
    }
    void setClassificationAge(const uint32_t classificationAge) { m_classificationAge = classificationAge; }

    void setObjectBoxSize(const Vector2<float>& objectBoxSize) { m_objectBoxSize = objectBoxSize; }
    void setObjectBoxSizeSigma(const Vector2<float>& objectBoxSizeSigma) { m_objBoxSizeSigma = objectBoxSizeSigma; }
    void setCourseAngle(const float courseAngle) { m_courseAngle = courseAngle; }
    void setCourseAngleSigma(const float courseAngleSigma) { m_courseAngleSigma = courseAngleSigma; }

    void setRelativeVelocity(const Vector2<float>& relativeVelocity) { m_relativeVelocity = relativeVelocity; }
    void setRelativeVelocitySigma(const Vector2<float>& relativeVelocitySigma)
    {
        m_relativeVelocitySigma = relativeVelocitySigma;
    }
    void setAbsoluteVelocity(const Vector2<float>& absoluteVelocity) { m_absoluteVelocity = absoluteVelocity; }
    void setAbsoluteVelocitySigma(const Vector2<float>& absoluteVelocitySigma)
    {
        m_absoluteVelocitySigma = absoluteVelocitySigma;
    }

    void setObjectHeight(const float objectHeight) { m_objectHeight = objectHeight; }
    void setObjectHeightSigma(const float objectHeightSigma) { m_objectHeightSigma = objectHeightSigma; }

    void setMotionReferencePoint(const Vector2<float>& motionReferencePoint)
    {
        m_motionReferencePoint = motionReferencePoint;
    }
    void setMotionReferencePointSigma(const Vector2<float>& motionReferencePointSigma)
    {
        m_motionReferencePointSigma = motionReferencePointSigma;
    }

    void setLongitudinalAcceleration(const float longitudinalAcceleration)
    {
        m_longitudianlAcceleration = longitudinalAcceleration;
    }
    void setLongitudinalAccelerationSigma(const float longitudinalAccelerationSigma)
    {
        m_longitudianlAccelerationSigma = longitudinalAccelerationSigma;
    }

    void setYawRate(const float yawRate) { m_yawRate = yawRate; }
    void setYawRateSigma(const float yawRateSigma) { m_yawRateSigma = yawRateSigma; }

    void setClosestContourPointIndex(const uint8_t closestContourPointIndex)
    {
        assert(closestContourPointIndex < m_contourPoints.size());
        m_closestContourPointIndex = closestContourPointIndex;
    }

    void setReferencePointLocation(const RefPointBoxLocation referencePointLocation)
    {
        m_referencePointLocation = referencePointLocation;
    }
    void setReferencePointCoord(const Vector2<float>& referencePointCoord)
    {
        m_referencePointCoord = referencePointCoord;
    }
    void setReferencePointCoordSigma(const Vector2<float>& referencePointCoordSigma)
    {
        m_referencePointCoordSigma = referencePointCoordSigma;
    }

    void setReferencePointPositionCorrCoeff(const float referencePointPositionCorrCoeff)
    {
        m_referencePointPositionCorrCoeff = referencePointPositionCorrCoeff;
    }
    void setAccelerationCorrCoeff(const float referenceAccelerationCorrCoeff);
    void setVelocityCorrCoeff(const float referenceVelocityCorrCoeff);

    void setCenterOfGravity(const Vector2<float>& centerOfGravity) { m_centerOfGravity = centerOfGravity; }
    void setObjectPriority(const uint16_t objectPriority) { m_objectPriority = objectPriority; }
    void setObjectExistenceMeas(const float objectExistenceMeas) { m_objectExistenceMeas = objectExistenceMeas; }

    void setContourPoints(const std::vector<Vector2<float>>& contourPoints) { m_contourPoints = contourPoints; }
    void setMeasurementList(const MeasurementList& measList) { m_measurementList = measList; }

    void setObjectBoxHeightOffset(const int8_t& objectBoxHeightOffset)
    {
        m_objectBoxHeightOffset = objectBoxHeightOffset;
    }
    void setObjectBoxHeightOffsetSigma(const uint8_t& objectBoxHeightOffsetSigma)
    {
        m_objectBoxHeightOffsetSigma = objectBoxHeightOffsetSigma;
    }

    void setReserved3(const uint8_t& reserved3) { m_reserved3 = reserved3; }
    void setReserved4(const uint8_t& reserved4) { m_reserved4 = reserved4; }

public:
    Vector2<float> convertRefPoint(const RefPointBoxLocation toPos) const
    {
        return ibeo::common::sdk::convertRefPoint(this->getReferencePointCoord(),
                                                  this->getCourseAngle(),
                                                  this->getObjectBoxSize(),
                                                  this->getReferencePointLocation(),
                                                  toPos);
    }

public:
    static const MeasurementKey mkey_OGpsImuTargetNumber;
    static const MeasurementKey mkey_VisibilityLaser;
    static const MeasurementKey mkey_OcclusionLaser;
    static const MeasurementKey mkey_VisibilityDut;
    static const MeasurementKey mkey_OcclusionDut;
    static const MeasurementKey mkey_OGpsImuTargetType;

    static const MeasurementKey mkey_AccelerationCorrCoeff;
    static const MeasurementKey mkey_VelocityCorrCoeff;

public:
    bool operator==(const ObjectIn2281& other) const;
    bool operator!=(const ObjectIn2281& other) const { return !((*this) == other); }

protected:
    uint32_t m_objectId;
    uint16_t m_flags;
    uint32_t m_objectAge;
    NTPTime m_timestamp;
    uint16_t m_hiddenStatusAge;

    ObjectClass m_classification;
    uint8_t m_classificationQuality;
    uint32_t m_classificationAge;

    Vector2<float> m_objectBoxSize;
    Vector2<float> m_objBoxSizeSigma;
    float m_courseAngle;
    float m_courseAngleSigma;

    Vector2<float> m_relativeVelocity;
    Vector2<float> m_relativeVelocitySigma;
    Vector2<float> m_absoluteVelocity;
    Vector2<float> m_absoluteVelocitySigma;

    float m_objectHeight;
    float m_objectHeightSigma;

    Vector2<float> m_motionReferencePoint;
    Vector2<float> m_motionReferencePointSigma;

    float m_longitudianlAcceleration;
    float m_longitudianlAccelerationSigma;

    float m_yawRate;
    float m_yawRateSigma;

    // m_numContourPoints (uint8_t)
    uint8_t m_closestContourPointIndex;

    RefPointBoxLocation m_referencePointLocation;
    Vector2<float> m_referencePointCoord;
    Vector2<float> m_referencePointCoordSigma;
    float m_referencePointPositionCorrCoeff;

    Vector2<float> m_centerOfGravity;
    uint16_t m_objectPriority;
    float m_objectExistenceMeas;

    // height of buttom edge of the object box
    // from the ground (z=0 in vehicle coordinates)
    // Unit: 4 cm units. -5.12m .. +5.08m
    int8_t m_objectBoxHeightOffset;
    // uncertainity of objectBoxHeightOffset in cm.
    // max value: 2.55m
    uint8_t m_objectBoxHeightOffsetSigma;
    uint8_t m_reserved3;
    uint8_t m_reserved4;

    std::vector<Vector2<float>> m_contourPoints;
    MeasurementList m_measurementList;
}; // ObjectIn2281

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

//==============================================================================
//!\file
//!
//!\brief General object with members in SI units (m, rad, m/s, rad/s).
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Apr 12, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/objectlist/ContourPoint.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/UnfilteredObjectData.hpp>
#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>
#include <ibeo/common/sdk/datablocks/MeasurementList.hpp>
#include <ibeo/common/sdk/Vector2.hpp>
#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/ObjectBasic.hpp>
#include <ibeo/common/sdk/Time.hpp>

#include <stddef.h>
#include <cstdint>
#include <iostream>
#include <vector>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class Object
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;
    friend class ObjectListImporter2280_2290;
    friend class ObjectListImporter2281_2291;
    friend class ObjectListExporter2281_2291;

public:
    // Object flags.
    static const uint16_t objectFlagTrackedByStationaryModel{0x0040}; ///< Object is tracked using stationary model.
    static const uint16_t objectFlagMobile{
        0x0080}; ///< Object has been detected/validated as mobile (the current tracking model is irrelevant; this flag just means it has been moving at some time).
    static const uint16_t objectFlagValidated{
        0x0100}; ///< Object (stationary or dynamic) has been validated, i.e. valid enough to send out to the interface.
    static const uint16_t objectFlagOccluded{
        0x0200}; ///< Object was partly or fully occluded by another object or the edge of the scan field of view in the last update cycle, such that the full extent of the object was not visible.
    static const uint16_t objectFlagOverdrivable{
        0x0400}; ///< Object is low and can likely be driven over (curb, speed bump).
    static const uint16_t objectFlagUnderdrivable{
        0x0800}; ///< Object is suspended above the street and can likely be driven under (sign, bridge, parking garage).

    // Dynamic flags.
    static const uint8_t dynamicFlagExistenceMask{0x01};
    static const uint8_t dynamicFlagInit{0x00};
    static const uint8_t dynamicFlagExisting{0x01};

    static const uint8_t dynamicStateMask{0x0E};
    static const uint8_t dynamicStateUnknown{0x00};
    static const uint8_t dynamicStateMoving{0x02};
    static const uint8_t dynamicStateStopped{0x04};
    static const uint8_t dynamicStateStarted{0x06};
    static const uint8_t dynamicStateAPriorityStatic{0x08};

public:
    Object()          = default;
    virtual ~Object() = default;

public:
    void addMeasurement(const Measurement& meas) { m_measurementList.addMeasurement(meas); }
    void addContourPoint(const ContourPoint& contourPoint) { m_contourPoints.push_back(contourPoint); }

public: // getter
    uint32_t getObjectId() const { return m_objectId; }
    NTPTime getTimestamp() const { return m_timestamp; }

    uint16_t getObjectFlags() const { return m_objectFlags; }
    bool isTrackedByStationaryModel() const { return ((getObjectFlags() & objectFlagTrackedByStationaryModel) != 0); }
    bool isMobile() const { return ((getObjectFlags() & objectFlagMobile) != 0); }
    bool isValidated() const { return ((getObjectFlags() & objectFlagValidated) != 0); }
    bool isOccluded() const { return ((getObjectFlags() & objectFlagOccluded) != 0); }
    bool isOverdrivable() const { return ((getObjectFlags() & objectFlagOverdrivable) != 0); }
    bool isUnderdrivable() const { return ((getObjectFlags() & objectFlagUnderdrivable) != 0); }

    uint8_t getDynamicFlags() const { return m_dynamicFlags; }
    bool hasDynamicFlags() const { return ((getDynamicFlags() & dynamicFlagExistenceMask) == dynamicFlagExisting); }
    bool isDynamicStateUnknown() const
    {
        return ((!hasDynamicFlags()) || (getDynamicFlags() & dynamicStateMask) == dynamicStateUnknown);
    }
    bool isDynamicStateMoving() const
    {
        return (hasDynamicFlags() && (getDynamicFlags() & dynamicStateMask) == dynamicStateMoving);
    }
    bool isDynamicStateStopped() const
    {
        return (hasDynamicFlags() && (getDynamicFlags() & dynamicStateMask) == dynamicStateStopped);
    }
    bool isDynamicStateStarted() const
    {
        return (hasDynamicFlags() && (getDynamicFlags() & dynamicStateMask) == dynamicStateStarted);
    }
    bool isDynamicStateAPriorityStatic() const
    {
        return (hasDynamicFlags() && (getDynamicFlags() & dynamicStateMask) == dynamicStateAPriorityStatic);
    }

    uint32_t getObjectAge() const { return m_objectAge; }
    uint16_t getHiddenStatusAge() const { return m_hiddenStatusAge; }

    Vector2<float> getObjectBoxSize() const { return m_objectBoxSize; }
    Vector2<float> getObjectBoxSizeSigma() const { return m_objectBoxSizeSigma; }
    float getObjectBoxHeight() const { return m_objectBoxHeight; }
    float getObjectBoxHeightSigma() const { return m_objectBoxHeightSigma; }
    float getObjectBoxHeightOffset() const { return m_objectBoxHeightOffset; }
    float getObjectBoxHeightOffsetSigma() const { return m_objectBoxHeightOffsetSigma; }

    RefPointBoxLocation getReferencePointLocation() const { return m_referencePointLocation; }
    Vector2<float> getReferencePointCoord() const { return m_referencePointCoord; }
    Vector2<float> getReferencePointCoordSigma() const { return m_referencePointCoordSigma; }
    float getReferencePointCoordCorrCoeff() const { return m_referencePointCoordCorrCoeff; }

    float getCourseAngle() const { return m_courseAngle; }
    float getCourseAngleSigma() const { return m_courseAngleSigma; }
    float getYawRate() const { return m_yawRate; }
    float getYawRateSigma() const { return m_yawRateSigma; }

    ObjectClass getClassification() const { return m_classification; }
    float getClassificationQuality() const { return m_classificationQuality; }
    uint32_t getClassificationAge() const { return m_classificationAge; }

    Vector2<float> getMotionReferencePoint() const { return m_motionReferencePoint; }
    Vector2<float> getMotionReferencePointSigma() const { return m_motionReferencePointSigma; }

    Vector2<float> getCenterOfGravity() const { return m_centerOfGravity; }
    float getExistenceProbability() const { return m_existenceProbability; }
    uint16_t getObjectPriority() const { return m_objectPriority; }

    Vector2<float> getRelativeVelocity() const { return m_relativeVelocity; }
    Vector2<float> getRelativeVelocitySigma() const { return m_relativeVelocitySigma; }
    Vector2<float> getAbsoluteVelocity() const { return m_absoluteVelocity; }
    Vector2<float> getAbsoluteVelocitySigma() const { return m_absoluteVelocitySigma; }
    float getAbsoluteVelocityCorrCoeff() const;

    Vector2<float> getAcceleration() const { return m_acceleration; }
    Vector2<float> getAccelerationSigma() const { return m_accelerationSigma; }
    float getAccelerationCorrCoeff() const { return m_accelerationCorrCoeff; }
    float getLongitudinalAcceleration() const;
    float getLongitudinalAccelerationSigma() const;

    Vector2<float> getClosestObjectPointCoord() const { return m_closestObjectPointCoord; }
    uint8_t getNumContourPoints() const { return static_cast<uint8_t>(m_contourPoints.size()); }
    const std::vector<ContourPoint>& getContourPoints() const { return m_contourPoints; }
    std::vector<ContourPoint>& getContourPoints() { return m_contourPoints; }

    const MeasurementList& getMeasurementList() const { return m_measurementList; }
    MeasurementList& getMeasurementList() { return m_measurementList; }
    const MeasurementList& dynamicObjectProperties() const { return getMeasurementList(); }
    MeasurementList& dynamicObjectProperties() { return getMeasurementList(); }

    bool hasUnfilteredObjectData() const { return (m_unfilteredObjectData != nullptr); }
    const UnfilteredObjectData* getUnfilteredObjectData() const { return m_unfilteredObjectData; }
    UnfilteredObjectData* getUnfilteredObjectData() { return m_unfilteredObjectData; }

    Vector2<float> getObjectBoxPosition(const RefPointBoxLocation targetRefPointLocation) const;
    Vector2<float> getCenterPoint() const { return getObjectBoxPosition(RefPointBoxLocation::ObjectCenter); }

public: // setter
    void setObjectId(const uint32_t value) { m_objectId = value; }
    void setTimestamp(const NTPTime timestamp) { m_timestamp = timestamp; }

    void setObjectFlags(const uint16_t objectFlags) { m_objectFlags = objectFlags; }
    void setTrackedByStationaryModel(const bool set = true) { setObjectFlag(objectFlagTrackedByStationaryModel, set); }
    void setMobile(const bool set = true) { setObjectFlag(objectFlagMobile, set); }
    void setValidated(const bool set = true) { setObjectFlag(objectFlagValidated, set); }
    void setOccluded(const bool set = true) { setObjectFlag(objectFlagOccluded, set); }
    void setOverdrivable(const bool set = true) { setObjectFlag(objectFlagOverdrivable, set); }
    void setUnderdrivable(const bool set = true) { setObjectFlag(objectFlagUnderdrivable, set); }

    void setDynamicFlags(const uint8_t dynamicFlags) { m_dynamicFlags = dynamicFlags; }
    void clearDynamicState() { m_dynamicFlags = dynamicFlagInit; }
    void setDynamicStateUnknown() { setDynamicState(dynamicStateUnknown); }
    void setDynamicStateMoving() { setDynamicState(dynamicStateMoving); }
    void setDynamicStateStopped() { setDynamicState(dynamicStateStopped); }
    void setDynamicStateStarted() { setDynamicState(dynamicStateStarted); }
    void setDynamicStateAPriorityStatic() { setDynamicState(dynamicStateAPriorityStatic); }

    void setObjectAge(const uint32_t objectAge) { m_objectAge = objectAge; }
    void setHiddenStatusAge(const uint16_t hiddenStatusAge) { m_hiddenStatusAge = hiddenStatusAge; }

    void setObjectBoxSize(const Vector2<float>& objectBoxSize) { m_objectBoxSize = objectBoxSize; }
    void setObjectBoxSizeSigma(const Vector2<float>& objectBoxSizeSigma) { m_objectBoxSizeSigma = objectBoxSizeSigma; }
    void setObjectBoxHeight(const float objectBoxHeight) { m_objectBoxHeight = objectBoxHeight; }
    void setObjectBoxHeightSigma(const float objectBoxHeightSigma) { m_objectBoxHeightSigma = objectBoxHeightSigma; }
    void setObjectBoxHeightOffset(const float objectBoxHeightOffset)
    {
        m_objectBoxHeightOffset = objectBoxHeightOffset;
    }
    void setObjectBoxHeightOffsetSigma(const float objectBoxHeightOffsetSigma)
    {
        m_objectBoxHeightOffsetSigma = objectBoxHeightOffsetSigma;
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
    void setReferencePointCoordCorrCoeff(const float referencePointCoordCorrCoeff)
    {
        m_referencePointCoordCorrCoeff = referencePointCoordCorrCoeff;
    }

    void setCourseAngle(const float courseAngle) { m_courseAngle = courseAngle; }
    void setCourseAngleSigma(const float courseAngleSigma) { m_courseAngleSigma = courseAngleSigma; }
    void setYawRate(const float yawRate) { m_yawRate = yawRate; }
    void setYawRateSigma(const float yawRateSigma) { m_yawRateSigma = yawRateSigma; }

    void setClassification(const ObjectClass classification) { m_classification = classification; }
    void setClassificationQuality(const float classificationQuality)
    {
        m_classificationQuality = classificationQuality;
    }
    void setClassificationAge(const uint32_t classificationAge) { m_classificationAge = classificationAge; }

    void setMotionReferencePoint(const Vector2<float>& motionReferencePoint)
    {
        m_motionReferencePoint = motionReferencePoint;
    }
    void setMotionReferencePointSigma(const Vector2<float>& motionReferencePointSigma)
    {
        m_motionReferencePointSigma = motionReferencePointSigma;
    }

    void setCenterOfGravity(const Vector2<float>& centerOfGravity) { m_centerOfGravity = centerOfGravity; }
    void setExistenceProbability(const float existenceProbability) { m_existenceProbability = existenceProbability; }
    void setObjectPriority(const uint16_t objectPriority) { m_objectPriority = objectPriority; }

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

    void setAcceleration(const Vector2<float> acceleration) { m_acceleration = acceleration; }
    void setAccelerationSigma(const Vector2<float> accelerationSigma) { m_accelerationSigma = accelerationSigma; }

    void setClosestObjectPointCoord(const Vector2<float>& closestObjectPointCoord)
    {
        m_closestObjectPointCoord = closestObjectPointCoord;
    }
    void setContourPoints(const std::vector<ContourPoint>& contourPoints) { m_contourPoints = contourPoints; }

    void setMeasurementList(const MeasurementList& measurementList) { m_measurementList = measurementList; }
    void setDynamicObjectProperties(const MeasurementList& dynamicObjectProperties)
    {
        setMeasurementList(dynamicObjectProperties);
    }

    void setUnfilteredObjectData(const UnfilteredObjectData& unfilteredObjectData)
    {
        if (m_unfilteredObjectData == nullptr)
        {
            m_unfilteredObjectData = new UnfilteredObjectData();
        }

        *m_unfilteredObjectData = unfilteredObjectData;
    }

protected:
    static std::vector<int> getDirectionVector(const RefPointBoxLocation location);

    void setObjectFlag(const uint16_t flag, const bool set)
    {
        m_objectFlags = static_cast<uint16_t>(set ? (m_objectFlags | flag) : (m_objectFlags & ~flag));
    }

    void setDynamicState(const uint8_t state) { m_dynamicFlags = dynamicFlagExisting | state; }

    //The following fields MUST be filled before calling this function:
    // - absolute velocity
    // - absolute velocity sigma and correlation coefficient
    // - yaw rate
    // - yaw rate sigma
    void fillAccelerationFields(const float longAcc, const float longAccSigma);

protected:
    static constexpr float MinimumVelocityForLongitudinalAcceleration{1e-5F};

    uint32_t m_objectId{0};
    NTPTime m_timestamp{0};

    uint16_t m_objectFlags{0};
    uint8_t m_dynamicFlags{0};
    uint32_t m_objectAge{0};
    uint16_t m_hiddenStatusAge{0};

    Vector2<float> m_objectBoxSize{NaN, NaN};
    Vector2<float> m_objectBoxSizeSigma{NaN, NaN};
    float m_objectBoxHeight{NaN};
    float m_objectBoxHeightSigma{NaN};
    float m_objectBoxHeightOffset{NaN};
    float m_objectBoxHeightOffsetSigma{NaN};

    RefPointBoxLocation m_referencePointLocation{RefPointBoxLocation::Unknown};
    Vector2<float> m_referencePointCoord{NaN, NaN};
    Vector2<float> m_referencePointCoordSigma{NaN, NaN};
    float m_referencePointCoordCorrCoeff{NaN};

    float m_courseAngle{NaN};
    float m_courseAngleSigma{NaN};
    float m_yawRate{NaN};
    float m_yawRateSigma{NaN};

    ObjectClass m_classification{ObjectClass::Unclassified};
    float m_classificationQuality{NaN};
    uint32_t m_classificationAge{0};

    Vector2<float> m_motionReferencePoint{NaN, NaN};
    Vector2<float> m_motionReferencePointSigma{NaN, NaN};

    Vector2<float> m_centerOfGravity{NaN, NaN};
    float m_existenceProbability{NaN};
    uint16_t m_objectPriority{0xFFFFU};

    Vector2<float> m_relativeVelocity{NaN, NaN};
    Vector2<float> m_relativeVelocitySigma{NaN, NaN};
    Vector2<float> m_absoluteVelocity{NaN, NaN};
    Vector2<float> m_absoluteVelocitySigma{NaN, NaN};

    Vector2<float> m_acceleration{NaN, NaN};
    Vector2<float> m_accelerationSigma{NaN, NaN};
    float m_accelerationCorrCoeff{NaN};

    Vector2<float> m_closestObjectPointCoord{NaN, NaN};
    std::vector<ContourPoint> m_contourPoints;
    MeasurementList m_measurementList;

    UnfilteredObjectData* m_unfilteredObjectData{nullptr};
}; // Object

//==============================================================================

bool operator==(const Object& v1, const Object& v2);
inline bool operator!=(const Object& v1, const Object& v2) { return !(v1 == v2); }

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

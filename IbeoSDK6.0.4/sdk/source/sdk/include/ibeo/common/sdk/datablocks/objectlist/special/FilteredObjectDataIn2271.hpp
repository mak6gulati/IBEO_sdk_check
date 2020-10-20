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
//!\date Apr 23, 2014
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/ObjectBasic.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ContourPointIn2271.hpp>
#include <ibeo/common/sdk/Vector2.hpp>

#include <vector>
#include <iostream>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class FilteredObjectDataIn2271
{
public:
    enum class DynamicFlags : uint8_t
    {
        Existing      = 0x01U, // bit 0: 0=Init, 1=Existing
        Unknown       = 0x00U, // bit 1-3: state=unknown
        Moving        = 0x02U, // bit 1-3: state=moving
        Stopped       = 0x04U, // bit 1-3: state=stopped
        Started       = 0x06U, // bit 1-3: state=started
        APrioryStatic = 0x08U, // bit 1-3: state=aPrioryStatic

        Undefined = 0xFFU // not set
    };
    static constexpr uint8_t dynamicStateMask{0x0E};

public:
    FilteredObjectDataIn2271()          = default;
    virtual ~FilteredObjectDataIn2271() = default;

public:
    bool isValid() const { return m_isValid; }
    bool hasContourPoints() const { return m_hasContourPoints; }

    uint8_t getPriority() const { return m_priority; }

    uint16_t getObjectAge() const { return m_objectAge; }
    uint16_t getHiddenStatusAge() const { return m_hiddenStatusAge; }
    uint8_t getDynamicFlags() const { return m_dynamicFlags; }
    bool isDynamicFlagSet(const DynamicFlags flag) const
    {
        return (m_dynamicFlags != static_cast<uint8_t>(DynamicFlags::Unknown)
                && (m_dynamicFlags & static_cast<uint8_t>(flag)) != 0);
    }

    bool hasDynamicState() const { return isDynamicFlagSet(DynamicFlags::Existing); }
    DynamicFlags getDynamicState() const
    {
        return hasDynamicState() ? static_cast<DynamicFlags>(m_dynamicFlags & dynamicStateMask) : DynamicFlags::Unknown;
    }

    bool isDynamicStateUnknown() const { return getDynamicState() == DynamicFlags::Unknown; }
    bool isMoving() const { return getDynamicState() == DynamicFlags::Moving; }
    bool isStopped() const { return getDynamicState() == DynamicFlags::Stopped; }
    bool isStarted() const { return getDynamicState() == DynamicFlags::Started; }
    bool isAPrioryStaticObject() const { return getDynamicState() == DynamicFlags::APrioryStatic; }

    uint16_t getRelativeTimeOfMeasure() const { return m_relativeTimeOfMeasure; }
    Vector2<int16_t> getPositionClosestObjectPoint() const { return m_positionClosestObjectPoint; }

    Vector2<int16_t> getRelativeVelocity() const { return m_relativeVelocity; }
    Vector2<uint16_t> getRelativeVelocitySigma() const { return m_relativeVelocitySigma; }
    rawObjectClass::RawObjectClass getClassification() const { return m_classification; }
    uint8_t getClassificationQuality() const { return m_classificationQuality; }
    uint16_t getClassificationAge() const { return m_classificationAge; }

    uint16_t getReserved() const { return m_reserved; }
    Vector2<uint16_t> getObjectBoxSize() const { return m_objectBoxSize; }
    Vector2<uint16_t> getObjectBoxSizeSigma() const { return m_objectBoxSizeSigma; }
    int16_t getObjectBoxOrientation() const { return m_objectBoxOrientation; }
    uint16_t getObjectBoxOrientationSigma() const { return m_objectBoxOrientationSigma; }
    uint8_t getObjectBoxHeight() const { return m_objectBoxHeight; }
    RefPointBoxLocation getReferencePointLocation() const { return m_referencePointLocation; }
    Vector2<int16_t> getReferencePointCoord() const { return m_referencePointCoord; }
    Vector2<uint16_t> getReferencePointCoordSigma() const { return m_referencePointCoordSigma; }
    int16_t getReferencePointPositionCorrCoeff() const { return m_referencePointPositionCorrCoeff; }
    uint8_t getExistenceProbaility() const { return m_existenceProbaility; }
    uint8_t getPossibleNbOfContourPoints() const { return m_possibleNbOfContourPoints; }

    Vector2<int16_t> getAbsoluteVelocity() const { return m_absoluteVelocity; }
    Vector2<uint16_t> getAbsoluteVelocitySigma() const { return m_absoluteVelocitySigma; }
    int16_t getVelocityCorrCoeff() const { return m_velocityCorrCoeff; }
    Vector2<int16_t> getAcceleration() const { return m_acceleration; }
    Vector2<uint16_t> getAccelerationSigma() const { return m_accelerationSigma; }
    int16_t getAccelerationCorrCoeff() const { return m_accelerationCorrCoeff; }
    int16_t getYawRate() const { return m_yawRate; }
    uint16_t getYawRateSigma() const { return m_yawRateSigma; }

    const std::vector<ContourPointIn2271>& getContourPoints() const { return m_contourPoints; }
    std::vector<ContourPointIn2271>& getContourPoints() { return m_contourPoints; }

public:
    void setIsValid(const bool newIsValid) { m_isValid = newIsValid; }
    void setHasContourPoints(const bool newHasContourPoints) { m_hasContourPoints = newHasContourPoints; }

    void setPriority(const uint8_t newPriority) { m_priority = newPriority; }

    void setObjectAge(const uint16_t newObjectAge) { m_objectAge = newObjectAge; }
    void setHiddenStatusAge(const uint16_t newHiddenStatusAge) { m_hiddenStatusAge = newHiddenStatusAge; }

    void setDynamicFlags(const uint8_t newDynamicFlags) { m_dynamicFlags = newDynamicFlags; }
    void setDynamicFlag(const DynamicFlags flag) { m_dynamicFlags |= static_cast<uint8_t>(flag); }
    void clearDynamicFlag(const DynamicFlags flag)
    {
        m_dynamicFlags = static_cast<uint8_t>(m_dynamicFlags & (~static_cast<uint32_t>(flag)));
    }
    void setDynamicFlag(const DynamicFlags flag, const bool value)
    {
        value ? setDynamicFlag(flag) : clearDynamicFlag(flag);
    }
    void setDynamicState(const DynamicFlags state)
    {
        m_dynamicFlags = static_cast<uint8_t>(m_dynamicFlags & (~dynamicStateMask)); // Clear current state.
        m_dynamicFlags |= static_cast<uint8_t>(state); // Set new state.
        setHasDynamicState(); // Mark state as set.
    }

    void setHasDynamicState(const bool hasDynamicState = true)
    {
        setDynamicFlag(DynamicFlags::Existing, hasDynamicState);
    }

    void setDynamicStateUnknown() { setDynamicState(DynamicFlags::Unknown); }
    void setDynamicStateMoving() { setDynamicState(DynamicFlags::Moving); }
    void setDynamicStateStopped() { setDynamicState(DynamicFlags::Stopped); }
    void setDynamicStateStarted() { setDynamicState(DynamicFlags::Started); }
    void setDynamicStateAPrioryStaticObj() { setDynamicState(DynamicFlags::APrioryStatic); }

    void setRelativeTimeOfMeasure(const uint16_t newRelativeTimeOfMeasure)
    {
        m_relativeTimeOfMeasure = newRelativeTimeOfMeasure;
    }
    void setPositionClosestObjectPoint(const Vector2<int16_t>& newPositionClosestObjectPoint)
    {
        m_positionClosestObjectPoint = newPositionClosestObjectPoint;
    }

    void setRelativeVelocity(const Vector2<int16_t>& newRelativeVelocity) { m_relativeVelocity = newRelativeVelocity; }
    void setRelativeVelocitySigma(const Vector2<uint16_t>& newRelativeVelocitySigma)
    {
        m_relativeVelocitySigma = newRelativeVelocitySigma;
    }
    void setClassification(const rawObjectClass::RawObjectClass newClassification)
    {
        m_classification = newClassification;
    }
    void setClassificationQuality(const uint8_t newClassificationQuality)
    {
        m_classificationQuality = newClassificationQuality;
    }
    void setClassificationAge(const uint16_t newClassificationAge) { m_classificationAge = newClassificationAge; }

    void setReserved(const uint16_t newReserved) { m_reserved = newReserved; }
    void setObjectBoxSize(const Vector2<uint16_t>& newObjectBoxSize) { m_objectBoxSize = newObjectBoxSize; }
    void setObjectBoxSizeSigma(const Vector2<uint16_t>& newObjectBoxSizeSigma)
    {
        m_objectBoxSizeSigma = newObjectBoxSizeSigma;
    }
    void setObjectBoxOrientation(const int16_t newObjectBoxOrientation)
    {
        m_objectBoxOrientation = newObjectBoxOrientation;
    }
    void setObjectBoxOrientationSigma(const uint16_t newObjectBoxOrientationSigma)
    {
        m_objectBoxOrientationSigma = newObjectBoxOrientationSigma;
    }
    void setObjectBoxHeight(const uint8_t newObjectBoxHeight) { m_objectBoxHeight = newObjectBoxHeight; }
    void setReferencePointLocation(const RefPointBoxLocation newReferencePointLocation)
    {
        m_referencePointLocation = newReferencePointLocation;
    }
    void setReferencePointCoord(const Vector2<int16_t>& newReferencePointCoord)
    {
        m_referencePointCoord = newReferencePointCoord;
    }
    void setReferencePointCoordSigma(const Vector2<uint16_t>& newReferencePointCoordSigma)
    {
        m_referencePointCoordSigma = newReferencePointCoordSigma;
    }
    void setReferencePointPositionCorrCoeff(const int16_t newReferencePointPositionCorrCoeff)
    {
        m_referencePointPositionCorrCoeff = newReferencePointPositionCorrCoeff;
    }
    void setExistenceProbaility(const uint8_t newExistenceProbaility)
    {
        m_existenceProbaility = newExistenceProbaility;
    }

    void setAbsoluteVelocity(const Vector2<int16_t>& newAbsoluteVelocity) { m_absoluteVelocity = newAbsoluteVelocity; }
    void setAbsoluteVelocitySigma(const Vector2<uint16_t>& newAbsoluteVelocitySigma)
    {
        m_absoluteVelocitySigma = newAbsoluteVelocitySigma;
    }
    void setVelocityCorrCoeff(const int16_t newVelocityCorrCoeff) { m_velocityCorrCoeff = newVelocityCorrCoeff; }
    void setAcceleration(const Vector2<int16_t>& newAcceleration) { m_acceleration = newAcceleration; }
    void setAccelerationSigma(const Vector2<uint16_t>& newAccelerationSigma)
    {
        m_accelerationSigma = newAccelerationSigma;
    }
    void setAccelerationCorrCoeff(const int16_t newAccelerationCorrCoeff)
    {
        m_accelerationCorrCoeff = newAccelerationCorrCoeff;
    }
    void setYawRate(const int16_t newWRate) { m_yawRate = newWRate; }
    void setYawRateSigma(const uint16_t newWRateSigma) { m_yawRateSigma = newWRateSigma; }
    // no setter for m_positionClosestObjectPoint, will be adjusted when serializing.

    void setPossibleNbOfContourPoints(const uint8_t possibleNbOfCtPts)
    {
        m_possibleNbOfContourPoints = possibleNbOfCtPts;
    }
    void setContourPoints(const std::vector<ContourPointIn2271>& contourPoints) { m_contourPoints = contourPoints; }

public:
    std::streamsize getSerializedSize() const;
    bool deserialize(std::istream& is);
    bool serialize(std::ostream& os) const;

protected:
    bool m_isValid{false}; // not serialized
    bool m_hasContourPoints{false}; // not serialized

    uint8_t m_priority{0};

    uint16_t m_objectAge{0};
    uint16_t m_hiddenStatusAge{0};
    uint8_t m_dynamicFlags{static_cast<uint8_t>(DynamicFlags::Undefined)};

    uint16_t m_relativeTimeOfMeasure{0};
    Vector2<int16_t> m_positionClosestObjectPoint{};

    Vector2<int16_t> m_relativeVelocity{};
    Vector2<uint16_t> m_relativeVelocitySigma{};

    rawObjectClass::RawObjectClass m_classification{rawObjectClass::RawObjectClass::Unclassified};
    uint8_t m_classificationQuality{0};
    uint16_t m_classificationAge{0};

    uint16_t m_reserved{0};

    Vector2<uint16_t> m_objectBoxSize{};
    Vector2<uint16_t> m_objectBoxSizeSigma{};
    int16_t m_objectBoxOrientation{0};
    uint16_t m_objectBoxOrientationSigma{0};
    uint8_t m_objectBoxHeight{0};

    RefPointBoxLocation m_referencePointLocation{RefPointBoxLocation::Unknown};
    Vector2<int16_t> m_referencePointCoord{};
    Vector2<uint16_t> m_referencePointCoordSigma{};
    int16_t m_referencePointPositionCorrCoeff{0};

    uint8_t m_existenceProbaility{0};

    Vector2<int16_t> m_absoluteVelocity{};
    Vector2<uint16_t> m_absoluteVelocitySigma{};
    int16_t m_velocityCorrCoeff{0};

    Vector2<int16_t> m_acceleration{};
    Vector2<uint16_t> m_accelerationSigma{};
    int16_t m_accelerationCorrCoeff{0};

    int16_t m_yawRate{0};
    uint16_t m_yawRateSigma{0};

    uint8_t m_possibleNbOfContourPoints{0};
    std::vector<ContourPointIn2271> m_contourPoints{};
}; // FilteredObjectDataIn2271

//==============================================================================
//==============================================================================
//==============================================================================

bool operator==(const ibeo::common::sdk::FilteredObjectDataIn2271& lhs,
                const ibeo::common::sdk::FilteredObjectDataIn2271& rhs);
bool operator!=(const ibeo::common::sdk::FilteredObjectDataIn2271& lhs,
                const ibeo::common::sdk::FilteredObjectDataIn2271& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

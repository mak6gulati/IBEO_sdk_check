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
//!\date Jan 17, 2014
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Math.hpp>
#include <ibeo/common/sdk/Vector2.hpp>

#include <ibeo/common/sdk/ObjectBasic.hpp>

#include <vector>
#include <iostream>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Object with extended tracking information in the format of the LUX4/Scala145 firmware
class ObjectIn2270
{
public:
    enum class Flags : uint8_t
    {
        Stationary = 0x01U, ///< Stationary model if set.
        Mobile     = 0x02U, ///< Mobile, can only be set if object tracked by dynamic model.
        MotionModelValidated
        = 0x04U ///< Motion model validated, is true if object is validated according to motion model.
    }; // Flags

public:
    ObjectIn2270();
    ObjectIn2270(const ObjectIn2270& other) = default;
    ObjectIn2270& operator=(const ObjectIn2270& other) = default;

    virtual ~ObjectIn2270();

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    uint16_t getObjectId() const { return m_id; }
    uint16_t getObjectAge() const { return m_age; }
    uint16_t getPredictionAge() const { return m_predictionAge; }

    uint16_t getRelativeTimestamp() const { return m_relativeTimestamp; }
    uint8_t getReserved0() const { return m_reserved0; }

    RefPointBoxLocation getRefPointBoxLocation() const { return m_referencePointLocation; }
    Vector2<int16_t> getReferencePoint() const { return m_refPoint; }
    Vector2<uint16_t> getReferencePointSigma() const { return m_refPointSigma; }
    uint16_t getRefPointPosCorrCoeff() const { return m_referencePointPositionCorrCoeff; }

    uint16_t getObjectPriority() const { return m_objectPriority; }
    uint16_t getObjectExistenceMeasure() const { return m_objectExistenceMeasure; }
    Vector2<int16_t> getClosestPoint() const { return m_closestPoint; }

    Vector2<int16_t> getBoundingBoxCenter() const { return m_boundingBoxCenter; }
    uint16_t getBoundingBoxWidth() const { return m_boundingBoxWidth; }
    uint16_t getBoundingBoxLength() const { return m_boundingBoxLength; }

    Vector2<int16_t> getObjectBoxCenter() const { return m_objectBoxCenter; }
    uint16_t getObjectBoxSizeX() const { return m_objectBoxSizeX; }
    uint16_t getObjectBoxSizeY() const { return m_objectBoxSizeY; }
    int16_t getObjectBoxOrientation() const { return m_objectBoxOrientation; }
    Vector2<uint16_t> getObjectBoxSizeSigma() const { return m_objectBoxSizeSigma; }
    uint16_t getObjectBoxOrientationSigma() const { return m_objectBoxOrientationSigma; }

    Vector2<int16_t> getAbsoluteVelocity() const { return m_absVelocity; }
    Vector2<uint16_t> getAbsoluteVelocitySigma() const { return m_absVelSigma; }

    Vector2<int16_t> getRelativeVelocity() const { return m_relVelocity; }
    Vector2<uint16_t> getRelativeVelocitySigma() const { return m_relVelSigma; }

    ObjectClass getClassification() const { return m_class; }
    uint8_t getFlags() const { return m_flags; }
    bool isFlagSet(const Flags flag) const { return (m_flags & static_cast<uint8_t>(flag)) != 0; }

    bool isTrackedByStationaryModel() const { return isFlagSet(Flags::Stationary); }
    bool isMobile() const { return isFlagSet(Flags::Mobile); }
    bool isMotionModelValidated() const { return isFlagSet(Flags::MotionModelValidated); }

    uint16_t getClassificationAge() const { return m_classAge; }
    uint16_t getClassificationConfidence() const { return m_classConfidence; }

    uint16_t getNbOfContourPoints() const { return m_nbOfContourPoints; }
    bool getNbContourPointsIsValid() const { return m_nbOfContourPointsIsValid; }
    const std::vector<Vector2<int16_t>>& getContourPoints() const { return m_contourPoints; }
    std::vector<Vector2<int16_t>>& getContourPoints() { return m_contourPoints; }

public:
    void setObjectId(const uint16_t id) { this->m_id = id; }
    void setObjectAge(const uint16_t age) { this->m_age = age; }
    void setPredictionAge(const uint16_t predictionAge) { this->m_predictionAge = predictionAge; }
    void setRelativeTimestamp(const uint16_t relativeTimestamp) { this->m_relativeTimestamp = relativeTimestamp; }

    void setRefPointBoxLocation(const RefPointBoxLocation newRefPtLocation)
    {
        m_referencePointLocation = newRefPtLocation;
    }
    void setRefPoint(const Vector2<int16_t> refPoint) { this->m_refPoint = refPoint; }
    void setRefPointSigma(const Vector2<uint16_t> refPointSigma) { this->m_refPointSigma = refPointSigma; }
    void setReferencePointPositionCorrCoeff(const uint16_t corrCoeff)
    {
        this->m_referencePointPositionCorrCoeff = corrCoeff;
    }

    void setObjectPriority(const uint16_t newObjPrio) { this->m_objectPriority = newObjPrio; }
    void setObjectExistenceMeasure(const uint16_t newExistenceMeasure)
    {
        this->m_objectExistenceMeasure = newExistenceMeasure;
    }
    void setClosestPoint(const Vector2<int16_t> newClosesPoint) { this->m_closestPoint = newClosesPoint; }

    void setBoundingBoxCenter(const Vector2<int16_t> boundingBoxCenter)
    {
        this->m_boundingBoxCenter = boundingBoxCenter;
    }
    void setBoundingBoxWidth(const uint16_t boundingBoxWidth) { this->m_boundingBoxWidth = boundingBoxWidth; }
    void setBoundingBoxLength(const uint16_t boundingBoxLength) { this->m_boundingBoxLength = boundingBoxLength; }

    void setObjectBoxCenter(const Vector2<int16_t> objectBoxCenter) { this->m_objectBoxCenter = objectBoxCenter; }
    void setObjectBoxLength(const uint16_t objectBoxLength) { this->m_objectBoxSizeX = objectBoxLength; }
    void setObjectBoxWidth(const uint16_t objectBoxWidth) { this->m_objectBoxSizeY = objectBoxWidth; }
    void setObjectBoxOrientation(const int16_t objectBoxOrientation)
    {
        this->m_objectBoxOrientation = objectBoxOrientation;
    }
    void setObjectBoxSizeSigma(const Vector2<uint16_t> newObjBoxSizeSigma)
    {
        this->m_objectBoxSizeSigma = newObjBoxSizeSigma;
    }
    void setObjectBoxOrientationSigma(const uint16_t newOrientSigma)
    {
        this->m_objectBoxOrientationSigma = newOrientSigma;
    }

    void setAbsVelocity(const Vector2<int16_t> absVelocity) { this->m_absVelocity = absVelocity; }
    void setAbsVelSigma(const Vector2<uint16_t> absVelSigma) { this->m_absVelSigma = absVelSigma; }
    void setRelVelocity(const Vector2<int16_t> relVelocity) { this->m_relVelocity = relVelocity; }
    void setRelVelSigma(const Vector2<uint16_t> relVelSigma) { this->m_relVelSigma = relVelSigma; }

    void setClass(const ObjectClass cl) { this->m_class = cl; }

    void setFlags(const uint8_t newFlags) { this->m_flags = newFlags; }
    void setFlag(const Flags flag) { m_flags |= static_cast<uint8_t>(flag); }
    void clearFlag(const Flags flag) { m_flags = static_cast<uint8_t>(m_flags & (~static_cast<uint32_t>(flag))); }
    void setFlag(const Flags flag, const bool value) { value ? setFlag(flag) : clearFlag(flag); }

    void setTrackedByStationaryModel(const bool isTrackedByStationaryModel = true)
    {
        setFlag(Flags::Stationary, isTrackedByStationaryModel);
    }
    void setMobile(const bool isMobile = true) { setFlag(Flags::Mobile, isMobile); }
    void setMotionModelValidated(const bool isMotionModelValidated = true)
    {
        setFlag(Flags::MotionModelValidated, isMotionModelValidated);
    }

    void setClassAge(const uint16_t classAge) { this->m_classAge = classAge; }
    void setClassCertainty(const uint16_t classConfidence) { this->m_classConfidence = classConfidence; }

    void setNbOfContourPoints(const uint16_t nbOfContourPoints)
    {
        if (nbOfContourPoints != contourIsInvalid)
        {
            this->m_nbOfContourPoints        = nbOfContourPoints;
            this->m_nbOfContourPointsIsValid = true;
        }
        else
        {
            this->m_nbOfContourPoints        = 1;
            this->m_nbOfContourPointsIsValid = false;
        }
    }

    void setNbOfCoutourPointsValid(const bool valid) { this->m_nbOfContourPointsIsValid = valid; }
    void setContourPoints(const std::vector<Vector2<int16_t>>& newContourPts) { this->m_contourPoints = newContourPts; }

public:
    static float angle2rad(const int16_t ticks)
    {
        const uint16_t angleTicksPerRotation = 36000;
        // (x < 0) ? ((x % N) + N) : x % N
        return ((ticks < 0) ? float((ticks % angleTicksPerRotation) + angleTicksPerRotation)
                            : float(ticks % angleTicksPerRotation))
               * 2.f * static_cast<float>(M_PI) / float(angleTicksPerRotation);
    }

protected:
    static const uint16_t contourIsInvalid;

protected:
    uint16_t m_id{0};
    uint16_t m_age{0};
    uint16_t m_predictionAge{0};

    uint16_t m_relativeTimestamp{0};
    uint8_t m_reserved0{0};

    RefPointBoxLocation m_referencePointLocation{RefPointBoxLocation::Unknown}; // as uint8_t
    Vector2<int16_t> m_refPoint{};
    Vector2<uint16_t> m_refPointSigma{};
    uint16_t m_referencePointPositionCorrCoeff{0};

    uint16_t m_objectPriority{0};
    uint16_t m_objectExistenceMeasure{0};
    Vector2<int16_t> m_closestPoint{};

    Vector2<int16_t> m_boundingBoxCenter{};
    uint16_t m_boundingBoxWidth{0}; // y-value
    uint16_t m_boundingBoxLength{0}; // x-value

    Vector2<int16_t> m_objectBoxCenter{};
    uint16_t m_objectBoxSizeX{0}; // x-value
    uint16_t m_objectBoxSizeY{0}; // y-value
    int16_t m_objectBoxOrientation{0}; // angle in [deg/100].
    Vector2<uint16_t> m_objectBoxSizeSigma{};
    uint16_t m_objectBoxOrientationSigma{0};

    Vector2<int16_t> m_absVelocity{};
    Vector2<uint16_t> m_absVelSigma{};

    Vector2<int16_t> m_relVelocity{};
    Vector2<uint16_t> m_relVelSigma{};

    ObjectClass m_class{ObjectClass::Unclassified}; // as uint8_t
    uint8_t m_flags{0};
    uint16_t m_classAge{0};
    uint16_t m_classConfidence{0};

    uint16_t m_nbOfContourPoints{0};
    bool m_nbOfContourPointsIsValid{true};
    std::vector<Vector2<int16_t>> m_contourPoints{};
}; // ObjectIn2270

//==============================================================================

bool operator==(const ObjectIn2270& lhs, const ObjectIn2270& rhs);
bool operator!=(const ObjectIn2270& lhs, const ObjectIn2270& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

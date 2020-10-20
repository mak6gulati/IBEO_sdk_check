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
//! \date Apr 26, 2012
//------------------------------------------------------------------------------

//==============================================================================

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

class ObjectIn2221
{
public:
    static constexpr uint16_t maxContourPoints{34};

public:
    using ContourPointVector = std::vector<Vector2<int16_t>>;

public:
    ObjectIn2221() = default;
    ObjectIn2221(const ObjectIn2221& other);
    ObjectIn2221& operator=(const ObjectIn2221& other);

    virtual ~ObjectIn2221() = default;

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    uint16_t getObjectId() const { return m_id; }
    uint16_t getObjectAge() const { return m_age; }
    uint16_t getPredictionAge() const { return m_predictionAge; }

    uint16_t getRelativeTimestamp() const { return m_relativeTimestamp; }
    Vector2<int16_t> getReferencePoint() const { return m_refPoint; }
    Vector2<uint16_t> getReferencePointSigma() const { return m_refPointSigma; }

    Vector2<int16_t> getClosestPoint() const { return m_closestPoint; }

    Vector2<int16_t> getBoundingBoxCenter() const { return m_boundingBoxCenter; }
    uint16_t getBoundingBoxWidth() const { return m_boundingBoxWidth; }
    uint16_t getBoundingBoxLength() const { return m_boundingBoxLength; }

    Vector2<int16_t> getObjectBoxCenter() const { return m_objectBoxCenter; }
    uint16_t getObjectBoxSizeX() const { return m_objectBoxSizeX; }
    uint16_t getObjectBoxSizeY() const { return m_objectBoxSizeY; }
    int16_t getObjectBoxOrientation() const { return m_objectBoxOrientation; }

    Vector2<int16_t> getAbsoluteVelocity() const { return m_absVelocity; }
    uint16_t getAbsoluteVelocitySigmaX() const { return m_absVelSigmaX; }
    uint16_t getAbsoluteVelocitySigmaY() const { return m_absVelSigmaY; }

    Vector2<int16_t> getRelativeVelocity() const { return m_relVelocity; }

    luxObjectClass::LuxObjectClass getClassification() const { return m_class; }
    uint16_t getClassificationAge() const { return m_classAge; }
    uint16_t getClassificationCertainty() const { return m_classCertainty; }

    uint16_t getNumberOfContourPoints() const { return m_numContourPoints; }
    bool isNumContourPointsValid() const { return this->m_numContourPointsIsValid; }
    const ContourPointVector& getContourPoints() const { return m_contourPoints; }
    ContourPointVector& getContourPoints() { return m_contourPoints; }

public:
    void setObjectId(const uint16_t id) { this->m_id = id; }
    void setObjectAge(const uint16_t age) { this->m_age = age; }
    void setPredictionAge(const uint16_t predictionAge) { this->m_predictionAge = predictionAge; }
    void setRelativeTimestamp(const uint16_t relativeTimestamp) { this->m_relativeTimestamp = relativeTimestamp; }
    void setRefPoint(const Vector2<int16_t> refPoint) { this->m_refPoint = refPoint; }
    void setRefPointSigma(const Vector2<uint16_t> refPointSigma) { this->m_refPointSigma = refPointSigma; }
    void setClosestPoint(const Vector2<int16_t> closestPoint) { this->m_closestPoint = closestPoint; }
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
    void setAbsVelocity(const Vector2<int16_t> absVelocity) { this->m_absVelocity = absVelocity; }
    void setAbsVelSigmaX(const uint16_t absVelSigmaX) { this->m_absVelSigmaX = absVelSigmaX; }
    void setAbsVelSigmaY(const uint16_t absVelSigmaY) { this->m_absVelSigmaY = absVelSigmaY; }
    void setRelVelocity(const Vector2<int16_t> relVelocity) { this->m_relVelocity = relVelocity; }
    void setClass(const luxObjectClass::LuxObjectClass cl) { this->m_class = cl; }
    void setClassAge(const uint16_t classAge) { this->m_classAge = classAge; }
    void setClassCertainty(const uint16_t classCertainty) { this->m_classCertainty = classCertainty; }
    void setNumContourPoints(const uint16_t numContourPoints);

    void setNumCoutourPointsValid(const bool valid) { this->m_numContourPointsIsValid = valid; }
    void setContourPoints(const ContourPointVector& newContourPts) { this->m_contourPoints = newContourPts; }

public:
    static float angle2rad(const int16_t ticks);

protected:
    static const uint16_t contourIsInvalid;

protected:
    uint16_t m_id{0};
    uint16_t m_age{0};
    uint16_t m_predictionAge{0};

    uint16_t m_relativeTimestamp{0};
    Vector2<int16_t> m_refPoint{};
    Vector2<uint16_t> m_refPointSigma{};
    Vector2<int16_t> m_closestPoint{};
    Vector2<int16_t> m_boundingBoxCenter{};
    uint16_t m_boundingBoxWidth{0}; // y-value
    uint16_t m_boundingBoxLength{0}; // x-value
    Vector2<int16_t> m_objectBoxCenter{};
    uint16_t m_objectBoxSizeX{0}; // x-value
    uint16_t m_objectBoxSizeY{0}; // y-value
    int16_t m_objectBoxOrientation{0}; // angle in [deg/100].
    Vector2<int16_t> m_absVelocity{};
    uint16_t m_absVelSigmaX{0};
    uint16_t m_absVelSigmaY{0};
    Vector2<int16_t> m_relVelocity{};
    luxObjectClass::LuxObjectClass m_class{luxObjectClass::LuxObjectClass::Unclassified};
    uint16_t m_classAge{0};
    uint16_t m_classCertainty{0};
    uint16_t m_numContourPoints{0};
    bool m_numContourPointsIsValid{true};
    ContourPointVector m_contourPoints{};
}; // ObjectIn2221

//==============================================================================

bool operator==(const ObjectIn2221& lhs, const ObjectIn2221& rhs);

inline bool operator!=(const ObjectIn2221& lhs, const ObjectIn2221& rhs) { return !(lhs == rhs); }

//==============================================================================

std::ostream& operator<<(std::ostream& os, const ObjectIn2221& luxObj);

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

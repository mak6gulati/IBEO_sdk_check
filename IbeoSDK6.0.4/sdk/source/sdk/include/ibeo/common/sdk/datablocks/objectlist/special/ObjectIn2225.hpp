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

#include <ibeo/common/sdk/Vector2.hpp>
#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/ObjectBasic.hpp>

#include <ibeo/common/sdk/misc/deprecatedwarning.hpp>

#include <vector>
#include <iostream>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class ObjectIn2225
{
public:
    ObjectIn2225();
    ObjectIn2225(const ObjectIn2225& src);
    virtual ~ObjectIn2225() = default;

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    uint16_t getObjectId() const { return m_id; }
    uint16_t getReserved() const { return m_reserved; }
    uint32_t getObjectAge() const { return m_age; }

    NTPTime getTimestamp() const { return m_timestamp; }
    uint16_t getHiddenStatusAge() const { return m_hiddenStatusAge; }

    ObjectClass getClassification() const { return m_class; }
    uint8_t getClassificationCertainty() const { return m_classCertainty; }
    uint32_t getClassificationAge() const { return m_classAge; }

    Vector2<float> getBoundingBoxCenter() { return m_boundingBoxCenter; }
    const Vector2<float>& getBoundingBoxCenter() const { return m_boundingBoxCenter; }
    Vector2<float> getBoundingBoxSize() { return m_boundingBoxSize; }
    const Vector2<float>& getBoundingBoxSize() const { return m_boundingBoxSize; }

    Vector2<float> getObjectBoxCenter() { return m_objectBoxCenter; }
    const Vector2<float>& getObjectBoxCenter() const { return m_objectBoxCenter; }
    Vector2<float> getObjectBoxSigma() { return m_objectBoxSigma; }
    const Vector2<float>& getObjectBoxSigma() const { return m_objectBoxSigma; }
    Vector2<float> getObjectBoxSize() { return m_objectBoxSize; }
    const Vector2<float>& getObjectBoxSize() const { return m_objectBoxSize; }
    uint64_t getReserved2() const { return m_reserved2; }

    IBEOSDK_DEPRECATED float getYawAngle() const { return m_objectBoxOrientation; }
    IBEOSDK_DEPRECATED float getYawAngleSigma() const { return m_objectBoxOrientationSigma; }
    float getObjectBoxOrientation() const { return m_objectBoxOrientation; }
    float getObjectBoxOrientationSigma() const { return m_objectBoxOrientationSigma; }

    Vector2<float> getRelativeVelocity() { return m_relVelocity; }
    const Vector2<float>& getRelativeVelocity() const { return m_relVelocity; }
    Vector2<float> getRelativeVelocitySigma() { return m_relVelocitySigma; }
    const Vector2<float>& getRelativeVelocitySigma() const { return m_relVelocitySigma; }

    Vector2<float> getAbsoluteVelocity() { return m_absVelocity; }
    const Vector2<float>& getAbsoluteVelocity() const { return m_absVelocity; }
    Vector2<float> getAbsoluteVelocitySigma() { return m_absVelocitySigma; }
    const Vector2<float>& getAbsoluteVelocitySigma() const { return m_absVelocitySigma; }
    float getOrientation() const { return this->m_orientation; }

    uint8_t getNumberOfContourPoints() const { return m_numContourPoints; }
    std::vector<Vector2<float>>& getContourPoints() { return m_contourPoints; }
    const std::vector<Vector2<float>>& getContourPoints() const { return m_contourPoints; }

    uint8_t getIndexOfClosestPoint() const { return m_indexOfClosedPoint; }

public:
    void setObjectId(const uint16_t newObjectId) { m_id = newObjectId; }
    void setReserved(const uint16_t newReserved) { m_reserved = newReserved; }
    void setObjectAge(const uint32_t newObjectAge) { m_age = newObjectAge; }

    void setTimestamp(const NTPTime newTimestamp) { m_timestamp = newTimestamp; }
    void setHiddenStatusAge(const uint16_t newHiddenStatusAge) { m_hiddenStatusAge = newHiddenStatusAge; }

    void setClassification(const ObjectClass newClassification) { m_class = newClassification; }
    void setClassificationCertainty(const uint8_t newClassificationCertainty)
    {
        m_classCertainty = newClassificationCertainty;
    }
    void setClassificationAge(const uint32_t newClassificationAge) { m_classAge = newClassificationAge; }

    void setBoundingBoxCenter(const Vector2<float>& newBoundingBoxCenter)
    {
        m_boundingBoxCenter = newBoundingBoxCenter;
    }
    void setBoundingBoxSize(const Vector2<float>& newBoundingBoxSize) { m_boundingBoxSize = newBoundingBoxSize; }
    void setReserved2(const uint64_t& newReserved2) { m_reserved2 = newReserved2; }

    void setObjectBoxCenter(const Vector2<float>& newObjectBoxCenter) { m_objectBoxCenter = newObjectBoxCenter; }
    void setObjectBoxSigma(const Vector2<float>& newObjectBoxSigma) { m_objectBoxSigma = newObjectBoxSigma; }
    void setObjectBoxSize(const Vector2<float>& newObjectBoxSize) { m_objectBoxSize = newObjectBoxSize; }

    IBEOSDK_DEPRECATED void setYawAngle(const float newObjBoxOrientation)
    {
        m_objectBoxOrientation = newObjBoxOrientation;
    }
    IBEOSDK_DEPRECATED void setYawAngleSigma(const float newObjBoxOrientationSigma)
    {
        m_objectBoxOrientationSigma = newObjBoxOrientationSigma;
    }
    void setObjBoxOrientation(const float newObjBoxOrientation) { m_objectBoxOrientation = newObjBoxOrientation; }
    void setObjBoxOrientationSigma(const float newObjBoxOrientationSigma)
    {
        m_objectBoxOrientationSigma = newObjBoxOrientationSigma;
    }

    void setRelativeVelocity(const Vector2<float>& newRelativeVelocity) { m_relVelocity = newRelativeVelocity; }
    void setRelativeVelocitySigma(const Vector2<float>& newRelativeVelocitySigma)
    {
        m_relVelocitySigma = newRelativeVelocitySigma;
    }

    void setAbsoluteVelocity(const Vector2<float>& newAbsoluteVelocity) { m_absVelocity = newAbsoluteVelocity; }
    void setAbsoluteVelocitySigma(const Vector2<float>& newAbsoluteVelocitySigma)
    {
        m_absVelocitySigma = newAbsoluteVelocitySigma;
    }
    void setOrientation(const float newOrientation) { this->m_orientation = newOrientation; }

    void setNumberOfContourPoints(const uint8_t newNumberOfContourPoints)
    {
        m_numContourPoints = newNumberOfContourPoints;
    }
    void setContourPoints(const std::vector<Vector2<float>>& newContourPoints) { m_contourPoints = newContourPoints; }

    void setIndexOfClosestPoint(const uint8_t newIndexOfClosestPoint) { m_indexOfClosedPoint = newIndexOfClosestPoint; }

public:
    bool operator==(const ObjectIn2225& other) const;
    bool operator!=(const ObjectIn2225& other) const { return !((*this) == other); }

protected:
    static const int nbOfBytesInReserved3 = 18;

protected:
    uint16_t m_id;
    uint16_t m_reserved;
    uint32_t m_age;
    NTPTime m_timestamp;
    uint16_t m_hiddenStatusAge;

    ObjectClass m_class;
    uint8_t m_classCertainty;
    uint32_t m_classAge;

    Vector2<float> m_boundingBoxCenter;
    Vector2<float> m_boundingBoxSize;

    Vector2<float> m_objectBoxCenter;
    Vector2<float> m_objectBoxSigma;
    Vector2<float> m_objectBoxSize;

    uint64_t m_reserved2;

    float m_objectBoxOrientation;
    float m_objectBoxOrientationSigma;

    Vector2<float> m_relVelocity;
    Vector2<float> m_relVelocitySigma;

    Vector2<float> m_absVelocity;
    Vector2<float> m_absVelocitySigma;

    char m_reserved3[nbOfBytesInReserved3];

    uint8_t m_numContourPoints;
    uint8_t m_indexOfClosedPoint;
    std::vector<Vector2<float>> m_contourPoints;

protected: // not serialized data
    float m_orientation;
}; // ObjectIn2225

//==============================================================================

std::ostream& operator<<(std::ostream& os, const ObjectIn2225& o);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

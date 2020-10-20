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
//! \date Sep 5, 2013
//------------------------------------------------------------------------------

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

//! \brief Object with extended tracking information (generic)
class ObjectIn2280
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
    ObjectIn2280();
    virtual ~ObjectIn2280() = default;

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public: // getter
    uint16_t getObjectId() const { return m_objectId; }

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
    uint16_t getObjectPredAge() const { return m_objectPredAge; }
    ObjectClass getClassification() const { return m_classification; }
    uint8_t getClassCertainty() const { return m_classCertainty; }
    uint32_t getClassAge() const { return m_classAge; }
    Vector2<float> getReserved0() const { return m_reserved0; }
    Vector2<float> getReserved1() const { return m_reserved1; }
    Vector2<float> getObjBoxCenter() const { return m_objBoxCenter; }
    Vector2<float> getObjBoxCenterSigma() const { return m_objBoxCenterSigma; }
    Vector2<float> getObjBoxSize() const { return m_objBoxSize; }
    Vector2<float> getReserved2() const { return m_reserved2; }
    IBEOSDK_DEPRECATED float getObjCourseAngle() const { return m_objBoxOrientation; }
    IBEOSDK_DEPRECATED float getObjCourseAngleSigma() const { return m_objBoxOrientationSigma; }
    float getObjBoxOrientation() const { return m_objBoxOrientation; }
    float getObjBoxOrientationSigma() const { return m_objBoxOrientationSigma; }
    Vector2<float> getRelVelocity() const { return m_relVelocity; }
    Vector2<float> getRelVelocitySigma() const { return m_relVelocitySigma; }
    Vector2<float> getAbsVelocity() const { return m_absVelocity; }
    Vector2<float> getAbsVelocitySigma() const { return m_absVelocitySigma; }
    uint64_t getReserved4() const { return m_reserved4; }
    float getReserved5() const { return m_reserved5; }
    float getReserved6() const { return m_reserved6; }
    uint16_t getReserved7() const { return m_reserved7; }
    uint8_t getNbOfContourPoints() const { return uint8_t(m_contourPoints.size()); }
    uint8_t getIdxOfClosestPoint() const { return m_idxOfClosestPoint; }
    RefPointBoxLocation getRefPointLocation() const { return m_refPointLocation; }
    Vector2<float> getRefPointCoords() const { return m_refPointCoords; }
    Vector2<float> getRefPointCoordsSigma() const { return m_refPointCoordsSigma; }
    float getRefPointPosCorrCoeffs() const { return m_refPointPosCorrCoeffs; }
    float getReserved8() const { return m_reserved8; }
    float getReserved9() const { return m_reserved9; }
    uint16_t getObjPriority() const { return m_objPriority; }
    float getObjExtMeasurement() const { return m_objExtMeasurement; }
    const std::vector<Vector2<float>>& getContourPoints() const { return m_contourPoints; }
    std::vector<Vector2<float>>& getContourPoints() { return m_contourPoints; }

public: // setter
    void setObjectId(const uint16_t newObjectId) { m_objectId = newObjectId; }

    void setFlags(const uint16_t newFlags) { m_flags = newFlags; }
    void setTrackedByStationaryModel(const bool set = true)
    {
        m_flags = set ? static_cast<uint16_t>(m_flags | static_cast<uint16_t>(Flags::TrackedByStationaryModel))
                      : static_cast<uint16_t>(m_flags & ~static_cast<uint16_t>(Flags::TrackedByStationaryModel));
    }
    void setMobile(const bool set = true)
    {
        m_flags = set ? static_cast<uint16_t>(m_flags | static_cast<uint16_t>(Flags::Mobile))
                      : static_cast<uint16_t>(m_flags & ~static_cast<uint16_t>(Flags::Mobile));
    }
    void setMotionModelValidated(const bool set = true)
    {
        m_flags = set ? static_cast<uint16_t>(m_flags | static_cast<uint16_t>(Flags::Validated))
                      : static_cast<uint16_t>(m_flags & ~static_cast<uint16_t>(Flags::Validated));
    }

    void setObjectAge(const uint32_t newObjectAge) { m_objectAge = newObjectAge; }
    void setTimestamp(const NTPTime newTimestamp) { m_timestamp = newTimestamp; }
    void setObjectPredAge(const uint16_t newObjectPredAge) { m_objectPredAge = newObjectPredAge; }
    void setClassification(const ObjectClass newClassification) { m_classification = newClassification; }
    void setClassCertainty(const uint8_t newClassCertainty) { m_classCertainty = newClassCertainty; }
    void setClassAge(const uint32_t newClassAge) { m_classAge = newClassAge; }
    void setReserved0(const Vector2<float> reserved0) { m_reserved0 = reserved0; }
    void setReserved1(const Vector2<float> reserved1) { m_reserved1 = reserved1; }
    void setObjBoxCenter(const Vector2<float> newObjBoxCenter) { m_objBoxCenter = newObjBoxCenter; }
    void setObjBoxCenterSigma(const Vector2<float> newObjBoxCenterSigma) { m_objBoxCenterSigma = newObjBoxCenterSigma; }
    void setObjBoxSize(const Vector2<float> newObjBoxSize) { m_objBoxSize = newObjBoxSize; }
    void setReserved2(const Vector2<float> reserved2) { m_reserved2 = reserved2; }

    IBEOSDK_DEPRECATED
    void setObjCourseAngle(const float newObjBoxOrientation) { m_objBoxOrientation = newObjBoxOrientation; }
    IBEOSDK_DEPRECATED
    void setObjCourseAngleSigma(const float newObjBoxOrientationSigma)
    {
        m_objBoxOrientationSigma = newObjBoxOrientationSigma;
    }

    void setObjBoxOrientation(const float newObjBoxOrientation) { m_objBoxOrientation = newObjBoxOrientation; }
    void setObjBoxOrientationSigma(const float newObjBoxOrientationSigma)
    {
        m_objBoxOrientationSigma = newObjBoxOrientationSigma;
    }
    void setRelVelocity(const Vector2<float> newRelVelocity) { m_relVelocity = newRelVelocity; }
    void setRelVelocitySigma(const Vector2<float> newRelVelocitySigma) { m_relVelocitySigma = newRelVelocitySigma; }
    void setAbsVelocity(const Vector2<float> newAbsVelocity) { m_absVelocity = newAbsVelocity; }
    void setAbsVelocitySigma(const Vector2<float> newAbsVelocitySigma) { m_absVelocitySigma = newAbsVelocitySigma; }
    void setReserved4(const uint64_t reserved4) { m_reserved4 = reserved4; }
    void setReserved5(const float reserved5) { m_reserved5 = reserved5; }
    void setReserved6(const float reserved6) { m_reserved6 = reserved6; }
    void setReserved7(const uint16_t reserved7) { m_reserved7 = reserved7; }
    void setNbOfContourPoints(const uint8_t newNbOfContourPoints) { m_contourPoints.resize(newNbOfContourPoints); }
    void setIdxOfClosestPoint(const uint8_t newIdxOfClosestPoint) { m_idxOfClosestPoint = newIdxOfClosestPoint; }
    void setRefPointLocation(const RefPointBoxLocation newRefPointLocation)
    {
        m_refPointLocation = newRefPointLocation;
    }
    void setRefPointCoords(const Vector2<float> newRefPointCoords) { m_refPointCoords = newRefPointCoords; }
    void setRefPointCoordsSigma(const Vector2<float> newRefPointCoordsSigma)
    {
        m_refPointCoordsSigma = newRefPointCoordsSigma;
    }
    void setRefPointPosCorrCoeffs(const float newRefPointPosCorrCoeffs)
    {
        m_refPointPosCorrCoeffs = newRefPointPosCorrCoeffs;
    }
    void setReserved8(const float reserved8) { m_reserved8 = reserved8; }
    void setReserved9(const float reserved9) { m_reserved9 = reserved9; }
    void setObjPriority(const uint16_t newObjPriority) { m_objPriority = newObjPriority; }
    void setObjExtMeasurement(const float newObjExtMeasurement) { m_objExtMeasurement = newObjExtMeasurement; }
    void setContourPoints(const std::vector<Vector2<float>> contourPoints) { m_contourPoints = contourPoints; }

public:
    Vector2<float> convertRefPoint(const RefPointBoxLocation toPos) const
    {
        return ibeo::common::sdk::convertRefPoint(this->getRefPointCoords(),
                                                  this->getObjBoxOrientation(),
                                                  this->getObjBoxSize(),
                                                  this->getRefPointLocation(),
                                                  toPos);
    }

public:
    bool operator==(const ObjectIn2280& other) const;
    bool operator!=(const ObjectIn2280& other) const { return !((*this) == other); }

protected:
    uint16_t m_objectId;
    uint16_t m_flags;
    uint32_t m_objectAge;
    NTPTime m_timestamp;
    uint16_t m_objectPredAge;
    ObjectClass m_classification; // uint8_t
    uint8_t m_classCertainty;
    uint32_t m_classAge;
    Vector2<float> m_reserved0;
    Vector2<float> m_reserved1;
    Vector2<float> m_objBoxCenter;
    Vector2<float> m_objBoxCenterSigma;
    Vector2<float> m_objBoxSize;
    Vector2<float> m_reserved2;
    float m_objBoxOrientation; //!<[rad]
    float m_objBoxOrientationSigma; //!<[rad]
    Vector2<float> m_relVelocity;
    Vector2<float> m_relVelocitySigma;
    Vector2<float> m_absVelocity;
    Vector2<float> m_absVelocitySigma;

    // 18 bytes reserved/internal
    uint64_t m_reserved4;
    float m_reserved5;
    float m_reserved6;
    uint16_t m_reserved7;

    // nb of contour points  uint8_t
    uint8_t m_idxOfClosestPoint;

    RefPointBoxLocation m_refPointLocation; // uint16_t
    Vector2<float> m_refPointCoords;
    Vector2<float> m_refPointCoordsSigma;
    float m_refPointPosCorrCoeffs;
    float m_reserved8;
    float m_reserved9;
    uint16_t m_objPriority;
    float m_objExtMeasurement;
    std::vector<Vector2<float>> m_contourPoints;
}; // ObjectIn2280

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

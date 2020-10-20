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

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2280.hpp>
#include <ibeo/common/sdk/Math.hpp>
#include <ibeo/common/sdk/ObjectBasic.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

ObjectIn2280::ObjectIn2280()
  : m_objectId(0),
    m_flags(0),
    m_objectAge(0),
    m_timestamp(),
    m_objectPredAge(0),
    m_classification(ObjectClass::Unclassified),
    m_classCertainty(0),
    m_classAge(0),
    m_reserved0(),
    m_reserved1(),
    m_objBoxCenter(),
    m_objBoxCenterSigma(),
    m_objBoxSize(),
    m_reserved2(),
    m_objBoxOrientation(.0f),
    m_objBoxOrientationSigma(.0f),
    m_relVelocity(),
    m_relVelocitySigma(),
    m_absVelocity(),
    m_absVelocitySigma(),
    m_reserved4(0),
    m_reserved5(.0f),
    m_reserved6(.0f),
    m_reserved7(0),
    m_idxOfClosestPoint(0),
    m_refPointLocation(RefPointBoxLocation::Unknown),
    m_refPointCoords(),
    m_refPointCoordsSigma(),
    m_refPointPosCorrCoeffs(.0f),
    m_reserved8(.0f),
    m_reserved9(.0f),
    m_objPriority(0),
    m_objExtMeasurement(.0f),
    m_contourPoints()
{}

//==============================================================================

std::streamsize ObjectIn2280::getSerializedSize() const
{
    return 2 * std::streamsize(sizeof(uint16_t)) // objectId, flags
           + std::streamsize(sizeof(uint32_t)) // objectAge
           + std::streamsize(sizeof(NTPTime)) // timestamp
           + std::streamsize(sizeof(uint16_t)) // objectPredAge
           + 2 * std::streamsize(sizeof(uint8_t)) // classification, classCertainty
           + std::streamsize(sizeof(uint32_t)) // classAge
           + serializedSize(m_reserved0) + serializedSize(m_reserved1) + serializedSize(m_objBoxCenter)
           + serializedSize(m_objBoxCenterSigma) + serializedSize(m_objBoxSize) + serializedSize(m_reserved2)
           + 2 * std::streamsize(sizeof(float)) // objCourseAngle, objCourseAngleSigma
           + serializedSize(m_relVelocity) + serializedSize(m_relVelocitySigma) + serializedSize(m_absVelocity)
           + serializedSize(m_absVelocitySigma) + std::streamsize(sizeof(uint64_t)) // reserved4
           + 2 * std::streamsize(sizeof(float)) // reserved5, 6
           + std::streamsize(sizeof(uint16_t)) // reserved7
           + 2 * std::streamsize(sizeof(uint8_t)) // nbOfPts, idxOfClosestPoint
           + std::streamsize(sizeof(uint16_t)) // refPointLocation
           + serializedSize(m_refPointCoords) + serializedSize(m_refPointCoordsSigma)
           + 3 * std::streamsize(sizeof(float)) // refPointPosCorrCoeffs, reserved8, 9
           + std::streamsize(sizeof(uint16_t)) // objPriority
           + std::streamsize(sizeof(float)) // objextMeasurement
           + std::streamsize(m_contourPoints.size()) * ibeo::common::sdk::serializedSize(Vector2<float>());
}
//==============================================================================

bool ObjectIn2280::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, m_objectId);
    readBE(is, m_flags);
    readBE(is, m_objectAge);
    readBE(is, m_timestamp);
    readBE(is, m_objectPredAge);
    readBE(is, m_classification);

    readBE(is, m_classCertainty);
    readBE(is, m_classAge);
    readBE(is, m_reserved0);
    readBE(is, m_reserved1);
    readBE(is, m_objBoxCenter);
    readBE(is, m_objBoxCenterSigma);
    readBE(is, m_objBoxSize);
    readBE(is, m_reserved2);
    readBE(is, m_objBoxOrientation);
    readBE(is, m_objBoxOrientationSigma);
    readBE(is, m_relVelocity);
    readBE(is, m_relVelocitySigma);
    readBE(is, m_absVelocity);
    readBE(is, m_absVelocitySigma);
    readBE(is, m_reserved4);
    readBE(is, m_reserved5);
    readBE(is, m_reserved6);
    readBE(is, m_reserved7);

    {
        uint8_t rd8;
        readBE(is, rd8);
        m_contourPoints.resize(rd8);
    }

    readBE(is, m_idxOfClosestPoint);
    readBE<16>(is, m_refPointLocation);
    readBE(is, m_refPointCoords);
    readBE(is, m_refPointCoordsSigma);
    readBE(is, m_refPointPosCorrCoeffs);
    readBE(is, m_reserved8);
    readBE(is, m_reserved9);
    readBE(is, m_objPriority);
    readBE(is, m_objExtMeasurement);
    std::vector<Vector2<float>>::iterator cpIter = m_contourPoints.begin();
    for (; cpIter != m_contourPoints.end(); ++cpIter)
    {
        readBE(is, *cpIter);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ObjectIn2280::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, m_objectId);
    writeBE(os, m_flags);
    writeBE(os, m_objectAge);
    writeBE(os, m_timestamp);
    writeBE(os, m_objectPredAge);
    writeBE(os, m_classification);

    writeBE(os, m_classCertainty);
    writeBE(os, m_classAge);
    writeBE(os, m_reserved0);
    writeBE(os, m_reserved1);
    writeBE(os, m_objBoxCenter);
    writeBE(os, m_objBoxCenterSigma);
    writeBE(os, m_objBoxSize);
    writeBE(os, m_reserved2);
    writeBE(os, m_objBoxOrientation);
    writeBE(os, m_objBoxOrientationSigma);
    writeBE(os, m_relVelocity);
    writeBE(os, m_relVelocitySigma);
    writeBE(os, m_absVelocity);
    writeBE(os, m_absVelocitySigma);
    writeBE(os, m_reserved4);
    writeBE(os, m_reserved5);
    writeBE(os, m_reserved6);
    writeBE(os, m_reserved7);

    writeBE(os, uint8_t(m_contourPoints.size()));
    writeBE(os, m_idxOfClosestPoint);
    writeBE<16>(os, m_refPointLocation);
    writeBE(os, m_refPointCoords);
    writeBE(os, m_refPointCoordsSigma);
    writeBE(os, m_refPointPosCorrCoeffs);
    writeBE(os, m_reserved8);
    writeBE(os, m_reserved9);
    writeBE(os, m_objPriority);
    writeBE(os, m_objExtMeasurement);
    std::vector<Vector2<float>>::const_iterator cpIter = m_contourPoints.begin();
    for (; cpIter != m_contourPoints.end(); ++cpIter)
    {
        writeBE(os, *cpIter);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ObjectIn2280::operator==(const ObjectIn2280& other) const
{
    return (m_objectId == other.getObjectId()) && (m_flags == other.getFlags()) && (m_objectAge == other.getObjectAge())
           && (m_timestamp == other.getTimestamp()) && (m_objectPredAge == other.getObjectPredAge())
           && (m_classification == other.getClassification()) && (m_classCertainty == other.getClassCertainty())
           && (m_classAge == other.getClassAge()) && (m_reserved0 == other.getReserved0())
           && (m_reserved1 == other.getReserved1()) && (m_objBoxCenter == other.getObjBoxCenter())
           && (m_objBoxCenterSigma == other.getObjBoxCenterSigma()) && (m_objBoxSize == other.getObjBoxSize())
           && (m_reserved2 == other.getReserved2())
           && (fuzzyFloatEqualT<7>(m_objBoxOrientation, other.getObjBoxOrientation()))
           && (fuzzyFloatEqualT<7>(m_objBoxOrientationSigma, other.getObjBoxOrientationSigma()))
           && (m_relVelocity == other.getRelVelocity()) && (m_relVelocitySigma == other.getRelVelocitySigma())
           && (m_absVelocity == other.getAbsVelocity()) && (m_absVelocitySigma == other.getAbsVelocitySigma())
           && (m_reserved4 == other.getReserved4()) && (fuzzyFloatEqualT<7>(m_reserved5, other.getReserved5()))
           && (fuzzyFloatEqualT<7>(m_reserved6, other.getReserved6())) && (m_reserved7 == other.getReserved7())
           && (m_idxOfClosestPoint == other.getIdxOfClosestPoint())
           && (m_refPointLocation == other.getRefPointLocation()) && (m_refPointCoords == other.getRefPointCoords())
           && (m_refPointCoordsSigma == other.getRefPointCoordsSigma())
           && (fuzzyFloatEqualT<7>(m_refPointPosCorrCoeffs, other.getRefPointPosCorrCoeffs()))
           && (fuzzyFloatEqualT<7>(m_reserved8, other.getReserved8()))
           && (fuzzyFloatEqualT<7>(m_reserved9, other.getReserved9())) && (m_objPriority == other.getObjPriority())
           && (fuzzyFloatEqualT<7>(m_objExtMeasurement, other.getObjExtMeasurement()))
           && (m_contourPoints == other.getContourPoints());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

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

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2270.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//static
const uint16_t ObjectIn2270::contourIsInvalid{0xFFFF};

//==============================================================================

ObjectIn2270::ObjectIn2270() { m_contourPoints.reserve(16); }

//==============================================================================

ObjectIn2270::~ObjectIn2270() {}

//==============================================================================

std::streamsize ObjectIn2270::getSerializedSize() const
{
    return 4 * std::streamsize(sizeof(uint16_t)) // id .. relativeTimestamp
           + 2 * std::streamsize(sizeof(uint8_t)) // reserved .. refPtLoc
           + serializedSize(m_refPoint) + serializedSize(m_refPointSigma)
           + 3 * std::streamsize(sizeof(uint16_t)) // refPtPosCorrCoeff .. objExMeas
           + serializedSize(m_closestPoint) + serializedSize(m_boundingBoxCenter)
           + 2 * std::streamsize(sizeof(uint16_t)) // bbBox size
           + serializedSize(m_objectBoxCenter) // obj box center
           + 2 * std::streamsize(sizeof(uint16_t)) + 1 * std::streamsize(sizeof(int16_t))
           + serializedSize(m_objectBoxSizeSigma) // objBoxSigma
           + 1 * std::streamsize(sizeof(uint16_t)) // objBoxOriSigma
           + serializedSize(m_absVelocity) + serializedSize(m_absVelSigma) + serializedSize(m_relVelocity)
           + serializedSize(m_relVelSigma) + 2 * std::streamsize(sizeof(uint8_t)) // class, flags
           + 3 * std::streamsize(sizeof(uint16_t)) // classAge .. m_numContourPoints
           + (m_nbOfContourPointsIsValid ? m_nbOfContourPoints : 1) * serializedSize(Vector2<int16_t>());
}

//==============================================================================

bool ObjectIn2270::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeLE(os, m_id);
    ibeo::common::sdk::writeLE(os, m_age);
    ibeo::common::sdk::writeLE(os, m_predictionAge);

    ibeo::common::sdk::writeLE(os, m_relativeTimestamp);
    ibeo::common::sdk::writeLE(os, m_reserved0);
    writeBE<8>(os, m_referencePointLocation);

    ibeo::common::sdk::writeLE(os, m_refPoint);
    ibeo::common::sdk::writeLE(os, m_refPointSigma);
    ibeo::common::sdk::writeLE(os, m_referencePointPositionCorrCoeff);

    ibeo::common::sdk::writeLE(os, m_objectPriority);
    ibeo::common::sdk::writeLE(os, m_objectExistenceMeasure);
    ibeo::common::sdk::writeLE(os, m_closestPoint);

    ibeo::common::sdk::writeLE(os, m_boundingBoxCenter);
    ibeo::common::sdk::writeLE(os, m_boundingBoxWidth);
    ibeo::common::sdk::writeLE(os, m_boundingBoxLength);

    ibeo::common::sdk::writeLE(os, m_objectBoxCenter);
    ibeo::common::sdk::writeLE(os, m_objectBoxSizeX);
    ibeo::common::sdk::writeLE(os, m_objectBoxSizeY);
    ibeo::common::sdk::writeLE(os, m_objectBoxOrientation);
    ibeo::common::sdk::writeLE(os, m_objectBoxSizeSigma);
    ibeo::common::sdk::writeLE(os, m_objectBoxOrientationSigma);

    ibeo::common::sdk::writeLE(os, m_absVelocity);
    ibeo::common::sdk::writeLE(os, m_absVelSigma);

    ibeo::common::sdk::writeLE(os, m_relVelocity);
    ibeo::common::sdk::writeLE(os, m_relVelSigma);

    ibeo::common::sdk::writeLE(os, uint8_t(m_class));
    ibeo::common::sdk::writeLE(os, m_flags);
    ibeo::common::sdk::writeLE(os, m_classAge);
    ibeo::common::sdk::writeLE(os, m_classConfidence);

    if (m_nbOfContourPointsIsValid)
        ibeo::common::sdk::writeLE(os, m_nbOfContourPoints);
    else
        ibeo::common::sdk::writeLE(os, ObjectIn2270::contourIsInvalid);

    std::vector<Vector2<int16_t>>::const_iterator cpIter = m_contourPoints.begin();
    for (; cpIter != m_contourPoints.end(); ++cpIter)
    {
        ibeo::common::sdk::writeLE(os, *cpIter);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ObjectIn2270::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readLE(is, m_id);
    ibeo::common::sdk::readLE(is, m_age);
    ibeo::common::sdk::readLE(is, m_predictionAge);

    ibeo::common::sdk::readLE(is, m_relativeTimestamp);
    ibeo::common::sdk::readLE(is, m_reserved0);

    readBE<8>(is, m_referencePointLocation);
    ibeo::common::sdk::readLE(is, m_refPoint);
    ibeo::common::sdk::readLE(is, m_refPointSigma);
    ibeo::common::sdk::readLE(is, m_referencePointPositionCorrCoeff);

    ibeo::common::sdk::readLE(is, m_objectPriority);
    ibeo::common::sdk::readLE(is, m_objectExistenceMeasure);
    ibeo::common::sdk::readLE(is, m_closestPoint);

    ibeo::common::sdk::readLE(is, m_boundingBoxCenter);
    ibeo::common::sdk::readLE(is, m_boundingBoxWidth);
    ibeo::common::sdk::readLE(is, m_boundingBoxLength);

    ibeo::common::sdk::readLE(is, m_objectBoxCenter);
    ibeo::common::sdk::readLE(is, m_objectBoxSizeX);
    ibeo::common::sdk::readLE(is, m_objectBoxSizeY);
    ibeo::common::sdk::readLE(is, m_objectBoxOrientation);
    ibeo::common::sdk::readLE(is, m_objectBoxSizeSigma);
    ibeo::common::sdk::readLE(is, m_objectBoxOrientationSigma);

    ibeo::common::sdk::readLE(is, m_absVelocity);
    ibeo::common::sdk::readLE(is, m_absVelSigma);

    ibeo::common::sdk::readLE(is, m_relVelocity);
    ibeo::common::sdk::readLE(is, m_relVelSigma);

    uint8_t c = static_cast<uint8_t>(ObjectClass::Unclassified);
    ibeo::common::sdk::readLE(is, c);
    switch (c)
    {
    case 1:
        m_class = ObjectClass::UnknownSmall;
        break;
    case 2:
        m_class = ObjectClass::UnknownBig;
        break;
    case 3:
        m_class = ObjectClass::Pedestrian;
        break;
    case 4:
        m_class = ObjectClass::Bike;
        break;
    case 5:
        m_class = ObjectClass::Car;
        break;
    case 6:
        m_class = ObjectClass::Truck;
        break;
    default:
        m_class = ObjectClass::Unclassified;
        break;
    }

    ibeo::common::sdk::readLE(is, m_flags);
    ibeo::common::sdk::readLE(is, m_classAge);
    ibeo::common::sdk::readLE(is, m_classConfidence);

    ibeo::common::sdk::readLE(is, m_nbOfContourPoints);
    m_nbOfContourPointsIsValid = (this->m_nbOfContourPoints != ObjectIn2270::contourIsInvalid);
    if (!m_nbOfContourPointsIsValid)
    {
        m_nbOfContourPoints = 1;
    }

    m_contourPoints.resize(m_nbOfContourPoints);
    std::vector<Vector2<int16_t>>::iterator cpIter = m_contourPoints.begin();
    for (; cpIter != m_contourPoints.end(); ++cpIter)
    {
        ibeo::common::sdk::readLE(is, *cpIter);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool operator==(const ObjectIn2270& lhs, const ObjectIn2270& rhs)
{
    return (lhs.getObjectId() == rhs.getObjectId()) && (lhs.getObjectAge() == rhs.getObjectAge())
           && (lhs.getPredictionAge() == rhs.getPredictionAge())

           && (lhs.getRelativeTimestamp() == rhs.getRelativeTimestamp()) && (lhs.getReserved0() == rhs.getReserved0())

           && (lhs.getRefPointBoxLocation() == rhs.getRefPointBoxLocation())
           && (lhs.getReferencePoint() == rhs.getReferencePoint())
           && (lhs.getReferencePointSigma() == rhs.getReferencePointSigma())
           && (lhs.getRefPointPosCorrCoeff() == rhs.getRefPointPosCorrCoeff())

           && (lhs.getObjectPriority() == rhs.getObjectPriority())
           && (lhs.getObjectExistenceMeasure() == rhs.getObjectExistenceMeasure())
           && (lhs.getClosestPoint() == rhs.getClosestPoint())

           && (lhs.getBoundingBoxCenter() == rhs.getBoundingBoxCenter())
           && (lhs.getBoundingBoxWidth() == rhs.getBoundingBoxWidth())
           && (lhs.getBoundingBoxLength() == rhs.getBoundingBoxLength())

           && (lhs.getObjectBoxCenter() == rhs.getObjectBoxCenter())
           && (lhs.getObjectBoxSizeX() == rhs.getObjectBoxSizeX())
           && (lhs.getObjectBoxSizeY() == rhs.getObjectBoxSizeY())
           && (lhs.getObjectBoxOrientation() == rhs.getObjectBoxOrientation())
           && (lhs.getObjectBoxSizeSigma() == rhs.getObjectBoxSizeSigma())
           && (lhs.getObjectBoxOrientationSigma() == rhs.getObjectBoxOrientationSigma())

           && (lhs.getAbsoluteVelocity() == rhs.getAbsoluteVelocity())
           && (lhs.getAbsoluteVelocitySigma() == rhs.getAbsoluteVelocitySigma())

           && (lhs.getRelativeVelocity() == rhs.getRelativeVelocity())
           && (lhs.getRelativeVelocitySigma() == rhs.getRelativeVelocitySigma())

           && (lhs.getClassification() == rhs.getClassification()) && (lhs.getFlags() == rhs.getFlags())
           && (lhs.getClassificationAge() == rhs.getClassificationAge())
           && (lhs.getClassificationConfidence() == rhs.getClassificationConfidence())

           && (lhs.getNbOfContourPoints() == rhs.getNbOfContourPoints())
           && (lhs.getContourPoints() == rhs.getContourPoints()) && (lhs.getContourPoints() == rhs.getContourPoints());
}

//==============================================================================

bool operator!=(const ObjectIn2270& lhs, const ObjectIn2270& rhs) { return !(lhs == rhs); }
//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2221.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//static
const uint16_t ObjectIn2221::contourIsInvalid = 0xFFFFU;

//==============================================================================

ObjectIn2221::ObjectIn2221(const ObjectIn2221& other)
  : m_id(other.m_id),
    m_age(other.m_age),
    m_predictionAge(other.m_predictionAge),
    m_relativeTimestamp(other.m_relativeTimestamp),
    m_refPoint(other.m_refPoint),
    m_refPointSigma(other.m_refPointSigma),
    m_closestPoint(other.m_closestPoint),
    m_boundingBoxCenter(other.m_boundingBoxCenter),
    m_boundingBoxWidth(other.m_boundingBoxWidth),
    m_boundingBoxLength(other.m_boundingBoxLength),
    m_objectBoxCenter(other.m_objectBoxCenter),
    m_objectBoxSizeX(other.m_objectBoxSizeX),
    m_objectBoxSizeY(other.m_objectBoxSizeY),
    m_objectBoxOrientation(other.m_objectBoxOrientation),
    m_absVelocity(other.m_absVelocity),
    m_absVelSigmaX(other.m_absVelSigmaX),
    m_absVelSigmaY(other.m_absVelSigmaY),
    m_relVelocity(other.m_relVelocity),
    m_class(other.m_class),
    m_classAge(other.m_classAge),
    m_classCertainty(other.m_classCertainty),
    m_numContourPoints(other.m_numContourPoints),
    m_numContourPointsIsValid(other.m_numContourPointsIsValid),
    m_contourPoints(other.m_contourPoints)
{}

//==============================================================================

ObjectIn2221& ObjectIn2221::operator=(const ObjectIn2221& other)
{
    if (this == &other)
        return *this;

    m_id                      = other.m_id;
    m_age                     = other.m_age;
    m_predictionAge           = other.m_predictionAge;
    m_relativeTimestamp       = other.m_relativeTimestamp;
    m_refPoint                = other.m_refPoint;
    m_refPointSigma           = other.m_refPointSigma;
    m_closestPoint            = other.m_closestPoint;
    m_boundingBoxCenter       = other.m_boundingBoxCenter;
    m_boundingBoxWidth        = other.m_boundingBoxWidth;
    m_boundingBoxLength       = other.m_boundingBoxLength;
    m_objectBoxCenter         = other.m_objectBoxCenter;
    m_objectBoxSizeX          = other.m_objectBoxSizeX;
    m_objectBoxSizeY          = other.m_objectBoxSizeY;
    m_objectBoxOrientation    = other.m_objectBoxOrientation;
    m_absVelocity             = other.m_absVelocity;
    m_absVelSigmaX            = other.m_absVelSigmaX;
    m_absVelSigmaY            = other.m_absVelSigmaY;
    m_relVelocity             = other.m_relVelocity;
    m_class                   = other.m_class;
    m_classAge                = other.m_classAge;
    m_classCertainty          = other.m_classCertainty;
    m_numContourPointsIsValid = other.m_numContourPointsIsValid;
    m_numContourPoints        = other.m_numContourPoints;
    m_contourPoints           = other.m_contourPoints;

    return *this;
}

//==============================================================================

std::streamsize ObjectIn2221::getSerializedSize() const
{
    return 4 * std::streamsize(sizeof(uint16_t)) + serializedSize(m_refPoint) + serializedSize(m_refPointSigma)
           + serializedSize(m_closestPoint) + serializedSize(m_boundingBoxCenter)
           + 2 * std::streamsize(sizeof(uint16_t)) + serializedSize(m_objectBoxCenter)
           + 2 * std::streamsize(sizeof(uint16_t)) + 1 * std::streamsize(sizeof(int16_t))
           + serializedSize(m_absVelocity) + 2 * std::streamsize(sizeof(uint16_t)) + serializedSize(m_relVelocity)
           + 4 * std::streamsize(sizeof(uint16_t))
           + (m_numContourPointsIsValid ? m_numContourPoints : 1) * serializedSize(Vector2<int16_t>());
}

//==============================================================================

bool ObjectIn2221::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeLE(os, m_id);
    ibeo::common::sdk::writeLE(os, m_age);
    ibeo::common::sdk::writeLE(os, m_predictionAge);
    ibeo::common::sdk::writeLE(os, m_relativeTimestamp);
    ibeo::common::sdk::writeLE(os, m_refPoint);
    ibeo::common::sdk::writeLE(os, m_refPointSigma);
    ibeo::common::sdk::writeLE(os, m_closestPoint);
    ibeo::common::sdk::writeLE(os, m_boundingBoxCenter);

    ibeo::common::sdk::writeLE(os, m_boundingBoxWidth);
    ibeo::common::sdk::writeLE(os, m_boundingBoxLength);

    ibeo::common::sdk::writeLE(os, m_objectBoxCenter);
    ibeo::common::sdk::writeLE(os, m_objectBoxSizeX);
    ibeo::common::sdk::writeLE(os, m_objectBoxSizeY);
    ibeo::common::sdk::writeLE(os, m_objectBoxOrientation);

    ibeo::common::sdk::writeLE(os, m_absVelocity);
    ibeo::common::sdk::writeLE(os, m_absVelSigmaX);
    ibeo::common::sdk::writeLE(os, m_absVelSigmaY);

    ibeo::common::sdk::writeLE(os, m_relVelocity);

    const uint16_t c = static_cast<uint16_t>(m_class);
    ibeo::common::sdk::writeLE(os, c);

    ibeo::common::sdk::writeLE(os, m_classAge);
    ibeo::common::sdk::writeLE(os, m_classCertainty);

    if (m_numContourPointsIsValid)
    {
        ibeo::common::sdk::writeLE(os, m_numContourPoints);
    }
    else
    {
        ibeo::common::sdk::writeLE(os, ObjectIn2221::contourIsInvalid);
    }

    std::vector<Vector2<int16_t>>::const_iterator cpIter = m_contourPoints.begin();
    for (; cpIter != m_contourPoints.end(); ++cpIter)
    {
        ibeo::common::sdk::writeLE(os, *cpIter);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ObjectIn2221::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readLE(is, m_id);
    ibeo::common::sdk::readLE(is, m_age);
    ibeo::common::sdk::readLE(is, m_predictionAge);
    ibeo::common::sdk::readLE(is, m_relativeTimestamp);

    ibeo::common::sdk::readLE(is, m_refPoint);
    ibeo::common::sdk::readLE(is, m_refPointSigma);

    ibeo::common::sdk::readLE(is, m_closestPoint);

    ibeo::common::sdk::readLE(is, m_boundingBoxCenter);
    ibeo::common::sdk::readLE(is, m_boundingBoxWidth);
    ibeo::common::sdk::readLE(is, m_boundingBoxLength);

    ibeo::common::sdk::readLE(is, m_objectBoxCenter);
    ibeo::common::sdk::readLE(is, m_objectBoxSizeX);
    ibeo::common::sdk::readLE(is, m_objectBoxSizeY);
    ibeo::common::sdk::readLE(is, m_objectBoxOrientation);

    ibeo::common::sdk::readLE(is, m_absVelocity);
    ibeo::common::sdk::readLE(is, m_absVelSigmaX);
    ibeo::common::sdk::readLE(is, m_absVelSigmaY);

    ibeo::common::sdk::readLE(is, m_relVelocity);

    uint16_t c = static_cast<uint16_t>(ObjectClass::Unclassified);
    ibeo::common::sdk::readLE(is, c);
    switch (c)
    {
    case 1:
        m_class = luxObjectClass::LuxObjectClass::UnknownSmall;
        break;
    case 2:
        m_class = luxObjectClass::LuxObjectClass::UnknownBig;
        break;
    case 3:
        m_class = luxObjectClass::LuxObjectClass::Pedestrian;
        break;
    case 4:
        m_class = luxObjectClass::LuxObjectClass::Bike;
        break;
    case 5:
        m_class = luxObjectClass::LuxObjectClass::Car;
        break;
    case 6:
        m_class = luxObjectClass::LuxObjectClass::Truck;
        break;
    case 12:
        m_class = luxObjectClass::LuxObjectClass::Bicycle;
        break;
    default:
        m_class = luxObjectClass::LuxObjectClass::Unclassified;
        break;
    }

    ibeo::common::sdk::readLE(is, m_classAge);
    ibeo::common::sdk::readLE(is, m_classCertainty);

    ibeo::common::sdk::readLE(is, m_numContourPoints);
    m_numContourPointsIsValid = (this->m_numContourPoints != ObjectIn2221::contourIsInvalid);
    if (!m_numContourPointsIsValid)
    {
        m_numContourPoints = 1;
    }

    if (this->m_numContourPoints <= ObjectIn2221::maxContourPoints)
    {
        m_contourPoints.resize(m_numContourPoints);

        std::vector<Vector2<int16_t>>::iterator cpIter = m_contourPoints.begin();
        for (; cpIter != m_contourPoints.end(); ++cpIter)
        {
            ibeo::common::sdk::readLE(is, *cpIter);
        }
    }
    else
    {
        is.clear(std::ios::failbit);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

void ObjectIn2221::setNumContourPoints(const uint16_t numContourPoints)
{
    if (numContourPoints != contourIsInvalid)
    {
        this->m_numContourPoints        = numContourPoints;
        this->m_numContourPointsIsValid = true;
    }
    else
    {
        this->m_numContourPoints        = 1;
        this->m_numContourPointsIsValid = false;
    }
}

//==============================================================================

float ObjectIn2221::angle2rad(const int16_t ticks)
{
    const uint16_t angleTicksPerRotation = 36000;
    // (x < 0) ? ((x % N) + N) : x % N
    return ((ticks < 0) ? float((ticks % angleTicksPerRotation) + angleTicksPerRotation)
                        : float(ticks % angleTicksPerRotation))
           * 2.f * static_cast<float>(M_PI) / float(angleTicksPerRotation);
}

//==============================================================================

bool operator==(const ObjectIn2221& lhs, const ObjectIn2221& rhs)
{
    return (lhs.getObjectId() == rhs.getObjectId()) && (lhs.getObjectAge() == rhs.getObjectAge())
           && (lhs.getPredictionAge() == rhs.getPredictionAge()) &&

           (lhs.getRelativeTimestamp() == rhs.getRelativeTimestamp())
           && (lhs.getReferencePoint() == rhs.getReferencePoint())
           && (lhs.getReferencePointSigma() == rhs.getReferencePointSigma()) &&

           (lhs.getClosestPoint() == rhs.getClosestPoint()) &&

           (lhs.getBoundingBoxCenter() == rhs.getBoundingBoxCenter())
           && (lhs.getBoundingBoxWidth() == rhs.getBoundingBoxWidth())
           && (lhs.getBoundingBoxLength() == rhs.getBoundingBoxLength()) &&

           (lhs.getObjectBoxCenter() == rhs.getObjectBoxCenter())
           && (lhs.getObjectBoxSizeX() == rhs.getObjectBoxSizeX())
           && (lhs.getObjectBoxSizeY() == rhs.getObjectBoxSizeY())
           && (lhs.getObjectBoxOrientation() == rhs.getObjectBoxOrientation()) &&

           (lhs.getAbsoluteVelocity() == rhs.getAbsoluteVelocity())
           && (lhs.getAbsoluteVelocitySigmaX() == rhs.getAbsoluteVelocitySigmaX())
           && (lhs.getAbsoluteVelocitySigmaY() == rhs.getAbsoluteVelocitySigmaY()) &&

           (lhs.getRelativeVelocity() == rhs.getRelativeVelocity()) &&

           (lhs.getClassification() == rhs.getClassification())
           && (lhs.getClassificationAge() == rhs.getClassificationAge())
           && (lhs.getClassificationCertainty() == rhs.getClassificationCertainty()) &&

           (lhs.getNumberOfContourPoints() == rhs.getNumberOfContourPoints())
           && (lhs.isNumContourPointsValid() == rhs.isNumContourPointsValid())
           && (lhs.getContourPoints() == rhs.getContourPoints());
}

//==============================================================================

std::ostream& operator<<(std::ostream& os, const ObjectIn2221& luxObj)
{
    os << "LUX object - "
       << "id: " << luxObj.getObjectId() << " "
       << "age: " << luxObj.getObjectAge() << " "
       << "predictionAge: " << luxObj.getPredictionAge() << " "
       << "relativeTimestamp: " << luxObj.getRelativeTimestamp() << " "
       << "refPoint: " << luxObj.getReferencePoint() << " "
       << "refPointSigma: " << luxObj.getReferencePointSigma() << " "
       << "closestPoint: " << luxObj.getClosestPoint() << " "
       << "boundingBoxCenter: " << luxObj.getBoundingBoxCenter() << " "
       << "boundingBoxWidth: " << luxObj.getBoundingBoxWidth() << " "
       << "boundingBoxLength: " << luxObj.getBoundingBoxLength() << " "
       << "objectBoxCenter: " << luxObj.getObjectBoxCenter() << " "
       << "objectBoxLength: " << luxObj.getObjectBoxSizeX() << " "
       << "objectBoxWidth: " << luxObj.getObjectBoxSizeY() << " "
       << "objectBoxOrientation: " << luxObj.getObjectBoxOrientation() << " "
       << "absVelocity: " << luxObj.getAbsoluteVelocity() << " "
       << "absVelSigmaX: " << luxObj.getAbsoluteVelocitySigmaX() << " "
       << "absVelSigmaY: " << luxObj.getAbsoluteVelocitySigmaY() << " "
       << "relVelocity: " << luxObj.getRelativeVelocity() << " "
       << "class: " << static_cast<uint8_t>(luxObj.getClassification()) << " "
       << "classAge: " << luxObj.getClassificationAge() << " "
       << "classCertainty: " << luxObj.getClassificationCertainty() << " "
       << "numContourPointsIsValid: " << (luxObj.isNumContourPointsValid() ? "yes" : "no") << " "
       << "numContourPoints: " << luxObj.getNumberOfContourPoints() << std::endl;
    return os;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

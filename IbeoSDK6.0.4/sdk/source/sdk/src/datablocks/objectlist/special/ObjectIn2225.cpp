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

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2225.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/Math.hpp>

#include <cstring>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

ObjectIn2225::ObjectIn2225()
  : m_id(0),
    m_reserved(0),
    m_age(0),
    m_timestamp(0),
    m_hiddenStatusAge(0),
    m_class(),
    m_classCertainty(0),
    m_classAge(0),
    m_boundingBoxCenter(),
    m_boundingBoxSize(),
    m_objectBoxCenter(),
    m_objectBoxSigma(),
    m_objectBoxSize(),
    m_reserved2(0),
    m_objectBoxOrientation(0.),
    m_objectBoxOrientationSigma(0),
    m_relVelocity(),
    m_relVelocitySigma(),
    m_absVelocity(),
    m_absVelocitySigma(),
    // m_reserved4
    m_numContourPoints(0),
    m_indexOfClosedPoint(0),
    m_contourPoints(m_numContourPoints),
    m_orientation(0.f)
{
    m_contourPoints.reserve(16);
    std::memset(m_reserved3, 0, nbOfBytesInReserved3);
}

//==============================================================================

ObjectIn2225::ObjectIn2225(const ObjectIn2225& other)
  : m_id(other.m_id),
    m_reserved(other.m_reserved),
    m_age(other.m_age),
    m_timestamp(other.m_timestamp),
    m_hiddenStatusAge(other.m_hiddenStatusAge),
    m_class(other.m_class),
    m_classCertainty(other.m_classCertainty),
    m_classAge(other.m_classAge),
    m_boundingBoxCenter(other.m_boundingBoxCenter),
    m_boundingBoxSize(other.m_boundingBoxSize),
    m_objectBoxCenter(other.m_objectBoxCenter),
    m_objectBoxSigma(other.m_objectBoxSigma),
    m_objectBoxSize(other.m_objectBoxSize),
    m_reserved2(other.m_reserved2),
    m_objectBoxOrientation(other.m_objectBoxOrientation),
    m_objectBoxOrientationSigma(other.m_objectBoxOrientationSigma),
    m_relVelocity(other.m_relVelocity),
    m_relVelocitySigma(other.m_relVelocitySigma),
    m_absVelocity(other.m_absVelocity),
    m_absVelocitySigma(other.m_absVelocitySigma),
    // m_reserved3
    m_numContourPoints(other.m_numContourPoints),
    m_indexOfClosedPoint(other.m_indexOfClosedPoint),
    m_contourPoints(other.m_contourPoints),
    m_orientation(other.m_orientation)
{
    std::memcpy(m_reserved3, other.m_reserved3, nbOfBytesInReserved3);
}

//==============================================================================

std::streamsize ObjectIn2225::getSerializedSize() const { return 132 + 8 * m_numContourPoints; }

//==============================================================================

bool ObjectIn2225::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_id);
    ibeo::common::sdk::readBE(is, m_reserved);
    ibeo::common::sdk::readBE(is, m_age);
    ibeo::common::sdk::readBE(is, m_timestamp);
    ibeo::common::sdk::readBE(is, m_hiddenStatusAge);

    uint8_t c;
    ibeo::common::sdk::readBE(is, c);
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
    } // switch c

    ibeo::common::sdk::readBE(is, m_classCertainty);
    ibeo::common::sdk::readBE(is, m_classAge);
    ibeo::common::sdk::readBE(is, m_boundingBoxCenter);
    ibeo::common::sdk::readBE(is, m_boundingBoxSize);
    ibeo::common::sdk::readBE(is, m_objectBoxCenter);
    ibeo::common::sdk::readBE(is, m_objectBoxSigma);
    ibeo::common::sdk::readBE(is, m_objectBoxSize);
    ibeo::common::sdk::readBE(is, m_reserved2);
    ibeo::common::sdk::readBE(is, m_objectBoxOrientation);
    ibeo::common::sdk::readBE(is, m_objectBoxOrientationSigma);
    ibeo::common::sdk::readBE(is, m_relVelocity);
    ibeo::common::sdk::readBE(is, m_relVelocitySigma);
    ibeo::common::sdk::readBE(is, m_absVelocity);
    ibeo::common::sdk::readBE(is, m_absVelocitySigma);

    for (int i = 0; i < nbOfBytesInReserved3; ++i)
        ibeo::common::sdk::readBE(is, m_reserved3[i]); // 18 bytes reserved

    ibeo::common::sdk::readBE(is, m_numContourPoints);
    ibeo::common::sdk::readBE(is, m_indexOfClosedPoint);

    if (m_contourPoints.size() != m_numContourPoints)
        m_contourPoints.resize(m_numContourPoints);

    std::vector<Vector2<float>>::iterator cpIter = m_contourPoints.begin();
    for (; cpIter != m_contourPoints.end(); ++cpIter)
    {
        ibeo::common::sdk::readBE(is, *cpIter);
    }

    // derived data
    m_orientation = std::atan2(m_absVelocity.getY(), m_absVelocity.getX());

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ObjectIn2225::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_id);
    ibeo::common::sdk::writeBE(os, m_reserved); // 2 bytes reserved
    ibeo::common::sdk::writeBE(os, m_age);
    ibeo::common::sdk::writeBE(os, m_timestamp);
    ibeo::common::sdk::writeBE(os, m_hiddenStatusAge);

    const uint8_t c = static_cast<uint8_t>(m_class);
    ibeo::common::sdk::writeBE(os, c);

    ibeo::common::sdk::writeBE(os, m_classCertainty);
    ibeo::common::sdk::writeBE(os, m_classAge);
    ibeo::common::sdk::writeBE(os, m_boundingBoxCenter);
    ibeo::common::sdk::writeBE(os, m_boundingBoxSize);
    ibeo::common::sdk::writeBE(os, m_objectBoxCenter);
    ibeo::common::sdk::writeBE(os, m_objectBoxSigma);
    ibeo::common::sdk::writeBE(os, m_objectBoxSize);
    ibeo::common::sdk::writeBE(os, m_reserved2); // 8 bytes reserved
    ibeo::common::sdk::writeBE(os, m_objectBoxOrientation);
    ibeo::common::sdk::writeBE(os, m_objectBoxOrientationSigma); // 4 bytes reserved
    ibeo::common::sdk::writeBE(os, m_relVelocity);
    ibeo::common::sdk::writeBE(os, m_relVelocitySigma);
    ibeo::common::sdk::writeBE(os, m_absVelocity);
    ibeo::common::sdk::writeBE(os, m_absVelocitySigma);

    for (int i = 0; i < nbOfBytesInReserved3; ++i)
        ibeo::common::sdk::writeBE(os, m_reserved3[i]); // 18 bytes reserved

    ibeo::common::sdk::writeBE(os, m_numContourPoints);
    ibeo::common::sdk::writeBE(os, m_indexOfClosedPoint);

    std::vector<Vector2<float>>::const_iterator cpIter = m_contourPoints.begin();
    for (; cpIter != m_contourPoints.end(); ++cpIter)
    {
        ibeo::common::sdk::writeBE(os, *cpIter);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

std::ostream& operator<<(std::ostream& os, const ObjectIn2225& o)
{
    os.width(3);
    //	os.precision(10);
    os << o.getObjectId() << ": ";
    os << "Age: " << o.getObjectAge() << ", ";
    os << "TS: " << o.getTimestamp() << ", ";
    os << "HS: " << o.getHiddenStatusAge() << ", ";
    os << "CL: " << static_cast<uint8_t>(o.getClassification()) << "  ";
    os << "CC: " << int(o.getClassificationCertainty()) << ", ";
    os << "CA: " << o.getClassificationAge() << ", ";
    os << "BBC: " << o.getBoundingBoxCenter() << ", ";
    os << "BBS: " << o.getBoundingBoxSize() << ", ";
    os << "OBC: " << o.getObjectBoxCenter() << ", ";
    os << "OBCs: " << o.getObjectBoxSigma() << ", ";
    os << "OBS: " << o.getObjectBoxSize() << ", ";
    os << "Yaw: " << o.getObjectBoxOrientation() << ", ";
    os << "RV: " << o.getRelativeVelocity() << ", ";
    os << "RVs: " << o.getRelativeVelocitySigma() << ", ";
    os << "AV: " << o.getAbsoluteVelocity() << ", ";
    os << "AVs: " << o.getAbsoluteVelocitySigma() << ", ";
    os << "#CP:" << int(o.getNumberOfContourPoints()) << ", ";
    os << "iCP:" << int(o.getIndexOfClosestPoint()) << ", ";
    os << "ori:" << o.getOrientation() << ", ";

    return os;
}

//==============================================================================

bool ObjectIn2225::operator==(const ObjectIn2225& other) const
{
    if (m_id != other.getObjectId())
        return false;

    if (m_reserved != other.getReserved())
        return false;

    if (m_age != other.getObjectAge())
        return false;

    if (m_timestamp != other.getTimestamp())
        return false;

    if (m_hiddenStatusAge != other.getHiddenStatusAge())
        return false;

    if (m_class != other.getClassification())
        return false;

    if (m_classCertainty != other.getClassificationCertainty())
        return false;

    if (m_classAge != other.getClassificationAge())
        return false;

    if (m_boundingBoxCenter != other.getBoundingBoxCenter())
        return false;

    if (m_boundingBoxSize != other.getBoundingBoxSize())
        return false;

    if (m_objectBoxCenter != other.getObjectBoxCenter())
        return false;

    if (m_objectBoxSigma != other.getObjectBoxSigma())
        return false;

    if (m_objectBoxSize != other.getObjectBoxSize())
        return false;

    if (m_reserved2 != other.getReserved2())
        return false;

    if (!(fuzzyCompareT<7>(m_objectBoxOrientation, other.getObjectBoxOrientation())))
        return false;

    if (!(fuzzyCompareT<7>(m_objectBoxOrientationSigma, other.getObjectBoxOrientationSigma())))
        return false;

    if (m_relVelocity != other.getRelativeVelocity())
        return false;

    if (m_relVelocitySigma != other.getRelativeVelocitySigma())
        return false;

    if (m_absVelocity != other.getAbsoluteVelocity())
        return false;

    if (m_absVelocitySigma != other.getAbsoluteVelocitySigma())
        return false;

    if (getNumberOfContourPoints() != other.getNumberOfContourPoints())
        return false;

    if (m_indexOfClosedPoint != other.getIndexOfClosestPoint())
        return false;

    for (size_t idx = 0; idx < m_contourPoints.size(); ++idx)
    {
        if (m_contourPoints[idx] != other.getContourPoints()[idx])
            return false;
    }

    return true;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

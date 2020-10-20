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
//!\date Mar 15, 2016
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/pointcloud/PointBase.hpp>

#include <ibeo/common/sdk/RotationMatrix3d.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/Math.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

void PointBase::transformToGlobalCoordinatesP3d(const ReferencePlane& refPlane,
                                                const Vector3<float>& offset,
                                                GpsPoint& globalPoint)
{
    const Vector3<float> transformedOffset = refPlane.getRotationMatrix() * offset;

    double lon, lat;
    PositionWgs84::transformFromTangentialPlane2d(refPlane.getGpsPoint().getLatitudeInRad(),
                                                  refPlane.getGpsPoint().getLongitudeInRad(),
                                                  static_cast<double>(transformedOffset.getX()),
                                                  static_cast<double>(transformedOffset.getY()),
                                                  lat,
                                                  lon);

    globalPoint.setAltitude(refPlane.getGpsPoint().getAltitude());
    globalPoint.setLatitudeInRad(lat);
    globalPoint.setLongitudeInRad(lon);
}

//==============================================================================

void PointBase::transformToGlobalCoordinatesF3d(const ReferencePlane& refPlane,
                                                const Vector3<float>& offset,
                                                GpsPoint& globalPoint)
{
    const Vector3<float> transformedOffset = refPlane.getRotationMatrix() * offset;

    double lon, lat, altitude;
    PositionWgs84::transformFromTangentialPlane3d(refPlane.getGpsPoint().getLatitudeInRad(),
                                                  refPlane.getGpsPoint().getLongitudeInRad(),
                                                  static_cast<double>(refPlane.getGpsPoint().getAltitude()),
                                                  static_cast<double>(transformedOffset.getX()),
                                                  static_cast<double>(transformedOffset.getY()),
                                                  static_cast<double>(transformedOffset.getZ()),
                                                  lat,
                                                  lon,
                                                  altitude);

    globalPoint.setAltitude(float(altitude));
    globalPoint.setLatitudeInRad(lat);
    globalPoint.setLongitudeInRad(lon);
}

//==============================================================================

void PointBase::transformToRelativeCoordinatesP3d(const ReferencePlane& origin,
                                                  const GpsPoint& globalPoint,
                                                  Vector3<float>& offset)
{
    double x, y;

    PositionWgs84::transformToTangentialPlane2d(origin.getGpsPoint().getLatitudeInRad(),
                                                origin.getGpsPoint().getLongitudeInRad(),
                                                globalPoint.getLatitudeInRad(),
                                                globalPoint.getLongitudeInRad(),
                                                x,
                                                y);

    const Vector3<float> p(float(x),
                           float(y),
                           std::isnan(globalPoint.getAltitude()) ? origin.getGpsPoint().getAltitude()
                                                                 : globalPoint.getAltitude());
    offset = origin.getRotationMatrix().getInverse() * p;
}

//==============================================================================

void PointBase::transformToRelativeCoordinatesF3d(const ReferencePlane& origin,
                                                  const GpsPoint& globalPoint,
                                                  Vector3<float>& offset)
{
    double x, y, z;

    PositionWgs84::transformToTangentialPlane3d(origin.getGpsPoint().getLatitudeInRad(),
                                                origin.getGpsPoint().getLongitudeInRad(),
                                                static_cast<double>(origin.getGpsPoint().getAltitude()),
                                                globalPoint.getLatitudeInRad(),
                                                globalPoint.getLongitudeInRad(),
                                                static_cast<double>(globalPoint.getAltitude()),
                                                x,
                                                y,
                                                z);

    //const Vector3<float> p(float(x), float(y), float(z));
    offset = origin.getRotationMatrix().getInverse() * Vector3<float>(float(x), float(y), float(z));
}

//==============================================================================

void PointBase::transformToRelativeCoordinatesP3d(const ReferencePlane& originRefPlane,
                                                  const EcefPoint& originRefPointsEcef,
                                                  const RotationMatrix3d<float>& invTargetRotMatrix,
                                                  const GpsPoint& globalPoint,
                                                  Vector3<float>& offset)
{
    double x, y;

    PositionWgs84::transformToTangentialPlane2d(
        originRefPointsEcef, globalPoint.getLatitudeInRad(), globalPoint.getLongitudeInRad(), x, y);

    const Vector3<float> p(static_cast<float>(x),
                           static_cast<float>(y),
                           std::isnan(globalPoint.getAltitude()) ? originRefPlane.getGpsPoint().getAltitude()
                                                                 : globalPoint.getAltitude());
    offset = invTargetRotMatrix * p;
}

//==============================================================================

void PointBase::transformToRelativeCoordinatesF3d(const EcefPoint& originRefPointsEcef,
                                                  const RotationMatrix3d<float>& invTargetRotMatrix,
                                                  const GpsPoint& globalPoint,
                                                  Vector3<float>& offset)
{
    double x, y, z;

    PositionWgs84::transformToTangentialPlaneF3d(originRefPointsEcef,
                                                 globalPoint.getLatitudeInRad(),
                                                 globalPoint.getLongitudeInRad(),
                                                 static_cast<double>(globalPoint.getAltitude()),
                                                 x,
                                                 y,
                                                 z);

    //Vector3<float> p(float(x), float(y), float(z)); konfuses the compiler
    // it is thinging of it as a function prototype.

    offset = invTargetRotMatrix * Vector3<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

//==============================================================================

void PointBase::transformToShiftedReferencePlaneP3d(const ReferencePlane& originRefPlane,
                                                    const ReferencePlane& targetRefPlane,
                                                    const Vector3<float>& originOffset,
                                                    Vector3<float>& targetOffset)
{
    GpsPoint globalPoint;
    transformToGlobalCoordinatesP3d(originRefPlane, originOffset, globalPoint);
    transformToRelativeCoordinatesP3d(targetRefPlane, globalPoint, targetOffset);
}

//==============================================================================

void PointBase::transformToShiftedReferencePlaneP3d(const ReferencePlane& originRefPlane,
                                                    const ReferencePlane& targetRefPlane,
                                                    const EcefPoint& targetRefPointsEcef,
                                                    const RotationMatrix3d<float>& invTargetRotMatrix,
                                                    const Vector3<float>& originOffset,
                                                    Vector3<float>& targetOffset)
{
    GpsPoint originsGps;
    transformToGlobalCoordinatesP3d(originRefPlane, originOffset, originsGps);
    transformToRelativeCoordinatesP3d(
        targetRefPlane, targetRefPointsEcef, invTargetRotMatrix, originsGps, targetOffset);
}

//==============================================================================

void PointBase::transformToShiftedReferencePlaneF3d(const ReferencePlane& originRefPlane,
                                                    const EcefPoint& targetRefPointsEcef,
                                                    const RotationMatrix3d<float>& invTargetRotMatrix,
                                                    const Vector3<float>& originOffset,
                                                    Vector3<float>& targetOffset)
{
    GpsPoint originsGps;
    transformToGlobalCoordinatesF3d(originRefPlane, originOffset, originsGps);
    transformToRelativeCoordinatesF3d(targetRefPointsEcef, invTargetRotMatrix, originsGps, targetOffset);
}

//==============================================================================

std::streamsize PointBase::getSerializedSizeWithType_static(const PointType& type)
{
    uint32_t size = 0;

    switch (type)
    {
    case PointType::PointWithEpw:
        size += 4;
        break;
    case PointType::PointWithFlags:
        size += 4;
        break;
    case PointType::PointWithEpwAndFlags:
        size += 8;
        break;
    case PointType::PointWithEpwFlagsAndColor:
        size += 11;
        break;
    default:
        break;
    } // switch

    return std::streamsize(size);
}

//==============================================================================

std::streamsize PointBase::getSerializedSizeWithType(const PointType& type) const
{
    return getSerializedSizeWithType_static(type);
}

//==============================================================================

bool PointBase::deserializeWithType(std::istream& is, const PointType& type)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    switch (type)
    {
    case PointType::PointWithEpw:
        ibeo::common::sdk::readBE(is, m_epw);
        break;
    case PointType::PointWithFlags:
        ibeo::common::sdk::readBE(is, m_flags);
        break;
    case PointType::PointWithEpwAndFlags:
        ibeo::common::sdk::readBE(is, m_epw);
        ibeo::common::sdk::readBE(is, m_flags);
        break;
    case PointType::PointWithEpwFlagsAndColor:
        ibeo::common::sdk::readBE(is, m_epw);
        ibeo::common::sdk::readBE(is, m_flags);
        ibeo::common::sdk::readBE(is, m_rgb[0]);
        ibeo::common::sdk::readBE(is, m_rgb[1]);
        ibeo::common::sdk::readBE(is, m_rgb[2]);
        break;
    default:
        break;
    } // switch

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSizeWithType(type));
}

//==============================================================================

bool PointBase::serializeWithType(std::ostream& os, const PointType& type) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    switch (type)
    {
    case PointType::PointWithEpw:
        ibeo::common::sdk::writeBE(os, m_epw);
        break;
    case PointType::PointWithFlags:
        ibeo::common::sdk::writeBE(os, uint32_t(m_flags));
        break;
    case PointType::PointWithEpwAndFlags:
        ibeo::common::sdk::writeBE(os, m_epw);
        ibeo::common::sdk::writeBE(os, uint32_t(m_flags));
        break;
    case PointType::PointWithEpwFlagsAndColor:
        ibeo::common::sdk::writeBE(os, m_epw);
        ibeo::common::sdk::writeBE(os, uint32_t(m_flags));
        ibeo::common::sdk::writeBE(os, m_rgb[0]);
        ibeo::common::sdk::writeBE(os, m_rgb[1]);
        ibeo::common::sdk::writeBE(os, m_rgb[2]);
        break;
    default:
        break;
    } // switch

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSizeWithType(type));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

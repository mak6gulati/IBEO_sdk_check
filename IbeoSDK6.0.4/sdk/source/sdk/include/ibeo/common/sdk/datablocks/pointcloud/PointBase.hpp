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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/GpsPoint.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/ReferencePlane.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/PointCloudBase.hpp>
#include <ibeo/common/sdk/Matrix3x3.hpp>

#include <ibeo/common/sdk/misc/deprecatedwarning.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class PointBase
{
public:
    PointBase() : m_epw(.0f), m_flags(0) {}
    virtual ~PointBase() {}

public:
    static std::streamsize getSerializedSizeWithType_static(const PointType& type);

public:
    static void transformToGlobalCoordinatesP3d(const ReferencePlane& refPlane,
                                                const Vector3<float>& offset,
                                                GpsPoint& globalPoint);

    static void transformToGlobalCoordinatesF3d(const ReferencePlane& refPlane,
                                                const Vector3<float>& offset,
                                                GpsPoint& globalPoint);

public:
    static void transformToRelativeCoordinatesP3d(const ReferencePlane& origin,
                                                  const GpsPoint& globalPoint,
                                                  Vector3<float>& offset);

    static void transformToRelativeCoordinatesF3d(const ReferencePlane& origin,
                                                  const GpsPoint& globalPoint,
                                                  Vector3<float>& offset);

public:
    static void transformToRelativeCoordinatesP3d(const ReferencePlane& originRefPlane,
                                                  const EcefPoint& originRefPointsEcef,
                                                  const RotationMatrix3d<float>& invTargetRotMatrix,
                                                  const GpsPoint& globalPoint,
                                                  Vector3<float>& offset);

    static void transformToRelativeCoordinatesF3d(const EcefPoint& originRefPointsEcef,
                                                  const RotationMatrix3d<float>& invTargetRotMatrix,
                                                  const GpsPoint& globalPoint,
                                                  Vector3<float>& offset);

public:
    //========================================
    //!\brief Coordinate transformation of a given point
    //!       in the \a originRefPlane (\a originOffset)
    //!       into the \a targetRefPlane.
    //!\param[in]  originRefPlane  The origin reference plane.
    //!\param[in]  targetRefPlane  The target reference plane.
    //!\param[in]  originOffset    The point's xyz coordinates in
    //!                            the origin reference plane.
    //!\param[out] targetOffset    On exit the point's xyz coordinates in
    //!                            the target reference plane.
    //----------------------------------------
    static void transformToShiftedReferencePlaneP3d(const ReferencePlane& originRefPlane,
                                                    const ReferencePlane& targetRefPlane,
                                                    const Vector3<float>& originOffset,
                                                    Vector3<float>& targetOffset);

public:
    //========================================
    //!\brief Coordinate transformation of a given point
    //!       in the \a originRefPlane (\a originOffset)
    //!       into the \a targetRefPlane.
    //!
    //! Use this method if you want to transform more than one point into
    //! the same target reference plane. Calculate \a targetRefPointsEcef
    //! using PositionWgs84::llaToEcef. This will avoid duplicate calculation
    //! other than using
    //! transformToShiftedReferencePlane(const ReferencePlane&, const ReferencePlane&, const Vector3<float>&, Vector3<float>&)
    //!
    //! \param[in]  originRefPlane       The origin reference plane.
    //! \param[in]  targetRefPlane       The target reference plane.
    //! \param[in]  targetRefPointsEcef  The ECEF coordinates and sine and cosine
    //!                                  of the latitude and longitude of the target
    //!                                  plane reference point.
    //! \param[in]  invTargetRotMatrix   Inverse rotation between global coordinates
    //!                                  and relative coordinates in the target plane.
    //! \param[in]  originOffset         The point's xyz coordinates in
    //!                                  the origin reference plane.
    //! \param[out] targetOffset         On exit the point's xyz coordinates in
    //!                                  the target reference plane.
    //! \note \a P3d stand for partial 3D, altitude will taken from the point
    //!       given by originOffset in originRefPlane. If this is not set,
    //!       the altitude of the originRefPlane GPS anchor point will be used.
    //----------------------------------------
    static void transformToShiftedReferencePlaneP3d(const ReferencePlane& originRefPlane,
                                                    const ReferencePlane& targetRefPlane,
                                                    const EcefPoint& targetRefPointsEcef,
                                                    const RotationMatrix3d<float>& invTargetRotMatrix,
                                                    const Vector3<float>& originOffset,
                                                    Vector3<float>& targetOffset);

    //========================================
    //!\brief Coordinate transformation of a given point
    //!       in the \a originRefPlane (\a originOffset)
    //!       into the \a targetRefPlane.
    //!
    //! Use this method if you want to transform more than one point into
    //! the same target reference plane. Calculate \a targetRefPointsEcef
    //! using PositionWgs84::llaToEcef. This will avoid duplicate calculation
    //! other than using
    //! transformToShiftedReferencePlane(const ReferencePlane&, const ReferencePlane&, const Vector3<float>&, Vector3<float>&)
    //!
    //! \param[in]  originRefPlane       The origin reference plane.
    //! \param[in]  targetRefPointsEcef  The ECEF coordinates and sine and cosine
    //!                                  of the latitude and longitude of the target
    //!                                  plane reference point.
    //! \param[in]  invTargetRotMatrix   Inverse rotation between global coordinates
    //!                                  and relative coordinates in the target plane.
    //! \param[in]  originOffset         The point's xyz coordinates in
    //!                                  the origin reference plane.
    //! \param[out] targetOffset         On exit the point's xyz coordinates in
    //!                                  the target reference plane.
    //! \note \a F3d stand for full 3D. The altitude will be calculated.
    //----------------------------------------
    static void transformToShiftedReferencePlaneF3d(const ReferencePlane& originRefPlane,
                                                    const EcefPoint& targetRefPointsEcef,
                                                    const RotationMatrix3d<float>& invTargetRotMatrix,
                                                    const Vector3<float>& originOffset,
                                                    Vector3<float>& targetOffset);

public:
    virtual std::streamsize getSerializedSizeWithType(const PointType& type) const;
    virtual bool deserializeWithType(std::istream& is, const PointType& type);
    virtual bool serializeWithType(std::ostream& os, const PointType& type) const;

public:
    virtual float getEpw() const { return m_epw; }
    virtual void setEpw(const float epw) { m_epw = epw; }

    virtual uint32_t getFlags() const { return m_flags; }
    virtual void setFlags(const uint32_t flags) { m_flags = flags; }

    virtual std::array<uint8_t, 3> getColor() const { return m_rgb; }
    virtual void setColor(const std::array<uint8_t, 3>& rgb) { m_rgb = rgb; }

private:
    float m_epw;
    uint32_t m_flags;
    std::array<uint8_t, 3> m_rgb;
}; // PointBase

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

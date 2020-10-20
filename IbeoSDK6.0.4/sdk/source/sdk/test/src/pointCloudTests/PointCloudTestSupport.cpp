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
//!\date Mar 26, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <pointCloudTests/PointCloudTestSupport.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

void PointCloudTestSupport::fillRandomly(ReferencePlane& rp)
{
    GpsPoint gps;
    fillRandomly(gps);
    rp.setGpsPoint(gps);

    rp.setYaw(getNonNanRandValue<float>());
    rp.setPitch(getNonNanRandValue<float>());
    rp.setRoll(getNonNanRandValue<float>());
}

//==============================================================================

void PointCloudTestSupport::fillRandomly(GpsPoint& gps)
{
    gps.setLongitudeInRad(getNonNanRandValue<double>());
    gps.setLatitudeInRad(getNonNanRandValue<double>());
    gps.setAltitude(getNonNanRandValue<float>());
}

//==============================================================================

void PointCloudTestSupport::fillRandomly(PointCloud7500& pc)
{
    pc.setKind(PointKind(getRandValue<uint16_t>()));
    pc.setType(PointType(getRandValue<uint16_t>()));

    ReferencePlane rp;
    fillRandomly(rp);
    pc.setReferencePlane(rp);

    const uint16_t nbOfPoints{getRandValue<uint16_t>()};
    PointCloud7500::PointVector points;
    points.resize(nbOfPoints);
    for (PointCloudPointIn7500& point : points)
    {
        fillRandomly(point);
    }
}

//==============================================================================

void PointCloudTestSupport::fillRandomly(PointCloudPointIn7500& pt)
{
    GpsPoint gps;
    fillRandomly(gps);
    pt.setGpsPoint(gps);
}

//==============================================================================

void PointCloudTestSupport::fillRandomly(PointCloud7510& pc)
{
    pc.setKind(PointKind(getRandValue<uint16_t>()));
    pc.setType(PointType(getRandValue<uint16_t>()));

    ReferencePlane rp;
    fillRandomly(rp);
    pc.setReferencePlane(rp);

    const uint16_t nbOfPoints{getRandValue<uint16_t>()};
    PointCloud7510::PointVector points;
    points.resize(nbOfPoints);
    for (PointCloudPointIn7510& point : points)
    {
        fillRandomly(point);
    }
}

//==============================================================================

void PointCloudTestSupport::fillRandomly(PointCloudPointIn7510& pt)
{
    pt.setPoint3D(getNonNanRandValue<Vector3<float>>());
}

//==============================================================================

void PointCloudTestSupport::fillRandomly(PointCloud& pc)
{
    pc.setKind(PointKind(getRandValue<uint16_t>()));
    pc.setType(PointType(getRandValue<uint16_t>()));

    ReferencePlane rp;
    fillRandomly(rp);
    pc.setReferencePlane(rp);

    const uint16_t nbOfPoints{getRandValue<uint16_t>()};
    PointCloud::PointVector points;
    points.resize(nbOfPoints);
    for (PointCloudPoint& point : points)
    {
        fillRandomly(point);
    }
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

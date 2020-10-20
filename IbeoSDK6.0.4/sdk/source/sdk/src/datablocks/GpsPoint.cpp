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
//! \date Mar 14, 2016
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/GpsPoint.hpp>

#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

GpsPoint::GpsPoint() : m_latitude(.0), m_longitude(.0), m_altitude(.0F) {}

//==============================================================================

GpsPoint::GpsPoint(const double& lonInDeg, const double& latInDeg, const float altitude)
  : m_latitude(latInDeg), m_longitude(lonInDeg), m_altitude(altitude)
{}

//==============================================================================

GpsPoint::GpsPoint(const PositionWgs84& wgs84Point)
  : m_latitude(wgs84Point.getLatitudeInDeg()),
    m_longitude(wgs84Point.getLongitudeInDeg()),
    m_altitude(float(wgs84Point.getAltitudeInMeterMSL()))
{}

//==============================================================================

std::streamsize GpsPoint::getSerializedSize_static() { return std::streamsize(2 * sizeof(double) + sizeof(float)); }

//==============================================================================

std::streamsize GpsPoint::getSerializedSize() const { return getSerializedSize_static(); }

//==============================================================================

bool GpsPoint::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_longitude);
    ibeo::common::sdk::readBE(is, m_latitude);
    ibeo::common::sdk::readBE(is, m_altitude);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool GpsPoint::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_longitude);
    ibeo::common::sdk::writeBE(os, m_latitude);
    ibeo::common::sdk::writeBE(os, m_altitude);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool GpsPoint::operator==(const GpsPoint& other) const
{
    return (m_altitude == other.m_altitude) && (m_latitude == other.m_latitude) && (m_longitude == other.m_longitude);
}

//==============================================================================

bool GpsPoint::operator!=(const GpsPoint& other) const { return !(*this == other); }

//==============================================================================

PositionWgs84 GpsPoint::getAsPositionWGS84(const float courseAngle) const
{
    PositionWgs84 ret;
    ret.setAltitudeInMeterMSL(static_cast<double>(m_altitude));
    ret.setLongitudeInDeg(m_longitude);
    ret.setLatitudeInDeg(m_latitude);
    ret.setCourseAngleInRad(static_cast<double>(courseAngle));

    return ret;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

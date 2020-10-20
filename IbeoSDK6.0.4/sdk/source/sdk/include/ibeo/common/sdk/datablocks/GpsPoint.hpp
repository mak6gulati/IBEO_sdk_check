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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/PositionWgs84.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//! \class GpsPoint
//! \brief A single point with GPS coordinates (WGS84).
//! \date Mar 14, 2016
//------------------------------------------------------------------------------
class GpsPoint
{
public:
    static std::streamsize getSerializedSize_static();

public:
    GpsPoint();
    GpsPoint(const PositionWgs84& wgs84Point);
    GpsPoint(const double& lonInDeg, const double& latInDeg, const float altitude);

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    bool operator==(const GpsPoint& other) const;
    bool operator!=(const GpsPoint& other) const;

public: // getter
    double getLongitudeInDeg() const { return m_longitude; }
    double getLatitudeInDeg() const { return m_latitude; }

    double getLongitudeInRad() const { return deg2rad * m_longitude; }
    double getLatitudeInRad() const { return deg2rad * m_latitude; }

    float getAltitude() const { return m_altitude; }

public: // setter
    void setLongitudeInDeg(const double lon) { m_longitude = lon; }
    void setLatitudeInDeg(const double lat) { m_latitude = lat; }

    void setLongitudeInRad(const double lon) { m_longitude = rad2deg * lon; }
    void setLatitudeInRad(const double lat) { m_latitude = rad2deg * lat; }

    void setAltitude(const float alt) { m_altitude = alt; }

    PositionWgs84 getAsPositionWGS84(const float courseAngle = .0f) const;

private:
    // WGS84 coordinates
    double m_latitude;
    double m_longitude;
    float m_altitude;
}; // GpsPoint

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

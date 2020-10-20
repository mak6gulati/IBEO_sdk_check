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
//! \date Mar 17, 2016
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/EcefPoint.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

EcefPoint::EcefPoint()
  : m_xyz(0.0, 0.0, 0.0),
    m_latSin(std::sin(0.0)),
    m_latCos(std::cos(0.0)),
    m_lonSin(std::sin(0.0)),
    m_lonCos(std::cos(0.0))
{}

//==============================================================================

EcefPoint::EcefPoint(const double x, const double y, const double z, const double latRad, const double lonRad)
  : m_xyz(x, y, z),
    m_latSin(std::sin(latRad)),
    m_latCos(std::cos(latRad)),
    m_lonSin(std::sin(lonRad)),
    m_lonCos(std::cos(lonRad))
{}

//==============================================================================

EcefPoint::EcefPoint(const Vector3<double>& xyz, const double latRad, const double lonRad)
  : m_xyz(xyz),
    m_latSin(std::sin(latRad)),
    m_latCos(std::cos(latRad)),
    m_lonSin(std::sin(lonRad)),
    m_lonCos(std::cos(lonRad))
{}

//==============================================================================

EcefPoint::EcefPoint(const Vector3<double>& xyz,
                     const double latSin,
                     const double latCos,
                     const double lonSin,
                     const double lonCos)
  : m_xyz(xyz), m_latSin(latSin), m_latCos(latCos), m_lonSin(lonSin), m_lonCos(lonCos)
{}

//==============================================================================

EcefPoint::EcefPoint(const double x,
                     const double y,
                     const double z,
                     const double latSin,
                     const double latCos,
                     const double lonSin,
                     const double lonCos)
  : m_xyz(x, y, z), m_latSin(latSin), m_latCos(latCos), m_lonSin(lonSin), m_lonCos(lonCos)
{}

//==============================================================================

void EcefPoint::set(const double x, const double y, const double z, const double latRad, const double lonRad)
{
    m_xyz    = Vector3<double>{x, y, z};
    m_latSin = std::sin(latRad);
    m_latCos = std::cos(latRad);
    m_lonSin = std::sin(lonRad);
    m_lonCos = std::cos(lonRad);
}

//==============================================================================

void EcefPoint::set(const Vector3<double>& xyz, const double latRad, const double lonRad)
{
    m_xyz    = xyz;
    m_latSin = std::sin(latRad);
    m_latCos = std::cos(latRad);
    m_lonSin = std::sin(lonRad);
    m_lonCos = std::cos(lonRad);
}

//==============================================================================

void EcefPoint::set(const Vector3<double>& xyz,
                    const double latSin,
                    const double latCos,
                    const double lonSin,
                    const double lonCos)
{
    m_xyz    = xyz;
    m_latSin = latSin;
    m_latCos = latCos;
    m_lonSin = lonSin;
    m_lonCos = lonCos;
}

//==============================================================================

void EcefPoint::set(const double x,
                    const double y,
                    const double z,
                    const double latSin,
                    const double latCos,
                    const double lonSin,
                    const double lonCos)
{
    m_xyz    = Vector3<double>{x, y, z};
    m_latSin = latSin;
    m_latCos = latCos;
    m_lonSin = lonSin;
    m_lonCos = lonCos;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

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
#include <ibeo/common/sdk/datablocks/vehiclestate/VehicleState2808.hpp>
#include <ibeo/common/sdk/RotationMatrix3d.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class ReferencePlane
{
public:
    ReferencePlane()
      : m_gpsPoint(), m_yaw(0.f), m_pitch(0.f), m_roll(0.f), m_rotationMatrixIsValid(false), m_rotationMatrix()
    {}

    ReferencePlane(const GpsPoint& point, const float yaw = 0.f, const float pitch = 0.f, const float roll = 0.f)
      : m_gpsPoint(point), m_yaw(yaw), m_pitch(pitch), m_roll(roll), m_rotationMatrixIsValid(false), m_rotationMatrix()
    {}

    ReferencePlane(const VehicleState2808& vsb);

public:
    bool operator==(const ReferencePlane& other) const;
    bool operator!=(const ReferencePlane& other) const;

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    GpsPoint& gpsPoint() { return m_gpsPoint; }
    const GpsPoint& getGpsPoint() const { return m_gpsPoint; }
    void setGpsPoint(const GpsPoint& point) { m_gpsPoint = point; }

    float getYaw() const { return m_yaw; }
    void setYaw(const float yaw)
    {
        m_rotationMatrixIsValid = false;
        m_yaw                   = yaw;
    }

    float getPitch() const { return m_pitch; }
    void setPitch(const float pitch)
    {
        m_rotationMatrixIsValid = false;
        m_pitch                 = pitch;
    }

    float getRoll() const { return m_roll; }
    void setRoll(const float roll)
    {
        m_rotationMatrixIsValid = false;
        m_roll                  = roll;
    }

    const RotationMatrix3d<float>& getRotationMatrix() const
    {
        if (!m_rotationMatrixIsValid)
        {
            m_rotationMatrix.setToIdentity();
            m_rotationMatrix.rotateZ(m_yaw);
            m_rotationMatrix.rotateY(m_pitch);
            m_rotationMatrix.rotateX(m_roll);
        }
        return m_rotationMatrix;
    }

    //========================================
private:
    GpsPoint m_gpsPoint;

    float m_yaw;
    float m_pitch;
    float m_roll;

private: // rotation matrix cache
    bool m_rotationMatrixIsValid;
    mutable RotationMatrix3d<float> m_rotationMatrix;
}; // ReferencePlane

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

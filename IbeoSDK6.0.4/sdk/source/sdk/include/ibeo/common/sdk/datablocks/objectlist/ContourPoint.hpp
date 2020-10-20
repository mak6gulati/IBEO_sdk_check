//==============================================================================
//!\file
//!
//!\brief Contour point (in SI units)
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Apr 16, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Vector2.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class ContourPoint
{
public:
    ContourPoint() = default;
    ContourPoint(const Vector2<float> pt);
    virtual ~ContourPoint() = default;

public:
    Vector2<float> getCoordinates() const { return Vector2<float>(m_x, m_y); }
    Vector2<float> getCoordinatesSigma() const { return Vector2<float>(m_xSigma, m_ySigma); }
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    float getXSigma() const { return m_xSigma; }
    float getYSigma() const { return m_ySigma; }
    float getCorrCoeff() const { return m_corrCoeff; }
    float getExistenceProbability() const { return m_existenceProbability; }

public:
    void setCoordinates(const Vector2<float>& coords)
    {
        m_x = coords.getX();
        m_y = coords.getY();
    }
    void setCoordinatesSigma(const Vector2<float>& coordsSigma)
    {
        m_xSigma = coordsSigma.getX();
        m_ySigma = coordsSigma.getY();
    }
    void setX(const float newX) { m_x = newX; }
    void setY(const float newY) { m_y = newY; }
    void setXSigma(const float newXSigma) { m_xSigma = newXSigma; }
    void setYSigma(const float newYSigma) { m_ySigma = newYSigma; }
    void setCorrCoeff(const float newCorrCoeff) { m_corrCoeff = newCorrCoeff; }
    void setExistenceProbability(const float newExistenceProbability)
    {
        m_existenceProbability = newExistenceProbability;
    }

protected:
    float m_x{NaN};
    float m_y{NaN};
    float m_xSigma{NaN};
    float m_ySigma{NaN};
    float m_corrCoeff{NaN};
    float m_existenceProbability{NaN};
}; // ContourPoint

//==============================================================================
//==============================================================================
//==============================================================================

bool operator==(const ContourPoint& lhs, const ContourPoint& rhs);
bool operator!=(const ContourPoint& lhs, const ContourPoint& rhs);

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

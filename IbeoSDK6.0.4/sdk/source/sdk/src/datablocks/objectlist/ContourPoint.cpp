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
//!\date Apr 13, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/objectlist/ContourPoint.hpp>
#include <ibeo/common/sdk/io.hpp>

#include <iostream>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ContourPoint::ContourPoint(const Vector2<float> pt) : m_x(pt.getX()), m_y(pt.getY()) {}

//==============================================================================
//==============================================================================
//==============================================================================

bool operator==(const ContourPoint& lhs, const ContourPoint& rhs)
{
    return (floatEqual(lhs.getX(), rhs.getX())) && (floatEqual(lhs.getY(), rhs.getY()))
           && (floatEqual(lhs.getXSigma(), rhs.getXSigma())) && (floatEqual(lhs.getYSigma(), rhs.getYSigma()))
           && (floatEqual(lhs.getCorrCoeff(), rhs.getCorrCoeff()))
           && (floatEqual(lhs.getExistenceProbability(), rhs.getExistenceProbability()));
}

//==============================================================================

bool operator!=(const ContourPoint& lhs, const ContourPoint& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

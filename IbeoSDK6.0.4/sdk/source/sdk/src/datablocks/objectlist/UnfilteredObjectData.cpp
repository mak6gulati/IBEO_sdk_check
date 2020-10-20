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

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectlist/UnfilteredObjectData.hpp>

#include <ibeo/common/sdk/ObjectBasic.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

bool operator==(const UnfilteredObjectData& lhs, const UnfilteredObjectData& rhs)
{
    return (lhs.getPriority() == rhs.getPriority()) && (lhs.getTimestamp() == rhs.getTimestamp())
           && (lhs.getPositionClosestObjectPoint() == rhs.getPositionClosestObjectPoint())
           && (lhs.getObjectBoxSize() == rhs.getObjectBoxSize())
           && (lhs.getObjectBoxSizeSigma() == rhs.getObjectBoxSizeSigma())
           && (lhs.getObjectBoxHeight() == rhs.getObjectBoxHeight()) && (lhs.getCourseAngle() == rhs.getCourseAngle())
           && (lhs.getCourseAngleSigma() == rhs.getCourseAngleSigma())
           && (lhs.getReferencePointLocation() == rhs.getReferencePointLocation())
           && (lhs.getReferencePointCoord() == rhs.getReferencePointCoord())
           && (lhs.getReferencePointCoordSigma() == rhs.getReferencePointCoordSigma())
           && (lhs.getReferencePointCoordCorrCoeff() == rhs.getReferencePointCoordCorrCoeff())
           && (lhs.getExistenceProbability() == rhs.getExistenceProbability())
           && (lhs.getContourPoints() == rhs.getContourPoints());
}

//==============================================================================

bool operator!=(const UnfilteredObjectData& lhs, const UnfilteredObjectData& rhs) { return !(lhs == rhs); }

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

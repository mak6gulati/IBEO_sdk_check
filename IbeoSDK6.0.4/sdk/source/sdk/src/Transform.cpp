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
//! \date Jan 01, 2016
//! \brief Transformation helper class
//------------------------------------------------------------------------------

//==============================================================================

#include "ibeo/common/sdk/Transform.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

TransformationMatrix2d<float> Transform::transformToGlobal(const TransformationMatrix2d<float>& ref2Global,
                                                           const TransformationMatrix2d<float>& rel2ref)
{
    return ref2Global * rel2ref;
}

//==============================================================================

TransformationMatrix2d<float> Transform::getTransformationSystem(const VehicleState2808& vs)
{
    return TransformationMatrix2d<float>(vs.getCourseAngle(),
                                         Vector2<float>(float(vs.getXPosition()), float(vs.getYPosition())));
}

//==============================================================================

TransformationMatrix2d<float> Transform::getTransformationSystem(const VehicleState2807& vs)
{
    return TransformationMatrix2d<float>(
        vs.getCourseAngle(), Vector2<float>(float(vs.getXPosition()) * 1e-4F, float(vs.getYPosition()) * 1e-4F));
}

//==============================================================================

TransformationMatrix2d<float> Transform::getTransformationSystem(const ObjectIn2281& object)
{
    return TransformationMatrix2d<float>(object.getCourseAngle(), object.getReferencePointCoord());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

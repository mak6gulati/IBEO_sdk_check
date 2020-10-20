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
//! \date Mrz 18, 2015
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/ObjectBasic.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

Vector2<float> convertRefPoint(const Vector2<float> refPoint,
                               const float refCourseAngle,
                               const Vector2<float> objectBox,
                               const RefPointBoxLocation fromPos,
                               const RefPointBoxLocation toPos)
{
    if (fromPos == toPos)
        return refPoint;

    int yShift = refLocIsCenterY(fromPos) ? 0 : (refLocIsLeft(fromPos) ? -1 : 1);
    yShift += refLocIsCenterY(toPos) ? 0 : (refLocIsLeft(toPos) ? 1 : -1);

    int xShift = refLocIsCenterX(fromPos) ? 0 : (refLocIsFront(fromPos) ? -1 : +1);
    xShift += refLocIsCenterX(toPos) ? 0 : (refLocIsFront(toPos) ? +1 : -1);

    Vector2<float> shift(0.5f * (float)xShift * objectBox.getX(), 0.5f * (float)yShift * objectBox.getY());
    shift.rotate(refCourseAngle);

    return refPoint + shift;
}

//==============================================================================

bool refLocIsRight(const RefPointBoxLocation refLoc)
{
    switch (refLoc)
    {
    case RefPointBoxLocation::FrontRight:
    case RefPointBoxLocation::RearRight:
    case RefPointBoxLocation::RightCenter:
        return true;
    default:
        return false;
    } // switch
}

//==============================================================================

bool refLocIsCenterY(const RefPointBoxLocation refLoc)
{
    switch (refLoc)
    {
    case RefPointBoxLocation::FrontCenter:
    case RefPointBoxLocation::RearCenter:
    case RefPointBoxLocation::ObjectCenter:
        return true;
    default:
        return false;
    } // switch
}

//==============================================================================

bool refLocIsLeft(const RefPointBoxLocation refLoc)
{
    switch (refLoc)
    {
    case RefPointBoxLocation::FrontLeft:
    case RefPointBoxLocation::RearLeft:
    case RefPointBoxLocation::LeftCenter:
        return true;
    default:
        return false;
    } // switch
}

//==============================================================================

bool refLocIsFront(const RefPointBoxLocation refLoc)
{
    switch (refLoc)
    {
    case RefPointBoxLocation::FrontLeft:
    case RefPointBoxLocation::FrontRight:
    case RefPointBoxLocation::FrontCenter:
        return true;
    default:
        return false;
    } // switch
}

//==============================================================================

bool refLocIsCenterX(const RefPointBoxLocation refLoc)
{
    switch (refLoc)
    {
    case RefPointBoxLocation::RightCenter:
    case RefPointBoxLocation::LeftCenter:
    case RefPointBoxLocation::ObjectCenter:
        return true;
    default:
        return false;
    } // switch
}

//==============================================================================

bool refLocIsRear(const RefPointBoxLocation refLoc)
{
    switch (refLoc)
    {
    case RefPointBoxLocation::RearRight:
    case RefPointBoxLocation::RearLeft:
    case RefPointBoxLocation::RearCenter:
        return true;
    default:
        return false;
    } // switch
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

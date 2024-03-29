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
//! \date Sep 4, 2013
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/io_prototypes.hpp>
#include <ibeo/common/sdk/Vector2.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

enum class ObjectClass : uint8_t
{
    Unclassified   = 0,
    UnknownSmall   = 1,
    UnknownBig     = 2,
    Pedestrian     = 3,
    Bike           = 4,
    Car            = 5,
    Truck          = 6,
    Underdriveable = 12,
    Train          = 14,
    Motorbike      = 15,
    Infrastructure = 16,
    Bicycle        = 17,
    SmallObstacle  = 18
}; // ObjectClass

//==============================================================================

template<>
void writeLE<ibeo::common::sdk::ObjectClass>(std::ostream& os, const ibeo::common::sdk::ObjectClass& oc);
template<>
void writeBE<ibeo::common::sdk::ObjectClass>(std::ostream& os, const ibeo::common::sdk::ObjectClass& oc);
template<>
void readLE<ibeo::common::sdk::ObjectClass>(std::istream& is, ibeo::common::sdk::ObjectClass& oc);
template<>
void readBE<ibeo::common::sdk::ObjectClass>(std::istream& is, ibeo::common::sdk::ObjectClass& oc);

//==============================================================================

namespace luxObjectClass { // prevent polluting of :: namespace.
//==============================================================================
//! \brief LuxObjectClass
//! \date Apr 27, 2016
//!
//! Not all classes may are available on every scanner type.
//! See the documentation of your model.
//------------------------------------------------------------------------------
enum class LuxObjectClass : uint8_t
{
    Unclassified = 0,
    UnknownSmall = 1,
    UnknownBig   = 2,
    Pedestrian   = 3,
    Bike         = 4,
    Car          = 5,
    Truck        = 6,
    Bicycle      = 12
}; // RawObjectClass
} // namespace luxObjectClass

//==============================================================================

template<>
void writeLE<ibeo::common::sdk::luxObjectClass::LuxObjectClass>(
    std::ostream& os,
    const ibeo::common::sdk::luxObjectClass::LuxObjectClass& oc);
template<>
void writeBE<ibeo::common::sdk::luxObjectClass::LuxObjectClass>(
    std::ostream& os,
    const ibeo::common::sdk::luxObjectClass::LuxObjectClass& oc);
template<>
void readLE<ibeo::common::sdk::luxObjectClass::LuxObjectClass>(std::istream& is,
                                                               ibeo::common::sdk::luxObjectClass::LuxObjectClass& oc);
template<>
void readBE<ibeo::common::sdk::luxObjectClass::LuxObjectClass>(std::istream& is,
                                                               ibeo::common::sdk::luxObjectClass::LuxObjectClass& oc);

//==============================================================================

namespace rawObjectClass { // prevent polluting of :: namespace.

//==============================================================================
//! \brief RawObjectClass
//! \date Sep 2, 2016
//------------------------------------------------------------------------------
enum class RawObjectClass : uint8_t
{
    Unclassified   = 0,
    UnknownSmall   = 1,
    UnknownBig     = 2,
    Pedestrian     = 3,
    Bike           = 4,
    Car            = 5,
    Truck          = 6,
    Overdrivable   = 10,
    Underdrivable  = 11,
    Bicycle        = 12,
    Motorbike      = 15,
    Infrastructure = 16,
    SmallObstacle  = 18
}; // RawObjectClass

//==============================================================================

} // namespace rawObjectClass

//==============================================================================

template<>
void writeLE<rawObjectClass::RawObjectClass>(std::ostream& os, const rawObjectClass::RawObjectClass& oc);
template<>
void writeBE<rawObjectClass::RawObjectClass>(std::ostream& os, const rawObjectClass::RawObjectClass& oc);
template<>
void readLE<rawObjectClass::RawObjectClass>(std::istream& is, rawObjectClass::RawObjectClass& oc);
template<>
void readBE<rawObjectClass::RawObjectClass>(std::istream& is, rawObjectClass::RawObjectClass& oc);

//==============================================================================

enum class RefPointBoxLocation : uint8_t
{
    CenterOfGravity = 0,
    FrontLeft       = 1,
    FrontRight      = 2,
    RearRight       = 3,
    RearLeft        = 4,
    FrontCenter     = 5,
    RightCenter     = 6,
    RearCenter      = 7,
    LeftCenter      = 8,
    ObjectCenter    = 9,
    Unknown         = 0xFF
}; // RefPointBoxLocation

//==============================================================================

// declare these templates but NOT define them since RefPointBoxLocation will be serialized sometimes as
// 8 sometimes as 16 bit. :(
template<>
void writeLE<ibeo::common::sdk::RefPointBoxLocation>(std::ostream& os,
                                                     const ibeo::common::sdk::RefPointBoxLocation& oc);
template<>
void writeBE<ibeo::common::sdk::RefPointBoxLocation>(std::ostream& os,
                                                     const ibeo::common::sdk::RefPointBoxLocation& oc);
template<>
void readLE<ibeo::common::sdk::RefPointBoxLocation>(std::istream& is, ibeo::common::sdk::RefPointBoxLocation& oc);
template<>
void readBE<ibeo::common::sdk::RefPointBoxLocation>(std::istream& is, ibeo::common::sdk::RefPointBoxLocation& oc);

template<int WIDTH>
void writeLE(std::ostream& os, const ibeo::common::sdk::RefPointBoxLocation rpbl);
template<int WIDTH>
void writeBE(std::ostream& os, const ibeo::common::sdk::RefPointBoxLocation rpbl);
template<int WIDTH>
void readLE(std::istream& is, ibeo::common::sdk::RefPointBoxLocation& rpbl);
template<int WIDTH>
void readBE(std::istream& is, ibeo::common::sdk::RefPointBoxLocation& rpbl);

template<>
void writeLE<8>(std::ostream& os, const ibeo::common::sdk::RefPointBoxLocation rpbl);
template<>
void writeBE<8>(std::ostream& os, const ibeo::common::sdk::RefPointBoxLocation rpbl);
template<>
void readLE<8>(std::istream& is, ibeo::common::sdk::RefPointBoxLocation& rpbl);
template<>
void readBE<8>(std::istream& is, ibeo::common::sdk::RefPointBoxLocation& rpbl);

template<>
void writeLE<16>(std::ostream& os, const ibeo::common::sdk::RefPointBoxLocation rpbl);
template<>
void writeBE<16>(std::ostream& os, const ibeo::common::sdk::RefPointBoxLocation rpbl);
template<>
void readLE<16>(std::istream& is, ibeo::common::sdk::RefPointBoxLocation& rpbl);
template<>
void readBE<16>(std::istream& is, ibeo::common::sdk::RefPointBoxLocation& rpbl);

//==============================================================================

bool refLocIsRight(const RefPointBoxLocation refLoc);
bool refLocIsCenterY(const RefPointBoxLocation refLoc);
bool refLocIsLeft(const RefPointBoxLocation refLoc);
bool refLocIsFront(const RefPointBoxLocation refLoc);
bool refLocIsCenterX(const RefPointBoxLocation refLoc);
bool refLocIsRear(const RefPointBoxLocation refLoc);

Vector2<float> convertRefPoint(const Vector2<float> refPoint,
                               const float refCourseAngle,
                               const Vector2<float> objectBox,
                               const RefPointBoxLocation fromPos,
                               const RefPointBoxLocation toPos);

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

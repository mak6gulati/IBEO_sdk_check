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
//!\date May 8, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/misc/Convert.hpp>
#include <ibeo/common/sdk/ObjectBasic.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================
// Helper functions for object list im-/export.
//==============================================================================

//==============================================================================
// cm to meter (big endian)
//==============================================================================

template<typename T>
static void readBEFromCm(std::istream& is, float& valueInMeter)
{
    T valueInCm;
    readBE(is, valueInCm);
    valueInMeter = convertFromCm<T>(valueInCm);
}

template<typename T>
static void readBEFromCm(std::istream& is, float& valueInMeter, const T nanValue)
{
    T valueInCm;
    readBE(is, valueInCm);
    valueInMeter = convertFromCm<T>(valueInCm, nanValue);
}

template<typename T>
static void readBEFromCm(std::istream& is, Vector2<float>& valueInMeter)
{
    Vector2<T> valueInCm;
    readBE(is, valueInCm);
    valueInMeter = convertFromCm<T>(valueInCm);
}

template<typename T>
static void readBEFromCm(std::istream& is, Vector2<float>& valueInMeter, const T nanValue)
{
    Vector2<T> valueInCm;
    readBE(is, valueInCm);
    valueInMeter = convertFromCm<T>(valueInCm, nanValue);
}

//==============================================================================

template<typename T>
static void writeBEToCm(std::ostream& os, const float valueInMeter)
{
    T valueInCm = convertToCm<T>(valueInMeter);
    writeBE(os, valueInCm);
}

template<typename T>
static void writeBEToCm(std::ostream& os, const float valueInMeter, const T nanValue)
{
    T valueInCm = convertToCm<T>(valueInMeter, nanValue);
    writeBE(os, valueInCm);
}

template<typename T>
static void writeBEToCm(std::ostream& os, const Vector2<float>& valueInMeter)
{
    Vector2<T> valueInCm = convertToCm<T>(valueInMeter);
    writeBE(os, valueInCm);
}

template<typename T>
static void writeBEToCm(std::ostream& os, const Vector2<float>& valueInMeter, const T nanValue)
{
    Vector2<T> valueInCm = convertToCm<T>(valueInMeter, nanValue);
    writeBE(os, valueInCm);
}

//==============================================================================
// cm to meter (little endian)
//==============================================================================

template<typename T>
static void readLEFromCm(std::istream& is, float& valueInMeter)
{
    T valueInCm;
    readLE(is, valueInCm);
    valueInMeter = convertFromCm<T>(valueInCm);
}

template<typename T>
static void readLEFromCm(std::istream& is, float& valueInMeter, const T nanValue)
{
    T valueInCm;
    readLE(is, valueInCm);
    valueInMeter = convertFromCm<T>(valueInCm, nanValue);
}

template<typename T>
static void readLEFromCm(std::istream& is, Vector2<float>& valueInMeter)
{
    Vector2<T> valueInCm;
    readLE(is, valueInCm);
    valueInMeter = convertFromCm<T>(valueInCm);
}

template<typename T>
static void readLEFromCm(std::istream& is, Vector2<float>& valueInMeter, const T nanValue)
{
    Vector2<T> valueInCm;
    readLE(is, valueInCm);
    valueInMeter = convertFromCm<T>(valueInCm, nanValue);
}

//==============================================================================

template<typename T>
static void writeLEToCm(std::ostream& os, const float valueInMeter)
{
    T valueInCm = convertToCm<T>(valueInMeter);
    writeLE(os, valueInCm);
}

template<typename T>
static void writeLEToCm(std::ostream& os, const float valueInMeter, const T nanValue)
{
    T valueInCm = convertToCm<T>(valueInMeter, nanValue);
    writeLE(os, valueInCm);
}

template<typename T>
static void writeLEToCm(std::ostream& os, const Vector2<float>& valueInMeter)
{
    Vector2<T> valueInCm = convertToCm<T>(valueInMeter);
    writeLE(os, valueInCm);
}

template<typename T>
static void writeLEToCm(std::ostream& os, const Vector2<float>& valueInMeter, const T nanValue)
{
    Vector2<T> valueInCm = convertToCm<T>(valueInMeter, nanValue);
    writeLE(os, valueInCm);
}

//==============================================================================
// centidegrees to rad (big endian)
//==============================================================================

template<typename T>
static void readBEFromCentiDegrees(std::istream& is, float& valueInRad)
{
    T valueInCentiDegrees;
    readBE(is, valueInCentiDegrees);
    valueInRad = convertFromCentiDegrees<T>(valueInCentiDegrees);
}

template<typename T>
static void readBEFromCentiDegrees(std::istream& is, float& valueInRad, const T nanValue)
{
    T valueInCentiDegrees;
    readBE(is, valueInCentiDegrees);
    valueInRad = convertFromCentiDegrees<T>(valueInCentiDegrees, nanValue);
}

template<typename T>
static void readBEFromCentiDegrees(std::istream& is, Vector2<float>& valueInRad)
{
    Vector2<T> valueInCentiDegrees;
    readBE(is, valueInCentiDegrees);
    valueInRad = convertFromCentiDegrees<T>(valueInCentiDegrees);
}

template<typename T>
static void readBEFromCentiDegrees(std::istream& is, Vector2<float>& valueInRad, const T nanValue)
{
    Vector2<T> valueInCentiDegrees;
    readBE(is, valueInCentiDegrees);
    valueInRad = convertFromCentiDegrees<T>(valueInCentiDegrees, nanValue);
}

//==============================================================================

template<typename T>
static void writeBEToCentiDegrees(std::ostream& os, const float valueInRad)
{
    T valueInCentiDegrees = convertToCentiDegrees<T>(valueInRad);
    writeBE(os, valueInCentiDegrees);
}

template<typename T>
static void writeBEToCentiDegrees(std::ostream& os, const float valueInRad, const T nanValue)
{
    T valueInCentiDegrees = convertToCentiDegrees<T>(valueInRad, nanValue);
    writeBE(os, valueInCentiDegrees);
}

template<typename T>
static void writeBEToCentiDegrees(std::ostream& os, const Vector2<float>& valueInRad)
{
    Vector2<T> valueInCentiDegrees = convertToCentiDegrees<T>(valueInRad);
    writeBE(os, valueInCentiDegrees);
}

template<typename T>
static void writeBEToCentiDegrees(std::ostream& os, const Vector2<float>& valueInRad, const T nanValue)
{
    Vector2<T> valueInCentiDegrees = convertToCentiDegrees<T>(valueInRad, nanValue);
    writeBE(os, valueInCentiDegrees);
}

//==============================================================================
// centidegrees to rad (little endian)
//==============================================================================

template<typename T>
static void readLEFromCentiDegrees(std::istream& is, float& valueInRad)
{
    T valueInCentiDegrees;
    readLE(is, valueInCentiDegrees);
    valueInRad = convertFromCentiDegrees<T>(valueInCentiDegrees);
}

template<typename T>
static void readLEFromCentiDegrees(std::istream& is, float& valueInRad, const T nanValue)
{
    T valueInCentiDegrees;
    readLE(is, valueInCentiDegrees);
    valueInRad = convertFromCentiDegrees<T>(valueInCentiDegrees, nanValue);
}

template<typename T>
static void readLEFromCentiDegrees(std::istream& is, Vector2<float>& valueInRad)
{
    Vector2<T> valueInCentiDegrees;
    readLE(is, valueInCentiDegrees);
    valueInRad = convertFromCentiDegrees<T>(valueInCentiDegrees);
}

template<typename T>
static void readLEFromCentiDegrees(std::istream& is, Vector2<float>& valueInRad, const T nanValue)
{
    Vector2<T> valueInCentiDegrees;
    readLE(is, valueInCentiDegrees);
    valueInRad = convertFromCentiDegrees<T>(valueInCentiDegrees, nanValue);
}

//==============================================================================

template<typename T>
static void writeLEToCentiDegrees(std::ostream& os, const float valueInRad)
{
    T valueInCentiDegrees = convertToCentiDegrees<T>(valueInRad);
    writeLE(os, valueInCentiDegrees);
}

template<typename T>
static void writeLEToCentiDegrees(std::ostream& os, const float valueInRad, const T nanValue)
{
    T valueInCentiDegrees = convertToCentiDegrees<T>(valueInRad, nanValue);
    writeLE(os, valueInCentiDegrees);
}

template<typename T>
static void writeLEToCentiDegrees(std::ostream& os, const Vector2<float>& valueInRad)
{
    Vector2<T> valueInCentiDegrees = convertToCentiDegrees<T>(valueInRad);
    writeLE(os, valueInCentiDegrees);
}

template<typename T>
static void writeLEToCentiDegrees(std::ostream& os, const Vector2<float>& valueInRad, const T nanValue)
{
    Vector2<T> valueInCentiDegrees = convertToCentiDegrees<T>(valueInRad, nanValue);
    writeLE(os, valueInCentiDegrees);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

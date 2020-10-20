//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Sep 29, 2015
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/CompressedPoint2d.hpp>
#include <ibeo/common/sdk/ObjectBasic.hpp>
#include <ibeo/common/sdk/Vector2.hpp>
#include <ibeo/common/sdk/Rectangle.hpp>
#include <ibeo/common/sdk/datablocks/MountingPosition.hpp>

#include <vector>
#include <type_traits>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class TestSupport
{
public:
    virtual ~TestSupport();

public:
    template<typename T>
    static T getRandValue();

    template<typename T>
    static T getRandValue(const T rangeMax);

    template<typename T>
    static T getRandValue(const T rangeMin, const T rangeMax);

    //========================================
    //!\brief get new random value that differs from the old value
    //!\param[in] oldValue              the old value, that's going to be replaced
    //!\return new random value
    //----------------------------------------
    template<typename T>
    static T getDifferentRandValue(const T& oldValue);

    template<typename T>
    static T getDifferentRandValue(const T& rangeMax, const T& oldValue);

    template<typename T>
    static T getDifferentRandValue(const T& rangeMin, const T& rangeMax, const T& oldValue);
    //----------------------------------------

    template<typename T>
    static inline T getNonNanRandValue();

    static std::string getRandString(const uint32_t length);
    static std::string getOrdinaryAsciiString(const uint32_t lenght); // no 0-bytes and line breaks

    template<typename T>
    static void fillVectorRandomly(std::vector<T>& vectorToBeFilled);

    template<typename T>
    static inline void fillVectorRandomlyNonNan(std::vector<T>& vectorToBeFilled);
}; // TestSupport

//==============================================================================

template<>
bool TestSupport::getRandValue();

template<>
char TestSupport::getRandValue();

template<>
uint8_t TestSupport::getRandValue();
template<>
uint8_t TestSupport::getRandValue(const uint8_t rangeMax);
template<>
uint8_t TestSupport::getRandValue(const uint8_t rangeMin, const uint8_t rangeMax);

template<>
int8_t TestSupport::getRandValue();

template<>
uint16_t TestSupport::getRandValue();
template<>
uint16_t TestSupport::getRandValue(const uint16_t rangeMax);
template<>
uint16_t TestSupport::getRandValue(const uint16_t rangeMin, const uint16_t rangeMax);

template<>
int16_t TestSupport::getRandValue();

template<>
uint32_t TestSupport::getRandValue();
template<>
int32_t TestSupport::getRandValue();
template<>
uint32_t TestSupport::getRandValue(const uint32_t rangeMax);
template<>
uint32_t TestSupport::getRandValue(const uint32_t rangeMin, const uint32_t rangeMax);

template<>
int64_t TestSupport::getRandValue();
template<>
uint64_t TestSupport::getRandValue();

template<typename T>
T TestSupport::getDifferentRandValue(const T& oldValue)
{
    T reallyOldValue = oldValue;
    T newValue;
    do
    {
        newValue = getRandValue<T>();
    } while ((std::is_floating_point<T>::value && (std::isnan(newValue) && std::isnan(reallyOldValue)))
             || (newValue == reallyOldValue));
    return newValue;
}

template<typename T>
T TestSupport::getDifferentRandValue(const T& rangeMax, const T& oldValue)
{
    uint32_t max = static_cast<uint32_t>(rangeMax);
    T newVal;
    do
    {
        newVal = getDifferentRandValue<T>(oldValue);
    } while (static_cast<uint32_t>(newVal) == max);

    return newVal;
}

template<typename T>
T TestSupport::getDifferentRandValue(const T& rangeMin, const T& rangeMax, const T& oldValue)
{
    uint32_t min = static_cast<uint32_t>(rangeMin);
    uint32_t max = static_cast<uint32_t>(rangeMax);

    T newVal;
    do
    {
        newVal = getDifferentRandValue<T>(oldValue);
    } while (static_cast<uint32_t>(newVal) < min || static_cast<uint32_t>(newVal) > max);

    return newVal;
}

template<>
float TestSupport::getRandValue();
template<>
float TestSupport::getRandValue(float rangeMin, float rangeMax);
template<>
double TestSupport::getRandValue();

template<>
Vector2<int16_t> TestSupport::getRandValue();
template<>
Vector2<uint16_t> TestSupport::getRandValue();
template<>
CompressedPoint2d TestSupport::getRandValue();
template<>
NTPTime TestSupport::getRandValue();

template<>
RefPointBoxLocation TestSupport::getRandValue();
template<>
ObjectClass TestSupport::getRandValue();
template<>
luxObjectClass::LuxObjectClass TestSupport::getRandValue();
template<>
rawObjectClass::RawObjectClass TestSupport::getRandValue();

template<>
Vector2<float> TestSupport::getRandValue();
template<>
Vector2<float> TestSupport::getRandValue(const Vector2<float> rangeMin, const Vector2<float> rangeMax);
template<>
Vector3<float> TestSupport::getRandValue();
template<>
Rectangle<int16_t> TestSupport::getRandValue();
template<>
Rectangle<float> TestSupport::getRandValue();

template<>
MountingPosition<float> TestSupport::getRandValue();

//==============================================================================

template<>
Vector2<float> TestSupport::getDifferentRandValue(const Vector2<float>& oldValue);
template<>
Vector2<float> TestSupport::getDifferentRandValue(const Vector2<float>& rangeMax, const Vector2<float>& oldValue);
template<>
Vector2<float> TestSupport::getDifferentRandValue(const Vector2<float>& rangeMin,
                                                  const Vector2<float>& rangeMax,
                                                  const Vector2<float>& oldValue);

//==============================================================================

template<typename T>
void TestSupport::fillVectorRandomly(std::vector<T>& vectorToBeFilled)
{
    for (auto& a : vectorToBeFilled)
    {
        a = getRandValue<T>();
    }
}

//==============================================================================

template<typename T>
inline void TestSupport::fillVectorRandomlyNonNan(std::vector<T>& vectorToBeFilled)
{
    for (auto& a : vectorToBeFilled)
    {
        a = getNonNanRandValue<T>();
    }
}

//==============================================================================

template<>
Vector2<float> TestSupport::getNonNanRandValue();

template<>
Vector3<float> TestSupport::getNonNanRandValue();

//==============================================================================

template<typename T>
inline T TestSupport::getNonNanRandValue()
{
    static_assert(std::is_floating_point<T>::value, "NaN values do only exit for floating point types");
    T r;
    do
    {
        r = getRandValue<T>();
    } while (std::isnan(r));
    return r;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

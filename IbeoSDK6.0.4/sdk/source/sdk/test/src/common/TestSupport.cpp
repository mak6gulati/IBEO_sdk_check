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
//!\date Sep 29, 2015
//------------------------------------------------------------------------------

//==============================================================================

#include "TestSupport.hpp"

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Math.hpp>
#include <type_traits>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

TestSupport::~TestSupport() {}

//==============================================================================

template<>
bool TestSupport::getRandValue()
{
    return (rand() % 2) ? true : false;
}

template<>
char TestSupport::getRandValue()
{
    return char(rand() % (1 << 8));
}

template<>
uint8_t TestSupport::getRandValue()
{
    return uint8_t(rand() % (1 << 8));
}

template<>
uint8_t TestSupport::getRandValue(const uint8_t rangeMax)
{
    return uint8_t(rand() % uint16_t(rangeMax + 1));
}

template<>
uint8_t TestSupport::getRandValue(const uint8_t rangeMin, const uint8_t rangeMax)
{
    return uint8_t(uint32_t(rand()) % uint32_t(rangeMax - rangeMin + 1) + rangeMin);
}

template<>
int8_t TestSupport::getRandValue()
{
    return getRandValue<char>();
}

template<>
uint16_t TestSupport::getRandValue()
{
    return uint16_t(rand() % (1 << 16));
}

template<>
uint16_t TestSupport::getRandValue(const uint16_t rangeMax)
{
    return uint16_t(uint32_t(rand()) % uint32_t(rangeMax + 1));
}

template<>
uint16_t TestSupport::getRandValue(const uint16_t rangeMin, const uint16_t rangeMax)
{
    return uint16_t(uint32_t(rand()) % uint32_t(rangeMax - rangeMin + 1) + rangeMin);
}

template<>
uint32_t TestSupport::getRandValue(const uint32_t rangeMin, const uint32_t rangeMax)
{
    return uint32_t(uint32_t(rand()) % uint32_t(rangeMax - rangeMin + 1) + rangeMin);
}

template<>
int16_t TestSupport::getRandValue()
{
    return int16_t((rand() % (1 << 16)) - (1 << 15));
}

template<>
uint32_t TestSupport::getRandValue()
{
    return uint32_t(rand());
}

template<>
int32_t TestSupport::getRandValue()
{
    return int32_t((rand() % (1LL << 32)) - (1 << 16));
}

template<>
uint32_t TestSupport::getRandValue(const uint32_t rangeMax)
{
    return uint32_t(uint64_t(rand()) % uint64_t(rangeMax + 1));
}

template<>
int64_t TestSupport::getRandValue()
{
    return int64_t(getRandValue<int32_t>()) << 32 | getRandValue<int32_t>();
}

template<>
uint64_t TestSupport::getRandValue()
{
    return uint64_t(getRandValue<uint32_t>()) << 32 | getRandValue<uint32_t>();
}

template<>
float TestSupport::getRandValue()
{
    const uint32_t r = getRandValue<uint32_t>();
    const uint32_t& t{r}; // use reference to avoid aliasing problems
    return reinterpret_cast<const float&>(t);
}

template<>
float TestSupport::getRandValue(const float rangeMin, float rangeMax)
{
    return rangeMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (rangeMax - rangeMin));
}

template<>
double TestSupport::getRandValue()
{
    const uint64_t r = getRandValue<uint64_t>();
    const uint64_t& t{r}; // use reference to avoid aliasing problems
    return reinterpret_cast<const double&>(t);
}

//==============================================================================

template<>
Vector2<float> TestSupport::getNonNanRandValue()
{
    Vector2<float> r;
    r.setX(getNonNanRandValue<float>());
    r.setY(getNonNanRandValue<float>());
    return r;
}

//==============================================================================

template<>
Vector3<float> TestSupport::getNonNanRandValue()
{
    Vector3<float> r;
    r.setX(getNonNanRandValue<float>());
    r.setY(getNonNanRandValue<float>());
    r.setZ(getNonNanRandValue<float>());
    return r;
}

//==============================================================================

std::string TestSupport::getRandString(const uint32_t length)
{
    std::string word;
    word.reserve(length);

    for (uint32_t ii = 0; ii < length; ++ii)
    {
        word.push_back(getRandValue<char>());
    }
    return word;
}

//==============================================================================

std::string TestSupport::getOrdinaryAsciiString(const uint32_t length)
{
    std::string word;
    word.reserve(length);

    for (uint32_t ii = 0; ii < length; ++ii)
    {
        const char c = static_cast<char>(toascii(getRandValue<char>()));
        if ((c != '\0') && (c != '\n'))
        {
            word.push_back(c);
        }
        else
        {
            word.push_back(' '); // use space instead
        }
    }

    return word;
}

//==============================================================================

template<>
Vector2<int16_t> TestSupport::getRandValue()
{
    return Vector2<int16_t>(getRandValue<int16_t>(), getRandValue<int16_t>());
}

template<>
Vector2<uint16_t> TestSupport::getRandValue()
{
    return Vector2<uint16_t>(getRandValue<uint16_t>(), getRandValue<uint16_t>());
}

template<>
CompressedPoint2d TestSupport::getRandValue()
{
    return CompressedPoint2d(getRandValue<int16_t>(), getRandValue<int16_t>());
}

template<>
RefPointBoxLocation TestSupport::getRandValue()
{
    return RefPointBoxLocation(getRandValue<uint8_t>());
}

template<>
ObjectClass TestSupport::getRandValue()
{
    return ObjectClass(getRandValue<uint8_t>());
}

template<>
luxObjectClass::LuxObjectClass TestSupport::getRandValue()
{
    return luxObjectClass::LuxObjectClass(getRandValue<uint8_t>());
}

template<>
rawObjectClass::RawObjectClass TestSupport::getRandValue()
{
    return rawObjectClass::RawObjectClass(getRandValue<uint8_t>());
}

template<>
NTPTime TestSupport::getRandValue()
{
    const uint64_t t = (uint64_t(getRandValue<uint16_t>()) << 48) | (uint64_t(getRandValue<uint16_t>()) << 32)
                       | (uint64_t(getRandValue<uint16_t>()) << 16) | (uint64_t(getRandValue<uint16_t>()));
    return NTPTime(t);
}

template<>
Vector2<float> TestSupport::getRandValue()
{
    return Vector2<float>(getRandValue<float>(), getRandValue<float>());
}

template<>
Vector2<float> TestSupport::getRandValue(const Vector2<float> rangeMin, const Vector2<float> rangeMax)
{
    return Vector2<float>(getRandValue<float>(rangeMin.getX(), rangeMax.getX()),
                          getRandValue<float>(rangeMin.getY(), rangeMax.getY()));
}

template<>
Vector3<float> TestSupport::getRandValue()
{
    return Vector3<float>(getRandValue<float>(), getRandValue<float>(), getRandValue<float>());
}

template<>
Rectangle<int16_t> TestSupport::getRandValue()
{
    return Rectangle<int16_t>(
        getRandValue<Vector2<int16_t>>(), getRandValue<Vector2<int16_t>>(), getRandValue<int16_t>());
}

template<>
Rectangle<float> TestSupport::getRandValue()
{
    return Rectangle<float>(getRandValue<Vector2<float>>(), getRandValue<Vector2<float>>(), getRandValue<float>());
}

template<>
MountingPosition<float> TestSupport::getRandValue()
{
    return MountingPosition<float>(getNonNanRandValue<float>(),
                                   getNonNanRandValue<float>(),
                                   getNonNanRandValue<float>(),
                                   getNonNanRandValue<float>(),
                                   getNonNanRandValue<float>(),
                                   getNonNanRandValue<float>());
}

//==============================================================================

template<>
Vector2<float> TestSupport::getDifferentRandValue(const Vector2<float>& oldValue)
{
    return Vector2<float>(getDifferentRandValue(oldValue.getX()), getDifferentRandValue(oldValue.getY()));
}

template<>
Vector2<float> TestSupport::getDifferentRandValue(const Vector2<float>& rangeMax, const Vector2<float>& oldValue)
{
    return Vector2<float>(getDifferentRandValue(rangeMax.getX(), oldValue.getX()),
                          getDifferentRandValue(rangeMax.getY(), oldValue.getY()));
}

template<>
Vector2<float> TestSupport::getDifferentRandValue(const Vector2<float>& rangeMin,
                                                  const Vector2<float>& rangeMax,
                                                  const Vector2<float>& oldValue)
{
    return Vector2<float>(getDifferentRandValue(rangeMin.getX(), rangeMax.getX(), oldValue.getX()),
                          getDifferentRandValue(rangeMin.getY(), rangeMax.getY(), oldValue.getY()));
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

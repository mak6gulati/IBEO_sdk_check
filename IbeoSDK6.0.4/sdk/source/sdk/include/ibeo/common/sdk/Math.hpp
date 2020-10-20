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
//!\date Sep 29, 2013
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <ibeo/common/sdk/misc/deprecatedwarning.hpp>

#include <limits>
#include <cassert>
#include <cmath>
#if _MSC_VER == 1600
#    ifdef _M_X64
#        include <math.h>
#    endif // _M_X64
#endif //_MSC_VER == 1600

//==============================================================================

#if defined _WIN32 && _MSC_VER < 1900
//!\brief rename VC _isnan function as isnan for compatibility
//------------------------------------------------------------------------------
#    if _MSC_VER == 1800
#        error "Not tested with VS 2013"
#    endif // _MSC_VER == 1800
namespace std {
inline bool isnan(const double d) { return 0 != _isnan(d); }
} // namespace std

#endif // _WIN32 &&  _MSC_VER < 1900

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

constexpr double piHalf  = M_PI / 2.0;
constexpr double twoPi   = 2.0 * M_PI;
constexpr double rad2deg = 180.0 / M_PI;
constexpr double deg2rad = M_PI / 180.0;

//==============================================================================

//!\brief template Class to hold the powers for float/double fuzzy compare template functions.
//! \date June 18, 2018
//------------------------------------------------------------------------------
template<typename FloatType, uint8_t Exponent>
class NegativePower
{
};

//definitions float
template<>
struct NegativePower<float, 0>
{
    constexpr float operator()() const { return 1e-0F; }
};
template<>
struct NegativePower<float, 1>
{
    constexpr float operator()() const { return 1e-1F; }
};
template<>
struct NegativePower<float, 2>
{
    constexpr float operator()() const { return 1e-2F; }
};
template<>
struct NegativePower<float, 3>
{
    constexpr float operator()() const { return 1e-3F; }
};
template<>
struct NegativePower<float, 4>
{
    constexpr float operator()() const { return 1e-4F; }
};
template<>
struct NegativePower<float, 5>
{
    constexpr float operator()() const { return 1e-5F; }
};
template<>
struct NegativePower<float, 6>
{
    constexpr float operator()() const { return 1e-6F; }
};
template<>
struct NegativePower<float, 7>
{
    constexpr float operator()() const { return 1e-7F; }
};

//definitions double
template<>
struct NegativePower<double, 0>
{
    constexpr double operator()() const { return 1e-0; }
};
template<>
struct NegativePower<double, 1>
{
    constexpr double operator()() const { return 1e-1; }
};
template<>
struct NegativePower<double, 2>
{
    constexpr double operator()() const { return 1e-2; }
};
template<>
struct NegativePower<double, 3>
{
    constexpr double operator()() const { return 1e-3; }
};
template<>
struct NegativePower<double, 4>
{
    constexpr double operator()() const { return 1e-4; }
};
template<>
struct NegativePower<double, 5>
{
    constexpr double operator()() const { return 1e-5; }
};
template<>
struct NegativePower<double, 6>
{
    constexpr double operator()() const { return 1e-6; }
};
template<>
struct NegativePower<double, 7>
{
    constexpr double operator()() const { return 1e-7; }
};
template<>
struct NegativePower<double, 8>
{
    constexpr double operator()() const { return 1e-8; }
};
template<>
struct NegativePower<double, 9>
{
    constexpr double operator()() const { return 1e-9; }
};
template<>
struct NegativePower<double, 10>
{
    constexpr double operator()() const { return 1e-10; }
};
template<>
struct NegativePower<double, 11>
{
    constexpr double operator()() const { return 1e-11; }
};
template<>
struct NegativePower<double, 12>
{
    constexpr double operator()() const { return 1e-12; }
};
template<>
struct NegativePower<double, 13>
{
    constexpr double operator()() const { return 1e-13; }
};
template<>
struct NegativePower<double, 14>
{
    constexpr double operator()() const { return 1e-14; }
};
template<>
struct NegativePower<double, 15>
{
    constexpr double operator()() const { return 1e-15; }
};
template<>
struct NegativePower<double, 16>
{
    constexpr double operator()() const { return 1e-16; }
};
template<>
struct NegativePower<double, 17>
{
    constexpr double operator()() const { return 1e-17; }
};

//==============================================================================

//!\brief Shortcut for the float NaN value.
//------------------------------------------------------------------------------
const float NaN = std::numeric_limits<float>::quiet_NaN();

//!\brief Shortcut for the double NaN value.
//------------------------------------------------------------------------------
const double NaN_double = std::numeric_limits<double>::quiet_NaN();

//==============================================================================

//!\brief Shortcut for the int NaN value.*/
// == alias for int32
//const int NaN_int = std::numeric_limits<int>::quiet_NaN();

//==============================================================================

constexpr float piHalff  = static_cast<float>(M_PI / 2.0);
constexpr float twoPif   = static_cast<float>(2.0 * M_PI);
constexpr float rad2degf = static_cast<float>(180.0 / M_PI);
constexpr float deg2radf = static_cast<float>(M_PI / 180.0);

//==============================================================================
//!\brief Tests whether two \c float values are nearly equal.
//!\tparam EXP   The exponent of the epsilon used for the fuzzy
//!              compare. 10^(-EXP).
//!\param[in] a  First value to be compared with second value.
//!\param[in] b  Second value to be compared with first value.
//!\return \c true if the two \c float numbers are equal in
//!        terms of the machine precision, which means their
//!        difference must be less than 10^(-EXP).
//!
//!The exponent range is defined in NegFloatPotenciesOf10.
//------------------------------------------------------------------------------
template<uint8_t EXP>
inline bool fuzzyCompareT(const float a, const float b)
{
    return std::abs(a - b) < NegativePower<float, EXP>{}();
}

//==============================================================================

IBEOSDK_DEPRECATED inline bool fuzzyCompare(const float a, const float b) { return fuzzyCompareT<6>(a, b); }

//==============================================================================
//!\brief Tests whether two \c double values are nearly equal.
//!\tparam EXP   The exponent of the epsilon used for the fuzzy
//!              compare. 10^(-EXP).
//!\param[in] a  First value to be compared with second value.
//!\param[in] b  Second value to be compared with first value.
//!\return \c true if the two \c double numbers are equal in
//!        terms of the machine precision, which means their
//!        difference must be less than 10^(-EXP).
//!
//!The exponent range is defined in NegDoublePotenciesOf10.
//------------------------------------------------------------------------------
template<uint8_t EXP>
inline bool fuzzyCompareT(const double a, const double b)
{
    return std::abs(a - b) < NegativePower<double, EXP>{}();
}

//==============================================================================
//!\brief Tests whether two \c float values are nearly equal.
//!\param[in] a  First value to be compared with second value.
//!\param[in] b  Second value to be compared with first value.
//!\return \c true if the two \c float numbers are equal in
//!        terms of the machine precision, which means their
//!        difference must be less than 1E-6.
//------------------------------------------------------------------------------
IBEOSDK_DEPRECATED inline bool fuzzyCompare(const double a, const double b) { return std::abs(a - b) < 1E-6; }

//==============================================================================
//!\brief Compare two floats \a a and \a b. NaN is equal NaN here.
//!\param[in] a  First float to be compared.
//!\param[in] b  Second float to be compared.
//!\return \c true if \a a == \a b or if both are NaN.
//!        \c false otherwise.
//------------------------------------------------------------------------------
inline bool floatEqual(const float a, const float b) { return ((std::isnan(a) && std::isnan(b)) || a == b); }

//==============================================================================
//!\brief Compare two doubles \a a and \a b. NaN is equal NaN here.
//!\param[in] a  First double to be compared.
//!\param[in] b  Second double to be compared.
//!\return \c true if \a a == \a b or if both are NaN.
//!        \c false otherwise.
//------------------------------------------------------------------------------
inline bool doubleEqual(const double a, const double b) { return ((std::isnan(a) && std::isnan(b)) || a == b); }

//==============================================================================
//!\brief Fuzzy Compare two floats \a a and \a b. NaN is equal NaN here.
//!\tparam EXP   The exponent of the epsilon used for the fuzzy
//!              compare. 10^(-EXP).
//!\param[in] a  First float to be compared.
//!\param[in] b  Second float to be compared.
//!\return \c true if the difference between \a a and \a b is not smaller
//!        than 10^(-EXP) or if both are NaN.
//!        \c false otherwise.
//------------------------------------------------------------------------------
template<uint8_t EXP>
inline bool fuzzyFloatEqualT(const float a, const float b)
{
    return ((std::isnan(a) && std::isnan(b)) || fuzzyCompareT<EXP>(a, b));
}

//==============================================================================
//!\brief Fuzzy Compare two doubles \a a and \a b. NaN is equal NaN here.
//!\tparam EXP   The exponent of the epsilon used for the fuzzy
//!              compare. 10^(-EXP).
//!\param[in] a  First double to be compared.
//!\param[in] b  Second double to be compared.
//!\return \c true if the difference between \a a and \a b is not smaller
//!        than 10^(-EXP) or if both are NaN.
//!        \c false otherwise.
//------------------------------------------------------------------------------
template<uint8_t EXP>
inline bool fuzzyDoubleEqualT(const double a, const double b)
{
    return ((std::isnan(a) && std::isnan(b)) || fuzzyCompareT<EXP>(a, b));
}

//==============================================================================
//!\brief Use fuzzyFloatEqualT instead.
//!\deprecated Use fuzzyFloatEqualT instead.
//------------------------------------------------------------------------------
IBEOSDK_DEPRECATED inline bool fuzzyFloatEqual(const float a, const float b) { return fuzzyFloatEqualT<6>(a, b); }

//==============================================================================

inline bool floatInequal(const float a, const float b) { return !floatEqual(a, b); }

//==============================================================================

template<uint8_t EXP>
inline bool fuzzyFloatInequalT(const float a, const float b)
{
    return (!fuzzyFloatEqualT<EXP>(a, b));
}

//==============================================================================

template<uint8_t EXP>
inline bool fuzzyDoubleInequalT(const double a, const double b)
{
    return (!fuzzyDoubleEqualT<EXP>(a, b));
}

//==============================================================================

//==============================================================================
//!\brief Use fuzzyFloatInequalT instead.
//!\deprecated Use fuzzyFloatInequalT instead.
//------------------------------------------------------------------------------
IBEOSDK_DEPRECATED inline bool fuzzyFloatInequal(const float a, const float b) { return fuzzyFloatInequalT<6>(a, b); }

//==============================================================================
//!\brief Normalize the given angle.
//!
//!Normalizes an angle given in radians by adding or subtracting an integer
//!multiple of 2*pi so that the resulting angle is in the half-open interval
//!(-pi,+pi]. The current implementation takes O(1) time, i.e. the time of
//!execution has a fixed upper boundary independend from the angle.
//!
//!\param[in] angleInRad  Angle to be normalized given in rad.
//!\return The normalized angle in (-pi, +pi].
//!\todo check whether (-pi, +pi] or [-pi, +pi) is correct.
//------------------------------------------------------------------------------
inline float normalizeRadians(float angleInRad)
{
    if (std::abs(angleInRad) > (3.0F * static_cast<float>(M_PI)))
    {
        // For numerical stability we must use this sin/cos/atan2
        // implementation even though it might consume more cycles.
        // Note that radians = -pi converts to atan2(0,-1) = +pi!
        angleInRad = std::atan2(std::sin(angleInRad), std::cos(angleInRad));
        // radians now in (-pi,+pi]
    } // if
    else
    {
        // fast version for "normal" out of range values
        while (angleInRad > static_cast<float>(M_PI))
        {
            angleInRad -= twoPif;
        } // while
        while (angleInRad <= static_cast<float>(-M_PI))
        {
            angleInRad += twoPif;
        } // while
    } // else
    return angleInRad;
}

//==============================================================================
//!\brief Normalize the given angle.
//!
//!Normalizes an angle given in radians by adding or subtracting an integer
//!multiple of 2*pi so that the resulting angle is in the half-open interval
//!(-pi,+pi]. The current implementation takes O(1) time, i.e. the time of
//!execution has a fixed upper boundary independend from the angle.
//!
//!\param[in] angleInRad  Angle to be normalized given in rad.
//!\return The normalized angle in (-pi, +pi].
//!\todo check whether (-pi, +pi] or [-pi, +pi) is correct.
//------------------------------------------------------------------------------
inline double normalizeRadians(double angleInRad)
{
    if (std::abs(angleInRad) > (3.0 * M_PI))
    {
        // For numerical stability we must use this sin/cos/atan2
        // implementation even though it might consume more cycles.
        // Note that radians = -pi converts to atan2(0,-1) = +pi!
        angleInRad = std::atan2(std::sin(angleInRad), std::cos(angleInRad));
        // radians now in (-pi,+pi]
    } // if
    else
    {
        // fast version for "normal" out of range values
        while (angleInRad > M_PI)
        {
            angleInRad -= twoPi;
        } // while
        while (angleInRad <= -M_PI)
        {
            angleInRad += twoPi;
        } // while
    } // else
    return angleInRad;
}

//==============================================================================
//!\brief Round to the closest integer
//!
//!\param[in] floatValue The float value that shall be rounded
//!\return \a floatValue rounded to the closest integer
//------------------------------------------------------------------------------
template<typename IntT>
inline IntT round(float floatValue)
{
    return IntT(floatValue + (floatValue >= 0.0F ? +0.5F : -0.5F));
}
//!\brief Round to the closest integer
//!
//!\param[in] doubleValue The double value that shall be rounded
//!\return \a doubleValue rounded to the closest integer
//------------------------------------------------------------------------------
template<typename IntT>
inline IntT round(double doubleValue)
{
    return IntT(doubleValue + (doubleValue >= 0.0 ? +0.5 : -0.5));
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

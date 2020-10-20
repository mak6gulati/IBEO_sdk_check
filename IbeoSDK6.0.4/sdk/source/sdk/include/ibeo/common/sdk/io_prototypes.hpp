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
//! \date Apr 24, 2014
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <iostream>
#include <type_traits>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

template<typename T>
void writeLE(std::ostream& os, const T& value);
template<typename T>
void writeBE(std::ostream& os, const T& value);

template<typename T>
void readLE(std::istream& is, T& value);
template<typename T>
void readBE(std::istream& is, T& value);

// default implementation
template<typename T>
inline constexpr std::streamsize serializedSize(const T&)
{
    static_assert(std::is_fundamental<T>::value,
                  "Called serializedSize template function with complex type. No specialization available");

    return std::streamsize(sizeof(T));
}

//==============================================================================

template<typename ENUMTYPE, typename INTTYPE>
void writeBE(std::ostream& os, const ENUMTYPE& value)
{
    writeBE(os, INTTYPE(value));
}

//==============================================================================

template<typename ENUMTYPE, typename INTTYPE>
void readBE(std::istream& is, ENUMTYPE& value)
{
    INTTYPE s;
    readBE(is, s);
    value = ENUMTYPE(s);
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

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
//! \date Oct 22, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <cstdint>
#include <iomanip>
#include <limits>
#include <sstream>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

inline std::stringstream& toHex(std::stringstream& ss, const unsigned char t)
{
    ss << std::hex << std::setfill('0') << std::setw(2) << uint32_t(uint8_t(t));
    return ss;
}

//==============================================================================

template<typename T>
std::string toHex(const T t);

//==============================================================================

template<>
inline std::string toHex<unsigned char>(const unsigned char t)
{
    std::stringstream ss;
    ss << "0x";
    toHex(ss, t);
    return ss.str();
}

//==============================================================================

template<>
inline std::string toHex<char>(const char t)
{
    return toHex(uint8_t(t));
}

//==============================================================================

template<>
inline std::string toHex<uint16_t>(const uint16_t t)
{
    std::stringstream ss;
    ss << "0x";
    ss << std::hex << std::setfill('0') << std::setw(4) << t;
    //	toHex(ss, uint8_t(t>>8));
    //	toHex(ss, uint8_t(t & 0xFF));
    return ss.str();
}

//==============================================================================

template<>
inline std::string toHex<int16_t>(const int16_t t)
{
    return toHex(uint16_t(t));
}

//==============================================================================

template<>
inline std::string toHex<uint32_t>(const uint32_t t)
{
    std::stringstream ss;
    ss << "0x";
    ss << std::hex << std::setfill('0') << std::setw(8) << t;

    return ss.str();
}

//==============================================================================

template<>
inline std::string toHex<int32_t>(const int32_t t)
{
    return toHex(uint32_t(t));
}

//==============================================================================

template<>
inline std::string toHex<uint64_t>(const uint64_t t)
{
    std::stringstream ss;
    ss << "0x";
    ss << std::hex << std::setfill('0') << std::setw(8) << (t >> 32) << ":" << std::hex << std::setfill('0')
       << std::setw(8) << (t & std::numeric_limits<uint32_t>::max());

    return ss.str();
}

//==============================================================================

template<>
inline std::string toHex<int64_t>(const int64_t t)
{
    return toHex(uint64_t(t));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

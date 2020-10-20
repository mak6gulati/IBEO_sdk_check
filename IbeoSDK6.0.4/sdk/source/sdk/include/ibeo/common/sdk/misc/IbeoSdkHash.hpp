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
//! \date Dec 15, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <stdint.h>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================
//! \brief FNV-1a hash for 64bit length
//!
//! \note The computation actually visits the string from back to front and not
//!       from front to back.
//------------------------------------------------------------------------------
constexpr inline uint64_t hash(const char* classId)
{
    return (*classId ? (hash(classId + 1) ^ static_cast<unsigned char>(*classId)) * 0x100000001b3 : 0xcbf29ce484222325);
}

//==============================================================================
//! \brief Helper structure for getting the hash value of an enum class.
//------------------------------------------------------------------------------
struct EnumClassHash
{
    template<typename T>
    uint64_t operator()(T t) const
    {
        return static_cast<uint64_t>(t);
    }
};

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

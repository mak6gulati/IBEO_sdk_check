//==============================================================================
//! \file
//!
//!        Compatibility file for windows (Visual Studio).
//!
//!\note: This file is a basic include. It should be included
//!       by all header files.
//!
//! \note: This file has an embedded auto include for the stdInt data type:
//!        - <stdint.h> (for linux and Visual Studio newer than 2008);
//!        - <stdintForVS2008.h> for VS 2008.
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Oct 2, 2013
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#ifdef _WIN32
#    if defined IBEOSDKLIBDLL_SHARED // shared usage
#        if defined IBEOSDKLIBDLL_EXPORTS // building --> exporting
#            define IBEOSDK_API __declspec(dllexport)
#        else // using --> import
#            define IBEOSDK_API __declspec(dllimport)
#        endif
#    else // static case for windows
#        define IBEOSDK_API
#    endif
#else // not windows
#    define IBEOSDK_API
#endif // _WIN32

#ifdef _WIN32
#    ifndef _USE_MATH_DEFINES
#        define _USE_MATH_DEFINES
#    endif // _USE_MATH_DEFINES

#    ifndef NOMINMAX
#        define NOMINMAX
#    endif // NOMINMAX

#    define __func__ __FUNCTION__

#    ifndef __BIG_ENDIAN
#        define __BIG_ENDIAN 1234
#    endif // __BIG_ENDIAN

#    ifndef __LITTLE_ENDIAN
#        define __LITTLE_ENDIAN 3412
#    endif // __LITTLE_ENDIAN

#endif // _WIN32

//==============================================================================

#if _MSC_VER == 1500
#    ifdef WCHAR_MIN
#        undef WCHAR_MIN
#        undef INT8_C
#        undef UINT8_C
#        undef INT16_C
#        undef UINT16_C
#        undef INT32_C
#        undef UINT32_C
#        undef INT64_C
#        undef UINT64_C
#        undef INTMAX_C
#        undef UINTMAX_C
#    endif // WCHAR_MIN
#    include <stdintForVS2008.h> // using a copy of VS2010 stdint.h here
#else
#    include <stdint.h>
#endif

#ifdef _WIN32
#    if _MSC_VER <= 1910
#        pragma warning(disable : 4290)
#        pragma warning(disable : 4996)
#    endif
#endif // _WIN32

#if WIN32
#    ifdef IBEOSDKLIBDLL_EXPORTS
#        define IBEOSDKLIBDLL_API __declspec(dllexport)
#    else
#        define IBEOSDKLIBDLL_API __declspec(dllimport)
#    endif
#endif // WIN32

//==============================================================================

#include <fstream>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

#if defined(_MSC_VER) & _MSC_VER < 1700 // begin: VS up to 2010
inline int64_t streamposToInt64(const std::streampos& streampos)
{
    // MSVC has a 64 bit file size, but accessible only through
    // the non-standard std::fpos::seekpos() method.
    // still visual studio 2010 does not calculate right size by itself
    const int64_t pos64 = streampos.seekpos() + std::streamoff(streampos) - _FPOSOFF(streampos.seekpos());

    return pos64;
}
#else // end: VS up to 2010; begin: VS from 2012 and linux
inline int64_t streamposToInt64(const std::streampos& streampos) { return std::streamoff(streampos); }
#endif // begin: VS from 2012 and linux

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

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
//! \date Mar 7, 2014
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#ifdef __GNUC__
#    ifndef __GNUC_PREREQ
/* Mingw has gcc but not this particular version check (huh?!?) */
#        define __GNUC_PREREQ(a, b) 1
#    endif
#    if __GNUC_PREREQ(3, 0)
/* The "deprecated" attribute is only available in gcc >= 3.0.x */
#        define IBEOSDK_DEPRECATED __attribute__((deprecated))
#        define ALLOW_WARNINGS_BEGIN _Pragma("GCC diagnostic push")
#        define ALLOW_WARNINGS_END _Pragma("GCC diagnostic pop")
#        define ALLOW_WARNING_DEPRECATED _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#    else
#        define IBEOSDK_DEPRECATED
#        define ALLOW_WARNING_DEPRECATED
#    endif
#else /* __GNUC__ */
/* Non-gcc compiler */
#    ifdef _MSC_VER
#        define IBEOSDK_DEPRECATED __declspec(deprecated)
#        define ALLOW_WARNINGS_BEGIN __pragma(warning(push))
#        define ALLOW_WARNINGS_END __pragma(warning(pop))
#        define ALLOW_WARNING_DEPRECATED __pragma(warning(disable : 4995)) __pragma(warning(disable : 4996))
//          4995: name was marked as #pragma deprecated
//          4996: __declspec(deprecated)
#    else
#        define IBEOSDK_DEPRECATED
#        define ALLOW_WARNING_DEPRECATED
#    endif
#endif /* __GNUC__ */

//==============================================================================

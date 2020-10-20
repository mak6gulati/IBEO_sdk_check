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
//! \date April 4, 2012
//!
//! Ibeo SDK main header file
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/misc/Version.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class IbeoSdk
{
public:
    IbeoSdk() {}
    virtual ~IbeoSdk() {}

    static const Version& getVersion();
}; // IbeoSdk

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

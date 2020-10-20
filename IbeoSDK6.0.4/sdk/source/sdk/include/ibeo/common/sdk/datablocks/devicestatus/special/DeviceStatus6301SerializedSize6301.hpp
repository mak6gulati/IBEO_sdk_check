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
//! \date Jan 30, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class DeviceStatus6301SerializedSize6301
{
public:
    static std::streamsize getSerializedSize(const DeviceStatus6301& ds);
    static std::streamsize getSerializedSize(const SerialNumberIn6301& sn);
    static std::streamsize getSerializedSize(const Version448In6301& version);
}; // DeviceStatus6301SerializedSize6301

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

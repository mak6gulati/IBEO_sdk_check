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

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class DeviceStatus6303SerializedSize6303
{
public:
    static std::streamsize getSerializedSize(const DeviceStatus6303& ds);
    static std::streamsize getSerializedSize(const SerialNumberIn6303& sn);
    static std::streamsize getSerializedSize(const Version448In6303& version);
}; // DeviceStatus6303SerializedSize6303

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

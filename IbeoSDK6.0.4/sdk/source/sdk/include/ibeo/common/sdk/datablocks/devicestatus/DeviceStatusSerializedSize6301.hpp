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

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatus.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class DeviceStatusSerializedSize6301
{
public:
    static std::streamsize getSerializedSize(const DeviceStatus& ds);
    static std::streamsize getSerializedSize(const SerialNumber& sn);
    static std::streamsize getSerializedSize(const Version448& version);
}; // DeviceStatus6301SerializedSize6301

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

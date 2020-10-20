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
//! \date Jan 20, 2014
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <string>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

inline uint16_t getPort(std::string& ip, const uint16_t defaultPort = 0)
{
    const size_t portPos = ip.find(':');
    uint16_t port        = defaultPort;
    if (portPos != std::string::npos)
    {
        std::string portStr = ip.substr(portPos + 1);
        std::stringstream ss;
        ss.str(portStr);
        ss >> port;
        ip = ip.substr(0, portPos);
    }

    return port;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

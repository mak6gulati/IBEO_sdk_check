//==============================================================================
//!\file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 23, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <exception>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class ContainerMismatch : public std::exception
{
public:
    virtual const char* what() const noexcept override { return msg; }

public:
    static constexpr const char* msg{"ContainerMismatch: Dynamic container casting failed."};
}; // ContainerMismatch

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

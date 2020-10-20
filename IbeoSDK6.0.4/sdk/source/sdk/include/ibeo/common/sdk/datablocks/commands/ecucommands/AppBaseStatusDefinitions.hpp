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
//! \date Apr 10, 2015
//------------------------------------------------------------------------------
#pragma once

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class AppBaseStatusDefinitions
{
public:
    enum class AppBaseStatusId : uint8_t
    {
        Recording = 0x01
    };
}; // AppBaseStatusDefinitions

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

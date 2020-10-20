//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Mar 14, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/idctrailer/IdcTrailer6120.hpp>

#include "common/TestSupport.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class IdcTrailer6120TestSupport : public TestSupport
{
public:
    IdcTrailer6120TestSupport()          = default;
    virtual ~IdcTrailer6120TestSupport() = default;

public:
    static IdcTrailer6120 createIdcTrailer();

protected:
    static const int32_t nbOfRepeats = 1;
}; // FrameIndex6130TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

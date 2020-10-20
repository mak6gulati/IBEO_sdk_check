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
//! \date Sep 17, 2015
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/scan/special/ScanPointIn2310.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

const uint16_t ScanPointIn2310::blockId = 0xF030U;

//==============================================================================

ScanPointIn2310::ScanPointIn2310() : ScanPointBaseIn2310() {}

//==============================================================================

ScanPointIn2310::~ScanPointIn2310() {}

//==============================================================================

bool ScanPointIn2310::operator==(const ScanPointIn2310& other) const
{
    return (static_cast<const ScanPointBaseIn2310&>(*this) == static_cast<const ScanPointBaseIn2310&>(other));
}

//==============================================================================

bool ScanPointIn2310::operator!=(const ScanPointIn2310& other) const
{
    return (static_cast<const ScanPointBaseIn2310&>(*this) != static_cast<const ScanPointBaseIn2310&>(other));
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

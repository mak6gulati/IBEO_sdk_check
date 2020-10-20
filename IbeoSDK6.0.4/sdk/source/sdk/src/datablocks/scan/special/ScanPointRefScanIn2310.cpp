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

#include <ibeo/common/sdk/datablocks/scan/special/ScanPointRefScanIn2310.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

const uint16_t ScanPointRefScanIn2310::blockId = 0xF060U;

//==============================================================================

ScanPointRefScanIn2310::ScanPointRefScanIn2310() : ScanPointBaseIn2310() {}

//==============================================================================

ScanPointRefScanIn2310::~ScanPointRefScanIn2310() {}

//==============================================================================

bool ScanPointRefScanIn2310::operator==(const ScanPointRefScanIn2310& other) const
{
    return (static_cast<const ScanPointBaseIn2310&>(*this) == static_cast<const ScanPointBaseIn2310&>(other));
}

//==============================================================================

bool ScanPointRefScanIn2310::operator!=(const ScanPointRefScanIn2310& other) const
{
    return (static_cast<const ScanPointBaseIn2310&>(*this) != static_cast<const ScanPointBaseIn2310&>(other));
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

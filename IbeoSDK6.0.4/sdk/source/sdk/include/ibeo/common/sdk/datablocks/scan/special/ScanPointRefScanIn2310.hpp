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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/ScanPointBaseIn2310.hpp>

#include <ibeo/common/sdk/misc/deprecatedwarning.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class IBEOSDK_API ScanPointRefScanIn2310 : public ScanPointBaseIn2310
{
public:
    ScanPointRefScanIn2310();
    virtual ~ScanPointRefScanIn2310();

public:
    //! Equality predicate
    bool operator==(const ScanPointRefScanIn2310& other) const;
    bool operator!=(const ScanPointRefScanIn2310& other) const;

public:
    virtual uint16_t getBlockId() const override { return blockId; }

public:
    static const uint16_t blockId;
}; // ScanPointRefScanIn2310

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

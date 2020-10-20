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

#include <istream>
#include <ostream>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class IBEOSDK_API ScanPointDiagPulseIn2310 : public ScanPointBaseIn2310
{
public:
    ScanPointDiagPulseIn2310();
    virtual ~ScanPointDiagPulseIn2310();

public:
    //! Equality predicate
    bool operator==(const ScanPointDiagPulseIn2310& other) const;
    bool operator!=(const ScanPointDiagPulseIn2310& other) const;

public:
    virtual uint16_t getBlockId() const override { return blockId; }

public:
    IBEOSDK_DEPRECATED uint8_t getChannelID() const { return m_channelId; }
    IBEOSDK_DEPRECATED uint8_t getEchoID() const { return m_echoId; }

public:
    IBEOSDK_DEPRECATED void setChannelID(const uint8_t id) { m_channelId = id; }
    IBEOSDK_DEPRECATED void setEchoID(const uint8_t id) { m_echoId = id; }

public:
    static const uint16_t blockId;
}; // ScanPointDiagPulseIn2310

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

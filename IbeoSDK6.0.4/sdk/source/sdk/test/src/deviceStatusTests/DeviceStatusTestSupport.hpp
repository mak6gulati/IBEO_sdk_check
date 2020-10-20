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

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/devicestatus/DeviceStatus.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6301.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303.hpp>
#include <ibeo/common/sdk/datablocks/devicestatus/special/AdaptiveApdVoltageAndNoiseInfoIn6303.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class DeviceStatusTestSupport : public TestSupport
{
public:
    DeviceStatusTestSupport() : TestSupport() {}
    virtual ~DeviceStatusTestSupport() = default;

protected:
    static DeviceStatus6303::ContentId random6303ContentType();

protected:
    //========================================
    //!\brief Fill a DeviceStatus instance with random values.
    //!\param[out] ds               The DeviceStatus to be filled.
    //----------------------------------------
    static void fillRandomly(DeviceStatus& ds);

    //========================================
    //!\brief Fill a DeviceStatus6301 instance with random values.
    //!\param[out] ds               The DeviceStatus6301 to be filled.
    //----------------------------------------
    static void fillRandomly(DeviceStatus6301& ds);

    //========================================
    //!\brief Fill a DeviceStatus6303 instance with random values.
    //!\param[out] ds               The DeviceStatus6303 to be filled.
    //!\param[in]  allowReordering  For some tests the content has to
    //!                             be reordered. This can also change
    //!                             the number of the needed padding
    //!                             bytes to keep the entries aligned.
    //!                             Setting \a allowReordering makes
    //!                             sure enough bytes remain unused so
    //!                             that a reordering will not exceed
    //!                             the buffer limit in the DeviceStatus6303
    //!                             instance where the content elements
    //!                             are copied to.
    //----------------------------------------
    static void fillRandomly(DeviceStatus6303& ds, const bool allowReordering);

    static SerialNumber createSerialNumber();
    static void fillRandomly(SerialNumber& sn);

    static Version448 createVersion448();
    static void fillRandomly(Version448& v);

    static bool create6303UserDefinedContentEntry(DeviceStatus6303& ds,
                                                  const DeviceStatus6303::ContentId cId,
                                                  std::size_t& freeBuf);

    static bool create6303ContentEntry(DeviceStatus6303& ds,
                                       const DeviceStatus6303::ContentId cId,
                                       std::size_t& freeBuf,
                                       const uint8_t worstCasePadding,
                                       char* const buf);

    static void fillRandomly(AdaptiveApdVoltageAndNoiseInfoIn6303& avt);
    static void fillRandomly(AdaptiveApdVoltageAndNoiseInfoIn6303::ApdSector& sector);

protected:
    static const int32_t nbOfRepeats = 100;
}; // DeviceStatusTestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

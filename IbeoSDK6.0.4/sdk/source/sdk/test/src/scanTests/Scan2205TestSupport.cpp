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
//!\date June 14, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "Scan2205TestSupport.hpp"
#include <math.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

template<>
void ScanTestSupport::fillRandomly(Scan2205& scan)
{
    scan.setStartTimestamp(getRandValue<NTPTime>());
    scan.setEndTimeOffset(getRandValue<uint32_t>());
    scan.setFlags(getRandValue<uint32_t>());
    scan.setScanNumber(getRandValue<uint16_t>());
    scan.setReserved0(getRandValue<uint8_t>());
    scan.setReserved1(getRandValue<uint16_t>());

    scan.setScannerInfos(getRandValue<Scan2205::ScannerInfoVector>());
    scan.setScanPoints(getRandValue<Scan2205::ScanPointVector>());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

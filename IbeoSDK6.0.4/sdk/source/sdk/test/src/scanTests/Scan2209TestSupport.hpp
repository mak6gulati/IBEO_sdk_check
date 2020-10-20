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
//!\date March 23, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <scanTests/ScanTestSupport.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2209.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/ScannerInfoIn2209.hpp>

#include <vector>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class Scan2209TestSupport : public ScanTestSupport
{
public:
    Scan2209TestSupport() : ScanTestSupport() {}

    virtual ~Scan2209TestSupport() = default;

}; // Scan2209TestSupport

//==============================================================================

template<>
void ScanTestSupport::fillRandomly(Scan2209& scan);

// !!!!!!!!!!!!!!!!!!!!!!!!!!
// - following 2 methods -> same as for basis class atm (see "scan.hpp")
// !!!!!!!!!!!!!!!!!!!!!!!!!!
//template<>
//Scan2209::ScannerInfoVector TestSupport::getRandValue();
//
//template<>
//Scan2209::ScanPointVector TestSupport::getRandValue();

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

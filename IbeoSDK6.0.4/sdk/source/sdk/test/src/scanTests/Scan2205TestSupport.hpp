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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <scanTests/ScanTestSupport.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2205.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/ScannerInfoIn2205.hpp>

#include <vector>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class Scan2205TestSupport : public ScanTestSupport
{
public:
    Scan2205TestSupport() : ScanTestSupport() {}

    virtual ~Scan2205TestSupport() = default;

}; // Scan2205TestSupport

//==============================================================================

template<>
void ScanTestSupport::fillRandomly(Scan2205& scan);

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

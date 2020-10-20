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

#include <ibeo/common/sdk/datablocks/scan/special/Scan2202.hpp>

#include <boost/filesystem.hpp>

#include <vector>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class Scan2202TestSupport : public ScanTestSupport
{
public:
    Scan2202TestSupport() : ScanTestSupport() {}

    virtual ~Scan2202TestSupport() = default;

}; // Scan2202TestSupport

//==============================================================================

template<>
void ScanTestSupport::fillRandomly(Scan2202& scan);

template<>
ScanPointIn2202 TestSupport::getRandValue();

template<>
std::vector<ScanPointIn2202> TestSupport::getRandValue();

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

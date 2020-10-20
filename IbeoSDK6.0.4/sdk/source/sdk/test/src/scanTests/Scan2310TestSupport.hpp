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
//!\date Mar 19, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/scan/special/Scan2310.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class Scan2310TestSupport : public TestSupport
{
public:
    Scan2310TestSupport();
    virtual ~Scan2310TestSupport();

public:
    static ibeo::common::sdk::Scan2310 createScan2310();

private:
    static void fillRandomly(Scan2310& sfrd);

    static void fillRandomly(ScanHeaderIn2310& header);
    static void fillRandomly(ScanInfoIn2310& info);

    static void fillRandomly(std::vector<ScanPointIn2310>& pointVector);
    static void fillRandomly(std::vector<ScanSegInfoIn2310>& segInfoVector);
    static void fillRandomly(std::vector<ScanPointDiagPulseIn2310>& diagPulseVector);
    static void fillRandomly(std::vector<ScanPointRefScanIn2310>& refScanVector);

    static void fillRandomly(ScanTrailerIn2310& trailer);

    static void fillRandomly(ScanPointBaseIn2310& spb);

protected:
    static const int32_t nbOfRepeats = 100;
}; // Scan2310TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

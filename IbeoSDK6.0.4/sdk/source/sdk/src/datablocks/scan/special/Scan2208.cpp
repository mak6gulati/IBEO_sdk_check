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
//! \date Jan 14, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/scan/special/Scan2208.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

Scan2208::Scan2208() : SpecializedDataContainer() {}

//==============================================================================

Scan2208::~Scan2208() {}

//==============================================================================

bool operator==(const Scan2208& lhs, const Scan2208& rhs)
{
    bool eq = lhs.getScanNumber() == rhs.getScanNumber() && lhs.getScannerType() == rhs.getScannerType()
              && lhs.getScannerStatus() == rhs.getScannerStatus()
              && lhs.getAngleTicksPerRotation() == rhs.getAngleTicksPerRotation()
              && lhs.getProcessingFlags() == rhs.getProcessingFlags()
              && lhs.getMountingPosition() == rhs.getMountingPosition();

    if (!eq)
        return false;

    for (uint8_t t = 0; t < Scan2208::nbOfThresholds; ++t)
    {
        eq &= lhs.getThreshold(t) == rhs.getThreshold(t);
    }

    if (!eq)
        return false;

    for (uint8_t r = 0; r < Scan2208::nbOfReserved; ++r)
    {
        eq &= lhs.getReserved(r) == rhs.getReserved(r);
    }

    eq &= lhs.getDeviceId() == rhs.getDeviceId();
    eq &= lhs.getNbOfSubScans() == rhs.getNbOfSubScans();

    if (!eq)
        return false;

    for (uint_fast8_t ss = 0; ss < lhs.getNbOfSubScans(); ++ss)
    {
        if (lhs.getSubScans().at(ss) != rhs.getSubScans().at(ss))
            return false;
    } // for ss
    return true;
}

//==============================================================================

bool operator!=(const Scan2208& lhs, const Scan2208& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

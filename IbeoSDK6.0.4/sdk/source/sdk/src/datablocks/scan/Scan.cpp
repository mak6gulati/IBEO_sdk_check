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

#include <ibeo/common/sdk/datablocks/scan/Scan.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

Scan::Scan() : DataContainerBase() {}

//==============================================================================
//==============================================================================

bool operator==(const Scan& lhs, const Scan& rhs)
{
    if (lhs.getStartTimestamp() != rhs.getStartTimestamp())
        return false;

    if (lhs.getEndTimeOffset() != rhs.getEndTimeOffset())
        return false;

    if (lhs.getFlags() != rhs.getFlags())
        return false;

    if (lhs.getScanNumber() != rhs.getScanNumber())
        return false;

    if (lhs.getReserved0() != rhs.getReserved0())
        return false;

    if (lhs.getReserved1() != rhs.getReserved1())
        return false;

    if (lhs.getScannerInfos().size() != rhs.getScannerInfos().size())
        return false;

    for (size_t scannerInfoIdx = 0; scannerInfoIdx < lhs.getScannerInfos().size(); ++scannerInfoIdx)
    {
        if (lhs.getScannerInfos()[scannerInfoIdx] != (rhs.getScannerInfos())[scannerInfoIdx])
            return false;
    }

    if (lhs.getScanPoints().size() != rhs.getScanPoints().size())
        return false;

    for (size_t scanPointIdx = 0; scanPointIdx < lhs.getScanPoints().size(); ++scanPointIdx)
    {
        if (lhs.getScanPoints()[scanPointIdx] != rhs.getScanPoints()[scanPointIdx])
            return false;
    }

    return true;
}

//==============================================================================

bool operator!=(const Scan& lhs, const Scan& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
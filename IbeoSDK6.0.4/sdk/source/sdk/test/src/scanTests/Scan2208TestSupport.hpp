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

#include <ibeo/common/sdk/datablocks/scan/special/Scan2208.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/SubScanIn2208.hpp>

#include <ibeo/common/sdk/datablocks/MountingPosition.hpp>

#include <vector>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class Scan2208TestSupport : public ScanTestSupport
{
public:
    Scan2208TestSupport() : ScanTestSupport() {}

    virtual ~Scan2208TestSupport() = default;

    template<typename T>
    MountingPosition<T> getRandMountingPosition()
    {
        MountingPosition<T> mp;
        mp.setYaw(getDifferentRandValue<T>(std::numeric_limits<T>::max(), mp.getYaw()));
        mp.setPitch(getDifferentRandValue<T>(std::numeric_limits<T>::max(), mp.getPitch()));
        mp.setRoll(getDifferentRandValue<T>(std::numeric_limits<T>::max(), mp.getRoll()));
        mp.setX(getDifferentRandValue<T>(std::numeric_limits<T>::max(), mp.getX()));
        mp.setY(getDifferentRandValue<T>(std::numeric_limits<T>::max(), mp.getY()));
        mp.setZ(getDifferentRandValue<T>(std::numeric_limits<T>::max(), mp.getZ()));

        return mp;
    }
}; // Scan2208TestSupport

//==============================================================================

template<>

void ScanTestSupport::fillRandomly(Scan2208& scan);

template<>
SubScanIn2208::PointVector TestSupport::getRandValue();

template<>
SubScanIn2208 TestSupport::getRandValue();

template<>
Scan2208::SubScanVector TestSupport::getRandValue();

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

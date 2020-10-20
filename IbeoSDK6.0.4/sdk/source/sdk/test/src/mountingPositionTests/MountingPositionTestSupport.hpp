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
//! \date Jan 12, 2018
//------------------------------------------------------------------------------
//==============================================================================

#pragma once

#include "common/TestSupport.hpp"
#include "common/VectorTestSupport.hpp"
#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <ibeo/common/sdk/datablocks/MountingPosition.hpp>
#include <ibeo/common/sdk/Vector3.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class MountingPositionTestSupport : public TestSupport
{
public:
    MountingPositionTestSupport() {}
    virtual ~MountingPositionTestSupport() {}

public:
    template<typename T>
    static ibeo::common::sdk::MountingPosition<T> createMountingPosition()
    {
        ibeo::common::sdk::MountingPosition<T> v;
        fillRandomly(v);
        return v;
    }

private:
    template<typename T>
    static void fillRandomly(ibeo::common::sdk::MountingPosition<T>& mp)
    {
        auto rotation = VectorTestSupport::createVector3<T>();
        auto position = VectorTestSupport::createVector3<T>();
        mp            = MountingPosition<T>{rotation, position};
    }

protected:
    static const int32_t nbOfRepeats = 100;
}; // MountingPositionTestSupport

//==============================================================================

} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

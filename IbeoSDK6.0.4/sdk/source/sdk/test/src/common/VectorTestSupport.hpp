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

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "TestSupport.hpp"

#include <ibeo/common/sdk/Vector2.hpp>
#include <ibeo/common/sdk/Vector3.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class VectorTestSupport : public TestSupport
{
public:
    VectorTestSupport()          = default;
    virtual ~VectorTestSupport() = default;

public:
    template<typename T>
    static ibeo::common::sdk::Vector2<T> createVector2()
    {
        ibeo::common::sdk::Vector2<T> v;
        fillRandomly(v);
        return v;
    }

    template<typename T>
    static ibeo::common::sdk::Vector3<T> createVector3()
    {
        ibeo::common::sdk::Vector3<T> v;
        fillRandomly(v);
        return v;
    }

    template<typename T>
    static T getRand()
    {
        T max = static_cast<T>(RAND_MAX / 100);
        T rnd = static_cast<T>(rand());

        return static_cast<T>(rnd / max);
    }

private:
    template<typename T>
    static void fillRandomly(ibeo::common::sdk::Vector2<T>& vector)
    {
        T v1   = getRand<T>();
        T v2   = getRand<T>();
        vector = Vector2<T>{v1, v2};
    }

    template<typename T>
    static void fillRandomly(ibeo::common::sdk::Vector3<T>& vector)
    {
        T v1   = getRand<T>();
        T v2   = getRand<T>();
        T v3   = getRand<T>();
        vector = Vector3<T>{v1, v2, v3};
    }

protected:
    static const int32_t nbOfRepeats = 100;
}; // Vector2TestSupport

//==============================================================================

} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

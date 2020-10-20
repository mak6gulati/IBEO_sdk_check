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

#include "VectorTestSupport.hpp"
#include "TestSupport.hpp"

#include <ibeo/common/sdk/Matrix2x2.hpp>
#include <ibeo/common/sdk/Matrix3x3.hpp>
#include <ibeo/common/sdk/RotationMatrix2d.hpp>
#include <ibeo/common/sdk/RotationMatrix3d.hpp>
#include <ibeo/common/sdk/TransformationMatrix2d.hpp>
#include <ibeo/common/sdk/TransformationMatrix3d.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class MatrixTestSupport : public TestSupport
{
public:
    MatrixTestSupport() {}
    virtual ~MatrixTestSupport() {}

public:
    template<typename T>
    static ibeo::common::sdk::Matrix2x2<T> createMatrix2x2()
    {
        ibeo::common::sdk::Matrix2x2<T> v;
        fillRandomly(v);
        return v;
    }

    template<typename T>
    static ibeo::common::sdk::RotationMatrix2d<T> createRotationMatrix2d()
    {
        ibeo::common::sdk::RotationMatrix2d<T> v;
        fillRandomly(v);
        return v;
    }

    template<typename T>
    static ibeo::common::sdk::TransformationMatrix2d<T> createTransformationMatrix2d()
    {
        ibeo::common::sdk::TransformationMatrix2d<T> v;
        fillRandomly(v);
        return v;
    }

    template<typename T>
    static ibeo::common::sdk::Matrix3x3<T> createMatrix3x3()
    {
        ibeo::common::sdk::Matrix3x3<T> v;
        fillRandomly(v);
        return v;
    }

    template<typename T>
    static ibeo::common::sdk::RotationMatrix3d<T> createRotationMatrix3d()
    {
        ibeo::common::sdk::RotationMatrix3d<T> v;
        fillRandomly(v);
        return v;
    }

    template<typename T>
    static ibeo::common::sdk::TransformationMatrix3d<T> createTransformationMatrix3d()
    {
        ibeo::common::sdk::TransformationMatrix3d<T> v;
        fillRandomly(v);
        return v;
    }

private:
    template<typename T>
    static void fillRandomly(ibeo::common::sdk::Matrix2x2<T>& matrix)
    {
        matrix = Matrix2x2<T>{getRand<T>(), getRand<T>(), getRand<T>(), getRand<T>()};
    }

    template<typename T>
    static void fillRandomly(ibeo::common::sdk::RotationMatrix2d<T>& matrix)
    {
        matrix = RotationMatrix2d<T>{getRand<T>()};
    }

    template<typename T>
    static void fillRandomly(ibeo::common::sdk::TransformationMatrix2d<T>& matrix)
    {
        auto m = createRotationMatrix2d<T>();
        auto p = VectorTestSupport::createVector2<T>();

        matrix = ibeo::common::sdk::TransformationMatrix2d<T>{m, p};
    }

    template<typename T>
    static void fillRandomly(ibeo::common::sdk::Matrix3x3<T>& matrix)
    {
        matrix = Matrix3x3<T>{getRand<T>(),
                              getRand<T>(),
                              getRand<T>(),
                              getRand<T>(),
                              getRand<T>(),
                              getRand<T>(),
                              getRand<T>(),
                              getRand<T>(),
                              getRand<T>()};
    }

    template<typename T>
    static void fillRandomly(ibeo::common::sdk::RotationMatrix3d<T>& matrix)
    {
        auto axis      = VectorTestSupport::createVector3<T>();
        auto alignment = VectorTestSupport::createVector3<T>();

        matrix = RotationMatrix3d<T>{axis, alignment};
    }

    template<typename T>
    static void fillRandomly(ibeo::common::sdk::TransformationMatrix3d<T>& matrix)
    {
        auto m = createRotationMatrix3d<T>();
        auto p = VectorTestSupport::createVector3<T>();

        matrix = TransformationMatrix3d<T>{m, p};
    }

    template<typename T>
    static T getRand()
    {
        return VectorTestSupport::getRand<T>();
    }

public:
    static const uint32_t nbOfRepeats = 100;
}; // Vector2TestSupport

//==============================================================================

} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

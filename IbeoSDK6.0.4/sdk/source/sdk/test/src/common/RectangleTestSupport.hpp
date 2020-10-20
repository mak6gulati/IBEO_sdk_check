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
#include "VectorTestSupport.hpp"

#include <include/ibeo/common/sdk/Rectangle.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

class RectangleTestSupport : public TestSupport
{
public:
    RectangleTestSupport() {}
    virtual ~RectangleTestSupport() {}

public:
    template<typename T>
    static ibeo::common::sdk::Rectangle<T> createRectangle()
    {
        ibeo::common::sdk::Rectangle<T> v;
        fillRandomly(v);
        return v;
    }

private:
    template<typename T>
    static void fillRandomly(ibeo::common::sdk::Rectangle<T>& rect)
    {
        auto center   = VectorTestSupport::createVector2<T>();
        auto size     = VectorTestSupport::createVector2<T>();
        auto rotation = static_cast<T>(rand() / 10);
        rect          = Rectangle<T>{center, size, rotation};
    }

protected:
    static const int32_t nbOfRepeats = 100;
}; // RectangleTestSupport

//==============================================================================

} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

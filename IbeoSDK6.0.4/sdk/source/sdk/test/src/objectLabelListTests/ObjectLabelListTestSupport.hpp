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
//! \date Jan 25, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectlabellist/ObjectLabelList.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
using Uoid = uint64_t;
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class ObjectLabelListTestSupport : public TestSupport
{
public:
    ObjectLabelListTestSupport();
    virtual ~ObjectLabelListTestSupport();

public:
    static ibeo::common::sdk::ObjectLabelList createObjectLabelList();

    static ibeo::common::sdk::ObjectLabel createObjectLabel();

private:
    static void fillRandomly(ibeo::common::sdk::ObjectLabelList& oll);

    static void fillRandomly(ibeo::common::sdk::ObjectLabel& ol);

    static void fillRandomly(ibeo::common::sdk::MeasurementList& ml);

protected:
    static const int32_t nbOfRepeats = 1;

}; // ObjectLabelListTestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

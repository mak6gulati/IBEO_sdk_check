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
//!\date Apr 28, 2016
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectlabellist/special/ObjectLabelList6503.hpp>

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

class ObjectLabelList6503TestSupport : public TestSupport
{
public:
    ObjectLabelList6503TestSupport();
    virtual ~ObjectLabelList6503TestSupport();

public:
    static ibeo::common::sdk::ObjectLabelList6503 createObjectLabelList6503();

    static ibeo::common::sdk::ObjectLabelIn6503 createObjectLabel6503();

private:
    static void fillRandomly(ibeo::common::sdk::ObjectLabelList6503& oll);

    static void fillRandomly(ibeo::common::sdk::ObjectLabelIn6503& ol);

    static void fillRandomly(ibeo::common::sdk::MeasurementList& ml);

protected:
    static const int32_t nbOfRepeats = 1;

}; // ObjectLabelList6503TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date October 11, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/stateofoperation/StateOfOperation9110.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class StateOfOperation9110TestSupport : public TestSupport
{
public:
    StateOfOperation9110TestSupport();
    virtual ~StateOfOperation9110TestSupport();

public:
    static StateOfOperation9110 createStateOfOperation9110C();

private:
    static void fillRandomly(ibeo::common::sdk::StateOfOperation9110& od);

protected:
    static const int32_t nbOfRepeats = 100;
}; //StateOfOperation9110TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

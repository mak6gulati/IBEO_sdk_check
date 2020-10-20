//==============================================================================
//!\file
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date January 02, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/idsequence/IdSequence3500.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class IdSequence3500TestSupport : public TestSupport
{
public:
    IdSequence3500TestSupport();

    virtual ~IdSequence3500TestSupport() = default;

    static IdSequence3500 createIdSequence3500();

    static void fillRandomly3500(IdSequence3500& is);

protected:
    static const int32_t nbOfRepeats = 100;
}; //IdSequence3500TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

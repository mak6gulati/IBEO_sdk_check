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
//!\date Semptember 25, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <common/TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/ibeoevent/IbeoEvent7001.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class IbeoEvent7001TestSupport : public TestSupport
{
public:
    virtual ~IbeoEvent7001TestSupport() = default;

public:
    static IbeoEvent7001 createIbeoEvent7001();

private:
    static void fillRandomly(IbeoEvent7001& od);

protected:
    static const int32_t nbOfRepeats = 400;
}; // IbeoEvent7001TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

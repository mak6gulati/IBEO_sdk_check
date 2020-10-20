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
//!\date 15.November 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84Sequence.hpp>
#include <common/TestSupport.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class PositionWgs84SequenceTestSupport : public TestSupport
{
public:
    PositionWgs84SequenceTestSupport()           = default;
    ~PositionWgs84SequenceTestSupport() override = default;

public:
    static PositionWgs84Sequence createPositionWgs84Sequence();
    static PositionWgs84Sequence createPositionWgs84Sequence2604();
    static void fillRandomly(PositionWgs84Sequence& ps);
    static void fillPosRandomly(PositionWgs84& p);

protected:
    static const int32_t nbOfRepeats = 100;

}; //PositionWgs84SequenceTestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

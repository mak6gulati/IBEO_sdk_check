//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 15, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84_2604.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

PositionWgs84_2604::PositionWgs84_2604() : SpecializedDataContainer() {}

//==============================================================================

PositionWgs84_2604::~PositionWgs84_2604() {}

//==============================================================================

bool operator==(const PositionWgs84_2604& lhs, const PositionWgs84_2604& rhs)
{
    return (lhs.getPosition() == rhs.getPosition());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date 14.November 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84Sequence.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

PositionWgs84Sequence::PositionWgs84Sequence() : DataContainerBase() {}

//==============================================================================

bool operator==(const PositionWgs84Sequence& lhs, const PositionWgs84Sequence& rhs)
{
    if ((lhs.getTimestamp() != rhs.getTimestamp()) || (lhs.getSourceType() != rhs.getSourceType())
        || (lhs.getId() != rhs.getId()) || (lhs.getReserved() != rhs.getReserved())
        || (lhs.getPositionSequence() != rhs.getPositionSequence()))
    {
        return false;
    }

    return true;
}

//==============================================================================

bool operator!=(const PositionWgs84Sequence& lhs, const PositionWgs84Sequence& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

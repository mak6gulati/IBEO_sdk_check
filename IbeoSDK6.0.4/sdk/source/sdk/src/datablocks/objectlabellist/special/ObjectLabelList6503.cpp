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
//!\date Jan 15, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectlabellist/special/ObjectLabelList6503.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

bool operator==(const ObjectLabelList6503& lhs, const ObjectLabelList6503& rhs)
{
    if (lhs.getTimeOffsetUs() != rhs.getTimeOffsetUs() || lhs.getTimestamp() != rhs.getTimestamp()
        || lhs.getScanNumber() != rhs.getScanNumber() || lhs.getScanMidTimestamp() != rhs.getScanMidTimestamp())
    {
        return false;
    }

    for (uint16_t r = 0; r < ObjectLabelList6503::nbOfReserved; ++r)
    {
        if (lhs.getReserved(r) != rhs.getReserved(r))
        {
            return false;
        }
    }

    if (lhs.getLabels() != rhs.getLabels())
    {
        return true;
    }

    return true;
}

//==============================================================================

bool operator!=(const ObjectLabelList6503& lhs, const ObjectLabelList6503& rhs)
{
    if (lhs.getTimeOffsetUs() != rhs.getTimeOffsetUs() || lhs.getTimestamp() != rhs.getTimestamp()
        || lhs.getScanNumber() != rhs.getScanNumber() || lhs.getScanMidTimestamp() != rhs.getScanMidTimestamp())
    {
        return true;
    }

    for (uint16_t r = 0; r < ObjectLabelList6503::nbOfReserved; ++r)
    {
        if (lhs.getReserved(r) != rhs.getReserved(r))
        {
            return true;
        }
    }

    if (lhs.getLabels() != rhs.getLabels())
    {
        return true;
    }

    return false;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

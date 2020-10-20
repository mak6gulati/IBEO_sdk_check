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
//!\date Sept 05, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/destination/Destination3520.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

Destination3520::Destination3520() : SpecializedDataContainer() {}

//==============================================================================

uint32_t Destination3520::getReserved(const uint_fast8_t idx) const { return m_reserved.at(idx); }

//==============================================================================

bool operator==(const Destination3520& lhs, const Destination3520& rhs)
{
    if ((lhs.getTargetPosition() != rhs.getTargetPosition()) || (lhs.getTargetId() != rhs.getTargetId())
        || (lhs.getTimestamp() != rhs.getTimestamp()) || (lhs.getSourceType() != rhs.getSourceType())
        || (lhs.getDestinationType() != rhs.getDestinationType()) || (lhs.getPurposeType() != rhs.getPurposeType())
        || (lhs.getId() != rhs.getId()))
    {
        return false;
    }

    for (uint_fast8_t i = 0; i < Destination3520::nbOfReserved; ++i)
    {
        if (lhs.getReserved(i) != rhs.getReserved(i))
        {
            return false;
        }
    }

    return true;
}

//==============================================================================

bool operator!=(const Destination3520& lhs, const Destination3520& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

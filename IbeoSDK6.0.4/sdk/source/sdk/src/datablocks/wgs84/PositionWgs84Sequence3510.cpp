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
//!\date Sept 03, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/wgs84/PositionWgs84Sequence3510.hpp>
#include <ibeo/common/sdk/DataBlockBufferProvider.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

PositionWgs84Sequence3510::PositionWgs84Sequence3510() : SpecializedDataContainer() {}

//==============================================================================

uint32_t PositionWgs84Sequence3510::getReserved(const uint_fast8_t idx) const { return m_reserved.at(idx); }

//==============================================================================

bool operator==(const PositionWgs84Sequence3510& lhs, const PositionWgs84Sequence3510& rhs)
{
    if ((lhs.getTimestamp() != rhs.getTimestamp()) || (lhs.getSourceType() != rhs.getSourceType())
        || (lhs.getId() != rhs.getId()))
    {
        return false;
    }

    for (uint_fast8_t i = 0; i < PositionWgs84Sequence3510::nbOfReserved; ++i)
    {
        if (lhs.getReserved(i) != rhs.getReserved(i))
        {
            return false;
        }
    }

    if (lhs.getPositionSequence().size() == rhs.getPositionSequence().size())
    {
        for (std::size_t i = 0; i < lhs.getPositionSequence().size(); ++i)
        {
            if (lhs.getPositionSequence().at(i) != rhs.getPositionSequence().at(i))
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

//==============================================================================

bool operator!=(const PositionWgs84Sequence3510& lhs, const PositionWgs84Sequence3510& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

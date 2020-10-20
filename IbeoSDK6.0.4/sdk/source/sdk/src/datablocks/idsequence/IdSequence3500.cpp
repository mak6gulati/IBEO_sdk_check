//==============================================================================
//! \file
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Sept 03, 2018
//!---------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/idsequence/IdSequence3500.hpp>
#include <ibeo/common/sdk/DataBlockBufferProvider.hpp>

namespace ibeo {
namespace common {
namespace sdk {

IdSequence3500::IdSequence3500() : m_idSequence(0), m_timestamp(), m_sourceType(SourceType::Unknown), m_id(0) {}

//==============================================================================

bool operator==(const IdSequence3500& is1, const IdSequence3500& is2)
{
    if ((is1.getIdSequence() != is2.getIdSequence()) || (is1.getTimestamp() != is2.getTimestamp())
        || (is1.getSourceType() != is2.getSourceType()) || (is1.getId() != is2.getId())
        || (is1.getReserved() != is2.getReserved()))
    {
        return false;
    }

    return true;
}

//==============================================================================

bool operator!=(const IdSequence3500& is1, const IdSequence3500& is2) { return !(is1 == is2); }

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

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
//!\date 08.November 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/idsequence/IdSequence.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

bool operator==(const IdSequence& is1, const IdSequence& is2)
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

bool operator!=(const IdSequence& is1, const IdSequence& is2) { return !(is1 == is2); }
//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

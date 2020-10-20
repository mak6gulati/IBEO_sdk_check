//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date May 05, 2016
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/commands/ecucommands/ReplyEcuSetFilter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ReplyEcuSetFilter::ReplyEcuSetFilter() {}

//==============================================================================

bool ReplyEcuSetFilter::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, m_commandId);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize())
           && this->getSerializedSize() == dh.getMessageSize();
}

//==============================================================================

bool ReplyEcuSetFilter::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, m_commandId);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

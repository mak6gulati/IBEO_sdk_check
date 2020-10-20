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
//! \date Apr 10, 2015
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/datablocks/commands/luxcommands/CommandLuxResetToDefaultParameters.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

CommandLuxResetToDefaultParameters::CommandLuxResetToDefaultParameters()
  : LuxCommand<CommandId::Id::CmdLuxResetDefaultParameters>(), m_reserved(0x0000)
{}

//==============================================================================

bool CommandLuxResetToDefaultParameters::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readLE(is, m_commandId);
    readLE(is, m_reserved);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize())
           && this->getSerializedSize() == dh.getMessageSize();
}

//==============================================================================

bool CommandLuxResetToDefaultParameters::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeLE(os, m_commandId);
    writeLE(os, m_reserved);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

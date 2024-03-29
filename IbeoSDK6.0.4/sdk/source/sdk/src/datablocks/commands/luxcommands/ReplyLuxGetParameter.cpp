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

#include <ibeo/common/sdk/datablocks/commands/luxcommands/ReplyLuxGetParameter.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

ReplyLuxGetParameter::ReplyLuxGetParameter()
  : LuxCommandReply<CommandId::Id::CmdLuxGetParameter>(),
    m_parameterIndex(ParameterIndex(0)),
    m_parameterData(ParameterData(0))
{}

//==============================================================================

bool ReplyLuxGetParameter::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readLE(is, m_commandId);
    m_parameterIndex.readLE(is);
    m_parameterData.readLE(is);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize())
           && this->getSerializedSize() == dh.getMessageSize();
}

//==============================================================================

bool ReplyLuxGetParameter::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeLE(os, m_commandId);
    m_parameterIndex.writeLE(os);
    m_parameterData.writeLE(os);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

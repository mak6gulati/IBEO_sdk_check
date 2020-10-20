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
//! \date Apr 8, 2015
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/datablocks/commands/ecucommands/ReplyEcuAppBaseStatus.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

static void readBE(std::istream& is, ReplyEcuAppBaseStatus::AppBaseStatusId& statusId)
{
    uint16_t tmp;
    readBE(is, tmp);
    statusId = ReplyEcuAppBaseStatus::AppBaseStatusId(tmp);
}

//==============================================================================

static void writeBE(std::ostream& os, const ReplyEcuAppBaseStatus::AppBaseStatusId statusId)
{
    writeBE(os, uint16_t(statusId));
}

//==============================================================================

ReplyEcuAppBaseStatus::ReplyEcuAppBaseStatus()
  : EcuCommandReply<CommandId::Id::CmdManagerAppBaseStatus>(),
    AppBaseStatusDefinitions(),
    m_statusId(AppBaseStatusId::Recording),
    m_data()
{}

//==============================================================================

bool ReplyEcuAppBaseStatus::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    m_commandId.readBE(is);
    readBE(is, m_statusId);

    is.unsetf(std::ios::skipws);
    std::istreambuf_iterator<char> eos;
    std::string s(std::istreambuf_iterator<char>(is), eos);
    is.setf(std::ios::skipws);
    this->m_data = s;

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize())
           && this->getSerializedSize() == dh.getMessageSize();
}

//==============================================================================

bool ReplyEcuAppBaseStatus::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    m_commandId.writeBE(os);
    writeBE(os, m_statusId);

    std::ostreambuf_iterator<char> strOut(os);
    copy(this->m_data.begin(), this->m_data.end(), strOut);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

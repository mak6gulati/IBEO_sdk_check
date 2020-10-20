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
//! \date Sep 5, 2013
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/CommandId.hpp>
#include <ibeo/common/sdk/DataTypeId.hpp>
#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
//! \class CommandReply
//! \brief Abstract base class for all CommandReply classes.
//! \date Sep 5, 2013
//!
//------------------------------------------------------------------------------
class CommandReplyBase
{
public:
    static const uint16_t errorMask = 0x8000;

public:
    //========================================
    //! \brief Create a Command object.
    //! \param[in] commandId      Id of the command.
    //-------------------------------------
    CommandReplyBase(const CommandId commandId) : m_commandId(commandId) {}

    virtual ~CommandReplyBase() {}

public:
    //========================================
    //! \brief Get the id of this Command.
    //! \return the id of this Command.
    //-------------------------------------
    CommandId getCommandId() const { return m_commandId; }

    virtual bool deserializeFromStream(std::istream& is, const IbeoDataHeader& dh) = 0;

public:
    bool isErrorReply() const { return (uint16_t(getCommandId()) & errorMask) != 0; }
    void setErrorReply() { m_commandId = CommandId(uint16_t(m_commandId) | errorMask); }
    void unsetErrorReply() { m_commandId = CommandId(uint16_t(uint16_t(m_commandId) & uint16_t(~errorMask))); }

protected:
    static const DataTypeId dataType;

protected:
    //========================================
    //! \brief The id of this Command.
    //-------------------------------------
    CommandId m_commandId;
}; // CommandReplyBase

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

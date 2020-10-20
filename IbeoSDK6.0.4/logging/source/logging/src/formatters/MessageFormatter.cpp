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
//! \date Oct 29, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/logging/formatters/MessageFormatter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

FormatterSPtr MessageFormatter::create(const FormatModifier& modifier, const std::list<std::string>& options)
{
    MessageFormatterSPtr formatter = MessageFormatterSPtr(new MessageFormatter());
    formatter->setModifier(modifier);

    return formatter;
}

//==============================================================================

std::string MessageFormatter::formatMessage(const std::string& loggerId, const LogLevel level, const MessageSPtr msg)
{
    return m_modifier.process(msg->getText());
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

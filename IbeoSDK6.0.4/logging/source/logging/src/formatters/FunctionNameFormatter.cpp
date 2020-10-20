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

#include <ibeo/common/logging/formatters/FunctionNameFormatter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

FormatterSPtr FunctionNameFormatter::create(const FormatModifier& modifier, const std::list<std::string>&)
{
    FunctionNameFormatterSPtr formatter = FunctionNameFormatterSPtr(new FunctionNameFormatter());
    formatter->setModifier(modifier);

    return formatter;
}

//==============================================================================

std::string
FunctionNameFormatter::formatMessage(const std::string& loggerId, const LogLevel level, const MessageSPtr msg)
{
    return m_modifier.process(msg->getFunction());
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

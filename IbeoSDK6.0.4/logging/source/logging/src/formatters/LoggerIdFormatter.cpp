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

#include <ibeo/common/logging/formatters/LoggerIdFormatter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

FormatterSPtr LoggerIdFormatter::create(const FormatModifier& modifier, const std::list<std::string>& options)
{
    LoggerIdFormatterSPtr formatter = LoggerIdFormatterSPtr(new LoggerIdFormatter());
    formatter->setModifier(modifier);
    formatter->storePrecisionFromOptions(options);

    return formatter;
}

//==============================================================================

std::string LoggerIdFormatter::formatMessage(const std::string& loggerId, const LogLevel level, const MessageSPtr msg)
{
    const std::string& loggerIdString = applyPrecision("::", loggerId);
    return m_modifier.process(loggerIdString);
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

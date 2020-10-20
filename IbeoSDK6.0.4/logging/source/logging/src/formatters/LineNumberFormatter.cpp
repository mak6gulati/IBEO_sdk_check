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

#include <ibeo/common/logging/formatters/LineNumberFormatter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

FormatterSPtr LineNumberFormatter::create(const FormatModifier& modifier, const std::list<std::string>&)
{
    LineNumberFormatterSPtr formatter = LineNumberFormatterSPtr(new LineNumberFormatter());
    formatter->setModifier(modifier);

    return formatter;
}

//==============================================================================

std::string LineNumberFormatter::formatMessage(const std::string& loggerId, const LogLevel level, const MessageSPtr msg)
{
    std::stringstream stream;
    stream << msg->getLineNo();
    return m_modifier.process(stream.str());
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

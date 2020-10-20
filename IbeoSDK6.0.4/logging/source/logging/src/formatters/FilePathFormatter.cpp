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

#include <ibeo/common/logging/formatters/FilePathFormatter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

FormatterSPtr FilePathFormatter::create(const FormatModifier& modifier, const std::list<std::string>& options)
{
    FilePathFormatterSPtr formatter = FilePathFormatterSPtr(new FilePathFormatter());
    formatter->setModifier(modifier);
    formatter->storePrecisionFromOptions(options);

    return formatter;
}

//==============================================================================

std::string FilePathFormatter::formatMessage(const std::string& loggerId, const LogLevel level, const MessageSPtr msg)
{
    const std::string& filePath = applyPrecision(std::string(1, pathSeparator), msg->getFile());
    return m_modifier.process(filePath);
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

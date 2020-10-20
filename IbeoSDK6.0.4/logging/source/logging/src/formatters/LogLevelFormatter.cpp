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

#include <ibeo/common/logging/formatters/LogLevelFormatter.hpp>

#include <string.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

FormatterSPtr LogLevelFormatter::create(const FormatModifier& modifier, const std::list<std::string>& options)
{
    static const std::string lengthOptionPrefix{"length="};
    static const std::string lowerCaseOptionPrefix{"lowerCase="};

    LogLevelFormatterSPtr formatter = LogLevelFormatterSPtr(new LogLevelFormatter());
    formatter->setModifier(modifier);

    for (const std::string& option : options)
    {
        if ((option.length() > lengthOptionPrefix.length()) && (option.find(lengthOptionPrefix) == 0))
        {
            // Length option.
            try
            {
                formatter->m_length = static_cast<uint32_t>(std::stoul(option.substr(lengthOptionPrefix.length())));
            }
            catch (const std::logic_error&)
            {
                // Not a number -> ignore error.
            }
        }
        else if ((option.length() > lowerCaseOptionPrefix.length()) && (option.find(lowerCaseOptionPrefix) == 0))
        {
            // Lower case option.
            if (option.find("true", lowerCaseOptionPrefix.length()) == lowerCaseOptionPrefix.length())
            {
                formatter->m_lowerCase = true;
            }
            else if (option.find("false", lowerCaseOptionPrefix.length()) == lowerCaseOptionPrefix.length())
            {
                formatter->m_lowerCase = false;
            }
            else
            {
                // Unknown lower case value -> ignore it.
            }
        }
        else
        {
            // Unknown option -> ignore it.
        }
    }

    return formatter;
}

//==============================================================================

std::string LogLevelFormatter::formatMessage(const std::string& loggerId, const LogLevel level, const MessageSPtr msg)
{
    std::string logLevelText{logLevelToString(level)};

    if (m_length < logLevelText.length())
    {
        // Cut text to length.
        logLevelText = logLevelText.substr(0, m_length);
    }

    if (m_lowerCase)
    {
        // Convert to lower case.
        for (char& c : logLevelText)
        {
            c = tolower(c);
        }
    }
    else
    {
        // Convert to upper case.
        for (char& c : logLevelText)
        {
            c = toupper(c);
        }
    }

    return m_modifier.process(logLevelText);
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

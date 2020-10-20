//==============================================================================
//!\file
//!\brief Formatting of the messages.
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Mar 15, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/logging/Format.hpp>

#include <ibeo/common/logging/formatters/DateFormatter.hpp>
#include <ibeo/common/logging/formatters/FilePathFormatter.hpp>
#include <ibeo/common/logging/formatters/FunctionNameFormatter.hpp>
#include <ibeo/common/logging/formatters/LineNumberFormatter.hpp>
#include <ibeo/common/logging/formatters/LoggerIdFormatter.hpp>
#include <ibeo/common/logging/formatters/LogLevelFormatter.hpp>
#include <ibeo/common/logging/formatters/MessageFormatter.hpp>
#include <ibeo/common/logging/formatters/PlainTextFormatter.hpp>
#include <ibeo/common/logging/formatters/SequenceNumberFormatter.hpp>
#include <ibeo/common/logging/formatters/ThreadIdFormatter.hpp>

#include <string.h>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

FormatSPtr Format::parse(const char* formatString)
{
    if ((formatString == nullptr) || (strlen(formatString) == 0))
    {
        // Use default format.
        return parse("[%level] %date{%Y-%m-%d %H-%M-%S,%s} - %file(%line) - %func: %msg%n");
    }

    FormatSPtr format = std::make_shared<Format>();

    // Split string into formatters.
    std::string formatStr{formatString};
    std::size_t pos{0};
    std::string plainText{};

    while ((pos != std::string::npos) && (pos < formatStr.length()))
    {
        std::size_t percentPos = formatStr.find('%', pos);
        if ((percentPos == std::string::npos) || (percentPos == formatStr.length() - 1))
        {
            // No more percent signs found or single percent sign at the end of the string
            // -> the rest of the format string is plain text.
            plainText.append(formatStr.substr(pos));

            // End of format string reached.
            break;
        }

        if (formatStr[percentPos + 1] == '%')
        {
            // Double percent sign found -> add single percent sign and continue searching.
            if (percentPos != pos)
            {
                // There is some text between the start position and the double percent sign.
                plainText.append(formatStr.substr(pos, percentPos - pos));
            }
            plainText.append("%");
            pos = percentPos + 2;

            continue;
        }

        else if (formatStr[percentPos + 1] == 'n')
        {
            // New line formatter found -> add new line and continue searching.
            plainText.append("\n");
            pos = percentPos + 2;
        }

        else if (percentPos != pos)
        {
            // There is some text between the start position and the next occurrence of the percent sign.
            plainText.append(formatStr.substr(pos, percentPos - pos));
            pos = percentPos;

            format->m_formatters.push_back(std::make_shared<PlainTextFormatter>(plainText));
            plainText.clear();
        }

        //else: no (more) plain text since last position.

        if (formatStr[pos] == '%')
        {
            // Start of conversion pattern found -> add collected plain text (if any).
            if (plainText.empty() == false)
            {
                format->m_formatters.push_back(std::make_shared<PlainTextFormatter>(plainText));
                plainText.clear();
            }

            // Next char.
            ++pos;

            // Parse format modifier (pos will be updated).
            FormatModifier formatModifier = FormatModifier::parse(formatStr, pos);

            // Get formatter for conversion pattern.
            std::string pattern{""};
            FormatterCreateFunction createFunction{nullptr};
            for (const FormatterFactoryMap::value_type& factoryPair : getFormatterFactory())
            {
                const std::string& key = factoryPair.first;
                if (formatStr.find(key, pos) == pos)
                {
                    // Potential conversion pattern found.
                    if (key.length() > pattern.length())
                    {
                        // This is the first or a better match -> use it.
                        pattern        = key;
                        createFunction = factoryPair.second;
                    }
                }
            }

            if (createFunction != nullptr)
            {
                // Conversion pattern found.
                pos += pattern.length();

                // Parse options (pos will be updated).
                std::list<std::string> formatterOptions = parseFormatterOptions(formatStr, pos);

                // Create formatter.
                FormatterSPtr formatter = createFunction(formatModifier, formatterOptions);
                format->m_formatters.push_back(formatter);
            }
            else
            {
                // No formatter for the given pattern found -> gracefully treat it as plain text and continue.
                plainText.append("%");
            }
        }
    }

    // Add remaining plain text (if any).
    if (plainText.empty() == false)
    {
        format->m_formatters.push_back(std::make_shared<PlainTextFormatter>(plainText));
        plainText.clear();
    }

    return format;
}

//==============================================================================

std::string Format::getFormattedText(const std::string& loggerId, const LogLevel level, const MessageSPtr msg)
{
    std::stringstream stream;

    for (const FormatterSPtr& formatter : m_formatters)
    {
        stream << formatter->formatMessage(loggerId, level, msg);
    }

    return stream.str();
}

//==============================================================================

std::list<std::string> Format::parseFormatterOptions(const std::string& formatStr, size_t& pos)
{
    std::list<std::string> options;

    while ((pos != std::string::npos) && (pos < formatStr.length()) && (formatStr[pos] == '{'))
    {
        // Begin of option found -> look for end.
        ++pos;
        std::size_t endPos = formatStr.find('}', pos);
        if (endPos == std::string::npos)
        {
            // No closing bracket found -> gracefully assume rest of string.
            endPos = formatStr.length();
        }

        options.push_back(formatStr.substr(pos, endPos - pos));
        pos = endPos + 1;
    }

    return options;
}

//==============================================================================

const Format::FormatterFactoryMap& Format::getFormatterFactory()
{
    static const FormatterFactoryMap formatterFactory{{std::string("date"), &DateFormatter::create},
                                                      {std::string("file"), &FilePathFormatter::create},
                                                      {std::string("func"), &FunctionNameFormatter::create},
                                                      {std::string("function"), &FunctionNameFormatter::create},
                                                      {std::string("level"), &LogLevelFormatter::create},
                                                      {std::string("line"), &LineNumberFormatter::create},
                                                      {std::string("logger"), &LoggerIdFormatter::create},
                                                      {std::string("msg"), &MessageFormatter::create},
                                                      {std::string("message"), &MessageFormatter::create},
                                                      {std::string("seqNo"), &SequenceNumberFormatter::create},
                                                      {std::string("sequenceNumber"), &SequenceNumberFormatter::create},
                                                      {std::string("thread"), &ThreadIdFormatter::create}};

    return formatterFactory;
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

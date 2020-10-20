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

#include <ibeo/common/logging/formatters/DateFormatter.hpp>

#include <iomanip>
#include <iostream>
#include <cstring>
#include <cmath>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

FormatterSPtr DateFormatter::create(const FormatModifier& modifier, const std::list<std::string>& options)
{
    DateFormatterSPtr formatter = DateFormatterSPtr(new DateFormatter());
    formatter->setModifier(modifier);

    if (options.empty())
    {
        formatter->m_formatString = "%x %X,%s";
    }
    else
    {
        const std::string& dateFormat = options.front();

        if (dateFormat == "DEFAULT")
        {
            formatter->m_formatString = "%Y-%m-%d %H:%M:%S,%s";
        }
        else
        {
            formatter->m_formatString = dateFormat;
        }
    }

    return formatter;
}

//==============================================================================

std::string DateFormatter::formatMessage(const std::string& loggerId, const LogLevel level, const MessageSPtr msg)
{
    std::stringstream stream;
    if (m_formatString == "UNIX")
    {
        // Number of seconds since epoch.
        std::chrono::system_clock::duration timeSinceEpoch = msg->getTimestamp().time_since_epoch();

        stream << timeSinceEpoch.count() * std::chrono::system_clock::period::num
                      / std::chrono::system_clock::period::den;
    }
    else if (m_formatString == "UNIX_MILLIS")
    {
        // Number of milliseconds since epoch.
        std::chrono::system_clock::duration timeSinceEpoch = msg->getTimestamp().time_since_epoch();

        stream << timeSinceEpoch.count() * std::chrono::system_clock::period::num
                      / (std::chrono::system_clock::period::den / 1000);
    }
    else
    {
        std::string formatString = m_formatString;
        std::size_t pos          = formatString.find("%s");
        if (pos != std::string::npos)
        {
            // With milliseconds.
            std::chrono::system_clock::duration timeSinceEpoch = msg->getTimestamp().time_since_epoch();
            int64_t totalMilliSeconds = timeSinceEpoch.count() * std::chrono::system_clock::period::num
                                        / (std::chrono::system_clock::period::den / 1000);

            std::stringstream msStream;
            msStream << std::setw(3) << std::setfill('0') << (totalMilliSeconds % 1000);

            formatString.replace(pos, 2, msStream.str());
        }

        std::time_t timeT = std::chrono::system_clock::to_time_t(msg->getTimestamp());

#ifdef _WIN32
        std::tm tmTime;
        localtime_s(&tmTime, &timeT);
#else
        std::tm tmTime = *std::localtime(&timeT);
#endif

        // try until max buffer size (2^11 = 2048) reached
        std::vector<char> buffer;
        for (uint8_t i{0}; i < 6; i++)
        {
            buffer.resize(static_cast<std::size_t>(std::pow(2, 6 + i)));

            if (std::strftime(&buffer[0], buffer.size(), formatString.c_str(), &tmTime))
            {
                stream.write(&buffer[0], std::strlen(&buffer[0]));
                break;
            }
        }
    }

    return stream.str();
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

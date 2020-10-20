//==============================================================================
//!\file
//!\brief File logger backend - writes all messages to file.
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

#include <ibeo/common/logging/backends/FileLoggerBackend.hpp>

#include <iostream>
#include <fstream>
#include <regex>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

FileLoggerBackend::FileLoggerBackend() : AsyncLoggerBackend{backendId} {}

//==============================================================================

FileLoggerBackend::~FileLoggerBackend()
{
    MutexGuard guard{m_mutex};

    m_logFile.close();
}

//==============================================================================

void FileLoggerBackend::logAsync(const std::string& loggerId, const LogLevel& level, const MessageSPtr msg)
{
    MutexGuard guard{m_mutex};

    if (m_logFileOpenFailed)
    {
        // Last time opening the file failed -> no need to try it again.
        return;
    }

    if (level == LogLevel::Off)
    {
        // Logging switched off.
        return;
    }

    if (m_logFile.is_open() == false)
    {
        m_logFile.open(m_filePath, std::ios::out | std::ios::trunc);
        if (m_logFile.is_open() == false)
        {
            std::cerr << "Cannot open '" << m_filePath << "' for logging! Logging to file will be disabled."
                      << std::endl;
            m_logFileOpenFailed = true;
            return;
        }
    }

    m_logFile << getFormattedText(loggerId, level, msg) << std::endl;

    m_logFile.flush();
}

//==============================================================================

bool FileLoggerBackend::configure(const tinyxml2::XMLElement* const xmlNode, const bool suppressErrors)
{
    // Format:
    // <Backend id="ibeo::common::logging::FileLoggerBackend"
    //          format="%d{HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n">
    //     <Path>${HOME}/ibeo/logging/ibeo.log</Path>
    // </Backend>

    if (AsyncLoggerBackend::configure(xmlNode, suppressErrors) == false)
    {
        // Configuring failed -> give up.
        return false;
    }

    MutexGuard guard{m_mutex};

    const tinyxml2::XMLElement* pathNode = xmlNode->FirstChildElement("Path");
    if (pathNode != nullptr)
    {
        std::string path = pathNode->GetText();
        if (path.empty() == false)
        {
            m_filePath = expandEnvironmentVariables(path);
        }

        // Log file path changed -> re-open log file next time.
        if (m_logFile.is_open())
        {
            m_logFile.close();
        }
        else if (m_logFileOpenFailed)
        {
            // Last time opening the log file failed -> retry now with new name.
            m_logFileOpenFailed = false;
        }
    }
    //else: No path node given -> do not change configuration.

    return true;
}

//==============================================================================

const std::string& FileLoggerBackend::getFilePath() const
{
    MutexGuard guard{m_mutex};
    return m_filePath;
}

//==============================================================================

void FileLoggerBackend::setFilePath(const std::string& filePath)
{
    MutexGuard guard{m_mutex};
    m_filePath = filePath;
}

//==============================================================================

std::string FileLoggerBackend::expandEnvironmentVariables(const std::string& input)
{
    static std::regex env(R"(\$\{([^}]+)\})");

    std::string output{input};
    std::smatch match;

    using StringIter = std::string::iterator;

    while (std::regex_search(output, match, env))
    {
#ifdef _WIN32
        std::string envValue{};
        std::size_t requiredSize;

        getenv_s(&requiredSize, NULL, 0, match[1].str().c_str());
        if (requiredSize > 0)
        {
            // The requiredSize includes the terminating zero. Thus, the buffer must have
            // at least this size otherwise the getenv_s will fail.
            envValue.resize(requiredSize, 0);
            getenv_s(&requiredSize, &envValue[0], requiredSize, match[1].str().c_str());

            // Now, getenv_s copied the string including the terminating zero to the buffer.
            // -> remove it.
            envValue.resize(envValue.size() - 1);
        }
#else
        std::string envValue(getenv(match[1].str().c_str()));
#endif

        // bugfix for older gcc versions (Ubuntu 14.04.)
        // Using [distance] and [advance] to convert [const_iterator]s to [iterator]s.
        // Source: Three Guidelines for Effective Iterator Usage - Scott Meyers
        StringIter iter1(output.begin());
        auto constIter1 = match[0].first;
        std::advance(iter1, std::distance<std::string::const_iterator>(iter1, constIter1));

        StringIter iter2(output.begin());
        auto constIter2 = match[0].second;
        std::advance(iter2, std::distance<std::string::const_iterator>(iter2, constIter2));

        output.replace(iter1, iter2, envValue);
    }

    return output;
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

//==============================================================================
//!\file
//!\brief Logger backend that writes all messages to std::cout / std::cerr.
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

#include <ibeo/common/logging/backends/ConsoleLoggerBackend.hpp>

#include <iostream>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

void ConsoleLoggerBackend::logAsync(const std::string& loggerId, const LogLevel& level, const MessageSPtr msg)
{
    if (level == LogLevel::Off)
    {
        // Logging switched off.
        return;
    }

    MutexGuard guard{m_consoleMutex};

    std::ostream& outStream = ((level == LogLevel::Critical) || (level == LogLevel::Error)) ? std::cerr : std::cout;
    outStream << getFormattedText(loggerId, level, msg) << std::endl;
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

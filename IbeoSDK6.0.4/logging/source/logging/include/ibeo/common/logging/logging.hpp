//==============================================================================
//!\file
//!\brief Convenience header with all necessary includes and handy macro definitions.
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

#pragma once

//==============================================================================

#include <ibeo/common/logging/backends/LoggerBackend.hpp>
#include <ibeo/common/logging/backends/LoggerBackendManager.hpp>
#include <ibeo/common/logging/backends/ConsoleLoggerBackend.hpp>
#include <ibeo/common/logging/backends/FileLoggerBackend.hpp>

#include <ibeo/common/logging/Configuration.hpp>
#include <ibeo/common/logging/Format.hpp>

#include <ibeo/common/logging/Logger.hpp>
#include <ibeo/common/logging/LoggerFactory.hpp>
#include <ibeo/common/logging/LogLevel.hpp>

#include <ibeo/common/logging/Message.hpp>
#include <ibeo/common/logging/MessageStreamHelper.hpp>
#include <ibeo/common/logging/LogManager.hpp>

//==============================================================================
//! \brief Macro for easy creation of a log message with the current source code location.
//!
//! Typical use:
//! \code logger->critical(LOGMSG << "Logging an int: " << std::setw(4) << std::setfill('0') << 42); \endcode
//!
//! \note For logging a simple string without using the streaming output operator ('<<') the \a LOGMSG_TEXT macro
//!       should be considered which runs faster.
//------------------------------------------------------------------------------
#define LOGMSG std::make_shared<ibeo::common::logging::Message>(__LINE__, __FUNCTION__, __FILE__)

//==============================================================================
//! \brief Macro for easy creation of a log message with the current source code location and a simple string.
//!
//! Typical use:
//! \code logger->critical(LOGMSG_TEXT("This is a log message!")); \endcode
//!
//! \note This is the preferred way for logging a simple string only. Nevertheless, you can still concatenate the log
//!       message with the streaming output operator ('<<') as shown in \a LOGMSG.
//------------------------------------------------------------------------------
#define LOGMSG_TEXT(text) std::make_shared<ibeo::common::logging::Message>(__LINE__, __FUNCTION__, __FILE__, text)

//==============================================================================
//! \brief Macros for easy creation of a log messages with a specific log level.
//!
//! Typical use:
//! \code LOGERROR(logger, "This is a log message!"); \endcode
//------------------------------------------------------------------------------
#define LOGCRITICAL(logger, stream) logger->critical(LOGMSG << stream);
#define LOGERROR(logger, stream) logger->error(LOGMSG << stream);
#define LOGWARNING(logger, stream) logger->warning(LOGMSG << stream);
#define LOGINFO(logger, stream) logger->info(LOGMSG << stream);
#define LOGTRACE(logger, stream) logger->trace(LOGMSG << stream);
#define LOGDEBUG(logger, stream) logger->debug(LOGMSG << stream);

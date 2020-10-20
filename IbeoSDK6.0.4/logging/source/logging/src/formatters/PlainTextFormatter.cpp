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

#include <ibeo/common/logging/formatters/PlainTextFormatter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

PlainTextFormatter::PlainTextFormatter(const std::string& text) : Formatter(), m_text{text} {}

//==============================================================================

std::string PlainTextFormatter::formatMessage(const std::string& loggerId, const LogLevel level, const MessageSPtr msg)
{
    return m_text;
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

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

#pragma once

//==============================================================================

#include <ibeo/common/logging/formatters/Formatter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

//==============================================================================
//! \brief A log message formatter for printing plain text.
//------------------------------------------------------------------------------
class PlainTextFormatter : public Formatter
{
public: // constructors, destructors
    //========================================
    //! \brief Constructor.
    //!
    //! \param[in] text  Plain text to print.
    //----------------------------------------
    PlainTextFormatter(const std::string& text = "");

    //========================================
    //! \brief Destructor.
    //----------------------------------------
    virtual ~PlainTextFormatter() = default;

public:
    //========================================
    //! \brief Format the message.
    //!
    //! \param[in] loggerId  ID of the logger that created the message.
    //! \param[in] level     The log level when the message was sent.
    //! \param[in] msg       The log message to be formatted.
    //! \return Text containing the log message formatted according to the configuration of this formatter.
    //----------------------------------------
    std::string formatMessage(const std::string& loggerId, const LogLevel level, const MessageSPtr msg) override;

private:
    std::string m_text{};
}; // PlainTextFormatter

//==============================================================================

using PlainTextFormatterSPtr = std::shared_ptr<PlainTextFormatter>;

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

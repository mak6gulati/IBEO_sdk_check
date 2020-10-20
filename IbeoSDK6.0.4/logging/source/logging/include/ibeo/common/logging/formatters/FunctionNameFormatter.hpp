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
//! \brief A log message formatter for converting the message's function name field.
//------------------------------------------------------------------------------
class FunctionNameFormatter : public Formatter
{
public: // constructors, destructors
    //========================================
    //! \brief Create an instance of a formatter for the message's function name field.
    //!
    //! \param[in] modifier  The \a FormatModifier used for applying common format options.
    //! \param[in] options   A list of strings with special format options for the function name field (not used).
    //! \return An instance of a FunctionNameFormatter.
    //----------------------------------------
    static FormatterSPtr create(const FormatModifier& modifier, const std::list<std::string>& options);

    //========================================
    //! \brief Destructor.
    //----------------------------------------
    virtual ~FunctionNameFormatter() = default;

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
    FunctionNameFormatter() = default;
}; // FunctionNameFormatter

//==============================================================================

using FunctionNameFormatterSPtr = std::shared_ptr<FunctionNameFormatter>;

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

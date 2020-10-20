//==============================================================================
//!\file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Mar 14, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <vector>
#include <algorithm>
#include <iterator>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Base class for trace messages
class LogMessage64x0Base
{
public:
    enum class TraceLevel : uint8_t
    {
        Off     = 0, ///< No trace output
        Error   = 1, ///< Show errors only (minimal trace output)
        Warning = 2, ///< Show errors and warnings
        Note    = 3, ///< Show errors, warnings, and notes
        Debug   = 4 ///< Show errors, warnings, notes, and debug messages
    };

public:
    LogMessage64x0Base(const std::string& msg) : m_message(msg) {}
    LogMessage64x0Base(std::string&& msg = std::string()) : m_message(msg) {}

    LogMessage64x0Base(const LogMessage64x0Base&) = default;
    LogMessage64x0Base(LogMessage64x0Base&&)      = default;

    //	LogMessage64x0Base operator=(const LogMessage64x0Base&) = default;
    //	LogMessage64x0Base operator=(LogMessage64x0Base&&) = default;

    virtual ~LogMessage64x0Base(){};

public:
    virtual TraceLevel getTraceLevel() const = 0;
    const std::string& getMessage() const { return m_message; }

public:
    void setMessage(const std::string& newMessage) { m_message = newMessage; }
    void setMessage(std::string&& newMessage) { m_message = newMessage; }

public:
    //========================================
    //! \brief Convert all letters in \a inStr to ASCII letters.
    //! \param[in] inStr  A vector containing characters to be
    //!                   converted to a string that contains only
    //!                   ASCII characters.
    //! \return The ASCII version of the string given in \a inStr.
    //-------------------------------------
    static std::string toASCII(const std::vector<char>& inStr)
    {
        std::string outStr;
        std::transform(inStr.begin(), inStr.end(), std::back_inserter(outStr), toascii);
        return outStr;
    }

protected:
    //========================================
    //! \brief Content of this LogMessage.
    //-------------------------------------
    std::string m_message;
}; // LogMessageBaseContainer

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

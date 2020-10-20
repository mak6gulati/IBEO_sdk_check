//==============================================================================
//!\file
//!\brief Base class for logger backends.
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

#include <ibeo/common/logging/backends/LoggerBackend.hpp>

#include <ctime>
#include <iostream>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

bool LoggerBackend::configure(const tinyxml2::XMLElement* const xmlNode, const bool suppressErrors)
{
    // Format:
    // <Backend id="ibeo::common::logging::FileLoggerBackend"
    //          format="%d{HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n">
    //     <Path directory="$HOME/ibeo/logging" fileName="ibeo_%d.log" />
    // </Backend>

    // Configure common part shared by all logger backends.
    FormatSPtr format = Format::parse(xmlNode->Attribute("format"));
    if (format == nullptr)
    {
        if (suppressErrors == false)
        {
            std::cerr << "Invalid format for logger backend ID '" << getId()
                      << "' in logging configuration! Fall back to default format." << std::endl;
        }
        return false;
    }
    else
    {
        m_format = format;
        return true;
    }
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

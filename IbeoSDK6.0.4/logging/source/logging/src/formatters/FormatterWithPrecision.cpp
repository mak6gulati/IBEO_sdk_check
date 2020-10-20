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
//! \date Nov 01, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/logging/formatters/FormatterWithPrecision.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

void FormatterWithPrecision::storePrecisionFromOptions(const std::list<std::string>& options)
{
    if (options.empty() == false)
    {
        try
        {
            m_precision = static_cast<uint32_t>(std::stoul(options.front()));
        }
        catch (const std::logic_error&)
        {
            // Not a number -> ignore error.
        }
    }
}

//==============================================================================
std::string FormatterWithPrecision::applyPrecision(const std::string& separator, const std::string& text)
{
    if (m_precision > 0)
    {
        // Use the rightmost n parts only.
        uint32_t partCount = m_precision;
        std::size_t pos{std::string::npos};
        while (true)
        {
            pos = text.rfind(separator, pos);
            if (pos == std::string::npos)
            {
                // Not found -> use whole text.
                pos = 0;
                break;
            }

            --partCount;
            if (partCount <= 0)
            {
                // No more text ro all parts found.
                pos += separator.length(); // Skip separator.
                break;
            }

            if (pos == 0)
            {
                // Still not found but at the beginning of the text -> use whole text.
                break;
            }

            // Continue search immediately in front of separator.
            --pos;
        }

        return text.substr(pos);
    }
    else
    {
        // No precision -> use whole text.
        return text;
    }
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

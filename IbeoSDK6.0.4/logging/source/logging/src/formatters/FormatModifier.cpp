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

//==============================================================================

#include <ibeo/common/logging/formatters/FormatModifier.hpp>

#include <stdexcept>

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
//==============================================================================

FormatModifier::FormatModifier() : m_maxWidth(std::numeric_limits<uint32_t>::max()){};

//==============================================================================

FormatModifier FormatModifier::parse(const std::string& formatStr, std::size_t& pos)
{
    FormatModifier modifier;
    bool alignmentCharSeen{false};
    bool minMaxWidthSeparatorCharSeen{false};
    bool truncationPositionCharSeen{false};

    // Check left alignment modifier (optional).
    if ((pos < formatStr.length()) && (formatStr[pos] == '-'))
    {
        modifier.m_padLeft = false;
        alignmentCharSeen  = true;

        // Format modifier given -> do not skip it.
        modifier.m_skip = false;

        // Next char.
        ++pos;
    }

    // Check minimum width (optional).
    if (pos < formatStr.length())
    {
        try
        {
            std::size_t nbOfCharConsumed;
            modifier.m_minWidth = static_cast<uint32_t>(std::stoul(formatStr.substr(pos), &nbOfCharConsumed));

            // Format modifier given -> do not skip it.
            modifier.m_skip = false;

            pos += nbOfCharConsumed;
        }
        catch (const std::logic_error&)
        {
            // Not a number -> no minimum width.
            if (alignmentCharSeen)
            {
                // Alignment character found -> revert position.
                --pos;
            }
        }
    }
    else if (alignmentCharSeen)
    {
        // Alignment char at end of format string -> revert position.
        --pos;
    }

    // Check min/max width separator.
    if ((pos < formatStr.length()) && (formatStr[pos] == '.'))
    {
        // Separator found -> check maximum width.
        ++pos;
        minMaxWidthSeparatorCharSeen = true;

        // Format modifier given -> do not skip it.
        modifier.m_skip = false;

        // Check truncation character (optional).
        if ((pos < formatStr.length()) && (formatStr[pos] == '-'))
        {
            modifier.m_truncateLeft    = false;
            truncationPositionCharSeen = true;

            // Next char.
            ++pos;
        }

        try
        {
            std::size_t nbOfCharConsumed;
            modifier.m_maxWidth = static_cast<uint32_t>(std::stoul(formatStr.substr(pos), &nbOfCharConsumed));

            pos += nbOfCharConsumed;
        }
        catch (const std::logic_error&)
        {
            // Not a number -> no maximum width -> revert position.
            if (truncationPositionCharSeen)
            {
                // Truncation character given -> revert it.
                --pos;
            }
            --pos;
        }
    }

    // std::string::npos
    return modifier;
}

//==============================================================================

std::string FormatModifier::process(const std::string& text)
{
    if (m_skip)
    {
        // No modifications necessary.
        return text;
    }

    std::string adjustedText{text};

    // Adjust minimum width.
    if (text.length() < m_minWidth)
    {
        const uint32_t paddingWidth = static_cast<uint32_t>(m_minWidth - text.length());
        if (m_padLeft)
        {
            adjustedText.insert(0, std::string(paddingWidth, ' '));
        }
        else // pad right
        {
            adjustedText.append(std::string(paddingWidth, ' '));
        }
    }

    // Adjust maximum width.
    if (text.length() > m_maxWidth)
    {
        const uint32_t nbOfCharsToBeDeleted = static_cast<uint32_t>(text.length() - m_maxWidth);

        if (m_truncateLeft)
        {
            adjustedText.erase(0, nbOfCharsToBeDeleted);
        }
        else
        {
            adjustedText.resize(adjustedText.length() - nbOfCharsToBeDeleted);
        }
    }

    return adjustedText;
}

//==============================================================================
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

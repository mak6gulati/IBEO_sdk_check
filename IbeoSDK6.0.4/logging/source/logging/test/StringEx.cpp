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
//! \date Sep 25, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include "StringEx.hpp"

//==============================================================================
namespace ibeo {
namespace common {
namespace logging {
namespace unittest {
//==============================================================================

bool StringEx::startsWith(const std::string& prefix) const
{
    if (this->length() >= prefix.length())
    {
        return (this->compare(0, prefix.length(), prefix) == 0);
    }
    else
    {
        return false;
    }
}

//==============================================================================

bool StringEx::endsWith(const std::string& suffix) const
{
    if (this->length() >= suffix.length())
    {
        return (this->compare(this->length() - suffix.length(), suffix.length(), suffix) == 0);
    }
    else
    {
        return false;
    }
}

//==============================================================================
} // namespace unittest
} // namespace logging
} // namespace common
} // namespace ibeo
//==============================================================================

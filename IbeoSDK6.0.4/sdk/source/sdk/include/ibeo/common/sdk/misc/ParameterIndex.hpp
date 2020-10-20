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
//! \date Apr 10, 2015
//------------------------------------------------------------------------------
#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/misc/Unconvertable.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/bufferIO.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class ParameterIndex : public ibeo::common::sdk::ComparableUnconvertable<uint16_t>
{
public:
    explicit ParameterIndex(const uint16_t index) : ibeo::common::sdk::ComparableUnconvertable<uint16_t>(index) {}

public: // BE io
    std::istream& readBE(std::istream& is)
    {
        ibeo::common::sdk::readBE(is, this->m_data);
        return is;
    }

    std::ostream& writeBE(std::ostream& os) const
    {
        ibeo::common::sdk::writeBE(os, this->m_data);
        return os;
    }

    void readBE(const char*& target) { ibeo::common::sdk::readBE(target, this->m_data); }
    void writeBE(char*& target) const { ibeo::common::sdk::writeBE(target, this->m_data); }

public: // LE io
    std::istream& readLE(std::istream& is)
    {
        ibeo::common::sdk::readLE(is, this->m_data);
        return is;
    }

    std::ostream& writeLE(std::ostream& os) const
    {
        ibeo::common::sdk::writeLE(os, this->m_data);
        return os;
    }

    void readLE(const char*& target) { ibeo::common::sdk::readLE(target, this->m_data); }
    void writeLE(char*& target) const { ibeo::common::sdk::writeLE(target, this->m_data); }
}; // ParameterIndex

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

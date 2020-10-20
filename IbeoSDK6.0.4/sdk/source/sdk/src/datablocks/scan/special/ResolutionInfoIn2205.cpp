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
//! \date Apr 26, 2012
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/ResolutionInfoIn2205.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/Math.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

ResolutionInfoIn2205::ResolutionInfoIn2205() : m_resolutionStartAngle(0.0), m_resolution(0.0) {}

//==============================================================================

ResolutionInfoIn2205::ResolutionInfoIn2205(const ResolutionInfoIn2205& other)
  : m_resolutionStartAngle(other.m_resolutionStartAngle), m_resolution(other.m_resolution)
{}

//==============================================================================

ResolutionInfoIn2205& ResolutionInfoIn2205::operator=(const ResolutionInfoIn2205& other)
{
    m_resolutionStartAngle = other.m_resolutionStartAngle;
    m_resolution           = other.m_resolution;

    return *this;
}

//==============================================================================

//static
std::streamsize ResolutionInfoIn2205::getSerializedSize_static() { return 2 * std::streamsize(sizeof(float)); }

//==============================================================================

bool ResolutionInfoIn2205::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_resolutionStartAngle);
    ibeo::common::sdk::readBE(is, m_resolution);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ResolutionInfoIn2205::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_resolutionStartAngle);
    ibeo::common::sdk::writeBE(os, m_resolution);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool ResolutionInfoIn2205::operator==(const ResolutionInfoIn2205& other) const
{
    if (!(fuzzyFloatEqualT<7>(m_resolutionStartAngle, other.getResolutionStartAngle())))
        return false;

    if (!(fuzzyFloatEqualT<7>(m_resolution, other.getResolution())))
        return false;

    return true;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

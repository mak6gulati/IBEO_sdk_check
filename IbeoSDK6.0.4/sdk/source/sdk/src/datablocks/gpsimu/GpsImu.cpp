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
//! \date Jan 31, 2019
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/gpsimu/GpsImu.hpp>
#include <ibeo/common/sdk/Math.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

GpsImu::GpsImu() : DataContainerBase() {}

//==============================================================================

std::string GpsImu::toString(const GpsImuSource s)
{
    switch (s)
    {
    case GpsImuSource::Can:
        return "CAN";
    case GpsImuSource::XSensImu:
        return "XSensIMU";
    case GpsImuSource::OGpsImuRt:
        return "OGpsImuRt";
    case GpsImuSource::GenesysAdma:
        return "GenesysADMA";
    case GpsImuSource::SpatialDual:
        return "SpatialDual";
    case GpsImuSource::Tfc:
        return "TFC";
    case GpsImuSource::VBox3i:
        return "VBOX3i";
    case GpsImuSource::Unknown:
        return "Unknown";
    default:
    {
        std::stringstream ss;
        ss << int(s);
        return "Unknown source: " + ss.str();
    }
    } // switch
}

//==============================================================================
//==============================================================================

bool operator==(const GpsImu& lhs, const GpsImu& rhs) { return lhs.m_delegate == rhs.m_delegate; }

//==============================================================================

bool operator!=(const GpsImu& lhs, const GpsImu& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

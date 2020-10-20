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
//!\date Mar 16, 2016
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/pointcloud/PointBase.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class PointCloudPointIn7500 : public PointBase
{
public:
    PointCloudPointIn7500() : PointBase() {}
    virtual ~PointCloudPointIn7500() = default;

public:
    static std::streamsize getSerializedSize_static();

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    GpsPoint& gpsPoint() { return m_gpsPoint; }
    const GpsPoint& getGpsPoint() const { return m_gpsPoint; }
    void setGpsPoint(const GpsPoint& point) { m_gpsPoint = point; }

private:
    GpsPoint m_gpsPoint;
}; // PointCloudPointIn7500

//==============================================================================

inline bool operator==(const PointCloudPointIn7500& lhs, const PointCloudPointIn7500& rhs)
{
    return lhs.getGpsPoint() == rhs.getGpsPoint();
}

inline bool operator!=(const PointCloudPointIn7500& lhs, const PointCloudPointIn7500& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

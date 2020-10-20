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
//!\date Mar 26, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "common/TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/pointcloud/PointCloud.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloud7500.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloud7510.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/ReferencePlane.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class PointCloudTestSupport : public TestSupport
{
public:
    virtual ~PointCloudTestSupport() = default;

public:
    static void fillRandomly(PointCloud7500& pc);
    static void fillRandomly(PointCloudPointIn7500& pt);

    static void fillRandomly(PointCloud7510& pc);
    static void fillRandomly(PointCloudPointIn7510& pt);

    static void fillRandomly(PointCloud& pc);
    //	static void fillRandomly(PointCloudPoint& pt);      same as fillRandomly(PointCloudPointIn7510& pp);

    static void fillRandomly(ReferencePlane& rp);

    static void fillRandomly(GpsPoint& gps);

protected:
    static constexpr int32_t nbOfRepeats = 100;
}; // PointCloudTestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

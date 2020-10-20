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
//!\date Mar 16, 2016
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloudPointIn7500.hpp>

#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloud7500.hpp>

#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize PointCloudPointIn7500::getSerializedSize_static() { return GpsPoint::getSerializedSize_static(); }

//==============================================================================

std::streamsize PointCloudPointIn7500::getSerializedSize() const { return getSerializedSize_static(); }

//==============================================================================

bool PointCloudPointIn7500::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    m_gpsPoint.deserialize(is);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool PointCloudPointIn7500::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    m_gpsPoint.serialize(os);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

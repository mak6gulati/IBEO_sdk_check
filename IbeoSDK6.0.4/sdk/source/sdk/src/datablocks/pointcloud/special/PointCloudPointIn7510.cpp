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
//!\date  Mar 15, 2016
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloudPointIn7510.hpp>

#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloud7510.hpp>

#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize PointCloudPointIn7510::getSerializedSize_static() { return serializedSize(Vector3<float>{}); }

//==============================================================================

std::streamsize PointCloudPointIn7510::getSerializedSize() const { return getSerializedSize_static(); }

//==============================================================================

bool PointCloudPointIn7510::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, m_point);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool PointCloudPointIn7510::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, m_point);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

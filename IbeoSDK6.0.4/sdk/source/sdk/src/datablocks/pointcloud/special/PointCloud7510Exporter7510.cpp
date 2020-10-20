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
//!\date Jan 16, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloud7510Exporter7510.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::PointCloud7510;
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_PointCloud7510>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    return static_cast<const PointCloudBase*>(container)->getSerializedSize() + std::streamsize(sizeof(uint32_t))
           + std::streamsize(container->m_points.size())
                 * (PointCloudPointIn7510::getSerializedSize_static()
                    + PointBase::getSerializedSizeWithType_static(container->m_type));
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_PointCloud7510>::serialize(std::ostream& os, const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(os.tellp());

    static_cast<const PointCloudBase*>(container)->serialize(os);

    ibeo::common::sdk::writeBE(os, uint32_t(container->m_points.size()));

    for (std::vector<PointCloudPointIn7510>::const_iterator pointIter = container->m_points.begin();
         pointIter != container->m_points.end();
         ++pointIter)
    {
        pointIter->serialize(os);
        pointIter->serializeWithType(os, container->m_type);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

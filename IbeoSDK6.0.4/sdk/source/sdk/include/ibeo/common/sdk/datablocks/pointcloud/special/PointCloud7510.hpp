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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/PointCloudBase.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloudPointIn7510.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Ibeo point cloud plane
//!
//! The point cloud datatype is used for holding a collection of 3-dimensional points.
//! The term plane is indicating that the data are stored with an offset to a reference system.
//! The differentiation is made because the reference system can also hold geo-coordinates and therefore it is important,
//! that this point cloud type does not store the geo-coordinates for each single point.
//!
//! General data type: \ref ibeo::common::sdk::PointCloud
class PointCloud7510 : public SpecializedDataContainer, public PointCloudBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    using PointVector = std::vector<PointCloudPointIn7510>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.pointcloud7510"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    PointCloud7510() : SpecializedDataContainer() {}
    virtual ~PointCloud7510() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    const PointVector& getPoints() const { return m_points; }
    void setPoints(const PointVector& points) { m_points = points; }

private:
    PointVector m_points;
}; // PointCloud7510

//==============================================================================

inline bool operator==(const PointCloud7510& lhs, const PointCloud7510& rhs)
{
    return (static_cast<const PointCloudBase&>(lhs) == static_cast<const PointCloudBase&>(rhs))
           && (lhs.getPoints() == rhs.getPoints());
}

//==============================================================================

inline bool operator!=(const PointCloud7510& lhs, const PointCloud7510& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

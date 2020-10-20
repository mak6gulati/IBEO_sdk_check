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
//! \date Jan 08, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/PointCloudBase.hpp>
#include <ibeo/common/sdk/datablocks/pointcloud/PointCloudPoint.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Holds a list of points.
//!
//! Special data types:
//! \ref ibeo::common::sdk::PointCloud7500
//! \ref ibeo::common::sdk::PointCloud7510
class PointCloud : public DataContainerBase, public PointCloudBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    using PointVector = std::vector<PointCloudPoint>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.pointcloud"};

    // in C++14 this could be a constexpr
    static uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    PointCloud() : DataContainerBase() {}
    ~PointCloud() override = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    const PointVector& getPoints() const { return m_points; }
    void setPoints(const PointVector& points) { m_points = points; }

private:
    PointVector m_points;
}; // PointCloud

//==============================================================================

inline bool operator==(const PointCloud& lhs, const PointCloud& rhs)
{
    return (static_cast<const PointCloudBase&>(lhs) == static_cast<const PointCloudBase&>(rhs))
           && (lhs.getPoints() == rhs.getPoints());
}

//==============================================================================

inline bool operator!=(const PointCloud& lhs, const PointCloud& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

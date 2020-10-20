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
#include <ibeo/common/sdk/datablocks/pointcloud/special/PointCloudPointIn7500.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Contains a vector of points.
//!
//! General data type: \ref ibeo::common::sdk::PointCloud
class PointCloud7500 : public SpecializedDataContainer, public PointCloudBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    using PointVector = std::vector<PointCloudPointIn7500>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.pointcloud7500"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    PointCloud7500() : SpecializedDataContainer() {}
    virtual ~PointCloud7500() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    const PointVector& getPoints() const { return m_points; }
    void setPoints(const PointVector& points) { m_points = points; }

private:
    PointVector m_points;
}; // PointCloud7500

//==============================================================================

inline bool operator==(const PointCloud7500& lhs, const PointCloud7500& rhs)
{
    return (static_cast<const PointCloudBase&>(lhs) == static_cast<const PointCloudBase&>(rhs))
           && (lhs.getPoints() == rhs.getPoints());
}

//==============================================================================

inline bool operator!=(const PointCloud7500& lhs, const PointCloud7500& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

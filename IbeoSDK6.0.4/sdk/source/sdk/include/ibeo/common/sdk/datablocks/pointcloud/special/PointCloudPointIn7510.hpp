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
//!\date  Mar 15, 2016
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

class PointCloudPointIn7510 : public PointBase
{
public:
    PointCloudPointIn7510() : PointBase() {}
    PointCloudPointIn7510(const Vector3<float> point) : PointBase(), m_point(point) {}

public:
    static std::streamsize getSerializedSize_static();

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    const Vector3<float>& getPoint3D() const { return m_point; }
    Vector3<float>& point3D() { return m_point; }
    void setPoint3D(const Vector3<float>& point) { m_point = point; }

private:
    Vector3<float> m_point;
}; // PointCloudPointIn7510

//==============================================================================

inline bool operator==(const PointCloudPointIn7510& lhs, const PointCloudPointIn7510& rhs)
{
    return lhs.getPoint3D() == rhs.getPoint3D();
}

inline bool operator!=(const PointCloudPointIn7510& lhs, const PointCloudPointIn7510& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

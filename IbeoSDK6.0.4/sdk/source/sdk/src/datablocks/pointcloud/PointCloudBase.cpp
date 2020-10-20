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
//!\date Mar 15, 2016
//------------------------------------------------------------------------------
//==============================================================================

#include <ibeo/common/sdk/datablocks/pointcloud/PointCloudBase.hpp>

#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

bool pointHasEpw(const PointType type)
{
    switch (type)
    {
    case PointType::PointWithEpw:
    case PointType::PointWithEpwAndFlags:
    case PointType::PointWithEpwFlagsAndColor:
        return true;
    default:
        return false;
    } // switch
}

//==============================================================================

bool pointHasFlags(const PointType type)
{
    switch (type)
    {
    case PointType::PointWithFlags:
    case PointType::PointWithEpwAndFlags:
    case PointType::PointWithEpwFlagsAndColor:
        return true;
    default:
        return false;
    } // switch
}

//==============================================================================

bool pointHasColor(const PointType type) { return (type == PointType::PointWithEpwFlagsAndColor); }

//==============================================================================

PointCloudBase::PointCloudBase() : m_kind(PointKind::Undefined), m_type(PointType::Point), m_refPlane(ReferencePlane())
{}

//==============================================================================

bool PointCloudBase::operator==(const PointCloudBase& other) const
{
    return (m_kind == other.m_kind) && (m_type == other.m_type) && (m_refPlane == other.m_refPlane);
}

//==============================================================================

PointKind PointCloudBase::stringToKind(const std::string& kind)
{
    if (kind == "LanePoint")
    {
        return PointKind::LanePoint;
    }
    else if (kind == "ScanPoint")
    {
        return PointKind::ScanPoint;
    }
    else
    {
        return PointKind::Undefined;
    }
}

//==============================================================================

std::string PointCloudBase::kindToString(const PointKind kind)
{
    if (kind == PointKind::LanePoint)
    {
        return "LanePoint";
    }
    else if (kind == PointKind::ScanPoint)
    {
        return "ScanPoint";
    }
    else
    {
        return "Undefined";
    }
}

//==============================================================================

std::streamsize PointCloudBase::getSerializedSize() const
{
    return std::streamsize(2 * sizeof(uint16_t) + sizeof(uint64_t)) + m_refPlane.getSerializedSize();
}

//==============================================================================

bool PointCloudBase::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    uint16_t type, kind;

    ibeo::common::sdk::readBE(is, kind);
    ibeo::common::sdk::readBE(is, type);
    m_refPlane.deserialize(is);

    uint64_t reserved;
    ibeo::common::sdk::readBE(is, reserved);

    m_type = static_cast<PointType>(type);
    m_kind = static_cast<PointKind>(kind);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool PointCloudBase::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, uint16_t(m_kind));
    ibeo::common::sdk::writeBE(os, uint16_t(m_type));
    m_refPlane.serialize(os);

    ibeo::common::sdk::writeBE(os, uint64_t(0));

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

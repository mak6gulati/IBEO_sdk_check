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
//!\date Oct 9, 2014
//!\brief Support point for a LaneSegment
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/PositionWgs84.hpp>
#include <ibeo/common/sdk/Vector2.hpp>

#include <ibeo/common/sdk/datablocks/ExporterBase.hpp>
#include <ibeo/common/sdk/datablocks/RegisteredImporter.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace lanes {
//==============================================================================

//==============================================================================
//!\brief This class represents a support point of a \ref LaneSegmentIn6970.
//!
//! A point holds information about gps position and heading and width
//! (more precisely the offsets to the left and right bounding line).
//------------------------------------------------------------------------------
class LaneSupportPointIn6970
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class ibeo::common::sdk::Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class ibeo::common::sdk::Exporter;

public:
    //! Default constructor, calls default constructors of members.
    LaneSupportPointIn6970() = default;

    //========================================
    //!\brief Constructor with initialization.
    //!\param[in] point            A GPS point with heading
    //!\param[in] lineOffsetLeft   The offset to the left bounding line
    //!\param[in] lineOffsetRight  The offset to the right bounding line
    //----------------------------------------
    LaneSupportPointIn6970(const PositionWgs84& point,
                           const Vector2<float>& lineOffsetLeft,
                           const Vector2<float>& lineOffsetRight)
      : m_latitudeInDeg{point.getLatitudeInDeg()},
        m_longitudeInDeg{point.getLongitudeInDeg()},
        m_courseAngelInDeg{point.getCourseAngleInDeg()},
        m_lineOffsetLeft{lineOffsetLeft},
        m_lineOffsetRight{lineOffsetRight}
    {}

public:
    //!\returns The GPS point and heading.
    PositionWgs84 getWgsPoint() const
    {
        PositionWgs84 p;
        p.setLongitudeInDeg(m_longitudeInDeg);
        p.setLatitudeInDeg(m_latitudeInDeg);
        p.setCourseAngleInDeg(m_courseAngelInDeg);
        return p;
    }

    double_t getLatituideInDeg() const { return m_latitudeInDeg; }
    double_t getLongitudeInDeg() const { return m_longitudeInDeg; }
    double_t getCourseAngleInDeg() const { return m_courseAngelInDeg; }

    //!\returns The offset to the left marking start point.
    Vector2<float> getLeftOffset() const { return m_lineOffsetLeft; }

    //!\returns The offset to the right marking start point.
    Vector2<float> getRightOffset() const { return m_lineOffsetRight; }

private:
    double_t m_latitudeInDeg{0.0};
    double_t m_longitudeInDeg{0.0};
    double_t m_courseAngelInDeg{0.0};
    Vector2<float> m_lineOffsetLeft{};
    Vector2<float> m_lineOffsetRight{};
}; // class LaneSupportPointIn6970

//==============================================================================

inline bool operator==(const LaneSupportPointIn6970& lhs, const LaneSupportPointIn6970& rhs)
{
    return (lhs.getLatituideInDeg() == rhs.getLatituideInDeg()) && (lhs.getLongitudeInDeg() == rhs.getLongitudeInDeg())
           && (lhs.getCourseAngleInDeg() == rhs.getCourseAngleInDeg()) && (lhs.getLeftOffset() == rhs.getLeftOffset())
           && (lhs.getRightOffset() == rhs.getRightOffset());
}

//==============================================================================

inline bool operator!=(const LaneSupportPointIn6970& lhs, const LaneSupportPointIn6970& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace lanes
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

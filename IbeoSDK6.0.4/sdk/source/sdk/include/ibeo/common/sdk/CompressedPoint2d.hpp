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
//! \date Sep 13, 2016
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>
#include <ibeo/common/sdk/Vector2.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class CompressedPoint2d : private Vector2<int16_t>
{
public:
    static const int16_t compressedPlusInfinity;
    static const int16_t compressedMinusInfinity;
    static const int16_t compressedNotANumber;

    static const float toCentimeter;
    static const float fromCentimeter;
    static const float toDecimeter;
    static const float fromDecimeter;

public:
    static std::streamsize getSerializedSize_static() { return serializedSize(Vector2<int16_t>{}); }
    static float decompressMeters(const int16_t compressedMeters);
    static float decompressRadians(const int16_t compressedRadians);

    static int16_t compressMeters(const float meters);
    static int16_t compressRadians(const float radians);

public:
    CompressedPoint2d();
    CompressedPoint2d(const int16_t compressedPosX, const int16_t compressedPosY);

    virtual ~CompressedPoint2d();

public:
    CompressedPoint2d& operator=(const CompressedPoint2d& src);

public:
    int16_t getCompressedX() const { return getX(); }
    int16_t getCompressedY() const { return getY(); }

    float getXinMeter() const { return decompressMeters(getX()); }
    float getYinMeter() const { return decompressMeters(getY()); }

public:
    void setCompressedX(const int16_t compressedPosX) { setX(compressedPosX); }
    void setCompressedY(const int16_t compressedPosY) { setY(compressedPosY); }

    void setX(const float posXMeter) { Vector2<int16_t>::setX(compressMeters(posXMeter)); }
    void setY(const float posYMeter) { Vector2<int16_t>::setY(compressMeters(posYMeter)); }

public:
    template<typename T>
    friend void readLE(std::istream& is, T& value);
    template<typename T>
    friend void readBE(std::istream& is, T& value);
}; // CompressedPoint2d

//==============================================================================

std::ostream& operator<<(std::ostream& os, const Vector2<int16_t>& tObj);
bool operator==(const CompressedPoint2d& lhs, const CompressedPoint2d& rhs);
bool operator!=(const CompressedPoint2d& lhs, const CompressedPoint2d& rhs);

//==============================================================================
//==============================================================================
//==============================================================================

template<>
inline void writeLE<CompressedPoint2d>(std::ostream& os, const CompressedPoint2d& p)
{
    ibeo::common::sdk::writeLE(os, p.getCompressedX());
    ibeo::common::sdk::writeLE(os, p.getCompressedY());
}

//==============================================================================

template<>
inline void readLE<CompressedPoint2d>(std::istream& is, CompressedPoint2d& p)
{
    ibeo::common::sdk::readLE(is, p.m_x);
    ibeo::common::sdk::readLE(is, p.m_y);
}

//==============================================================================
//==============================================================================
//==============================================================================

template<>
inline void writeBE<CompressedPoint2d>(std::ostream& os, const CompressedPoint2d& p)
{
    ibeo::common::sdk::writeBE(os, p.getCompressedX());
    ibeo::common::sdk::writeBE(os, p.getCompressedY());
}

//==============================================================================

template<>
inline void readBE<CompressedPoint2d>(std::istream& is, CompressedPoint2d& p)
{
    ibeo::common::sdk::readBE(is, p.m_x);
    ibeo::common::sdk::readBE(is, p.m_y);
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

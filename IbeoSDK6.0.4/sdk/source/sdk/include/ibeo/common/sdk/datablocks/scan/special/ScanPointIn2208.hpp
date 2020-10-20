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
//! \date Aug 2, 2013
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <istream>
#include <ostream>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \brief Raw scan point for Scala and Minilux
class ScanPointIn2208
{
public:
    enum class Flags : uint16_t
    {
        Transparent = 0x0001U,
        Rain        = 0x0002U,
        Ground      = 0x0004U,
        Dirt        = 0x0008U,

        HighThreshold = 0x0010U,
        Noise         = 0x0020U,
        NearRange     = 0x0040U,
        Marker        = 0x0080U,

        Blooming   = 0x0100U,
        Background = 0x0200U,
        Reserved3  = 0x0400U,
        Reserved4  = 0x0800U,

        Reflector     = 0x1000U,
        Reserved5     = 0x2000U,
        InterlacingPt = 0x4000U, // only for A1 prototype
        Reserved7     = 0x8000U
    };

public:
    ScanPointIn2208();
    virtual ~ScanPointIn2208();

public:
    //! Equality predicate
    bool operator==(const ScanPointIn2208& other) const;

    bool operator!=(const ScanPointIn2208& other) const;

public:
    static std::streamsize getSerializedSize_static() { return 11; }

public:
    virtual std::streamsize getSerializedSize() const { return getSerializedSize_static(); }
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    uint8_t getThresholdId() const { return m_thresholdId; }
    uint8_t getEchoId() const { return m_echoId; }
    uint8_t getReserved() const { return m_reserved; }
    uint8_t getLayerId() const { return m_layerId; }
    uint16_t getFlags() const { return m_flags; }
    int16_t getHorizontalAngle() const { return m_horizontalAngle; }
    uint16_t getRadialDistance() const { return m_radialDistance; }
    uint16_t getEchoPulseWidth() const { return m_echoPulseWidth; }
    uint8_t getPfValue() const { return m_pfValue; }

public:
    void setThresholdId(const uint8_t newThresholdId) { this->m_thresholdId = newThresholdId & 0x0f; } // 4 bit
    void setEchoId(const uint8_t newEchoId) { this->m_echoId = newEchoId & 0x03; } // 2 bit
    void setReserved(const uint8_t newReserved) { this->m_reserved = newReserved & 0x03; } // 2 bit
    void setLayerId(const uint8_t newLayerId) { this->m_layerId = newLayerId; }
    void setFlags(const uint16_t newFlags) { this->m_flags = newFlags; }
    void setHorizontalAngle(const int16_t newHorizontalAngle) { this->m_horizontalAngle = newHorizontalAngle; }
    void setRadialDistance(const uint16_t newRadialDistance) { this->m_radialDistance = newRadialDistance; }
    void setEchoPulseWidth(const uint16_t newEchoPulseWidth) { this->m_echoPulseWidth = newEchoPulseWidth; }
    void setPfValue(const uint8_t newPfValue) { this->m_pfValue = newPfValue; }

public:
    //	static const uint8_t undefinedThresholdId = 0xF; // 0xE
protected:
    uint8_t m_thresholdId; // 4 bit
    uint8_t m_echoId; // 2 bit
    uint8_t m_reserved; // 2bit

    uint8_t m_layerId;
    uint16_t m_flags;
    int16_t m_horizontalAngle;
    uint16_t m_radialDistance;
    uint16_t m_echoPulseWidth;
    uint8_t m_pfValue;
}; // ScanPointIn2208

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

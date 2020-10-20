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
//! \date Apr 25, 2012
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief scan point in the format of the LUX3 firmware
class ScanPointIn2202
{
public:
    enum class Flags : uint8_t
    {
        Transparent = 0x01U, //!< transparent point
        Rain        = 0x02U, //!< clutter (atmospheric)
        Ground      = 0x04U, //!< ground
        Dirt        = 0x08U //!< dirt
        // 0x10, 0x20, 0x40, 0x80 are reserved
    }; // Flags

public:
    ScanPointIn2202();
    ScanPointIn2202(const ScanPointIn2202& src);
    virtual ~ScanPointIn2202();

    ScanPointIn2202& operator=(const ScanPointIn2202& src);

public:
    static std::streamsize getSerializedSize_static();

public:
    virtual std::streamsize getSerializedSize() const { return getSerializedSize_static(); }
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public: // getter
    uint8_t getLayer() const { return m_layer; }
    uint8_t getEcho() const { return m_echo; }
    uint8_t getFlags() const { return m_flags; }
    int16_t getHorizontalAngleTicks() const { return m_angle; }
    uint16_t getDistanceCm() const { return m_distance; }
    uint16_t getEchoPulseWidthCm() const { return m_epw; }
    uint16_t getReserved() const { return m_reserved; }

public: // setter
    void setLayer(const uint8_t newLayer) { this->m_layer = newLayer; }
    void setEcho(const uint8_t newEcho) { this->m_echo = newEcho; }
    void setFlags(const uint8_t newFlags) { this->m_flags = newFlags; }
    void setHorizontalAngleTicks(const int16_t newHorizontalAngleTicks) { this->m_angle = newHorizontalAngleTicks; }
    void setDistanceCm(const uint16_t newDistanceCm) { this->m_distance = newDistanceCm; }
    void setEchoPulseWidthCm(const uint16_t newEchoPulseWidthCm) { this->m_epw = newEchoPulseWidthCm; }
    void setReserved(const uint16_t newReserved) { this->m_reserved = newReserved; }

private:
    uint8_t m_layer{0}; // 4 bit used
    uint8_t m_echo{0}; // 4 bit used
    uint8_t m_flags{0}; // combination of bits from LuxScanPointFlag
    int16_t m_angle{0};
    uint16_t m_distance{0}; // cm
    uint16_t m_epw{0}; // cm
    uint16_t m_reserved{0}; //Segment + ObjectID (2xUINT8)
}; // ScanPointIn2202

//==============================================================================

bool operator==(const ScanPointIn2202& lhs, const ScanPointIn2202& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

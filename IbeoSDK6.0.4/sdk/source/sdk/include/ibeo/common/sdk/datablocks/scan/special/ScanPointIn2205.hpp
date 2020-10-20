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
//! \date Apr 26, 2012
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Math.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! \brief scan points in the new generic proposed format
class ScanPointIn2205
{
public:
    //======================================================================

    enum class Flags : uint16_t
    {
        Ground      = 0x0001U, ///< Invalid scan point, echo from ground
        Dirt        = 0x0002U, ///< Invalid scan point, echo from dirt
        Rain        = 0x0004U, ///< Invalid scan point, echo from rain drop
        RoadMarking = 0x0008U, ///< Scan point belongs to road marking
        ThresholdSwitching
        = 0x0010U, ///< Scan point was measured using the higher threshold (since FGPA version 8.0.08)
        ///< Old: Scan point was measured in a shot with threshold switching (earlier FPGA versions)
        Reflector = 0x0020U, ///< EPW of scan point is high enough to be a reflector
        NearRange
        = 0x0040U, ///< Scan point is measured in near range. Flag is set by FPGA according threshold switching time.
        Curbstone    = 0x0080U, ///< Scan point belongs to a curbstone
        LeftCovered  = 0x0100U, ///< Left neighbour point may be covered
        RightCovered = 0x0200U, ///< Right neighbour point may be covered
        Background
        = 0x0400U, ///< Point has been recognized as background and should not be used in the tracking anymore
        Marker      = 0x0800U, ///< Point is "marked" (see above)
        Transparent = 0x1000U, ///< There is at least one more echo behind this scan point (B or C echo)
        Dynamic
        = 0x2000U, ///< There is a dynamic object corresponds to this scan point (object ID is written in segmentID)
        EpwIsIntensity = 0x4000, ///< The echo pulse width field (epw) is uses as intensity.
        // 0x8000 unused
        MaskInvalid = Ground | Dirt | Rain | Background | RoadMarking | Curbstone, ///< All flags of invalid scan points
        MaskCovered = LeftCovered | RightCovered, ///< All coverage flags
        Guardrail   = RoadMarking | Curbstone ///< Scan point belongs to guard rail
    }; // Flags

public:
    ScanPointIn2205();
    ScanPointIn2205(const ScanPointIn2205& src);
    virtual ~ScanPointIn2205();

    ScanPointIn2205& operator=(const ScanPointIn2205& src);

public:
    static std::streamsize getSerializedSize_static();

public:
    virtual std::streamsize getSerializedSize() const { return getSerializedSize_static(); }
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public: // getter
    float getPositionX() const { return m_posX; }
    float getPositionY() const { return m_posY; }
    float getPositionZ() const { return m_posZ; }

    float getEchoPulseWidth() const { return isEpwIsIntensity() ? NaN : m_epw; }
    float getIntensity() const { return isEpwIsIntensity() ? m_epw : NaN; }

    uint8_t getDeviceId() const { return m_deviceId; }

    uint8_t getLayer() const { return m_layer; }
    uint8_t getEcho() const { return m_echo; }
    uint8_t getReserved() const { return m_reserved; }
    uint32_t getTimeOffset() const { return m_timeOffset; }

    uint16_t getFlags() const { return m_flags; }
    bool isFlagSet(const Flags flags) const
    {
        return (m_flags & static_cast<uint16_t>(flags)) == static_cast<uint16_t>(flags);
    }

    bool isAnyFlagOfMaskSet(const Flags mask) const { return (m_flags & static_cast<uint16_t>(mask)) != 0; }

    bool isGround() const { return isFlagSet(Flags::Ground); }
    bool isDirt() const { return isFlagSet(Flags::Dirt); }
    bool isRain() const { return isFlagSet(Flags::Rain); }
    bool isRoadMarking() const { return isFlagSet(Flags::RoadMarking); }
    bool isThresholdSwitching() const { return isFlagSet(Flags::ThresholdSwitching); }
    bool isReflector() const { return isFlagSet(Flags::Reflector); }
    bool isNearRange() const { return isFlagSet(Flags::NearRange); }
    bool isCurbstone() const { return isFlagSet(Flags::Curbstone); }
    bool isLeftCovered() const { return isFlagSet(Flags::LeftCovered); }
    bool isRightCovered() const { return isFlagSet(Flags::RightCovered); }
    bool isBackground() const { return isFlagSet(Flags::Background); }
    bool isMarker() const { return isFlagSet(Flags::Marker); }
    bool isTransparent() const { return isFlagSet(Flags::Transparent); }
    bool isDynamic() const { return isFlagSet(Flags::Dynamic); }
    bool isEpwIsIntensity() const { return isFlagSet(Flags::EpwIsIntensity); }

    bool isInvalid() const { return isAnyFlagOfMaskSet(Flags::MaskInvalid); }
    bool isCovered() const { return isAnyFlagOfMaskSet(Flags::MaskCovered); }
    bool isGuardRail() const { return isFlagSet(Flags::Guardrail); }

    //! \note the segment ID could also be filled with the corresponding ObjectID
    uint16_t getSegmentId() const { return m_segmentId; }

public: // setter
    void setPosX(const float newPosX) { m_posX = newPosX; }
    void setPosY(const float newPosY) { m_posY = newPosY; }
    void setPosZ(const float newPosZ) { m_posZ = newPosZ; }
    void setEpw(const float newEpw)
    {
        m_epw = newEpw;
        setEpwIsIntensity(false);
    }
    void setIntensity(const float newIntensity)
    {
        m_epw = newIntensity;
        setEpwIsIntensity(true);
    }
    void setDeviceId(const uint8_t newDeviceId) { m_deviceId = newDeviceId; }
    void setLayer(const uint8_t newLayer) { m_layer = newLayer; }
    void setEcho(const uint8_t newEcho) { m_echo = newEcho; }
    void setReserved(const uint8_t newReserved) { m_reserved = newReserved; }
    void setTimeOffset(const uint32_t newTimeOffset) { m_timeOffset = newTimeOffset; }

    void setFlags(const uint16_t newFlags) { m_flags = newFlags; }
    void setFlag(const Flags flag) { m_flags |= static_cast<uint16_t>(flag); }
    void clearFlag(const Flags flag) { m_flags &= static_cast<uint16_t>(~static_cast<uint16_t>(flag)); }
    void setFlag(const Flags flag, const bool value) { value ? setFlag(flag) : clearFlag(flag); }

    void setGround(const bool isGround = true) { setFlag(Flags::Ground, isGround); }
    void setDirt(const bool isDirt = true) { setFlag(Flags::Dirt, isDirt); }
    void setRain(const bool isRain = true) { setFlag(Flags::Rain, isRain); }
    void setRoadMarking(const bool isRoadMarking = true) { setFlag(Flags::RoadMarking, isRoadMarking); }
    void setThresholdSwitching(const bool isThresholdSwitching = true)
    {
        setFlag(Flags::ThresholdSwitching, isThresholdSwitching);
    }
    void setReflector(const bool isReflector = true) { setFlag(Flags::Reflector, isReflector); }
    void setNearRange(const bool isNearRange = true) { setFlag(Flags::NearRange, isNearRange); }
    void setCurbstone(const bool isCurbstone = true) { setFlag(Flags::Curbstone, isCurbstone); }
    void setLeftCovered(const bool isLeftCovered = true) { setFlag(Flags::LeftCovered, isLeftCovered); }
    void setRightCovered(const bool isRightCovered = true) { setFlag(Flags::RightCovered, isRightCovered); }
    void setBackground(const bool isBackground = true) { setFlag(Flags::Background, isBackground); }
    void setMarker(const bool isMarker = true) { setFlag(Flags::Marker, isMarker); }
    void setTransparent(const bool isTransparent = true) { setFlag(Flags::Transparent, isTransparent); }
    void setDynamic(const bool isDynamic = true) { setFlag(Flags::Dynamic, isDynamic); }
    void setEpwIsIntensity(const bool isEpwIsIntensity = true) { setFlag(Flags::EpwIsIntensity, isEpwIsIntensity); }

    void setSegmentId(const uint16_t newSegmentId) { m_segmentId = newSegmentId; }

public:
    bool operator==(const ScanPointIn2205& other) const;
    bool operator!=(const ScanPointIn2205& other) const { return !((*this) == other); }

protected:
    float m_posX;
    float m_posY;
    float m_posZ;
    float m_epw; // could also be filled with intensity [0.0 - 1.0]
    uint8_t m_deviceId;
    uint8_t m_layer;
    uint8_t m_echo;
    uint8_t m_reserved;
    uint32_t m_timeOffset;
    uint16_t m_flags; // combination of bits from EcuScanPointFlag
    uint16_t m_segmentId;
}; // ScanPointIn2205

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

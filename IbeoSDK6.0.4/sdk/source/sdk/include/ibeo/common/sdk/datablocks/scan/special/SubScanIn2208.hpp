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
//!\date Aug 2, 2013
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/ScanPointIn2208.hpp>

#include <ibeo/common/sdk/Time.hpp>

#include <vector>
#include <istream>
#include <ostream>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class SubScanIn2208
{
public:
    static const uint8_t nbOfReserved   = 6;
    static const uint16_t maxNbOfPoints = 9 * 581;

public:
    using PointVector = std::vector<ScanPointIn2208>;
    enum class Flags : uint8_t
    {
        Laser = 0x01U //!< id of the used laser
        // reserved
    }; // Flags
public:
    SubScanIn2208();
    virtual ~SubScanIn2208();

public:
    //! Equality predicate
    bool operator==(const SubScanIn2208& other) const;

    bool operator!=(const SubScanIn2208& other) const;

public:
    virtual std::streamsize getSerializedSize() const
    {
        return 36 + ScanPointIn2208::getSerializedSize_static() * std::streamsize(scanPoints.size());
    }
    virtual bool deserialize(std::istream& is);
    virtual bool serialize(std::ostream& os) const;

public:
    NTPTime getStartScanTimestamp() const { return startScanTimestamp; }
    NTPTime getEndScanTimestamp() const { return endScanTimestamp; }
    int16_t getStartScanAngle() const { return startScanAngle; }
    int16_t getEndScanAngle() const { return endScanAngle; }
    uint8_t getFlags() const { return flags; }
    uint8_t getMirrorSide() const { return mirrorSide; }
    float getMirrorTiltDeprecated() const { return mirrorTiltDeprecated; }
    uint16_t getMirrorTilt() const { return mirrorTilt; }
    uint8_t getReserved(const uint8_t idx) const { return reserved[idx]; }
    uint32_t getNbOfPoints() const { return uint16_t(scanPoints.size()); }

    const PointVector& getScanPoints() const { return scanPoints; }
    PointVector& getScanPoints() { return scanPoints; }

public:
    void setStartScanTimestamp(const NTPTime newStartScanTimestamp) { startScanTimestamp = newStartScanTimestamp; }
    void setEndScanTimestamp(const NTPTime newEndScanTimestamp) { endScanTimestamp = newEndScanTimestamp; }
    void setStartScanAngle(const int16_t newStartScanAngle) { startScanAngle = newStartScanAngle; }
    void setEndScanAngle(const int16_t newEndScanAngle) { endScanAngle = newEndScanAngle; }
    void setFlags(const uint8_t newFlags) { flags = newFlags; }
    void setMirrorSide(const uint8_t newMirrorSide) { mirrorSide = newMirrorSide; }
    void setMirrorTiltDeprecated(const float newMirrorTiltDeprecated)
    {
        mirrorTiltDeprecated = newMirrorTiltDeprecated;
    }
    void setMirrorTilt(const uint16_t newMirrorTilt) { mirrorTilt = newMirrorTilt; }
    void setReserved(const uint8_t idx, const uint8_t newReserved) { reserved[idx] = newReserved; }

protected:
    NTPTime startScanTimestamp{};
    NTPTime endScanTimestamp{};
    int16_t startScanAngle{0};
    int16_t endScanAngle{0};
    uint8_t flags{};
    uint8_t mirrorSide{0};
    float mirrorTiltDeprecated{0.0F}; //!< deg
    uint16_t mirrorTilt{0}; //!< 1/500 deg
    uint8_t reserved[nbOfReserved]{};
    // uint16_t nbOfPoints
    PointVector scanPoints{};
}; // SubScanIn2208

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

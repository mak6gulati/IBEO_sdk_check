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
//!\date Apr 26, 2012
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/ResolutionInfoIn2205.hpp>
#include <ibeo/common/sdk/RotationOrder.hpp>
#include <ibeo/common/sdk/ScannerType.hpp>
#include <ibeo/common/sdk/TransformationMatrix3d.hpp>
#include <ibeo/common/sdk/Time.hpp>

#include <vector>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class ScannerInfoIn2205
{
public:
    // The scanner info flags are an extension to the scan flags.
    static constexpr uint32_t rotationFlagsShift = 14; //!< Rotation flags start at bit 14 in the scanner info flags.
    static constexpr uint32_t rotationFlagsMask  = 0x07; //!< Size of rotation flags: 3 bit.

public:
    ScannerInfoIn2205();
    ScannerInfoIn2205(const ScannerInfoIn2205& src);
    virtual ~ScannerInfoIn2205();

public:
    static std::streamsize getSerializedSize_static();

public:
    std::streamsize getSerializedSize() const { return getSerializedSize_static(); }
    bool deserialize(std::istream& is);
    bool serialize(std::ostream& os) const;

public:
    uint8_t getDeviceId() const { return m_deviceId; }
    ScannerType getScannerType() const { return m_scannerType; }
    uint16_t getScanNumber() const { return m_scanNumber; }

    uint32_t getScannerStatus() const { return m_scannerStatus; }

    float getStartAngle() const { return m_startAngle; }
    float getEndAngle() const { return m_endAngle; }

    NTPTime getScanStartTime() const { return m_scanStartTime; }
    NTPTime getScanEndTime() const { return m_scanEndTime; }

    NTPTime getScanStartTimeFromDevice() const { return m_scanStartTimeFromDevice; }
    NTPTime getScanEndTimeFromDevice() const { return m_scanEndTimeFromDevice; }

    float getFrequency() const { return m_scanFrequency; }
    float getBeamTilt() const { return m_beamTilt; }

    uint32_t getFlags() const { return m_scanFlags; }

    float getYawAngle() const { return m_yawAngle; }
    float getPitchAngle() const { return m_pitchAngle; }
    float getRollAngle() const { return m_rollAngle; }

    float getOffsetX() const { return m_offsetX; }
    float getOffsetY() const { return m_offsetY; }
    float getOffsetZ() const { return m_offsetZ; }

    RotationOrder getRotationOrder() const
    {
        return static_cast<RotationOrder>((m_scanFlags >> rotationFlagsShift) & rotationFlagsMask);
    }

    //========================================
    //! \brief Create a matrix for converting points from this scanner's coordinate system into vehicle coordinate
    //! system.
    //!
    //! \param[in] initialTransformationMatrix  Rotation matrix for initial transformation (e.g. for adjusting the zero
    //!                                         degree mark on the sensor).
    //! \return Matrix for transfomrming coordinates into vehicle coordinate system.
    //----------------------------------------
    TransformationMatrix3d<float>
    getCoordinateSystemTransformationMatrix(const Matrix3x3<float>& initialTransformationMatrix
                                            = Matrix3x3<float>()) const;

    const std::vector<ResolutionInfoIn2205>& getResolutionInfo() const { return m_ri; }
    std::vector<ResolutionInfoIn2205>& getResolutionInfo() { return m_ri; }

public:
    void setDeviceId(const uint8_t newDeviceID) { m_deviceId = newDeviceID; }
    void setScannerType(const ScannerType newScannerType) { m_scannerType = newScannerType; }
    void setScanNumber(const uint16_t newScanNumber) { m_scanNumber = newScanNumber; }

    void setScannerStatus(const uint32_t newScannerStatus) { m_scannerStatus = newScannerStatus; }

    void setStartAngle(const float newStartAngle) { m_startAngle = newStartAngle; }
    void setEndAngle(const float newEndAngle) { m_endAngle = newEndAngle; }

    void setScanStartTime(const NTPTime newScanStartTime) { m_scanStartTime = newScanStartTime; }
    void setScanEndTime(const NTPTime newScanEndTime) { m_scanEndTime = newScanEndTime; }

    void setScanStartTimeFromDevice(const NTPTime newScanStartTimeFromDevice)
    {
        m_scanStartTimeFromDevice = newScanStartTimeFromDevice;
    }
    void setScanEndTimeFromDevice(const NTPTime newScanEndTimeFromDevice)
    {
        m_scanEndTimeFromDevice = newScanEndTimeFromDevice;
    }

    void setFrequency(const float newFrequency) { m_scanFrequency = newFrequency; }
    void setBeamTilt(const float newBeamTilt) { m_beamTilt = newBeamTilt; }

    void setFlags(const uint32_t newScanFlags) { m_scanFlags = newScanFlags; }

    void setYawAngle(const float newYawAngle) { m_yawAngle = newYawAngle; }
    void setPitchAngle(const float newPitchAngle) { m_pitchAngle = newPitchAngle; }
    void setRollAngle(const float newRollAngle) { m_rollAngle = newRollAngle; }

    void setOffsetX(const float newOffsetX) { m_offsetX = newOffsetX; }
    void setOffsetY(const float newOffsetY) { m_offsetY = newOffsetY; }
    void setOffsetZ(const float newOffsetZ) { m_offsetZ = newOffsetZ; }

    void setRotationOrder(const RotationOrder rotationOrder)
    {
        // rotation order is stored in flag bits
        const auto mask = ~(rotationFlagsMask << rotationFlagsShift);
        m_scanFlags &= mask;
        const auto flag = static_cast<uint32_t>(rotationOrder) << rotationFlagsShift;
        m_scanFlags |= flag;
    }

    void setResolutionInfo(const std::vector<ResolutionInfoIn2205> newResolutionInfo) { m_ri = newResolutionInfo; }

public:
    static const unsigned int nbOfResolutionInfo = 8;

public:
    bool operator==(const ScannerInfoIn2205& other) const;
    bool operator!=(const ScannerInfoIn2205& other) const { return !((*this) == other); }

protected:
    uint8_t m_deviceId;
    ScannerType m_scannerType; // uint8_t
    uint16_t m_scanNumber;

    uint32_t m_scannerStatus;

    float m_startAngle; // TODO: define FLOAT32 // [rad] - between [-pi;pi]
    float m_endAngle; // TODO: define FLOAT32   // [rad] - between [-pi;pi]
    NTPTime m_scanStartTime;
    NTPTime m_scanEndTime;
    NTPTime m_scanStartTimeFromDevice;
    NTPTime m_scanEndTimeFromDevice;
    float m_scanFrequency; // TODO: define FLOAT32  // [Hz]
    float m_beamTilt; // TODO: define FLOAT32       // [rad] - between [-pi;pi]
    uint32_t m_scanFlags;
    float m_yawAngle; // [rad] - between [-pi;pi] - relative to vehicle ref point
    float m_pitchAngle; // [rad] - between [-pi;pi] - relative to vehicle ref point
    float m_rollAngle; // [rad] - between [-pi;pi] - relative to vehicle ref point
    float m_offsetX; // [m] - relative to vehicle ref point
    float m_offsetY; // [m] - relative to vehicle ref point
    float m_offsetZ; // [m] - relative to vehicle ref point
    std::vector<ResolutionInfoIn2205> m_ri;
}; // ScannerInfo

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/ScannerInfoIn2205.hpp>
#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/Math.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

ScannerInfoIn2205::ScannerInfoIn2205()
  : m_deviceId(0),
    m_scannerType(ScannerType::Invalid),
    m_scanNumber(0),
    m_scannerStatus(0),
    m_startAngle(0.),
    m_endAngle(0.),
    m_scanStartTime(0),
    m_scanEndTime(0),
    m_scanStartTimeFromDevice(0),
    m_scanEndTimeFromDevice(0),
    m_scanFrequency(0.),
    m_beamTilt(0.),
    m_scanFlags(0),
    m_yawAngle(0.),
    m_pitchAngle(0.),
    m_rollAngle(0.),
    m_offsetX(0.),
    m_offsetY(0.),
    m_offsetZ(0.),
    m_ri(8)
{}

//==============================================================================

ScannerInfoIn2205::ScannerInfoIn2205(const ScannerInfoIn2205& other)
  : m_deviceId(other.m_deviceId),
    m_scannerType(other.m_scannerType),
    m_scanNumber(other.m_scanNumber),
    m_scannerStatus(other.m_scannerStatus),
    m_startAngle(other.m_startAngle),
    m_endAngle(other.m_endAngle),
    m_scanStartTime(other.m_scanStartTime),
    m_scanEndTime(other.m_scanEndTime),
    m_scanStartTimeFromDevice(other.m_scanStartTimeFromDevice),
    m_scanEndTimeFromDevice(other.m_scanEndTimeFromDevice),
    m_scanFrequency(other.m_scanFrequency),
    m_beamTilt(other.m_beamTilt),
    m_scanFlags(other.m_scanFlags),
    m_yawAngle(other.m_yawAngle),
    m_pitchAngle(other.m_pitchAngle),
    m_rollAngle(other.m_rollAngle),

    m_offsetX(other.m_offsetX),
    m_offsetY(other.m_offsetY),
    m_offsetZ(other.m_offsetZ),
    m_ri(other.m_ri.size()) // only set the size here
{
    m_ri = other.m_ri;
}

//==============================================================================

ScannerInfoIn2205::~ScannerInfoIn2205() {}

//==============================================================================

bool ScannerInfoIn2205::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_deviceId);

    uint8_t st;
    ibeo::common::sdk::readBE(is, st);
    m_scannerType = ScannerType(st);

    ibeo::common::sdk::readBE(is, m_scanNumber);

    ibeo::common::sdk::readBE(is, m_scannerStatus);

    ibeo::common::sdk::readBE(is, m_startAngle);
    ibeo::common::sdk::readBE(is, m_endAngle);

    ibeo::common::sdk::readBE(is, m_scanStartTime);
    ibeo::common::sdk::readBE(is, m_scanEndTime);

    ibeo::common::sdk::readBE(is, m_scanStartTimeFromDevice);
    ibeo::common::sdk::readBE(is, m_scanEndTimeFromDevice);

    ibeo::common::sdk::readBE(is, m_scanFrequency);
    ibeo::common::sdk::readBE(is, m_beamTilt);

    ibeo::common::sdk::readBE(is, m_scanFlags);

    ibeo::common::sdk::readBE(is, m_yawAngle);
    ibeo::common::sdk::readBE(is, m_pitchAngle);
    ibeo::common::sdk::readBE(is, m_rollAngle);

    ibeo::common::sdk::readBE(is, m_offsetX);
    ibeo::common::sdk::readBE(is, m_offsetY);
    ibeo::common::sdk::readBE(is, m_offsetZ);

    for (unsigned int i = 0; i < nbOfResolutionInfo; i++)
    {
        m_ri[i].deserialize(is);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}
//==============================================================================

//static
std::streamsize ScannerInfoIn2205::getSerializedSize_static()
{
    return 2 * std::streamsize(sizeof(uint8_t)) + std::streamsize(sizeof(uint16_t)) + std::streamsize(sizeof(uint32_t))
           + 2 * std::streamsize(sizeof(float)) + 4 * std::streamsize(sizeof(NTPTime))
           + 2 * std::streamsize(sizeof(float)) + std::streamsize(sizeof(uint32_t)) + 6 * std::streamsize(sizeof(float))
           + 8 * ResolutionInfoIn2205::getSerializedSize_static();
}

//==============================================================================

bool ScannerInfoIn2205::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_deviceId);

    ibeo::common::sdk::writeBE(os, uint8_t(m_scannerType));

    ibeo::common::sdk::writeBE(os, m_scanNumber);

    ibeo::common::sdk::writeBE(os, m_scannerStatus);

    ibeo::common::sdk::writeBE(os, m_startAngle);
    ibeo::common::sdk::writeBE(os, m_endAngle);

    ibeo::common::sdk::writeBE(os, m_scanStartTime);
    ibeo::common::sdk::writeBE(os, m_scanEndTime);

    ibeo::common::sdk::writeBE(os, m_scanStartTimeFromDevice);
    ibeo::common::sdk::writeBE(os, m_scanEndTimeFromDevice);

    ibeo::common::sdk::writeBE(os, m_scanFrequency);
    ibeo::common::sdk::writeBE(os, m_beamTilt);

    ibeo::common::sdk::writeBE(os, m_scanFlags);

    ibeo::common::sdk::writeBE(os, m_yawAngle);
    ibeo::common::sdk::writeBE(os, m_pitchAngle);
    ibeo::common::sdk::writeBE(os, m_rollAngle);

    ibeo::common::sdk::writeBE(os, m_offsetX);
    ibeo::common::sdk::writeBE(os, m_offsetY);
    ibeo::common::sdk::writeBE(os, m_offsetZ);

    for (unsigned int i = 0; i < nbOfResolutionInfo; i++)
    {
        m_ri[i].serialize(os);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================

TransformationMatrix3d<float>
ScannerInfoIn2205::getCoordinateSystemTransformationMatrix(const Matrix3x3<float>& initialTransformationMatrix) const
{
    // Create transformation matrix.
    Vector3<float> scannerPosition{getOffsetX(), getOffsetY(), getOffsetZ()};

    TransformationMatrix3d<float> transformationMatrix{initialTransformationMatrix, scannerPosition};

    switch (getRotationOrder())
    {
    case RotationOrder::RollPitchYaw:
        transformationMatrix.rotateX(getRollAngle()); // roll  = rotate X
        transformationMatrix.rotateY(getPitchAngle()); // pitch = rotate Y
        transformationMatrix.rotateZ(getYawAngle()); // yaw   = rotate Z
        break;

    case RotationOrder::RollYawPitch:
        transformationMatrix.rotateX(getRollAngle()); // roll  = rotate X
        transformationMatrix.rotateZ(getYawAngle()); // yaw   = rotate Z
        transformationMatrix.rotateY(getPitchAngle()); // pitch = rotate Y
        break;

    case RotationOrder::PitchRollYaw:
        transformationMatrix.rotateY(getPitchAngle()); // pitch = rotate Y
        transformationMatrix.rotateX(getRollAngle()); // roll  = rotate X
        transformationMatrix.rotateZ(getYawAngle()); // yaw   = rotate Z
        break;

    case RotationOrder::PitchYawRoll:
        transformationMatrix.rotateY(getPitchAngle()); // pitch = rotate Y
        transformationMatrix.rotateZ(getYawAngle()); // yaw   = rotate Z
        transformationMatrix.rotateX(getRollAngle()); // roll  = rotate X
        break;

    case RotationOrder::YawRollPitch:
        transformationMatrix.rotateZ(getYawAngle()); // yaw   = rotate Z
        transformationMatrix.rotateX(getRollAngle()); // roll  = rotate X
        transformationMatrix.rotateY(getPitchAngle()); // pitch = rotate Y
        break;

    case RotationOrder::YawPitchRoll:
        transformationMatrix.rotateZ(getYawAngle()); // yaw   = rotate Z
        transformationMatrix.rotateY(getPitchAngle()); // pitch = rotate Y
        transformationMatrix.rotateX(getRollAngle()); // roll  = rotate X
        break;

    default:
        throw std::logic_error("Unknown rotation order!");
    }

    return transformationMatrix;
}

//==============================================================================

bool ScannerInfoIn2205::operator==(const ScannerInfoIn2205& other) const
{
    if (m_deviceId != other.getDeviceId())
        return false;

    if (m_scannerType != other.getScannerType())
        return false;

    if (m_scanNumber != other.getScanNumber())
        return false;

    if (m_scannerStatus != other.getScannerStatus())
        return false;

    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(m_startAngle, other.getStartAngle()))
        return false;

    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(m_endAngle, other.getEndAngle()))
        return false;

    if (m_scanStartTime != other.getScanStartTime())
        return false;

    if (m_scanEndTime != other.getScanEndTime())
        return false;

    if (m_scanStartTimeFromDevice != other.getScanStartTimeFromDevice())
        return false;

    if (m_scanEndTimeFromDevice != other.getScanEndTimeFromDevice())
        return false;

    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(m_scanFrequency, other.getFrequency()))
        return false;

    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(m_beamTilt, other.getBeamTilt()))
        return false;

    if (m_scanFlags != other.getFlags())
        return false;

    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(m_yawAngle, other.getYawAngle()))
        return false;

    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(m_pitchAngle, other.getPitchAngle()))
        return false;

    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(m_rollAngle, other.getRollAngle()))
        return false;

    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(m_offsetX, other.getOffsetX()))
        return false;

    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(m_offsetY, other.getOffsetY()))
        return false;

    if (!ibeo::common::sdk::fuzzyFloatEqualT<7>(m_offsetZ, other.getOffsetZ()))
        return false;

    if (m_ri.size() != other.getResolutionInfo().size())
        return false;

    for (std::size_t riIdx = 0; riIdx < m_ri.size(); ++riIdx)
    {
        if (m_ri[riIdx] != (other.getResolutionInfo())[riIdx])
            return false;
    }

    return true;
}

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

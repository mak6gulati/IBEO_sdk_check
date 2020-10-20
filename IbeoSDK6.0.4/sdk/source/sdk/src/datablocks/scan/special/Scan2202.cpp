//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 15, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/scan/special/Scan2202.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

ibeo::common::logging::LoggerSPtr Scan2202::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

Scan2202::Scan2202() : SpecializedDataContainer() {}

//==============================================================================

Scan2202::~Scan2202() {}

//==============================================================================

bool Scan2202::nbOfAngleTicksPerRotationCheck() const
{
    if (m_angleTicksPerRotation != nbOfAngleTicksPerRotation)
    {
        LOGERROR(logger,
                 "Read scan #" << this->m_scanNumber << ": number of angle ticks per rotation are "
                               << this->m_angleTicksPerRotation << " expected: " << nbOfAngleTicksPerRotation
                               << "  - discarding scan.");
        return false;
    }
    return true;
}
//==============================================================================

bool operator==(const Scan2202& lhs, const Scan2202& rhs)
{
    if ((lhs.getScanNumber() == rhs.getScanNumber()) && (lhs.getScannerStatus() == rhs.getScannerStatus())
        && (lhs.getSyncPhaseOffset() == rhs.getSyncPhaseOffset())
        && (lhs.getStartTimestamp() == rhs.getStartTimestamp())

        && (lhs.getEndTimestamp() == rhs.getEndTimestamp())
        && (lhs.getAngleTicksPerRotation() == rhs.getAngleTicksPerRotation())
        && (lhs.getStartAngleTicks() == rhs.getStartAngleTicks()) && (lhs.getEndAngleTicks() == rhs.getEndAngleTicks())

        && (lhs.getNumberOfScanPoints() == rhs.getNumberOfScanPoints())
        && (lhs.getMountingPositionYawAngleTicks() == rhs.getMountingPositionYawAngleTicks())
        && (lhs.getMountingPositionPitchAngleTicks() == rhs.getMountingPositionPitchAngleTicks())
        && (lhs.getMountingPositionRollAngleTicks() == rhs.getMountingPositionRollAngleTicks())

        && (lhs.getMountingPositionCmX() == rhs.getMountingPositionCmX())
        && (lhs.getMountingPositionCmY() == rhs.getMountingPositionCmY())
        && (lhs.getMountingPositionCmZ() == rhs.getMountingPositionCmZ()) && (lhs.getFlags() == rhs.getFlags()))
    {
        return (lhs.getScanPoints() == rhs.getScanPoints());
    }

    return false;
}

//==============================================================================

bool operator!=(const Scan2202& lhs, const Scan2202& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

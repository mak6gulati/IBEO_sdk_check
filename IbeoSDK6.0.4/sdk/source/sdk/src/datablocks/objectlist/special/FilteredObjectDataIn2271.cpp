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
//!\date Apr 23, 2014
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectlist/special/FilteredObjectDataIn2271.hpp>

#include <ibeo/common/sdk/ObjectBasic.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize FilteredObjectDataIn2271::getSerializedSize() const
{
    if (!m_isValid)
    {
        return 0;
    }

    return std::streamsize(sizeof(uint8_t)) + 2 * std::streamsize(sizeof(uint16_t)) + std::streamsize(sizeof(uint8_t))

           + std::streamsize(sizeof(uint16_t)) // rel t of measure
           + serializedSize(m_positionClosestObjectPoint)

           + serializedSize(m_relativeVelocity) + serializedSize(m_relativeVelocitySigma)
           + 2 * std::streamsize(sizeof(uint8_t)) + std::streamsize(sizeof(uint16_t)) // class age

           + std::streamsize(sizeof(uint16_t)) + serializedSize(m_objectBoxSize) + serializedSize(m_objectBoxSizeSigma)
           + 2 * std::streamsize(sizeof(uint16_t)) + 2 * std::streamsize(sizeof(uint8_t)) // ... refPointLoc
           + serializedSize(m_referencePointCoord) + serializedSize(m_referencePointCoordSigma)
           + std::streamsize(sizeof(int16_t)) + std::streamsize(sizeof(uint8_t)) // exist Prob

           + serializedSize(m_absoluteVelocity) + serializedSize(m_absoluteVelocitySigma)
           + std::streamsize(sizeof(int16_t)) + serializedSize(m_acceleration) + serializedSize(m_accelerationSigma)
           + std::streamsize(sizeof(int16_t)) // accCorrCoeff
           + 2 * std::streamsize(sizeof(uint16_t)) // yawRate, yawRateSigma

           + std::streamsize(sizeof(uint8_t)) // nb of points
           + (m_hasContourPoints ? m_possibleNbOfContourPoints * ContourPointIn2271::getSerializedSize_static() : 0);
}

//==============================================================================

bool FilteredObjectDataIn2271::deserialize(std::istream& is)
{
    if (!m_isValid)
    {
        return true;
    }

    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_priority);

    ibeo::common::sdk::readBE(is, m_objectAge);
    ibeo::common::sdk::readBE(is, m_hiddenStatusAge);
    ibeo::common::sdk::readBE(is, m_dynamicFlags);

    ibeo::common::sdk::readBE(is, m_relativeTimeOfMeasure);
    ibeo::common::sdk::readBE(is, m_positionClosestObjectPoint);

    ibeo::common::sdk::readBE(is, m_relativeVelocity);
    ibeo::common::sdk::readBE(is, m_relativeVelocitySigma);
    ibeo::common::sdk::readBE(is, m_classification);
    ibeo::common::sdk::readBE(is, m_classificationQuality);
    ibeo::common::sdk::readBE(is, m_classificationAge);

    ibeo::common::sdk::readBE(is, m_reserved);
    ibeo::common::sdk::readBE(is, m_objectBoxSize);
    ibeo::common::sdk::readBE(is, m_objectBoxSizeSigma);
    ibeo::common::sdk::readBE(is, m_objectBoxOrientation);
    ibeo::common::sdk::readBE(is, m_objectBoxOrientationSigma);
    ibeo::common::sdk::readBE(is, m_objectBoxHeight);
    ibeo::common::sdk::readBE<8>(is, m_referencePointLocation);
    ibeo::common::sdk::readBE(is, m_referencePointCoord);
    ibeo::common::sdk::readBE(is, m_referencePointCoordSigma);
    ibeo::common::sdk::readBE(is, m_referencePointPositionCorrCoeff);
    ibeo::common::sdk::readBE(is, m_existenceProbaility);

    ibeo::common::sdk::readBE(is, m_absoluteVelocity);
    ibeo::common::sdk::readBE(is, m_absoluteVelocitySigma);
    ibeo::common::sdk::readBE(is, m_velocityCorrCoeff);
    ibeo::common::sdk::readBE(is, m_acceleration);
    ibeo::common::sdk::readBE(is, m_accelerationSigma);
    ibeo::common::sdk::readBE(is, m_accelerationCorrCoeff);
    ibeo::common::sdk::readBE(is, m_yawRate);
    ibeo::common::sdk::readBE(is, m_yawRateSigma);

    ibeo::common::sdk::readBE(is, m_possibleNbOfContourPoints);
    // only if this FilteredObjectAttributes object is dedicated to
    // have contour points, nbOfContourPoints presents the number
    // of contour points that have been attached.
    // Otherwise nbOfContourPoints is just the number of contour
    // points that would have been written in case it was allowed to.
    if (m_hasContourPoints)
    {
        m_contourPoints.resize(m_possibleNbOfContourPoints);
        for (ContourPointIn2271& cp : m_contourPoints)
        {
            cp.deserialize(is);
        }
    }
    else
    {
        m_contourPoints.clear();
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize());
}

//==============================================================================

bool FilteredObjectDataIn2271::serialize(std::ostream& os) const
{
    if (!m_isValid)
    {
        return true;
    }

    const int64_t startPos = streamposToInt64(os.tellp());
    ibeo::common::sdk::writeBE(os, m_priority);

    ibeo::common::sdk::writeBE(os, m_objectAge);
    ibeo::common::sdk::writeBE(os, m_hiddenStatusAge);
    ibeo::common::sdk::writeBE(os, m_dynamicFlags);

    ibeo::common::sdk::writeBE(os, m_relativeTimeOfMeasure);
    ibeo::common::sdk::writeBE(os, m_positionClosestObjectPoint);

    ibeo::common::sdk::writeBE(os, m_relativeVelocity);
    ibeo::common::sdk::writeBE(os, m_relativeVelocitySigma);
    ibeo::common::sdk::writeBE(os, m_classification);
    ibeo::common::sdk::writeBE(os, m_classificationQuality);
    ibeo::common::sdk::writeBE(os, m_classificationAge);

    ibeo::common::sdk::writeBE(os, m_reserved);
    ibeo::common::sdk::writeBE(os, m_objectBoxSize);
    ibeo::common::sdk::writeBE(os, m_objectBoxSizeSigma);
    ibeo::common::sdk::writeBE(os, m_objectBoxOrientation);
    ibeo::common::sdk::writeBE(os, m_objectBoxOrientationSigma);
    ibeo::common::sdk::writeBE(os, m_objectBoxHeight);
    ibeo::common::sdk::writeBE<8>(os, m_referencePointLocation);
    ibeo::common::sdk::writeBE(os, m_referencePointCoord);
    ibeo::common::sdk::writeBE(os, m_referencePointCoordSigma);
    ibeo::common::sdk::writeBE(os, m_referencePointPositionCorrCoeff);
    ibeo::common::sdk::writeBE(os, m_existenceProbaility);

    ibeo::common::sdk::writeBE(os, m_absoluteVelocity);
    ibeo::common::sdk::writeBE(os, m_absoluteVelocitySigma);
    ibeo::common::sdk::writeBE(os, m_velocityCorrCoeff);
    ibeo::common::sdk::writeBE(os, m_acceleration);
    ibeo::common::sdk::writeBE(os, m_accelerationSigma);
    ibeo::common::sdk::writeBE(os, m_accelerationCorrCoeff);
    ibeo::common::sdk::writeBE(os, m_yawRate);
    ibeo::common::sdk::writeBE(os, m_yawRateSigma);

    // only if this UnfilteredObjectData object is dedicated to
    // have contour points, the contour points will be stored.
    if (m_hasContourPoints)
    {
        // Write current number of contour points.
        ibeo::common::sdk::writeBE(os, static_cast<uint8_t>(m_contourPoints.size()));

        // Write contour points.
        for (const ContourPointIn2271& cp : m_contourPoints)
        {
            cp.serialize(os);
        }
    }
    else
    {
        // No contour points allowed -> write only number of possible contour points.
        ibeo::common::sdk::writeBE(os, m_possibleNbOfContourPoints);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================
//==============================================================================
//==============================================================================

bool operator==(const ibeo::common::sdk::FilteredObjectDataIn2271& lhs,
                const ibeo::common::sdk::FilteredObjectDataIn2271& rhs)
{
    if (lhs.isValid() != rhs.isValid())
    {
        return false;
    }
    if (!lhs.isValid())
    {
        return true;
    } // if the structure is not valid, its contents is irrelevant.

    if (lhs.getPriority() != rhs.getPriority())
    {
        return false;
    }

    if (lhs.getObjectAge() != rhs.getObjectAge())
    {
        return false;
    }
    if (lhs.getHiddenStatusAge() != rhs.getHiddenStatusAge())
    {
        return false;
    }
    if (lhs.getDynamicFlags() != rhs.getDynamicFlags())
    {
        return false;
    }

    if (lhs.getRelativeTimeOfMeasure() != rhs.getRelativeTimeOfMeasure())
    {
        return false;
    }
    if (lhs.getPositionClosestObjectPoint() != rhs.getPositionClosestObjectPoint())
    {
        return false;
    }

    if (lhs.getRelativeVelocity() != rhs.getRelativeVelocity())
    {
        return false;
    }
    if (lhs.getRelativeVelocitySigma() != rhs.getRelativeVelocitySigma())
    {
        return false;
    }

    if (lhs.getClassification() != rhs.getClassification())
    {
        return false;
    }
    if (lhs.getClassificationQuality() != rhs.getClassificationQuality())
    {
        return false;
    }
    if (lhs.getClassificationAge() != rhs.getClassificationAge())
    {
        return false;
    }

    if (lhs.getReserved() != rhs.getReserved())
    {
        return false;
    }

    if (lhs.getObjectBoxSize() != rhs.getObjectBoxSize())
    {
        return false;
    }
    if (lhs.getObjectBoxSizeSigma() != rhs.getObjectBoxSizeSigma())
    {
        return false;
    }
    if (lhs.getObjectBoxOrientation() != rhs.getObjectBoxOrientation())
    {
        return false;
    }
    if (lhs.getObjectBoxOrientationSigma() != rhs.getObjectBoxOrientationSigma())
    {
        return false;
    }
    if (lhs.getObjectBoxHeight() != rhs.getObjectBoxHeight())
    {
        return false;
    }

    if (lhs.getReferencePointLocation() != rhs.getReferencePointLocation())
    {
        return false;
    }
    if (lhs.getReferencePointCoord() != rhs.getReferencePointCoord())
    {
        return false;
    }
    if (lhs.getReferencePointCoordSigma() != rhs.getReferencePointCoordSigma())
    {
        return false;
    }
    if (lhs.getReferencePointPositionCorrCoeff() != rhs.getReferencePointPositionCorrCoeff())
    {
        return false;
    }

    if (lhs.getExistenceProbaility() != rhs.getExistenceProbaility())
    {
        return false;
    }

    if (lhs.getAbsoluteVelocity() != rhs.getAbsoluteVelocity())
    {
        return false;
    }
    if (lhs.getAbsoluteVelocitySigma() != rhs.getAbsoluteVelocitySigma())
    {
        return false;
    }
    if (lhs.getVelocityCorrCoeff() != rhs.getVelocityCorrCoeff())
    {
        return false;
    }

    if (lhs.getAcceleration() != rhs.getAcceleration())
    {
        return false;
    }
    if (lhs.getAccelerationSigma() != rhs.getAccelerationSigma())
    {
        return false;
    }
    if (lhs.getAccelerationCorrCoeff() != rhs.getAccelerationCorrCoeff())
    {
        return false;
    }

    if (lhs.getYawRate() != rhs.getYawRate())
    {
        return false;
    }
    if (lhs.getYawRateSigma() != rhs.getYawRateSigma())
    {
        return false;
    }

    if (lhs.getPossibleNbOfContourPoints() != rhs.getPossibleNbOfContourPoints())
    {
        return false;
    }

    if (lhs.hasContourPoints() != rhs.hasContourPoints())
    {
        return false;
    }
    if (lhs.hasContourPoints())
    {
        if (lhs.getContourPoints() != rhs.getContourPoints())
        {
            return false;
        }
    }
    return true;
}
//==============================================================================

bool operator!=(const ibeo::common::sdk::FilteredObjectDataIn2271& lhs,
                const ibeo::common::sdk::FilteredObjectDataIn2271& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

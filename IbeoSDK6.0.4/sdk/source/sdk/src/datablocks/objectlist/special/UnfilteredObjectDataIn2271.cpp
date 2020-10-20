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

#include <ibeo/common/sdk/datablocks/objectlist/special/UnfilteredObjectDataIn2271.hpp>

#include <ibeo/common/sdk/ObjectBasic.hpp>
#include <ibeo/common/sdk/io.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize UnfilteredObjectDataIn2271::getSerializedSize() const
{
    if (!m_isValid)
    {
        return 0;
    }

    return serializedSize(m_priority) + serializedSize(m_relativeTimeOfMeasure)
           + serializedSize(m_positionClosestObjectPoint) + serializedSize(m_reserved) + serializedSize(m_objectBoxSize)
           + serializedSize(m_objectBoxSizeSigma) + serializedSize(m_objectBoxOrientation)
           + serializedSize(m_objectBoxOrientationSigma) + serializedSize(m_objectBoxHeight)
           + serializedSize<uint8_t>(static_cast<uint8_t>(m_referencePointLocation))
           + serializedSize(m_referencePointCoord) + serializedSize(m_referencePointCoordSigma)
           + serializedSize(m_referencePointPositionCorrCoeff) + serializedSize(m_existenceProbaility)
           + serializedSize(m_possibleNbOfContourPoints)
           + (m_hasContourPoints ? m_possibleNbOfContourPoints * ContourPointIn2271::getSerializedSize_static() : 0);
}

//==============================================================================

bool UnfilteredObjectDataIn2271::deserialize(std::istream& is)
{
    if (!m_isValid)
    {
        return true;
    }

    const int64_t startPos = streamposToInt64(is.tellg());

    ibeo::common::sdk::readBE(is, m_priority);
    ibeo::common::sdk::readBE(is, m_relativeTimeOfMeasure);
    ibeo::common::sdk::readBE(is, m_positionClosestObjectPoint);
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

    ibeo::common::sdk::readBE(is, m_possibleNbOfContourPoints);
    // only if this UnfilteredObjectAttributes object is dedicated to
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

bool UnfilteredObjectDataIn2271::serialize(std::ostream& os) const
{
    if (!m_isValid)
    {
        return true;
    }

    const int64_t startPos = streamposToInt64(os.tellp());

    ibeo::common::sdk::writeBE(os, m_priority);
    ibeo::common::sdk::writeBE(os, m_relativeTimeOfMeasure);
    ibeo::common::sdk::writeBE(os, m_positionClosestObjectPoint);
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

    if (!m_contourPoints.empty())
    {
        m_possibleNbOfContourPoints = static_cast<uint8_t>(m_contourPoints.size());
    }

    ibeo::common::sdk::writeBE(os, m_possibleNbOfContourPoints);

    // only if this UnfilteredObjectAttributes object is dedicated to
    // have contour points, the contour points will be stored.
    if (m_hasContourPoints)
    {
        for (const ContourPointIn2271& cp : m_contourPoints)
        {
            cp.serialize(os);
        }
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize());
}

//==============================================================================
//==============================================================================
//==============================================================================

bool operator==(const UnfilteredObjectDataIn2271& lhs, const UnfilteredObjectDataIn2271& rhs)
{
    if (lhs.isValid() != rhs.isValid())
    {
        return false;
    }
    if (!lhs.isValid())
    {
        return true;
    } // if the structure is not valid, its contents is irrelevant.

    if (lhs.hasContourPoints() != rhs.hasContourPoints())
    {
        return false;
    }

    if (lhs.getPriority() != rhs.getPriority())
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

    if (lhs.getPossibleNbOfContourPoints() != rhs.getPossibleNbOfContourPoints())
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

bool operator!=(const UnfilteredObjectDataIn2271& lhs, const UnfilteredObjectDataIn2271& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Apr 13, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/objectlist/Object.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectIn2281.hpp>

//==============================================================================
namespace {
//==============================================================================
// Local helper functions
//==============================================================================

//calculates m1 * m2, stores the result in result
template<uint32_t x1, uint32_t y1, uint32_t y2>
static void multiply(const float (&m1)[x1][y1], const float (&m2)[y1][y2], float (&result)[x1][y2])
{
    for (uint32_t i = 0; i < x1; ++i)
    {
        for (uint32_t j = 0; j < y2; ++j)
        {
            float temp = 0;
            for (uint32_t k = 0; k < y1; ++k)
            {
                temp += m1[i][k] * m2[k][j];
            }
            result[i][j] = temp;
        }
    }
}

//==============================================================================

//transposes the SECOND matrix only
//i.e. result = m1 * m2'
template<uint32_t x1, uint32_t y1, uint32_t y2>
static void multiplyTranspose(const float (&m1)[x1][y1], const float (&m2)[y2][y1], float (&result)[x1][y2])
{
    for (uint32_t i = 0; i < x1; ++i)
    {
        for (uint32_t j = 0; j < y2; ++j)
        {
            float temp = 0;
            for (uint32_t k = 0; k < y1; ++k)
            {
                temp += m1[i][k] * m2[j][k];
            }
            result[i][j] = temp;
        }
    }
}

//==============================================================================
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

float Object::getAbsoluteVelocityCorrCoeff() const
{
    float velocityCorrCoeff = NaN; // Assuming value not given.

    if (m_measurementList.contains(ObjectIn2281::mkey_VelocityCorrCoeff))
    {
        // Velocity correlation coefficient found in measurements.
        const Measurement& velocityCorrCoeffMeasurement
            = *m_measurementList.getMeasurement(ObjectIn2281::mkey_VelocityCorrCoeff);

        switch (velocityCorrCoeffMeasurement.getMeasurementType())
        {
        case Measurement::MeasurementType::Float:
            // Value has already the correct type -> no conversion necessary.
            velocityCorrCoeff = velocityCorrCoeffMeasurement.getData<float>();
            break;

        case Measurement::MeasurementType::INT16: //no break
        case Measurement::MeasurementType::INT32:
            // Scale by 1/32767 to convert from integer.
            velocityCorrCoeff
                = velocityCorrCoeffMeasurement.getAs<float>() / static_cast<float>(std::numeric_limits<int16_t>::max());
            break;

        default:
            // Unknown type -> treat value as not given.
            break;
        }
    }
    // else: velocity correction coefficient is not in measurements.

    return velocityCorrCoeff;
}

//==============================================================================

float ibeo::common::sdk::Object::getLongitudinalAcceleration() const
{
    float v = m_absoluteVelocity.getLength();
    if (v < MinimumVelocityForLongitudinalAcceleration)
    {
        return m_acceleration.getLength();
    }

    //project onto velocity vector.
    return m_acceleration * m_absoluteVelocity / v;
}

//==============================================================================

float ibeo::common::sdk::Object::getLongitudinalAccelerationSigma() const
{
    //rotate the covariance matrix by the negative velocity angle, then take the x component.
    const float v = m_absoluteVelocity.getLength();
    if (v < MinimumVelocityForLongitudinalAcceleration)
        return m_absoluteVelocitySigma.getLength();

    const float c = m_absoluteVelocity.getX() / v; //cos(-vel angle)
    const float s = -m_absoluteVelocity.getY() / v; //sin(-vel angle)

    const float sigma_x = m_absoluteVelocitySigma.getX();
    const float sigma_y = m_absoluteVelocitySigma.getY();
    const float covar   = getAbsoluteVelocityCorrCoeff() * sigma_x * sigma_y;

    return sqrtf(powf(c * sigma_x, 2) - 2 * covar * s * c + powf(s * sigma_y, 2));
}

//==============================================================================

void Object::fillAccelerationFields(const float longAcc, const float longAccSigma)
{
    // First lateral acceleration (only a function of velocity and yaw rate):
    const float vx = m_absoluteVelocity.getX();
    const float vy = m_absoluteVelocity.getY();

    // Velocity covariance matrix
    const float s2vx = powf(m_absoluteVelocitySigma.getX(), 2);
    const float s2vy = powf(m_absoluteVelocitySigma.getY(), 2);
    const float s2vxy
        = m_absoluteVelocitySigma.getX() * m_absoluteVelocitySigma.getY() * getAbsoluteVelocityCorrCoeff();

    const float s2w = m_yawRateSigma * m_yawRateSigma;
    const float w2  = m_yawRate * m_yawRate;

    const Vector2<float> alat2D(-vy * m_yawRate, vx * m_yawRate);

    // Acceleration covariance matrix
    float s2ax  = s2vy * w2 + s2w * vy * vy;
    float s2ay  = s2vx * w2 + s2w * vx * vx;
    float s2axy = -s2vxy * w2 - s2w * vx * vy;

    // Now longitudinal acceleration:
    const float v        = m_absoluteVelocity.getLength();
    const float s2a_long = longAccSigma * longAccSigma;
    Vector2<float> along2D;

    if (v < 1e-5f)
    {
        // If the velocity angle cannot be determined, we just assume 0 for the angle. and make the variance a circle.
        // This is not correct, we lose a lot of information. but there is no way to do it correctly.
        along2D = Vector2<float>(longAcc, 0);
        s2ax += s2a_long;
        s2ay += s2a_long;
    }
    else
    {
        const float vinv  = 1.0F / v;
        const float vinv3 = vinv * vinv * vinv;
        along2D           = m_absoluteVelocity * longAcc * vinv;

        const float J[2][3]        = {{vy * vy * longAcc * vinv3, -vx * vy * longAcc * vinv3, vx * vinv},
                               {-vx * vy * longAcc * vinv3, vx * vx * longAcc * vinv3, vy * vinv}};
        const float covInput[3][3] = {{s2vx, s2vxy, 0}, {s2vxy, s2vy, 0}, {0, 0, s2a_long}};
        float temp[2][3];
        float result[2][2];
        multiply<2, 3, 3>(J, covInput, temp);
        multiplyTranspose<2, 3, 2>(temp, J, result);

        s2ax += result[0][0];
        s2axy += result[0][1];
        s2ay += result[1][1];
    }

    m_acceleration      = alat2D + along2D;
    m_accelerationSigma = Vector2<float>(sqrtf(s2ax), sqrtf(s2ay));

    if (m_measurementList.contains(ObjectIn2281::mkey_AccelerationCorrCoeff))
    {
        // Acceleration correlation coefficient found in measurements -> use it.
        const Measurement& accelerationCorrCoeffMeasurement
            = *m_measurementList.getMeasurement(ObjectIn2281::mkey_AccelerationCorrCoeff);

        switch (accelerationCorrCoeffMeasurement.getMeasurementType())
        {
        case Measurement::MeasurementType::Float:
            // Value has already the correct type -> no conversion necessary.
            m_accelerationCorrCoeff = accelerationCorrCoeffMeasurement.getData<float>();
            break;

        case Measurement::MeasurementType::INT16: //no break
        case Measurement::MeasurementType::INT32:
            // Scale by 1/32767 to convert from integer.
            m_accelerationCorrCoeff = accelerationCorrCoeffMeasurement.getAs<float>()
                                      / static_cast<float>(std::numeric_limits<int16_t>::max());
            break;

        default:
            // Unknown type -> treat value as not given.
            break;
        } // switch
    }
    else
    {
        // Acceleration correction coefficient is not in measurements -> calculate it
        const float c           = s2axy / sqrtf(s2ax * s2ay);
        m_accelerationCorrCoeff = (c < -1) ? -1 : ((c > 1) ? 1 : c);
    }
}

//==============================================================================

Vector2<float> Object::getObjectBoxPosition(const RefPointBoxLocation targetRefPointLocation) const
{
    // Assert that target and current reference point location are in the interval from CenterOfGravity to ObjectCenter!
    if ((targetRefPointLocation < RefPointBoxLocation::CenterOfGravity)
        || (RefPointBoxLocation::ObjectCenter < targetRefPointLocation))
    {
        throw std::invalid_argument(
            "targetRefPointLocation must be in the interval from CenterOfGravity to ObjectCenter!");
    }
    if ((m_referencePointLocation < RefPointBoxLocation::CenterOfGravity)
        || (RefPointBoxLocation::ObjectCenter < m_referencePointLocation))
    {
        throw std::runtime_error(
            "m_referencePointLocation must be in the interval from CenterOfGravity to ObjectCenter!");
    }

    const std::vector<int> currRefPtDirs(getDirectionVector(m_referencePointLocation));
    const std::vector<int> targetRefPtDirs(getDirectionVector(targetRefPointLocation));

    const float sizeXh = 0.5F * m_objectBoxSize.getX();
    const float sizeYh = 0.5F * m_objectBoxSize.getY();
    const float cca    = std::cos(m_courseAngle);
    const float sca    = std::sin(m_courseAngle);
    const Vector2<float> halfLength(cca * sizeXh, sca * sizeXh);
    const Vector2<float> halfWidth(-sca * sizeYh, cca * sizeYh);

    const int dl = targetRefPtDirs.at(0) - currRefPtDirs.at(0);
    const int db = targetRefPtDirs.at(1) - currRefPtDirs.at(1);

    return m_referencePointCoord + halfLength * static_cast<float>(dl) + halfWidth * static_cast<float>(db);
}

//==============================================================================

std::vector<int> Object::getDirectionVector(const RefPointBoxLocation location)
{
    int xDir;
    int yDir;

    switch (location)
    {
    case RefPointBoxLocation::CenterOfGravity:
        xDir = 0;
        yDir = 0;
        break;

    case RefPointBoxLocation::FrontLeft:
        xDir = 1;
        yDir = 1;
        break;
    case RefPointBoxLocation::FrontRight:
        xDir = 1;
        yDir = -1;
        break;

    case RefPointBoxLocation::RearRight:
        xDir = -1;
        yDir = -1;
        break;
    case RefPointBoxLocation::RearLeft:
        xDir = -1;
        yDir = 1;
        break;

    case RefPointBoxLocation::FrontCenter:
        xDir = 1;
        yDir = 0;
        break;
    case RefPointBoxLocation::RightCenter:
        xDir = 0;
        yDir = -1;
        break;
    case RefPointBoxLocation::RearCenter:
        xDir = -1;
        yDir = 0;
        break;
    case RefPointBoxLocation::LeftCenter:
        xDir = 0;
        yDir = 1;
        break;

    case RefPointBoxLocation::ObjectCenter:
        xDir = 0;
        yDir = 0;
        break;

    default:
        xDir = 0;
        yDir = 0;
        break;
    } // switch

    return std::vector<int>{xDir, yDir};
    ;
}

//==============================================================================

bool operator==(const Object& lhs, const Object& rhs)
{
    bool isEqual
        = (lhs.getObjectId() == rhs.getObjectId()) && (lhs.getTimestamp() == rhs.getTimestamp())
          && (lhs.getObjectFlags() == rhs.getObjectFlags()) && (lhs.getDynamicFlags() == rhs.getDynamicFlags())
          && (lhs.getObjectAge() == rhs.getObjectAge()) && (lhs.getHiddenStatusAge() == rhs.getHiddenStatusAge())
          && (lhs.getObjectBoxSize() == rhs.getObjectBoxSize())
          && (lhs.getObjectBoxSizeSigma() == rhs.getObjectBoxSizeSigma())
          && (fuzzyFloatEqualT<7>(lhs.getObjectBoxHeight(), rhs.getObjectBoxHeight()))
          && (fuzzyFloatEqualT<7>(lhs.getObjectBoxHeightSigma(), rhs.getObjectBoxHeightSigma()))
          && (floatEqual(lhs.getObjectBoxHeightOffset(), rhs.getObjectBoxHeightOffset()))
          && (floatEqual(lhs.getObjectBoxHeightOffsetSigma(), rhs.getObjectBoxHeightOffsetSigma()))
          && (lhs.getReferencePointLocation() == rhs.getReferencePointLocation())
          && (lhs.getReferencePointCoord() == rhs.getReferencePointCoord())
          && (lhs.getReferencePointCoordSigma() == rhs.getReferencePointCoordSigma())
          && (floatEqual(lhs.getReferencePointCoordCorrCoeff(), rhs.getReferencePointCoordCorrCoeff()))
          && (fuzzyFloatEqualT<7>(lhs.getCourseAngle(), rhs.getCourseAngle()))
          && (fuzzyFloatEqualT<7>(lhs.getCourseAngleSigma(), rhs.getCourseAngleSigma()))
          && (floatEqual(lhs.getYawRate(), rhs.getYawRate()))
          && (floatEqual(lhs.getYawRateSigma(), rhs.getYawRateSigma()))
          && (lhs.getClassification() == rhs.getClassification())
          && (floatEqual(lhs.getClassificationQuality(), rhs.getClassificationQuality()))
          && (lhs.getClassificationAge() == rhs.getClassificationAge())
          && (lhs.getMotionReferencePoint() == rhs.getMotionReferencePoint())
          && (lhs.getMotionReferencePointSigma() == rhs.getMotionReferencePointSigma())
          && (lhs.getCenterOfGravity() == rhs.getCenterOfGravity())
          && (floatEqual(lhs.getExistenceProbability(), rhs.getExistenceProbability()))
          && (lhs.getObjectPriority() == rhs.getObjectPriority())
          && (lhs.getRelativeVelocity() == rhs.getRelativeVelocity())
          && (lhs.getRelativeVelocitySigma() == rhs.getRelativeVelocitySigma())
          && (lhs.getAbsoluteVelocity() == rhs.getAbsoluteVelocity())
          && (lhs.getAbsoluteVelocitySigma() == rhs.getAbsoluteVelocitySigma()) &&
          // Skip acceleration during comparison, because some containers (e.g. 0x2281) contain the longitudinal part only!
          (lhs.getClosestObjectPointCoord() == rhs.getClosestObjectPointCoord())
          && (lhs.getContourPoints() == rhs.getContourPoints())
          && (lhs.getMeasurementList() == rhs.getMeasurementList());

    if (isEqual)
    {
        if ((lhs.getUnfilteredObjectData() == nullptr) && (rhs.getUnfilteredObjectData() != nullptr))
        {
            isEqual = false;
        }

        else if ((lhs.getUnfilteredObjectData() != nullptr) && (rhs.getUnfilteredObjectData() == nullptr))
        {
            isEqual = false;
        }

        else if ((lhs.getUnfilteredObjectData() != nullptr) && (rhs.getUnfilteredObjectData() != nullptr))
        {
            isEqual = (*lhs.getUnfilteredObjectData() == *rhs.getUnfilteredObjectData());
        }

        // else: both objects do not have unfiltered data -> they are equal.
    }

    return isEqual;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

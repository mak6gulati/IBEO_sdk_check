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
//!\date Apr 9, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Math.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectList.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListExporter2281_2291.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

bool ObjectListExporter2281_2291::serialize(std::ostream& os, const DataContainerBase& c) const
{
    const ObjectList* container{nullptr};
    try
    {
        container = &dynamic_cast<const ObjectList&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, container->m_timestamp);
    writeBE(os, container->m_objectListId);
    writeBE(os, static_cast<uint8_t>(container->m_deviceType));
    writeBE(os, container->m_deviceInterfaceVersion);
    writeBE(os, container->m_flags);

    writeBE(os, static_cast<uint8_t>(0)); // reserved

    writeBE(os, static_cast<uint16_t>(container->m_objects.size()));
    for (const Object& object : container->m_objects)
    {
        serialize(os, object);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================

bool ObjectListExporter2281_2291::serialize(std::ostream& os, const Object& object) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, object.m_objectId);
    writeBE(os, object.m_objectFlags);
    writeBE(os, object.m_objectAge);
    writeBE(os, object.m_timestamp);
    writeBE(os, object.m_hiddenStatusAge);

    writeBE(os, object.m_classification);
    writeBE(os, round<uint8_t>(std::min(std::max(object.m_classificationQuality, 0.0f), 2.55f) * 100.0f));
    writeBE(os, object.m_classificationAge);

    writeBE(os, object.m_objectBoxSize);
    writeBE(os, object.m_objectBoxSizeSigma);
    writeBE(os, object.m_courseAngle);
    writeBE(os, object.m_courseAngleSigma);

    writeBE(os, object.m_relativeVelocity);
    writeBE(os, object.m_relativeVelocitySigma);
    writeBE(os, object.m_absoluteVelocity);
    writeBE(os, object.m_absoluteVelocitySigma);

    writeBE(os, object.m_objectBoxHeight);
    writeBE(os, object.m_objectBoxHeightSigma);

    writeBE(os, object.m_motionReferencePoint);
    writeBE(os, object.m_motionReferencePointSigma);

    writeBE(os, object.getLongitudinalAcceleration());
    writeBE(os, object.getLongitudinalAccelerationSigma());

    writeBE(os, object.m_yawRate);
    writeBE(os, object.m_yawRateSigma);

    writeBE(os, static_cast<uint8_t>(object.m_contourPoints.size()));

    uint8_t closestContourPointIndex = 0;
    for (unsigned int i = 0; i < object.m_contourPoints.size(); ++i)
    {
        if (object.m_contourPoints[i].getCoordinates() == object.m_closestObjectPointCoord)
        {
            closestContourPointIndex = static_cast<uint8_t>(i);
        }
    }
    writeBE(os, closestContourPointIndex);

    writeBE<16>(os, object.m_referencePointLocation);
    writeBE(os, object.m_referencePointCoord);
    writeBE(os, object.m_referencePointCoordSigma);
    writeBE(os, object.m_referencePointCoordCorrCoeff);

    writeBE(os, object.m_centerOfGravity);
    writeBE(os, object.m_objectPriority);
    writeBE(os, object.m_existenceProbability);

    int8_t heightOffset4Cm = round<int8_t>(std::min(std::max(object.m_objectBoxHeightOffset, -5.12f), 5.08f) * 25.0f);
    uint8_t heightOffsetSigmaCm = round<uint8_t>(std::min(object.m_objectBoxHeightOffsetSigma, 2.55f) * 100.0f);
    writeBE(os, heightOffset4Cm);
    writeBE(os, heightOffsetSigmaCm);

    uint8_t reserved = 0;
    writeBE(os, reserved);
    writeBE(os, reserved);

    for (const ContourPoint& contourPoint : object.m_contourPoints)
    {
        // Only X and Y position of contour points are serialized!
        writeBE(os, contourPoint.getCoordinates());
    }

    object.m_measurementList.serialize(os);

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(object));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

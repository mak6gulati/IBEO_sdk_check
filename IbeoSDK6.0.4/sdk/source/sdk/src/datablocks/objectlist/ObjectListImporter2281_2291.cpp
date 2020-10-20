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
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImporter2281_2291.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

bool ObjectListImporter2281_2291::deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& dh)
{
    ObjectList* container{nullptr};
    try
    {
        container = &dynamic_cast<ObjectList&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, container->m_timestamp);
    readBE(is, container->m_objectListId);

    {
        uint8_t dt;
        ibeo::common::sdk::readBE(is, dt);
        container->m_deviceType = ObjectList::DeviceType(dt);
    }

    readBE(is, container->m_deviceInterfaceVersion);

    readBE(is, container->m_flags);
    if (c.getImportedType() == DataTypeId::DataType_ObjectList2291)
    {
        // Data type 0x2291 contains reference objects only!
        container->setReferenceObjectsOnly(true);
    }

    {
        uint8_t reserved;
        readBE(is, reserved);
    }

    {
        uint16_t nbOfObjects = 0;
        readBE(is, nbOfObjects);
        container->m_objects.resize(nbOfObjects);
        for (Object& object : container->m_objects)
        {
            deserialize(is, object);
        }
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == getSerializedSize(c))
           && getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================

bool ObjectListImporter2281_2291::deserialize(std::istream& is, Object& object)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, object.m_objectId);
    readBE(is, object.m_objectFlags);
    readBE(is, object.m_objectAge);
    readBE(is, object.m_timestamp);
    readBE(is, object.m_hiddenStatusAge);

    readBE(is, object.m_classification);
    {
        uint8_t classificationQualityInt;
        readBE(is, classificationQualityInt);
        object.m_classificationQuality = static_cast<float>(classificationQualityInt) / 100.0F;
    }
    readBE(is, object.m_classificationAge);

    readBE(is, object.m_objectBoxSize);
    readBE(is, object.m_objectBoxSizeSigma);
    readBE(is, object.m_courseAngle);
    readBE(is, object.m_courseAngleSigma);

    readBE(is, object.m_relativeVelocity);
    readBE(is, object.m_relativeVelocitySigma);
    readBE(is, object.m_absoluteVelocity);
    readBE(is, object.m_absoluteVelocitySigma);

    readBE(is, object.m_objectBoxHeight);
    readBE(is, object.m_objectBoxHeightSigma);

    readBE(is, object.m_motionReferencePoint);
    readBE(is, object.m_motionReferencePointSigma);

    float longitudinalAcceleration;
    readBE(is, longitudinalAcceleration);
    float longitudinalAccelerationSigma;
    readBE(is, longitudinalAccelerationSigma);

    readBE(is, object.m_yawRate);
    readBE(is, object.m_yawRateSigma);

    {
        uint8_t nbOfContourPoints;
        readBE(is, nbOfContourPoints);
        object.m_contourPoints.clear();
        object.m_contourPoints.resize(nbOfContourPoints);
    }

    uint8_t closestContourPointIndex;
    readBE(is, closestContourPointIndex);

    readBE<16>(is, object.m_referencePointLocation);
    readBE(is, object.m_referencePointCoord);
    readBE(is, object.m_referencePointCoordSigma);
    readBE(is, object.m_referencePointCoordCorrCoeff);

    readBE(is, object.m_centerOfGravity);
    readBE(is, object.m_objectPriority);
    readBE(is, object.m_existenceProbability);

    {
        int8_t heightOffset4cm;
        readBE(is, heightOffset4cm);
        object.m_objectBoxHeightOffset = static_cast<float>(heightOffset4cm) / 25.0F;
        uint8_t heightOffsetSigmaCm;
        readBE(is, heightOffsetSigmaCm);
        object.m_objectBoxHeightOffsetSigma = static_cast<float>(heightOffsetSigmaCm) / 100.0F;
    }

    {
        uint8_t reserved;
        readBE(is, reserved);
        readBE(is, reserved);
    }

    // Container has already been resized to the right size.
    for (ContourPoint& contourPoint : object.m_contourPoints)
    {
        // Only X and Y position of contour points are serialized!
        Vector2<float> coordinates;
        readBE(is, coordinates);
        contourPoint.setCoordinates(coordinates);
    }

    object.m_measurementList.deserialize(is);

    // Post processing.
    if (object.m_contourPoints.empty() == false)
    {
        // Set closest point according to index(std::vector<>.at throws OOB exception if necessary).
        const ContourPoint& closestPoint = object.m_contourPoints.at(closestContourPointIndex);
        object.m_closestObjectPointCoord = closestPoint.getCoordinates();
    }
    else
    {
        // No contour points -> no closest object point.
        object.m_closestObjectPointCoord = Vector2<float>(NaN, NaN);
    }

    object.fillAccelerationFields(longitudinalAcceleration, longitudinalAccelerationSigma);

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == getSerializedSize(object));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

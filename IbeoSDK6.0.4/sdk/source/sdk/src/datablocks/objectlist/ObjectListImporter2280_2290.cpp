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

#include <ibeo/common/sdk/datablocks/objectlist/ObjectList.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImporter2280_2290.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

bool ObjectListImporter2280_2290::deserialize(std::istream& is, DataContainerBase& c, const IbeoDataHeader& dh)
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

    container->setReferenceObjectsOnly(c.getImportedType() == DataTypeId::DataType_ObjectList2290);

    readBE(is, container->m_timestamp);

    {
        uint16_t nbOfObjects;
        readBE(is, nbOfObjects);
        container->m_objects.resize(nbOfObjects);
    }
    for (Object& object : container->m_objects)
    {
        deserialize(is, object);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == getSerializedSize(c))
           && getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================

bool ObjectListImporter2280_2290::deserialize(std::istream& is, Object& object)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    {
        uint16_t objectId;
        readBE(is, objectId);
        object.m_objectId = objectId;
    }

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

    {
        Vector2<float> ignored;
        readBE(is, ignored); // boundingBoxCenter
        readBE(is, ignored); // boundingBoxSize
    }

    {
        Vector2<float> ignored;
        readBE(is, ignored); // objectBoxCenter
        readBE(is, ignored); // objectBoxCenterSigma
    }
    readBE(is, object.m_objectBoxSize);
    readBE(is, object.m_objectBoxSizeSigma);
    readBE(is, object.m_courseAngle);
    readBE(is, object.m_courseAngleSigma);

    readBE(is, object.m_relativeVelocity);
    readBE(is, object.m_relativeVelocitySigma);
    readBE(is, object.m_absoluteVelocity);
    readBE(is, object.m_absoluteVelocitySigma);

    {
        uint64_t ignored;
        readBE(is, ignored); // vehicleWLANid
    }
    readBE(is, object.m_objectBoxHeight);
    readBE(is, object.m_objectBoxHeightSigma);

    {
        uint16_t ignored;
        readBE(is, ignored); // objectMass
    }

    {
        uint8_t nbOfContourPoints;
        readBE(is, nbOfContourPoints);
        object.m_contourPoints.resize(nbOfContourPoints);
    }

    uint8_t closestContourPointIndex;
    readBE(is, closestContourPointIndex);

    readBE<16>(is, object.m_referencePointLocation);
    readBE(is, object.m_referencePointCoord);
    readBE(is, object.m_referencePointCoordSigma);
    readBE(is, object.m_referencePointCoordCorrCoeff);

    {
        uint64_t ignored;
        readBE(is, ignored); // pointVersion
    }

    readBE(is, object.m_objectPriority);
    readBE(is, object.m_existenceProbability);

    // Container has already been resized to the right size.
    for (ContourPoint& contourPoint : object.m_contourPoints)
    {
        // Only X and Y position of contour points are serialized!
        Vector2<float> coordinates;
        readBE(is, coordinates);
        contourPoint.setCoordinates(coordinates);
    }

    // Post processing.
    if (object.m_contourPoints.empty() == false)
    {
        // Set closest point according to index(std::vector<>.at throw OOB exception if necessary).
        const ContourPoint& closestPoint = object.m_contourPoints.at(closestContourPointIndex);
        object.m_closestObjectPointCoord = closestPoint.getCoordinates();
    }
    else
    {
        // No contour points -> no closest object point.
        object.m_closestObjectPointCoord = Vector2<float>(NaN, NaN);
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == getSerializedSize(object));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

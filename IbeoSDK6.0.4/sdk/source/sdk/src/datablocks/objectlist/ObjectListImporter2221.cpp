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
//!\date May 4, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/ObjectBasic.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ContourPointIn2271.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListHelper.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImporter2221.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::ObjectList;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_ObjectList2221>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace

//==============================================================================
namespace {
//==============================================================================
//!\brief Convert a raw object class to an object class.
//!
//------------------------------------------------------------------------------
static ibeo::common::sdk::ObjectClass
convertFromRawClassification(const ibeo::common::sdk::rawObjectClass::RawObjectClass rawClass)
{
    switch (rawClass)
    {
    case ibeo::common::sdk::rawObjectClass::RawObjectClass::Unclassified:
        return ibeo::common::sdk::ObjectClass::Unclassified;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::UnknownSmall:
        return ibeo::common::sdk::ObjectClass::UnknownSmall;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::UnknownBig:
        return ibeo::common::sdk::ObjectClass::UnknownBig;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::Pedestrian:
        return ibeo::common::sdk::ObjectClass::Pedestrian;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::Bike:
        return ibeo::common::sdk::ObjectClass::Bike;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::Car:
        return ibeo::common::sdk::ObjectClass::Car;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::Truck:
        return ibeo::common::sdk::ObjectClass::Truck;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::Overdrivable:
        return ibeo::common::sdk::ObjectClass::Unclassified;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::Underdrivable:
        return ibeo::common::sdk::ObjectClass::Underdriveable;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::Bicycle:
        return ibeo::common::sdk::ObjectClass::Bicycle;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::Motorbike:
        return ibeo::common::sdk::ObjectClass::Motorbike;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::Infrastructure:
        return ibeo::common::sdk::ObjectClass::Infrastructure;

    case ibeo::common::sdk::rawObjectClass::RawObjectClass::SmallObstacle:
        return ibeo::common::sdk::ObjectClass::SmallObstacle;

    default:
        return ibeo::common::sdk::ObjectClass::Unclassified;
    } // switch rawClass
}

//==============================================================================
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================
// Specializations for RegisteredImporter
//==============================================================================

//generate link between data-type-id/importer and importer create function <dtid, ImpHash> ==> Imp::create

template<>
const Id R::registeredImporterInitial
    = Id(std::make_pair(R::getDataTypeStatic(), C::getClassIdHashStatic()), R::create);

//registering ... (create map)
//add all device that can receive any datatype that can be imported to GeneralDataTypeContainer
class IdcFile;
class IbeoEcu;

// basically R::registeredImporter = R::registeredImporterInitial
// but on its way it will be added to all mentioned RegisteredImporterGlobal maps
// through which registerImporter method it has been piped through.
// RegisteredImporterGlobal is a singleton for each device.
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(registeredImporterInitial));

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_ObjectList2221>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    std::streamsize sz = std::streamsize(sizeof(NTPTime)) // timestamp
                         + std::streamsize(sizeof(uint16_t)); // # of objects

    for (const Object& obj : container->m_objects)
    {
        sz += getSerializedSize(obj);
    }
    return sz;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_ObjectList2221>::deserialize(std::istream& is,
                                                                   DataContainerBase& c,
                                                                   const IbeoDataHeader& dh) const
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

    readLE(is, container->m_timestamp);

    {
        uint16_t nbOfObjects = 0;
        readLE(is, nbOfObjects);
        container->m_objects.resize(nbOfObjects);
        for (Object& object : container->m_objects)
        {
            if (deserialize(is, object, container->m_timestamp) == false)
            {
                return false;
            }
        }
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_ObjectList2221>::getSerializedSize(const Object& object) const
{
    return std::streamsize(sizeof(uint16_t)) // objectId
           + std::streamsize(sizeof(uint16_t)) // objectAge
           + std::streamsize(sizeof(uint16_t)) // predictionAge
           + std::streamsize(sizeof(uint16_t)) // relativeMomentOfMeasure
           + serializedSize(Vector2<int16_t>()) // positionTrackingReferencePoint
           + serializedSize(Vector2<uint16_t>()) // sigmaTrackingReferencePoint
           + serializedSize(Vector2<int16_t>()) // positionClosestObjectPoint
           + serializedSize(Vector2<int16_t>()) // boundingBoxCenter
           + serializedSize(Vector2<uint16_t>()) // boundingBoxSize
           + serializedSize(Vector2<int16_t>()) // objectBoxCenter
           + serializedSize(Vector2<uint16_t>()) // objectBoxSize
           + std::streamsize(sizeof(int16_t)) // objectBoxOrientation
           + serializedSize(Vector2<int16_t>()) // absoluteVelocity
           + serializedSize(Vector2<uint16_t>()) // sigmaAbsoluteVelocity
           + serializedSize(Vector2<int16_t>()) // relativeVelocity
           + std::streamsize(sizeof(uint16_t)) // classification
           + std::streamsize(sizeof(uint16_t)) // classificationAge
           + std::streamsize(sizeof(uint16_t)) // classificationConfidence
           + std::streamsize(sizeof(uint16_t)) // numberContourPoints
           + std::streamsize(object.getContourPoints().size()) * serializedSize(Vector2<int16_t>());
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_ObjectList2221>::deserialize(std::istream& is,
                                                                   Object& object,
                                                                   const NTPTime& containerTimestamp) const
{
    const int64_t startPos = streamposToInt64(is.tellg());

    {
        uint16_t objectId;
        readLE(is, objectId);
        object.m_objectId = objectId;
    }
    {
        uint16_t objectAge;
        readLE(is, objectAge);
        object.m_objectAge = objectAge;
    }
    readLE(is, object.m_hiddenStatusAge); // predictionAge

    {
        uint16_t relativeMomentOfMeasure;
        readLE(is, relativeMomentOfMeasure);
        NTPTime objectTimestamp(containerTimestamp);
        objectTimestamp.addMicroseconds(relativeMomentOfMeasure);
        object.m_timestamp = objectTimestamp;
    }

    {
        Vector2<int16_t> positionTrackingReferencePoint;
        readLE(is, positionTrackingReferencePoint);

        Vector2<uint16_t> positionTrackingReferencePointSigma;
        readLE(is, positionTrackingReferencePointSigma);

        object.m_referencePointLocation = RefPointBoxLocation::ObjectCenter;
        object.m_referencePointCoord    = convertFromCm<int16_t>(positionTrackingReferencePoint);
        object.m_referencePointCoordSigma
            = convertFromCm<uint16_t>(positionTrackingReferencePointSigma, std::numeric_limits<uint16_t>::max());
    }

    {
        Vector2<int16_t> positionClosestObjectPoint;
        readLE(is, positionClosestObjectPoint);
        object.m_closestObjectPointCoord = convertFromCm<int16_t>(positionClosestObjectPoint);
    }

    {
        Vector2<int16_t> ignoredCoords;
        readLE(is, ignoredCoords); // boundingBoxCenterX/Y

        uint16_t ignoredWidth;
        readLE(is, ignoredWidth); // boundingBoxWidth

        uint16_t ignoredLength;
        readLE(is, ignoredLength); // boundingBoxLength
    }

    {
        Vector2<int16_t> ignoredCoords;
        readLE(is, ignoredCoords); // objectBoxCenterX/Y
    }

    {
        uint16_t objectBoxSizeX;
        readLE(is, objectBoxSizeX);

        uint16_t objectBoxSizeY;
        readLE(is, objectBoxSizeY);

        object.m_objectBoxSize
            = Vector2<float>(convertFromCm<uint16_t>(objectBoxSizeX), convertFromCm<uint16_t>(objectBoxSizeY));
    }

    {
        int16_t objectBoxOrientation;
        readLE(is, objectBoxOrientation);
        object.m_courseAngle = convertFromCentiDegrees<int16_t>(objectBoxOrientation);
    }

    {
        Vector2<int16_t> absoluteVelocity;
        readLE(is, absoluteVelocity);
        object.m_absoluteVelocity = convertFromCm<int16_t>(absoluteVelocity);

        uint16_t absoluteVelocitySigmaX;
        readLE(is, absoluteVelocitySigmaX);

        uint16_t absoluteVelocitySigmaY;
        readLE(is, absoluteVelocitySigmaY);

        object.m_absoluteVelocitySigma
            = Vector2<float>(convertFromCm<uint16_t>(absoluteVelocitySigmaX, std::numeric_limits<uint16_t>::max()),
                             convertFromCm<uint16_t>(absoluteVelocitySigmaY, std::numeric_limits<uint16_t>::max()));
    }

    {
        Vector2<int16_t> relativeVelocity;
        readLE(is, relativeVelocity);
        object.m_relativeVelocity = convertFromCm<int16_t>(relativeVelocity);
    }

    {
        uint8_t classValue;
        readLE(is, classValue);

        rawObjectClass::RawObjectClass rawClass = static_cast<rawObjectClass::RawObjectClass>(classValue);
        object.m_classification                 = convertFromRawClassification(rawClass);

        uint8_t ignoredUInt8;
        readLE(is, ignoredUInt8); // classificationFlags
    }
    {
        uint16_t classificationAge;
        readLE(is, classificationAge);
        object.m_classificationAge = classificationAge;
    }
    {
        uint16_t classificationConfidence;
        readLE(is, classificationConfidence);
        object.m_classificationQuality
            = static_cast<float>(classificationConfidence) / static_cast<float>(std::numeric_limits<uint16_t>::max());
    }

    {
        uint16_t nbOfContourPoints;
        readLE(is, nbOfContourPoints);

        object.m_contourPoints.resize(nbOfContourPoints);
    }

    // Container has already been resized to the right size.
    for (ContourPoint& contourPoint : object.m_contourPoints)
    {
        // Only X and Y position of contour points are serialized!
        Vector2<float> coordinates;
        readLEFromCm<int16_t>(is, coordinates);
        contourPoint.setCoordinates(coordinates);
    }

    // Post processing.
    if (object.m_absoluteVelocity.getX() == std::numeric_limits<int16_t>::min())
    {
        // Ego is not moving.
        object.m_absoluteVelocity      = object.m_relativeVelocity; // absolute = relative velocity
        object.m_relativeVelocitySigma = object.m_absoluteVelocitySigma; // relative = absolute velocity sigma
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(object));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

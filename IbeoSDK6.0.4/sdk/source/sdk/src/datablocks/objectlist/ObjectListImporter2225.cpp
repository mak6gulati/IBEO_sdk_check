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

#include <ibeo/common/sdk/datablocks/objectlist/special/ContourPointIn2271.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImporter2225.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::ObjectList;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_ObjectList2225>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
} // namespace

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

std::streamsize Importer<C, DataTypeId::DataType_ObjectList2225>::getSerializedSize(const DataContainerBase& c) const
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

bool Importer<C, DataTypeId::DataType_ObjectList2225>::deserialize(std::istream& is,
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

    readBE(is, container->m_timestamp);

    {
        uint16_t nbOfObjects = 0;
        readBE(is, nbOfObjects);
        container->m_objects.resize(nbOfObjects);
        for (Object& object : container->m_objects)
        {
            if (deserialize(is, object) == false)
            {
                return false;
            }
        }
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_ObjectList2225>::getSerializedSize(const Object& object) const
{
    return std::streamsize(sizeof(uint16_t)) // objectId
           + std::streamsize(sizeof(uint16_t)) // flags
           + std::streamsize(sizeof(uint32_t)) // objectAge
           + std::streamsize(sizeof(NTPTime)) // timestamp
           + std::streamsize(sizeof(uint16_t)) // hiddenStatusAge
           + std::streamsize(sizeof(uint8_t)) // classification
           + std::streamsize(sizeof(uint8_t)) // classificationQuality
           + std::streamsize(sizeof(uint32_t)) // classificationAge
           + serializedSize(Vector2<float>()) // boundingBoxCenter
           + serializedSize(Vector2<float>()) // boundingBoxSize
           + serializedSize(Vector2<float>()) // objectBoxCenter
           + serializedSize(Vector2<float>()) // objectBoxCenterSigma
           + serializedSize(Vector2<float>()) // objectBoxSize
           + serializedSize(Vector2<float>()) // objectBoxSizeSigma
           + std::streamsize(sizeof(float)) // yawAngle
           + std::streamsize(sizeof(float)) // yawAngleSigma
           + serializedSize(Vector2<float>()) // relativeVelocity
           + serializedSize(Vector2<float>()) // relativeVelocitySigma
           + serializedSize(Vector2<float>()) // absoluteVelocity
           + serializedSize(Vector2<float>()) // absoluteVelocitySigma
           + std::streamsize(sizeof(uint64_t)) // vehicleWLANid
           + std::streamsize(sizeof(float)) // objectHeight
           + std::streamsize(sizeof(float)) // objectHeightSigma
           + std::streamsize(sizeof(uint16_t)) // objectMass
           + std::streamsize(sizeof(uint8_t)) // numContourPoints
           + std::streamsize(sizeof(uint8_t)) // closestContourPointIndex
           + std::streamsize(object.getContourPoints().size()) * serializedSize(Vector2<float>());
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_ObjectList2225>::deserialize(std::istream& is, Object& object) const
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
    readBE(is, object.m_hiddenStatusAge); // predictionAge

    readBE(is, object.m_classification);
    {
        uint8_t classificationQualityInt;
        readBE(is, classificationQualityInt);
        object.m_classificationQuality = static_cast<float>(classificationQualityInt) / 100.0F;
    }
    readBE(is, object.m_classificationAge);

    {
        Vector2<float> ignoredCoords;
        readBE(is, ignoredCoords); // boundingBoxCenter

        Vector2<float> ignoredSize;
        readBE(is, ignoredCoords); // boundingBoxSize
    }

    object.m_referencePointLocation = RefPointBoxLocation::ObjectCenter;
    readBE(is, object.m_referencePointCoord); // objectBoxCenter
    readBE(is, object.m_referencePointCoordSigma); // objectBoxCenterSigma

    readBE(is, object.m_objectBoxSize);
    readBE(is, object.m_objectBoxSizeSigma);

    readBE(is, object.m_courseAngle); // yawAngle
    readBE(is, object.m_courseAngleSigma); // yawAngleSigma

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

    // Container has already been resized to the right size.
    for (ContourPoint& contourPoint : object.m_contourPoints)
    {
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

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(object));
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

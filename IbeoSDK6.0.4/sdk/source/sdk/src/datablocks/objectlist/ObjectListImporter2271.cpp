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

#include <ibeo/common/sdk/datablocks/objectlist/ObjectListHelper.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImporter2271.hpp>

#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

//==============================================================================
namespace {
using C  = ibeo::common::sdk::ObjectList;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_ObjectList2271>;
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

std::streamsize Importer<C, DataTypeId::DataType_ObjectList2271>::getSerializedSize(const DataContainerBase& c) const
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
                         + std::streamsize(sizeof(uint16_t)) // scanNumber
                         + std::streamsize(sizeof(uint8_t)) // objectListId
                         + std::streamsize(sizeof(uint8_t)) // deviceType
                         + std::streamsize(sizeof(uint16_t)) // deviceInterfaceVersion
                         + std::streamsize(sizeof(uint32_t)) // reserved
                         + std::streamsize(sizeof(uint16_t)); // # of objects

    for (const Object& obj : container->m_objects)
    {
        sz += getSerializedSize(obj);
    }
    return sz;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_ObjectList2271>::deserialize(std::istream& is,
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
        uint16_t ignored;
        readBE(is, ignored); // scanNumber
    }
    readBE(is, container->m_objectListId);

    {
        uint8_t dt;
        ibeo::common::sdk::readBE(is, dt);
        container->m_deviceType = ObjectList::DeviceType(dt);
    }

    readBE(is, container->m_deviceInterfaceVersion);
    {
        uint32_t ignored;
        readBE(is, ignored); // reserved
    }

    {
        uint16_t nbOfObjects = 0;
        readBE(is, nbOfObjects);
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

std::streamsize Importer<C, DataTypeId::DataType_ObjectList2271>::getSerializedSize(const Object& object) const
{
    // unfilteredAttributes
    const std::streamsize unfilteredDataSize = object.hasUnfilteredObjectData()
                                                   ? getSerializedSize(*object.getUnfilteredObjectData())
                                                   : 0; // no unfiltered object data

    // filteredAttributes
    const std::streamsize filteredDataSize
        = hasFilteredObjectData(object) ? std::streamsize(sizeof(uint8_t)) // priority
                                              + std::streamsize(sizeof(uint16_t)) // objectAge
                                              + std::streamsize(sizeof(uint16_t)) // hiddenStatusAge
                                              + std::streamsize(sizeof(uint8_t)) // dynamicFlag
                                              + std::streamsize(sizeof(uint16_t)) // relativeTimeOfMeasure
                                              + serializedSize(Vector2<int16_t>()) // positionClosestObjectPoint
                                              + serializedSize(Vector2<int16_t>()) // relativeVelocity
                                              + serializedSize(Vector2<uint16_t>()) // relativeVelocitySigma
                                              + std::streamsize(sizeof(uint8_t)) // classification
                                              + std::streamsize(sizeof(uint8_t)) // classificationQuality
                                              + std::streamsize(sizeof(uint16_t)) // classificationAge
                                              + std::streamsize(sizeof(uint8_t)) // objectTTP
                                              + std::streamsize(sizeof(uint8_t)) // reserved
                                              + serializedSize(Vector2<uint16_t>()) // objectBoxSize
                                              + serializedSize(Vector2<uint16_t>()) // objectBoxSizeSigma
                                              + std::streamsize(sizeof(int16_t)) // objectBoxOrientation
                                              + std::streamsize(sizeof(uint16_t)) // objectBoxOrientationSigma
                                              + std::streamsize(sizeof(uint8_t)) // objectBoxHeight
                                              + std::streamsize(sizeof(uint8_t)) // referencePointLocation
                                              + serializedSize(Vector2<int16_t>()) // referencePointCoord
                                              + serializedSize(Vector2<uint16_t>()) // referencePointCoordSigma
                                              + std::streamsize(sizeof(int16_t)) // referencePointCoordCorrCoeff
                                              + std::streamsize(sizeof(uint8_t)) // existenceProbability
                                              + serializedSize(Vector2<int16_t>()) // absoluteVelocity
                                              + serializedSize(Vector2<uint16_t>()) // absoluteVelocitySigma
                                              + std::streamsize(sizeof(int16_t)) // velocityCorrCoeff
                                              + serializedSize(Vector2<int16_t>()) // acceleration
                                              + serializedSize(Vector2<uint16_t>()) // accelerationSigma
                                              + std::streamsize(sizeof(int16_t)) // accelerationCorrCoeff
                                              + std::streamsize(sizeof(int16_t)) // yawRate
                                              + std::streamsize(sizeof(uint16_t)) // yawRateSigma
                                              + std::streamsize(sizeof(uint8_t)) // numContourPoints
                                              + std::streamsize( // contourPoints
                                                    object.getNumContourPoints())
                                                    * getContourPointSerializedSize()
                                        : 0; // no filtered attributes

    return std::streamsize(sizeof(uint32_t)) // objectId
           + std::streamsize(sizeof(uint8_t)) // correspondingFence
           + std::streamsize(sizeof(uint8_t)) // interfaceFlags
           + std::streamsize(sizeof(uint8_t)) // attributesFlag
           + unfilteredDataSize // unfilteredAttributes
           + filteredDataSize // filteredAttributes
           + std::streamsize(sizeof(int32_t)) // reserved
        ;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_ObjectList2271>::deserialize(std::istream& is,
                                                                   Object& object,
                                                                   const NTPTime& containerTimestamp) const
{
    // Clear previous unfiltered object data (just in case).
    if (object.m_unfilteredObjectData != nullptr)
    {
        delete object.m_unfilteredObjectData;
        object.m_unfilteredObjectData = nullptr;
    }

    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, object.m_objectId);
    {
        uint8_t ignored;
        readBE(is, ignored); // correspondingFence
        readBE(is, ignored); // interfaceFlags
    }
    uint8_t attribFlags;
    readBE(is, attribFlags);

    if ((attribFlags & attributesFlagUnfilteredAttributesAvailable) != 0)
    {
        // Read unfiltered object data.
        object.m_unfilteredObjectData = new UnfilteredObjectData();
        if (deserialize(is,
                        *object.m_unfilteredObjectData,
                        containerTimestamp,
                        (attribFlags & attributesFlagUnfilteredAttributesContourAvailable) != 0)
            == false)
        {
            return false;
        }
    }
    // else: no unfiltered attributes.

    if ((attribFlags & attributesFlagFilteredAttributesAvailable) != 0)
    {
        // Read filtered object data.
        {
            uint8_t priority;
            readBE(is, priority);
            object.m_objectPriority = priority;
        }
        {
            uint16_t objectAge;
            readBE(is, objectAge);
            object.m_objectAge = objectAge;
        }
        {
            uint16_t hiddenStatusAge;
            readBE(is, hiddenStatusAge);
            object.m_hiddenStatusAge = hiddenStatusAge;
        }
        readBE(is, object.m_dynamicFlags);

        {
            uint16_t relativeTimeOfMeasure;
            readBE(is, relativeTimeOfMeasure);
            NTPTime objectTimestamp(containerTimestamp);
            objectTimestamp.addMicroseconds(relativeTimeOfMeasure);
            object.m_timestamp = objectTimestamp;
        }

        readBEFromCm<int16_t>(is, object.m_closestObjectPointCoord);
        readBEFromCm<int16_t>(is, object.m_relativeVelocity);
        readBEFromCm<uint16_t>(is, object.m_relativeVelocitySigma, std::numeric_limits<uint16_t>::max());

        readBE(is, object.m_classification);
        {
            uint8_t classificationQuality;
            readBE(is, classificationQuality);
            object.m_classificationQuality
                = static_cast<float>(classificationQuality) / static_cast<float>(std::numeric_limits<uint8_t>::max());
        }
        {
            uint16_t classificationAge;
            readBE(is, classificationAge);
            object.m_classificationAge = classificationAge;
        }

        {
            uint8_t ignored;
            readBE(is, ignored); // objectTTP
            readBE(is, ignored); // reserved
        }

        readBEFromCm<uint16_t>(is, object.m_objectBoxSize, std::numeric_limits<uint16_t>::max());
        readBEFromCm<uint16_t>(is, object.m_objectBoxSizeSigma, std::numeric_limits<uint16_t>::max());

        readBEFromCentiDegrees<int16_t>(is, object.m_courseAngle, std::numeric_limits<int16_t>::min());
        readBEFromCentiDegrees<uint16_t>(is, object.m_courseAngleSigma, std::numeric_limits<uint16_t>::max());

        readBEFromCm<uint8_t>(is, object.m_objectBoxHeight, std::numeric_limits<uint8_t>::max());
        object.m_objectBoxHeight *= objectBoxHeightScalingFactor;

        readBE<8>(is, object.m_referencePointLocation);
        readBEFromCm<int16_t>(is, object.m_referencePointCoord);
        readBEFromCm<uint16_t>(is, object.m_referencePointCoordSigma, std::numeric_limits<uint16_t>::max());
        {
            int16_t referencePointCoordCorrCoeff;
            readBE(is, referencePointCoordCorrCoeff);
            object.m_referencePointCoordCorrCoeff = static_cast<float>(referencePointCoordCorrCoeff)
                                                    / static_cast<float>(std::numeric_limits<int16_t>::max());
        }
        {
            uint8_t existenceProbability;
            readBE(is, existenceProbability);
            object.m_existenceProbability
                = static_cast<float>(existenceProbability) / static_cast<float>(std::numeric_limits<uint8_t>::max());
        }

        readBEFromCm<int16_t>(is, object.m_absoluteVelocity);
        readBEFromCm<uint16_t>(is, object.m_absoluteVelocitySigma, std::numeric_limits<uint16_t>::max());

        {
            uint16_t ignored;
            readBE(is, ignored); // velocityCorrCoeff
        }

        readBEFromCm<int16_t>(is, object.m_acceleration);
        readBEFromCm<uint16_t>(is, object.m_accelerationSigma);
        readBEFromCm<uint16_t>(is, object.m_accelerationCorrCoeff);

        {
            int16_t yawRate;
            readBE(is, yawRate);
            object.m_yawRate = static_cast<float>(yawRate) / yawRateScalingFactor;

            uint16_t yawRateSigma;
            readBE(is, yawRateSigma);
            object.m_yawRateSigma = static_cast<float>(yawRateSigma) / yawRateScalingFactor;
        }

        {
            uint8_t nbOfContourPoints;
            readBE(is, nbOfContourPoints);
            if ((attribFlags & attributesFlagFilteredAttributesContourAvailable) != 0)
            {
                object.m_contourPoints.resize(nbOfContourPoints);

                for (ContourPoint& contourPoint : object.m_contourPoints)
                {
                    deserialize(is, contourPoint);
                }
            }
            else
            {
                // No contour points in filtered attributes.
                object.m_contourPoints.clear();
            }
        }
    }
    else
    {
        // No filtered attributes -> reset corresponding members to default.
        resetFilteredObjectData(object);
    }

    {
        uint32_t ignored;
        readBE(is, ignored); // reserved
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(object));
}

//==============================================================================

std::streamsize
Importer<C, DataTypeId::DataType_ObjectList2271>::getSerializedSize(const UnfilteredObjectData& objectData) const
{
    return std::streamsize(sizeof(uint8_t)) // priority
           + std::streamsize(sizeof(uint16_t)) // relativeTimeOfMeasure
           + serializedSize(Vector2<int16_t>()) // positionClosestObjectPoint
           + std::streamsize(sizeof(uint16_t)) // reserved
           + serializedSize(Vector2<uint16_t>()) // objectBoxSize
           + serializedSize(Vector2<uint16_t>()) // objectBoxSizeSigma
           + std::streamsize(sizeof(int16_t)) // objectBoxOrientation
           + std::streamsize(sizeof(uint16_t)) // objectBoxOrientationSigma
           + std::streamsize(sizeof(uint8_t)) // objectHeight
           + std::streamsize(sizeof(uint8_t)) // referencePointLocation
           + serializedSize(Vector2<int16_t>()) // referencePointCoord
           + serializedSize(Vector2<uint16_t>()) // referencePointCoordSigma
           + std::streamsize(sizeof(int16_t)) // referencePointCoordCorrCoeff
           + std::streamsize(sizeof(uint8_t)) // existenceProbability
           + std::streamsize(sizeof(uint8_t)) // numContourPoints
           + std::streamsize( // contourPoints
                 objectData.getNumContourPoints())
                 * getContourPointSerializedSize();
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_ObjectList2271>::deserialize(std::istream& is,
                                                                   UnfilteredObjectData& objectData,
                                                                   const NTPTime& containerTimestamp,
                                                                   const bool hasContourPoints) const
{
    const int64_t startPos = streamposToInt64(is.tellg());

    readBE(is, objectData.m_priority);

    {
        uint16_t relativeTimeOfMeasure;
        readBE(is, relativeTimeOfMeasure);
        NTPTime objectTimestamp(containerTimestamp);
        objectTimestamp.addMicroseconds(relativeTimeOfMeasure);
        objectData.m_timestamp = objectTimestamp;
    }

    readBEFromCm<int16_t>(is, objectData.m_positionClosestObjectPoint);
    {
        uint16_t ignored;
        readBE(is, ignored); // reserved
    }

    readBEFromCm<uint16_t>(is, objectData.m_objectBoxSize, std::numeric_limits<uint16_t>::max());
    readBEFromCm<uint16_t>(is, objectData.m_objectBoxSizeSigma, std::numeric_limits<uint16_t>::max());

    readBEFromCentiDegrees<int16_t>(is, objectData.m_courseAngle, std::numeric_limits<int16_t>::min());
    readBEFromCentiDegrees<uint16_t>(is, objectData.m_courseAngleSigma, std::numeric_limits<uint16_t>::max());

    readBEFromCm<uint8_t>(is, objectData.m_objectBoxHeight, std::numeric_limits<uint8_t>::max());
    objectData.m_objectBoxHeight *= 3.0F;

    readBE<8>(is, objectData.m_referencePointLocation);
    readBEFromCm<int16_t>(is, objectData.m_referencePointCoord);
    readBEFromCm<uint16_t>(is, objectData.m_referencePointCoordSigma, std::numeric_limits<uint16_t>::max());

    {
        uint16_t referencePointCoordCorrCoeff;
        readBE(is, referencePointCoordCorrCoeff);
        objectData.m_referencePointCoordCorrCoeff = static_cast<float>(referencePointCoordCorrCoeff)
                                                    / static_cast<float>(std::numeric_limits<int16_t>::max());
    }

    {
        uint8_t existenceProbability;
        readBE(is, existenceProbability);
        objectData.m_existenceProbability
            = static_cast<float>(existenceProbability) / static_cast<float>(std::numeric_limits<uint8_t>::max());
    }

    {
        uint8_t nbOfContourPoints;
        readBE(is, nbOfContourPoints);
        if (hasContourPoints)
        {
            objectData.m_contourPoints.resize(nbOfContourPoints);

            for (ContourPoint& contourPoint : objectData.m_contourPoints)
            {
                deserialize(is, contourPoint);
            }
        }
        else
        {
            // No contour points in filtered attributes.
            objectData.m_contourPoints.clear();
        }
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(objectData));
}

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_ObjectList2271>::getContourPointSerializedSize()
{
    return std::streamsize(sizeof(int16_t)) // x
           + std::streamsize(sizeof(int16_t)) // y
           + std::streamsize(sizeof(uint8_t)) // xSigma
           + std::streamsize(sizeof(uint8_t)) // ySigma
           + std::streamsize(sizeof(int8_t)) // correlationCoeff
           + std::streamsize(sizeof(uint8_t)) // existenceProbability
        ;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_ObjectList2271>::deserialize(std::istream& is, ContourPoint& cp) const
{
    const int64_t startPos = streamposToInt64(is.tellg());

    {
        Vector2<float> coords;
        readBEFromCm<int16_t>(is, coords);
        cp.setCoordinates(coords);
    }

    {
        float xSigma;
        float ySigma;
        readBEFromCm<uint8_t>(is, xSigma);
        readBEFromCm<uint8_t>(is, ySigma);
        cp.setXSigma(xSigma);
        cp.setYSigma(ySigma);
    }

    {
        int8_t corrCoeff;
        readBE(is, corrCoeff);
        cp.setCorrCoeff(static_cast<float>(corrCoeff) / static_cast<float>(std::numeric_limits<int8_t>::max()));
    }

    {
        uint8_t existenceProb;
        readBE(is, existenceProb);
        cp.setExistenceProbability(static_cast<float>(existenceProb)
                                   / static_cast<float>(std::numeric_limits<uint8_t>::max()));
    }

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == getContourPointSerializedSize());
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_ObjectList2271>::hasFilteredObjectData(const Object& object) const
{
    // Check all members that are part of the filtered attribute set whether they have their default value.
    // If so, the object does not have a filtered attribute set.

    static const Object defaultObject;

    return (object.m_objectAge != defaultObject.m_objectAge)
           || (object.m_hiddenStatusAge != defaultObject.m_hiddenStatusAge)
           || (object.m_dynamicFlags != defaultObject.m_dynamicFlags)
           || (object.m_timestamp != defaultObject.m_timestamp)
           || (object.m_closestObjectPointCoord != defaultObject.m_closestObjectPointCoord)
           || (object.m_relativeVelocity != defaultObject.m_relativeVelocity)
           || (object.m_relativeVelocitySigma != defaultObject.m_relativeVelocitySigma)
           || (object.m_classification != defaultObject.m_classification)
           || (floatEqual(object.m_classificationQuality, defaultObject.m_classificationQuality) == false)
           || (object.m_classificationAge != defaultObject.m_classificationAge)
           || (object.m_objectBoxSize != defaultObject.m_objectBoxSize)
           || (object.m_objectBoxSizeSigma != defaultObject.m_objectBoxSizeSigma)
           || (floatEqual(object.m_courseAngle, defaultObject.m_courseAngle) == false)
           || (floatEqual(object.m_courseAngleSigma, defaultObject.m_courseAngleSigma) == false)
           || (floatEqual(object.m_objectBoxHeight, defaultObject.m_objectBoxHeight) == false)
           || (object.m_referencePointLocation != defaultObject.m_referencePointLocation)
           || (object.m_referencePointCoord != defaultObject.m_referencePointCoord)
           || (object.m_referencePointCoordSigma != defaultObject.m_referencePointCoordSigma)
           || (floatEqual(object.m_referencePointCoordCorrCoeff, defaultObject.m_referencePointCoordCorrCoeff) == false)
           || (floatEqual(object.m_existenceProbability, defaultObject.m_existenceProbability) == false)
           || (object.m_absoluteVelocity != defaultObject.m_absoluteVelocity)
           || (object.m_absoluteVelocitySigma != defaultObject.m_absoluteVelocitySigma)
           || (object.m_acceleration != defaultObject.m_acceleration)
           || (object.m_accelerationSigma != defaultObject.m_accelerationSigma)
           || (floatEqual(object.m_accelerationCorrCoeff, defaultObject.m_accelerationCorrCoeff) == false)
           || (floatEqual(object.m_yawRate, defaultObject.m_yawRate) == false)
           || (floatEqual(object.m_yawRateSigma, defaultObject.m_yawRateSigma) == false)
           || (object.m_contourPoints != defaultObject.m_contourPoints);
}

//==============================================================================

void Importer<C, DataTypeId::DataType_ObjectList2271>::resetFilteredObjectData(Object& object) const
{
    static const Object defaultObject;

    // Reset only those object members that are part of the 0x2271 filtered object data back to default.

    object.m_objectAge                    = defaultObject.m_objectAge;
    object.m_hiddenStatusAge              = defaultObject.m_hiddenStatusAge;
    object.m_dynamicFlags                 = defaultObject.m_dynamicFlags;
    object.m_timestamp                    = defaultObject.m_timestamp;
    object.m_closestObjectPointCoord      = defaultObject.m_closestObjectPointCoord;
    object.m_relativeVelocity             = defaultObject.m_relativeVelocity;
    object.m_relativeVelocitySigma        = defaultObject.m_relativeVelocitySigma;
    object.m_classification               = defaultObject.m_classification;
    object.m_classificationQuality        = defaultObject.m_classificationQuality;
    object.m_classificationAge            = defaultObject.m_classificationAge;
    object.m_objectBoxSize                = defaultObject.m_objectBoxSize;
    object.m_objectBoxSizeSigma           = defaultObject.m_objectBoxSizeSigma;
    object.m_courseAngle                  = defaultObject.m_courseAngle;
    object.m_courseAngleSigma             = defaultObject.m_courseAngleSigma;
    object.m_objectBoxHeight              = defaultObject.m_objectBoxHeight;
    object.m_referencePointLocation       = defaultObject.m_referencePointLocation;
    object.m_referencePointCoord          = defaultObject.m_referencePointCoord;
    object.m_referencePointCoordSigma     = defaultObject.m_referencePointCoordSigma;
    object.m_referencePointCoordCorrCoeff = defaultObject.m_referencePointCoordCorrCoeff;
    object.m_existenceProbability         = defaultObject.m_existenceProbability;
    object.m_absoluteVelocity             = defaultObject.m_absoluteVelocity;
    object.m_absoluteVelocitySigma        = defaultObject.m_absoluteVelocitySigma;
    object.m_acceleration                 = defaultObject.m_acceleration;
    object.m_accelerationSigma            = defaultObject.m_accelerationSigma;
    object.m_accelerationCorrCoeff        = defaultObject.m_accelerationCorrCoeff;
    object.m_yawRate                      = defaultObject.m_yawRate;
    object.m_yawRateSigma                 = defaultObject.m_yawRateSigma;
    object.m_contourPoints                = defaultObject.m_contourPoints;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

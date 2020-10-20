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
//!\date May 11, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/objectlist/ObjectListHelper.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListExporter2271.hpp>

//==============================================================================
namespace {
using C = ibeo::common::sdk::ObjectList;
} // namespace

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_ObjectList2271>::getSerializedSize(const DataContainerBase& c) const
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

bool Exporter<C, DataTypeId::DataType_ObjectList2271>::serialize(std::ostream& os, const DataContainerBase& c) const
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
    writeBE(os, static_cast<uint16_t>(0)); // scanNumber
    writeBE(os, container->m_objectListId);
    writeBE(os, static_cast<uint8_t>(container->m_deviceType));
    writeBE(os, container->m_deviceInterfaceVersion);
    writeBE(os, static_cast<uint32_t>(0)); // reserved

    writeBE(os, static_cast<uint16_t>(container->m_objects.size()));
    for (const Object& object : container->m_objects)
    {
        serialize(os, object, container->m_timestamp);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(c));
}

//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_ObjectList2271>::getSerializedSize(const Object& object) const
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

bool Exporter<C, DataTypeId::DataType_ObjectList2271>::serialize(std::ostream& os,
                                                                 const Object& object,
                                                                 const NTPTime& containerTimestamp) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, object.m_objectId);
    writeBE(os, static_cast<uint8_t>(0)); // correspondingFence
    writeBE(os, static_cast<uint8_t>(0)); // interfaceFlags

    uint8_t attribFlags = 0;
    if (object.m_unfilteredObjectData != nullptr)
    {
        attribFlags |= attributesFlagUnfilteredAttributesAvailable;
        if (object.m_unfilteredObjectData->getNumContourPoints() > 0)
        {
            attribFlags |= attributesFlagUnfilteredAttributesContourAvailable;
        }
    }
    if (hasFilteredObjectData(object))
    {
        attribFlags |= attributesFlagFilteredAttributesAvailable;
        if (object.getNumContourPoints() > 0)
        {
            attribFlags |= attributesFlagFilteredAttributesContourAvailable;
        }
    }
    writeBE(os, attribFlags);

    if (object.m_unfilteredObjectData != nullptr)
    {
        // Write unfiltered object data.
        if (serialize(os, *object.m_unfilteredObjectData, containerTimestamp) == false)
        {
            return false;
        }
    }
    // else: no unfiltered attributes.

    if (hasFilteredObjectData(object))
    {
        // Write filtered object data.
        writeBE(os, static_cast<uint8_t>(object.m_objectPriority));
        writeBE(os, static_cast<uint16_t>(object.m_objectAge));
        writeBE(os, static_cast<uint16_t>(object.m_hiddenStatusAge));
        writeBE(os, object.m_dynamicFlags);

        {
            NTPTime relativeTimeOfMeasure = object.m_timestamp - containerTimestamp;
            writeBE(os, static_cast<uint16_t>(relativeTimeOfMeasure.getMicroseconds()));
        }

        writeBEToCm<int16_t>(os, object.m_closestObjectPointCoord);
        writeBEToCm<int16_t>(os, object.m_relativeVelocity);
        writeBEToCm<uint16_t>(os, object.m_relativeVelocitySigma, std::numeric_limits<uint16_t>::max());

        writeBE(os, object.m_classification);
        writeBE(os,
                static_cast<uint8_t>(object.m_classificationQuality
                                     * static_cast<float>(std::numeric_limits<uint8_t>::max())));
        writeBE(os, static_cast<uint16_t>(object.m_classificationAge));

        writeBE(os, static_cast<uint8_t>(0)); // objectTTP
        writeBE(os, static_cast<uint8_t>(0)); // reserved

        writeBEToCm<uint16_t>(os, object.m_objectBoxSize, std::numeric_limits<uint16_t>::max());
        writeBEToCm<uint16_t>(os, object.m_objectBoxSizeSigma, std::numeric_limits<uint16_t>::max());

        writeBEToCentiDegrees<int16_t>(os, object.m_courseAngle, std::numeric_limits<int16_t>::min());
        writeBEToCentiDegrees<uint16_t>(os, object.m_courseAngleSigma, std::numeric_limits<uint16_t>::max());

        writeBEToCm<uint8_t>(os, object.m_objectBoxHeight / 3.0F, std::numeric_limits<uint8_t>::max());

        writeBE<8>(os, object.m_referencePointLocation);
        writeBEToCm<int16_t>(os, object.m_referencePointCoord);
        writeBEToCm<uint16_t>(os, object.m_referencePointCoordSigma, std::numeric_limits<uint16_t>::max());
        writeBE(os,
                static_cast<int16_t>(object.m_referencePointCoordCorrCoeff
                                     * static_cast<float>(std::numeric_limits<int16_t>::max())));
        writeBE(os,
                static_cast<uint8_t>(object.m_existenceProbability
                                     * static_cast<float>(std::numeric_limits<uint8_t>::max())));

        writeBEToCm<int16_t>(os, object.m_absoluteVelocity);
        writeBEToCm<uint16_t>(os, object.m_absoluteVelocitySigma, std::numeric_limits<uint16_t>::max());

        writeBE(os, static_cast<uint16_t>(0)); // velocityCorrCoeff

        writeBEToCm<int16_t>(os, object.m_acceleration);
        writeBEToCm<uint16_t>(os, object.m_accelerationSigma);
        writeBEToCm<uint16_t>(os, object.m_accelerationCorrCoeff);

        writeBE(os, static_cast<int16_t>(roundf(object.m_yawRate * 10000.0F)));
        writeBE(os, static_cast<uint16_t>(roundf(object.m_yawRateSigma * 10000.0F)));

        writeBE(os, static_cast<uint8_t>(object.getNumContourPoints()));
        for (const ContourPoint& contourPoint : object.m_contourPoints)
        {
            serialize(os, contourPoint);
        }
    }
    // else: no filtered attributes.

    writeBE(os, static_cast<uint32_t>(0)); // reserved

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(object));
}

//==============================================================================

std::streamsize
Exporter<C, DataTypeId::DataType_ObjectList2271>::getSerializedSize(const UnfilteredObjectData& objectData) const
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

bool Exporter<C, DataTypeId::DataType_ObjectList2271>::serialize(std::ostream& os,
                                                                 const UnfilteredObjectData& objectData,
                                                                 const NTPTime& containerTimestamp) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBE(os, objectData.m_priority);

    {
        NTPTime relativeTimeOfMeasure = objectData.m_timestamp - containerTimestamp;
        writeBE(os, static_cast<uint16_t>(relativeTimeOfMeasure.getMicroseconds()));
    }

    writeBEToCm<int16_t>(os, objectData.m_positionClosestObjectPoint);
    writeBE(os, static_cast<uint16_t>(0)); // reserved

    writeBEToCm<uint16_t>(os, objectData.m_objectBoxSize, std::numeric_limits<uint16_t>::max());
    writeBEToCm<uint16_t>(os, objectData.m_objectBoxSizeSigma, std::numeric_limits<uint16_t>::max());

    writeBEToCentiDegrees<int16_t>(
        os, objectData.m_courseAngle, static_cast<int16_t>(std::numeric_limits<uint16_t>::min()));
    writeBEToCentiDegrees<uint16_t>(os, objectData.m_courseAngleSigma, std::numeric_limits<uint16_t>::max());

    writeBEToCm<uint8_t>(os, objectData.m_objectBoxHeight / 3.0F, std::numeric_limits<uint8_t>::max());

    writeBE<8>(os, objectData.m_referencePointLocation);
    writeBEToCm<int16_t>(os, objectData.m_referencePointCoord);
    writeBEToCm<uint16_t>(os, objectData.m_referencePointCoordSigma, std::numeric_limits<uint16_t>::max());

    writeBE(os,
            static_cast<uint16_t>(objectData.m_referencePointCoordCorrCoeff
                                  * static_cast<float>(std::numeric_limits<int16_t>::max())));

    writeBE(os,
            static_cast<uint8_t>(objectData.m_existenceProbability
                                 * static_cast<float>(std::numeric_limits<uint8_t>::max())));

    writeBE(os, objectData.getNumContourPoints());
    for (const ContourPoint& contourPoint : objectData.m_contourPoints)
    {
        serialize(os, contourPoint);
    }

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == this->getSerializedSize(objectData));
}

//==============================================================================

std::streamsize Exporter<C, DataTypeId::DataType_ObjectList2271>::getContourPointSerializedSize()
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

bool Exporter<C, DataTypeId::DataType_ObjectList2271>::serialize(std::ostream& os, const ContourPoint& cp) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

    writeBEToCm<int16_t>(os, cp.getCoordinates());

    writeBEToCm<uint8_t>(os, cp.getXSigma());
    writeBEToCm<uint8_t>(os, cp.getYSigma());

    writeBE(os, static_cast<int8_t>(cp.getCorrCoeff() * static_cast<float>(std::numeric_limits<int8_t>::max())));
    writeBE(
        os,
        static_cast<uint8_t>(cp.getExistenceProbability() * static_cast<float>(std::numeric_limits<uint8_t>::max())));

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == getContourPointSerializedSize());
}

//==============================================================================

bool Exporter<C, DataTypeId::DataType_ObjectList2271>::hasFilteredObjectData(const Object& object) const
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
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

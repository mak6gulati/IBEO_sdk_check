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

#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImExporterCommon2281_2291.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize ObjectListImExporterCommon2281_2291::getSerializedSize(const DataContainerBase& c)
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

    std::streamsize sz = std::streamsize(sizeof(NTPTime) // timestamp
                                         + sizeof(uint8_t) // object list ID
                                         + sizeof(uint8_t) // device type
                                         + sizeof(uint16_t) // device interface version
                                         + sizeof(uint8_t) // flags
                                         + sizeof(uint8_t) // reserved
                                         + sizeof(uint16_t) // number of objects
    );

    for (const Object& object : container->getObjects())
    {
        sz += getSerializedSize(object);
    }

    return sz;
}

//==============================================================================

std::streamsize ObjectListImExporterCommon2281_2291::getSerializedSize(const Object& object)
{
    return std::streamsize(sizeof(uint32_t)) // objectId
           + std::streamsize(sizeof(uint16_t)) // flags
           + std::streamsize(sizeof(uint32_t)) // objectAge
           + std::streamsize(sizeof(uint64_t)) // timestamp
           + std::streamsize(sizeof(uint16_t)) // hiddenStatusAge
           + std::streamsize(sizeof(uint8_t)) // classification
           + std::streamsize(sizeof(uint8_t)) // classificationQuality
           + std::streamsize(sizeof(uint32_t)) // classificationAge
           + serializedSize(Vector2<float>()) // objectBoxSize
           + serializedSize(Vector2<float>()) // objectBoxSizeSigma
           + std::streamsize(sizeof(float)) // courseAngle
           + std::streamsize(sizeof(float)) // courseAngleSigma
           + serializedSize(Vector2<float>()) // relativeVelocity
           + serializedSize(Vector2<float>()) // relativeVelocitySigma
           + serializedSize(Vector2<float>()) // absoluteVelocity
           + serializedSize(Vector2<float>()) // absoluteVelocitySigma
           + std::streamsize(sizeof(float)) // objectHeight
           + std::streamsize(sizeof(float)) // objectHeightSigma
           + serializedSize(Vector2<float>()) // motionReferencePoint
           + serializedSize(Vector2<float>()) // motionReferencePointSigma
           + std::streamsize(sizeof(float)) // longitudinalAccelaration
           + std::streamsize(sizeof(float)) // longitudinalAccelarationSigma
           + std::streamsize(sizeof(float)) // yawRate
           + std::streamsize(sizeof(float)) // yawRateSigma
           + std::streamsize(sizeof(uint8_t)) // numContourPoints
           + std::streamsize(sizeof(uint8_t)) // closestContourPointIndex
           + std::streamsize(sizeof(uint16_t)) // referencePointLocation
           + serializedSize(Vector2<float>()) // referencePointCoord
           + serializedSize(Vector2<float>()) // referencePointCoordSigma
           + std::streamsize(sizeof(float)) // referencePointCoordCorrCoeff
           + serializedSize(Vector2<float>()) // centerOfGravity
           + std::streamsize(sizeof(uint16_t)) // objectPriority
           + std::streamsize(sizeof(float)) // objectExistenceMeas
           + std::streamsize(sizeof(int8_t)) // objectBoxHeightOffset
           + std::streamsize(sizeof(uint8_t)) // objectBoxHeightOffsetSigma
           + std::streamsize(sizeof(uint8_t)) // reserved
           + std::streamsize(sizeof(uint8_t)) // reserved
           + std::streamsize(object.getContourPoints().size()) * serializedSize(Vector2<float>())
           + object.getMeasurementList().getSerializedSize();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

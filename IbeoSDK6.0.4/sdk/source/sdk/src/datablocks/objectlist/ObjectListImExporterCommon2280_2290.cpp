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

#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImExporterCommon2280_2290.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::streamsize ObjectListImExporterCommon2280_2290::getSerializedSize(const DataContainerBase& c)
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
                                         + sizeof(uint16_t) // number of objects
    );

    for (const Object& object : container->getObjects())
    {
        sz += getSerializedSize(object);
    }

    return sz;
}

//==============================================================================

std::streamsize ObjectListImExporterCommon2280_2290::getSerializedSize(const Object& object)
{
    return std::streamsize(sizeof(uint16_t)) // objectId
           + std::streamsize(sizeof(uint16_t)) // flags
           + std::streamsize(sizeof(uint32_t)) // objectAge
           + std::streamsize(sizeof(uint64_t)) // timestamp
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
           + std::streamsize(sizeof(uint16_t)) // referencePointLocation
           + serializedSize(Vector2<float>()) // referencePointCoord
           + serializedSize(Vector2<float>()) // referencePointCoordSigma
           + std::streamsize(sizeof(float)) // referencePointCoordCorrCoeff
           + std::streamsize(sizeof(uint64_t)) // pointVersion
           + std::streamsize(sizeof(uint16_t)) // objectPriority
           + std::streamsize(sizeof(float)) // objectExistenceMeas
           + std::streamsize(object.getContourPoints().size()) * serializedSize(Vector2<float>());
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

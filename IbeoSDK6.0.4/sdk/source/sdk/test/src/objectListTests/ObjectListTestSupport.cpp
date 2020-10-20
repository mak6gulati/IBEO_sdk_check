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
//!\date Apr 25, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <math.h>
#include <objectListTests/ObjectListTestSupport.hpp>

//==============================================================================

static const float sigmaMin = -1.0F;
static const float sigmaMax = 1.0F;

static const ibeo::common::sdk::Vector2<float> sigma2Min(sigmaMin, sigmaMin);
static const ibeo::common::sdk::Vector2<float> sigma2Max(sigmaMax, sigmaMax);

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ObjectList& objList)
{
    objList.setTimestamp(getRandValue<NTPTime>());
    objList.setObjectListId(getRandValue<uint8_t>());
    objList.setFlags(getRandValue<uint8_t>());
    objList.setDeviceType((ObjectList::DeviceType)getRandValue<uint8_t>());
    objList.setDeviceInterfaceVersion(getRandValue<uint16_t>());
    objList.setReferenceObjectsOnly(getRandValue<bool>());

    ObjectList::ObjectVector objects;
    objects.resize(getRandValue<uint8_t>());
    for (Object& obj : objects)
    {
        fillRandomly(obj);
    }
    objList.setObjects(objects);
}

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(Object& obj)
{
    obj.setObjectId(getRandValue<uint32_t>());
    obj.setTimestamp(getRandValue<NTPTime>());

    obj.setObjectFlags(getRandValue<uint16_t>());
    obj.setDynamicFlags(getRandValue<uint8_t>());

    obj.setObjectAge(getRandValue<uint32_t>());
    obj.setHiddenStatusAge(getRandValue<uint16_t>());

    obj.setObjectBoxSize(getRandValue<Vector2<float>>());
    obj.setObjectBoxSizeSigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));
    obj.setObjectBoxHeight(getRandValue<float>());
    obj.setObjectBoxHeightSigma(getRandValue<float>(sigmaMin, sigmaMax));
    obj.setObjectBoxHeightOffset(getRandValue<float>());
    obj.setObjectBoxHeightOffsetSigma(getRandValue<float>(sigmaMin, sigmaMax));

    obj.setReferencePointLocation((RefPointBoxLocation)getRandValue<uint8_t>());
    obj.setReferencePointCoord(getRandValue<Vector2<float>>());
    obj.setReferencePointCoordSigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));
    obj.setReferencePointCoordCorrCoeff(getRandValue<float>());

    obj.setCourseAngle(getRandValue<float>());
    obj.setCourseAngleSigma(getRandValue<float>(sigmaMin, sigmaMax));
    obj.setYawRate(getRandValue<float>());
    obj.setYawRateSigma(getRandValue<float>(sigmaMin, sigmaMax));

    obj.setClassification((ObjectClass)getRandValue<uint8_t>());
    obj.setClassificationQuality(getRandValue<float>());
    obj.setClassificationAge(getRandValue<uint32_t>());

    obj.setMotionReferencePoint(getRandValue<Vector2<float>>());
    obj.setMotionReferencePointSigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));

    obj.setCenterOfGravity(getRandValue<Vector2<float>>());
    obj.setExistenceProbability(getRandValue<float>(0.0F, 1.0F));
    obj.setObjectPriority(getRandValue<uint16_t>());

    obj.setRelativeVelocity(
        getRandValue<Vector2<float>>(Vector2<float>(-100.0F, -100.0F), Vector2<float>(100.0F, 100.0F)));
    obj.setRelativeVelocitySigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));
    obj.setAbsoluteVelocity(
        getRandValue<Vector2<float>>(Vector2<float>(-100.0F, -100.0F), Vector2<float>(100.0F, 100.0F)));
    obj.setAbsoluteVelocitySigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));

    obj.setAcceleration(getRandValue<Vector2<float>>(Vector2<float>(-100.0F, -100.0F), Vector2<float>(100.0F, 100.0F)));
    obj.setAccelerationSigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));

    std::vector<ContourPoint> contourPoints;
    contourPoints.resize(getRandValue<uint8_t>());
    for (ContourPoint& contourPoint : contourPoints)
    {
        fillRandomly(contourPoint);
    }
    obj.setContourPoints(contourPoints);

    if (contourPoints.empty() == false)
    {
        uint8_t closestPointIx = getRandValue<uint8_t>(uint8_t(contourPoints.size() - 1));
        obj.setClosestObjectPointCoord(contourPoints[closestPointIx].getCoordinates());
    }

    MeasurementList measList;
    uint8_t nbOfMeasurements = getRandValue<uint8_t>();
    for (uint8_t measIx = 0; measIx < nbOfMeasurements; ++measIx)
    {
        Measurement meas;
        fillRandomly(meas);
        measList.addMeasurement(meas);
    }

    //obj.setUnfilteredObjectData(getRandValue<UnfilteredObjectData>());
}

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ContourPoint& cp)
{
    cp.setX(getRandValue<float>());
    cp.setY(getRandValue<float>());
    cp.setXSigma(getRandValue<float>(sigmaMin, sigmaMax));
    cp.setYSigma(getRandValue<float>(sigmaMin, sigmaMax));
    cp.setCorrCoeff(getRandValue<float>());
    cp.setExistenceProbability(getRandValue<float>(0.0F, 1.0F));
}

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(Measurement& meas)
{
    MeasurementKey key(getRandValue<uint8_t>());

    uint8_t typeIx = getRandValue<uint8_t>(11); // all types as given by 'getAs' methods except void
    switch (typeIx)
    {
    case 0:
        meas.setValue(key, getRandValue<float>());
        break;
    case 1:
        meas.setValue(key, getRandValue<double>());
        break;
    case 2:
        meas.setValue(key, getRandValue<int8_t>());
        break;
    case 3:
        meas.setValue(key, getRandValue<uint8_t>());
        break;
    case 4:
        meas.setValue(key, getRandValue<int16_t>());
        break;
    case 5:
        meas.setValue(key, getRandValue<uint16_t>());
        break;
    case 6:
        meas.setValue(key, getRandValue<int32_t>());
        break;
    case 7:
        meas.setValue(key, getRandValue<uint32_t>());
        break;
    case 8:
        meas.setValue(key, getRandValue<int64_t>());
        break;
    case 9:
        meas.setValue(key, getRandValue<uint64_t>());
        break;
    case 10:
        meas.setValue(key, getRandValue<bool>());
        break;
    case 11:
        meas.setValue(key, getRandString(256));
        break;
    default:
        throw std::runtime_error("Invalid type index!");
    } // switch
}

//==============================================================================
//==============================================================================
//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ObjectList2221& objList)
{
    objList.setScanStartTimeStamp(getRandValue<NTPTime>());

    ObjectList2221::ObjectVector objects;
    objects.resize(getRandValue<uint16_t>(256));
    for (ObjectIn2221& obj : objects)
    {
        fillRandomly(obj);
    }
    objList.setObjects(objects);
}

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ObjectIn2221& obj)
{
    obj.setObjectId(getRandValue<uint16_t>());
    obj.setObjectAge(getRandValue<uint16_t>());
    obj.setPredictionAge(getRandValue<uint16_t>());
    obj.setRelativeTimestamp(getRandValue<uint16_t>());
    obj.setRefPoint(getRandValue<Vector2<int16_t>>());
    obj.setRefPointSigma(getRandValue<Vector2<uint16_t>>());
    obj.setClosestPoint(getRandValue<Vector2<int16_t>>());
    obj.setBoundingBoxCenter(getRandValue<Vector2<int16_t>>());
    obj.setBoundingBoxWidth(getRandValue<uint16_t>());
    obj.setBoundingBoxLength(getRandValue<uint16_t>());
    obj.setObjectBoxCenter(getRandValue<Vector2<int16_t>>());
    obj.setObjectBoxLength(getRandValue<uint16_t>());
    obj.setObjectBoxWidth(getRandValue<uint16_t>());
    obj.setObjectBoxOrientation(getRandValue<int16_t>());
    obj.setAbsVelocity(getRandValue<Vector2<int16_t>>());
    obj.setAbsVelSigmaX(getRandValue<uint16_t>());
    obj.setAbsVelSigmaY(getRandValue<uint16_t>());
    obj.setRelVelocity(getRandValue<Vector2<int16_t>>());
    obj.setClass(getValidRandLuxObjectClass()); // must be a valid value otherwise the deserializer reads it as Unknown
    obj.setClassAge(getRandValue<uint16_t>());
    obj.setClassCertainty(getRandValue<uint16_t>());

    uint16_t nbContourPoints{getRandValue<uint16_t>(ObjectIn2221::maxContourPoints)};
    obj.setNumContourPoints(nbContourPoints);

    ObjectIn2221::ContourPointVector contourPoints;
    contourPoints.resize(nbContourPoints);
    for (Vector2<int16_t>& contourPoint : contourPoints)
    {
        contourPoint = getRandValue<Vector2<int16_t>>();
    }
    obj.setContourPoints(contourPoints);
}

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ObjectList2271& objList)
{
    objList.setScanStartTimestamp(getRandValue<NTPTime>());
    objList.setScanNumber(getRandValue<uint16_t>());
    objList.setObjectListId(getRandValue<uint8_t>());
    objList.setDeviceId(getRandValue<uint8_t>());
    objList.setDeviceInterfaceVersion(getRandValue<uint16_t>() & 0x3FFF);
    objList.setReserved(getRandValue<uint32_t>());

    ObjectList2271::ObjectVector objects;
    objects.resize(getRandValue<uint16_t>(256));
    for (ObjectIn2271& obj : objects)
    {
        fillRandomly(obj);
    }
    objList.setObjects(objects);
}

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ObjectIn2271& obj)
{
    obj.setObjectId(getRandValue<uint32_t>());
    obj.setInterfaceFlags(getRandValue<uint8_t>());

    if (getRandValue<bool>() == true)
    {
        UnfilteredObjectDataIn2271 unfilteredAttrib;
        fillRandomly(unfilteredAttrib);
        obj.setUnfilteredObjectData(unfilteredAttrib);
    }

    if (getRandValue<bool>() == true)
    {
        FilteredObjectDataIn2271 filteredAttrib;
        fillRandomly(filteredAttrib);
        obj.setFilteredObjectData(filteredAttrib);
    }
}

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(UnfilteredObjectDataIn2271& unfilteredObjectData)
{
    unfilteredObjectData.setIsValid(true);
    unfilteredObjectData.setHasContourPoints(getRandValue<bool>());
    unfilteredObjectData.setPriority(getRandValue<uint8_t>());
    unfilteredObjectData.setRelativeTimeOfMeasure(getRandValue<uint16_t>());
    unfilteredObjectData.setPositionClosestObjectPoint(getRandValue<Vector2<int16_t>>());
    unfilteredObjectData.setReserved(getRandValue<uint16_t>());
    unfilteredObjectData.setObjectBoxSize(getRandValue<Vector2<uint16_t>>());
    unfilteredObjectData.setObjectBoxSizeSigma(getRandValue<Vector2<uint16_t>>());
    unfilteredObjectData.setObjectBoxOrientation(getRandValue<int16_t>());
    unfilteredObjectData.setObjectBoxOrientationSigma(getRandValue<uint16_t>());
    unfilteredObjectData.setObjectBoxHeight(getRandValue<uint8_t>());
    unfilteredObjectData.setReferencePointLocation(RefPointBoxLocation(getRandValue<uint8_t>()));
    unfilteredObjectData.setReferencePointCoord(getRandValue<Vector2<int16_t>>());
    unfilteredObjectData.setReferencePointCoordSigma(getRandValue<Vector2<uint16_t>>());
    unfilteredObjectData.setReferencePointPositionCorrCoeff(getRandValue<int16_t>());
    unfilteredObjectData.setExistenceProbaility(getRandValue<uint8_t>());

    if (unfilteredObjectData.hasContourPoints())
    {
        // Ensure having at least one contour point.
        std::vector<ContourPointIn2271> contourPoints(getRandValue<uint8_t>(1, std::numeric_limits<uint8_t>::max()));
        for (ContourPointIn2271& cp : contourPoints)
        {
            fillRandomly(cp);
        }
        unfilteredObjectData.setContourPoints(contourPoints);
        unfilteredObjectData.setPossibleNbOfContourPoints(uint8_t(contourPoints.size()));
    }
    else
    {
        unfilteredObjectData.setPossibleNbOfContourPoints(0);
    }
}

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(FilteredObjectDataIn2271& filteredObjectData)
{
    filteredObjectData.setIsValid(true);
    filteredObjectData.setHasContourPoints(getRandValue<bool>());

    filteredObjectData.setPriority(getRandValue<uint8_t>());

    filteredObjectData.setObjectAge(getRandValue<uint16_t>());
    filteredObjectData.setHiddenStatusAge(getRandValue<uint16_t>());
    filteredObjectData.setDynamicFlags(getRandValue<uint8_t>());

    filteredObjectData.setRelativeTimeOfMeasure(getRandValue<uint16_t>());
    filteredObjectData.setPositionClosestObjectPoint(getRandValue<Vector2<int16_t>>());

    filteredObjectData.setRelativeVelocity(getRandValue<Vector2<int16_t>>());
    filteredObjectData.setRelativeVelocitySigma(getRandValue<Vector2<uint16_t>>());
    filteredObjectData.setClassification(rawObjectClass::RawObjectClass(getRandValue<uint8_t>()));
    filteredObjectData.setClassificationQuality(getRandValue<uint8_t>());
    filteredObjectData.setClassificationAge(getRandValue<uint16_t>());

    filteredObjectData.setReserved(getRandValue<uint16_t>());
    filteredObjectData.setObjectBoxSize(getRandValue<Vector2<uint16_t>>());
    filteredObjectData.setObjectBoxSizeSigma(getRandValue<Vector2<uint16_t>>());
    filteredObjectData.setObjectBoxOrientation(getRandValue<int16_t>());
    filteredObjectData.setObjectBoxOrientationSigma(getRandValue<uint16_t>());
    filteredObjectData.setObjectBoxHeight(getRandValue<uint8_t>());
    filteredObjectData.setReferencePointLocation(RefPointBoxLocation(getRandValue<uint8_t>()));
    filteredObjectData.setReferencePointCoord(getRandValue<Vector2<int16_t>>());
    filteredObjectData.setReferencePointCoordSigma(getRandValue<Vector2<uint16_t>>());
    filteredObjectData.setReferencePointPositionCorrCoeff(getRandValue<int16_t>());
    filteredObjectData.setExistenceProbaility(getRandValue<uint8_t>());

    filteredObjectData.setAbsoluteVelocity(getRandValue<Vector2<int16_t>>());
    filteredObjectData.setAbsoluteVelocitySigma(getRandValue<Vector2<uint16_t>>());
    filteredObjectData.setVelocityCorrCoeff(getRandValue<int16_t>());
    filteredObjectData.setAcceleration(getRandValue<Vector2<int16_t>>());
    filteredObjectData.setAccelerationSigma(getRandValue<Vector2<uint16_t>>());
    filteredObjectData.setAccelerationCorrCoeff(getRandValue<int16_t>());
    filteredObjectData.setYawRate(getRandValue<int16_t>());
    filteredObjectData.setYawRateSigma(getRandValue<uint16_t>());

    if (filteredObjectData.hasContourPoints())
    {
        // Ensure having at least one contour point.
        std::vector<ContourPointIn2271> contourPoints(getRandValue<uint8_t>(1, std::numeric_limits<uint8_t>::max()));
        for (ContourPointIn2271& cp : contourPoints)
        {
            fillRandomly(cp);
        }
        filteredObjectData.setContourPoints(contourPoints);
        filteredObjectData.setPossibleNbOfContourPoints(uint8_t(contourPoints.size()));
    }
    else
    {
        filteredObjectData.setPossibleNbOfContourPoints(0);
    }
}

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ContourPointIn2271& cp)
{
    cp.setX(getRandValue<int16_t>());
    cp.setY(getRandValue<int16_t>());
    cp.setXSigma(getRandValue<uint8_t>());
    cp.setYSigma(getRandValue<uint8_t>());
    cp.setCorrCoeff(getRandValue<int8_t>());
    cp.setExistenceProbability(getRandValue<uint8_t>());
}

//==============================================================================
//==============================================================================
//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ObjectList2280& objList)
{
    objList.setTimestamp(getRandValue<NTPTime>());

    ObjectList2280::ObjectVector objects;
    objects.resize(getRandValue<uint16_t>(256));
    for (ObjectIn2280& obj : objects)
    {
        fillRandomly(obj);
    }
    objList.setObjects(objects);
}

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ObjectIn2280& obj)
{
    obj.setObjectId(getRandValue<uint16_t>());
    obj.setFlags(getRandValue<uint16_t>());
    obj.setObjectAge(getRandValue<uint32_t>());
    obj.setTimestamp(getRandValue<NTPTime>());
    obj.setObjectPredAge(getRandValue<uint16_t>());

    obj.setClassification(getRandValue<ObjectClass>());
    obj.setClassCertainty(getRandValue<uint8_t>());
    obj.setClassAge(getRandValue<uint32_t>());

    obj.setReserved0(getRandValue<Vector2<float>>());
    obj.setReserved1(getRandValue<Vector2<float>>());

    obj.setObjBoxCenter(getRandValue<Vector2<float>>());
    obj.setObjBoxCenterSigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));
    obj.setObjBoxSize(getRandValue<Vector2<float>>());
    obj.setReserved2(getRandValue<Vector2<float>>());
    obj.setObjBoxOrientation(getRandValue<float>());
    obj.setObjBoxOrientationSigma(getRandValue<float>(sigmaMin, sigmaMax));

    obj.setRelVelocity(getRandValue<Vector2<float>>());
    obj.setRelVelocitySigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));
    obj.setAbsVelocity(getRandValue<Vector2<float>>());
    obj.setAbsVelocitySigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));

    obj.setReserved4(getRandValue<uint64_t>());
    obj.setReserved5(getRandValue<float>());
    obj.setReserved6(getRandValue<float>());
    obj.setReserved7(getRandValue<uint16_t>());

    obj.setRefPointLocation(getRandValue<RefPointBoxLocation>());
    obj.setRefPointCoords(getRandValue<Vector2<float>>());
    obj.setRefPointCoordsSigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));

    obj.setRefPointPosCorrCoeffs(getRandValue<float>());

    obj.setReserved8(getRandValue<float>());
    obj.setReserved9(getRandValue<float>());

    obj.setObjPriority(getRandValue<uint16_t>());
    obj.setObjExtMeasurement(getRandValue<float>());

    std::vector<Vector2<float>> contourPoints;
    contourPoints.resize(getRandValue<uint8_t>());
    for (Vector2<float>& contourPoint : contourPoints)
    {
        contourPoint = getRandValue<Vector2<float>>();
    }
    obj.setContourPoints(contourPoints);

    if (contourPoints.empty() == false)
    {
        uint8_t closestPointIx = getRandValue<uint8_t>(uint8_t(contourPoints.size() - 1));
        obj.setIdxOfClosestPoint(closestPointIx);
    }
}

//==============================================================================
//==============================================================================
//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ObjectList2281& objList)
{
    objList.setTimestamp(getRandValue<NTPTime>());
    objList.setObjectListId(getRandValue<uint8_t>());
    objList.setDeviceType(ObjectList2281::DeviceType(getRandValue<uint8_t>()));
    objList.setDeviceInterfaceVerstion(getRandValue<uint16_t>());
    objList.setFlags(getRandValue<uint8_t>());
    objList.setReserved1(getRandValue<uint8_t>());

    ObjectList2281::ObjectVector objects;
    objects.resize(getRandValue<uint16_t>(256));
    for (ObjectIn2281& obj : objects)
    {
        fillRandomly(obj);
    }
    objList.setObjects(objects);
}

//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ObjectIn2281& obj)
{
    obj.setObjectId(getRandValue<uint32_t>());
    obj.setFlags(getRandValue<uint16_t>());
    obj.setObjectAge(getRandValue<uint32_t>());
    obj.setTimestamp(getRandValue<NTPTime>());
    obj.setHiddenStatusAge(getRandValue<uint16_t>());

    obj.setClassification(getRandValue<ObjectClass>());
    obj.setClassificationQuality(getRandValue<uint8_t>());
    obj.setClassificationAge(getRandValue<uint32_t>());

    obj.setObjectBoxSize(getRandValue<Vector2<float>>());
    obj.setObjectBoxSizeSigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));
    obj.setCourseAngle(getRandValue<float>());
    obj.setCourseAngleSigma(getRandValue<float>(sigmaMin, sigmaMax));

    obj.setRelativeVelocity(getRandValue<Vector2<float>>());
    obj.setRelativeVelocitySigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));
    obj.setAbsoluteVelocity(getRandValue<Vector2<float>>());
    obj.setAbsoluteVelocitySigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));

    obj.setObjectHeight(getRandValue<float>());
    obj.setObjectHeightSigma(getRandValue<float>(sigmaMin, sigmaMax));

    obj.setMotionReferencePoint(getRandValue<Vector2<float>>());
    obj.setMotionReferencePointSigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));

    obj.setLongitudinalAcceleration(getRandValue<float>(-100.0F, 100.0F));
    obj.setLongitudinalAccelerationSigma(getRandValue<float>(sigmaMin, sigmaMax));

    obj.setYawRate(getRandValue<float>());
    obj.setYawRateSigma(getRandValue<float>(sigmaMin, sigmaMax));

    obj.setReferencePointLocation(getRandValue<RefPointBoxLocation>());
    obj.setReferencePointCoord(getRandValue<Vector2<float>>());
    obj.setReferencePointCoordSigma(getRandValue<Vector2<float>>(sigma2Min, sigma2Max));

    obj.setReferencePointPositionCorrCoeff(getRandValue<float>());

    obj.setCenterOfGravity(getRandValue<Vector2<float>>());
    obj.setObjectPriority(getRandValue<uint16_t>());
    obj.setObjectExistenceMeas(getRandValue<float>());

    obj.setObjectBoxHeightOffset(getRandValue<int8_t>());
    obj.setObjectBoxHeightOffsetSigma(getRandValue<uint8_t>());

    obj.setReserved3(getRandValue<uint8_t>());
    obj.setReserved4(getRandValue<uint8_t>());

    std::vector<Vector2<float>> contourPoints;
    contourPoints.resize(getRandValue<uint8_t>());
    for (Vector2<float>& contourPoint : contourPoints)
    {
        contourPoint = getRandValue<Vector2<float>>();
    }
    obj.setContourPoints(contourPoints);

    if (contourPoints.empty() == false)
    {
        uint8_t closestPointIx = getRandValue<uint8_t>(uint8_t(contourPoints.size() - 1));
        obj.setClosestContourPointIndex(closestPointIx);
    }

    MeasurementList measList;
    uint8_t nbOfMeasurements = getRandValue<uint8_t>();
    for (uint8_t measIx = 0; measIx < nbOfMeasurements; ++measIx)
    {
        Measurement meas;
        fillRandomly(meas);
        measList.addMeasurement(meas);
    }
    obj.setMeasurementList(measList);
}

//==============================================================================
//==============================================================================
//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ObjectList2290& objList)
{
    objList.setTimestamp(getRandValue<NTPTime>());

    ObjectList2290::ObjectVector objects;
    objects.resize(getRandValue<uint16_t>(256));
    for (ObjectIn2290& obj : objects)
    {
        fillRandomly(obj);
    }
    objList.setObjects(objects);
}

//==============================================================================
//==============================================================================
//==============================================================================

template<>
void ObjectListTestSupport::fillRandomly(ObjectList2291& objList)
{
    objList.setTimestamp(getRandValue<NTPTime>());
    objList.setObjectListId(getRandValue<uint8_t>());
    objList.setDeviceType(ObjectList2291::DeviceType(getRandValue<uint8_t>()));
    objList.setDeviceInterfaceVerstion(getRandValue<uint16_t>());
    objList.setFlags(getRandValue<uint8_t>());
    objList.setReserved1(getRandValue<uint8_t>());

    ObjectList2291::ObjectVector objects;
    objects.resize(getRandValue<uint16_t>(256));
    for (ObjectIn2291& obj : objects)
    {
        fillRandomly(obj);
    }
    objList.setObjects(objects);
}

//==============================================================================
//==============================================================================
//==============================================================================

luxObjectClass::LuxObjectClass ObjectListTestSupport::getValidRandLuxObjectClass()
{
    static const std::vector<luxObjectClass::LuxObjectClass> validValues{luxObjectClass::LuxObjectClass::Unclassified,
                                                                         luxObjectClass::LuxObjectClass::UnknownSmall,
                                                                         luxObjectClass::LuxObjectClass::UnknownBig,
                                                                         luxObjectClass::LuxObjectClass::Pedestrian,
                                                                         luxObjectClass::LuxObjectClass::Bike,
                                                                         luxObjectClass::LuxObjectClass::Car,
                                                                         luxObjectClass::LuxObjectClass::Truck,
                                                                         luxObjectClass::LuxObjectClass::Bicycle};

    const std::size_t index
        = getRandValue<uint8_t>(static_cast<uint8_t>(validValues.size() - 1)); // getRandValue includes maximum!

    return validValues.at(index);
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

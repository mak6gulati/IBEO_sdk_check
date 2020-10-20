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
//!\date Sep 29, 2015
//------------------------------------------------------------------------------

#include "ObjectList2271TestSupport.hpp"

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2271.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

ObjectListScala2271TestSupport::ObjectListScala2271TestSupport() : TestSupport() {}

//==============================================================================

ObjectListScala2271TestSupport::~ObjectListScala2271TestSupport() {}

//==============================================================================

ObjectList2271 ObjectListScala2271TestSupport::createObjList()
{
    ObjectList2271 objList(getRandValue<NTPTime>());
    objList.setScanNumber(getRandValue<uint16_t>());
    objList.setObjectListId(getRandValue<uint8_t>());
    objList.setDeviceId(getRandValue<uint8_t>());
    objList.setDeviceInterfaceVersion(getRandValue<uint16_t>(0x3FFF));
    objList.setReserved(getRandValue<uint32_t>());

    ObjectList2271::ObjectVector& objs = objList.getObjects();
    objs.resize(getRandValue<uint16_t>(500));

    for (uint16_t i = 0; i < objs.size(); ++i)
    {
        fillRandomly(objs[i]);
    }

    return objList;
}

//==============================================================================

ObjectIn2271 ObjectListScala2271TestSupport::createObj(const bool unfAvailable,
                                                       const bool unfContourAvailable,
                                                       const bool filAvailable,
                                                       const bool filContourAvailable)
{
    ObjectIn2271 obj;
    fillRandomly(obj, unfAvailable, unfContourAvailable, filAvailable, filContourAvailable);
    return obj;
}

//==============================================================================

void ObjectListScala2271TestSupport::fillRandomly(ObjectIn2271& obj)
{
    const bool unfAvailable        = getRandValue<bool>();
    const bool unfContourAvailable = unfAvailable ? getRandValue<bool>() : false;
    const bool filAvailable        = getRandValue<bool>();
    const bool filContourAvailable = filAvailable ? getRandValue<bool>() : false;

    fillRandomly(obj, unfAvailable, unfContourAvailable, filAvailable, filContourAvailable);
}

//==============================================================================

void ObjectListScala2271TestSupport::fillRandomly(ObjectIn2271& obj,
                                                  const bool unfAvailable,
                                                  const bool unfContourAvailable,
                                                  const bool filAvailable,
                                                  const bool filContourAvailable)
{
    obj.setObjectId(getRandValue<uint32_t>());
    obj.setInternal(getRandValue<uint8_t>());
    obj.setInterfaceFlags(getRandValue<uint8_t>());

    UnfilteredObjectDataIn2271& unfAttr = obj.getUnfilteredObjectData();
    fillRandomly(unfAttr, unfAvailable, unfContourAvailable);

    FilteredObjectDataIn2271& filAttr = obj.getFilteredObjectData();
    fillRandomly(filAttr, filAvailable, filContourAvailable);

    obj.setReserved(getRandValue<uint32_t>());
}

//==============================================================================

void ObjectListScala2271TestSupport::fillRandomly(UnfilteredObjectDataIn2271& unf,
                                                  const bool isAvailable,
                                                  const bool contourIsAvailable)
{
    unf.setIsValid(isAvailable);
    if (!isAvailable)
    {
        return;
    }

    unf.setPriority(getRandValue<uint8_t>());
    unf.setRelativeTimeOfMeasure(getRandValue<uint16_t>());
    unf.setPositionClosestObjectPoint(getRandValue<Vector2<int16_t>>());
    unf.setReserved(getRandValue<uint16_t>());

    unf.setObjectBoxSize(getRandValue<Vector2<uint16_t>>());
    unf.setObjectBoxSizeSigma(getRandValue<Vector2<uint16_t>>());
    unf.setObjectBoxOrientation(getRandValue<int16_t>());
    unf.setObjectBoxOrientationSigma(getRandValue<uint16_t>());
    unf.setObjectBoxHeight(getRandValue<uint8_t>());

    unf.setReferencePointLocation(getRandValue<RefPointBoxLocation>());
    unf.setReferencePointCoord(getRandValue<Vector2<int16_t>>());
    unf.setReferencePointCoordSigma(getRandValue<Vector2<uint16_t>>());
    unf.setReferencePointPositionCorrCoeff(getRandValue<int16_t>());

    unf.setExistenceProbaility(getRandValue<uint8_t>());

    unf.setPossibleNbOfContourPoints(getRandValue<uint8_t>(20));
    unf.setHasContourPoints(contourIsAvailable);
    if (contourIsAvailable)
    {
        std::vector<ContourPointIn2271>& cps = unf.getContourPoints();
        cps.resize(unf.getPossibleNbOfContourPoints());

        for (uint8_t p = 0; p < unf.getPossibleNbOfContourPoints(); ++p)
        {
            cps[p] = ContourPointIn2271(getRandValue<Vector2<int16_t>>());
        }
    } // unfContourAvailable
}

//==============================================================================

void ObjectListScala2271TestSupport::fillRandomly(FilteredObjectDataIn2271& fil,
                                                  const bool isAvailable,
                                                  const bool contourIsAvailable)
{
    fil.setIsValid(isAvailable);
    if (!isAvailable)
    {
        return;
    }

    fil.setPriority(getRandValue<uint8_t>());

    fil.setObjectAge(getRandValue<uint16_t>());
    fil.setHiddenStatusAge(getRandValue<uint16_t>());
    fil.setDynamicFlags(getRandValue<uint8_t>());

    fil.setRelativeTimeOfMeasure(getRandValue<uint16_t>());
    fil.setPositionClosestObjectPoint(getRandValue<Vector2<int16_t>>());

    fil.setRelativeVelocity(getRandValue<Vector2<int16_t>>());
    fil.setRelativeVelocitySigma(getRandValue<Vector2<uint16_t>>());

    fil.setClassification(getRandValue<rawObjectClass::RawObjectClass>());
    fil.setClassificationQuality(getRandValue<uint8_t>());
    fil.setClassificationAge(getRandValue<uint16_t>());

    fil.setReserved(getRandValue<uint16_t>());

    fil.setObjectBoxSize(getRandValue<Vector2<uint16_t>>());
    fil.setObjectBoxSizeSigma(getRandValue<Vector2<uint16_t>>());
    fil.setObjectBoxOrientation(getRandValue<int16_t>());
    fil.setObjectBoxOrientationSigma(getRandValue<uint16_t>());
    fil.setObjectBoxHeight(getRandValue<uint8_t>());

    fil.setReferencePointLocation(getRandValue<RefPointBoxLocation>());
    fil.setReferencePointCoord(getRandValue<Vector2<int16_t>>());
    fil.setReferencePointCoordSigma(getRandValue<Vector2<uint16_t>>());
    fil.setReferencePointPositionCorrCoeff(getRandValue<int16_t>());

    fil.setExistenceProbaility(getRandValue<uint8_t>());

    fil.setAbsoluteVelocity(getRandValue<Vector2<int16_t>>());
    fil.setAbsoluteVelocitySigma(getRandValue<Vector2<uint16_t>>());
    fil.setVelocityCorrCoeff(getRandValue<int16_t>());

    fil.setAcceleration(getRandValue<Vector2<int16_t>>());
    fil.setAccelerationSigma(getRandValue<Vector2<uint16_t>>());
    fil.setAccelerationCorrCoeff(getRandValue<int16_t>());

    fil.setYawRate(getRandValue<int16_t>());
    fil.setYawRateSigma(getRandValue<uint16_t>());

    fil.setPossibleNbOfContourPoints(getRandValue<uint8_t>(20));
    fil.setHasContourPoints(contourIsAvailable);
    if (contourIsAvailable)
    {
        std::vector<ContourPointIn2271>& cps = fil.getContourPoints();
        cps.resize(fil.getPossibleNbOfContourPoints());

        for (uint8_t p = 0; p < fil.getPossibleNbOfContourPoints(); ++p)
        {
            cps[p] = ContourPointIn2271(getRandValue<Vector2<int16_t>>());
        }
    } // unfContourAvailable
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

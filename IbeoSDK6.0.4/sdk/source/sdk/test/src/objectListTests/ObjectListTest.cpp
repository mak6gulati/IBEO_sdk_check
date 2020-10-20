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

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2271.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2271Exporter2271.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2271Importer2271.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListExporter2271.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImporter2271.hpp>

#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2281.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2281Exporter2281.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/special/ObjectList2281Importer2281.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListExporter2281.hpp>
#include <ibeo/common/sdk/datablocks/objectlist/ObjectListImporter2281.hpp>

#include <objectListTests/ObjectListTestSupport.hpp>

#define BOOST_TEST_MODULE ObjectListTest
#include <boost/test/unit_test.hpp>

//==============================================================================
// Helper macros used for testing members.
//==============================================================================

#define TEST_SETTER(orig, copy, member, type)                                                                          \
    orig.set##member(getDifferentRandValue<type>(orig.get##member()));                                                 \
    BOOST_CHECK(orig != copy);                                                                                         \
    copy.set##member(orig.get##member());                                                                              \
    BOOST_CHECK(orig == copy);

#define TEST_SETTER_NTPTIME(orig, copy, member)                                                                        \
    {                                                                                                                  \
        NTPTime tmpTime = orig.get##member();                                                                          \
        do                                                                                                             \
        {                                                                                                              \
            orig.set##member(getRandValue<NTPTime>());                                                                 \
        } while ((orig.get##member().is_not_a_date_time() && tmpTime.is_not_a_date_time())                             \
                 || (orig.get##member() == tmpTime));                                                                  \
        BOOST_CHECK(orig != copy);                                                                                     \
        copy.set##member(orig.get##member());                                                                          \
        BOOST_CHECK(orig == copy);                                                                                     \
    }

#define TEST_SETTER_ENUM(orig, copy, member, enumType, intType)                                                        \
    orig.set##member(enumType(getDifferentRandValue<intType>(static_cast<intType>(orig.get##member()))));              \
    BOOST_CHECK(orig != copy);                                                                                         \
    copy.set##member(orig.get##member());                                                                              \
    BOOST_CHECK(orig == copy);

#define TEST_ASSIGNMENT(orig, copy, member, type)                                                                      \
    orig.set##member(getDifferentRandValue<type>(orig.get##member()));                                                 \
    BOOST_CHECK(orig != copy);                                                                                         \
    copy = orig;                                                                                                       \
    BOOST_CHECK(orig == copy);

#define TEST_ASSIGNMENT_NTPTIME(orig, copy, member)                                                                    \
    {                                                                                                                  \
        NTPTime tmpTime = orig.get##member();                                                                          \
        do                                                                                                             \
        {                                                                                                              \
            orig.set##member(getRandValue<NTPTime>());                                                                 \
        } while ((orig.get##member().is_not_a_date_time() && tmpTime.is_not_a_date_time())                             \
                 || (orig.get##member() == tmpTime));                                                                  \
        BOOST_CHECK(orig != copy);                                                                                     \
        copy = orig;                                                                                                   \
        BOOST_CHECK(orig == copy);                                                                                     \
    }

#define TEST_ASSIGNMENT_ENUM(orig, copy, member, enumType, intType)                                                    \
    orig.set##member(enumType(getDifferentRandValue<intType>(static_cast<intType>(orig.get##member()))));              \
    BOOST_CHECK(orig != copy);                                                                                         \
    copy = orig;                                                                                                       \
    BOOST_CHECK(orig == copy);

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ObjectListBasicTestSuite)

//==============================================================================

class Fixture : public unittests::ObjectListTestSupport
{
}; // Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createObjectList, Fixture)
{
    ObjectList objList;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoObjectListIdentity2281, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ObjectListExporter2281 exporter;
        ObjectList orig(createObjectList<ObjectList>());

        // Re-init all members that are not serialized by data type 0x2281 and correct rounding issues.
        Object defaultObj;
        for (Object& object : orig.getObjects())
        {
            object.setDynamicFlags(defaultObj.getDynamicFlags());

            int8_t heightOffset4Cm
                = round<int8_t>(std::min(std::max(object.getObjectBoxHeightOffset(), -5.12f), 5.08f) * 25.0f);
            object.setObjectBoxHeightOffset(float(heightOffset4Cm) / 25.0f);
            uint8_t heightOffsetSigmaCm
                = round<uint8_t>(std::min(object.getObjectBoxHeightOffsetSigma(), 2.55f) * 100.0f);
            object.setObjectBoxHeightOffsetSigma(float(heightOffsetSigmaCm) / 100.0f);

            uint8_t classificationQualityInt
                = round<uint8_t>(std::min(std::max(object.getClassificationQuality(), 0.0f), 2.55f) * 100.0f);
            object.setClassificationQuality((float(classificationQualityInt)) / 100.0f);

            for (ContourPoint& contourPoint : object.getContourPoints())
            {
                contourPoint.setXSigma(NaN);
                contourPoint.setYSigma(NaN);
                contourPoint.setCorrCoeff(NaN);
                contourPoint.setExistenceProbability(NaN);
            }
        }

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, orig));

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(orig)), 0, NTPTime());

        ObjectList copy;
        BOOST_CHECK(orig != copy);
        const ObjectListImporter2281 importer;
        BOOST_CHECK(importer.deserialize(ss, copy, dh));
        BOOST_CHECK(orig == copy);
    } // for r
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoObjectListEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ObjectList orig;
        ObjectList copy;
        BOOST_CHECK(orig == copy);

        TEST_SETTER_NTPTIME(orig, copy, Timestamp);
        TEST_SETTER(orig, copy, ObjectListId, uint8_t);
        TEST_SETTER(orig, copy, Flags, uint8_t);
        TEST_SETTER_ENUM(orig, copy, DeviceType, ObjectList::DeviceType, uint8_t);
        TEST_SETTER(orig, copy, DeviceInterfaceVersion, uint16_t);

        for (ObjectList::ObjectVector::size_type objIx = 0; objIx < orig.getNbOfObjects(); ++objIx)
        {
            Object& origObj = orig.getObjects()[objIx];
            Object& copyObj = copy.getObjects()[objIx];

            TEST_SETTER(origObj, copyObj, ObjectId, uint32_t);
            TEST_SETTER_NTPTIME(origObj, copyObj, Timestamp);

            TEST_SETTER(origObj, copyObj, ObjectFlags, uint16_t);
            TEST_SETTER(origObj, copyObj, DynamicFlags, uint8_t);

            TEST_SETTER(origObj, copyObj, ObjectAge, uint32_t);
            TEST_SETTER(origObj, copyObj, HiddenStatusAge, uint16_t);

            TEST_SETTER(origObj, copyObj, ObjectBoxSize, Vector2<float>);
            TEST_SETTER(origObj, copyObj, ObjectBoxSizeSigma, Vector2<float>);
            TEST_SETTER(origObj, copyObj, ObjectBoxHeight, float);
            TEST_SETTER(origObj, copyObj, ObjectBoxHeightSigma, float);
            TEST_SETTER(origObj, copyObj, ObjectBoxHeightOffset, float);
            TEST_SETTER(origObj, copyObj, ObjectBoxHeightOffsetSigma, float);

            TEST_SETTER_ENUM(origObj, copyObj, ReferencePointLocation, RefPointBoxLocation, uint8_t);
            TEST_SETTER(origObj, copyObj, ReferencePointCoord, Vector2<float>);
            TEST_SETTER(origObj, copyObj, ReferencePointCoordSigma, Vector2<float>);
            TEST_SETTER(origObj, copyObj, ReferencePointCoordCorrCoeff, float);

            TEST_SETTER(origObj, copyObj, CourseAngle, float);
            TEST_SETTER(origObj, copyObj, CourseAngleSigma, float);
            TEST_SETTER(origObj, copyObj, YawRate, float);
            TEST_SETTER(origObj, copyObj, YawRateSigma, float);

            TEST_SETTER_ENUM(origObj, copyObj, Classification, ObjectClass, uint8_t);
            TEST_SETTER(origObj, copyObj, ClassificationQuality, float);
            TEST_SETTER(origObj, copyObj, ClassificationAge, uint32_t);

            TEST_SETTER(origObj, copyObj, MotionReferencePoint, Vector2<float>);
            TEST_SETTER(origObj, copyObj, MotionReferencePointSigma, Vector2<float>);

            TEST_SETTER(origObj, copyObj, CenterOfGravity, Vector2<float>);
            TEST_SETTER(origObj, copyObj, ExistenceProbability, float);
            TEST_SETTER(origObj, copyObj, ObjectPriority, uint16_t);

            TEST_SETTER(origObj, copyObj, RelativeVelocity, Vector2<float>);
            TEST_SETTER(origObj, copyObj, RelativeVelocitySigma, Vector2<float>);
            TEST_SETTER(origObj, copyObj, AbsoluteVelocity, Vector2<float>);
            TEST_SETTER(origObj, copyObj, AbsoluteVelocitySigma, Vector2<float>);

            TEST_SETTER(origObj, copyObj, Acceleration, Vector2<float>);
            TEST_SETTER(origObj, copyObj, AccelerationSigma, Vector2<float>);

            TEST_SETTER(origObj, copyObj, ClosestObjectPointCoord, Vector2<float>);
            for (ObjectList::ObjectVector::size_type cpIx = 0; cpIx < origObj.getNumContourPoints(); ++cpIx)
            {
                ContourPoint& origCp = origObj.getContourPoints()[cpIx];
                ContourPoint& copyCp = copyObj.getContourPoints()[cpIx];

                TEST_SETTER(origCp, copyCp, X, float);
                TEST_SETTER(origCp, copyCp, Y, float);
                TEST_SETTER(origCp, copyCp, XSigma, float);
                TEST_SETTER(origCp, copyCp, YSigma, float);
                TEST_SETTER(origCp, copyCp, CorrCoeff, float);
                TEST_SETTER(origCp, copyCp, ExistenceProbability, float);
            }
        }

        //	obj.setMeasurementList(getDifferentRandValue<MeasurementList>());
        //	obj.setUnfilteredObjectData(getDifferentRandValue<UnfilteredObjectData>());
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoObjectListAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        ObjectList orig;
        ObjectList copy;
        BOOST_CHECK(orig == copy);

        TEST_ASSIGNMENT_NTPTIME(orig, copy, Timestamp);
        TEST_ASSIGNMENT(orig, copy, ObjectListId, uint8_t);
        TEST_ASSIGNMENT(orig, copy, Flags, uint8_t);
        TEST_ASSIGNMENT_ENUM(orig, copy, DeviceType, ObjectList::DeviceType, uint8_t);
        TEST_ASSIGNMENT(orig, copy, DeviceInterfaceVersion, uint16_t);

        for (ObjectList::ObjectVector::size_type objIx = 0; objIx < orig.getNbOfObjects(); ++objIx)
        {
            Object& origObj = orig.getObjects()[objIx];
            Object& copyObj = copy.getObjects()[objIx];

            TEST_ASSIGNMENT(origObj, copyObj, ObjectId, uint32_t);
            TEST_ASSIGNMENT_NTPTIME(origObj, copyObj, Timestamp);

            TEST_ASSIGNMENT(origObj, copyObj, ObjectFlags, uint16_t);
            TEST_ASSIGNMENT(origObj, copyObj, DynamicFlags, uint8_t);

            TEST_ASSIGNMENT(origObj, copyObj, ObjectAge, uint32_t);
            TEST_ASSIGNMENT(origObj, copyObj, HiddenStatusAge, uint16_t);

            TEST_ASSIGNMENT(origObj, copyObj, ObjectBoxSize, Vector2<float>);
            TEST_ASSIGNMENT(origObj, copyObj, ObjectBoxSizeSigma, Vector2<float>);
            TEST_ASSIGNMENT(origObj, copyObj, ObjectBoxHeight, float);
            TEST_ASSIGNMENT(origObj, copyObj, ObjectBoxHeightSigma, float);
            TEST_ASSIGNMENT(origObj, copyObj, ObjectBoxHeightOffset, float);
            TEST_ASSIGNMENT(origObj, copyObj, ObjectBoxHeightOffsetSigma, float);

            TEST_ASSIGNMENT_ENUM(origObj, copyObj, ReferencePointLocation, RefPointBoxLocation, uint8_t);
            TEST_ASSIGNMENT(origObj, copyObj, ReferencePointCoord, Vector2<float>);
            TEST_ASSIGNMENT(origObj, copyObj, ReferencePointCoordSigma, Vector2<float>);
            TEST_ASSIGNMENT(origObj, copyObj, ReferencePointCoordCorrCoeff, float);

            TEST_ASSIGNMENT(origObj, copyObj, CourseAngle, float);
            TEST_ASSIGNMENT(origObj, copyObj, CourseAngleSigma, float);
            TEST_ASSIGNMENT(origObj, copyObj, YawRate, float);
            TEST_ASSIGNMENT(origObj, copyObj, YawRateSigma, float);

            TEST_ASSIGNMENT_ENUM(origObj, copyObj, Classification, ObjectClass, uint8_t);
            TEST_ASSIGNMENT(origObj, copyObj, ClassificationQuality, float);
            TEST_ASSIGNMENT(origObj, copyObj, ClassificationAge, uint32_t);

            TEST_ASSIGNMENT(origObj, copyObj, MotionReferencePoint, Vector2<float>);
            TEST_ASSIGNMENT(origObj, copyObj, MotionReferencePointSigma, Vector2<float>);

            TEST_ASSIGNMENT(origObj, copyObj, CenterOfGravity, Vector2<float>);
            TEST_ASSIGNMENT(origObj, copyObj, ExistenceProbability, float);
            TEST_ASSIGNMENT(origObj, copyObj, ObjectPriority, uint16_t);

            TEST_ASSIGNMENT(origObj, copyObj, RelativeVelocity, Vector2<float>);
            TEST_ASSIGNMENT(origObj, copyObj, RelativeVelocitySigma, Vector2<float>);
            TEST_ASSIGNMENT(origObj, copyObj, AbsoluteVelocity, Vector2<float>);
            TEST_ASSIGNMENT(origObj, copyObj, AbsoluteVelocitySigma, Vector2<float>);

            TEST_ASSIGNMENT(origObj, copyObj, Acceleration, Vector2<float>);
            TEST_ASSIGNMENT(origObj, copyObj, AccelerationSigma, Vector2<float>);

            TEST_ASSIGNMENT(origObj, copyObj, ClosestObjectPointCoord, Vector2<float>);
            for (ObjectList::ObjectVector::size_type cpIx = 0; cpIx < origObj.getNumContourPoints(); ++cpIx)
            {
                ContourPoint& origCp = origObj.getContourPoints()[cpIx];
                ContourPoint& copyCp = copyObj.getContourPoints()[cpIx];

                TEST_ASSIGNMENT(origCp, copyCp, X, float);
                TEST_ASSIGNMENT(origCp, copyCp, Y, float);
                TEST_ASSIGNMENT(origCp, copyCp, XSigma, float);
                TEST_ASSIGNMENT(origCp, copyCp, YSigma, float);
                TEST_ASSIGNMENT(origCp, copyCp, CorrCoeff, float);
                TEST_ASSIGNMENT(origCp, copyCp, ExistenceProbability, float);
            }
        }

        //	obj.setMeasurementList(getDifferentRandValue<MeasurementList>());
        //	obj.setUnfilteredObjectData(getDifferentRandValue<UnfilteredObjectData>());
    }
}

//==============================================================================

// test conversion from data container 0x2281
BOOST_FIXTURE_TEST_CASE(isIoObjectListConversion2281, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        // Create special 2281 object list as original.
        ObjectList2281 orig(createObjectList<ObjectList2281>());

        ObjectList temp;
        {
            std::stringstream ss;

            // .. and export to container.
            const ObjectList2281Exporter2281 exporter;
            BOOST_CHECK(exporter.serialize(ss, orig));

            // Import as generic object list from container.
            const IbeoDataHeader dh(
                exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(orig)), 0, NTPTime());
            const ObjectListImporter2281 importer;
            BOOST_CHECK(importer.deserialize(ss, temp, dh));
        }

        ObjectList2281 copy;
        {
            std::stringstream ss;

            // Export generic object list to container.
            const ObjectListExporter2281 exporter;
            BOOST_CHECK(exporter.serialize(ss, temp));

            // Import as special object list from container.
            const IbeoDataHeader dh(
                exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(temp)), 0, NTPTime());
            const ObjectList2281Importer2281 importer;
            BOOST_CHECK(importer.deserialize(ss, copy, dh));
        }

        // Re-init all members that are not serialized by data type 0x2281 and correct rounding issues.
        static const ObjectList2281 def;
        orig.setReserved1(def.getReserved1());

        static const ObjectIn2281 defObj;
        for (std::size_t ix = 0; ix < orig.getObjects().size(); ++ix)
        {
            ObjectIn2281& origObj = orig.getObjects()[ix];
            ObjectIn2281& copyObj = copy.getObjects()[ix];

            // Longitudinal acceleration is destroyed during conversion.
            copyObj.setLongitudinalAcceleration(origObj.getLongitudinalAcceleration());
            copyObj.setLongitudinalAccelerationSigma(origObj.getLongitudinalAccelerationSigma());

            origObj.setReserved3(defObj.getReserved3());
            origObj.setReserved4(defObj.getReserved4());
        }

        // Copy must be identical to original!
        BOOST_CHECK(orig == copy);
    } // for r
}

//==============================================================================

// test conversion from data container 0x2271
BOOST_FIXTURE_TEST_CASE(isIoObjectListConversion2271, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        // Create special 2271 object list as original.
        ObjectList2271 orig(createObjectList<ObjectList2271>());

        ObjectList temp;
        {
            std::stringstream ss;

            // .. and export to container.
            const ObjectList2271Exporter2271 exporter;
            BOOST_CHECK(exporter.serialize(ss, orig));

            // Import as generic object list from container.
            const IbeoDataHeader dh(
                exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(orig)), 0, NTPTime());
            const ObjectListImporter2271 importer;
            BOOST_CHECK(importer.deserialize(ss, temp, dh));
        }

        ObjectList2271 copy;
        {
            std::stringstream ss;

            // Export generic object list to container.
            const ObjectListExporter2271 exporter;
            BOOST_CHECK(exporter.serialize(ss, temp));

            // Import as special object list from container.
            const IbeoDataHeader dh(
                exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(temp)), 0, NTPTime());
            const ObjectList2271Importer2271 importer;
            BOOST_CHECK(importer.deserialize(ss, copy, dh));
        }

        // Re-init all members that are not serialized by data type 0x2271 and correct rounding issues.
        static const ObjectList2271 def;
        orig.setScanNumber(def.getScanNumber());
        orig.setReserved(def.getReserved());

        static const ObjectIn2271 defObj;
        for (std::size_t ix = 0; ix < orig.getObjects().size(); ++ix)
        {
            ObjectIn2271& origObj = orig.getObjects()[ix];
            //			ObjectIn2271& copyObj = copy.getObjects()[ix];

            origObj.setInterfaceFlags(defObj.getInterfaceFlags());
            origObj.setReserved(defObj.getReserved());

            origObj.getFilteredObjectData().setReserved(defObj.getFilteredObjectData().getReserved());
            origObj.getUnfilteredObjectData().setReserved(defObj.getUnfilteredObjectData().getReserved());

            origObj.setReserved(defObj.getReserved());
            origObj.getFilteredObjectData().setVelocityCorrCoeff(defObj.getFilteredObjectData().getVelocityCorrCoeff());
        }

        // Copy must be identical to original!
        BOOST_CHECK(orig == copy);
    } // for r
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

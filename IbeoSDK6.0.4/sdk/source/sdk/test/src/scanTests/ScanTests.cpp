//==============================================================================
//!\file
//!
//! Tests for General Data Container SCANS
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date June 12, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/scan/special/Scan2205.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2209.hpp>
#include "Scan2209TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/scan/special/Scan2202Exporter2202.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2205Exporter2205.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2209Importer2209.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2202Importer2202.hpp>
#include <ibeo/common/sdk/datablocks/scan/special/Scan2209Exporter2209.hpp>

#include <ibeo/common/sdk/datablocks/scan/Scan.hpp>
#include "ScanTestSupport.hpp"
#include "Scan2202TestSupport.hpp"
#include "Scan2205TestSupport.hpp"
#include <ibeo/common/sdk/datablocks/scan/ScanImporter2202.hpp>
#include <ibeo/common/sdk/datablocks/scan/ScanImporter2205.hpp>
#include <ibeo/common/sdk/datablocks/scan/ScanImporter2209.hpp>
#include <ibeo/common/sdk/datablocks/scan/ScanExporter2209.hpp>

#define BOOST_TEST_MODULE ScanTest
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(ScanBasicTestSuite)

//==============================================================================

class Fixture : public unittests::ScanTestSupport
{
}; // Fixture

//==============================================================================

bool operator==(const Scan& lhs, const Scan2205& rhs)
{
    if (lhs.getStartTimestamp() != rhs.getStartTimestamp())
    {
        return false;
    }
    if (lhs.getEndTimeOffset() != rhs.getEndTimeOffset())
    {
        return false;
    }
    if (lhs.getFlags() != rhs.getFlags())
    {
        return false;
    }

    if (lhs.getScanNumber() != rhs.getScanNumber())
    {
        return false;
    }

    if (lhs.getReserved0() != rhs.getReserved0())
    {
        return false;
    }

    if (lhs.getReserved1() != rhs.getReserved1())
    {
        return false;
    }

    if (lhs.getScannerInfos() != (rhs.getScannerInfos()))
    {
        return false;
    }
    if (lhs.getScanPoints() != (rhs.getScanPoints()))
    {
        return false;
    }

    return true;
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createScan, Fixture)
{
    Scan scan;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoScanIdentity, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const ScanExporter2209 exporter;
        Scan scanGdc(createScan<Scan>());

        //for this test the scan-coordinates must be in vehicle coordinates
        //(constraint: ScanGdc is always in vehicle coordinates and no valid
        //back-transformation to Scanner-Coords on export is given)
        //we reset the flag prev. filled with random data
        scanGdc.setVehicleCoordinates();

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, scanGdc));

        const IbeoDataHeader dh(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(scanGdc)), 0, NTPTime());

        Scan scan2209;
        BOOST_CHECK(scanGdc != scan2209);
        const ScanImporter2209 importer;
        BOOST_CHECK(importer.deserialize(ss, scan2209, dh));

        BOOST_CHECK(scanGdc == scan2209);
    } // for r
}

//==============================================================================
//Only importer available
BOOST_FIXTURE_TEST_CASE(isIoScanIdentity2202Gdc, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Scan2202Exporter2202 exporter2202;
        Scan2202 scan2202(createScan<Scan2202>());

        std::stringstream ss;

        BOOST_CHECK(exporter2202.serialize(ss, scan2202));

        const IbeoDataHeader dh(
            exporter2202.getDataType(), 0, uint32_t(exporter2202.getSerializedSize(scan2202)), 0, NTPTime());

        const ScanImporter2202 scanImporter2202;
        Scan scanGdc;
        BOOST_CHECK(scanGdc != scan2202);
        BOOST_CHECK(scanImporter2202.deserialize(ss, scanGdc, dh));

        BOOST_CHECK(scanGdc == scan2202);
    } // for r
}

//==============================================================================
// test unit conversion
BOOST_FIXTURE_TEST_CASE(checkImportScan2202UnitConversion, Fixture)
{
    const Scan2202Exporter2202 exporter2202;
    Scan2202 scan2202(createScan<Scan2202>());

    // set some defined values to check after import
    // 360 degrees per rotation
    scan2202.setAngleTicksPerRotation(36);
    // 360 / 36 = 10 degrees per tick
    scan2202.setStartAngleTicks(1);
    scan2202.setEndAngleTicks(2);
    scan2202.setMountingPositionYawAngleTicks(3);
    scan2202.setMountingPositionPitchAngleTicks(4);
    scan2202.setMountingPositionRollAngleTicks(5);
    scan2202.setMountingPositionCmX(100);
    scan2202.setMountingPositionCmY(-100);
    scan2202.setMountingPositionCmZ(200);

    std::stringstream ss;

    BOOST_CHECK(exporter2202.serialize(ss, scan2202));

    const IbeoDataHeader dh(
        exporter2202.getDataType(), 0, uint32_t(exporter2202.getSerializedSize(scan2202)), 0, NTPTime());

    const ScanImporter2202 scanImporter2202;
    Scan scanGdc;
    BOOST_CHECK(scanGdc != scan2202);
    BOOST_CHECK(scanImporter2202.deserialize(ss, scanGdc, dh));

    auto info = scanGdc.getScannerInfos().front();
    BOOST_CHECK(fuzzyFloatEqualT<7>(info.getStartAngle(), 10.0F * deg2radf));
    BOOST_CHECK(fuzzyFloatEqualT<7>(info.getEndAngle(), 20.0F * deg2radf));
    BOOST_CHECK(fuzzyFloatEqualT<7>(info.getYawAngle(), 30.0F * deg2radf));
    BOOST_CHECK(fuzzyFloatEqualT<7>(info.getPitchAngle(), 40.0F * deg2radf));
    BOOST_CHECK(fuzzyFloatEqualT<7>(info.getRollAngle(), 50.0F * deg2radf));
    BOOST_CHECK(fuzzyFloatEqualT<7>(info.getOffsetX(), 1.0F));
    BOOST_CHECK(fuzzyFloatEqualT<7>(info.getOffsetY(), -1.0F));
    BOOST_CHECK(fuzzyFloatEqualT<7>(info.getOffsetZ(), 2.0F));
}

//==============================================================================

// The following test checks equality for Scan2209->Scan_GDC->Scan2209
BOOST_FIXTURE_TEST_CASE(isIoScanIdentity2209Gdc2209, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan2209 scan2209orig(createScan<Scan2209>());

        //for this test we must scan-coordinates to be in vehicle coordinates
        //(constraint: ScanGdc is always in vehicle coordinates and no valid
        //back-transformation to Scanner-Coords on export is given)
        //we reset the flag prev. filled with random data
        scan2209orig.setFlags(scan2209orig.getFlags() | static_cast<uint32_t>(Scan::Flags::VehicleCoordinates));

        const Scan2209Exporter2209 exporter2209_2209;

        std::stringstream ss;
        BOOST_CHECK(exporter2209_2209.serialize(ss, scan2209orig));

        const IbeoDataHeader dh(exporter2209_2209.getDataType(),
                                0,
                                uint32_t(exporter2209_2209.getSerializedSize(scan2209orig)),
                                0,
                                NTPTime());

        Scan scanGdc;
        const ScanImporter2209 importer;
        BOOST_CHECK(importer.deserialize(ss, scanGdc, dh));

        const ScanExporter2209 exporter2209;
        BOOST_CHECK(exporter2209.serialize(ss, scanGdc));
        const IbeoDataHeader dhGdc(
            exporter2209.getDataType(), 0, uint32_t(exporter2209.getSerializedSize(scanGdc)), 0, NTPTime());

        Scan2209 scan2209dup;
        BOOST_CHECK(scan2209orig != scan2209dup);
        const Scan2209Importer2209 importer2209_2209;
        BOOST_CHECK(importer2209_2209.deserialize(ss, scan2209dup, dh));

        BOOST_CHECK(scan2209orig == scan2209dup);
    } // for r
}

//==============================================================================

// The following test checks equality for Scan2205->Scan_GDC
BOOST_FIXTURE_TEST_CASE(isIoScanIdentity2205Gdc, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Scan2205Exporter2205 exporter2205;
        Scan2205 scan2205(createScan<Scan2205>());

        //for this test the scan-coordinates must be in vehicle coordinates
        //(constraint: ScanGdc is always in vehicle coordinates and no valid
        //back-transformation to Scanner-Coords on export is given)
        //we reset the flag prev. filled with random data
        scan2205.setVehicleCoordinates();

        std::stringstream ss;
        BOOST_CHECK(exporter2205.serialize(ss, scan2205));

        const IbeoDataHeader dh(
            exporter2205.getDataType(), 0, uint32_t(exporter2205.getSerializedSize(scan2205)), 0, NTPTime());

        Scan scanGdc;
        const ScanImporter2205 importer;
        BOOST_CHECK(importer.deserialize(ss, scanGdc, dh));

        BOOST_CHECK(scanGdc == scan2205);
    } // for r
}

// The following test checks equality for Scan2202->Scan_GDC->Scan2209
BOOST_FIXTURE_TEST_CASE(isIoScanIdentity2202Gdc2209, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const Scan2202Exporter2202 exporter2202;
        Scan2202 scan2202(createScan<Scan2202>());

        std::stringstream ss;

        // serialize 2202
        BOOST_CHECK(exporter2202.serialize(ss, scan2202));
        const IbeoDataHeader dh2202(
            exporter2202.getDataType(), 0, uint32_t(exporter2202.getSerializedSize(scan2202)), 0, NTPTime());

        // 2202 -> gdc
        Scan scanGdcFrom2202;
        const ScanImporter2202 importer;
        BOOST_CHECK(importer.deserialize(ss, scanGdcFrom2202, dh2202));

        // gdc -> 2209
        const ScanExporter2209 exporter2209;
        BOOST_CHECK(exporter2209.serialize(ss, scanGdcFrom2202));
        const IbeoDataHeader dh2209(
            exporter2209.getDataType(), 0, uint32_t(exporter2209.getSerializedSize(scanGdcFrom2202)), 0, NTPTime());

        // 2209 -> gdc
        Scan scanGdcFrom2209;
        BOOST_CHECK(scanGdcFrom2202 != scanGdcFrom2209);
        const ScanImporter2209 importer2209;
        BOOST_CHECK(importer2209.deserialize(ss, scanGdcFrom2209, dh2209));

        // problem is 2202 does NOT transform to vehicle coordinates on import
        // but 2209 does! -> comparison fails because flags and points are different!
        BOOST_CHECK(!scanGdcFrom2202.isVehicleCoordinates());
        auto tm = scanGdcFrom2202.getScannerInfos().front().getCoordinateSystemTransformationMatrix();
        // to compare also transform into vehicle coordinate system
        for (auto& pt : scanGdcFrom2202.getScanPoints())
        {
            Vector3<float> point{pt.getPositionX(), pt.getPositionY(), pt.getPositionZ()};
            point = tm * point;
            pt.setPosX(point.getX());
            pt.setPosY(point.getY());
            pt.setPosZ(point.getZ());
        }
        scanGdcFrom2202.setVehicleCoordinates();
        BOOST_CHECK(scanGdcFrom2202 == scanGdcFrom2209);
    } // for r
}

//==============================================================================
// test vehicle coordinate transformation
BOOST_FIXTURE_TEST_CASE(checkImportScan2209VehicleTransformation, Fixture)
{
    for (int i = 0; i < nbOfRepeats; i++)
    {
        const Scan2209Exporter2209 exporter2209;
        Scan2209 scan2209(createScan<Scan2209>());

        const auto testRotationOrder
            = static_cast<RotationOrder>(getRandValue<uint8_t>(static_cast<uint8_t>(RotationOrder::YawPitchRoll)));
        const auto testStartAngle = getRandValue<float>(static_cast<float>(-M_PI), static_cast<float>(M_PI));
        const auto testEndAngle   = getRandValue<float>(static_cast<float>(-M_PI), static_cast<float>(M_PI));
        const auto testYawAngle   = getRandValue<float>(static_cast<float>(-M_PI), static_cast<float>(M_PI));
        const auto testPitchAngle = getRandValue<float>(static_cast<float>(-M_PI), static_cast<float>(M_PI));
        const auto testRollAngle  = getRandValue<float>(static_cast<float>(-M_PI), static_cast<float>(M_PI));
        const auto testOffsetX    = getRandValue<float>(-10.0F, 10.0F);
        const auto testOffsetY    = getRandValue<float>(-10.0F, 10.0F);
        const auto testOffsetZ    = getRandValue<float>(-10.0F, 10.0F);

        // set some defined values to check after import
        // 360 degrees per rotation
        for (auto& info : scan2209.getScannerInfos())
        {
            info.setStartAngle(testStartAngle);
            info.setEndAngle(testEndAngle);
            info.setYawAngle(testYawAngle);
            info.setPitchAngle(testPitchAngle);
            info.setRollAngle(testRollAngle);
            info.setOffsetX(testOffsetX);
            info.setOffsetY(testOffsetY);
            info.setOffsetZ(testOffsetZ);
            info.setRotationOrder(testRotationOrder);
            auto roto = info.getRotationOrder();
            BOOST_CHECK(roto == testRotationOrder);
        }
        scan2209.setVehicleCoordinates(false);

        std::stringstream ss;

        BOOST_CHECK(exporter2209.serialize(ss, scan2209));

        const IbeoDataHeader dh(
            exporter2209.getDataType(), 0, uint32_t(exporter2209.getSerializedSize(scan2209)), 0, NTPTime());

        const ScanImporter2209 scanImporter2209;
        Scan scanGdc;
        BOOST_CHECK(scanImporter2209.deserialize(ss, scanGdc, dh));

        auto infoGdc = scanGdc.getScannerInfos().front();
        BOOST_CHECK(scanGdc.isVehicleCoordinates() == true);
        auto roto = infoGdc.getRotationOrder();
        BOOST_CHECK(roto == testRotationOrder);
        BOOST_CHECK(fuzzyFloatEqualT<7>(infoGdc.getStartAngle(), testStartAngle));
        BOOST_CHECK(fuzzyFloatEqualT<7>(infoGdc.getEndAngle(), testEndAngle));
        BOOST_CHECK(fuzzyFloatEqualT<7>(infoGdc.getYawAngle(), testYawAngle));
        BOOST_CHECK(fuzzyFloatEqualT<7>(infoGdc.getPitchAngle(), testPitchAngle));
        BOOST_CHECK(fuzzyFloatEqualT<7>(infoGdc.getRollAngle(), testRollAngle));
        BOOST_CHECK(fuzzyFloatEqualT<7>(infoGdc.getOffsetX(), testOffsetX));
        BOOST_CHECK(fuzzyFloatEqualT<7>(infoGdc.getOffsetY(), testOffsetY));
        BOOST_CHECK(fuzzyFloatEqualT<7>(infoGdc.getOffsetZ(), testOffsetZ));

        // check if a point got transformed correctly
        for (uint32_t ptidx = 0; ptidx < scanGdc.getNumberOfScanPoints(); ptidx++)
        {
            const auto& scanPtGdc  = scanGdc.getScanPoints()[ptidx];
            const auto& scanPt2209 = scan2209.getScanPoints()[ptidx];

            // transform 2209 pt into vehicle coordinates
            auto scanPt2209Transformed = scanPt2209;
            Vector3<float> point{scanPt2209.getPositionX(), scanPt2209.getPositionY(), scanPt2209.getPositionZ()};
            point = scan2209.getScannerInfos()[scanPt2209.getDeviceId()].getCoordinateSystemTransformationMatrix()
                    * point;
            scanPt2209Transformed.setPosX(point.getX());
            scanPt2209Transformed.setPosY(point.getY());
            scanPt2209Transformed.setPosZ(point.getZ());

            // skip points with infinity value because == fails
            if ((fabsf(point.getX()) == fabsf(scanPtGdc.getPositionX()))
                && (fabsf(point.getX()) == std::numeric_limits<float>::infinity()))
                continue;
            if ((fabsf(point.getY()) == fabsf(scanPtGdc.getPositionY()))
                && (fabsf(point.getY()) == std::numeric_limits<float>::infinity()))
                continue;
            if ((fabsf(point.getZ()) == fabsf(scanPtGdc.getPositionZ()))
                && (fabsf(point.getZ()) == std::numeric_limits<float>::infinity()))
                continue;

            BOOST_CHECK(scanPtGdc == scanPt2209Transformed);
        }
    }
}

//==============================================================================

//test operators != and operator==
BOOST_FIXTURE_TEST_CASE(isIoScanEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan scanOrig, scanCopy;
        BOOST_CHECK(scanOrig == scanCopy);

        NTPTime tmpTime = scanOrig.getStartTimestamp();
        do
        {
            scanOrig.setStartTimestamp(getRandValue<NTPTime>());
        } while ((scanOrig.getStartTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (scanOrig.getStartTimestamp() == tmpTime));

        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setStartTimestamp(scanOrig.getStartTimestamp());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setEndTimeOffset(getDifferentRandValue<uint32_t>(scanOrig.getEndTimeOffset()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setEndTimeOffset(scanOrig.getEndTimeOffset());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setFlags(getDifferentRandValue<uint32_t>(scanOrig.getFlags()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setFlags(scanOrig.getFlags());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanNumber(getDifferentRandValue<uint16_t>(scanOrig.getScanNumber()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScanNumber(scanOrig.getScanNumber());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setReserved0(getDifferentRandValue<uint8_t>(scanOrig.getReserved0()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setReserved0(scanOrig.getReserved0());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setReserved1(getDifferentRandValue<uint16_t>(scanOrig.getReserved1()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setReserved1(scanOrig.getReserved1());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScannerInfos(getRandValue<Scan::ScannerInfoVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScannerInfos(scanOrig.getScannerInfos());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanPoints(getRandValue<Scan::ScanPointVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScanPoints(scanOrig.getScanPoints());
        BOOST_CHECK(scanOrig == scanCopy);
    }
}

//==============================================================================

//test operator=
BOOST_FIXTURE_TEST_CASE(isIoScanAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Scan scanOrig, scanCopy;
        BOOST_CHECK(scanOrig == scanCopy);

        NTPTime tmpTime = scanOrig.getStartTimestamp();
        do
        {
            scanOrig.setStartTimestamp(getRandValue<NTPTime>());
        } while ((scanOrig.getStartTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                 || (scanOrig.getStartTimestamp() == tmpTime));

        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setEndTimeOffset(getDifferentRandValue<uint32_t>(scanOrig.getEndTimeOffset()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setFlags(getDifferentRandValue<uint32_t>(scanOrig.getFlags()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setFlags(scanOrig.getFlags());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanNumber(getDifferentRandValue<uint16_t>(scanOrig.getScanNumber()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setReserved0(getDifferentRandValue<uint8_t>(scanOrig.getReserved0()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setReserved1(getDifferentRandValue<uint16_t>(scanOrig.getReserved1()));
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy = scanOrig;
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScannerInfos(getRandValue<Scan::ScannerInfoVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScannerInfos(scanOrig.getScannerInfos());
        BOOST_CHECK(scanOrig == scanCopy);

        scanOrig.setScanPoints(getRandValue<Scan::ScanPointVector>());
        BOOST_CHECK(scanOrig != scanCopy);
        scanCopy.setScanPoints(scanOrig.getScanPoints());
        BOOST_CHECK(scanOrig == scanCopy);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

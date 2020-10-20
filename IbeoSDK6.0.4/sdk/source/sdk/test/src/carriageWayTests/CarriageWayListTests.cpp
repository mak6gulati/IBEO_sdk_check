//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Dec 19, 2018
//------------------------------------------------------------------------------

#include "CarriageWayListTestSupport.hpp"
#include <ibeo/common/sdk/datablocks/carriageway/CarriageWayListExporter6972.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/CarriageWayListImporter6970.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/CarriageWayListImporter6972.hpp>

#define BOOST_TEST_MODULE CarriageWayListTests
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
using namespace ibeo::common::sdk::lanes;
//==============================================================================

BOOST_AUTO_TEST_SUITE(CarriageWayListTestSuite)

//==============================================================================

class Fixture : public unittests::CarriageListWayTestSupport
{
}; // Fixture

//==============================================================================

class IdcFixture : public unittests::CarriageListWayTestSupport
{
protected:
    IdcFixture(const char* idcFileName)
    {
        const char* const programName{boost::unit_test::framework::master_test_suite().argv[0]};

        boost::filesystem::path path = boost::filesystem::system_complete(programName);
        path                         = path.parent_path();
        path.append(idcFileName, boost::filesystem::path::codecvt());
        m_is.open(path.c_str(), std::ifstream::in | std::ifstream::binary);
        if (m_is.fail())
        {
            BOOST_ERROR("Opening " << path << " failed, reason: " << std::strerror(errno) << "!");
        }
        m_is.seekg(276, m_is.beg); // skip empty scan and vehicle state
    }

protected:
    std::fstream m_is;
}; // IdcFixture

//==============================================================================

class Idc6970Fixture : public IdcFixture
{
public:
    Idc6970Fixture() : IdcFixture("carriageway6970_example.idc") {}
}; // Idc6970Fixture

//==============================================================================

class Idc6972Fixture : public IdcFixture
{
public:
    Idc6972Fixture() : IdcFixture("carriageway6972_example.idc") {}
}; // Idc6972Fixture

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isLaneSupportPointSelfEqual, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        LaneSupportPoint lsp{getLaneSupportPoint<LaneSupportPoint>()};

        BOOST_CHECK(lsp == lsp);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isLaneSegmentSelfEqual, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        LaneSegment::Ptr ls{createLaneSegment<LaneSegment::Ptr>()};

        BOOST_CHECK(LaneSegment::arePtrsEqualNonRecursive(ls, ls));
        BOOST_CHECK(LaneSegment::areEqualRecursive(*ls, *ls));
        BOOST_CHECK(LaneSegment::areEqualNonRecursive(*ls, *ls));
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isEmptyLaneSelfEqual, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Lane::Ptr lane{createEmptyLane<Lane::Ptr>()};

        BOOST_CHECK(Lane::arePtrsEqualNonRecursive(lane, lane));
        BOOST_CHECK(Lane::areEqualRecursive(*lane, *lane));
        BOOST_CHECK(Lane::areEqualNonRecursive(*lane, *lane));
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isLaneSelfEqual, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        Lane::Ptr lane{createLane<Lane::Ptr>()};

        BOOST_CHECK(Lane::arePtrsEqualNonRecursive(lane, lane));
        BOOST_CHECK(Lane::areEqualRecursive(*lane, *lane));
        BOOST_CHECK(Lane::areEqualNonRecursive(*lane, *lane));
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoEmptyCarriageWayListIdentity, Fixture)
{
    CarriageWayList cwl1;

    std::stringstream ss;
    CarriageWayListExporter6972 exporter;
    BOOST_CHECK(exporter.serialize(ss, cwl1));
    IbeoDataHeader dh(DataTypeId::DataType_CarriageWayList6972,
                      0,
                      static_cast<uint32_t>(exporter.getSerializedSize(cwl1)),
                      1,
                      NTPTime{});

    CarriageWayList cwl2;
    CarriageWayListImporter6972 importer;
    BOOST_CHECK(importer.deserialize(ss, cwl2, dh));

    BOOST_CHECK(exporter.getSerializedSize(cwl1) == exporter.getSerializedSize(cwl2));

    BOOST_CHECK(cwl1 == cwl2);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadCarriageWayIsOk, Idc6972Fixture)
{
    BOOST_REQUIRE(m_is.is_open());

    IbeoDataHeader dh;
    BOOST_REQUIRE(dh.deserialize(m_is));

    CarriageWayList cwl;
    CarriageWayListImporter6972 importer;
    BOOST_CHECK(importer.deserialize(m_is, cwl, dh));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoCarriageWayListIdentity, Idc6972Fixture)
{
    BOOST_REQUIRE(m_is.is_open());

    IbeoDataHeader dh;
    BOOST_REQUIRE(dh.deserialize(m_is));

    CarriageWayList cwl1;
    CarriageWayListImporter6972 importer;
    BOOST_CHECK(importer.deserialize(m_is, cwl1, dh));

    std::stringstream ss;
    CarriageWayListExporter6972 exporter;
    BOOST_CHECK(exporter.serialize(ss, cwl1));

    CarriageWayList cwl2;
    BOOST_CHECK(importer.deserialize(ss, cwl2, dh));

    BOOST_CHECK(importer.getSerializedSize(cwl1) == importer.getSerializedSize(cwl2));

    BOOST_CHECK(cwl1 == cwl2);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadCarriageWayIsOk6970, Idc6970Fixture)
{
    BOOST_REQUIRE(m_is.is_open());

    IbeoDataHeader dh;
    BOOST_REQUIRE(dh.deserialize(m_is));

    CarriageWayList cwl;
    CarriageWayListImporter6970 importer;
    BOOST_CHECK(importer.deserialize(m_is, cwl, dh));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoCarriageWayListIdentity6970, Idc6970Fixture)
{
    BOOST_REQUIRE(m_is.is_open());

    // 1. Import from 6970 container.
    IbeoDataHeader dh;
    BOOST_REQUIRE(dh.deserialize(m_is));

    CarriageWayList cwl1;
    CarriageWayListImporter6970 importer6970;
    BOOST_CHECK(importer6970.deserialize(m_is, cwl1, dh));

    // Check general data container members that could not be imported if they are initialized correctly.
    for (const auto& cwlIn : cwl1.getCarriageWays())
    {
        for (const auto& cwsme : cwlIn->getCwSegmentsMap())
        {
            for (const auto& lme : cwsme.second->getLanesMap())
            {
                for (const auto& lsme : lme.second->getLaneSegmentsMap())
                {
                    const LaneSegment::Ptr& laneSeg{lsme.second};

                    BOOST_CHECK_EQUAL(laneSeg->getMarkingWidthLeft(), 0.0F);
                    BOOST_CHECK_EQUAL(laneSeg->getMarkingWidthRight(), 0.0F);
                    BOOST_CHECK_EQUAL(laneSeg->getMedianDashLengthLeft(), 0.0F);
                    BOOST_CHECK_EQUAL(laneSeg->getMedianDashLengthRight(), 0.0F);
                    BOOST_CHECK_EQUAL(laneSeg->getMedianGapLengthLeft(), 0.0F);
                    BOOST_CHECK_EQUAL(laneSeg->getMedianGapLengthRight(), 0.0F);
                }
            }
        }
    }

    // 2. Export to 6972 container.
    std::stringstream ss;
    CarriageWayListExporter6972 exporter;
    BOOST_CHECK(exporter.serialize(ss, cwl1));

    // 3. Re-import from 6972 container.
    const IbeoDataHeader dh2(exporter.getDataType(), 0, uint32_t(exporter.getSerializedSize(cwl1)), 0, NTPTime());

    CarriageWayList cwl2;
    CarriageWayListImporter6972 importer6972;
    BOOST_CHECK(importer6972.deserialize(ss, cwl2, dh2));

    BOOST_CHECK(cwl1 == cwl2);
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

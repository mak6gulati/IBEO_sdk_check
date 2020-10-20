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
//!\date Mar 19, 2018
//------------------------------------------------------------------------------

#include "CarriageWayListTestSupport.hpp"
#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6970Exporter6970.hpp>
#include <ibeo/common/sdk/datablocks/carriageway/special/CarriageWayList6970Importer6970.hpp>

#define BOOST_TEST_MODULE CarriageWayList6970Tests
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
using namespace ibeo::common::sdk::lanes;
//==============================================================================

BOOST_AUTO_TEST_SUITE(CarriageWayList6970TestSuite)

//==============================================================================

class Fixture : public unittests::CarriageListWayTestSupport
{
}; // Fixture

class IdcFixture : public unittests::CarriageListWayTestSupport
{
public:
    IdcFixture()
    {
        const char* const programName{boost::unit_test::framework::master_test_suite().argv[0]};

        boost::filesystem::path path = boost::filesystem::system_complete(programName);
        path                         = path.parent_path();
        path.append("carriageway6970_example.idc", boost::filesystem::path::codecvt());
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

BOOST_FIXTURE_TEST_CASE(isLaneSupportPointSelfEqual, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        LaneSupportPointIn6970 lsp{getLaneSupportPoint<LaneSupportPointIn6970>()};

        BOOST_CHECK(lsp == lsp);
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isLaneSegmentSelfEqual, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        LaneSegmentIn6970::Ptr ls = createLaneSegment<LaneSegmentIn6970::Ptr>();

        BOOST_CHECK(LaneSegmentIn6970::arePtrsEqualNonRecursive(ls, ls));
        BOOST_CHECK(LaneSegmentIn6970::areEqualRecursive(*ls, *ls));
        BOOST_CHECK(LaneSegmentIn6970::areEqualNonRecursive(*ls, *ls));
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isEmptyLaneSelfEqual, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        LaneIn6970::Ptr lane = createEmptyLane<LaneIn6970::Ptr>();

        BOOST_CHECK(LaneIn6970::arePtrsEqualNonRecursive(lane, lane));
        BOOST_CHECK(LaneIn6970::areEqualRecursive(*lane, *lane));
        BOOST_CHECK(LaneIn6970::areEqualNonRecursive(*lane, *lane));
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isLaneSelfEqual, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        LaneIn6970::Ptr lane = createEmptyLane<LaneIn6970::Ptr>();

        BOOST_CHECK(LaneIn6970::arePtrsEqualNonRecursive(lane, lane));
        BOOST_CHECK(LaneIn6970::areEqualRecursive(*lane, *lane));
        BOOST_CHECK(LaneIn6970::areEqualNonRecursive(*lane, *lane));
    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isReadCarriageWayIsOk, IdcFixture)
{
    BOOST_REQUIRE(m_is.is_open());

    IbeoDataHeader dh;
    BOOST_REQUIRE(dh.deserialize(m_is));

    CarriageWayList6970 cwl;
    CarriageWayList6970Importer6970 importer;
    BOOST_CHECK(importer.deserialize(m_is, cwl, dh));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoEmptyCarriageWayList6970Identity, Fixture)
{
    CarriageWayList6970 cwl1;

    std::stringstream ss;
    CarriageWayList6970Exporter6970 exporter;
    BOOST_CHECK(exporter.serialize(ss, cwl1));
    IbeoDataHeader dh(DataTypeId::DataType_CarriageWayList6970,
                      0,
                      static_cast<uint32_t>(exporter.getSerializedSize(cwl1)),
                      1,
                      NTPTime{});

    CarriageWayList6970 cwl2;
    CarriageWayList6970Importer6970 importer;
    BOOST_CHECK(importer.deserialize(ss, cwl2, dh));

    BOOST_CHECK(exporter.getSerializedSize(cwl1) == exporter.getSerializedSize(cwl2));

    BOOST_CHECK(cwl1 == cwl2);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoCarriageWayList6970Identity, IdcFixture)
{
    BOOST_REQUIRE(m_is.is_open());

    IbeoDataHeader dh;
    BOOST_REQUIRE(dh.deserialize(m_is));

    CarriageWayList6970 cwl1;
    CarriageWayList6970Importer6970 importer;
    BOOST_CHECK(importer.deserialize(m_is, cwl1, dh));

    std::stringstream ss;
    CarriageWayList6970Exporter6970 exporter;
    BOOST_CHECK(exporter.serialize(ss, cwl1));

    CarriageWayList6970 cwl2;
    BOOST_CHECK(importer.deserialize(ss, cwl2, dh));

    BOOST_CHECK(importer.getSerializedSize(cwl1) == importer.getSerializedSize(cwl2));

    BOOST_CHECK(cwl1 == cwl2);
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

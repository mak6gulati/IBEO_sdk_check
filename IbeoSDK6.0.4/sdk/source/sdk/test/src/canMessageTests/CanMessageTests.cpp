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
//!\date 12.October 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include "CanMessageTestSupport.hpp"

#include <ibeo/common/sdk/datablocks/canmessage/CanMessageImporter1002.hpp>
#include <ibeo/common/sdk/datablocks/canmessage/CanMessageExporter1002.hpp>

#define BOOST_TEST_MODULE CanMessageTests
#include <boost/test/unit_test.hpp>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

BOOST_AUTO_TEST_SUITE(CanMessageTestSuite)

//==============================================================================

class Fixture : public unittests::CanMessageTestSupport
{
}; // Fixture

//==============================================================================

template<bool extId, bool ts>
class TestSetup
{
public:
    static const bool hasExtId{extId};
    static const bool hasTs{ts};
}; // TestSetup

//==============================================================================

using TestSetupCollection
    = boost::mpl::list<TestSetup<false, false>, TestSetup<false, true>, TestSetup<true, false>, TestSetup<true, true>>;

//==============================================================================

BOOST_FIXTURE_TEST_CASE(createCanMessage, Fixture)
{
    CanMessage cm;
    BOOST_CHECK(true);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(isIoCanMessageIdentity, TS, TestSetupCollection, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        const CanMessageExporter1002 exporter;
        CanMessage cmOrig(createCanMessage(TS::hasExtId, TS::hasTs));

        const IbeoDataHeader dh(
            exporter.getDataType(), 0U, uint32_t(exporter.getSerializedSize(cmOrig)), 0U, NTPTime());

        std::stringstream ss;
        BOOST_CHECK(exporter.serialize(ss, cmOrig));

        CanMessage cmCopy;
        const CanMessageImporter1002 importer;
        BOOST_CHECK(importer.deserialize(ss, cmCopy, dh));
        BOOST_CHECK(cmCopy == cmCopy);

    } // for r
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoCanMessageEquality, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        CanMessage cmCopy, cmOrig;
        BOOST_CHECK(cmCopy == cmOrig);

        cmOrig.setVersion(getDifferentRandValue<uint8_t>(CanMessage::maxVersion, cmOrig.getVersion()));
        BOOST_CHECK(cmCopy != cmOrig);
        cmCopy.setVersion(cmOrig.getVersion());
        BOOST_CHECK(cmCopy == cmOrig);

        cmOrig.setLength(
            getDifferentRandValue<uint8_t>(0, static_cast<uint8_t>(cmOrig.maxMsgSize), cmOrig.getLength()));
        BOOST_CHECK(cmCopy != cmOrig);
        cmCopy.setLength(cmOrig.getLength());
        BOOST_CHECK(cmCopy == cmOrig);

        for (uint8_t s = 0; s < cmOrig.getLength(); ++s)
        {
            cmOrig.setData(CanMessage::ByteNumber(s),
                           getDifferentRandValue<uint8_t>(cmOrig.getData(CanMessage::ByteNumber(s))));
        }

        BOOST_CHECK(cmCopy != cmOrig);
        for (uint8_t b = 0; b < cmCopy.getLength(); ++b)
        {
            cmCopy.setData(CanMessage::ByteNumber(b), cmOrig.getData(CanMessage::ByteNumber(b)));
        }
        BOOST_CHECK(cmCopy == cmOrig);

        cmOrig.setMsgType(static_cast<CanMessage::MsgType>(
            getDifferentRandValue<uint8_t>(0, 0xFF, static_cast<uint8_t>(cmOrig.getMsgType()))));
        BOOST_CHECK(cmCopy != cmOrig);
        cmCopy.setMsgType(cmOrig.getMsgType());
        BOOST_CHECK(cmCopy == cmOrig);

        if (cmOrig.hasExtendedCanId())
        {
            cmOrig.setCanId(
                getDifferentRandValue<uint32_t>(static_cast<uint32_t>(CanMessage::maxExtId), cmOrig.getCanId()));
        }
        else
        {
            cmOrig.setCanId(
                getDifferentRandValue<uint32_t>(static_cast<uint32_t>(CanMessage::maxStdId), cmOrig.getCanId()));
        }
        BOOST_CHECK(cmCopy != cmOrig);
        cmCopy.setCanId(cmOrig.getCanId());
        BOOST_CHECK(cmCopy == cmOrig);

        if (cmOrig.hasTimeStamp())
        {
            NTPTime tmpTime = cmOrig.getTimestamp();
            do
            {
                cmOrig.setTimestamp(getRandValue<NTPTime>());
            } while ((cmOrig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                     || (cmOrig.getTimestamp() == tmpTime));

            BOOST_CHECK(cmCopy != cmOrig);
            cmCopy.setTimestamp(cmOrig.getTimestamp());
            BOOST_CHECK(cmCopy == cmOrig);

            cmOrig.setUsSinceStartup(getDifferentRandValue<uint32_t>(cmOrig.getUsSinceStartup()));
            BOOST_CHECK(cmCopy != cmOrig);
            cmCopy.setUsSinceStartup(cmOrig.getUsSinceStartup());
            BOOST_CHECK(cmCopy == cmOrig);
        }

        cmOrig.setDeviceId(getDifferentRandValue<uint8_t>(cmOrig.getDeviceId()));
        BOOST_CHECK(cmCopy != cmOrig);
        cmCopy.setDeviceId(cmOrig.getDeviceId());
        BOOST_CHECK(cmCopy == cmOrig);
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(isIoCanMessageAssignment, Fixture)
{
    for (int32_t r = 0; r < nbOfRepeats; ++r)
    {
        CanMessage cmCopy, cmOrig, cmEmpty;
        BOOST_CHECK(cmCopy == cmOrig);
        BOOST_CHECK(cmEmpty == cmOrig);

        cmOrig.setVersion(getDifferentRandValue<uint8_t>(CanMessage::maxVersion, cmOrig.getVersion()));
        BOOST_CHECK(cmCopy != cmOrig);
        cmCopy = cmOrig;
        BOOST_CHECK(cmCopy == cmOrig);

        cmOrig.setLength(
            getDifferentRandValue<uint8_t>(0, static_cast<uint8_t>(cmOrig.maxMsgSize), cmOrig.getLength()));
        BOOST_CHECK(cmCopy != cmOrig);
        cmCopy = cmOrig;
        BOOST_CHECK(cmCopy == cmOrig);

        for (uint8_t s = 0; s < cmOrig.getLength(); ++s)
        {
            cmOrig.setData(CanMessage::ByteNumber(s),
                           getDifferentRandValue<uint8_t>(cmOrig.getData(CanMessage::ByteNumber(s))));
        }
        BOOST_CHECK(cmCopy != cmOrig);
        cmCopy = cmOrig;
        BOOST_CHECK(cmCopy == cmOrig);

        cmOrig.setMsgType(static_cast<CanMessage::MsgType>(
            getDifferentRandValue<uint8_t>(0, 0xFF, static_cast<uint8_t>(cmOrig.getMsgType()))));
        BOOST_CHECK(cmCopy != cmOrig);
        cmCopy = cmOrig;
        BOOST_CHECK(cmCopy == cmOrig);

        if (cmOrig.hasExtendedCanId())
        {
            cmOrig.setCanId(
                getDifferentRandValue<uint32_t>(static_cast<uint32_t>(CanMessage::maxExtId), cmOrig.getCanId()));
        }
        else
        {
            cmOrig.setCanId(
                getDifferentRandValue<uint32_t>(static_cast<uint32_t>(CanMessage::maxStdId), cmOrig.getCanId()));
        }
        BOOST_CHECK(cmCopy != cmOrig);
        cmCopy = cmOrig;
        BOOST_CHECK(cmCopy == cmOrig);

        if (cmOrig.hasTimeStamp())
        {
            NTPTime tmpTime = cmOrig.getTimestamp();
            do
            {
                cmOrig.setTimestamp(getRandValue<NTPTime>());
            } while ((cmOrig.getTimestamp().is_not_a_date_time() && tmpTime.is_not_a_date_time())
                     || (cmOrig.getTimestamp() == tmpTime));

            BOOST_CHECK(cmCopy != cmOrig);
            cmCopy = cmOrig;
            BOOST_CHECK(cmCopy == cmOrig);

            cmOrig.setUsSinceStartup(getDifferentRandValue<uint32_t>(cmOrig.getCanId()));
            BOOST_CHECK(cmCopy != cmOrig);
            cmCopy = cmOrig;
            BOOST_CHECK(cmCopy == cmOrig);
        }

        cmOrig.setDeviceId(getDifferentRandValue<uint8_t>(cmOrig.getDeviceId()));
        BOOST_CHECK(cmCopy != cmOrig);
        cmCopy = cmOrig;
        BOOST_CHECK(cmCopy == cmOrig);

        cmOrig = cmEmpty;
        BOOST_CHECK(cmOrig == cmEmpty);
        BOOST_CHECK(cmCopy != cmOrig);

        cmCopy = cmEmpty;
        BOOST_CHECK(cmCopy == cmEmpty);
        BOOST_CHECK(cmCopy == cmOrig);
    }
}

//==============================================================================

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

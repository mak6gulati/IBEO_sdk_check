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
//!\date Feb 22, 2018
//------------------------------------------------------------------------------

#include "Command2010TestSupport.hpp"

#include <set>

//==============================================================================
#define BOOST_TEST_MODULE Command2010Test
#include <boost/test/unit_test.hpp>

#include <sstream>

//==============================================================================
using namespace ibeo::common::sdk;
//==============================================================================

//==============================================================================
BOOST_AUTO_TEST_SUITE(Command2010TestsTestSuite)
//==============================================================================

//==============================================================================

class Fixture : public unittests::Command2010TestSupport
{
};

//==============================================================================

class IoFixture : public unittests::Command2010TestSupport
{
public:
    template<std::size_t N>
    void setStreamAndHeader1(const Arr<N>& arr)
    {
        m_ss1.write(reinterpret_cast<const char*>(arr.data()), N);
        m_dh1.setMessageSize(N);
    }

    template<std::size_t N>
    void setStreamAndHeader2(const Arr<N>& arr)
    {
        m_ss2.write(reinterpret_cast<const char*>(arr.data()), N);
        m_dh2.setMessageSize(N);
    }

    void resetStreamAndHeader1()
    {
        m_ss1.str("");
        m_ss1.clear();
    }
    void resetStreamAndHeader2()
    {
        m_ss2.str("");
        m_ss2.clear();
    }

protected:
    std::stringstream m_ss1;
    std::stringstream m_ss2;
}; // IoFixture

//==============================================================================

template<class S, std::size_t N>
class PreparedRawCommand
{
public:
    using SpecialCommand = S;
    static const IoFixture::Arr<N>& getRawCmd() { return IoFixture::getRawCmd<S, N>(); }
}; // PreparedRawCommand

PreparedRawCommand<CommandEcuSetFilterC, 4> a;

using PreparedRawCommandTypeList = boost::mpl::list<PreparedRawCommand<CommandEcuSetFilterC, 4>,
                                                    PreparedRawCommand<CommandEcuSetFilterC, 8>,
                                                    PreparedRawCommand<CommandEcuSetFilterC, 12>,
                                                    PreparedRawCommand<CommandEcuSetFilterC, 16>,
                                                    PreparedRawCommand<CommandEcuAppBaseCtrlC, 10>,
                                                    PreparedRawCommand<CommandEcuAppBaseStatusC, 4>,
                                                    PreparedRawCommand<CommandLuxResetC, 4>,
                                                    PreparedRawCommand<CommandLuxGetStatusC, 4>,
                                                    PreparedRawCommand<CommandLuxSaveConfigC, 4>,
                                                    PreparedRawCommand<CommandLuxSetParameterC, 10>,
                                                    PreparedRawCommand<CommandLuxGetParameterC, 6>,
                                                    PreparedRawCommand<CommandLuxResetToDefaultParametersC, 4>,
                                                    PreparedRawCommand<CommandLuxStartMeasureC, 4>,
                                                    PreparedRawCommand<CommandLuxStopMeasureC, 4>,
                                                    PreparedRawCommand<CommandLuxSetNtpTimestampSyncC, 14>>;

//==============================================================================

template<class S, CommandId::Id cmdId, class B, class I, class E>
class BaseSpecialCommand
{
public:
    using SpecialCommand = S;
    using CommandDevBase = B;
    using ImporterType   = I;
    using ExporterType   = E;
    static const CommandId::Id commandId{cmdId};
}; // BaseSpecialCommand

using BaseSpecialEcuCommandTypeList = boost::mpl::list<BaseSpecialCommand<CommandEcuSetFilterC,
                                                                          CommandId::Id::CmdManagerSetFilter,
                                                                          EcuCommandCBase,
                                                                          CommandEcuSetFilter2010Importer2010,
                                                                          CommandEcuSetFilter2010Exporter2010>,
                                                       BaseSpecialCommand<CommandEcuAppBaseCtrlC,
                                                                          CommandId::Id::CmdManagerAppBaseCtrl,
                                                                          EcuCommandCBase,
                                                                          CommandEcuAppBaseCtrl2010Importer2010,
                                                                          CommandEcuAppBaseCtrl2010Exporter2010>,
                                                       BaseSpecialCommand<CommandEcuAppBaseStatusC,
                                                                          CommandId::Id::CmdManagerAppBaseStatus,
                                                                          EcuCommandCBase,
                                                                          CommandEcuAppBaseStatus2010Importer2010,
                                                                          CommandEcuAppBaseStatus2010Exporter2010>>;

using BaseSpecialLuxCommandTypeList
    = boost::mpl::list<BaseSpecialCommand<CommandLuxResetC,
                                          CommandId::Id::CmdLuxReset,
                                          LuxCommandCBase,
                                          CommandLuxReset2010Importer2010,
                                          CommandLuxReset2010Exporter2010>,
                       BaseSpecialCommand<CommandLuxGetStatusC,
                                          CommandId::Id::CmdLuxGetStatus,
                                          LuxCommandCBase,
                                          CommandLuxGetStatus2010Importer2010,
                                          CommandLuxGetStatus2010Exporter2010>,
                       BaseSpecialCommand<CommandLuxSaveConfigC,
                                          CommandId::Id::CmdLuxSaveConfig,
                                          LuxCommandCBase,
                                          CommandLuxSaveConfig2010Importer2010,
                                          CommandLuxSaveConfig2010Exporter2010>,
                       BaseSpecialCommand<CommandLuxSetParameterC,
                                          CommandId::Id::CmdLuxSetParameter,
                                          LuxCommandCBase,
                                          CommandLuxSetParameter2010Importer2010,
                                          CommandLuxSetParameter2010Exporter2010>,
                       BaseSpecialCommand<CommandLuxGetParameterC,
                                          CommandId::Id::CmdLuxGetParameter,
                                          LuxCommandCBase,
                                          CommandLuxGetParameter2010Importer2010,
                                          CommandLuxGetParameter2010Exporter2010>,
                       BaseSpecialCommand<CommandLuxResetToDefaultParametersC,
                                          CommandId::Id::CmdLuxResetDefaultParameters,
                                          LuxCommandCBase,
                                          CommandLuxResetToDefaultParameters2010Importer2010,
                                          CommandLuxResetToDefaultParameters2010Exporter2010>,
                       BaseSpecialCommand<CommandLuxStartMeasureC,
                                          CommandId::Id::CmdLuxStartMeasure,
                                          LuxCommandCBase,
                                          CommandLuxStartMeasure2010Importer2010,
                                          CommandLuxStartMeasure2010Exporter2010>,
                       BaseSpecialCommand<CommandLuxStopMeasureC,
                                          CommandId::Id::CmdLuxStopMeasure,
                                          LuxCommandCBase,
                                          CommandLuxStopMeasure2010Importer2010,
                                          CommandLuxStopMeasure2010Exporter2010>,
                       BaseSpecialCommand<CommandLuxSetNtpTimestampSyncC,
                                          CommandId::Id::CmdLuxSetNTPTimestampSync,
                                          LuxCommandCBase,
                                          CommandLuxSetNtpTimestampSync2010Importer2010,
                                          CommandLuxSetNtpTimestampSync2010Exporter2010>>;

using BaseSpecialMiniLuxCommandTypeList
    = boost::mpl::list<BaseSpecialCommand<CommandMiniLuxResetC,
                                          CommandId::Id::CmdLuxReset,
                                          MiniLuxCommandCBase,
                                          CommandMiniLuxReset2010Importer2010,
                                          CommandMiniLuxReset2010Exporter2010>,
                       BaseSpecialCommand<CommandMiniLuxGetStatusC,
                                          CommandId::Id::CmdLuxGetStatus,
                                          MiniLuxCommandCBase,
                                          CommandMiniLuxGetStatus2010Importer2010,
                                          CommandMiniLuxGetStatus2010Exporter2010>,
                       BaseSpecialCommand<CommandMiniLuxSaveConfigC,
                                          CommandId::Id::CmdLuxSaveConfig,
                                          MiniLuxCommandCBase,
                                          CommandMiniLuxSaveConfig2010Importer2010,
                                          CommandMiniLuxSaveConfig2010Exporter2010>,
                       BaseSpecialCommand<CommandMiniLuxSetParameterC,
                                          CommandId::Id::CmdLuxSetParameter,
                                          MiniLuxCommandCBase,
                                          CommandMiniLuxSetParameter2010Importer2010,
                                          CommandMiniLuxSetParameter2010Exporter2010>,
                       BaseSpecialCommand<CommandMiniLuxGetParameterC,
                                          CommandId::Id::CmdLuxGetParameter,
                                          MiniLuxCommandCBase,
                                          CommandMiniLuxGetParameter2010Importer2010,
                                          CommandMiniLuxGetParameter2010Exporter2010>,
                       BaseSpecialCommand<CommandMiniLuxResetToDefaultParametersC,
                                          CommandId::Id::CmdLuxResetDefaultParameters,
                                          MiniLuxCommandCBase,
                                          CommandMiniLuxResetToDefaultParameters2010Importer2010,
                                          CommandMiniLuxResetToDefaultParameters2010Exporter2010>,
                       BaseSpecialCommand<CommandMiniLuxStartMeasureC,
                                          CommandId::Id::CmdLuxStartMeasure,
                                          MiniLuxCommandCBase,
                                          CommandMiniLuxStartMeasure2010Importer2010,
                                          CommandMiniLuxStartMeasure2010Exporter2010>,
                       BaseSpecialCommand<CommandMiniLuxStopMeasureC,
                                          CommandId::Id::CmdLuxStopMeasure,
                                          MiniLuxCommandCBase,
                                          CommandMiniLuxStopMeasure2010Importer2010,
                                          CommandMiniLuxStopMeasure2010Exporter2010>,
                       BaseSpecialCommand<CommandMiniLuxSetNtpTimestampSyncC,
                                          CommandId::Id::CmdLuxSetNTPTimestampSync,
                                          MiniLuxCommandCBase,
                                          CommandMiniLuxSetNtpTimestampSync2010Importer2010,
                                          CommandMiniLuxSetNtpTimestampSync2010Exporter2010>>;

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE(createCommand2010Works, Fixture) { Command2010 c; }

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(specialEcuContainerIsSelfEqualAndNotSelfInequal,
                                 BSC,
                                 BaseSpecialEcuCommandTypeList,
                                 Fixture)
{
    typename BSC::SpecialCommand s;
    BOOST_CHECK(s == s);
    BOOST_CHECK(!(s != s));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(specialLuxContainerIsSelfEqualAndNotSelfInequal,
                                 BSC,
                                 BaseSpecialLuxCommandTypeList,
                                 Fixture)
{
    typename BSC::SpecialCommand s;
    BOOST_CHECK(s == s);
    BOOST_CHECK(!(s != s));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(specialMiniLuxContainerIsSelfEqualAndNotSelfInequal,
                                 BSC,
                                 BaseSpecialMiniLuxCommandTypeList,
                                 Fixture)
{
    typename BSC::SpecialCommand s;
    BOOST_CHECK(s == s);
    BOOST_CHECK(!(s != s));
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(createSpecialEcuCommandWorks, BSC, BaseSpecialEcuCommandTypeList, Fixture)
{
    BOOST_CHECK(getSpecialCommand<typename BSC::CommandDevBase>(BSC::commandId) != nullptr);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(createSpecialLuxCommandWorks, BSC, BaseSpecialLuxCommandTypeList, Fixture)
{
    BOOST_CHECK(getSpecialCommand<typename BSC::CommandDevBase>(BSC::commandId) != nullptr);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(createSpecialMiniLuxCommandWorks, BSC, BaseSpecialMiniLuxCommandTypeList, Fixture)
{
    BOOST_CHECK(getSpecialCommand<typename BSC::CommandDevBase>(BSC::commandId) != nullptr);
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(createFilledSpecialEcuCommandWorks, BSC, BaseSpecialEcuCommandTypeList, Fixture)
{
    BOOST_CHECK(getFilledSpecialCommand<typename BSC::CommandDevBase>(BSC::commandId) != nullptr);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(createFilledSpecialLuxCommandWorks, BSC, BaseSpecialLuxCommandTypeList, Fixture)
{
    BOOST_CHECK(getFilledSpecialCommand<typename BSC::CommandDevBase>(BSC::commandId) != nullptr);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(createFilledSpecialMiniLuxCommandWorks,
                                 BSC,
                                 BaseSpecialMiniLuxCommandTypeList,
                                 Fixture)
{
    BOOST_CHECK(getFilledSpecialCommand<typename BSC::CommandDevBase>(BSC::commandId) != nullptr);
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(createSpecialLuxCommand2010AsEcuFails, BSC, BaseSpecialLuxCommandTypeList, Fixture)
{
    BOOST_CHECK(getSpecialCommand<EcuCommandCBase>(BSC::commandId) == nullptr);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(createSpecialMiniLuxCommand2010AsEcuFails,
                                 BSC,
                                 BaseSpecialMiniLuxCommandTypeList,
                                 Fixture)
{
    BOOST_CHECK(getSpecialCommand<EcuCommandCBase>(BSC::commandId) == nullptr);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(createSpecialEcuCommand2010AsLuxFails, BSC, BaseSpecialEcuCommandTypeList, Fixture)
{
    BOOST_CHECK(getSpecialCommand<LuxCommandCBase>(BSC::commandId) == nullptr);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(createSpecialEcuCommand2010AsMiniLuxFails, BSC, BaseSpecialEcuCommandTypeList, Fixture)
{
    BOOST_CHECK(getSpecialCommand<MiniLuxCommandCBase>(BSC::commandId) == nullptr);
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE(importEcuSetFilterWorks, IoFixture)
{
    CommandEcuSetFilterC s;
    CommandEcuSetFilter2010Importer2010 imp;
    setStreamAndHeader1(rawCmdEcuSetFilter0);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getNbOfRanges() == 0);

    setStreamAndHeader1(rawCmdEcuSetFilter1);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getNbOfRanges() == 1);
    BOOST_CHECK(s.getRanges()[0].first == DataTypeId{DataTypeId::DataType_Unknown});
    BOOST_CHECK(s.getRanges()[0].second == DataTypeId{DataTypeId::DataType_LastId});

    setStreamAndHeader1(rawCmdEcuSetFilter2);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getNbOfRanges() == 2);
    BOOST_CHECK(s.getRanges()[0].first == DataTypeId{DataTypeId::DataType_Scan2202});
    BOOST_CHECK(s.getRanges()[0].second == DataTypeId{DataTypeId::DataType_Scan2209});
    BOOST_CHECK(s.getRanges()[1].first == DataTypeId{DataTypeId::DataType_Scan2310});
    BOOST_CHECK(s.getRanges()[1].second == DataTypeId{DataTypeId::DataType_Scan2310});

    setStreamAndHeader1(rawCmdEcuSetFilter3);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getNbOfRanges() == 3);
    BOOST_CHECK(s.getRanges()[0].first == DataTypeId{DataTypeId::DataType_Scan2202});
    BOOST_CHECK(s.getRanges()[0].second == DataTypeId{DataTypeId::DataType_Scan2209});
    BOOST_CHECK(s.getRanges()[1].first == DataTypeId{DataTypeId::DataType_Scan2310});
    BOOST_CHECK(s.getRanges()[1].second == DataTypeId{DataTypeId::DataType_Scan2310});
    BOOST_CHECK(s.getRanges()[2].first == DataTypeId{DataTypeId::DataType_ObjectList2221});
    BOOST_CHECK(s.getRanges()[2].second == DataTypeId{DataTypeId::DataType_ObjectList2291});

    setStreamAndHeader2(rawCmdEcuAppBaseCtrl);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importEcuAppBaseCtrlWorks, IoFixture)
{
    CommandEcuAppBaseCtrlC s;
    CommandEcuAppBaseCtrl2010Importer2010 imp;
    setStreamAndHeader1(rawCmdEcuAppBaseCtrl);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getCtrlId() == CommandEcuAppBaseCtrlC::AppBaseCtrlId::StartRecording);

    setStreamAndHeader2(rawCmdEcuAppBaseStatus);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importEcuAppBaseStatusWorks, IoFixture)
{
    CommandEcuAppBaseStatusC s;
    CommandEcuAppBaseStatus2010Importer2010 imp;
    setStreamAndHeader1(rawCmdEcuAppBaseStatus);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getAppBaseStatusId() == CommandEcuAppBaseStatusC::AppBaseStatusId::Recording);

    setStreamAndHeader2(rawCmdLuxGetStatus);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE(importLuxResetWorks, IoFixture)
{
    CommandLuxResetC s;
    CommandLuxReset2010Importer2010 imp;
    setStreamAndHeader1(rawCmdReset);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdLuxGetStatus);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importLuxGetStatusWorks, IoFixture)
{
    CommandLuxGetStatusC s;
    CommandLuxGetStatus2010Importer2010 imp;
    setStreamAndHeader1(rawCmdLuxGetStatus);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdLuxSaveConfig);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importLuxSaveConfigWorks, IoFixture)
{
    CommandLuxSaveConfigC s;
    CommandLuxSaveConfig2010Importer2010 imp;
    setStreamAndHeader1(rawCmdLuxSaveConfig);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdLuxResetDefaultParameters);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importLuxSetParameterWorks, IoFixture)
{
    CommandLuxSetParameterC s;
    CommandLuxSetParameter2010Importer2010 imp;
    setStreamAndHeader1(rawCmdSetParameter);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getParameterIndex() == 0x1718);
    BOOST_CHECK(s.getParameterData() == 0x01020304);

    setStreamAndHeader2(rawCmdGetParameter);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importLuxGetParameterWorks, IoFixture)
{
    CommandLuxGetParameterC s;
    CommandLuxGetParameter2010Importer2010 imp;
    setStreamAndHeader1(rawCmdGetParameter);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getParameterIndex() == 0x1718);

    setStreamAndHeader2(rawCmdLuxResetDefaultParameters);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importLuxResetDefaultParametersWorks, IoFixture)
{
    CommandLuxResetToDefaultParametersC s;
    CommandLuxResetToDefaultParameters2010Importer2010 imp;
    setStreamAndHeader1(rawCmdLuxResetDefaultParameters);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdnLuxStartMeasure);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importLuxStartMesureWorks, IoFixture)
{
    CommandLuxStartMeasureC s;
    CommandLuxStartMeasure2010Importer2010 imp;
    setStreamAndHeader1(rawCmdnLuxStartMeasure);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdLuxStopMeasure);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importLuxStopMearureWorks, IoFixture)
{
    CommandLuxStopMeasureC s;
    CommandLuxStopMeasure2010Importer2010 imp;
    setStreamAndHeader1(rawCmdLuxStopMeasure);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdLuxSetNtpTimestampSync);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importLuxSetNtpTimestampSyncWorks, IoFixture)
{
    CommandLuxSetNtpTimestampSyncC s;
    CommandLuxSetNtpTimestampSync2010Importer2010 imp;
    setStreamAndHeader1(rawCmdLuxSetNtpTimestampSync);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getTimestamp().getSeconds() == 0x01020304);
    BOOST_CHECK(s.getTimestamp().getFracSeconds() == 0x0C0D0E0F);

    setStreamAndHeader2(rawCmdEcuSetFilter1);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE(importMiniLuxResetWorks, IoFixture)
{
    CommandMiniLuxResetC s;
    CommandMiniLuxReset2010Importer2010 imp;
    setStreamAndHeader1(rawCmdReset);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdLuxGetStatus);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importMiniLuxGetStatusWorks, IoFixture)
{
    CommandMiniLuxGetStatusC s;
    CommandMiniLuxGetStatus2010Importer2010 imp;
    setStreamAndHeader1(rawCmdLuxGetStatus);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdLuxSaveConfig);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importMiniLuxSaveConfigWorks, IoFixture)
{
    CommandMiniLuxSaveConfigC s;
    CommandMiniLuxSaveConfig2010Importer2010 imp;
    setStreamAndHeader1(rawCmdLuxSaveConfig);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdLuxResetDefaultParameters);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importMiniLuxSetParameterWorks, IoFixture)
{
    CommandMiniLuxSetParameterC s;
    CommandMiniLuxSetParameter2010Importer2010 imp;
    setStreamAndHeader1(rawCmdSetParameter);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getParameterIndex() == 0x1718);
    BOOST_CHECK(s.getParameterData() == 0x01020304);

    setStreamAndHeader2(rawCmdGetParameter);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importMiniLuxGetParameterWorks, IoFixture)
{
    CommandMiniLuxGetParameterC s;
    CommandMiniLuxGetParameter2010Importer2010 imp;
    setStreamAndHeader1(rawCmdGetParameter);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getParameterIndex() == 0x1718);

    setStreamAndHeader2(rawCmdLuxResetDefaultParameters);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importMiniLuxResetDefaultParametersWorks, IoFixture)
{
    CommandMiniLuxResetToDefaultParametersC s;
    CommandMiniLuxResetToDefaultParameters2010Importer2010 imp;
    setStreamAndHeader1(rawCmdLuxResetDefaultParameters);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdnLuxStartMeasure);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importMiniLuxStartMesureWorks, IoFixture)
{
    CommandMiniLuxStartMeasureC s;
    CommandMiniLuxStartMeasure2010Importer2010 imp;
    setStreamAndHeader1(rawCmdnLuxStartMeasure);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdLuxStopMeasure);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importMiniLuxStopMearureWorks, IoFixture)
{
    CommandMiniLuxStopMeasureC s;
    CommandMiniLuxStopMeasure2010Importer2010 imp;
    setStreamAndHeader1(rawCmdLuxStopMeasure);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));

    setStreamAndHeader2(rawCmdLuxSetNtpTimestampSync);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE(importMiniLuxSetNtpTimestampSyncWorks, IoFixture)
{
    CommandMiniLuxSetNtpTimestampSyncC s;
    CommandMiniLuxSetNtpTimestampSync2010Importer2010 imp;
    setStreamAndHeader1(rawCmdLuxSetNtpTimestampSync);
    BOOST_CHECK(imp.deserialize(m_ss1, s, m_dh1));
    BOOST_CHECK(s.getTimestamp().getSeconds() == 0x01020304);
    BOOST_CHECK(s.getTimestamp().getFracSeconds() == 0x0C0D0E0F);

    setStreamAndHeader2(rawCmdReset);
    BOOST_CHECK(!imp.deserialize(m_ss2, s, m_dh2));
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(importAsCmdWorks, PRC, PreparedRawCommandTypeList, IoFixture)
{
    Command2010 c;
    Command2010Importer2010 cImp;
    setStreamAndHeader1(PRC::getRawCmd());
    BOOST_CHECK(cImp.deserialize(m_ss1, c, m_dh1));
    BOOST_CHECK(!c.getSpecialCommand().empty());

    for (auto& p : c.getSpecialCommand())
    {
        BOOST_CHECK(p.second->getCommandId() == PRC::SpecialCommand::key);
    }
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE(allSpecialCommandHashesAreUnique, IoFixture)
{
    const std::unique_ptr<SpecialCommand2010TestSupport::OwningVector> allClasses{getAllSpecialCommands()};

    std::set<std::size_t> allHashes;
    int idx = 0;
    for (auto c : allClasses->getVector())
    {
        auto res = allHashes.insert(c->getClassIdHash());
        BOOST_CHECK_MESSAGE(res.second, "Hash " << c->getClassIdHash() << " appears twice. " << idx << "'s check.");
        ++idx;
    }

    BOOST_CHECK(allHashes.size() == 21);
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(baipCreatesOnlyOneInstanceOfImporterAndBufferEcu,
                                 BSC,
                                 BaseSpecialEcuCommandTypeList,
                                 IoFixture)
{
    Command2010Importer2010 cImp;
    BufferAndImporterProvider<CommandCBase>& baip = cImp.getBufferAndImporterProvider();
    const CommandId::Id cmdId                     = CommandId::Id(uint16_t(BSC::commandId));
    const uint64_t hash                           = BSC::SpecialCommand::getClassIdHashStatic();
    const CommandCBase::KeyType keyCBase          = cmdId;
    const SpecialImporterBase<CommandCBase>::ImporterRegisterId::Key keyImporter{std::make_pair(keyCBase, hash)};

    SpecialImporterBase<CommandCBase>* spImp = baip.getImporter(keyImporter);
    BOOST_CHECK(spImp != nullptr);
    CommandCBase* spCmd = baip.getBuffer(keyImporter);
    BOOST_CHECK(spCmd != nullptr);

    SpecialImporterBase<CommandCBase>* spImp2 = baip.getImporter(keyImporter);
    BOOST_CHECK(spImp2 == spImp);
    CommandCBase* spCmd2 = baip.getBuffer(keyImporter);
    BOOST_CHECK(spCmd2 == spCmd);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(baipCreatesOnlyOneInstanceOfImporterAndBufferLux,
                                 BSC,
                                 BaseSpecialLuxCommandTypeList,
                                 IoFixture)
{
    Command2010Importer2010 cImp;
    BufferAndImporterProvider<CommandCBase>& baip = cImp.getBufferAndImporterProvider();
    const CommandId::Id cmdId                     = CommandId::Id(uint16_t(BSC::commandId));
    const uint64_t hash                           = BSC::SpecialCommand::getClassIdHashStatic();
    const CommandCBase::KeyType keyCBase          = cmdId;
    const SpecialImporterBase<CommandCBase>::ImporterRegisterId::Key keyImporter{std::make_pair(keyCBase, hash)};

    SpecialImporterBase<CommandCBase>* spImp = baip.getImporter(keyImporter);
    BOOST_CHECK(spImp != nullptr);
    CommandCBase* spCmd = baip.getBuffer(keyImporter);
    BOOST_CHECK(spCmd != nullptr);

    SpecialImporterBase<CommandCBase>* spImp2 = baip.getImporter(keyImporter);
    BOOST_CHECK(spImp2 == spImp);
    CommandCBase* spCmd2 = baip.getBuffer(keyImporter);
    BOOST_CHECK(spCmd2 == spCmd);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(baipCreatesOnlyOneInstanceOfImporterAndBufferMiniLux,
                                 BSC,
                                 BaseSpecialMiniLuxCommandTypeList,
                                 IoFixture)
{
    Command2010Importer2010 cImp;
    BufferAndImporterProvider<CommandCBase>& baip = cImp.getBufferAndImporterProvider();
    const CommandId::Id cmdId                     = CommandId::Id(uint16_t(BSC::commandId));
    const uint64_t hash                           = BSC::SpecialCommand::getClassIdHashStatic();
    const CommandCBase::KeyType keyCBase          = cmdId;
    const SpecialImporterBase<CommandCBase>::ImporterRegisterId::Key keyImporter{std::make_pair(keyCBase, hash)};

    SpecialImporterBase<CommandCBase>* spImp = baip.getImporter(keyImporter);
    BOOST_REQUIRE(spImp != nullptr);
    CommandCBase* spCmd = baip.getBuffer(keyImporter);
    BOOST_REQUIRE(spCmd != nullptr);

    SpecialImporterBase<CommandCBase>* spImp2 = baip.getImporter(keyImporter);
    BOOST_REQUIRE(spImp2 == spImp);
    CommandCBase* spCmd2 = baip.getBuffer(keyImporter);
    BOOST_REQUIRE(spCmd2 == spCmd);
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(doesSerializedSizeOfImporterAndExporterAreEqualEcu,
                                 BSC,
                                 BaseSpecialEcuCommandTypeList,
                                 IoFixture)
{
    typename BSC::SpecialCommand s;
    typename BSC::ExporterType e;
    typename BSC::ImporterType i;

    uint32_t eSz{0};
    try
    {
        eSz = static_cast<uint32_t>(e.getSerializedSize(s));
    }
    catch (const ContainerMismatch&)
    {
        BOOST_FAIL("Exporter type is not matching SpecialCommand type.");
    }

    uint32_t iSz{0};
    try
    {
        iSz = static_cast<uint32_t>(i.getSerializedSize(s));
    }
    catch (const ContainerMismatch&)
    {
        BOOST_FAIL("Importer type is not matching SpecialCommand type.");
    }

    BOOST_REQUIRE(eSz == iSz);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(doesSerializedSizeOfImporterAndExporterAreEqualLux,
                                 BSC,
                                 BaseSpecialLuxCommandTypeList,
                                 IoFixture)
{
    typename BSC::SpecialCommand s;
    typename BSC::ExporterType e;
    typename BSC::ImporterType i;

    uint32_t eSz{0};
    try
    {
        eSz = static_cast<uint32_t>(e.getSerializedSize(s));
    }
    catch (const ContainerMismatch&)
    {
        BOOST_FAIL("Exporter type is not matching SpecialCommand type.");
    }

    uint32_t iSz{0};
    try
    {
        iSz = static_cast<uint32_t>(i.getSerializedSize(s));
    }
    catch (const ContainerMismatch&)
    {
        BOOST_FAIL("Importer type is not matching SpecialCommand type.");
    }

    BOOST_REQUIRE(eSz == iSz);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(doesSerializedSizeOfImporterAndExporterAreEqualMiniLux,
                                 BSC,
                                 BaseSpecialMiniLuxCommandTypeList,
                                 IoFixture)
{
    typename BSC::SpecialCommand s;
    typename BSC::ExporterType e;
    typename BSC::ImporterType i;

    uint32_t eSz{0};
    try
    {
        eSz = static_cast<uint32_t>(e.getSerializedSize(s));
    }
    catch (const ContainerMismatch&)
    {
        BOOST_FAIL("Exporter type is not matching SpecialCommand type.");
    }

    uint32_t iSz{0};
    try
    {
        iSz = static_cast<uint32_t>(i.getSerializedSize(s));
    }
    catch (const ContainerMismatch&)
    {
        BOOST_FAIL("Importer type is not matching SpecialCommand type.");
    }

    BOOST_REQUIRE(eSz == iSz);
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(isImportAfterExportIdentityEcu, BSC, BaseSpecialEcuCommandTypeList, IoFixture)
{
    typename BSC::SpecialCommand s1;
    typename BSC::ExporterType e;
    typename BSC::ImporterType i;

    const std::streamsize serSize = e.getSerializedSize(s1);

    BOOST_REQUIRE(e.serialize(m_ss1, s1));
    m_dh1.setMessageSize(static_cast<uint32_t>(serSize));

    typename BSC::SpecialCommand s2;
    BOOST_REQUIRE(i.deserialize(m_ss1, s2, m_dh1));
    BOOST_REQUIRE(i.getSerializedSize(s1) == i.getSerializedSize(s2));
    BOOST_REQUIRE(s1 == s2);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(isImportAfterExportIdentityLux, BSC, BaseSpecialLuxCommandTypeList, IoFixture)
{
    typename BSC::SpecialCommand s1;
    typename BSC::ExporterType e;
    typename BSC::ImporterType i;

    const std::streamsize serSize = e.getSerializedSize(s1);

    BOOST_REQUIRE(e.serialize(m_ss1, s1));
    m_dh1.setMessageSize(static_cast<uint32_t>(serSize));

    typename BSC::SpecialCommand s2;
    BOOST_REQUIRE(i.deserialize(m_ss1, s2, m_dh1));
    BOOST_REQUIRE(i.getSerializedSize(s1) == i.getSerializedSize(s2));
    BOOST_REQUIRE(s1 == s2);
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(isImportAfterExportIdentityMiniLux, BSC, BaseSpecialMiniLuxCommandTypeList, IoFixture)
{
    typename BSC::SpecialCommand s1;
    typename BSC::ExporterType e;
    typename BSC::ImporterType i;

    const std::streamsize serSize = e.getSerializedSize(s1);

    BOOST_REQUIRE(e.serialize(m_ss1, s1));
    m_dh1.setMessageSize(static_cast<uint32_t>(serSize));

    typename BSC::SpecialCommand s2;
    BOOST_REQUIRE(i.deserialize(m_ss1, s2, m_dh1));
    BOOST_REQUIRE(i.getSerializedSize(s1) == i.getSerializedSize(s2));
    BOOST_REQUIRE(s1 == s2);
}

//==============================================================================
//==============================================================================
//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(isImportAfterExportIdentityViaCommandEcu,
                                 BSC,
                                 BaseSpecialEcuCommandTypeList,
                                 IoFixture)
{
    using SpecialCommand = typename BSC::SpecialCommand;
    using ExporterType   = typename BSC::ExporterType;

    Command2010 c1;
    SpecialCommand s1;
    ExporterType se;

    try
    {
        c1.setSpecialCommand(s1, se);
    }
    catch (const ContainerMismatch&)
    {
        BOOST_FAIL("Exporter type is not matching SpecialCommand type.");
    }

    Command2010Exporter2010 e;
    BOOST_REQUIRE_MESSAGE(e.serialize(m_ss1, c1), "Serialization failed.");

    m_dh1.setMessageSize(static_cast<uint32_t>(e.getSerializedSize(c1)));

    Command2010 c2;
    Command2010Importer2010 i;
    BOOST_REQUIRE_MESSAGE(i.deserialize(m_ss1, c2, m_dh1), "Deserialization failed.");

    BOOST_REQUIRE(c1.getRawContent() == c2.getRawContent());

    const Command2010::SpecialCommandMap& scm = c2.getSpecialCommand();

    BOOST_REQUIRE_MESSAGE(!scm.empty(), "Deserialization did not store a special command in Command2010 container.");

    if (!scm.empty())
    {
        bool foundSerializedSpecialCommand{false};

        for (const auto& sc : scm)
        {
            const auto s = dynamic_cast<const SpecialCommand*>(sc.second);
            if (s)
            {
                foundSerializedSpecialCommand = true;
                BOOST_REQUIRE_MESSAGE(s1 == *s, "Original and serialized-deserailized SpecialCommands differ.");
            }
        }

        BOOST_REQUIRE_MESSAGE(foundSerializedSpecialCommand, "No SpecialCommand of expected type found.");
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(isImportAfterExportIdentityViaCommandLux,
                                 BSC,
                                 BaseSpecialLuxCommandTypeList,
                                 IoFixture)
{
    using SpecialCommand = typename BSC::SpecialCommand;
    using ExporterType   = typename BSC::ExporterType;

    Command2010 c1;
    SpecialCommand s1;
    ExporterType se;

    try
    {
        c1.setSpecialCommand(s1, se);
    }
    catch (const ContainerMismatch&)
    {
        BOOST_FAIL("Exporter type is not matching SpecialCommand type.");
    }

    Command2010Exporter2010 e;
    BOOST_REQUIRE_MESSAGE(e.serialize(m_ss1, c1), "Serialization failed.");

    m_dh1.setMessageSize(static_cast<uint32_t>(e.getSerializedSize(c1)));

    Command2010 c2;
    Command2010Importer2010 i;
    BOOST_REQUIRE_MESSAGE(i.deserialize(m_ss1, c2, m_dh1), "Deserialization failed.");

    BOOST_REQUIRE(c1.getRawContent() == c2.getRawContent());

    const Command2010::SpecialCommandMap& scm = c2.getSpecialCommand();

    BOOST_REQUIRE_MESSAGE(!scm.empty(), "Deserialization did not store a special command in Command2010 container.");

    if (!scm.empty())
    {
        bool foundSerializedSpecialCommand{false};

        for (const auto& sc : scm)
        {
            const auto s = dynamic_cast<const SpecialCommand*>(sc.second);
            if (s)
            {
                foundSerializedSpecialCommand = true;
                BOOST_REQUIRE_MESSAGE(s1 == *s, "Original and serialized-deserailized SpecialCommands differ.");
            }
        }

        BOOST_REQUIRE_MESSAGE(foundSerializedSpecialCommand, "No SpecialCommand of expected type found.");
    }
}

//==============================================================================

BOOST_FIXTURE_TEST_CASE_TEMPLATE(isImportAfterExportIdentityViaCommandMiniLux,
                                 BSC,
                                 BaseSpecialMiniLuxCommandTypeList,
                                 IoFixture)
{
    using SpecialCommand = typename BSC::SpecialCommand;
    using ExporterType   = typename BSC::ExporterType;

    Command2010 c1;
    SpecialCommand s1;
    ExporterType se;

    try
    {
        c1.setSpecialCommand(s1, se);
    }
    catch (const ContainerMismatch&)
    {
        BOOST_FAIL("Exporter type is not matching SpecialCommand type.");
    }

    Command2010Exporter2010 e;
    BOOST_REQUIRE_MESSAGE(e.serialize(m_ss1, c1), "Serialization failed.");

    m_dh1.setMessageSize(static_cast<uint32_t>(e.getSerializedSize(c1)));

    Command2010 c2;
    Command2010Importer2010 i;
    BOOST_REQUIRE_MESSAGE(i.deserialize(m_ss1, c2, m_dh1), "Deserialization failed.");

    BOOST_REQUIRE(c1.getRawContent() == c2.getRawContent());

    const Command2010::SpecialCommandMap& scm = c2.getSpecialCommand();

    BOOST_REQUIRE_MESSAGE(!scm.empty(), "Deserialization did not store a special command in Command2010 container.");

    if (!scm.empty())
    {
        bool foundSerializedSpecialCommand{false};

        for (const auto& sc : scm)
        {
            const auto s = dynamic_cast<const SpecialCommand*>(sc.second);
            if (s)
            {
                foundSerializedSpecialCommand = true;
                BOOST_REQUIRE_MESSAGE(s1 == *s, "Original and serialized-deserailized SpecialCommands differ.");
            }
        }

        BOOST_REQUIRE_MESSAGE(foundSerializedSpecialCommand, "No SpecialCommand of expected type found.");
    }
}

//==============================================================================
BOOST_AUTO_TEST_SUITE_END()
//==============================================================================

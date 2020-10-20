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

//==============================================================================

#include <command2010Tests/SpecialCommand2010TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/commands/ecucommands/ecucommands.hpp>
#include <ibeo/common/sdk/datablocks/commands/luxcommands/luxcommands.hpp>
#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/miniluxcommands.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

SpecialCommand2010TestSupport::OwningVector::~OwningVector()
{
    for (auto b : m_vec)
    {
        delete b;
    }
}

//==============================================================================

void SpecialCommand2010TestSupport::OwningVector::push_back(CommandCBase* const c) { m_vec.push_back(c); }

//==============================================================================

CommandCBase* SpecialCommand2010TestSupport ::OwningVector::operator[](const std::size_t idx) const
{
    return m_vec[idx];
}

//==============================================================================
//==============================================================================
//==============================================================================

const SpecialCommand2010TestSupport::Arr<4> SpecialCommand2010TestSupport ::rawCmdEcuSetFilter0{0x00, 0x05, 0x00, 0x00};

const SpecialCommand2010TestSupport::Arr<8>
    SpecialCommand2010TestSupport ::rawCmdEcuSetFilter1{0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0xFF, 0xFF};

const SpecialCommand2010TestSupport::Arr<12> SpecialCommand2010TestSupport::rawCmdEcuSetFilter2{0x00,
                                                                                                0x05,
                                                                                                0x00,
                                                                                                0x04,
                                                                                                0x22,
                                                                                                0x02,
                                                                                                0x22,
                                                                                                0x09,
                                                                                                0x23,
                                                                                                0x10,
                                                                                                0x23,
                                                                                                0x10};

const SpecialCommand2010TestSupport::Arr<16> SpecialCommand2010TestSupport::
    rawCmdEcuSetFilter3{0x00, 0x05, 0x00, 0x06, 0x22, 0x02, 0x22, 0x09, 0x23, 0x10, 0x23, 0x10, 0x22, 0x21, 0x22, 0x91};

const SpecialCommand2010TestSupport::Arr<10>
    SpecialCommand2010TestSupport::rawCmdEcuAppBaseCtrl{0x00, 0x0B, 0x00, 0x01, 'A', 'B', 'C', 'D', 'E', '\0'};

const SpecialCommand2010TestSupport::Arr<4> SpecialCommand2010TestSupport::rawCmdEcuAppBaseStatus{0x00,
                                                                                                  0x0C,
                                                                                                  0x00,
                                                                                                  0x01};

//==============================================================================

const SpecialCommand2010TestSupport::Arr<4> SpecialCommand2010TestSupport::rawCmdReset{0x00, 0x00, 0x00, 0x00};

const SpecialCommand2010TestSupport::Arr<4> SpecialCommand2010TestSupport::rawCmdLuxGetStatus{0x01, 0x00, 0x00, 0x00};

const SpecialCommand2010TestSupport::Arr<4> SpecialCommand2010TestSupport::rawCmdLuxSaveConfig{0x04, 0x00, 0x00, 0x00};

const SpecialCommand2010TestSupport::Arr<10>
    SpecialCommand2010TestSupport ::rawCmdSetParameter{0x10, 0x00, 0x00, 0x00, 0x18, 0x17, 0x04, 0x03, 0x02, 0x01};
const SpecialCommand2010TestSupport::Arr<6> SpecialCommand2010TestSupport ::rawCmdGetParameter{0x11,
                                                                                               0x00,
                                                                                               0x00,
                                                                                               0x00,
                                                                                               0x18,
                                                                                               0x17};

const SpecialCommand2010TestSupport::Arr<4> SpecialCommand2010TestSupport::rawCmdLuxResetDefaultParameters{0x1A,
                                                                                                           0x00,
                                                                                                           0x00,
                                                                                                           0x00};

const SpecialCommand2010TestSupport::Arr<4> SpecialCommand2010TestSupport::rawCmdnLuxStartMeasure{0x20,
                                                                                                  0x00,
                                                                                                  0x00,
                                                                                                  0x00};

const SpecialCommand2010TestSupport::Arr<4> SpecialCommand2010TestSupport::rawCmdLuxStopMeasure{0x21, 0x00, 0x00, 0x00};

const SpecialCommand2010TestSupport::Arr<14> SpecialCommand2010TestSupport ::
    rawCmdLuxSetNtpTimestampSync{0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x03, 0x02, 0x01, 0x0F, 0x0E, 0x0D, 0x0C};

//==============================================================================

SpecialCommand2010TestSupport::SpecialCommand2010TestSupport() {}

//==============================================================================

SpecialCommand2010TestSupport::~SpecialCommand2010TestSupport() {}

//==============================================================================

template<>
EcuCommandCBase* SpecialCommand2010TestSupport ::getSpecialCommand<EcuCommandCBase>(const CommandId::Id cmdId,
                                                                                    const bool fill)
{
    switch (cmdId)
    {
    case CommandId::Id::CmdManagerSetFilter:
        return registerSpecialCommand(new CommandEcuSetFilterC, fill);
    case CommandId::Id::CmdManagerAppBaseCtrl:
        return registerSpecialCommand(new CommandEcuAppBaseCtrlC, fill);
    case CommandId::Id::CmdManagerAppBaseStatus:
        return registerSpecialCommand(new CommandEcuAppBaseStatusC, fill);
    default:
        return nullptr;
    }
}

//==============================================================================

template<>
LuxCommandCBase* SpecialCommand2010TestSupport ::getSpecialCommand<LuxCommandCBase>(const CommandId::Id cmdId,
                                                                                    const bool fill)
{
    switch (cmdId)
    {
    case CommandId::Id::CmdLuxReset:
        return registerSpecialCommand(new CommandLuxResetC, fill);
    case CommandId::Id::CmdLuxGetStatus:
        return registerSpecialCommand(new CommandLuxGetStatusC, fill);
    case CommandId::Id::CmdLuxSaveConfig:
        return registerSpecialCommand(new CommandLuxSaveConfigC, fill);
    case CommandId::Id::CmdLuxSetParameter:
        return registerSpecialCommand(new CommandLuxSetParameterC, fill);
    case CommandId::Id::CmdLuxGetParameter:
        return registerSpecialCommand(new CommandLuxGetParameterC, fill);
    case CommandId::Id::CmdLuxResetDefaultParameters:
        return registerSpecialCommand(new CommandLuxResetToDefaultParametersC, fill);
    case CommandId::Id::CmdLuxStartMeasure:
        return registerSpecialCommand(new CommandLuxStartMeasureC, fill);
    case CommandId::Id::CmdLuxStopMeasure:
        return registerSpecialCommand(new CommandLuxStopMeasureC, fill);
    case CommandId::Id::CmdLuxSetNTPTimestampSync:
        return registerSpecialCommand(new CommandLuxSetNtpTimestampSyncC, fill);
    default:
        return nullptr;
    }
}

//==============================================================================

template<>
MiniLuxCommandCBase* SpecialCommand2010TestSupport ::getSpecialCommand<MiniLuxCommandCBase>(const CommandId::Id cmdId,
                                                                                            const bool fill)
{
    switch (cmdId)
    {
    case CommandId::Id::CmdLuxReset:
        return registerSpecialCommand(new CommandMiniLuxResetC, fill);
    case CommandId::Id::CmdLuxGetStatus:
        return registerSpecialCommand(new CommandMiniLuxGetStatusC, fill);
    case CommandId::Id::CmdLuxSaveConfig:
        return registerSpecialCommand(new CommandMiniLuxSaveConfigC, fill);
    case CommandId::Id::CmdLuxSetParameter:
        return registerSpecialCommand(new CommandMiniLuxSetParameterC, fill);
    case CommandId::Id::CmdLuxGetParameter:
        return registerSpecialCommand(new CommandMiniLuxGetParameterC, fill);
    case CommandId::Id::CmdLuxResetDefaultParameters:
        return registerSpecialCommand(new CommandMiniLuxResetToDefaultParametersC, fill);
    case CommandId::Id::CmdLuxStartMeasure:
        return registerSpecialCommand(new CommandMiniLuxStartMeasureC, fill);
    case CommandId::Id::CmdLuxStopMeasure:
        return registerSpecialCommand(new CommandMiniLuxStopMeasureC, fill);
    case CommandId::Id::CmdLuxSetNTPTimestampSync:
        return registerSpecialCommand(new CommandMiniLuxSetNtpTimestampSyncC, fill);
    default:
        return nullptr;
    }
}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandEcuSetFilterC* specialCommand)
{
    CommandEcuSetFilterC::RangeVector rv;

    const uint8_t nbOfRanges = getRandValue<uint8_t>(10);
    rv.reserve(nbOfRanges);
    for (uint_fast8_t r = 0; r < nbOfRanges; ++r)
    {
        const uint16_t rangeMin = getRandValue<uint16_t>();
        const uint16_t rangeMax = getRandValue<uint16_t>(rangeMin, 0xFFFF);
        rv.push_back(CommandEcuSetFilterC::Range(DataTypeId::DataType(rangeMin), DataTypeId::DataType(rangeMax)));
    }

    specialCommand->setRanges(rv);
}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandEcuAppBaseCtrlC* specialCommand)
{
    const CommandEcuAppBaseCtrlC::AppBaseCtrlId ctrlId{CommandEcuAppBaseCtrlC::AppBaseCtrlId(getRandValue<uint8_t>(2))};

    const uint16_t dataLen{getRandValue<uint16_t>()};
    std::string data(dataLen, ' ');
    for (auto& c : data)
    {
        c = char(getRandValue<uint8_t>(127) + 32);
    }

    specialCommand->setContent(ctrlId, data);
}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandEcuAppBaseStatusC* specialCommand)
{
    AppBaseStatusDefinitions::AppBaseStatusId s{AppBaseStatusDefinitions::AppBaseStatusId(getRandValue<uint16_t>())};
    specialCommand->setAppBaseStatusId(s);
}

//==============================================================================
//==============================================================================
//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxResetC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxGetStatusC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxSaveConfigC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxSetParameterC* specialCommand)
{
    specialCommand->setParameterIndex(ParameterIndex{getRandValue<uint16_t>()});
    specialCommand->setParameterData(ParameterData{getRandValue<uint16_t>()});
}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxGetParameterC* specialCommand)
{
    specialCommand->setParameterIndex(ParameterIndex{getRandValue<uint16_t>()});
}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxResetToDefaultParametersC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxStartMeasureC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxStopMeasureC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxSetNtpTimestampSyncC* specialCommand)
{
    specialCommand->setTimestamp(NTPTime{getRandValue<uint64_t>()});
}

//==============================================================================
//==============================================================================
//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxResetC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxGetStatusC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxSaveConfigC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxSetParameterC* specialCommand)
{
    specialCommand->setParameterIndex(ParameterIndex{getRandValue<uint16_t>()});
    specialCommand->setParameterData(ParameterData{getRandValue<uint16_t>()});
}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxGetParameterC* specialCommand)
{
    specialCommand->setParameterIndex(ParameterIndex{getRandValue<uint16_t>()});
}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxResetToDefaultParametersC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxStartMeasureC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxStopMeasureC*)
{}

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxSetNtpTimestampSyncC* specialCommand)
{
    specialCommand->setTimestamp(NTPTime{getRandValue<uint64_t>()});
}

//==============================================================================

std::unique_ptr<SpecialCommand2010TestSupport::OwningVector>
SpecialCommand2010TestSupport ::getAllSpecialCommands() const
{
    std::unique_ptr<OwningVector> vec{new OwningVector};
    vec->push_back(new CommandEcuAppBaseCtrlC);
    vec->push_back(new CommandEcuAppBaseStatusC);
    vec->push_back(new CommandEcuSetFilterC);

    vec->push_back(new CommandLuxGetParameterC);
    vec->push_back(new CommandLuxGetStatusC);
    vec->push_back(new CommandLuxResetC);
    vec->push_back(new CommandLuxResetToDefaultParametersC);
    vec->push_back(new CommandLuxSaveConfigC);
    vec->push_back(new CommandLuxSetNtpTimestampSyncC);
    vec->push_back(new CommandLuxSetParameterC);
    vec->push_back(new CommandLuxStartMeasureC);
    vec->push_back(new CommandLuxStopMeasureC);

    vec->push_back(new CommandMiniLuxGetParameterC);
    vec->push_back(new CommandMiniLuxGetStatusC);
    vec->push_back(new CommandMiniLuxResetC);
    vec->push_back(new CommandMiniLuxResetToDefaultParametersC);
    vec->push_back(new CommandMiniLuxSaveConfigC);
    vec->push_back(new CommandMiniLuxSetNtpTimestampSyncC);
    vec->push_back(new CommandMiniLuxSetParameterC);
    vec->push_back(new CommandMiniLuxStartMeasureC);
    vec->push_back(new CommandMiniLuxStopMeasureC);

    return vec;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/commands/Command2010.hpp>

#include <ibeo/common/sdk/datablocks/commands/ecucommands/ecucommands.hpp>
#include <ibeo/common/sdk/datablocks/commands/luxcommands/luxcommands.hpp>
#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/miniluxcommands.hpp>

#include <common/TestSupport.hpp>

#include <array>

#include <cstddef>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class SpecialCommand2010TestSupport : public TestSupport
{
public:
    template<std::size_t N>
    using Arr = std::array<uint8_t, N>;

    //========================================
    class OwningVector
    {
    public:
        ~OwningVector();

    public:
        const std::vector<CommandCBase*> getVector() const { return m_vec; }
        CommandCBase* operator[](const std::size_t idx) const;

    public:
        void push_back(CommandCBase* const c);

    private:
        std::vector<CommandCBase*> m_vec;
    }; // OwningVector

public:
    SpecialCommand2010TestSupport();
    virtual ~SpecialCommand2010TestSupport();

public:
    template<class DevComBase>
    DevComBase* getFilledSpecialCommand(const CommandId::Id cmdId);

    template<class DevComBase>
    DevComBase* getSpecialCommand(const CommandId::Id cmdId);

    template<class S>
    void fillSpecialCommand(S* specialCommand);

    template<class T, std::size_t N>
    static const Arr<N>& getRawCmd();

public:
    std::unique_ptr<OwningVector> getAllSpecialCommands() const;

protected:
    template<class DevComBase>
    DevComBase* getSpecialCommand(const CommandId::Id cmdId, const bool fill);

    template<class S>
    S* registerSpecialCommand(S* const sp, const bool fill);

protected:
    // ecu set filter // 0x05
    // ecu appbase ctrl // 0x0B
    // ecu appbase status // 0x0C

    static const Arr<4> rawCmdEcuSetFilter0;
    static const Arr<8> rawCmdEcuSetFilter1;
    static const Arr<12> rawCmdEcuSetFilter2;
    static const Arr<16> rawCmdEcuSetFilter3;

    static const Arr<10> rawCmdEcuAppBaseCtrl;
    static const Arr<4> rawCmdEcuAppBaseStatus;

    static const Arr<4> rawCmdReset;
    static const Arr<4> rawCmdLuxGetStatus;
    static const Arr<4> rawCmdLuxSaveConfig;
    static const Arr<10> rawCmdSetParameter;
    static const Arr<6> rawCmdGetParameter;
    static const Arr<4> rawCmdLuxResetDefaultParameters;
    static const Arr<4> rawCmdnLuxStartMeasure;
    static const Arr<4> rawCmdLuxStopMeasure;
    static const Arr<14> rawCmdLuxSetNtpTimestampSync;

protected:
    IbeoDataHeader m_dh1{DataTypeId::DataType_Command2010, 0, 4, 0, NTPTime{}};
    IbeoDataHeader m_dh2{DataTypeId::DataType_Command2010, 0, 4, 0, NTPTime{}};

protected:
    OwningVector m_createdSpecialCommands;
}; // SpecialCommand2010TestSupport

//==============================================================================

using SCS = SpecialCommand2010TestSupport;

template<>
inline const SCS::Arr<4>& SCS::getRawCmd<CommandEcuSetFilterC>()
{
    return rawCmdEcuSetFilter0;
}
template<>
inline const SCS::Arr<8>& SCS::getRawCmd<CommandEcuSetFilterC>()
{
    return rawCmdEcuSetFilter1;
}

template<>
inline const SCS::Arr<12>& SCS::getRawCmd<CommandEcuSetFilterC>()
{
    return rawCmdEcuSetFilter2;
}

template<>
inline const SCS::Arr<16>& SCS::getRawCmd<CommandEcuSetFilterC>()
{
    return rawCmdEcuSetFilter3;
}

template<>
inline const SCS::Arr<10>& SCS::getRawCmd<CommandEcuAppBaseCtrlC>()
{
    return rawCmdEcuAppBaseCtrl;
}

template<>
inline const SCS::Arr<4>& SCS::getRawCmd<CommandEcuAppBaseStatusC>()
{
    return rawCmdEcuAppBaseStatus;
}

template<>
inline const SCS::Arr<4>& SCS::getRawCmd<CommandLuxResetC>()
{
    return rawCmdReset;
}

template<>
inline const SCS::Arr<4>& SCS::getRawCmd<CommandLuxGetStatusC>()
{
    return rawCmdLuxGetStatus;
}

template<>
inline const SCS::Arr<4>& SCS::getRawCmd<CommandLuxSaveConfigC>()
{
    return rawCmdLuxSaveConfig;
}

template<>
inline const SCS::Arr<10>& SCS::getRawCmd<CommandLuxSetParameterC>()
{
    return rawCmdSetParameter;
}

template<>
inline const SCS::Arr<6>& SCS::getRawCmd<CommandLuxGetParameterC>()
{
    return rawCmdGetParameter;
}

template<>
inline const SCS::Arr<4>& SCS::getRawCmd<CommandLuxResetToDefaultParametersC>()
{
    return rawCmdLuxResetDefaultParameters;
}

template<>
inline const SCS::Arr<4>& SCS::getRawCmd<CommandLuxStartMeasureC>()
{
    return rawCmdnLuxStartMeasure;
}

template<>
inline const SCS::Arr<4>& SCS::getRawCmd<CommandLuxStopMeasureC>()
{
    return rawCmdLuxStopMeasure;
}

template<>
inline const SCS::Arr<14>& SCS::getRawCmd<CommandLuxSetNtpTimestampSyncC>()
{
    return rawCmdLuxSetNtpTimestampSync;
}

//==============================================================================

template<class DevComBase>
DevComBase* SpecialCommand2010TestSupport::getFilledSpecialCommand(const CommandId::Id cmdId)
{
    DevComBase* const b = getSpecialCommand<DevComBase>(cmdId, true);
    if ((!b) || (b->getCommandId() != cmdId))
    {
        return nullptr;
    }
    return b;
}

//==============================================================================

template<class DevComBase>
DevComBase* SpecialCommand2010TestSupport::getSpecialCommand(const CommandId::Id cmdId)
{
    DevComBase* const b = getSpecialCommand<DevComBase>(cmdId, false);
    if ((!b) || (b->getCommandId() != cmdId))
    {
        return nullptr;
    }
    return b;
}

//==============================================================================

template<>
EcuCommandCBase* SpecialCommand2010TestSupport ::getSpecialCommand<EcuCommandCBase>(const CommandId::Id cmdId,
                                                                                    const bool fill);

template<>
LuxCommandCBase* SpecialCommand2010TestSupport ::getSpecialCommand<LuxCommandCBase>(const CommandId::Id cmdId,
                                                                                    const bool fill);

template<>
MiniLuxCommandCBase* SpecialCommand2010TestSupport ::getSpecialCommand<MiniLuxCommandCBase>(const CommandId::Id cmdId,
                                                                                            const bool fill);

//==============================================================================

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandEcuSetFilterC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandEcuAppBaseCtrlC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandEcuAppBaseStatusC* specialCommand);

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxResetC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxGetStatusC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxSaveConfigC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxSetParameterC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxGetParameterC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxResetToDefaultParametersC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxStartMeasureC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxStopMeasureC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandLuxSetNtpTimestampSyncC* specialCommand);

template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxResetC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxGetStatusC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxSaveConfigC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxSetParameterC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxGetParameterC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxResetToDefaultParametersC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxStartMeasureC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxStopMeasureC* specialCommand);
template<>
void SpecialCommand2010TestSupport::fillSpecialCommand(CommandMiniLuxSetNtpTimestampSyncC* specialCommand);

//==============================================================================

template<class SpCmd>
SpCmd* SpecialCommand2010TestSupport::registerSpecialCommand(SpCmd* const sp, const bool fill)
{
    CommandCBase* const b = &dynamic_cast<CommandCBase&>(*sp);
    m_createdSpecialCommands.push_back(b);

    if (fill)
    {
        fillSpecialCommand(sp);
    }
    return sp;
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

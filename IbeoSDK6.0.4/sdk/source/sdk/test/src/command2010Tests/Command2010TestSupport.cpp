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

#include <command2010Tests/Command2010TestSupport.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

Command2010TestSupport::Command2010TestSupport() { fillCommandVectors(); }

//==============================================================================

Command2010TestSupport::~Command2010TestSupport() {}

//==============================================================================

void Command2010TestSupport::fillRandomly(Command2010&) const
{
    //todo: implement
}

//==============================================================================

CommandId Command2010TestSupport::getRandomCommandId(const CommandIdVector& cv) const
{
    if (cv.empty())
    {
        throw;
    }
    const uint16_t cmdIdx = getRandValue<uint16_t>(uint16_t(cv.size() - 1));
    return cv[cmdIdx];
}

//==============================================================================

void Command2010TestSupport::fillCommandVectors()
{
    ecuCommands.push_back(CommandId::Id::CmdManagerSetFilter);
    ecuCommands.push_back(CommandId::Id::CmdManagerAppBaseCtrl);
    ecuCommands.push_back(CommandId::Id::CmdManagerAppBaseStatus);

    luxCommands.push_back(swapOrder(CommandId::Id::CmdLuxReset));
    luxCommands.push_back(swapOrder(CommandId::Id::CmdLuxGetStatus));
    luxCommands.push_back(swapOrder(CommandId::Id::CmdLuxSaveConfig));
    luxCommands.push_back(swapOrder(CommandId::Id::CmdLuxSetParameter));
    luxCommands.push_back(swapOrder(CommandId::Id::CmdLuxGetParameter));
    luxCommands.push_back(swapOrder(CommandId::Id::CmdLuxResetDefaultParameters));
    luxCommands.push_back(swapOrder(CommandId::Id::CmdLuxStartMeasure));
    luxCommands.push_back(swapOrder(CommandId::Id::CmdLuxStopMeasure));
    luxCommands.push_back(swapOrder(CommandId::Id::CmdLuxSetNTPTimestampSync));

    miniluxCommands = luxCommands;

    allCommands = ecuCommands;
    allCommands.insert(allCommands.end(), luxCommands.begin(), luxCommands.end());
}

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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
//!\date Feb 19, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/CommandId.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

std::ostream& operator<<(std::ostream& os, const CommandId& cmdId)
{
    const uint16_t c = uint16_t(cmdId);

    switch (CommandId::Id(c))
    {
    case CommandId::Id::CmdManagerSetFilter:
        os << "CmdManagerSetFilter";
        break;
    case CommandId::Id::CmdManagerAppBaseCtrl:
        os << "CmdManagerAppBaseCtrl";
        break;
    case CommandId::Id::CmdManagerAppBaseStatus:
        os << "CmdManagerAppBaseStatus";
        break;

    case CommandId::Id::CmdLuxReset:
        os << "CmdLuxReset";
        break;
    case CommandId::Id::CmdLuxGetStatus:
        os << "CmdLuxGetStatus";
        break;
    case CommandId::Id::CmdLuxSaveConfig:
        os << "CmdLuxSaveConfig";
        break;
    case CommandId::Id::CmdLuxSetParameter:
        os << "CmdLuxSetParameter";
        break;
    case CommandId::Id::CmdLuxGetParameter:
        os << "CmdLuxGetParameter";
        break;
    case CommandId::Id::CmdLuxResetDefaultParameters:
        os << "CmdLuxResetDefaultParameters";
        break;
    case CommandId::Id::CmdLuxStartMeasure:
        os << "CmdLuxStartMeasure";
        break;
    case CommandId::Id::CmdLuxStopMeasure:
        os << "CmdLuxStopMeasure";
        break;
    case CommandId::Id::CmdLuxSetNTPTimestampSync:
        os << "CmdLuxSetNTPTimestampSync";
        break;
    default:
        os << int(cmdId);
        break;
    } // switch cmdId
    return os;
}

//==============================================================================

std::ostream& operator<<(std::ostream& os, const CommandId::Id& cmdId)
{
    os << CommandId(cmdId);
    return os;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

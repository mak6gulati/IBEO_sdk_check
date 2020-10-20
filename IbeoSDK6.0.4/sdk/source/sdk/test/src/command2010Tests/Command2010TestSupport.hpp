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

#include <command2010Tests/SpecialCommand2010TestSupport.hpp>

#include <ibeo/common/sdk/datablocks/commands/Command2010Exporter2010.hpp>
#include <ibeo/common/sdk/datablocks/commands/Command2010Importer2010.hpp>

#include <vector>
#include <type_traits>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
namespace unittests {
//==============================================================================

class Command2010TestSupport : public SpecialCommand2010TestSupport
{
public:
    using CommandIdVector = std::vector<CommandId::Id>;

public:
    static CommandId::Id swapOrder(const CommandId::Id commandIn)
    {
        using UET          = std::underlying_type<CommandId::Id>::type;
        const uint16_t in  = static_cast<UET>(commandIn);
        const uint16_t out = uint16_t(((in & 0xFF) << 8) & (in >> 8));
        return CommandId::Id(out);
    }

public:
    Command2010TestSupport();
    virtual ~Command2010TestSupport();

public:
    void fillRandomly(Command2010& c) const;

public:
    CommandId getRandomEcuCommandId() const { return getRandomCommandId(ecuCommands); }
    CommandId getRandomLuxCommandId() const { return getRandomCommandId(luxCommands); }
    CommandId getRandomMiniLuxCommandId() const { return getRandomCommandId(miniluxCommands); }
    CommandId getRandomCommandId() const { return getRandomCommandId(allCommands); }

protected:
    void fillCommandVectors();
    CommandId getRandomCommandId(const CommandIdVector& cv) const;

protected:
    CommandIdVector ecuCommands;
    CommandIdVector luxCommands;
    CommandIdVector miniluxCommands;
    CommandIdVector allCommands;
}; // Command2010TestSupport

//==============================================================================
} // namespace unittests
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

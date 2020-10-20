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

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/commands/miniluxcommands/MiniLuxCommandC.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class CommandMiniLuxSaveConfigC : public MiniLuxCommandC<CommandId::Id::CmdLuxSaveConfig>
{
    template<class ContainerType, DataTypeId::DataType id, class SpecialCommand>
    friend class SpecialImporter;
    template<class SpecialCommand>
    friend class EmptyCommandExporter;

public:
    //========================================
    //! \brief Length of the SetFilter command.
    //-------------------------------------
    constexpr static const KeyType key{CommandId::Id::CmdLuxSaveConfig};
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.command2010.commandminiluxsaveconfig"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    CommandMiniLuxSaveConfigC() : MiniLuxCommandC<CommandId::Id::CmdLuxSaveConfig>() {}

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    uint16_t getReserved() const { return m_reserved; }

protected:
    uint16_t m_reserved{0x0000U};
}; // CommandMiniLuxSaveConfigC

//==============================================================================
//==============================================================================
//==============================================================================

inline bool operator==(const CommandMiniLuxSaveConfigC& lhs, const CommandMiniLuxSaveConfigC& rhs)
{
    return static_cast<const CommandCBase&>(lhs) == static_cast<const CommandCBase&>(rhs)
           && lhs.getReserved() == rhs.getReserved();
}

//==============================================================================

inline bool operator!=(const CommandMiniLuxSaveConfigC& lhs, const CommandMiniLuxSaveConfigC& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

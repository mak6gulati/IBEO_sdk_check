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
//!\date Feb 16, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/commands/ecucommands/EcuCommandC.hpp>
#include <ibeo/common/sdk/datablocks/commands/ecucommands/AppBaseStatusDefinitions.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class CommandEcuAppBaseStatusC : public EcuCommandC<CommandId::Id::CmdManagerAppBaseStatus>,
                                 public AppBaseStatusDefinitions
{
    template<class ContainerType, DataTypeId::DataType id, class SpecialCommand>
    friend class SpecialImporter;
    template<class SpecialCommand>
    friend class SpecialExporter;

public:
    //========================================
    //! \brief Length of the SetFilter command.
    //-------------------------------------
    constexpr static const KeyType key{CommandId::Id::CmdManagerAppBaseStatus};
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.command.commandecuappbasestatus"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    CommandEcuAppBaseStatusC()
      : EcuCommandC<CommandId::Id::CmdManagerAppBaseStatus>(),
        AppBaseStatusDefinitions(),
        m_statusId{AppBaseStatusId::Recording}
    {}

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    AppBaseStatusId getAppBaseStatusId() const { return m_statusId; }

public:
    void setAppBaseStatusId(const AppBaseStatusId sId) { m_statusId = sId; }

protected:
    AppBaseStatusId m_statusId;
}; // CommandEcuAppBaseStatusC

//==============================================================================
//==============================================================================
//==============================================================================

inline bool operator==(const CommandEcuAppBaseStatusC& lhs, const CommandEcuAppBaseStatusC& rhs)
{
    return static_cast<const CommandCBase&>(lhs) == static_cast<const CommandCBase&>(rhs)
           && lhs.getAppBaseStatusId() == rhs.getAppBaseStatusId();
}

//==============================================================================

inline bool operator!=(const CommandEcuAppBaseStatusC& lhs, const CommandEcuAppBaseStatusC& rhs)
{
    return static_cast<const CommandCBase&>(lhs) != static_cast<const CommandCBase&>(rhs)
           || lhs.getAppBaseStatusId() != rhs.getAppBaseStatusId();
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

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

#include <ibeo/common/sdk/datablocks/commands/luxcommands/LuxCommandC.hpp>
#include <ibeo/common/sdk/misc/ParameterData.hpp>
#include <ibeo/common/sdk/misc/ParameterIndex.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class CommandLuxSetParameterC : public LuxCommandC<CommandId::Id::CmdLuxSetParameter>
{
    template<class ContainerType, DataTypeId::DataType id, class SpecialCommand>
    friend class SpecialImporter;
    template<class SpecialCommand>
    friend class SpecialExporter;

public:
    //========================================
    //! \brief Length of the SetFilter command.
    //-------------------------------------
    constexpr static const KeyType key{CommandId::Id::CmdLuxSetParameter};
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.command2010.commandluxsetparameter"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    CommandLuxSetParameterC() : CommandLuxSetParameterC(ParameterIndex{0x0000U}, ParameterData{0xFFFFFFFFU}) {}
    CommandLuxSetParameterC(const ParameterIndex parameterIndex, const ParameterData parameterData)
      : LuxCommandC<CommandId::Id::CmdLuxSetParameter>(),
        m_parameterIndex(parameterIndex),
        m_parameterData(parameterData)
    {}

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    uint16_t getReserved() const { return m_reserved; }
    ParameterIndex getParameterIndex() const { return m_parameterIndex; }
    ParameterData getParameterData() const { return m_parameterData; }

public:
    void setParameterIndex(const ParameterIndex idx) { m_parameterIndex = idx; }
    void setParameterData(const ParameterData data) { m_parameterData = data; }

protected:
    uint16_t m_reserved{0x0000U};
    ParameterIndex m_parameterIndex;
    ParameterData m_parameterData;
}; // CommandLuxSetParameterC

//==============================================================================
//==============================================================================
//==============================================================================

inline bool operator==(const CommandLuxSetParameterC& lhs, const CommandLuxSetParameterC& rhs)
{
    return static_cast<const CommandCBase&>(lhs) == static_cast<const CommandCBase&>(rhs)
           && lhs.getReserved() == rhs.getReserved() && lhs.getParameterIndex() == rhs.getParameterIndex()
           && lhs.getParameterData() == rhs.getParameterData();
}

//==============================================================================

inline bool operator!=(const CommandLuxSetParameterC& lhs, const CommandLuxSetParameterC& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

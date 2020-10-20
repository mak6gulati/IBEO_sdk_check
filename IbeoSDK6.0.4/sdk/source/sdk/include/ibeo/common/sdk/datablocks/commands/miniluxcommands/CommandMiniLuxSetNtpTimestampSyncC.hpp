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

class CommandMiniLuxSetNtpTimestampSyncC : public MiniLuxCommandC<CommandId::Id::CmdLuxSetNTPTimestampSync>
{
    template<class ContainerType, DataTypeId::DataType id, class SpecialCommand>
    friend class SpecialImporter;
    template<class SpecialCommand>
    friend class SpecialExporter;

public:
    //========================================
    //! \brief Length of the SetFilter command.
    //-------------------------------------
    constexpr static const KeyType key{CommandId::Id::CmdLuxSetNTPTimestampSync};
    constexpr static const char* const containerType{
        "ibeo.sdk.specialcontainer.command2010.commandminiluxsetntptimestampsync"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    CommandMiniLuxSetNtpTimestampSyncC() : CommandMiniLuxSetNtpTimestampSyncC(NTPTime{0}) {}

    CommandMiniLuxSetNtpTimestampSyncC(const NTPTime timestamp)
      : MiniLuxCommandC<CommandId::Id::CmdLuxSetNTPTimestampSync>(), m_timestamp(timestamp)
    {}

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    uint16_t getReserved0() const { return m_reserved0; }
    uint16_t getReserved1() const { return m_reserved1; }
    NTPTime getTimestamp() const { return m_timestamp; }

public:
    void setTimestamp(const NTPTime timestamp) { m_timestamp = timestamp; }

protected:
    uint16_t m_reserved0{0x0000U};
    uint16_t m_reserved1{0x0000U};
    NTPTime m_timestamp;
}; // CommandMiniLuxSetNtpTimestampSyncC

//==============================================================================
//==============================================================================
//==============================================================================

inline bool operator==(const CommandMiniLuxSetNtpTimestampSyncC& lhs, const CommandMiniLuxSetNtpTimestampSyncC& rhs)
{
    return static_cast<const CommandCBase&>(lhs) == static_cast<const CommandCBase&>(rhs)
           && lhs.getReserved0() == rhs.getReserved0() && lhs.getReserved1() == rhs.getReserved1()
           && lhs.getReserved0() == rhs.getTimestamp();
}

//==============================================================================

inline bool operator!=(const CommandMiniLuxSetNtpTimestampSyncC& lhs, const CommandMiniLuxSetNtpTimestampSyncC& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

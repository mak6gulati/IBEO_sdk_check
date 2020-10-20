//==============================================================================
//! \file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 12, 2015
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/misc/Unconvertable.hpp>
#include <ibeo/common/sdk/misc/ToHex.hpp>

#include <ibeo/common/sdk/io.hpp>
#include <ibeo/common/sdk/bufferIO.hpp>

#include <boost/functional/hash.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class CommandId : public ibeo::common::sdk::ComparableUnconvertable<uint16_t>
{
public:
    enum class Id : uint16_t
    {
        // ECU commands
        CmdManagerSetFilter     = 0x0005, ///< Sets the data type filter, EMPTY REPLY
        CmdManagerAppBaseCtrl   = 0x000B, //!< EMPTY REPLY
        CmdManagerAppBaseStatus = 0x000C, //!<

        // LUX3 commands
        CmdLuxReset                  = 0x0000, //!< ID of the Reset command, NO REPLY!
        CmdLuxGetStatus              = 0x0001, //!< ID of the GetStatus command
        CmdLuxSaveConfig             = 0x0004, //!< ID of the SaveConfig command, EMPTY REPLY!
        CmdLuxSetParameter           = 0x0010, //!< sets a parameter in the sensor, EMPTY REPLY!
        CmdLuxGetParameter           = 0x0011, //!< reads a parameter from the sensor
        CmdLuxResetDefaultParameters = 0x001A, //!< resets all parameters to the factory defaults, EMPTY REPLY!
        CmdLuxStartMeasure           = 0x0020, //!< starts the measurement with the currently configured settings
        CmdLuxStopMeasure            = 0x0021, //!< stops the measurement
        CmdLuxSetNTPTimestampSync    = 0x0034 //!< set the complete NTPtime stamp, EMPTY REPLY!1
    };

public:
    explicit CommandId(const uint16_t cId) : ibeo::common::sdk::ComparableUnconvertable<uint16_t>(cId) {}
    CommandId(const Id c) : ibeo::common::sdk::ComparableUnconvertable<uint16_t>(uint16_t(c)) {}

    operator Id() { return static_cast<Id>(m_data); }

public: // BE io
    std::istream& readBE(std::istream& is)
    {
        ibeo::common::sdk::readBE(is, this->m_data);
        return is;
    }

    std::ostream& writeBE(std::ostream& os) const
    {
        ibeo::common::sdk::writeBE(os, this->m_data);
        return os;
    }

    void readBE(const char*& target) { ibeo::common::sdk::readBE(target, this->m_data); }
    void writeBE(char*& target) const { ibeo::common::sdk::writeBE(target, this->m_data); }

public: // LE io
    std::istream& readLE(std::istream& is)
    {
        ibeo::common::sdk::readLE(is, this->m_data);
        return is;
    }

    std::ostream& writeLE(std::ostream& os) const
    {
        ibeo::common::sdk::writeLE(os, this->m_data);
        return os;
    }

    void readLE(const char*& target) { ibeo::common::sdk::readLE(target, this->m_data); }
    void writeLE(char*& target) const { ibeo::common::sdk::writeLE(target, this->m_data); }

public: // friend functions for serialization
    template<typename TT>
    friend void readBE(std::istream& is, TT& value);
    template<typename TT>
    friend void readLE(std::istream& is, TT& value);
    template<typename TT>
    friend void writeBE(std::ostream& os, const TT& value);
    template<typename TT>
    friend void writeLE(std::ostream& os, const TT& value);

}; // CommandId

//==============================================================================

//==============================================================================

template<>
inline std::string toHex<CommandId>(const CommandId c)
{
    return toHex(uint16_t(c));
}

//==============================================================================
template<>
inline void readBE<CommandId>(std::istream& is, CommandId& c)
{
    ibeo::common::sdk::readBE(is, c.m_data);
}

//==============================================================================
template<>
inline void readLE<CommandId>(std::istream& is, CommandId& c)
{
    ibeo::common::sdk::readLE(is, c.m_data);
}

//==============================================================================
template<>
inline void writeBE<CommandId>(std::ostream& os, const CommandId& c)
{
    ibeo::common::sdk::writeBE(os, c.m_data);
}

//==============================================================================
template<>
inline void writeLE<CommandId>(std::ostream& os, const CommandId& c)
{
    ibeo::common::sdk::writeLE(os, c.m_data);
}

////========================================
////========================================
////========================================
//template<> inline
//void readBE<CommandId::Id>(std::istream& is, CommandId::Id& c)
//{
//	uint16_t id;
//	ibeo::common::sdk::readBE(is, id);
//	c = static_cast<CommandId::Id>(id);
//}
//
////========================================
//template<> inline
//void readLE<CommandId::Id>(std::istream& is, CommandId::Id& c)
//{
//	uint16_t id;
//	ibeo::common::sdk::readLE(is, id);
//	c = static_cast<CommandId::Id>(id);
//}
//
////========================================
//template<> inline
//void writeBE<CommandId::Id>(std::ostream& os, const CommandId::Id& c)
//{
//	ibeo::common::sdk::writeBE(os, static_cast<uint16_t>(c));
//}
//
////========================================
//template<> inline
//void writeLE<CommandId::Id>(std::ostream& os, const CommandId::Id& c)
//{
//	ibeo::common::sdk::writeLE(os, static_cast<uint16_t>(c));
//}

//==============================================================================

std::ostream& operator<<(std::ostream& os, const CommandId& cmdId);
std::ostream& operator<<(std::ostream& os, const CommandId::Id& cmdId);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

//==============================================================================
namespace boost {
template<>
struct hash<ibeo::common::sdk::CommandId> : public std::unary_function<ibeo::common::sdk::CommandId, std::size_t>
{
    std::size_t operator()(ibeo::common::sdk::CommandId const& cId) const { return boost::hash_value(uint16_t(cId)); }
}; // hash<ibeo::common::sdk::CommandId>
} // namespace boost
//==============================================================================

//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Feb 21, 2017
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include "../misc/WinCompatibility.hpp"
#include "../misc/deprecatedwarning.hpp"

#include "../Time.hpp"
#include "../Math.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class ClockType
{
public:
    enum class ClockName : uint8_t
    {
        Unknown      = 0, //!< Clock_Unknown
        Laserscanner = 1, //!< Clock_Laserscanner
        Ecu          = 2, //!< Clock_ECU
        CanBus       = 3, //!< Clock_CanBus
        Camera       = 4, //!< Clock_Camera
        GpsImu       = 5, //!< Clock_GpsImu
        Dut          = 6, //!< Clock_DUT
        Other        = 255 //!< Clock_Other
    };

    static constexpr uint8_t unknownId = 0xFF;

public:
    ClockType();
    ClockType(const uint8_t clockId, const ClockName clockName);
    virtual ~ClockType();

public:
    std::streamsize getSerializedSize() const;
    bool deserialize(std::istream& is);
    bool serialize(std::ostream& os) const;

public: //getter
    uint8_t getClockId() const { return m_clockId; }
    ClockName getClockName() const { return m_clockName; }
    std::string getClockNameString(const ClockName cn);
    bool operator<(const ClockType& other) const;

public: //setter
    void setClockId(const uint8_t clockId) { this->m_clockId = clockId; }
    void setClockName(const ClockName clockName) { this->m_clockName = clockName; }

protected:
    //========================================
    //! \brief A unique ID given to each processing device.
    //!
    //! The ID is required to distinguish between two similar
    //! clock names but from different devices and having
    //! different properties.
    //-------------------------------------
    uint8_t m_clockId;

    //========================================
    //! \brief Name of the clock (enum) indicates the type
    //!        of device it is being received.
    //-------------------------------------
    ClockName m_clockName;
}; // ClockType

//==============================================================================

bool operator==(const ClockType& clk1, const ClockType& clk2);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

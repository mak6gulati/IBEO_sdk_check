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
//!\date Mar 16, 2018
//------------------------------------------------------------------------------

//==============================================================================

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/Timestamp.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

#include <array>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief State of operation at a given time
class StateOfOperation9110 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    constexpr static const uint8_t nbOfReserved = 4;

public:
    enum class Operation : uint8_t
    {
        Off     = 1,
        Standby = 2,
        Ready   = 3,
        Running = 4
    };

    enum class DriverInterrupt : uint8_t
    {
        None     = 1,
        Cancel   = 2,
        Takeover = 3
    };

    using ArrayOfReserved = std::array<uint32_t, nbOfReserved>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.stateofoperation9110"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    StateOfOperation9110();
    ~StateOfOperation9110() override;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    void setTimestamp(const Timestamp& timestamp) { m_timestamp = timestamp; }
    void setOperation(const Operation type) { m_operation = type; }
    void setDriverInterrupt(const DriverInterrupt type) { m_driverInterrupt = type; }
    void setTakeOverRequest(const bool request) { m_takeOverRequest = request; }

    const Timestamp& getTimestamp() const { return m_timestamp; }
    Operation getOperation() const { return m_operation; }
    DriverInterrupt getDriverInterrupt() const { return m_driverInterrupt; }
    bool getTakeOverRequest() const { return m_takeOverRequest; }

    const ArrayOfReserved& getReserved() const { return m_reserved; }

protected:
    Timestamp m_timestamp{}; //!< Timestamp of StateOfOperation
    Operation m_operation{Operation::Off}; //!< operating mode
    DriverInterrupt m_driverInterrupt{DriverInterrupt::None}; //!< interrupt type
    bool m_takeOverRequest{false}; //!< takeOver flag

private:
    ArrayOfReserved m_reserved{{0U, 0U, 0U, 0U}};
}; // StateOfOperation9110

//==============================================================================

bool operator==(const StateOfOperation9110& lhs, const StateOfOperation9110& rhs);
bool operator!=(const StateOfOperation9110& lhs, const StateOfOperation9110& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

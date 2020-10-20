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
//!\date Jan 29, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

#include <vector>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Serialisation of incoming OGpsImu UDP packets
//!
//! General data type: \ref ibeo::common::sdk::OGpsImuMessage
class OGpsImuMessage2610 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.ogpsimumessage2610"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    OGpsImuMessage2610();
    virtual ~OGpsImuMessage2610();

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public: // getter
    uint32_t getIpAddress() const { return m_ipAddress; }
    const std::vector<uint8_t>& getData() const { return m_data; }
    std::vector<uint8_t>& getData() { return m_data; }

public: // setter
    void setIpAddress(const uint32_t ipAddress) { m_ipAddress = ipAddress; }

protected:
    uint32_t m_ipAddress{0};
    std::vector<uint8_t> m_data{};
}; // OGpsImuMessage2610

//==============================================================================

bool operator==(const OGpsImuMessage2610& lhs, const OGpsImuMessage2610& rhs);
bool operator!=(const OGpsImuMessage2610& lhs, const OGpsImuMessage2610& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

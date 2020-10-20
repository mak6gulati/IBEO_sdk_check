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
//! \date Jan 31, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

#include <ibeo/common/sdk/datablocks/ogpsimumessage/special/OGpsImuMessage2610.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief Serialisation of incoming OGpsImu UDP packets
//!
//! Special data type: \ref ibeo::common::sdk::OGpsImuMessage2610
class OGpsImuMessage : public DataContainerBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

    friend bool operator==(const OGpsImuMessage& lhs, const OGpsImuMessage& rhs);

public:
    constexpr static const char* const containerType{"ibeo.sdk.generalcontainer.ogpsimumessage"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    OGpsImuMessage()          = default;
    virtual ~OGpsImuMessage() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public: // getter
    uint32_t getIpAddress() const { return m_delegate.getIpAddress(); }
    const std::vector<uint8_t>& getData() const { return m_delegate.getData(); }
    std::vector<uint8_t>& getData() { return m_delegate.getData(); }

public: // setter
    void setIpAddress(const uint32_t ipAddress) { m_delegate.setIpAddress(ipAddress); }

private:
    OGpsImuMessage2610 m_delegate;
}; // OGpsImuMessage

//==============================================================================

inline bool operator==(const OGpsImuMessage& lhs, const OGpsImuMessage& rhs)
{
    return lhs.m_delegate == rhs.m_delegate;
}

inline bool operator!=(const OGpsImuMessage& lhs, const OGpsImuMessage& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

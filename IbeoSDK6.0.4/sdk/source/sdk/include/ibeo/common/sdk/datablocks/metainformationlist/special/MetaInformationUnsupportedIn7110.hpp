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
//! \date Apr 5, 2016
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/metainformationlist/special/MetaInformationBaseIn7110.hpp>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class MetaInformationUnsupportedIn7110 : public MetaInformationBaseIn7110
{
public:
    using DataVector = std::vector<uint8_t>;

public:
    MetaInformationUnsupportedIn7110()
      : MetaInformationBaseIn7110(MetaInformationBaseIn7110::MetaInformationType::Unsupported)
    {}

    MetaInformationUnsupportedIn7110(const uint16_t originalType, const NTPTime timestamp, const uint32_t dataSize)
      : MetaInformationBaseIn7110(MetaInformationBaseIn7110::MetaInformationType::Unsupported, timestamp),
        m_originalType(originalType),
        m_data(dataSize)
    {}

    MetaInformationUnsupportedIn7110(const uint16_t originalType, const NTPTime timestamp, const DataVector& data)
      : MetaInformationBaseIn7110(MetaInformationBaseIn7110::MetaInformationType::Unsupported, timestamp),
        m_originalType(originalType),
        m_data(data)
    {}

    virtual ~MetaInformationUnsupportedIn7110() = default;

public:
    const DataVector& getData() const { return m_data; }
    DataVector& getData() { return m_data; }

    uint16_t getOriginalType() const { return m_originalType; }
    void setOriginalType(const uint16_t type) { m_originalType = type; }

public: // MetaInformationBaseIn7110 interface
    bool isEqual(const MetaInformationBaseIn7110& other) const override;

    bool serialize(std::ostream& os) const override;

    uint32_t getSerializedPayloadSize() const override { return uint32_t(m_data.size()); }
    bool deserializePayload(std::istream& is, const uint32_t payloadSize) override;
    bool serializePayload(std::ostream& os) const override;

private:
    uint16_t m_originalType{static_cast<uint16_t>(MetaInformationBaseIn7110::MetaInformationType::Unsupported)};
    DataVector m_data{};
}; // MetaInformationUnsupportedIn7110

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

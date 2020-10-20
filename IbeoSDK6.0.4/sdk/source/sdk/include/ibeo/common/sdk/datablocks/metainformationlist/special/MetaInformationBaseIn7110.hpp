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

#include "ibeo/common/sdk/misc/WinCompatibility.hpp"

#include "ibeo/common/sdk/Time.hpp"

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

//! Snippet containing data for a meta information
class MetaInformationBaseIn7110
{
public:
    static constexpr uint32_t maxStringLength{std::numeric_limits<uint16_t>::max()};

public:
    //! type of this meta information bit
    enum class MetaInformationType : uint16_t
    {
        Unsupported       = 0,
        VersionNumber     = 1,
        AppBaseConfig     = 2,
        AppBaseSyncMethod = 3,
        EcuId             = 4,
        Keywords          = 5
    }; // MetaInformationType

public:
    explicit MetaInformationBaseIn7110(const MetaInformationType type, const NTPTime timeStamp = NTPTime())
      : m_type(type), m_timeStamp(timeStamp)
    {}
    virtual ~MetaInformationBaseIn7110() = default;

public:
    MetaInformationType getType() const { return m_type; }
    void setTimestamp(const NTPTime& time) { m_timeStamp = time; }
    const NTPTime& getTimestamp() const { return m_timeStamp; }

public:
    virtual bool isEqual(const MetaInformationBaseIn7110& other) const;

public:
    virtual std::streamsize getSerializedSize() const;
    virtual bool deserialize(std::istream& is);

    virtual bool serialize(std::ostream& os) const;

public:
    virtual uint32_t getSerializedPayloadSize() const                             = 0;
    virtual bool deserializePayload(std::istream& is, const uint32_t payloadSize) = 0;
    virtual bool serializePayload(std::ostream& os) const                         = 0;

protected:
    MetaInformationType m_type{MetaInformationType::Unsupported};
    NTPTime m_timeStamp{};
}; // MetaInformationBaseIn7110

//==============================================================================

using MetaInformationBaseIn7110SPtr = std::shared_ptr<MetaInformationBaseIn7110>;

//==============================================================================

inline bool operator==(const MetaInformationBaseIn7110& lhs, const MetaInformationBaseIn7110& rhs)
{
    return lhs.isEqual(rhs);
}

//==============================================================================

inline bool operator!=(const MetaInformationBaseIn7110& lhs, const MetaInformationBaseIn7110& rhs)
{
    return !(lhs == rhs);
}

//==============================================================================

std::ostream& operator<<(std::ostream& os, const MetaInformationBaseIn7110::MetaInformationType t);

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

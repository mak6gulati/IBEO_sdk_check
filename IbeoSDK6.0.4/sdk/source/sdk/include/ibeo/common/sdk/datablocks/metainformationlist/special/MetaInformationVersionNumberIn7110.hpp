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

#include <string>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class MetaInformationVersionNumberIn7110 : public MetaInformationBaseIn7110
{
public:
    enum class SoftwareType : uint16_t
    {
        Undefined = 0,
        Custom    = 1,
        AppBase   = 2,
        EvS       = 3,
        Ilv       = 4
    };

    using VersionNumberType = uint32_t;
    using VersionPartType   = uint16_t;

public:
    MetaInformationVersionNumberIn7110()
      : MetaInformationBaseIn7110(MetaInformationBaseIn7110::MetaInformationType::VersionNumber)
    {}

    virtual ~MetaInformationVersionNumberIn7110() = default;

public:
    VersionNumberType getVersionNumber() const { return m_versionNumber; }
    void setVersionNumber(const uint32_t newVersion) { m_versionNumber = newVersion; }
    void
    setVersionNumber(const uint16_t major, const uint16_t minor, const uint16_t patch, const std::string extra = "");

    void setSoftwareType(const SoftwareType type) { m_softwareType = type; }
    SoftwareType getSoftwareType() const { return m_softwareType; }

    VersionPartType getMajorVersion() const;
    VersionPartType getMinorVersion() const;
    VersionPartType getPatchVersion() const;

    const std::string& getExtraString() const { return m_extraString; }
    void setExtraString(const std::string& extra) { m_extraString = extra; }

public: // MetaInformationBaseIn7110 interface
    virtual bool isEqual(const MetaInformationBaseIn7110& other) const override;
    virtual uint32_t getSerializedPayloadSize() const override;
    virtual bool deserializePayload(std::istream& is, const uint32_t payloadSize) override;
    virtual bool serializePayload(std::ostream& os) const override;

private:
    SoftwareType m_softwareType{SoftwareType::Undefined};
    VersionNumberType m_versionNumber{0};
    std::string m_extraString{};
}; // MetaInformationVersionNumberIn7110

//==============================================================================

std::ostream& operator<<(std::ostream& os, const MetaInformationVersionNumberIn7110::SoftwareType st);

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

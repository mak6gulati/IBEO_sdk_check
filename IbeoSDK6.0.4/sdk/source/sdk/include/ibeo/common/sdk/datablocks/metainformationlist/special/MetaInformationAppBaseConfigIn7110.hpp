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

class MetaInformationAppBaseConfigIn7110 : public MetaInformationBaseIn7110
{
public:
    MetaInformationAppBaseConfigIn7110()
      : MetaInformationBaseIn7110(MetaInformationBaseIn7110::MetaInformationType::AppBaseConfig)
    {}
    virtual ~MetaInformationAppBaseConfigIn7110() = default;

public:
    const std::string& getAppBaseConfig() const { return m_appBaseConfig; }
    void setAppBaseConfig(const std::string& newAppBaseConfig);

public:
    bool isEqual(const MetaInformationBaseIn7110& otherBase) const override;
    uint32_t getSerializedPayloadSize() const override;
    bool deserializePayload(std::istream& is, const uint32_t payloadSize) override;
    bool serializePayload(std::ostream& os) const override;

private:
    std::string m_appBaseConfig{};
}; // MetaInformationAppBaseConfigIn7110

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

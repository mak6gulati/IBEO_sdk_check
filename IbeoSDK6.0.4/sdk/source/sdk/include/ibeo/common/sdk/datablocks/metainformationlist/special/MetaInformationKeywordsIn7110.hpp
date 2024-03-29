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

#include <unordered_set>
#include <vector>
#include <string>

//==============================================================================

namespace ibeo {
namespace common {
namespace sdk {

//==============================================================================

class MetaInformationKeywordsIn7110 : public MetaInformationBaseIn7110
{
public:
    using StringSet    = std::unordered_set<std::string>;
    using StringVector = std::vector<std::string>;

public:
    MetaInformationKeywordsIn7110()
      : MetaInformationBaseIn7110(MetaInformationBaseIn7110::MetaInformationType::Keywords)
    {}
    virtual ~MetaInformationKeywordsIn7110() = default;

public:
    const StringSet& getKeywords() const { return m_keywords; }
    void setKeywords(const StringSet& keywords) { m_keywords = keywords; }

    void addKeyword(const std::string& keyword);
    void deleteKeyword(const std::string& keyword);
    bool containsKeyword(const std::string& keyword);

    StringVector getKeywordsAsVector() const;

public: // MetaInformationBaseIn7110 interface
    bool isEqual(const MetaInformationBaseIn7110& otherBase) const override;
    uint32_t getSerializedPayloadSize() const override;
    bool deserializePayload(std::istream& is, const uint32_t payloadSize) override;
    bool serializePayload(std::ostream& os) const override;

protected:
    StringSet m_keywords{};
}; // MetaInformationKeywordsIn7110

//==============================================================================

} // namespace sdk
} // namespace common
} // namespace ibeo

//==============================================================================

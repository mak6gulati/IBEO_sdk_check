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
//!\date Mar 26, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

class IbeoEvent7001 : public SpecializedDataContainer
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

public:
    constexpr static const char* const containerType{"ibeo.sdk.specialcontainer.ibeoevent7001"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    IbeoEvent7001();
    IbeoEvent7001(const uint16_t type, const std::string& body, const std::string& author);
    IbeoEvent7001(const uint16_t type, const char* const body, const char* const author);

    virtual ~IbeoEvent7001() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public: // Getter
    uint16_t getType() const { return m_type; }
    const std::string& getBody() const { return m_body; }
    const std::string& getAuthor() const { return m_author; }

public: // Setter
    void setType(const uint16_t type) { m_type = type; }
    void setBody(const std::string& b) { m_body = b; }
    void setAuthor(const std::string& a) { m_author = a; }

protected:
    uint16_t m_type; // Type of event
    std::string m_body; // Payload
    std::string m_author; // Authorship: for now, no real semantics
}; // IbeoEvent7001

//==============================================================================

bool operator==(const IbeoEvent7001& lhs, const IbeoEvent7001& rhs);
bool operator!=(const IbeoEvent7001& lhs, const IbeoEvent7001& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

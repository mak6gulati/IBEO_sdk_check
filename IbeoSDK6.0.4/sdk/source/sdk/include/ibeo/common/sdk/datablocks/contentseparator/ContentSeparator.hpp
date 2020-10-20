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
//!\date Feb 4, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>
#include <ibeo/common/sdk/datablocks/Timestamp.hpp>

#include <ibeo/common/sdk/datablocks/contentseparator/special/ContentSeparator7100.hpp>

#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

using ContentSeparatorType = ContentSeparatorTypeIn7100;

//==============================================================================

//! \brief ibeo content separator
//!
//! Special data container: ibeo::common::sdk::ContentSeparator7100
class ContentSeparator : public DataContainerBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

    friend bool operator==(const ContentSeparator& lhs, const ContentSeparator& rhs);

public:
    constexpr static const char* const containerType{"ibeo.sdk.generalcontainer.contentseparator"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    ContentSeparator();
    ~ContentSeparator() override = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public: // getter
    ContentSeparatorType getSeparatorType() const { return m_delegate.getSeparatorType(); }
    uint32_t getContentSize() const { return m_delegate.getContentSize(); }

public: // setter
    void setSeparatorType(const ContentSeparatorType newSeparatorType)
    {
        m_delegate.setSeparatorType(newSeparatorType);
    }
    void setContentSize(const uint32_t size) { m_delegate.setContentSize(size); }

protected:
    ContentSeparator7100 m_delegate; // only possible specialization currently
}; // GpsImuContainer

//==============================================================================

bool operator==(const ContentSeparator& lhs, const ContentSeparator& rhs);
bool operator!=(const ContentSeparator& lhs, const ContentSeparator& rhs);

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================

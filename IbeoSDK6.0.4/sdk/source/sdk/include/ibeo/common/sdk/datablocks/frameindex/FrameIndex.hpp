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
//! \date Jan 24, 2019
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/frameindex/special/FrameIndex6130.hpp>
#include <ibeo/common/sdk/datablocks/frameindex/FramingPolicy.hpp>
#include <ibeo/common/sdk/datablocks/frameindex/FrameIndexEntry.hpp>
#include <ibeo/common/sdk/datablocks/DataContainerBase.hpp>

#include <ibeo/common/sdk/Time.hpp>
#include <ibeo/common/sdk/misc/IbeoSdkHash.hpp>

#include <vector>
#include <string>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//! \brief frame index
//!
//! Special data type:
//! \ref ibeo::common::sdk::FrameIndex6130
class FrameIndex : public DataContainerBase
{
    template<class ContainerType, DataTypeId::DataType id>
    friend class Importer;
    template<class ContainerType, DataTypeId::DataType id>
    friend class Exporter;

    friend bool operator==(const FrameIndex& lhs, const FrameIndex& rhs);

public:
    using FrameVector = std::vector<FrameIndexEntry>;

public:
    constexpr static const char* const containerType{"ibeo.sdk.generalcontainer.frameindex"};

    static constexpr uint64_t getClassIdHashStatic() { return hash(containerType); }

public:
    FrameIndex() : DataContainerBase() {}
    virtual ~FrameIndex() = default;

public:
    uint64_t getClassIdHash() const override { return getClassIdHashStatic(); }

public:
    const FramingPolicy& getFramingPolicy() const { return m_delegate.getFramingPolicy(); }

    const FrameVector& getFrameIndices() const { return m_delegate.getFrameIndices(); }
    FrameVector getFrameIndices() { return m_delegate.getFrameIndices(); }

    uint64_t getTimeOffsetMs() const { return m_delegate.getTimeOffsetMs(); }

public:
    void setFramingPolicy(const FramingPolicy& policy) { m_delegate.setFramingPolicy(policy); }
    void setFrameIndices(const FrameVector& frameIndices) { m_delegate.setFrameIndices(frameIndices); }

public:
    void addFrame(const FrameIndexEntry& entry) { m_delegate.addFrame(entry); }
    void clearFrames() { m_delegate.clearFrames(); }

public:
    static constexpr uint8_t majorVersion{FrameIndex6130::majorVersion};
    static constexpr uint8_t minorVersion{FrameIndex6130::minorVersion};
    constexpr static const char* const nameString{FrameIndex6130::nameString};

private:
    FrameIndex6130 m_delegate;
}; // FrameIndex

//==============================================================================

inline bool operator==(const FrameIndex& lhs, const FrameIndex& rhs) { return (lhs.m_delegate == rhs.m_delegate); }

inline bool operator!=(const FrameIndex& lhs, const FrameIndex& rhs) { return !(lhs == rhs); }

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
